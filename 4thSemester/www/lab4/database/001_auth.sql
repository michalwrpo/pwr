CREATE TYPE USERTYPE AS ENUM('user', 'admin');

CREATE TABLE Users(
    id SERIAL PRIMARY KEY,
    type USERTYPE NOT NULL,
    username VARCHAR(64) NOT NULL UNIQUE CHECK (char_length(username) > 3),
    password CHAR(64) NOT NULL -- SHA256
);

INSERT INTO Users (type, username, password) VALUES ('admin', 'Admin', 'd82494f05d6917ba02f7aaa29689ccb444bb73f20380876cb05d1f37537b7892');
