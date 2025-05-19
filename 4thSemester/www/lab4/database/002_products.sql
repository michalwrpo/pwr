CREATE TABLE Products(
    id SERIAL PRIMARY KEY,
    name VARCHAR(255) NOT NULL,
    description TEXT UNIQUE NOT NULL,
    price BIGINT NOT NULL CHECK (price > 0)
);

CREATE TABLE Reviews(
    id SERIAL PRIMARY KEY,
    user_id SERIAL REFERENCES Users(id),
    product_id SERIAL REFERENCES Products(id),
    rating INT NOT NULL CHECK (rating > 0 AND rating < 11)
);

ALTER TABLE Reviews ADD CONSTRAINT unique_user_product_review UNIQUE(user_id, product_id);