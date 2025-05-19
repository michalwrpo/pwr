# Test dla list 4
## Michał Waluś
Authorization: <br>
Typ: <br>
Link: http://localhost:5000/ <br>
Body:
```json

```
Output:
```json

```
Code:

Testy robione za pomocą programu postman. Authorization - odnosi się do nagłówka o tej samej nazwie, jeśli wpisane użytkownik/administrator to znajduje się tam "Bearer (token)", gdzie token jest tokenem JWT dla odpowiedniego typu konta.

### Użytkownicy

#### Login (konto nie istnieje)

Authorization: brak (nie wpływa) <br>
Typ: POST <br>
Link: http://localhost:5000/login <br>
Body:
```json
{
    "username":"test",
    "password":"test"
}
```
Output:
```json
{
    "message": "Invalid email or password"
}
```
Code: 400

#### Rejestracja

Authorization: brak (nie wpływa) <br>
Typ: POST <br>
Link: http://localhost:5000/register <br>
Body:
```json
{
    "username":"test",
    "password":"test"
}
```
Output:
```json
{
    "message": "User registered successfully."
}
```
Code: 200

#### Rejestracja (Użytkownik istnieje)

Authorization: brak (nie wpływa) <br>
Typ: POST <br>
Link: http://localhost:5000/register <br>
Body:
```json
{
    "username":"test",
    "password":"test"
}
```
Output:
```json
{
    "message": "User already exists. Please login."
}
```
Code: 400

#### Rejestracja (Błędne dane)

Authorization: brak (nie wpływa) <br>
Typ: POST <br>
Link: http://localhost:5000/register <br>
Body (4 zapytania):
```json
{
    "username":"",
    "password":"test"
}
{
    "username":"a",
    "password":"test"
}
{
    "username":"ab",
    "password":"test"
}
{
    "username":"abc",
    "password":"test"
}
```
Output:
```json
{
    "message": "Username must be at least 4 characters long."
}
```
Code: 400

Authorization: brak (nie wpływa) <br>
Typ: POST <br>
Link: http://localhost:5000/register <br>
Body (4 zapytania):
```json
{
    "username":"test",
    "password":""
}
{
    "username":"test",
    "password":"a"
}
{
    "username":"test",
    "password":"ab"
}
{
    "username":"test",
    "password":"abc"
}
```
Output:
```json
{
    "message": "Password must be at least 4 characters long."
}
```
Code: 400

Authorization: brak (nie wpływa) <br>
Typ: POST <br>
Link: http://localhost:5000/register <br>
Body (4 zapytania):
```json
{
    "username":"1234567890_1234567890_1234567890_1234567890_1234567890_1234567890",
    "password":"test"
}

```
Output:
```json
{
    "message": "Username might be at most 64 characters long."
}
```
Code: 400

Authorization: brak (nie wpływa) <br>
Typ: POST <br>
Link: http://localhost:5000/register <br>
Body (4 zapytania):
```json
{
    "username":"test",
    "password":"1234567890_1234567890_1234567890_1234567890_1234567890_1234567890"
}
```
Output:
```json
{
    "message": "Password might be at most 64 characters long."
}
```
Code: 400

#### Logowanie 

Authorization: brak (nie wpływa) <br>
Typ: POST <br>
Link: http://localhost:5000/login <br>
Body:
```json
{
    "username":"test",
    "password":"test"
}
```
Output:
```json
{
    "access_token": "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJpZCI6MywiZXhwIjoxNzQ3NjE3NTY2fQ.AcdVW_P4eJ4faBYhU_HUS3Sl_gk8qj9hae2BoPkYg6g"
}
```
Code: 200

Authorization: brak (nie wpływa) <br>
Link: http://localhost:5000/login <br>
Body:
```json
{
    "username":"Admin",
    "password":"adminadmin"
}
```
Output:
```json
{
    "access_token": "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJpZCI6MSwiZXhwIjoxNzQ3NjE3NjM2fQ.dShkuRXfQEJrjY-x4xpoTZ80iY2a6rSHJ1Z2wdpmcBQ"
}
```
Code: 200

#### GET (list użytkowników)

Authorization: Użytkownik <br>
Typ: GET <br>
Link: http://localhost:5000/users <br>
Output:
```json
{
    "message": "Access denied."
}
```
Code: 403

