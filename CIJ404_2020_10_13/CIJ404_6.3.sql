mysql> CREATE TABLE Tanfolyam (tkod INT PRIMARY KEY, ar INT NOT NULL, tipus char(32), megnevezes varchar(128) NOT NULL CHECK (ar > 0));

mysql> CREATE TABLE Resztvevo (tajszam INT PRIMARY KEY, lakcim varchar(128) NOT NULL, nev varchar(128) NOT NULL);

mysql> CREATE TABLE Befizetesek (tajszam INT NOT NULL, tkod INT NOT NULL, FOREIGN KEY (tajszam) REFERENCES Resztvevo (tajszam), FOREIGN KEY (tkod) REFERENCES Tanfolyam (tkod));
