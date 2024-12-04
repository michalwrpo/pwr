# Bazy Danych - Laboratorium 3
## Michał Waluś

Baza danych używając docker'a i
```yaml
services:
  mariadb:
    image: mariadb:latest
    container_name: mariadb-lab3
    environment:
      MYSQL_ROOT_PASSWORD: rootpassword
      MYSQL_DATABASE: people
      MYSQL_USER: user
      MYSQL_PASSWORD: password
    volumes:
      - db_data:/var/lib/mysql
      - ./init.sql:/docker-entrypoint-initdb.d/init.sql
    ports:
      - "3306:3306"
    networks:
      - mariadb-network

volumes:
  db_data:

networks:
  mariadb-network:
    driver: bridge
```

Startujemy bazę danych za pomocą:
```sh
docker compose up -d

docker exec -it mariadb-lab3 mariadb -D people -u root -prootpassword
```

### Zad.1

Tworzenie tabeli `Ludzie`
```sql
CREATE TABLE Ludzie (
    PESEL CHAR(11) PRIMARY KEY CHECK (NOT PESEL LIKE '%[^0-9]%'),
    imie VARCHAR(30),
    nazwisko VARCHAR(30),
    data_urodzenia DATE,
    plec ENUM('K', 'M'),
    CONSTRAINT peselDay CHECK (SUBSTRING(PESEL, 5, 2) < 32),
    CONSTRAINT peselGender CHECK ((SUBSTRING(PESEL, 10, 1) % 2 = 0 AND plec = 'K') OR (SUBSTRING(PESEL, 10, 1) % 2 = 1 AND plec = 'M')),
    CONSTRAINT peselLastDigit CHECK (((SUBSTRING(pesel, 1, 1) + 3*SUBSTRING(pesel, 2, 1) + 7*SUBSTRING(pesel, 3, 1) + 9*SUBSTRING(pesel, 4, 1) + SUBSTRING(pesel, 5, 1) + 3*SUBSTRING(pesel, 6, 1) + 7*SUBSTRING(pesel, 7, 1) + 9*SUBSTRING(pesel, 8, 1) + SUBSTRING(pesel, 9, 1) + 3*SUBSTRING(pesel, 10, 1) + SUBSTRING(pesel, 11, 1)) % 10) = 0)
);
```
Tworzenie tabeli `Zawody`
```sql
CREATE TABLE Zawody (
    zawod_id INT PRIMARY KEY AUTO_INCREMENT,
    nazwa VARCHAR(50),
    pensja_min FLOAT CHECK (pensja_min >= 0),
    pensja_max FLOAT CHECK (pensja_max >= 0),
    CONSTRAINT pensja_min_man CHECK (pensja_min < pensja_max)
) AUTO_INCREMENT = 1;
```
Tworzenie tabeli `Pracownicy`
```sql
CREATE TABLE Pracownicy (
    pracownik_id INT PRIMARY KEY AUTO_INCREMENT,
    PESEL CHAR(11),
    zawod_id INT,
    pensja FLOAT CHECK (pensja >= 0),
    FOREIGN KEY (PESEL) REFERENCES Ludzie(PESEL),
    FOREIGN KEY (zawod_id) REFERENCES Zawody(zawod_id)
);
```

W tabeli `Ludzie` PESEL jest unikalny, więc może być kluczem głównym, ale jedna osoba może być zatrudniona w kilku miejscach, więc w tabeli `Pracownicy` PESEL może się powtórzyć.

