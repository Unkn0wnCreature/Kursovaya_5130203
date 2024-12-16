#include <iostream>
#include <iomanip>
#include <cstring>
#include <cstdio>
#include "order.h"
#include "book.h"
#include "client.h"
using namespace std;

int num_orders = 0;
static int index = 0;

void menu_orders(int *opt, Client *list_clients, Book *list_books, Order *list_orders) {
    do {
        cout << "\n--- ORDER MANAGEMENT ---\n";
        cout << "[1] Insert Order\n";
        cout << "[2] Print Orders\n";
        cout << "[3] Exit to Main Menu\n";
        cout << "Choose an option: ";
        cin >> *opt;

        switch (*opt) {
            case 1:
                insert_order(&list_orders[get_num_orders()], list_clients, list_books);
                break;
            case 2:
                print_list_orders(list_orders);
                break;
            case 3:
                cout << "Exiting to Main Menu...\n";
                break;
            default:
                cout << "Invalid option. Try again.\n";
        }
    } while (*opt != 3);
}

void insert_order(Order *ord, Client *list_clients, Book *list_books) {
    char client_name[50];
    int client_pos;

    cout << "\n--- INSERT NEW ORDER ---\n";
    index++;
    ord->code = index;

    cout << "Enter Client Name: ";
    cin >> client_name;
    client_pos = search_client(client_name, list_clients);

    if (client_pos == -1) {
        cout << "Client not found.\n";
        return;
    }
    ord->client = get_client(client_pos, list_clients);

    char cont;
    do {
        if (ord->num_details < MAX_DETAILS) {
            insert_order_detail(&ord->details[ord->num_details], list_books);
            ord->total += ord->details[ord->num_details].subtotal;
            ord->num_details++;
        } else {
            cout << "Maximum order details reached.\n";
            break;
        }

        cout << "Add another order detail? (y/n): ";
        cin >> cont;
    } while (cont == 'y' || cont == 'Y');

    ord->client.salary -= ord->total;
    num_orders++;
}

void insert_order_detail(OrderDetail *od, Book *list_books) {
    char book_title[40];
    int book_pos;

    cout << "\n--- INSERT ORDER DETAIL ---\n";
    cout << "Enter Book Title: ";
    cin >> book_title;
    book_pos = search_book(book_title, list_books);

    if (book_pos == -1) {
        cout << "Book not found.\n";
        return;
    }
    od->book = get_book(book_pos, list_books);

    do {
        cout << "Enter Quantity: ";
        cin >> od->quantity;
        if (od->quantity > od->book.stock) {
            cout << "Not enough stock available. Try again.\n";
        }
    } while (od->quantity > od->book.stock);

    od->subtotal = od->quantity * od->book.price;
    od->book.stock -= od->quantity;
}

void print_list_orders(Order *list_orders) {
    cout << "\n--- LIST OF ORDERS ---\n";
    for (int i = 0; i < get_num_orders(); i++) {
        print_order(list_orders[i]);
    }
}

void print_order(const Order &ord) {
    cout << "Order ID: " << ord.code << endl;
    cout << "Client: " << ord.client.name << endl;
    cout << "---------------------------------------------\n";
    cout << left << setw(5) << "Item" << setw(20) << "Book Title"
         << setw(10) << "Quantity" << setw(10) << "Subtotal\n";
    cout << "---------------------------------------------\n";

    for (int i = 0; i < ord.num_details; i++) {
        cout << setw(5) << i + 1
             << setw(20) << ord.details[i].book.title
             << setw(10) << ord.details[i].quantity
             << setw(10) << ord.details[i].subtotal << endl;
    }
    cout << "Total: " << ord.total << "\n\n";
}

int get_num_orders() {
    return num_orders;
}
