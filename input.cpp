#include <iostream>
#include <cstdio>
#include <iomanip>
#include <string.h>
using namespace std;

#include "client.h"

void read_file_client(char file_name[30], struct Client *list_clients)
{
    FILE *file;
    char file_path[100];
    //struct Client c;
    int num_cl;

    strcpy(file_path, "data/");
    strcat(file_path, file_name);

    file = fopen(file_path, "r");

    if (file)
    {   
        fscanf(file, "%d\n", &num_clients);
        
        for (int i = 0; i < num_clients; i++)
        {
            fscanf(file, "%d %s %d %lf\n", &(list_clients[i].code), &(list_clients[i].name), &(list_clients[i].age), &(list_clients[i].salary));
        };
    }
    else {cout<< "Error to open file\n" << endl;};

    fclose(file);
};
