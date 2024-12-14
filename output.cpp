#include <iostream>
#include <cstdio>
#include <string.h>
using namespace std;

#include "client.h"

void print_file_client(char file_name[30], struct Client c)
{
    FILE *file;
    char file_path[100];

    strcpy(file_path, "data/");
    strcat(file_path, file_name);

    file = fopen(file_path, "a");

    if (file)
    {   
        fprintf(file, "%d %s %d %f\n", c.code, c.name, c.age, c.salary);
    }
    else {cout<< "Error to open file\n" << endl;};

    fclose(file);
};

void clean_file(char file_name[30])
{
    FILE *file;
    char file_path[100];

    strcpy(file_path, "data/");
    strcat(file_path, file_name);

    file = fopen(file_path, "w");
    fclose(file);
};

void print_num_clients(char file_name[30], int num_cl)
{
    FILE *file;
    char file_path[100];

    strcpy(file_path, "data/");
    strcat(file_path, file_name);

    file = fopen(file_path, "w");

    if (file) {fprintf(file, "%d\n", num_cl);}
    else {cout<< "Error to open file\n" << endl;};

    fclose(file);
};

void print_clients_file(struct Client *list_clients)
{
    clean_file("client.txt");

    print_num_clients("client.txt", get_num_clients());
    
    for (int i = 0; i < get_num_clients(); i++)
    {
        print_file_client("client.txt", list_clients[i]);
    };
};