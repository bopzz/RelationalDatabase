#include "Database.h"
#include "ReadWriteDB.h"
#include "RelationalAlgebra.h"

void part_1()
{
    printf("Importing necessary databases for part 1...\n");

    TABLE P1_CSG = {NULL};
    read("CSG.txt", P1_CSG);

    TABLE P1_CP = {NULL};
    read("CP.txt", P1_CP);

    TABLE P1_CDH = {NULL};
    read("CDH.txt", P1_CDH);

    printf("a) lookup(<\"CSC172\", 98789, *>, Course-StudentId-Grade)\n");
    char *p4_a[3] = {"CSC172", "98789", ""};
    TUPLELIST a = create_new_tuple(p4_a, 1, 3);
    printf("Result (if exists): \n");
    lookup(a, P1_CSG);
    printf("\n");

    printf("b) lookup(<\"CSC173\", \"CSC172\">, Course-Prerequisite)\n");
    char *p4_b[2] = {"CSC173", "CSC172"};
    TUPLELIST b = create_new_tuple(p4_b, 1, 2);
    printf("Result (if exists): \n");
    lookup(b, P1_CP);
    printf("\n");

    printf("c) delete(<\"DSCC201\", *, *>, Course-Day-Hour)\n");
    char *p4_c[3] = {"DSCC201", "", ""};
    TUPLELIST c = create_new_tuple(p4_c, 1, 3);
    delete_tuple(c, P1_CDH);
    printf("\nNew table\n");
    print_table(P1_CDH);
    printf("\n");

    printf("d) insert(<\"CSC280\", \"CSC173\">, Course-Prerequisite)\n");
    char *p4_d[2] = {"CSC280", "CSC173"};
    TUPLELIST d = create_new_tuple(p4_d, 1, 2);
    insert(d, P1_CP);
    printf("\nNew table\n");
    print_table(P1_CP);
    printf("\n");

    printf("e) insert(<\"DSCC202\", \"DSCC201\">, Course-Prerequisite)\n");
    char *p4_e[2] = {"DSCC202", "DSCC201"};
    TUPLELIST e = create_new_tuple(p4_e, 1, 2);
    insert(e, P1_CP);
    printf("\nNew table\n");
    print_table(P1_CP);
    printf("\n\n");

    // free_tuple(a);
    // free_tuple(b);
    // free_tuple(c);
    // free_tuple(d);
    // free_tuple(e);
    // free_table(P1_CSG);
    // free_table(P1_CDH);
    // free_table(P1_CP);
}

void part_2_1(char *name, char *course, TABLE CSG, TABLE SNAP)
{
    bool isFound = false;
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        TUPLELIST tuple = SNAP[i];
        while (tuple != NULL)
        {
            if (strcmp(tuple->data[1], name) == 0)
            {
                char *id = tuple->data[0];
                for (int j = 0; j < TABLE_SIZE; j++)
                {
                    TUPLELIST tuple2 = CSG[j];
                    while (tuple2 != NULL)
                    {
                        if (strcmp(tuple2->data[0], course) == 0 && strcmp(tuple2->data[1], id) == 0)
                        {
                            printf("%s got %s for %s.\n\n", name, tuple2->data[2], course);
                            isFound = true;
                        }
                        tuple2 = tuple2->next;
                    }
                }
            }
            tuple = tuple->next;
        }
    }
    if (!isFound)
    {
        printf("Can't find that information.\n\n");
    }
}

void part_2_2(char *name, char *hour, char *day, TABLE SNAP, TABLE CSG, TABLE CDH, TABLE CR)
{
    bool isFound = false;
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        TUPLELIST tuple = SNAP[i];
        while (tuple != NULL)
        {
            if (strcmp(tuple->data[1], name) == 0)
            {
                char *id = tuple->data[0];
                for (int j = 0; j < TABLE_SIZE; j++)
                {
                    TUPLELIST tuple2 = CSG[j];
                    while (tuple2 != NULL)
                    {
                        if (strcmp(tuple2->data[1], id) == 0)
                        {
                            char *course = tuple2->data[0];
                            for (int m = 0; m < TABLE_SIZE; m++)
                            {
                                TUPLELIST tuple3 = CDH[m];
                                while (tuple3 != NULL)
                                {
                                    if (strcmp(tuple3->data[0], course) == 0 && strcmp(tuple3->data[1], day) == 0 && strcmp(tuple3->data[2], hour) == 0)
                                    {
                                        char *confirmed_course = tuple3->data[0];
                                        for (int n = 0; n < TABLE_SIZE; n++)
                                        {
                                            TUPLELIST tuple4 = CR[n];
                                            while (tuple4 != NULL)
                                            {
                                                if (strcmp(tuple4->data[0], confirmed_course) == 0)
                                                {
                                                    printf("%s is at %s at %s on %s.\n\n", name, tuple4->data[1], hour, day);
                                                    return;
                                                }
                                                tuple4 = tuple4->next;
                                            }
                                        }
                                    }
                                    tuple3 = tuple3->next;
                                }
                            }
                        }
                        tuple2 = tuple2->next;
                    }
                }
            }
            tuple = tuple->next;
        }
    }
    if (!isFound)
    {
        printf("Can't find that information.\n\n");
    }
}

