//
//  Relation.h
//  RDB
//
//  Created by Seungmin Kuk on 10/11/2019.
//  Copyright © 2019 Seungmin Kuk. All rights reserved.
//

#ifndef Relation_h
#define Relation_h
#include "LinkedList.h"
#include <stdio.h>
#include <string.h>


typedef struct Tuple *Tuple;
struct Tuple {
    char* array[10];
    int size;
};

typedef struct Relation* Relation;
struct Relation{
    char* name;
    Tuple schema;
    int key;
    LinkedList hashTable[19];
    int column_size;
    int num_tuples;
};


extern Relation Relation_new(void);
extern int Relation_hash(int keynum);
extern void Relation_free(Relation relation);
extern bool Relation_compare_tuple(Tuple tuple1,Tuple tuple2);
extern void Relation_insert(Tuple tuple,Relation relation);
extern  Tuple Tuple_new(void);
extern void Tuple_free(Tuple tuple);
extern void Relation_delete(Tuple tuple,Relation relation);

extern LinkedList Relation_lookup(Tuple tuple,Relation relation);

extern void Relation_Tuple_setSize(int size,Tuple tuple);
extern void Relation_Tuple_addElements(char* elements[],Tuple tuple);
extern void Relation_setRelation(int key,Tuple schema,char* name,Relation relation);
extern void Tuple_print(Tuple tuple);
extern void Relation_lookup_print(LinkedList this,Relation relation,Tuple tuple);
extern void Relation_print(Relation relation);
extern void Relation_query_grade(Relation SNAP, Relation CSG,char* name, char* course );
extern void Relation_query_location(Relation CSG, Relation SNAP, Relation CDH, Relation CR,char* name, char* day, char* hour);
extern Relation Relation_selection(Relation relation,char* condition,char*type);
extern Relation Relation_projection(Relation relation,LinkedList conditions);
extern Relation Relation_join(Relation relation1,Relation relation2,char * condition);
#endif /* Relation_h */
