<!-- - zapisać w tabeli wyniki
- pisać po polsku
- zapoznać się ze scapy python 
- wireshark przechwycić komunikat
- Przeanalizuj rezultaty uzyskane w programie wireshark nasluchującego program ping? Czy widać anomalie/zagrozenia?
- Wyciagnij dalekoidące wnioski i spostrzezenia -->

# Technologie sieciowe, Lista 1 - Michał Waluś 279695

## 1. Wprowadzenie  
Celem ćwiczenia było przetestowanie działania programów sieciowych `ping` i `traceroute` oraz przeanalizowanie ich przydatności w diagnostyce sieci. Badania przeprowadzono dla serwerów zlokalizowanych w różnych miejscach na świecie, z uwzględnieniem wpływu rozmiaru pakietów, fragmentacji oraz analizy ścieżek przez sieci wirtualne i chmurowe.  

## 2. Opis programów  

**Ping** – narzędzie sieciowe używane do testowania osiągalności hosta w sieci IP oraz pomiaru czasu odpowiedzi. Polega na wysyłaniu pakietów ICMP Echo Request i oczekiwaniu na Echo Reply. Dodatkowo pozwala określić rozmiar pakietu, liczbę prób oraz TTL (Time To Live).  

**Traceroute** – służy do wyznaczania trasy, jaką pakiety pokonują od komputera użytkownika do serwera docelowego. Wyświetla adresy IP i czas odpowiedzi poszczególnych węzłów (routerów) pośredniczących.  

**Wireshark** - narzędzie służące do analizy ruchu sieciowego. Umożliwia przechwytywania i szczegółową analizę pakietów przesyłanych przez interfejsy sieciowe.

## 3. Wyniki i analiza  

### 3.1. Ping  

Wywołanie: `ping -c [liczba prób] -t [TTL] -s [rozmiar] [adres]`.

Czas w ms (t) oraz liczba węzłów (n) (do/od) w zależności od wielkości pakietu. Czas mierzony jako średnia z 10 prób.
| Adres          | 84 B (t) | 228 B (t) | 1024 B (t) | 84 B (n) | 228 B (n) | 1024 B (n) | MTU | Lokalizacja serwera |
| :----          | :--: | :--: | :--: | :---: | :---: | :---: | :---: | :------------: |
| cs.pwr.edu.pl  | 6.03 | 6.67 | 6.16 | 4/3   | 4/3   | 4/3   | 1500  | Wrocław        |
| pwr.edu.pl     | 5.47 | 6.07 | 6.32 | 5/5   | 5/5   | 5/5   | 1500  | Wrocław        |
| olx.pl         | 13.0 | 12.1 | 12.0 | 17/11 | 17/11 | 17/11 | 1500  | Warszawa       |
| rust-lang.org  | 13.3 | 13.0 | 13.7 | 18/11 | 18/11 | 18/11 | 1500  | Francja        |
| whitehouse.gov | 25.1 | 29.9 | 25.9 | 14/13 | 14/13 | 14/13 | 65535 | USA            |
| spbti.ru       | 63.7 | 63.4 | 89.7 | 16/15 | 16/15 | 16/15 | 1500  | Rosja          |
| uom.lk         | 258  | 259  | 272  | 24/23 | 24/23 | 24/23 | 1024  | Indie          |
| lands.gov.sb   | 457  | 461  | 461  | 33/18 | 33/18 | 33/18 | 65535 | Wyspy Solomona |

Na podstawie przeprowadzonych testów zaobserwowano następujące zależności:  

- **Liczba węzłów i trasy powrotne**  
Trasy tam i z powrotem często różnią się liczbą węzłów (np. cs.pwr.edu.pl – 4 skoki do serwera, ale tylko 3 skoki z powrotem). Jest to efekt asymetrycznych tras w sieci IP. Wielkość pakietów, które możemy przesłać bez fragmentacji nie wpływa na długość trasy.

