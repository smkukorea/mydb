
#include "Database.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

Database new_Database(void){
    Database db=(Database)malloc(sizeof(struct Database));
    db->relations=new_LinkedList();
    return db;
}

void DB_free(Database db){
    if(db==NULL){
        return;
    }
    int size=LinkedList_getsize(db->relations);
    for(int i=0;i<size;i++){
        Relation r=LinkedList_elementAt(db->relations, i);
        Relation_free(r);
    }
    
    
    LinkedList_free(db->relations, true);
    
    
}

int numRelation(LinkedList relations){
    int size=0;
    LinkedList k=relations;
    
            LinkedListIterator b= LinkedList_iterator(k);
                        
             while(LinkedListIterator_hasNext(b)){
                 LinkedListIterator_next(b);
                 size++;
             }
    return size;
}

 void outputFile(Database database, char* filename){

    FILE * file=NULL;
    file=fopen(filename, "r");
    if(file==NULL){
        file=fopen(filename, "w+");
    }else{
        remove(filename);
        file=fopen(filename, "w+");
    }
    
     int numRelations=numRelation(database->relations);
     
    fprintf(file,"Num of Relations\n%d\n",numRelations);//Number of relations
    for(int i=0; i<numRelations;i++){//write a relation
        fprintf(file,"\n");
        
        Relation r= LinkedList_elementAt(database->relations, i);
        fprintf(file, "%s\n",r->name);
        fprintf(file,"Primary Key\n");
        fprintf(file, "%d\n",r->key);
        fprintf(file,"Num of tuples\n");
        fprintf(file, "%d\n",r->num_tuples/2);
        for(int k=0; k<r->schema->size;k++){//write the schema
            fprintf(file, "%s",r->schema->array[k]);
            if(k!=r->schema->size-1) fprintf(file, ";"); else fprintf(file, "\n");
            
        }
          fprintf(file, "%d\n",r->schema->size);
       
        
        for(int i=0;i<19;i++){
        LinkedListIterator l=LinkedList_iterator(r->hashTable[i]);
        while(LinkedListIterator_hasNext(l)){
            Tuple temp = LinkedListIterator_next(l);
          for(int l=0; l<r->schema->size; l++){//write a tuple
                         fprintf(file, "%s",temp->array[l]);
                         if(l!=r->schema->size-1) fprintf(file, ";"); else fprintf(file, "\n");
                     }
        }
            free(l);
        }
        
        
    }
    fclose(file);
}



 int stringToInt(char* string){
     int result=0;
     long length=strlen(string);
        for(int i=0; i<length;i++){
            result=result*10+(string[i]-'0');
        }
        return result;
}

 Tuple stringToTuple(char* tuple){
     Tuple result=Tuple_new();
     char *token = strtok(tuple, ";");
     int i=0;
    while (token != NULL)
    {
         
        result->array[i]=token;
        
        token = strtok(NULL, ";");
       
        i++;
         Relation_Tuple_setSize(i, result);
    }
    return result;
}
 void removeNewLine2(char* i){
    long length=strlen(i);
       if(i[length-1]=='\n'){
           i[length-1]='\0';
       }
}

 char* removeNewLine(char* i){
    long length=strlen(i);
    if(i[length-1]=='\n'){
        i[length-1]='\0';
    }
    return i;
}

 char* readLine(FILE * file){
    char line[256];
    char* output=removeNewLine(fgets(line, sizeof(line), file));
    char * copy = malloc(strlen(output) + 1);
    strcpy(copy, output);
    if(copy==NULL) return readLine(file);
    return copy;
    
}

void DB_print(Database db){
     LinkedList k=db->relations;
         LinkedListIterator b= LinkedList_iterator(k);
                     
          while(LinkedListIterator_hasNext(b)){
            Relation ab = LinkedListIterator_next(b);
              Relation_print(ab);
              
          }
}

Database readFile(char* filename){
    Database db=new_Database();
    FILE* file;
    file=fopen(filename, "r");
    if(file==NULL){
        printf("File not found\n");
    }else{
   
        //IGNORE TITLE
    readLine(file);
        //NUMBER OF RELATIONS
        char* tmp=readLine(file);
        int numRelation=stringToInt(tmp);
        
        for( int i=0; i<numRelation;i++){//create a relation
            Relation tmp=Relation_new();
            //IGNORE SPACE
            readLine(file);
            //NAME
            tmp->name=readLine(file);
  
           
            readLine(file);
         
            tmp->key=stringToInt(readLine(file));
            
        
            readLine(file);

            int numofTuple=stringToInt(readLine(file));
            tmp->num_tuples=numofTuple;
             
          
            char* schema=readLine(file);
            tmp->schema=stringToTuple(schema);
            
          
            tmp->schema->size=stringToInt(readLine(file));
                     
            tmp->column_size = tmp->schema->size;
            Relation_setRelation(tmp->key, tmp->schema, tmp->name, tmp);
            
            //INSERT TUPLES
            for( int j=0; j<numofTuple; j++){//create a tuple
                char* tuple=readLine(file);
                
                Tuple t=stringToTuple(tuple);
                Relation_Tuple_setSize(tmp->column_size, t);
            Relation_insert(t, tmp);
            }
    
            
            LinkedList_add_at_end(db->relations, tmp);
            
        }
    }
    fclose(file);
    return db;
    
}


