from flask import Flask, jsonify, request, make_response, abort
from flask_cors import CORS, cross_origin
import psycopg2
from hashlib import sha256
import jwt
from datetime import datetime, timezone, timedelta
from flask import Blueprint

app = Flask(__name__)
CORS(app, supports_credentials=True, resources={r"/api/*": {"origins": "http://localhost:43879/"}})
app.config['CORS_HEADERS'] = 'Content-Type, Authorization, X-Auth-Token, Access-Control-Allow-Origin, Access-Control-Allow-Credentials'
app.config['CORS_METHODS'] = 'GET, POST, PUT, DELETE, OPTIONS'

app.config['SECRET_KEY'] = '12345'

conn = psycopg2.connect("dbname=wwwlab user=appuser password=appuser host=wwwlab-database")

@app.route("/api/debug-headers")
def debug_headers():
    auth_header = request.headers.get('Authorization')
    
    if auth_header:
        return {"Response": check_token(request)}
    else:
        return {k: v for k, v in request.headers.items()}

def check_token(request):
    auth_header = request.headers.get('Authorization')

    if not auth_header:
        abort(401, 'No authentication token present')

    parts = auth_header.split()

    if len(parts) != 2 or parts[0] != 'Bearer':
        abort(403, 'Invalid Authorization Header.')

    token = parts[1]

    try:
        data = jwt.decode(token, app.config['SECRET_KEY'], algorithms=["HS256"])
    except jwt.ExpiredSignatureError:
        abort(401, 'Session expired.')
    except jwt.InvalidTokenError:
        abort(403, 'Token is invalid!')

    user_id = data.get('id')
    if not user_id:
        abort(403, 'Token is invalid!')

    return user_id


def hash_password(password):
    return sha256(bytes(password, 'utf-8')).hexdigest()

def check_password_hash(password, potential_password):
    return password == hash_password(potential_password)

@app.errorhandler(400)
def bad_request(e):
    return jsonify({'message': e.description}), 400

@app.errorhandler(401)
def unauthorized(e):
    return jsonify({'message': e.description}), 401

@app.errorhandler(403)
def forbidden(e):
    return jsonify({'message': e.description}), 403

# Login
@app.route('/api/login', methods=['POST'])
@cross_origin()
def login():
    if request.is_json:
        data = request.get_json()
        username = data["username"]
        password = data["password"]
    else:
        username = request.form['username']
        password = request.form['password']

    cur = conn.cursor()

    cur.execute(f"SELECT id, password FROM Users WHERE username='{username}'")
    user = cur.fetchone()

    if not user or not check_password_hash(user[1], password):
        return jsonify({'message': 'Invalid email or password'}), 400
    
    token = jwt.encode({'id': user[0], 'exp': datetime.now(timezone.utc) + timedelta(hours=1)},
                    app.config['SECRET_KEY'], algorithm="HS256")
    
    cur.close()

    resp = jsonify({'message': 'Login successful'})
    resp.set_cookie('access_token', f'{token}', httponly=False, samesite='Strict', secure=True)
    return resp

# Register
@app.route('/api/register', methods=['POST'])
@cross_origin()
def register():
    if request.is_json:
        data = request.get_json()
        username = data["username"]
        password = data["password"]
    else:
        username = request.form['username']
        password = request.form['password']

    cur = conn.cursor()

    if len(username) < 4:
        return jsonify({'message': 'Username must be at least 4 characters long.'}), 400

    if len(password) < 4:
        return jsonify({'message': 'Password must be at least 4 characters long.'}), 400
    
    if len(username) > 64:
        return jsonify({'message': 'Username might be at most 64 characters long.'}), 400

    if len(password) > 64:
        return jsonify({'message': 'Password might be at most 64 characters long.'}), 400

    cur.execute(f"SELECT id FROM Users WHERE username='{username}'")
    existing_user = cur.fetchone()

    if existing_user:
        return jsonify({'message': 'User already exists. Please login.'}), 400
    
    hashed_password = hash_password(password)

    cur.execute(f"INSERT INTO Users (type, username, password) VALUES ('user','{username}', '{hashed_password}');")
    
    conn.commit()
    cur.close()

    return jsonify({'message': 'User registered successfully.'}), 201

