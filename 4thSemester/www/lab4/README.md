random POST request
json
```sh
curl -X POST http://localhost:5000/login -d '{"username":"test","password":"test"}' -H 'Content-Type: application/json'
```
x-www-form-urlencoded
```sh
curl -X POST http://localhost:5000/login -d 'username=test&password=test' -H 'Content-Type: application/x-www-form-urlencoded'
```

register user
```sh
curl -X POST http://localhost:5000/register -d '{"username":"test","password":"test"}' -H 'Content-Type: application/json'
```