- **Wpływ wielkości pakietu**  
Dla adresów takich jak pwr.edu.pl czy uom.lk zauważono, że większe pakiety istotnie wpływają na wzrost czasu odpowiedzi. W przypadku bliskich serwerów wzrost był niewielki, ale dla odległych (np. Wyspy Salomona) różnice sięgały nawet 100 ms.  

- **Fragmentacja pakietów**  
Fragmentacja występowała dla wartości pakietu przekraczających MTU. Dla niektórych serwerów największy niefragmentowany pakiet mieścił się w granicy 1500 bajtów (standardowe MTU dla Ethernetu), ale dla serwerów z USA czy egzotycznych lokalizacji pakiety powyżej 1024 bajtów były już dzielone, co znacząco zwiększało opóźnienia.  

- **Średnica Internetu**  
Za najdłuższą wykrytą ścieżkę uznano połączenie do lands.gov.sb – aż 33 skoki. Oznacza to, że średnica Internetu, rozumiana jako maksymalna liczba routerów pośredniczących, może wynosić powyżej 30 hopów.  

### 3.2. Traceroute  

Wywołanie: `traceroute [adres]`

#### 1. google.com

Szczegóły trasy:
 1.  _gateway (192.168.68.1)  3.271 ms  5.638 ms  5.609 ms
 2.  192.168.0.1 (192.168.0.1)  5.594 ms  5.562 ms  5.536 ms
 3.  10.213.92.1 (10.213.92.1)  7.672 ms  7.646 ms  7.619 ms
 4.  185-56-208-41.ip4.greenlan.pl (185.56.208.41)  7.594 ms  7.570 ms  7.539 ms
 5.  30.56.126.176.ip4.epix.net.pl (176.126.56.30)  10.643 ms  10.620 ms  10.596 ms
 6.  1-1-c28-1-357.ear1.Prague1.Level3.net (212.133.51.113)  13.593 ms  17.376 ms  13.628 ms
 7.  ae1.3103.edge1.bdp1.neo.colt.net (171.75.10.71)  19.882 ms  19.864 ms *
 8.  173.194.121.76 (173.194.121.76)  27.697 ms 4.68.127.38 (4.68.127.38)  30.403 ms  30.387 ms
 9.  \* \* \*
10.  216.239.49.78 (216.239.49.78)  27.604 ms 142.251.65.220 (142.251.65.220)  31.767 ms 142.251.228.28 (142.251.228.28)  27.570 ms
11.  192.178.81.126 (192.178.81.126)  30.191 ms 192.178.72.180 (192.178.72.180)  30.297 ms 192.178.72.142 (192.178.72.142)  31.659 ms
12.  142.251.71.213 (142.251.71.213)  23.508 ms 72.14.233.3 (72.14.233.3)  29.850 ms 142.251.71.213 (142.251.71.213)  25.498 ms
13.  72.14.233.3 (72.14.233.3)  29.690 ms  29.662 ms 216.239.35.132 (216.239.35.132)  25.351 ms
14.  192.178.99.101 (192.178.99.101)  23.933 ms 216.239.40.213 (216.239.40.213)  24.783 ms 142.251.253.217 (142.251.253.217)  24.771 ms
15.  mil02s06-in-f14.1e100.net (172.217.16.14)  23.807 ms  23.327 ms 216.239.40.213 (216.239.40.213)  24.278 ms

#### 2. www.wroclaw.pl

Szczegóły trasy:
 1.  _gateway (192.168.68.1)  9.025 ms  11.524 ms  11.505 ms
 2.  192.168.0.1 (192.168.0.1)  11.458 ms  11.440 ms  11.423 ms
 3.  10.213.92.1 (10.213.92.1)  16.170 ms  18.531 ms  18.515 ms
 4.  185-56-208-41.ip4.greenlan.pl (185.56.208.41)  16.157 ms  16.139 ms  16.122 ms
 5.  cloudflare2.tpix.pl (195.149.233.103)  35.694 ms  23.707 ms  23.690 ms
 6.  162.158.100.23 (162.158.100.23)  23.639 ms  13.978 ms 162.158.100.25 (162.158.100.25)  15.114 ms
 7.  104.18.6.101 (104.18.6.101)  12.463 ms  12.443 ms  12.424 ms

