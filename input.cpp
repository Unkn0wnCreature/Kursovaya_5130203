#include <iostream>
#include <cstdio>
#include <iomanip>
#include <string.h>
using namespace std;

#include "client.h"

void read_file_client(char file_name[30])
{
    FILE *file;
    char file_path[100];
    struct Client c;

    strcpy(file_path, "data/");
    strcat(file_path, file_name);

    file = fopen(file_path, "r");

    if (file)
    {   
        cout<< "\n" << setw(5) << "Code" << setw(10) << "Name" << setw(5) << "Age" << setw(10) << "Salary" <<endl;
        for (int i = 0; i < get_num_clients(); i++)
        {
            fscanf(file, "%d %s %d %lf\n", &(c.code), &(c.name), &(c.age), &(c.salary));
            cout<<left;
            cout<< setw(5) << c.code << setw(10) << c.name << setw(5) << c.age << setw(10) << c.salary <<endl;
        };
    }
    else {cout<< "Error to open file\n" << endl;};

    fclose(file);
};
