Przypadek 1: Dodaj książkę
Aktorzy: Bibliotekarz
Cel: Dodanie nowej książki do systemu
Warunki wstępne: Bibliotekarz jest zalogowany do systemu
Przepływ główny: Dodanie książki:
1. Bibliotekarz wybiera opcję „Dodaj książkę” w systemie.
2. System prosi o podanie autora książki.
3. Bibliotekarz wprowadza autora książki.
4. System prosi o podanie tytułu książki.
5. Bibliotekarz wprowadza tytuł książki.
6. System dodaje nową książkę do listy książek i wyświetla komunikat o pomyślnym dodaniu książki.
Warunki końcowe: Książka została dodana do systemu.

Przypadek 2: Dodaj kopię książki
Aktorzy: Bibliotekarz
Cel: Dodanie nowej kopii do systemu
Warunki wstępne: Bibliotekarz jest zalogowany do systemu
Przepływ główny: Dodanie kopii:
1. Bibliotekarz wybiera opcję „Dodaj kopię” w systemie.
2. System prosi o podanie ID książki.
3. Bibliotekarz wprowadza ID książki.
4. System dodaje nową kopię do listy kopii danej książki i wyświetla komunikat o pomyślnym dodaniu kopii.
Warunki końcowe: Kopia książki została dodana do systemu.

Przypadek 3: Dodaj klienta
Aktorzy: Bibliotekarz
Cel: Dodanie nowego klienta do systemu
Warunki wstępne: Bibliotekarz jest zalogowany do systemu
Przepływ główny: Dodanie klienta:
1. Bibliotekarz wybiera opcję „Dodaj klienta” w systemie.
2. System prosi o podanie imienia klienta.
3. Bibliotekarz wprowadza imię klienta.
4. System prosi o podanie nazwiska klienta.
5. Bibliotekarz wprowadza nazwisko klienta.
6. System dodaje nowego klienta do listy klientów i wyświetla komunikat o pomyślnym dodaniu klienta.
Warunki końcowe: Klient został dodany do systemu.

Przypadek 4: Wyświetlenie informacji o książce
Aktorzy: Bibliotekarz
Cel: Wyświetlenie informacji o książce
Warunki wstępne: Bibliotekarz jest zalogowany do systemu
Przepływ główny: Wyświetlenie informacji o książce:
1. Bibliotekarz wybiera opcję "Wyświetl informacje o książce" w systemie.
2. System prosi o podanie ID książki.
3. Bibliotekarz wprowadza ID ksiązki.
4. System sprawdza czy książka istnieje:
    - Jeżeli istnieje wyświetla autora i tytuł książki.
    - Jeżeli nie istnieje zwraca błąd.
Warunki końcowe: Informacje o książce zostają wyświetlone.

Przypadek 5: Wyświetlenie informacji o kliencie
Aktorzy: Bibliotekarz
Cel: Wyświetlenie informacji o kliencie
Warunki wstępne: Bibliotekarz jest zalogowany do systemu
Przepływ główny: Wyświetlenie informacji o kliencie:
1. Bibliotekarz wybiera opcję "Wyświetl informacje o kliencie" w systemie.
2. System prosi o podanie ID klienta.
3. Bibliotekarz wprowadza ID klienta.
4. System sprawdza czy klient istnieje:
    - Jeżeli istnieje wyświetla imię i nazwisko kilenta.
    - Jeżeli nie istnieje zwraca błąd.
Warunki końcowe: Informacje o kliencie zostają wyświetlone.

Przypadek 6: Wypożyczenie książki
Aktorzy: Bibliotekarz
Cel: Wypożyczenie kopii książki klientowi
Warunki wstępne: Bibliotekarz jest zalogowany do systemu
Przepływ główny: Wypożyczenie książki:
1. Bibliotekarz wybiera opcję "Wypożycz książkę" w systemie.
2. System prosi o podanie ID książki.
3. Bibliotekarz wprowadza ID ksiązki.
4. System prosi o podanie ID kopii.
5. Bibliotekarz wprowadza ID kopii.
6. System prosi o podanie ID klienta.
7. Bibliotekarz wprowadza ID klienta.
8. System sprawdza czy kopia jest dostępna:
    - Jeżeli jest, książka zostaje wypożyczona.
    - Jeżeli nie jest, system zwraca błąd.
Warunki końcowe: Książka zostaje wypożyczona klientowi.
Wyjątki: Książka, kopia lub klient nie istnieją w systemie.

Przypadek 7: Zwrot książki
Aktorzy: Bibliotekarz
Cel: Zwrot kopii książki przez klienta
Warunki wstępne: Bibliotekarz jest zalogowany do systemu
Przepływ główny: Zwrot książki:
1. Bibliotekarz wybiera opcję "Zwróć książkę" w systemie.
2. System prosi o podanie ID książki.
3. Bibliotekarz wprowadza ID ksiązki.
4. System prosi o podanie ID kopii.
5. Bibliotekarz wprowadza ID kopii.
6. System prosi o podanie ID klienta.
7. Bibliotekarz wprowadza ID klienta.
8. System sprawdza czy kopia jest wypożyczona przez tego klienta:
    - Jeżeli jest, książka zostaje zwrócona pomyślnie.
    - Jeżeli nie jest, system zwraca błąd.
Warunki końcowe: Książka zostaje zwrócona.
Wyjątki: Książka, kopia lub klient nie istnieją w systemie.