# Return user info
@app.route('/api/users/me', methods=['GET'])
@cross_origin()
def get_user_info():
    user_id = check_token(request)

    cur = conn.cursor()

    cur.execute(f"SELECT type, username FROM Users WHERE id='{user_id}'")
    user_info = cur.fetchone()

    if not user_info:
        cur.close()
        return jsonify({'message': 'User not found.'}), 404

    user_type, username = user_info
    cur.close()

    return jsonify({'id': user_id, 'username': username, 'type': user_type}), 200

# Delete your account
@app.route('/api/users/me', methods=['DELETE'])
@cross_origin()
def del_account():
    user_id = check_token(request)

    cur = conn.cursor()

    cur.execute(f"DELETE FROM Users WHERE id='{user_id}'")

    conn.commit()
    cur.close()
    return jsonify({'message': 'Deleted account'}), 200

# Manage Users
@app.route('/api/users/', methods=['GET', 'POST'])
@cross_origin()
def manage_users():
    user_id = check_token(request)
    cur = conn.cursor()

    # Check if current user is admin
    cur.execute(f"SELECT type FROM Users WHERE id = {user_id}")
    user_type = cur.fetchone()[0]

    if user_type != 'admin':
        cur.close()
        return jsonify({'message': 'Access denied.'}), 403

    # GET: List all users
    if request.method == 'GET':
        cur.execute("SELECT id, username, type FROM Users")
        users = cur.fetchall()
        cur.close()
        user_list = [{'id': u[0], 'username': u[1], 'type': u[2]} for u in users]
        return jsonify({'users': user_list}), 200

    # POST: Create a new user
    if request.is_json:
        data = request.get_json()
    else:
        data = request.form

    new_username = data.get('username')
    new_password = data.get('password')
    new_type = data.get('type', 'user')

    if not new_username or not new_password:
        cur.close()
        return jsonify({'message': 'Username and password are required.'}), 400
    
    if len(new_username) < 4:
        return jsonify({'message': 'Username must be at least 4 characters long.'}), 400

    if len(new_password) < 4:
        return jsonify({'message': 'Password must be at least 4 characters long.'}), 400
    
    if len(new_username) > 64:
        return jsonify({'message': 'Username might be at most 64 characters long.'}), 400

    if len(new_password) > 64:
        return jsonify({'message': 'Password might be at most 64 characters long.'}), 400


    if new_type not in ['user', 'admin']:
        cur.close()
        return jsonify({'message': 'Invalid user type.'}), 400

    cur.execute(f"SELECT id FROM Users WHERE username = '{new_username}'")
    if cur.fetchone():
        cur.close()
        return jsonify({'message': 'User already exists.'}), 400

    hashed_pw = hash_password(new_password)

    cur.execute(f"INSERT INTO Users (username, password, type) VALUES ('{new_username}', '{hashed_pw}', '{new_type}');")

    conn.commit()
    cur.close()
    return jsonify({'message': 'User created successfully.'}), 201

# Delete users
@app.route('/api/users/<int:target_user_id>', methods=['DELETE'])
@cross_origin()
def delete_user(target_user_id):
    user_id = check_token(request)
    cur = conn.cursor()

    # Check if current user is admin
    cur.execute(f"SELECT type FROM Users WHERE id = {user_id}")
    user_type = cur.fetchone()[0]

    if user_type != 'admin':
        cur.close()
        return jsonify({'message': 'Access denied.'}), 403

    # Check if user exists
    cur.execute(f"SELECT id FROM Users WHERE id = {target_user_id}")
    if not cur.fetchone():
        cur.close()
        return jsonify({'message': 'User not found.'}), 404

    cur.execute(f"DELETE FROM Users WHERE id = {target_user_id}")
    conn.commit()
    cur.close()
    return jsonify({'message': 'User deleted successfully.'}), 200