Authorization: Brak <br>
Typ: GET <br>
Link: http://localhost:5000/users <br>
Output:
```json
{
    "message": "No authentication token present"
}
```
Code: 401

Authorization: Administrator <br>
Typ: GET <br>
Link: http://localhost:5000/users <br>
Output:
```json
{
    "users": [
        {
            "id": 1,
            "type": "admin",
            "username": "Admin"
        },
        {
            "id": 3,
            "type": "user",
            "username": "test"
        }
    ]
}
```
Code: 200

#### POST (nowy użytkownik)

Authorization: Brak <br>
Typ: POST <br>
Link: http://localhost:5000/users <br>
Body:
```json
{
    "username":"JanKowalski",
    "password":"1234",
    "type":"user"
}
```
Output:
```json
{
    "message": "No authentication token present"
}
```
Code: 401

Authorization: Użytkownik <br>
Typ: POST <br>
Link: http://localhost:5000/users <br>
Body:
```json
{
    "username":"JanKowalski",
    "password":"1234",
    "type":"user"
}
```
Output:
```json
{
    "message": "Access denied."
}
```
Code: 403

Authorization: Administrator <br>
Typ: POST <br>
Link: http://localhost:5000/users <br>
Body:
```json
{
    "username":"JanKowalski",
    "password":"1234",
    "type":"user"
}
```
Output:
```json
{
    "message": "User created successfully."
}
```
Code: 200

Authorization: Administrator <br>
Typ: POST <br>
Link: http://localhost:5000/users <br>
Body:
```json
{
    "username":"JanuszKowalski",
    "password":"12345",
    "type":"admin"
}
```
Output:
```json
{
    "message": "User created successfully."
}
```
Code: 200

#### POST (niewłaściwy typ)

Authorization: Administrator <br>
Typ: POST <br>
Link: http://localhost:5000/users <br>
Body:
```json
{
    "username":"JanekKowalski",
    "password":"12345",
    "type":""
}
```
Output:
```json
{
    "message": "Invalid user type."
}
```
Code: 200

#### POST (próba stworzenia istniejącego użytkownika)

Authorization: Administrator <br>
Typ: POST <br>
Link: http://localhost:5000/users <br>
Body:
```json
{
    "username":"JanKowalski",
    "password":"1234",
    "type":"user"
}
```
Output:
```json
{
    "message": "User already exists."
}
```
Code: 400

#### DELETE (Usuwanie konta)

Authorization: Użytkownik (zalogowany jako JanKowalski) <br>
Typ: DELETE<br>
Link: http://localhost:5000/users <br>
Body: brak
Output:
```json
{
    "message": "Deleted account"
}
```
Code: 200

Authorization: Brak <br>
Typ: DELETE<br>
Link: http://localhost:5000/users <br>
Body: brak
Output:
```json
{
    "message": "No authentication token present"
}
```
Code: 401

Lista użytkowników w tym momencie:
```json
{
    "users": [
        {
            "id": 1,
            "type": "admin",
            "username": "Admin"
        },
        {
            "id": 3,
            "type": "user",
            "username": "test"
        },
        {
            "id": 6,
            "type": "admin",
            "username": "JanuszKowalski"
        }
    ]
}
```

#### DELETE (Usuwanie innych użytkowników)

Authorization: Użytkownik <br>
Typ: DELETE<br>
Link: http://localhost:5000/users/6 <br>
Body: brak
Output:
```json
{
    "message": "Access denied."
}
```
Code: 403

Authorization: Administrator <br>
Typ: DELETE<br>
Link: http://localhost:5000/users/6 <br>
Body: brak
Output:
```json
{
    "message": "User deleted successfully."
}
```
Code: 200

### Produkty 

#### GET (Lista produktów)

Authorization: Brak (nie ma znaczenia) <br>
Typ: GET <br>
Link: http://localhost:5000/products <br>
Body: brak
Output:
```json
{
    "products": [
        {
            "description": "A cheap Brick",
            "id": 1,
            "name": "Brick",
            "price": 7.0
        },
        {
            "description": "A cheap Brick too",
            "id": 3,
            "name": "Brick",
            "price": 7.0
        },
        {
            "description": "Perfect for bricks",
            "id": 8,
            "name": "Mortar",
            "price": 40.0
        }
    ]
}
```
Code: 200

#### POST (Dodawanie)

