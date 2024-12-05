/*M!999999\- enable the sandbox mode */ 
-- MariaDB dump 10.19-11.5.2-MariaDB, for debian-linux-gnu (x86_64)
--
-- Host: localhost    Database: people
-- ------------------------------------------------------
-- Server version	11.5.2-MariaDB-ubu2404

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*M!100616 SET @OLD_NOTE_VERBOSITY=@@NOTE_VERBOSITY, NOTE_VERBOSITY=0 */;

--
-- Table structure for table `Ludzie`
--

DROP TABLE IF EXISTS `Ludzie`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `Ludzie` (
  `PESEL` char(11) NOT NULL CHECK (`PESEL`  not like '%[^0-9]%'),
  `imie` varchar(30) DEFAULT NULL,
  `nazwisko` varchar(30) DEFAULT NULL,
  `data_urodzenia` date DEFAULT NULL,
  `plec` enum('K','M') DEFAULT NULL,
  PRIMARY KEY (`PESEL`),
  CONSTRAINT `peselDay` CHECK (substr(`PESEL`,5,2) < 32),
  CONSTRAINT `peselGender` CHECK (substr(`PESEL`,10,1) MOD 2 = 0 and `plec` = 'K' or substr(`PESEL`,10,1) MOD 2 = 1 and `plec` = 'M'),
  CONSTRAINT `peselLastDigit` CHECK ((substr(`PESEL`,1,1) + 3 * substr(`PESEL`,2,1) + 7 * substr(`PESEL`,3,1) + 9 * substr(`PESEL`,4,1) + substr(`PESEL`,5,1) + 3 * substr(`PESEL`,6,1) + 7 * substr(`PESEL`,7,1) + 9 * substr(`PESEL`,8,1) + substr(`PESEL`,9,1) + 3 * substr(`PESEL`,10,1) + substr(`PESEL`,11,1)) MOD 10 = 0)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_uca1400_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Ludzie`
--

LOCK TABLES `Ludzie` WRITE;
/*!40000 ALTER TABLE `Ludzie` DISABLE KEYS */;
INSERT INTO `Ludzie` VALUES
('08271802143','Anna','Kowalska','2008-07-18','K'),
('09312209844','Julia','Wójcik','2009-11-22','K'),
('10251212350','Mateusz','Nowak','2010-05-12','M'),
('11263016530','Filip','Zieliński','2011-06-30','M'),
('12231013571','Jakub','Wiśniewski','2012-03-10','M'),
('44021509849','Maria','Nowak','1944-02-15','K'),
('48071202387','Krystyna','Wójcik','1948-07-12','K'),
('50010112336','Jan','Kowalski','1950-01-01','M'),
('57030511594','Tadeusz','Wiśniewski','1957-03-05','M'),
('60080913537','Zbigniew','Zieliński','1960-08-09','M'),
('72060615652','Adam','Sikorski','1972-06-06','M'),
('79090314775','Tomasz','Krawczyk','1979-09-03','M'),
('81020312335','Krzysztof','Kowalski','1981-02-03','M'),
('81092203461','Magdalena','Szulc','1981-09-22','K'),
('82071918235','Andrzej','Baran','1982-07-19','M'),
('82081707139','Rafał','Lis','1982-08-17','M'),
('83052408583','Natalia','Walczak','1983-05-24','K'),
('84073010571','Jacek','Czajka','1984-07-30','M'),
('84091912631','Mateusz','Malinowski','1984-09-19','M'),
('84122311596','Piotr','Wiśniewski','1984-12-23','M'),
('85061009827','Ewa','Kamińska','1985-06-10','K'),
('85061813578','Przemysław','Gajda','1985-06-18','M'),
('85080518322','Barbara','Jankowska','1985-08-05','K'),
('85090519843','Aleksandra','Sikorska','1985-09-05','K'),
('86051408714','Janusz','Majewski','1986-05-14','M'),
('86071514378','Karol','Sobczak','1986-07-15','M'),
('86091518374','Kacper','Brzeziński','1986-09-15','M'),
('87041712190','Adam','Czarnecki','1987-04-17','M'),
('87062413955','Marcin','Górski','1987-06-24','M'),
('87092709242','Justyna','Sadowska','1987-09-27','K'),
('88010605921','Alicja','Rutkowska','1988-01-06','K'),
('88021515934','Paweł','Dąbrowski','1988-02-15','M'),
('88041214835','Dominik','Wieczorek','1988-04-12','M'),
('88070517963','Gabriela','Wolska','1988-07-05','K'),
('88082917847','Ewelina','Pawlak','1988-08-29','K'),
('89012315393','Wojciech','Marciniak','1989-01-23','M'),
('89030405179','Grzegorz','Michalski','1989-03-04','M'),
('89031516599','Sebastian','Witkowski','1989-03-15','M'),
('89080713534','Michał','Zieliński','1989-08-07','M'),
('89090207425','Monika','Piotrowska','1989-09-02','K'),
('90041509848','Anna','Nowak','1990-04-15','K'),
('91021811245','Zuzanna','Krysiak','1991-02-18','K'),
('91031204183','Sylwia','Wiśniewska','1991-03-12','K'),
('91031307367','Joanna','Lewandowska','1991-03-13','K'),
('91091109347','Renata','Zając','1991-09-11','K'),
('92010110327','Patrycja','Adamska','1992-01-01','K'),
('92071202380','Maria','Wójcik','1992-07-12','K'),
('93030312988','Martyna','Król','1993-03-03','K'),
('93050113659','Kamil','Kubiak','1993-05-01','M'),
('93070619829','Karolina','Ostrowska','1993-07-06','K'),
('94010203649','Agnieszka','Mazur','1994-01-02','K'),
('94021315771','Łukasz','Kozłowski','1994-02-13','M'),
('95062109242','Katarzyna','Szymańska','1995-06-21','K'),
('95071011235','Artur','Chmielewski','1995-07-10','M'),
('95080815640','Weronika','Stępień','1995-08-08','K');
/*!40000 ALTER TABLE `Ludzie` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Pracownicy`
--

DROP TABLE IF EXISTS `Pracownicy`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `Pracownicy` (
  `pracownik_id` int(11) NOT NULL AUTO_INCREMENT,
  `PESEL` char(11) DEFAULT NULL,
  `zawod_id` int(11) DEFAULT NULL,
  `pensja` float DEFAULT NULL CHECK (`pensja` >= 0),
  PRIMARY KEY (`pracownik_id`),
  KEY `PESEL` (`PESEL`),
  KEY `zawod_id` (`zawod_id`),
  CONSTRAINT `Pracownicy_ibfk_1` FOREIGN KEY (`PESEL`) REFERENCES `Ludzie` (`PESEL`),
  CONSTRAINT `Pracownicy_ibfk_2` FOREIGN KEY (`zawod_id`) REFERENCES `Zawody` (`zawod_id`)
) ENGINE=InnoDB AUTO_INCREMENT=51 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_uca1400_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Pracownicy`
--

LOCK TABLES `Pracownicy` WRITE;
/*!40000 ALTER TABLE `Pracownicy` DISABLE KEYS */;
INSERT INTO `Pracownicy` VALUES
(1,'44021509849',2,4063.4),
(2,'48071202387',1,55384.5),
(3,'50010112336',2,4849.5),
(4,'57030511594',4,17975.6),
(5,'60080913537',3,12352.5),
(6,'72060615652',1,99446.6),
(7,'79090314775',3,12773.2),
(8,'81020312335',3,17356.4),
(9,'81092203461',2,5511.84),
(10,'82071918235',4,7096.01),
(11,'82081707139',1,90585.5),
(12,'83052408583',1,88848.2),
(13,'84073010571',4,14761.9),
(14,'84091912631',3,10908.8),
(15,'84122311596',2,6211.83),
(16,'85061009827',4,10263.4),
(17,'85061813578',4,22979),
(18,'85080518322',2,6990.25),
(19,'85090519843',2,5067.59),
(20,'86051408714',2,4569.33),
(21,'86071514378',1,81787.6),
(22,'86091518374',3,23846.7),
(23,'87041712190',2,3607.58),
(24,'87062413955',2,6384.57),
(25,'87092709242',4,8385.01),
(26,'88010605921',3,14346),
(27,'88021515934',2,5180.06),
(28,'88041214835',3,13355.8),
(29,'88070517963',3,8862.05),
(30,'88082917847',2,4337.46),
(31,'89012315393',3,18303.1),
(32,'89030405179',2,6304.87),
(33,'89031516599',2,6224.83),
(34,'89080713534',4,16704.3),
(35,'89090207425',3,8229.16),
(36,'90041509848',4,18509.4),
(37,'91021811245',1,8192.04),
(38,'91031204183',1,29878.1),
(39,'91031307367',4,24908.7),
(40,'91091109347',3,21015.4),
(41,'92010110327',2,4855.89),
(42,'92071202380',4,12349.1),
(43,'93030312988',4,22129.2),
(44,'93050113659',3,24839.3),
(45,'93070619829',4,23652.4),
(46,'94010203649',4,23191.8),
(47,'94021315771',3,8367.06),
(48,'95062109242',2,6361.16),
(49,'95071011235',3,16950.1),
(50,'95080815640',1,90875.3);
/*!40000 ALTER TABLE `Pracownicy` ENABLE KEYS */;
UNLOCK TABLES;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8mb3 */ ;
/*!50003 SET character_set_results = utf8mb3 */ ;
/*!50003 SET collation_connection  = utf8mb3_uca1400_ai_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'STRICT_TRANS_TABLES,ERROR_FOR_DIVISION_BY_ZERO,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=`root`@`localhost`*/ /*!50003 TRIGGER ValidatePensja
BEFORE INSERT ON Pracownicy
FOR EACH ROW
BEGIN
    DECLARE pensjaMin float;
    DECLARE pensjaMax float;

    SELECT pensja_min, pensja_max INTO pensjaMin, pensjaMax
    FROM Zawody
    WHERE zawod_id = NEW.zawod_id;

    IF NEW.pensja < pensjaMin OR NEW.pensja > pensjaMAX THEN
        SIGNAL SQLSTATE '45000' SET MESSAGE_TEXT = 'Pensja is out of range';
    END IF;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;

--
-- Table structure for table `Zawody`
--

DROP TABLE IF EXISTS `Zawody`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `Zawody` (
  `zawod_id` int(11) NOT NULL AUTO_INCREMENT,
  `nazwa` varchar(50) DEFAULT NULL,
  `pensja_min` float DEFAULT NULL CHECK (`pensja_min` >= 0),
  `pensja_max` float DEFAULT NULL CHECK (`pensja_max` >= 0),
  PRIMARY KEY (`zawod_id`),
  CONSTRAINT `pensja_min_man` CHECK (`pensja_min` < `pensja_max`)
) ENGINE=InnoDB AUTO_INCREMENT=5 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_uca1400_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Zawody`
--

LOCK TABLES `Zawody` WRITE;
/*!40000 ALTER TABLE `Zawody` DISABLE KEYS */;
INSERT INTO `Zawody` VALUES
(1,'Polityk',4000,100000),
(2,'Nauczyciel',3500,7000),
(3,'Lekarz',8000,25000),
(4,'Informatyk',5000,25000);
/*!40000 ALTER TABLE `Zawody` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Dumping routines for database 'people'
--
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'STRICT_TRANS_TABLES,ERROR_FOR_DIVISION_BY_ZERO,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ ;
/*!50003 DROP FUNCTION IF EXISTS `PeselCheck` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8mb3 */ ;
/*!50003 SET character_set_results = utf8mb3 */ ;
/*!50003 SET collation_connection  = utf8mb3_uca1400_ai_ci */ ;
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` FUNCTION `PeselCheck`(pesel CHAR(11)) RETURNS tinyint(1)
BEGIN
    DECLARE p1 INT DEFAULT SUBSTRING(pesel, 1, 1);
    DECLARE p2 INT DEFAULT SUBSTRING(pesel, 2, 1);
    DECLARE p3 INT DEFAULT SUBSTRING(pesel, 3, 1);
    DECLARE p4 INT DEFAULT SUBSTRING(pesel, 4, 1);
    DECLARE p5 INT DEFAULT SUBSTRING(pesel, 5, 1);
    DECLARE p6 INT DEFAULT SUBSTRING(pesel, 6, 1);
    DECLARE p7 INT DEFAULT SUBSTRING(pesel, 7, 1);
    DECLARE p8 INT DEFAULT SUBSTRING(pesel, 8, 1);
    DECLARE p9 INT DEFAULT SUBSTRING(pesel, 9, 1);
    DECLARE p10 INT DEFAULT SUBSTRING(pesel, 10, 1);
    DECLARE p11 INT DEFAULT SUBSTRING(pesel, 11, 1);
    RETURN ((p1 + 3*p2 + 7*p3 + 9*p4 + p5 + 3*p6 + 7*p7 + 9*p8 + p9 + 3*p10 + p11) % 10) = 0;
END ;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'STRICT_TRANS_TABLES,ERROR_FOR_DIVISION_BY_ZERO,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ ;
/*!50003 DROP PROCEDURE IF EXISTS `AddEmployment` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8mb3 */ ;
/*!50003 SET character_set_results = utf8mb3 */ ;
/*!50003 SET collation_connection  = utf8mb3_uca1400_ai_ci */ ;
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `AddEmployment`()
BEGIN
  DECLARE done BOOLEAN DEFAULT FALSE;
  DECLARE curPesel CHAR(11);
  DECLARE curBDate DATE;
  DECLARE curGender ENUM('K', 'M');
  DECLARE minSalary FLOAT;
  DECLARE maxSalary FLOAT;
  DECLARE rndSalary FLOAT;
  DECLARE rndProfession INT;

  DECLARE ludzieCursor CURSOR FOR
    SELECT PESEL, data_urodzenia, plec FROM Ludzie
    WHERE data_urodzenia <= DATE_SUB(CURDATE(), INTERVAL 18 YEAR);

  DECLARE CONTINUE HANDLER FOR NOT FOUND SET done = TRUE;

  OPEN ludzieCursor;

  ludzieLoop: LOOP
    IF done THEN
      LEAVE ludzieLoop;
    END IF;

    FETCH ludzieCursor INTO curPesel, curBDate, curGender;

    REPEAT
      SELECT zawod_id, pensja_min, pensja_max
      INTO rndProfession, minSalary, maxSalary
      FROM Zawody
      ORDER BY RAND()
      LIMIT 1;

      IF (rndProfession = (SELECT zawod_id FROM Zawody WHERE nazwa = 'Lekarz')) THEN
        IF (curGender = 'M' AND curBDate < DATE_SUB(CURDATE(), INTERVAL 65 YEAR)) OR (curGender = 'K' AND curBDate < DATE_SUB(CURDATE(), INTERVAL 60 YEAR)) THEN
          SET rndProfession = NULL;
        END IF;
      END IF;
    UNTIL rndProfession IS NOT NULL END REPEAT;

    SET rndSalary = minSalary + RAND() * (maxSalary - minSalary);

    IF NOT EXISTS (
      SELECT 1 FROM Pracownicy
      WHERE PESEL = curPesel
    ) THEN
      INSERT INTO Pracownicy(PESEL, zawod_id, pensja) VALUES
      (curPesel, rndProfession, rndSalary);
    END IF;
        
  END LOOP;

  CLOSE ludzieCursor;
END ;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*M!100616 SET NOTE_VERBOSITY=@OLD_NOTE_VERBOSITY */;

-- Dump completed on 2024-12-05  0:51:59
