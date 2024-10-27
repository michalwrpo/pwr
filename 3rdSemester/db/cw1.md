# Lista 1

1. SELECT DISTINCT Nazwisko_prezesa
   FROM Firma;

2. SELECT Nazwa 
FROM Firma 
WHERE Data_założenia < '2000-01-01';

3. SELECT Nazwa_firmy
FROM Zatrudnienie
GROUP BY Nazwa_firmy
WHERE Count(id_pracownika) >= 10;

4. SELECT Firma.Nazwisko_prezesa
FROM Firma 
JOIN Pracownicy ON Firma.Pesel_prezesa = Pracownicy.Pesel
WHERE Data_zwolnienia IS NULL;

5. SELECT Firma.Nazwa, Firma.Imię_prezea, Firma.Nazwisko_prezesa, Obroty.Rok, Obroty.Miesiąc
FROM Firma
JOIN Obroty
ON Firma.Nazwa = Obroty.Nazwa_firmy
WHERE Obroty.Przychód < Obroty.Wydatki;

6. SELECT Firma.Nazwa, Obroty.Rok, (SUM(Obroty.Przychód) - SUM(Obroty.Wydatki)) AS Obroty
FROM Firma
JOIN Obroty
ON Firma.Nazwa = Obroty.Nazwa_firmy
WHERE Firma.Nazwisko_prezesa = "Kowalski"
GROUP BY Firma.Nazwa, Obroty.Rok;

7. SELECT Nazwa, Imię_prezesa, Nazwisko_prezesa
FROM Firma
WHERE Nazwa_firmy NOT IT
    (SELECT Zatrudnienie.Nazwa_firmy
    FROM Pracownicy
    JOIN Zatrudnienie
    ON Pracownicy.Id = Zatrudnienie.Id_pracownika 
    WHERE Pracownicy.Nazwisko = "Fikcyjny" OR Zatrudnienie.Data_zwolnienia IS NULL
);

8. SELECT *
FROM Firma
WHERE Nazwa LIKE "%sp. z.o.o.%";

9. SELECT Firma.Nazwa, Firma.Data_założenia 
FROM Firma
JOIN 
    (SELECT MIN(Data_założenia) AS Data_założenia
    FROM Firma) AS Stare
ON Firma.Data_założenia = Stare.Data_założenia;

Lub

SELECT Nazwa, Data_założenia
FROM Firma
WHERE Data_założenia = 
    (SELECT MIN(Data_założenia) FROM Firma);

10. SELECT Nazwa
FROM Firma
WHERE Nazwa NOT IN (
    SELECT Nazwa_firmy 
    FROM Zatrudnienie 
    WHERE Data_zwolnienia IS NULL
);

11. SELECT *
FROM Firma
WHERE Data_założenia < (
    SELECT Data_założenia 
    FROM Firma
    WHERE Nazwa="Korepetycje sp. z.o.o." 
);

12. SELECT DISTINCT Imię
FROM Pracownicy
WHERE Nazwisko IN ("Kowalski", "Nowak");

13. SELECT Firma.*, SUM(Obroty.Przychód - Obroty.Wydatki) AS Zysk
FROM Firma
JOIN Obroty
ON Firma.Nazwa = Obroty.Nazwa_firmy
WHERE Obroty.Rok = YEAR(Firma.Data_założenia)
GROUP BY Firma.Nazwa
HAVING Zarobek = (
    
)

14.
```sql 
SELECT Nazwa_firmy 
FROM Obroty
WHERE Rok = YEAR(CURDATE()) - 1
GROUP BY Nazwa_firmy
HAVING SUM(Przychod) < SUM(Wydatki);
```

15. 
```sql
SELECT F1.Nazwa, F2.Nazwa 
FROM Firma AS F1
JOIN Firma AS F2 ON F1.Adres = F2.Adres 
WHERE F1.Nazwa < F2.Nazwa;
```

16. 
```sql
SELECT Nazwa_firmy, Rok, SUM(Wydatki)
FROM Obroty
WHERE Miesiac < 7
GROUP BY Nazwa_firmy, Rok; 
```

17.
```sql
SELECT Nazwa, YEAR(Data_zalozenia)
FROM Firma
ORDER BY Data_zalozenia ASC;
```