//
//  Relation.c
//  RDB
//
//  Created by Seungmin Kuk on 10/11/2019.
//  Copyright © 2019 Seungmin Kuk. All rights reserved.

#include "Relation.h"
#include <stdio.h>
#include <stdlib.h>

Tuple Tuple_new(void) {
    Tuple this = (Tuple)malloc(sizeof(struct Tuple));
    this->size=0;
    return this;
}

void Tuple_free(Tuple tuple){
    if(tuple==NULL){
        return;
    }
    

}
Relation Relation_new(void){
    Relation this = (Relation)malloc(sizeof(struct Relation));
    this->name=NULL;
    this->schema=Tuple_new();
    this->key=-100;
    this->num_tuples=0;
    for (int i=0; i<19; i++){
        this->hashTable[i] = new_LinkedList();
    }
    return this;
}


void Relation_free(Relation relation){
    if (relation == NULL) {
        return;
    }
    
    
    Tuple_free(relation->schema);
    
    for(int i=0;i<19; i++){
        if(relation->hashTable[i]!=NULL){
            int size=LinkedList_getsize(relation->hashTable[i]);
            for(int j=0;j<size;j++){
                Tuple t=LinkedList_elementAt(relation->hashTable[i], j);
                Tuple_free(t);
            }
            LinkedList_free(relation->hashTable[i], true);
        }
        
        
    }
   
    
}

int Relation_hash(int keynum){
    return keynum%19;
}


void Relation_insert(Tuple tuple,Relation relation){
    int key=*(tuple->array[relation->key]);
    int hash_index=Relation_hash(key);
    LinkedListIterator l=LinkedList_iterator(relation->hashTable[hash_index]);
    bool same=false;
    while(LinkedListIterator_hasNext(l)){
        
        Tuple temp = LinkedListIterator_next(l);
        if( Relation_compare_tuple(tuple, temp)){
            same=true;
            break;
        }
    }free(l);
    if(!same){
        LinkedList_add_at_end(relation->hashTable[hash_index], tuple);
        relation->num_tuples++;
    }
}

void Relation_delete(Tuple tuple,Relation relation){
    
    if(*tuple->array[relation->key]!='*'){
        int key=*(tuple->array[relation->key]);
        int hash_index=Relation_hash(key);
        
        LinkedListIterator l=LinkedList_iterator(relation->hashTable[hash_index]);
        while(LinkedListIterator_hasNext(l)){
            
            Tuple temp = LinkedListIterator_next(l);
            
            
            if(Relation_compare_tuple(tuple, temp)){
                LinkedList_remove(relation->hashTable[hash_index], temp);
                relation->num_tuples--;
            }
            
        }free(l);
    }else{
        
        for(int i=0;i<19;i++){
            LinkedListIterator l=LinkedList_iterator(relation->hashTable[i]);
            while(LinkedListIterator_hasNext(l)){
                
                Tuple temp = LinkedListIterator_next(l);
                
                
                if(Relation_compare_tuple(tuple, temp)){
                    LinkedList_remove(relation->hashTable[i], temp);
                    relation->num_tuples--;
                }
                
            }
            free(l);
        }
    }
    
}

LinkedList Relation_lookup(Tuple tuple,Relation relation){
    LinkedList output_list=new_LinkedList();
    if(*tuple->array[relation->key]!='*'){
        int key=*(tuple->array[relation->key]);
        int hash_index=Relation_hash(key);
        
        LinkedListIterator l=LinkedList_iterator(relation->hashTable[hash_index]);
        while(LinkedListIterator_hasNext(l)){
            
            Tuple temp = LinkedListIterator_next(l);
            
            
            if(Relation_compare_tuple(tuple, temp)){
                LinkedList_add_at_end(output_list, temp);
            }
            
        }free(l);
    }else{
        for(int i=0;i<19;i++){
            LinkedListIterator l=LinkedList_iterator(relation->hashTable[i]);
            while(LinkedListIterator_hasNext(l)){
                
                Tuple temp = LinkedListIterator_next(l);
                
                if(Relation_compare_tuple(tuple, temp)){
                    LinkedList_add_at_end(output_list, temp);
                }
            }
            free(l);
            
            
        }
    }
    return output_list;
    
}

void Relation_lookup_print(LinkedList this,Relation relation,Tuple tuple){
    
    printf("\n");
    printf("Result of lookup for tuple: ");
    Tuple_print(tuple);
    
    Tuple_print(relation->schema);
    LinkedListIterator l=LinkedList_iterator(this);
    while(LinkedListIterator_hasNext(l)){
        
        
        Tuple temp = LinkedListIterator_next(l);
        
        Tuple_print(temp);
        
    }
    free(l);
    
}


