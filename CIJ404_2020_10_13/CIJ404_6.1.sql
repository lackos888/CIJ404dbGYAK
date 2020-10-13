mysql> CREATE TABLE GYARTO (adoszam INT PRIMARY KEY, nev CHAR(30));

mysql> CREATE TABLE TERMEK (tkod INT PRIMARY KEY, nev CHAR(50), ear INT, gyarto INT, CHECK(ear > 0), FOREIGN KEY (gyarto) REFERENCES GYARTO (adoszam));

