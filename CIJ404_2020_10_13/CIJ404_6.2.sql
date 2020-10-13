mysql> ALTER TABLE GYARTO ADD irsz CHAR(4);

mysql> ALTER TABLE GYARTO ADD varos CHAR(40);

mysql> ALTER TABLE GYARTO ADD utca CHAR(100);

mysql> CREATE TABLE Egysegek (aru INT, db INT NOT NULL CHECK (db > 0), FOREIGN KEY (aru) REFERENCES TERMEK (tkod));

mysql> CREATE TABLE Alkatresz (akod INT PRIMARY KEY, nev CHAR(50));

mysql> CREATE TABLE Komponens (termek INT, alkatresz INT, FOREIGN KEY (termek) REFERENCES TERMEK (tkod), FOREIGN KEY (alkatresz) REFERENCES Alkatresz (akod));