# Products
@app.route('/api/products/', methods=['GET', 'POST'])
@cross_origin()
def products():
    cur = conn.cursor()
    if request.method == 'GET':
        page = request.args.get("page")
        page_size = 5

        less = request.args.get("less")
        more = request.args.get("more")
        which = 0

        if less:
            if not str(less).isnumeric():
                return jsonify({'message': "Less has to be a positive number."}), 400
            less = int(less)
            if less < 1:
                return jsonify({'message': "Less has to be a positive number."}), 400
            which += 1
        if more:
            if not str(more).isnumeric():
                return jsonify({'message': "More has to be a nonnegative number."}), 400
            more = int(more)
            if more < 0:
                return jsonify({'message': "More has to be a nonnegative number."}), 400
            which += 2

        sort = request.args.get("sort")
        desc = request.args.get("desc")

        query = "SELECT * FROM Products"

        match which:
            case 1:
                query += f" WHERE price < {less}"
            case 2:
                query += f" WHERE price > {more}"
            case 3:
                if more >= less:
                    return jsonify({'message': "More should be smaller than less."}), 400
                query += f" WHERE price < {less} AND price > {more}"

        if sort:
            if sort.lower() in ["price", "name", "description"]:
                query += f" ORDER BY {sort.lower()}"
                if desc:
                    if desc.lower() == "true":
                        query += f" DESC"
        elif desc:
            return jsonify({'message': "What do you wanna sort by?"}), 400
                
        query += ";"

        cur.execute(query)
        results = cur.fetchall()
        ans = []
        for result in results:
            ans.append({"id": result[0], "name": result[1], "description": result[2], "price": result[3] / 100})
        cur.close()
        if page:
            if not page.isnumeric():
                return jsonify({'message': "Page has to be a positive number."}), 400
            
            page = int(page)
            if page < 1:
                return jsonify({'message': "Page has to be a positive number."}), 400
            if (page - 1) * page_size > len(ans):
                return jsonify({'message': "No such page."}), 400
            ans = ans[(page - 1) * page_size: page * page_size]

        return jsonify({'products': ans}), 200
    if request.method == 'POST':
        user_id = check_token(request)
        cur.execute(f"SELECT type FROM Users WHERE id='{user_id}';")
        user_type = cur.fetchone()[0]
        
        if user_type != 'admin':
            cur.close()
            return jsonify({'message': 'Access denied.'}), 403
        
        if request.is_json:
            data = request.get_json()
            name = data["name"]
            description = data["description"]
            price = data["price"]
        else:
            name = request.form["name"]
            description = request.form["description"]
            price = request.form["price"]

        if len(name) < 4:
            return jsonify({'message': "Name must be at least 4 characters long."}), 400

        if len(description) < 5:
            return jsonify({'message': "Description must be at least 5 characters long."}), 400

        if not str(price).isnumeric():
            return jsonify({'message': "Price must be a positive number."}), 400

        price = int(price)

        if price < 1:
            cur.close()
            return jsonify({'message': "Price must be positive."}), 400
        
        cur.execute(f"SELECT id FROM Products WHERE description = '{description}'")
        if cur.fetchone():
            cur.close()
            return jsonify({'message': 'Product already exists.'}), 400

            
        cur.execute(f"INSERT INTO Products (name, description, price) VALUES ('{name}', '{description}', {price});")
        conn.commit()
        cur.close()
        return jsonify({'message': "Added product."}), 201

@app.route('/api/products/<int:product_id>', methods=['PUT', 'DELETE'])
@cross_origin()
def edit_product(product_id):
    if request.method == 'PUT':
        user_id = check_token(request)
        cur = conn.cursor()

        cur.execute(f"SELECT type FROM Users WHERE id = {user_id};")
        user_type = cur.fetchone()[0]
        if user_type != 'admin':
            cur.close()
            return jsonify({'message': 'Access denied.'}), 403

        if request.is_json:
            data = request.get_json()
        else:
            data = request.form

        name = data.get("name")
        description = data.get("description")
        price = data.get("price")

        if not any([name, description, price]):
            cur.close()
            return jsonify({'message': 'At least one field (name, description, price) must be provided'}), 400

        # Build update query dynamically
        fields = []

        if name:
            if len(name) < 4:
                return jsonify({'message': "Name must be at least 4 characters long."}), 400
            fields.append(f"name = '{name}'")
        if description:
            if len(description) < 5:
                return jsonify({'message': "Description must be at least 5 characters long."}), 400
            fields.append(f"description = '{description}'")
        if price or price == 0:
            if not str(price).isnumeric():
                return jsonify({'message': "Price must be a positive number."}), 400
            price = int(price)

            if price < 1:
                cur.close()
                return jsonify({'message': "Price must be positive."}), 400
            fields.append(f"price = {price}")

        cur.execute(f"UPDATE Products SET {', '.join(fields)} WHERE id = {product_id};")

        if cur.rowcount == 0:
            cur.close()
            return jsonify({'message': 'Product not found'}), 404

        conn.commit()
        cur.close()
        return jsonify({'message': 'Product updated successfully'}), 200
    if request.method == 'DELETE':
        user_id = check_token(request)
        cur = conn.cursor()

        # Check if user is admin
        cur.execute(f"SELECT type FROM Users WHERE id = {user_id};")
        user_type = cur.fetchone()[0]

        if user_type != 'admin':
            cur.close()
            return jsonify({'message': 'Access denied.'}), 403

        # Check if product exists
        cur.execute(f"SELECT id FROM Products WHERE id = {product_id};")
        if not cur.fetchone():
            cur.close()
            return jsonify({'message': 'Product not found'}), 404

        # Delete the product
        cur.execute(f"DELETE FROM Products WHERE id = {product_id};")
        conn.commit()
        cur.close()

        return jsonify({'message': 'Product deleted successfully'}), 200

