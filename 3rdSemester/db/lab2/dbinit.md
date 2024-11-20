```sh
## Up DB
docker compose up -d
## Down DB
docker compose down && docker volume rm lista2_db_data

# Execution

## Root user
docker exec -it mariadb-container mariadb -D aparaty -u root -prootpassword
## Normal user
docker exec -it mariadb-container mariadb -D aparaty -u 123456 -pkowalski56 
```