bool Relation_compare_tuple(Tuple tuple1,Tuple tuple2){
    
    
    for (int i=0; i<tuple1->size; i++){
        if(strcmp(tuple1->array[i], tuple2->array[i])!=0 && strcmp(tuple1->array[i], "*")!=0){
            return false;
        }
    }
    return true;
}
void Relation_Tuple_setSize(int size,Tuple tuple){
    tuple->size=size;
}

void Relation_Tuple_addElements(char* elements[],Tuple tuple){
    for(int i=0; i<tuple->size;i++){
        tuple->array[i]=elements[i];
    }
}

void Relation_setRelation(int key,Tuple schema,char* name,Relation relation){
    relation->key=key;
    relation->name=name;
    relation->schema=schema;
    relation->column_size=schema->size;
    
}

void Tuple_print(Tuple tuple){
    if(tuple==NULL){
        return;
    }
    for(int i=0;i<tuple->size;i++){
        printf("%s\t\t", tuple->array[i]);
    }
    printf("\n");
}

void Relation_print(Relation relation){
    Tuple_print(relation->schema);
    
    
    for(int i=0;i<19;i++){
        LinkedListIterator l=LinkedList_iterator(relation->hashTable[i]);
        while(LinkedListIterator_hasNext(l)){
            Tuple temp = LinkedListIterator_next(l);
            
            Tuple_print(temp);
        }
        free(l);
    }
    
}
void Relation_query_grade(Relation SNAP, Relation CSG,char* name, char* course ){
    //setup student t with given name
    Tuple student=Tuple_new();
    Relation_Tuple_setSize(SNAP->column_size, student);
    student->array[1]=name;
    student->array[0]="*";
    student->array[2]="*";
    student->array[3]="*";
    LinkedList students=Relation_lookup(student, SNAP);
    LinkedListIterator l=LinkedList_iterator(students);
    while(LinkedListIterator_hasNext(l)){
        Tuple temp=LinkedListIterator_next(l);
        char* id=temp->array[0];
        
        for(int i=0;i<19;i++){
            LinkedListIterator it=LinkedList_iterator(CSG->hashTable[i]);
            while(LinkedListIterator_hasNext(it)){
                
                Tuple temp = LinkedListIterator_next(it);
                
                if(strcmp(temp->array[0],course)==0&&strcmp(temp->array[1],id)==0){
                    printf("Student received %s in %s\n",temp->array[2],temp->array[0]);
                }
            }free(it);
        }
        
    }
    free(l);
}
void Relation_query_location(Relation CSG, Relation SNAP, Relation CDH, Relation CR,char* name, char* day, char* hour){
    Tuple student=Tuple_new();
    Relation_Tuple_setSize(SNAP->column_size, student);
    
    student->array[0]="*";
    student->array[1]=name;
    student->array[2]="*";
    student->array[3]="*";
    LinkedList students=Relation_lookup(student, SNAP);
    
    LinkedListIterator l=LinkedList_iterator(students);
    while(LinkedListIterator_hasNext(l)){
        Tuple temp=LinkedListIterator_next(l);
        
        
        
        char* id=temp->array[0];
        Tuple ids=Tuple_new();
        Relation_Tuple_setSize(CSG->column_size, ids);
        ids->array[0]="*";
        ids->array[1]=id;
        ids->array[2]="*";
        LinkedList courses=Relation_lookup(ids, CSG);
        
        
        
        LinkedListIterator it=LinkedList_iterator(courses);
        while(LinkedListIterator_hasNext(it)){
            Tuple tempcourse=LinkedListIterator_next(it);
            
            
            char* cur_course=tempcourse->array[0];
            Tuple time=Tuple_new();
            Relation_Tuple_setSize(CDH->column_size, time);
            time->array[0]=cur_course;
            time->array[1]=day;
            time->array[2]=hour;
            LinkedList times=Relation_lookup(time, CDH);
            LinkedListIterator itt=LinkedList_iterator(times);
            while(LinkedListIterator_hasNext(itt)){
                Tuple temptime=LinkedListIterator_next(itt);
                
                
                char* cur_time_course=temptime->array[0];
                Tuple room=Tuple_new();
                Relation_Tuple_setSize(CR->column_size, room);
                room->array[0]=cur_time_course;
                room->array[1]="*";
                LinkedList location=Relation_lookup(room, CR);
                
                
                LinkedListIterator ittt=LinkedList_iterator(location);
                while(LinkedListIterator_hasNext(ittt)){
                    Tuple response=LinkedListIterator_next(ittt);
                    printf("The location of the student is :%s\n",response->array[1]);
                }free(ittt);
                
                
            }free(itt);
        }free(it);
    }free(l);
}



LinkedList hashTable[19];
int column_size;
int num_tuples;


