#include <iostream>
#include <cstdio>
#include <iomanip>
#include <string.h>
using namespace std;

#include "client.h"
#include "book.h"

void read_file_client(const char file_name[30], struct Client *list_clients)
{
    FILE *file;
    char file_path[100];
    int num_clients;

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

void read_file_book(const char file_name[30], struct Book *list_books)
{
    FILE *file;
    char file_path[100];

    int num_books;

    strcpy(file_path, "data/");
    strcat(file_path, file_name);

    file = fopen(file_path, "r");

    if (file)
    {   
        fscanf(file, "%d\n", &num_books);
        
        for (int i = 0; i < num_books; i++)
        {
            fscanf(file, "%d %s %s %d %lf %d %d\n", &(list_books[i].code), &(list_books[i].author), &(list_books[i].title),
            &(list_books[i].stock), &(list_books[i].price), &(list_books[i].year), &(list_books[i].category));
        }
    }
    else {cout<< "Error to open file\n" << endl;};

    fclose(file);
};