#### 3. lands.gov.sb

 1.  _gateway (192.168.68.1)  4.938 ms  10.611 ms  10.592 ms
 2.  192.168.0.1 (192.168.0.1)  10.595 ms  10.575 ms  10.556 ms
 3.  10.213.92.1 (10.213.92.1)  15.430 ms  16.464 ms  16.446 ms
 4.  185-56-208-41.ip4.greenlan.pl (185.56.208.41)  15.379 ms  15.361 ms  12.780 ms
 5.  2-1-c20-1-346.ear1.Prague1.Level3.net (212.187.202.221)  19.558 ms  19.542 ms  19.524 ms
 6.  \* \* \*
 7.  \* \* \*
 8.  be3261.ccr21.bts01.atlas.cogentco.com (130.117.3.137)  25.712 ms be3263.ccr22.bts01.atlas.cogentco.com (154.54.59.177)  56.658 ms  56.643 ms
 9.  be3463.ccr52.vie01.atlas.cogentco.com (154.54.59.185)  25.649 ms  25.634 ms be2988.ccr51.vie01.atlas.cogentco.com (154.54.59.86)  25.614 ms
10.  be2974.ccr21.muc03.atlas.cogentco.com (154.54.58.5)  29.832 ms be3462.ccr22.muc03.atlas.cogentco.com (154.54.59.182)  29.828 ms  29.812 ms
11.  be7944.ccr42.fra05.atlas.cogentco.com (154.54.75.98)  194.949 ms be5516.ccr41.fra05.atlas.cogentco.com (154.54.62.121)  189.125 ms be7944.ccr42.fra05.atlas.cogentco.com (154.54.75.98)  189.056 ms
12.  be5967.ccr41.fra05.atlas.cogentco.com (154.54.58.153)  191.080 ms  191.051 ms be3733.ccr31.sin01.atlas.cogentco.com (154.54.166.118)  190.402 ms
13.  be2428.ccr51.per01.atlas.cogentco.com (154.54.88.137)  256.365 ms be3733.ccr31.sin01.atlas.cogentco.com (154.54.166.118)  190.264 ms  229.613 ms
14.  be2546.ccr71.syd01.atlas.cogentco.com (154.54.1.30)  280.392 ms be3578.agr51.syd01.atlas.cogentco.com (154.54.47.18)  287.320 ms be2428.ccr51.per01.atlas.cogentco.com (154.54.88.137)  234.590 ms
15.  be3585.ccr71.syd01.atlas.cogentco.com (154.54.47.29)  283.229 ms  283.155 ms 154.18.96.10 (154.18.96.10)  279.663 ms
16.  154.18.96.10 (154.18.96.10)  278.219 ms *  277.646 ms
17.  \* \* reth0-1094.fw01.cp.glsw.as55803.net.au (101.0.127.117)  276.681 ms
18.  \* reth0-1094.fw01.cp.glsw.as55803.net.au (101.0.127.117)  279.063 ms  367.215 ms
19.  reth0-1094.fw01.cp.glsw.as55803.net.au (101.0.127.117)  367.123 ms  367.086 ms vmres08.web-servers.com.au (116.90.60.58)  368.339 ms

#### 4. example.com

 1.  _gateway (192.168.68.1)  6.319 ms  14.430 ms  14.409 ms
 2.  192.168.0.1 (192.168.0.1)  14.334 ms  14.311 ms  14.292 ms
 3.  10.213.92.1 (10.213.92.1)  13.173 ms  18.188 ms  13.134 ms
 4.  185-56-208-41.ip4.greenlan.pl (185.56.208.41)  13.124 ms  13.106 ms  13.086 ms
 5.  2-1-c20-1-346.ear1.Prague1.Level3.net (212.187.202.221)  21.012 ms  18.706 ms  20.975 ms
 6.  prag-b4-link.ip.twelve99.net (62.115.184.34)  24.503 ms  21.493 ms  22.738 ms
 7.  ffm-bb2-link.ip.twelve99.net (62.115.124.28)  27.950 ms  42.230 ms  30.132 ms
 8.  prs-bb2-link.ip.twelve99.net (62.115.122.138)  42.196 ms  42.181 ms  42.170 ms
 9.  ash-bb2-link.ip.twelve99.net (62.115.140.107)  124.382 ms  124.371 ms  124.347 ms
