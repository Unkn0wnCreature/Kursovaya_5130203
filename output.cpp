#include <iostream>
#include <cstdio>
#include <string.h>
using namespace std;

#include "client.h"
#include "book.h"

void print_file_client(const char file_name[30], struct Client c)
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

void clean_file(const char file_name[30])
{
    FILE *file;
    char file_path[100];

    strcpy(file_path, "data/");
    strcat(file_path, file_name);

    file = fopen(file_path, "w");
    fclose(file);
};

void print_num_clients(const char file_name[30], int num_cl)
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


void print_file_book(const char file_name[30], struct Book b)
{
    FILE *file;
    char file_path[100];

    strcpy(file_path, "data/");
    strcat(file_path, file_name);

    file = fopen(file_path, "a");

    if (file)
    {   
        fprintf(file, "%d %s %s %d %lf %d %d\n", b.code, b.author, b.title, b.stock,
        b.price, b.year, b.category);
    }
    else {cout<< "Error to open file\n" << endl;};

    fclose(file);
}

void print_num_books(const char file_name[30], int num_books)
{
    FILE *file;
    char file_path[100];

    strcpy(file_path, "data/");
    strcat(file_path, file_name);

    file = fopen(file_path, "w");

    if (file) {fprintf(file, "%d\n", num_books);}
    else {cout<< "Error to open file\n" << endl;};

    fclose(file);
}

void print_books_file(struct Book *list_books)
{
    clean_file("book.txt");

    print_num_books("book.txt", get_num_books());
    
    for (int i = 0; i < get_num_books(); i++)
    {
        print_file_book("book.txt", list_books[i]);
    };
}