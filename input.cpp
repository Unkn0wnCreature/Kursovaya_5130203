#include <iostream>
#include <cstdio>
#include <iomanip>
#include <string.h>
using namespace std;

#include "client.h"
#include "book.h"
#include "order.h"


void read_file_client(char file_name[30], struct Client *list_clients)
{
    FILE *file;
    char file_path[100];
    extern int num_clients;

    strcpy(file_path, "data/");
    strcat(file_path, file_name);

    file = fopen(file_path, "r");

    if (file)
    {   
        fscanf(file, "%d\n", &(num_clients));
        
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
    extern int num_books;

    strcpy(file_path, "data/");
    strcat(file_path, file_name);

    file = fopen(file_path, "r");

    if (file)
    {   
        fscanf(file, "%d\n", &(num_books));
        
        for (int i = 0; i < num_books; i++)
        {
            fscanf(file, "%d %s %s %d %lf %d %d\n", &(list_books[i].code), &(list_books[i].author), &(list_books[i].title),
            &(list_books[i].stock), &(list_books[i].price), &(list_books[i].year), &(list_books[i].category));
        }
    }
    else {cout<< "Error to open file\n" << endl;};

    fclose(file);
};

void read_file_order(const char file_name[30], struct Order *list_orders, struct Client *list_clients, struct Book *list_books) {
    FILE *file;
    char file_path[100];
    extern int num_orders;

    strcpy(file_path, "data/");
    strcat(file_path, file_name);

    file = fopen(file_path, "r");
    if (!file) {
        cout << "Error: Could not open file " << file_name << "\n";
        return;
    }

    // Считываем общее количество заказов
    if (fscanf(file, "%d\n", &num_orders) != 1) {
        cout << "Error: Could not read number of orders from file.\n";
        fclose(file);
        return;
    }

    // Считываем каждый заказ
    for (int i = 0; i < num_orders; i++) {
        int client_code, num_details;
        if (fscanf(file, "%d %d %d %lf\n", &(list_orders[i].code), &client_code, &num_details, &(list_orders[i].total)) != 4) {
            cout << "Error: Could not read order details for order " << (i + 1) << ".\n";
            fclose(file);
            return;
        }

        // Ищем клиента по коду
        int client_index = search_client_by_code(client_code, list_clients);
        if (client_index != -1) {
            list_orders[i].client = list_clients[client_index];
        } else {
            cout << "Warning: Client with code " << client_code << " not found.\n";
        }

        // Считываем детали заказа
        list_orders[i].num_details = num_details;
        for (int j = 0; j < num_details; j++) {
            char book_title[40];
            int quantity;
            double subtotal;

            if (fscanf(file, " %39s %d %lf\n", book_title, &quantity, &subtotal) != 3) {
                cout << "Error: Could not read order detail " << (j + 1) << " for order " << (i + 1) << ".\n";
                fclose(file);
                return;
            }

            // Ищем книгу по названию
            int book_index = search_book(book_title, list_books);
            if (book_index != -1) {
                list_orders[i].details[j].book = list_books[book_index];
                list_orders[i].details[j].quantity = quantity;
                list_orders[i].details[j].subtotal = subtotal;
            } else {
                cout << "Warning: Book with title \"" << book_title << "\" not found.\n";
            }
        }
    }

    fclose(file);
}