Authorization: Brak <br>
Typ: POST <br>
Link: http://localhost:5000/products <br>
Body:
```json
{
    "name": "Plank",
    "description": "Oak wood",
    "price": 350
}
```
Output:
```json
{
    "message": "No authentication token present"
}
```
Code: 401

Authorization: Użytkownik <br>
Typ: POST <br>
Link: http://localhost:5000/products <br>
Body:
```json
{
    "name": "Plank",
    "description": "Oak wood",
    "price": 350
}
```
Output:
```json
{
    "message": "Access denied."
}
```
Code: 403

Authorization: Administrator <br>
Typ: POST <br>
Link: http://localhost:5000/products <br>
Body:
```json
{
    "name": "Plank",
    "description": "Oak wood",
    "price": 350
}
```
Output:
```json
{
    "message": "Added product."
}
```
Code: 200

Authorization: Administrator <br>
Typ: POST <br>
Link: http://localhost:5000/products <br>
Body:
```json
{
    "name": "Plank",
    "description": "Birch wood",
    "price": 350
}
```
Output:
```json
{
    "message": "Added product."
}
```
Code: 200

Authorization: Administrator <br>
Typ: POST <br>
Link: http://localhost:5000/products <br>
Body:
```json
{
    "name": "Plank",
    "description": "Birch wood",
    "price": 350
}
```
Output:
```json
{
    "message": "Product already exists."
}
```
Code: 400

Authorization: Administrator <br>
Typ: POST <br>
Link: http://localhost:5000/products <br>
Body:
```json
{
    "name": "Door",
    "description": "Made from wood",
    "price": -2
}
```
Output:
```json
{
    "message": "Price must be positive."
}
```
Code: 400

Authorization: Administrator <br>
Typ: POST <br>
Link: http://localhost:5000/products <br>
Body:
```json
{
    "name": "Door",
    "description": "Made from wood",
    "price": 100000
}
```
Output:
```json
{
    "message": "Added product."
}
```
Code: 200

#### GET (z parametrami)

Authorization: Brak (nie ma znaczenia) <br>
Typ: GET <br>
Link: http://localhost:5000/products <br>
Body: brak
Output:
```json
{
    "products": [
        {
            "description": "A cheap Brick",
            "id": 1,
            "name": "Brick",
            "price": 7.0
        },
        {
            "description": "A cheap Brick too",
            "id": 3,
            "name": "Brick",
            "price": 7.0
        },
        {
            "description": "Perfect for bricks",
            "id": 8,
            "name": "Mortar",
            "price": 40.0
        },
        {
            "description": "Oak wood",
            "id": 9,
            "name": "Plank",
            "price": 3.5
        },
        {
            "description": "Birch wood",
            "id": 10,
            "name": "Plank",
            "price": 3.5
        },
        {
            "description": "Made from wood",
            "id": 11,
            "name": "Door",
            "price": 1000.0
        }
    ]
}
```
Code: 200

Authorization: Brak (nie ma znaczenia) <br>
Typ: GET <br>
Link: http://localhost:5000/products?page=1 <br>
Body: brak
Output:
```json
{
    "products": [
        {
            "description": "A cheap Brick",
            "id": 1,
            "name": "Brick",
            "price": 7.0
        },
        {
            "description": "A cheap Brick too",
            "id": 3,
            "name": "Brick",
            "price": 7.0
        },
        {
            "description": "Perfect for bricks",
            "id": 8,
            "name": "Mortar",
            "price": 40.0
        },
        {
            "description": "Oak wood",
            "id": 9,
            "name": "Plank",
            "price": 3.5
        },
        {
            "description": "Birch wood",
            "id": 10,
            "name": "Plank",
            "price": 3.5
        }
    ]
}
```
Code: 200

Authorization: Brak (nie ma znaczenia) <br>
Typ: GET <br>
Link: http://localhost:5000/products?page=2 <br>
Body: brak
Output:
```json
{
    "products": [
        {
            "description": "Made from wood",
            "id": 11,
            "name": "Door",
            "price": 1000.0
        }
    ]
}
```
Code: 200

Authorization: Brak (nie ma znaczenia) <br>
Typ: GET <br>
Link: http://localhost:5000/products?page=3 <br>
Body: brak
Output:
```json
{
    "message": "No such page."
}
```
Code: 400

