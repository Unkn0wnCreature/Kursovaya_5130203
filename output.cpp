#include <iostream>
#include <cstdio>
#include <string.h>
using namespace std;

#include "client.h"
#include "book.h"
#include "order.h"

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
    print_num_books("book.txt", get_num_books());
    
    for (int i = 0; i < get_num_books(); i++)
    {
        print_file_book("book.txt", list_books[i]);
    };
}

// Функция для записи отдельного заказа в файл
void print_file_order(const char file_name[30], struct Order o)
{
    FILE *file;
    char file_path[100];

    strcpy(file_path, "data/");
    strcat(file_path, file_name);

    file = fopen(file_path, "a");

    if (file)
    {
        fprintf(file, "%d %d %d %.2f\n", o.code, o.client.code, o.num_details, o.total);

        // Сохранение всех деталей заказа
        for (int i = 0; i < o.num_details; i++) {
            fprintf(file, "  %s %d %.2f\n",
                    o.details[i].book.title,
                    o.details[i].quantity,
                    o.details[i].subtotal);
        }
    }
    else {
        cout << "Error: Could not open file " << file_name << "\n";
    }

    fclose(file);
}

// Функция для записи общего количества заказов
void print_num_orders(const char file_name[30], int num_orders)
{
    FILE *file;
    char file_path[100];

    strcpy(file_path, "data/");
    strcat(file_path, file_name);

    file = fopen(file_path, "w");

    if (file) {
        fprintf(file, "%d\n", num_orders);
    }
    else {
        cout << "Error: Could not open file " << file_name << "\n";
    }

    fclose(file);
}

// Функция для записи всех заказов в файл
void print_orders_file(struct Order *list_orders)
{
    print_num_orders("order.txt", get_num_orders());

    for (int i = 0; i < get_num_orders(); i++)
    {
        print_file_order("order.txt", list_orders[i]);
    }
}
