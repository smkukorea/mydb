
#ifndef Database_h
#define Database_h

#include <stdio.h>

#include "Relation.h"


struct Database{
    LinkedList relations;
};

typedef struct Database* Database;

extern int numRelation(LinkedList relations);
extern Database new_Database(void);

extern void outputFile(Database database, char* filename);

extern Database readFile(char* filename);

extern int stringToInt(char* string);

extern Tuple stringToTuple(char* tuple);

extern void removeNewLine2(char* i);

extern char* removeNewLine(char* i);

extern char* readLine(FILE * file);

extern void DB_print(Database db);

extern void DB_free(Database db);
#endif
