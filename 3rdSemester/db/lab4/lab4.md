# Bazy Danych - Laboratorium 4
## Michał Waluś


### Zad.2
Tworzenie bazy danych
```
use library
```
Tworzenie kolekcji
```bash
db.createColleciton("authors")
db.createCollection("books")
```
Dodanie autorów
```json
db.authors.insertMany([
    {
        "_id": ObjectId("65711ccdcb2d05e2c973fe85"),
        "name": { "first": "J.R.R", "last": "Tolkien" },
        "country": "UK",
        "birth": new Date("1892-01-03"),
        "death": new Date("1973-09-02")
    },
    {
        "_id": ObjectId("65711ccdcb2d05e2c973fe86"),
        "name": { "first": "Andrzej", "last": "Sapkowski" },
        "country": "Poland",
        "birth": new Date("1948-06-21"),
        "death": null
    },
    {
        "_id": ObjectId("65711ccdcb2d05e2c973fe87"),
        "name": { "first": "Henryk", "last": "Sienkiewicz" },
        "country": "Poland",
        "birth": new Date("1798-12-24"),
        "death": new Date("1855-1-26")
    },
    {
        "_id": ObjectId("65711ccdcb2d05e2c973fe88"),
        "name": { "first": "William", "last": "Shakespear" },
        "country": "UK",
        "birth": new Date("1564-04-26"),
        "death": new Date("1616-04-24")
    }
])
```
Dodanie książek
```json
db.books.insertMany([
    {
        "_id": ObjectId("65712008cb2d05e2c973fe86"),
        "title": "The Hobbit",
        "isbn": "978-0-261-10295-6",
        "publication_year": 1937,
        "language": "English",
        "author": ObjectId("65711ccdcb2d05e2c973fe85"),
        "publisher": 
            {
                "name": "George Allen & Unwin",
                "country": "UK"
            }
    },
    {
        "_id": ObjectId("65712008cb2d05e2c973fe87"),
        "title": "The Fellowship of the Ring",
        "isbn": "978-0-345-33970-6",
        "publication_year": 1954,
        "language": "English",
        "author": ObjectId("65711ccdcb2d05e2c973fe85"),
        "publisher": 
            {
                "name": "George Allen & Unwin",
                "country": "UK"
            }
    },
    {
        "_id": ObjectId("65712008cb2d05e2c973fe88"),
        "title": "Quo Vadis",
        "isbn": "978-0-261-10295-6",
        "publication_year": 1896,
        "language": "Polish",
        "author": ObjectId("65711ccdcb2d05e2c973fe87"),
        "publisher": 
            {
                "name": "Zakład Narodowy im. Ossolińskich",
                "country": "Poland"
            }
    },
    {
        "_id": ObjectId("65712008cb2d05e2c973fe89"),
        "title": "Krzyżacy",
        "isbn": "978-0-261-10295-6",
        "publication_year": 1900,
        "language": "Polish",
        "author": ObjectId("65711ccdcb2d05e2c973fe87"),
        "publisher": 
            {
                "name": "Zakład Narodowy im. Ossolińskich",
                "country": "Poland"
            }
    },
    {
        "_id": ObjectId("65712008cb2d05e2c973fe90"),
        "title": "Potop",
        "isbn": "978-0-261-10295-6",
        "publication_year": 1886,
        "language": "Polish",
        "author": ObjectId("65711ccdcb2d05e2c973fe87"),
        "publisher": 
            {
                "name": "Zakład Narodowy im. Ossolińskich",
                "country": "Poland"
            }
    },
    {
        "_id": ObjectId("65712008cb2d05e2c973fe91"),
        "title": "Ostatnie Życzenie",
        "isbn": "978-0-575-08244-1",
        "publication_year": 1993,
        "language": "Polish",
        "author": ObjectId("65711ccdcb2d05e2c973fe86"),
        "publisher": 
            {
                "name": "superNOWA",
                "country": "Poland"
            }
    },
    {
        "_id": ObjectId("65712008cb2d05e2c973fe92"),
        "title": "Miecz Przeznaczenia",
        "isbn": "978-1-4732-1153-7",
        "publication_year": 1993,
        "language": "Polish",
        "author": ObjectId("65711ccdcb2d05e2c973fe86"),
        "publisher": 
            {
                "name": "superNOWA",
                "country": "Poland"
            }
    },
    {
        "_id": ObjectId("65712008cb2d05e2c973fe93"),
        "title": "Romeo and Juliet",
        "isbn": "978-0-743-47711-6",
        "publication_year": 1597,
        "language": "English",
        "author": ObjectId("65711ccdcb2d05e2c973fe88"),
        "publisher": 
            {
                "name": "Simon & Schuster",
                "country": "UK"
            }
    }
])
```
Jak widać na przykładzie wyżej data śmierci może być nullem (Andrzej Sapkowski), poniżej dane z pomyloną nazwą pola i typem oraz pominiętym polem i dodanym nowym.
```json
db.authors.insertOne({
    "_id": ObjectId("65711ccdcb2d05e2c973fe92"),
    "name": { "first": "William", "last": "Shakespear" },
    "country": 1,
    "death": new Date("1616-04-24"),
    "british": "true"
})
```
Mongo pozwala nam dodać taki dokument do bazy. <br>
Żeby wymusić poprawność danych możemy użyć JSON schema validation.
```json
# usunięcie kolekcji
db.authors.drop()

db.createCollection('authors', {
    validator: {
        $jsonSchema: {
            bsonType: "object",
            required: [ "name", "country", "birth", "death" ],
            properties: {
                name: {
                    bsonType: "object",
                    required: [ "first", "last" ],
                    properties: {
                        first: {
                            bsonType: "string",
                            description: "Must be a string - Required"
                        },
                        last: {
                            bsonType: "string",
                            description: "Must be a string - Required"
                        }
                    }
                },
                country: {
                    bsonType: "string",
                    description: "Must be a string - Required"
                },
                birth: {
                    bsonType: "date",
                    description: "Must be a date - Required"
                },
                death: {
                    bsonType: ["null", "date"],
                    description: "Must be a date or null - Required"
                }
            }
        }
    }
})
```
Stworzenie kolekcji `reviews`
```json
db.createCollection('reviews', {
    validator: {
        $jsonSchema: {
            bsonType: "object",
            required: [ "book", "reviewer", "rating", "text" ],
            properties: {
                book: {
                    bsonType: "objectId",
                    description: "Must be an id - Required"
                },
                reviewer: {
                    bsonType: "string",
                    description: "Must be a string - Required"
                },
                rating: {
                    bsonType: "int",
                    minimum: 1,
                    maximum: 5,
                    description: "Must be an integer in range 1-5 - Required"
                },
                text: {
                    bsonType: "string",
                    description: "Must be a string - Required"
                }
            }
        }
    }
})
```
Dodanie recenzji
```json
db.reviews.insertMany([
    {
        "book": ObjectId("65712008cb2d05e2c973fe91"),
        "reviewer": "Jan Kowalski",
        "rating": 5,
        "text": "Great book!"
    },
    {
        "book": ObjectId("65712008cb2d05e2c973fe91"),
        "reviewer": "Anna Kowalska",
        "rating": 3,
        "text": "Good book."
    },
    {
        "book": ObjectId("65712008cb2d05e2c973fe91"),
        "reviewer": "Adam Nowak",
        "rating": 1,
        "text": "I can't read"
    },
    {
        "book": ObjectId("65712008cb2d05e2c973fe92"),
        "reviewer": "Jan Kowalski",
        "rating": 5,
        "text": "Another great book!"
    },
    {
        "book": ObjectId("65712008cb2d05e2c973fe90"),
        "reviewer": "Jan Kowalski",
        "rating": 2,
        "text": "Not my cup of tea"
    },
])
```
Wybrana przeze mnie metoda pozwala prosto wstawiać i wyszukiwać dane, ale uniemożliwia rozróżnienie recenzentów o tym samym imieniu i nazwisku. <br>
Doddanie tablicy nagród
```json
db.authors.updateMany({}, { $set: { awards: [] } })
```
Dodanie tablice gatunków literackich
```json
db.books.updateMany({}, { $set: { genres: [] } })
// Sapkowski
db.books.updateMany(
    { "author": ObjectId("65711ccdcb2d05e2c973fe86") },
    { $addToSet: { genres: "Fantasy" } }
)
db.books.updateOne(
    { "_id": ObjectId("65712008cb2d05e2c973fe92") },
    { $addToSet: { genres: "Folklore" } }
)
// Tolkien
db.books.updateMany(
    { "author": ObjectId("65711ccdcb2d05e2c973fe85") },
    { $addToSet: { genres: "Fantasy" } }
)

```

