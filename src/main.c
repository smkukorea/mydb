//
//  main.c
//  RDB
//
//  Created by Seungmin Kuk on 09/11/2019.
//  Copyright © 2019 Seungmin Kuk. All rights reserved.
//

#include <stdio.h>
#include "Relation.h"
#include "Database.h"
#include "LinkedList.h"
int main(int argc, const char * argv[]) {
    // insert code here...
    
    
    
    Database db = readFile("Database.txt");
    
    printf("Part 1-1 and 1-4:\nInitial database loaded from saved file \n with all relations in FOCS Figure 8.1 and 8.2:\n");
    DB_print(db);
    
    //Part 1
    
    Tuple a=Tuple_new();
    Relation_Tuple_setSize(3, a);
    char* attributes_a[]={"CS101","12345","*"};
    Relation_Tuple_addElements(attributes_a, a);
    
    Relation CSG=LinkedList_elementAt(db->relations, 0);
    Relation_lookup_print(Relation_lookup(a, CSG),CSG,a);
    
    
    
    Tuple b=Tuple_new();
    Relation_Tuple_setSize(2, b);
    char* attributes_b[]={"CS205","CS120"};
    Relation_Tuple_addElements(attributes_b, b);
    
    Relation CP=LinkedList_elementAt(db->relations, 2);
    Relation_lookup_print(Relation_lookup(b, CP),CP,b);
    
    
    
    Tuple c=Tuple_new();
    Relation_Tuple_setSize(2, c);
    char* attributes_c[]={"CS101","*"};
    Relation_Tuple_addElements(attributes_c, c);
    
    Relation CR=LinkedList_elementAt(db->relations, 4);
    Relation_delete(c, CR);
    printf("\nResult of deltion on CR\n");
    Relation_print(CR);
    
    
    Tuple d=Tuple_new();
    Relation_Tuple_setSize(2, d);
    char* attributes_d[]={"CS205","CS120"};
    Relation_Tuple_addElements(attributes_d, d);
    Relation_insert(d, CP);
    printf("\nResult of insertion on CP 1\n");
    Relation_print(CP);
    
    Tuple e=Tuple_new();
    Relation_Tuple_setSize(2, e);
    char* attributes_e[]={"CS205","CS101"};
    Relation_Tuple_addElements(attributes_e, e);
    Relation_insert(e, CP);
    printf("\nResult of insertion on CP 2\n");
    Relation_print(CP);
    
    
    DB_free(db);
    
    db = readFile("Database.txt");
    //part2
    
    //1
    printf("Query: What Grade Did [StudentName] get in [CourseName] ?\n");
    char studentName[256];
    char courseName[256];
    
    do{
        printf("    -Please enter the student's name\n");
        fgets(studentName,255,stdin);
        removeNewLine2(studentName);
        printf("    -Please enter the course name (Enter 'quit' to quit query)\n");
        fgets(courseName,255,stdin);
        removeNewLine2(courseName);
        Relation csg = LinkedList_elementAt(db->relations, 0);
        Relation snap = LinkedList_elementAt(db->relations, 1);
        
        Relation_query_grade(snap, csg, studentName, courseName);
        
    } while((strcmp(studentName, "quit")!=0)&& (strcmp(courseName, "quit")!=0));
    
    //2
    
    
    printf("Query: Where is [StudentName] at [Time] on [Day]?...\n");
    
    char studentName2[256];
    char Time[256];
    char Day[256];
    
    do{
        printf("    -Please enter student's name\n");
        fgets(studentName2,255,stdin);
        removeNewLine2(studentName2);
        printf("    -Please enter Time\n");
        fgets(Time,255,stdin);
        removeNewLine2(Time);
        printf("    -Please enter Day (Enter 'quit' to quit query)\n");
        fgets(Day,255, stdin);
        removeNewLine2(Day);
        
        Relation csgPart3 = LinkedList_elementAt(db->relations, 0);
        Relation snapPart3 = LinkedList_elementAt(db->relations, 1);
        Relation cdhPart3 =LinkedList_elementAt(db->relations, 3);
        Relation crPart3 = LinkedList_elementAt(db->relations, 4);
        
        Relation_query_location(csgPart3, snapPart3, cdhPart3, crPart3, studentName2, Day, Time);
        
    } while((strcmp(studentName2, "quit")!=0 )&&(strcmp(Time, "quit")!=0 )
            &&  (strcmp(Day, "quit")!=0 ) );
    
    
    printf("\n Selection example using 8.12 \n");
    Relation select_example = LinkedList_elementAt(db->relations, 0);
    
    Relation select_output=Relation_selection(select_example, "CS101", "Course");
    Relation_print(select_output);
    
    
    
    
    printf("\n Projectioon example using 8.13 \n");
    LinkedList conditions=new_LinkedList();
    LinkedList_add_at_end(conditions, "Student");
    Relation project_output=Relation_projection(select_output, conditions);
    Relation_print(project_output);
    
    
    printf("\n Join example using 8.14 \n");
    Relation join1 = LinkedList_elementAt(db->relations, 4);
    Relation join2 = LinkedList_elementAt(db->relations, 3);
    char*condition="Course";
    Relation join_output=Relation_join(join1, join2, condition);
    Relation_print(join_output);
    
    
    printf("\n combined example using 8.15 \n");
    
    Relation combined1=Relation_selection(join_output, "Turing_Aud.", "Room");
    LinkedList combined_list=new_LinkedList();
    LinkedList_add_at_end(combined_list, "Day");
    LinkedList_add_at_end(combined_list, "Hour");
    Relation combined2=Relation_projection(combined1, combined_list);
    Relation_print(combined2);
   
    
    outputFile(db,"Database.txt");
  
    Relation_free(project_output);
  Relation_free(combined2);
    Relation_free(join_output);
    
   
    DB_free(db);
    
    printf("\n Generic implementation demo by using registration db with two new relations: \n");
    db = readFile("Database2.txt");
    printf("\n Initial database: \n");
    DB_print(db);
    
    printf("\n Lookup Demo1:");
    a=Tuple_new();
    Relation_Tuple_setSize(2, a);
    char* attributes_a2[]={"CS101","*"};
    Relation_Tuple_addElements(attributes_a2, a);
    
    Relation CD=LinkedList_elementAt(db->relations, 5);
    Relation_lookup_print(Relation_lookup(a, CD),CD,a);
    
    
    printf("\n Lookup Demo2: ");
    b=Tuple_new();
    Relation_Tuple_setSize(3, b);
    char* attributes_b2[]={"*","C.Brown","*"};
    Relation_Tuple_addElements(attributes_b2, b);
    
    Relation CNM=LinkedList_elementAt(db->relations, 6);
    Relation_lookup_print(Relation_lookup(b, CNM),CNM,b);
    
    c=Tuple_new();
    Relation_Tuple_setSize(2, c);
    char* attributes_c2[]={"CS101","Easy"};
    Relation_Tuple_addElements(attributes_c2, c);
    
    Relation_delete(c, CD);
    printf("\n Demo Result of deltion on CD\n");
    Relation_print(CD);
    
    
    
    Relation_insert(c, CD);
    printf("\n Demo Result of insertion on CD\n");
    Relation_print(CD);
    
    
    
    
    printf("\n Selection Demo \n");
    Relation demo = LinkedList_elementAt(db->relations, 5);
    
    Relation select_demo=Relation_selection(demo, "CS101", "Course");
    Relation_print(select_demo);
    
    
    printf("\n Projection Demo \n");
    
    Relation demo2 = LinkedList_elementAt(db->relations, 6);
    LinkedList conditions4=new_LinkedList();
    LinkedList_add_at_end(conditions4, "Major");
    
    Relation projection_demo=Relation_projection(demo2, conditions4);
    Relation_print(projection_demo);
    
    
    
    
    
    printf("\n Join Demo \n");
    Relation join1D = LinkedList_elementAt(db->relations, 0);
    Relation join2D = LinkedList_elementAt(db->relations, 6);
    char*conditionD="Student";
    Relation join_outputD=Relation_join(join1D, join2D, conditionD);
    Relation_print(join_outputD);
    

    Relation_free(projection_demo);
    Relation_free(join_outputD);
    
    DB_free(db);
    
    
    return 0;
}
