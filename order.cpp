#include <iostream>
#include <iomanip>
#include <cstring>
#include <cstdio>
#include "order.h"
#include "output.h"
#include "input.h"

using namespace std;

int num_orders = 0; // Количество заказов
static int order_index = 0; // Уникальный идентификатор заказа

// Меню для управления заказами
void menu_orders(int *opt, Client *list_clients, Book *list_books, Order *list_orders) {
    do {
        cout << "\n--- ORDER MANAGEMENT ---\n";
        cout << "[1] Insert Order\n";
        cout << "[2] Print Orders\n";
        cout << "[3] Delete Order\n";
        cout << "[4] Exit to Main Menu\n";
        cout << "Choose an option: ";
        cin >> *opt;

        switch (*opt) {
            case 1:
                insert_order(&list_orders[get_num_orders()], list_clients, list_books);
                sort_orders_by_code(list_orders);
                print_orders_file(list_orders);
                break;
            case 2:
                read_file_order("order.txt", list_orders, list_clients, list_books);
                sort_orders_by_code(list_orders);
                clean_file("order.txt");
                print_orders_file(list_orders);
                read_file_order("order.txt", list_orders, list_clients, list_books);
                print_list_orders(list_orders, num_orders);
                break;
            case 3: {
                delete_order(list_orders);
                clean_file("order.txt");
                print_list_orders(list_orders, num_orders);
                break;
            }
            case 4:
                cout << "Exiting to Main Menu...\n";
                break;
            default:
                cout << "Invalid option. Try again.\n";
        }
    } while (*opt != 4);
}

// Вставка нового заказа
void insert_order(Order *ord, Client *list_clients, Book *list_books) {
    char client_name[50];
    int client_index;

    cout << "\n--- INSERT NEW ORDER ---\n";
    order_index++;
    ord->code = order_index;

    //cout << "Enter Client Name: ";
    //cin >> client_name;
    client_index = search_client(client_name, list_clients);

    if (client_index == -1) {
        cout << "Client not found.\n";
        return;
    }
    ord->client = get_client(client_index, list_clients);

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

        cout << "Add another detail? (y/n): ";
        cin >> cont;
    } while (cont == 'y' || cont == 'Y');

    num_orders++;

    cout << "Order inserted successfully.\n";
}

// Вставка новой детали заказа
void insert_order_detail(OrderDetail *detail, Book *list_books) {
    char book_title[40];
    int book_index;

    cout << "\n--- INSERT ORDER DETAIL ---\n";
    //cout << "Enter Book Title: ";
    //cin >> book_title;

    book_index = search_book(book_title, list_books);
    if (book_index == -1) {
        cout << "Book not found.\n";
        return;
    }
    detail->book = get_book(book_index, list_books);

    do {
        cout << "Enter Quantity: ";
        cin >> detail->quantity;
        if (detail->quantity > detail->book.stock) {
            cout << "Not enough stock available. Try again.\n";
        }
    } while (detail->quantity > detail->book.stock);

    detail->subtotal = detail->quantity * detail->book.price;
    detail->book.stock -= detail->quantity;

    // Уменьшение запаса книги
    list_books[book_index].stock -= detail->quantity;

    cout << "Order detail added successfully.\n";
}

// Печать списка всех заказов
void print_list_orders(const Order *list_orders, int num_orders) {
    cout << "\n--- LIST OF ORDERS ---\n";
    for (int i = 0; i < num_orders; i++) {
        print_order(list_orders[i]);
    }
}

// Печать одного заказа
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

// Удаление заказа
void delete_order(Order *list_orders) {
    int ind;

    ind = search_order(list_orders);
    if (ind != -1)
    {
        for (int i = ind; i < get_num_orders() - 1; i++) {
            list_orders[i] = list_orders[i + 1];
        }
        num_orders--;
        cout << "Order deleted successfully.\n";
    }
    else {cout<< "Order not found!" <<endl;};
}

// Поиск заказа по коду
int search_order(Order *list_orders) {
    int ind;
    cout<< "Enter code of Order: ";
    cin>>ind;
    for (int i = 0; i < num_orders; i++) {
        if (list_orders[i].code == ind) {
            return i;
        }
    }
    return -1;
}

// Получение количества заказов
int get_num_orders() {
    return num_orders;
}

void sort_orders_by_code(struct Order *list_orders)
{
    struct Order temp;

    for (int i = 0; i < get_num_orders() - 1; i++)
    {
        for (int j = i + 1; j < get_num_orders(); j++)
        {
            if (list_orders[i].code > list_orders[j].code)
            {
                temp = list_orders[i];
                list_orders[i] = list_orders[j];
                list_orders[j] = temp;
            }
            else if (list_orders[i].code == list_orders[j].code)
            {
                (list_orders[j].code)++;
            };
        };
    };
};