Authorization: Brak (nie ma znaczenia) <br>
Typ: GET <br>
Link: http://localhost:5000/products?more=500 <br>
Body: brak
Output:
```json
{
    "products": [
        {
            "description": "A cheap Brick",
            "id": 1,
            "name": "Brick",
            "price": 7.0
        },
        {
            "description": "A cheap Brick too",
            "id": 3,
            "name": "Brick",
            "price": 7.0
        },
        {
            "description": "Perfect for bricks",
            "id": 8,
            "name": "Mortar",
            "price": 40.0
        },
        {
            "description": "Made from wood",
            "id": 11,
            "name": "Door",
            "price": 1000.0
        }
    ]
}
```
Code: 200

Authorization: Brak (nie ma znaczenia) <br>
Typ: GET <br>
Link: http://localhost:5000/products?less=500 <br>
Body: brak
Output:
```json
{
    "products": [
        {
            "description": "Oak wood",
            "id": 9,
            "name": "Plank",
            "price": 3.5
        },
        {
            "description": "Birch wood",
            "id": 10,
            "name": "Plank",
            "price": 3.5
        }
    ]
}
```
Code: 200

Authorization: Brak (nie ma znaczenia) <br>
Typ: GET <br>
Link: http://localhost:5000/products?more=500&less=1000 <br>
Body: brak
Output:
```json
{
    "products": [
        {
            "description": "A cheap Brick",
            "id": 1,
            "name": "Brick",
            "price": 7.0
        },
        {
            "description": "A cheap Brick too",
            "id": 3,
            "name": "Brick",
            "price": 7.0
        }
    ]
}
```
Code: 200

Authorization: Brak (nie ma znaczenia) <br>
Typ: GET <br>
Link: http://localhost:5000/products?more=500&sort=price <br>
Body: brak
Output:
```json
{
    "products": [
        {
            "description": "A cheap Brick",
            "id": 1,
            "name": "Brick",
            "price": 7.0
        },
        {
            "description": "A cheap Brick too",
            "id": 3,
            "name": "Brick",
            "price": 7.0
        },
        {
            "description": "Perfect for bricks",
            "id": 8,
            "name": "Mortar",
            "price": 40.0
        },
        {
            "description": "Made from wood",
            "id": 11,
            "name": "Door",
            "price": 1000.0
        }
    ]
}
```
Code: 200

Authorization: Brak (nie ma znaczenia) <br>
Typ: GET <br>
Link: http://localhost:5000/products?more=500&sort=description&desc=true <br>
Body: brak
Output:
```json
{
    "products": [
        {
            "description": "Perfect for bricks",
            "id": 8,
            "name": "Mortar",
            "price": 40.0
        },
        {
            "description": "Made from wood",
            "id": 11,
            "name": "Door",
            "price": 1000.0
        },
        {
            "description": "A cheap Brick too",
            "id": 3,
            "name": "Brick",
            "price": 7.0
        },
        {
            "description": "A cheap Brick",
            "id": 1,
            "name": "Brick",
            "price": 7.0
        }
    ]
}
```
Code: 200

Authorization: Brak (nie ma znaczenia) <br>
Typ: GET <br>
Link: http://localhost:5000/products?less=1000&sort=name&desc=true <br>
Body: brak
Output:
```json
{
    "products": [
        {
            "description": "Oak wood",
            "id": 9,
            "name": "Plank",
            "price": 3.5
        },
        {
            "description": "Birch wood",
            "id": 10,
            "name": "Plank",
            "price": 3.5
        },
        {
            "description": "A cheap Brick",
            "id": 1,
            "name": "Brick",
            "price": 7.0
        },
        {
            "description": "A cheap Brick too",
            "id": 3,
            "name": "Brick",
            "price": 7.0
        }
    ]
}
```
Code: 200

Authorization: Brak (nie ma znaczenia) <br>
Typ: GET <br>
Link: http://localhost:5000/products?less=1000&desc=true <br>
Body: brak
Output:
```json
{
    "message": "What do you wanna sort by?"
}
```
Code: 400

Authorization: Brak (nie ma znaczenia) <br>
Typ: GET <br>
Link: http://localhost:5000/products?less=100&more=200 <br>
Body: brak
Output:
```json
{
    "message": "More should be smaller than less."
}
```
Code: 400

