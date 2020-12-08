#include <stdio.h>
#include <stdlib.h>
#include "../../sqlitec/sqlite3.h"

//soronkénti visszatérés a column-ok nevével, és a hozzá tartozó adatokkal
int ourCallback(void *ptr, int numberOfColumns, char **returnedValues, char **columnNames)
{
    for(int i = 0; i < numberOfColumns; i++)
    {
        printf("%s = %s\n", columnNames[i], returnedValues[i]);
    }

    return SQLITE_OK;
}

int main()
{
    sqlite3 *ourdb = NULL;

    int retOpen = sqlite3_open_v2("13gyak.db", &ourdb, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, "win32-longpath"); //adatbázis létrehozása, "kapcsolódás"
    if(retOpen != SQLITE_OK)
    {
        printf("Couldn't open database 13gyak.db Err: %s\n", sqlite3_errmsg(ourdb));
        exit(0);
    }

    int retOfCreateTable = sqlite3_exec(ourdb, "CREATE TABLE `teszt` (`id` INTEGER PRIMARY KEY AUTOINCREMENT, `szoveg` text NOT NULL)", NULL, NULL, NULL); //tábla létrehozása
    if(retOfCreateTable != SQLITE_OK)
    {
        printf("Couldn't create TABLE \'teszt\'. Err: %s\n", sqlite3_errmsg(ourdb));
    }

    const char *preparedQuery = "REPLACE INTO `teszt` (`id`, `szoveg`) VALUES (:userId, :userName);"; //SQL injection ellen prepared statement használata

    sqlite3_stmt *sqlitestmt = NULL;
    char *unused = NULL;

    int retOfInsert = sqlite3_prepare_v2(ourdb, preparedQuery, strlen(preparedQuery), &sqlitestmt, &unused);
    if(retOfInsert != SQLITE_OK)
    {
        printf("Couldn't prepare into TABLE \'teszt\'. Err: %s\n", sqlite3_errmsg(ourdb));
        exit(1);
    }
    int primaryId = 1;

    const char *currentName = "teszt2";

    sqlite3_bind_int(sqlitestmt, sqlite3_bind_parameter_index(sqlitestmt, ":userId"), primaryId);
    sqlite3_bind_text(sqlitestmt, sqlite3_bind_parameter_index(sqlitestmt, ":userName"), currentName, strlen(currentName), SQLITE_STATIC);

    int retOfReplace = sqlite3_step(sqlitestmt); //előkészített query lefuttatása
    if(retOfReplace != SQLITE_DONE)
    {
        printf("Couldn't replace into TABLE \'teszt\'. Err: %s\n", sqlite3_errmsg(ourdb));
        exit(1);
    }

    char *err_msg = NULL;

    int retOfSelect = sqlite3_exec(ourdb, "SELECT * FROM `teszt`", ourCallback, NULL, &err_msg);
    if(retOfSelect != SQLITE_OK)
    {
        printf("Couldn't select from TABLE \'teszt\'. Err: %s\n", sqlite3_errmsg(ourdb));
        exit(1);
    }

    sqlite3_close(ourdb);

    return 0;
}