### Zad.3

Książki napisane przez Andrzeja Sapkowskiego
```json
db.books.find({ "author": db.authors.findOne({ "name.first": "Andrzej", "name.last": "Sapkowski" })._id })
```

Polskie książki fantasy
```json
db.books.find({ "language": "Polish", "genres": "Fantasy" })
```

Wszystkie książki ze średnią ocen co najmniej 4
```json
db.reviews.aggregate([
    {
        $group: {
            _id: "$book",
            avgRating: { $avg: "$rating" }
        }
    },
    {
        $match: {
            avgRating: { $gte: 4 }
        }
    },
    {
        $project: {
            _id: 1
        }
    }
])
```

Książki napisane przez polskich autorów
```json
db.books.aggregate([
    {
        $lookup: {
            from: "authors",
            localField: "author",
            foreignField: "_id",
            as: "author"
        }
    },
    {
        $unwind: "$author"
    },
    {
        $match: {
            "author.country": "Poland"
        }
    },
    {
        $lookup: {
            from: "reviews",
            localField: "_id",
            foreignField: "book",
            as: "reviews"
        }
    },
    {
        $unwind: "$reviews"
    },
    {
        $group: {
            _id: "$_id",
            title: { $first: "$title" },
            author: { $first: "$author.name" },
            language: { $first: "$language" },
            avgRating: { $avg: "$reviews.rating"  },
            publication_year: { $first: "$publication_year" },
            isbn: { $first: "$isbn" },
            publisher: { $first: "$publisher" }
        }
    }
])
```