Relation Relation_selection(Relation relation,char* condition,char* type){
    Relation selection=Relation_new();
    Relation_setRelation(relation->key, relation->schema, condition, selection);
    selection->column_size=relation->column_size;
    Tuple con=Tuple_new();
    Relation_Tuple_setSize(selection->column_size, con);
    int con_index = 100;
    
    for(int i=0;i<relation->column_size;i++){
        if(strcmp(relation->schema->array[i], type)==0){
            con_index=i;
        }
    }
    
    for(int i=0;i<con->size;i++){
        if(i==con_index){
            
            con->array[i]=condition;
        }else{
            
            con->array[i]="*";
        }
    }
    LinkedList selections=Relation_lookup(con, relation);
    LinkedListIterator i=LinkedList_iterator(selections);
    while(LinkedListIterator_hasNext(i)){
        Tuple result=LinkedListIterator_next(i);
        Relation_insert(result, selection);
        
    }
    
    free(i);
    
    
    return selection;
}

//conditions implemented as linked list incase of several conditions (it may not always be one element)
Relation Relation_projection(Relation relation,LinkedList conditions){
    Tuple schema_= Tuple_new();
    Relation_Tuple_setSize(LinkedList_getsize(conditions), schema_);
    LinkedListIterator i=LinkedList_iterator(conditions);
    int count=0;
    while(LinkedListIterator_hasNext(i)){
        
        char* condition=LinkedListIterator_next(i);
        schema_->array[count]=condition;
        count++;
    }
    free(i);
    
    
    Relation project=Relation_new();
    project->schema=schema_;
    project->key=0;
    project->column_size=schema_->size;
    
    int indexes[schema_->size];
    for(int i=0;i<schema_->size;i++){
        for(int j=0;j<relation->column_size;j++){
            if(strcmp(relation->schema->array[j], schema_->array[i])==0){
                indexes[i]=j;
                
            }
        }
        
    }
    
    
    for(int i=0;i<19;i++){
        LinkedListIterator it=LinkedList_iterator(relation->hashTable[i]);
        
        while(LinkedListIterator_hasNext(it)){
            Tuple temp=LinkedListIterator_next(it);
            
            
            Tuple project_tuple=Tuple_new();
            Relation_Tuple_setSize(schema_->size, project_tuple);
            
            for(int j=0;j<schema_->size;j++){
                
                
                project_tuple->array[j]=temp->array[indexes[j]];
                
            }
            Relation_insert(project_tuple, project);
        }free(it);
        
        
        
    }
    return project;
}




Relation Relation_join(Relation relation1,Relation relation2,char * condition){
    Relation join=Relation_new();
    join->column_size=(relation1->column_size+relation2->column_size)-1;
    join->key=0;
    Tuple schema=Tuple_new();
    Relation_Tuple_setSize(join->column_size, schema);
    schema->array[0]=condition;
    int cur_index=1;
    int condition_index1=0;
    int condition_index2=0;
    for(int i=0; i<relation1->schema->size;i++){
        if(strcmp(relation1->schema->array[i], condition)!=0){
            schema->array[cur_index]=relation1->schema->array[i];
            cur_index++;
        }else{
            condition_index1=i;
        }
    }
    for(int i=0; i<relation2->schema->size;i++){
        if(strcmp(relation2->schema->array[i], condition)!=0){
            schema->array[cur_index]=relation2->schema->array[i];
            cur_index++;
        }else{
            condition_index2=i;
        }
    }
    join->schema=schema;
    
    
    
    
    
    for(int i=0;i<19;i++){
        LinkedListIterator it=LinkedList_iterator(relation1->hashTable[i]);
        
        while(LinkedListIterator_hasNext(it)){
            Tuple temp=LinkedListIterator_next(it);
            for(int j=0;j<19;j++){
                
                LinkedListIterator itt=LinkedList_iterator(relation2->hashTable[j]);
                while(LinkedListIterator_hasNext(itt)){
                    Tuple temp2=LinkedListIterator_next(itt);
                    if(strcmp(temp->array[condition_index1], temp2->array[condition_index2])==0){
                        Tuple joined=Tuple_new();
                        Relation_Tuple_setSize(join->column_size, joined);
                        joined->array[0]=temp->array[condition_index1];
                        int joined_index=1;
                        
                        for(int i=0; i<relation1->schema->size;i++){
                            if(i!=condition_index1){
                                joined->array[joined_index]=temp->array[i];
                                joined_index++;
                            }
                        }
                        for(int i=0; i<relation2->schema->size;i++){
                            if(i!=condition_index2){
                                joined->array[joined_index]=temp2->array[i];
                                joined_index++;
                            }
                        }
                        
                        Relation_insert(joined, join);
                    }
                    
                    
                }free(itt);
            }
        }
        free(it);
    }
    
    
    
    return join;
}