10.  \* rest-b6-link.ip.twelve99.net (62.115.140.209)  124.319 ms \*
11.  akamai-ic-382205.ip.twelve99-cust.net (80.239.161.243)  129.624 ms  129.612 ms  171.320 ms
12.  lo1.r03.stem01.iad04.fab.netarch.akamai.com (23.44.169.22)  124.402 ms lo1.r02.stem01.iad04.fab.netarch.akamai.com (23.44.169.21)  128.490 ms lo1.r01.stem01.iad04.fab.netarch.akamai.com (23.44.169.20)  128.422 ms
13.  lo1.r01.spine02.iad04.fab.netarch.akamai.com (23.44.169.8)  124.124 ms lo1.r01.spine03.iad04.fab.netarch.akamai.com (23.44.169.12)  124.032 ms lo1.r03.spine04.iad04.fab.netarch.akamai.com (23.44.169.18)  128.080 ms
14.  lo1.r02.leaf01.iad04.fab.netarch.akamai.com (23.44.169.28)  123.982 ms lo1.r03.leaf01.iad04.fab.netarch.akamai.com (23.44.169.29)  122.900 ms  124.191 ms
15.  vlan100.r19.tor01.iad04.fab.netarch.akamai.com (23.213.246.129)  128.342 ms  128.281 ms  128.200 ms
16.  a23-215-0-136.deploy.static.akamaitechnologies.com (23.215.0.136)  123.790 ms  123.971 ms  123.167 ms


- **Liczba węzłów**  
Dla krótkich tras (np. www.wroclaw.pl) liczba węzłów była bardzo mała – tylko 7 skoków.  
Trasa do lands.gov.sb była wyjątkowo długa i złożona (co najmniej 19 widocznych hopów, z licznymi opóźnieniami i przesiadkami między kontynentami).  

- **Trasy przez sieci wirtualne (cloud)**  
Obecność w trasach routerów obsługiwanych przez firmy jak Akamai, Google, czy Cloudflare potwierdza obecność sieci wirtualnych i platform chmurowych. Dla tras do `example.com` wyraźnie widoczne były segmenty prowadzące przez infrastrukturę Akamai, co świadczy o dynamicznym przekierowywaniu ruchu.  

- **Czas propagacji**  
Im dalsza lokalizacja, tym wyraźniejszy wzrost czasu odpowiedzi. Do USA wartości osiągały 120-150 ms, do Wysp Salomona – nawet 370 ms.  

---

### 4. Wnioski  

1. Program `ping` jest bardzo użytecznym narzędziem do szybkiej diagnozy dostępności i oceny jakości łącza, ale nie daje informacji o szczegółowej trasie pakietu.
2. Wielkość pakietu wpływa znacząco na opóźnienia. Na krótkich dystansach wpływ jest minimalny, natomiast dla serwerów oddalonych geograficznie wzrost czasu jest zauważalny, a powyżej MTU pojawia się fragmentacja i dodatkowe opóźnienia.
3. `Traceroute` pozwala dokładnie prześledzić trasę i jest kluczowy w analizie, gdzie występują opóźnienia i straty. Dzięki niemu można zidentyfikować „wąskie gardła” oraz serwery pośrednie, które mogą należeć do dużych dostawców chmurowych.
4. Średnica Internetu może wynosić nawet powyżej 30 hopów, a przesyłanie pakietów do bardzo odległych lokalizacji wiąże się ze znacznymi opóźnieniami i często wymusza korzystanie z rozproszonych sieci CDN i cloud computing.
5. Zarówno `ping`, jak i `traceroute` są narzędziami komplementarnymi, pozwalającymi nie tylko na ocenę dostępności serwera, ale także na analizę topologii sieci oraz jakości połączenia.  