Dodanie danych do tabeli `Ludzie`
```sql
INSERT INTO Ludzie(PESEL, imie, nazwisko, data_urodzenia, plec) VALUES
('10251212350', 'Mateusz', 'Nowak', '2010-05-12', 'M'),
('08271802143', 'Anna', 'Kowalska', '2008-07-18', 'K'),
('12231013571', 'Jakub', 'Wiśniewski', '2012-03-10', 'M'),
('09312209844', 'Julia', 'Wójcik', '2009-11-22', 'K'),
('11263016530', 'Filip', 'Zieliński', '2011-06-30', 'M'),
('81020312335', 'Krzysztof', 'Kowalski', '1981-02-03', 'M'),
('90041509848', 'Anna', 'Nowak', '1990-04-15', 'K'),
('84122311596', 'Piotr', 'Wiśniewski', '1984-12-23', 'M'),
('92071202380', 'Maria', 'Wójcik', '1992-07-12', 'K'),
('89080713534', 'Michał', 'Zieliński', '1989-08-07', 'M'),
('85061009827', 'Ewa', 'Kamińska', '1985-06-10', 'K'),
('79090314775', 'Tomasz', 'Krawczyk', '1979-09-03', 'M'),
('94010203649', 'Agnieszka', 'Mazur', '1994-01-02', 'K'),
('88021515934', 'Paweł', 'Dąbrowski', '1988-02-15', 'M'),
('91031307367', 'Joanna', 'Lewandowska', '1991-03-13', 'K'),
('82071918235', 'Andrzej', 'Baran', '1982-07-19', 'M'),
('95062109242', 'Katarzyna', 'Szymańska', '1995-06-21', 'K'),
('87041712190', 'Adam', 'Czarnecki', '1987-04-17', 'M'),
('89090207425', 'Monika', 'Piotrowska', '1989-09-02', 'K'),
('93050113659', 'Kamil', 'Kubiak', '1993-05-01', 'M'),
('85080518322', 'Barbara', 'Jankowska', '1985-08-05', 'K'),
('89030405179', 'Grzegorz', 'Michalski', '1989-03-04', 'M'),
('81092203461', 'Magdalena', 'Szulc', '1981-09-22', 'K'),
('94021315771', 'Łukasz', 'Kozłowski', '1994-02-13', 'M'),
('88082917847', 'Ewelina', 'Pawlak', '1988-08-29', 'K'),
('86071514378', 'Karol', 'Sobczak', '1986-07-15', 'M'),
('92010110327', 'Patrycja', 'Adamska', '1992-01-01', 'K'),
('89031516599', 'Sebastian', 'Witkowski', '1989-03-15', 'M'),
('83052408583', 'Natalia', 'Walczak', '1983-05-24', 'K'),
('95071011235', 'Artur', 'Chmielewski', '1995-07-10', 'M'),
('88010605921', 'Alicja', 'Rutkowska', '1988-01-06', 'K'),
('84091912631', 'Mateusz', 'Malinowski', '1984-09-19', 'M'),
('91031204183', 'Sylwia', 'Wiśniewska', '1991-03-12', 'K'),
('87062413955', 'Marcin', 'Górski', '1987-06-24', 'M'),
('85090519843', 'Aleksandra', 'Sikorska', '1985-09-05', 'K'),
('82081707139', 'Rafał', 'Lis', '1982-08-17', 'M'),
('93030312988', 'Martyna', 'Król', '1993-03-03', 'K'),
('88041214835', 'Dominik', 'Wieczorek', '1988-04-12', 'M'),
('91091109347', 'Renata', 'Zając', '1991-09-11', 'K'),
('86051408714', 'Janusz', 'Majewski', '1986-05-14', 'M'),
('95080815640', 'Weronika', 'Stępień', '1995-08-08', 'K'),
('84073010571', 'Jacek', 'Czajka', '1984-07-30', 'M'),
('87092709242', 'Justyna', 'Sadowska', '1987-09-27', 'K'),
('85061813578', 'Przemysław', 'Gajda', '1985-06-18', 'M'),
('93070619829', 'Karolina', 'Ostrowska', '1993-07-06', 'K'),
('89012315393', 'Wojciech', 'Marciniak', '1989-01-23', 'M'),
('91021811245', 'Zuzanna', 'Krysiak', '1991-02-18', 'K'),
('86091518374', 'Kacper', 'Brzeziński', '1986-09-15', 'M'),
('88070517963', 'Gabriela', 'Wolska', '1988-07-05', 'K'),
('72060615652', 'Adam', 'Sikorski', '1972-06-06', 'M'),
('50010112336', 'Jan', 'Kowalski', '1950-01-01', 'M'),
('44021509849', 'Maria', 'Nowak', '1944-02-15', 'K'),
('57030511594', 'Tadeusz', 'Wiśniewski', '1957-03-05', 'M'),
('48071202387', 'Krystyna', 'Wójcik', '1948-07-12', 'K'),
('60080913537', 'Zbigniew', 'Zieliński', '1960-08-09', 'M');
```

Dodanie danych do tabeli `Zawody`
```sql
INSERT INTO Zawody(nazwa, pensja_min, pensja_max) VALUES
('Polityk', 4000, 100000),
('Nauczyciel', 3500, 7000),
('Lekarz', 8000, 25000),
('Informatyk', 5000, 25000);
```

Przypisujemy zawody przy użyciu kursora
```sql
-- TODO
```