# Reviews
@app.route('/api/products/<int:product_id>/reviews', methods=['POST', 'PUT', 'DELETE'])
@cross_origin()
def handle_reviews(product_id):
    user_id = check_token(request)
    cur = conn.cursor()

    if request.is_json:
        data = request.get_json()
    else:
        data = request.form

    # POST: Add a review
    if request.method == 'POST':
        rating = data.get('rating')
        if not rating and rating != 0:
            return jsonify({'message': 'Rating is required'}), 400
        
        if not str(rating).isnumeric():
            return jsonify({'message': 'Rating has to be a number 1-10'}), 400
        
        rating = int(rating)

        if rating < 1 or rating > 10:
            return jsonify({'message': 'Rating has to be a number 1-10'}), 400

        # Check if review already exists
        cur.execute(f"SELECT id FROM Reviews WHERE user_id = {user_id} AND product_id = {product_id}")
        existing = cur.fetchone()

        if existing:
            return jsonify({'message': 'Review already exists for this product'}), 400

        # Add new review
        cur.execute(f"INSERT INTO Reviews (user_id, product_id, rating) VALUES ({user_id}, {product_id}, {rating})")
        conn.commit()
        cur.close()
        return jsonify({'message': 'Review added successfully'}), 201

    # PUT: Edit existing review
    elif request.method == 'PUT':
        rating = data.get('rating')
        if not rating and rating != 0:
            return jsonify({'message': 'Rating is required'}), 400
        
        if not str(rating).isnumeric():
            return jsonify({'message': 'Rating has to be a number 1-10'}), 400
        
        rating = int(rating)

        if rating < 1 or rating > 10:
            return jsonify({'message': 'Rating has to be a number 1-10'}), 400

        cur.execute(f"UPDATE Reviews SET rating = {rating} WHERE user_id = {user_id} AND product_id = {product_id}")

        if cur.rowcount == 0:
            cur.close()
            return jsonify({'message': 'Review does not exist'}), 404

        conn.commit()
        cur.close()
        return jsonify({'message': 'Review updated successfully'}), 200

    # DELETE: Remove review
    elif request.method == 'DELETE':
        cur.execute(f"DELETE FROM Reviews WHERE user_id = {user_id} AND product_id = {product_id}")

        if cur.rowcount == 0:
            cur.close()
            return jsonify({'message': 'Review does not exist'}), 404

        conn.commit()
        cur.close()
        return jsonify({'message': 'Review deleted successfully'}), 200

# Get Reviews
@app.route('/api/products/<int:product_id>/reviews', methods=['GET'])
@cross_origin()
def get_reviews(product_id):
    cur = conn.cursor()
    cur.execute(f"SELECT Users.username, Reviews.rating FROM Reviews JOIN Users ON Reviews.user_id = Users.id WHERE Reviews.product_id = {product_id}")
    results = cur.fetchall()
    reviews = [{'username': r[0], 'rating': r[1]} for r in results]
    cur.close()
    return jsonify({'reviews': reviews}), 200



if __name__ == '__main__':
    app.run(port=5000, debug=True)

    conn.close()