void part_3(TABLE CSG, TABLE CR, TABLE CDH){
    printf("1) Selection\n");
    TABLE p3_1 = {NULL};
    char* category[1] = {"StudentId"};
    char* data[1] = {"67890"};
    selection(category, data, 1, CSG, p3_1);
    print_table(p3_1);
    
    printf("\n2) Projection\n");
    TABLE p3_2 = {NULL};
    int category_1[1] = {1};
    projection(category_1, 1, p3_1, p3_2);
    print_table(p3_2);

    printf("\n3) Join\n");
    TABLE p3_3 = {NULL};
    join(1, 1, CR, CDH, p3_3);
    print_table(p3_3);

    printf("\n4) All of the above\n");
    TABLE p4_1 = {NULL};
    char* category_2[1] = {"Room"};
    char* data_2[1] = {"Wegmans 1400"};
    selection(category_2, data_2, 1, p3_3, p4_1);
    TABLE p4_2 = {NULL};
    int category_3[2] = {3,4};
    projection(category_3, 2, p4_1, p4_2);
    print_table(p4_2);

    free_table(p3_1);
    free_table(p3_2);
    free_table(p3_3);
    free_table(p4_1);
    free_table(p4_2);
}

int main()
{
    printf("Loading every database...\n\n");
    TABLE CSG = {NULL};
    read("CSG.txt", CSG);
    TABLE SNAP = {NULL};
    read("SNAP.txt", SNAP);
    TABLE CDH = {NULL};
    read("CDH.txt", CDH);
    TABLE CP = {NULL};
    read("CP.txt", CP);
    TABLE CR = {NULL};
    read("CR.txt", CR);

    printf("Part 1:\n\n");
    part_1();

    printf("Part 2:\n\n");
    printf("2.1: What grade did Name get in Course?\n");
    while (true)
    {
        char name[50];
        char course[50];
        printf("Enter \"quit\" to quit\n");
        printf("Enter name: ");
        fgets(name, 50, stdin);
        if (strcmp(name, "quit\n") == 0)
        {
            break;
        }
        char *final_name = strtok(name, "\n");
        // printf("Name is %s\n", strtok(name, "\n"));

        printf("Enter course: ");
        fgets(course, 50, stdin);
        if (strcmp(course, "quit\n") == 0)
        {
            break;
        }
        char *final_course = strtok(course, "\n");
        // printf("Course is %s\n", strtok(course, "\n"));

        printf("\n");
        part_2_1(final_name, final_course, CSG, SNAP);
    }

    printf("\n\n2.2: Where is Name at Hour on Day?\n");
    while (true)
    {
        char name[50];
        char hour[50];
        char day[50];
        printf("Enter \"quit\" to quit\n");
        printf("Enter name: ");
        fgets(name, 50, stdin);
        if (strcmp(name, "quit\n") == 0)
        {
            break;
        }
        char *final_name = strtok(name, "\n");

        printf("Enter hour: ");
        fgets(hour, 50, stdin);
        if (strcmp(hour, "quit\n") == 0)
        {
            break;
        }
        char *final_hour = strtok(hour, "\n");

        printf("Enter day: ");
        fgets(day, 50, stdin);
        if (strcmp(day, "quit\n") == 0)
        {
            break;
        }
        char *final_day = strtok(day, "\n");

        printf("\n");
        part_2_2(final_name, final_hour, final_day, SNAP, CSG, CDH, CR);
    }

    printf("\n\nPart 3\n\n");
    part_3(CSG, CR, CDH);

    printf("\n\nExtra Credit\n\n");
    printf("Demonstrating on CSG database...\n");
    printf("Reading CSG...\n");
    TABLE CSG_test = {NULL};
    read("CSG.txt", CSG_test);

    printf("Writing database to CSG_2.txt...\n");
    write("CSG_2.txt", CSG_test);

    free_table(CSG);
    free_table(SNAP);
    free_table(CDH);
    free_table(CP);
    free_table(CR);
    free_table(CSG_test);
}