Authorization: Brak (nie ma znaczenia) <br>
Typ: GET <br>
Link: http://localhost:5000/products?less=100&more=100e <br>
Body: brak
Output:
```json
{
    "message": "More should be smaller than less."
}
```
Code: 400

Authorization: Brak (nie ma znaczenia) <br>
Typ: GET <br>
Link: http://localhost:5000/products?less=0 <br>
Body: brak
Output:
```json
{
    "message": "Less has to be a positive number."
}
```
Code: 400

#### PUT (aktualizowanie produktu)

Przy braku autoryzacji i dla użytkownika tak samo jak przy POST.

Authorization: Administrator <br>
Typ: POST <br>
Link: http://localhost:5000/products/10 <br>
Body:
```json
{
    "name": "Plank",
    "description": "Spruce wood",
    "price": 350
}
```
Output:
```json
{
    "message": "Product updated successfully"
}
```
Code: 200

Authorization: Administrator <br>
Typ: POST <br>
Link: http://localhost:5000/products/10 <br>
Body:
```json
{
    "name": "Plank",
    "description": "Spruce wood",
    "price": 0
}
```
Output:
```json
{
    "message": "Price must be positive."
}
```
Code: 400

#### DELETE (usuwanie produktu)

Przy braku autoryzacji i dla użytkownika tak samo jak przy POST.

Authorization: Administrator <br>
Typ: DELETE <br>
Link: http://localhost:5000/products/10 <br>
Body: brak
Output:
```json
{
    "message": "Product deleted successfully"
}
```
Code: 200

Authorization: Administrator <br>
Typ: DELETE <br>
Link: http://localhost:5000/products/10 <br>
Body: brak
Output:
```json
{
    "message": "Product not found"
}
```
Code: 404

### Opinie

#### GET

Authorization: Brak (bez znaczenia) <br>
Typ: GET <br>
Link: http://localhost:5000/products/1/reviews <br>
Body: brak
Output:
```json
{
    "reviews": []
}
```
Code: 200

#### POST

Authorization: Brak <br>
Typ: POST <br>
Link: http://localhost:5000/products/1/reviews <br>
Body:
```json
{
    "rating": 8
}
```
Output:
```json
{
    "message": "No authentication token present"
}
```
Code: 401

Authorization: Użytkownik/Administrator <br>
Typ: POST <br>
Link: http://localhost:5000/products/1/reviews <br>
Body:
```json
{
    "rating": 8
}
```
Output:
```json
{
    "message": "Review added successfully"
}
```
Code: 200

Authorization: Użytkownik/Administrator <br>
Typ: POST <br>
Link: http://localhost:5000/products/1/reviews <br>
Body:
```json
{
    "rating": 8
}
```
Output:
```json
{
    "message": "Review already exists for this product"
}
```
Code: 400

#### PUT

Authorization: Użytkownik/Administrator <br>
Typ: PUT <br>
Link: http://localhost:5000/products/1/reviews <br>
Body:
```json
{
    "rating": 9
}
```
Output:
```json
{
    "message": "Review updated successfully"
}
```
Code: 200

Authorization: Użytkownik/Administrator <br>
Typ: PUT <br>
Link: http://localhost:5000/products/1/reviews <br>
Body:
```json
{
    "rating": 0
}
```
Output:
```json
{
    "message": "Rating is required"
}
```
Code: 400

Authorization: Użytkownik/Administrator <br>
Typ: PUT <br>
Link: http://localhost:5000/products/3/reviews <br>
Body:
```json
{
    "rating": 2
}
```
Output:
```json
{
    "message": "Review does not exist"
}
```
Code: 400

#### GET (ponownie)

Authorization: Brak (bez znaczenia) <br>
Typ: GET <br>
Link: http://localhost:5000/products/1/reviews <br>
Body: brak
Output:
```json
{
    "reviews": [
        {
            "rating": 9,
            "username": "test"
        }
    ]
}
```
Code: 200

#### DELETE

Authorization: Użytkownik/Administrator <br>
Typ: DELETE <br>
Link: http://localhost:5000/products/3/reviews <br>
Body: brak
Output:
```json
{
    "message": "Review does not exist"
}
```
Code: 404

Authorization: Użytkownik/Administrator <br>
Typ: DELETE <br>
Link: http://localhost:5000/products/1/reviews <br>
Body: brak
Output:
```json
{
    "message": "Review deleted successfully"
}
```
Code: 200