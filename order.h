#pragma once
#include "client.h"
#include "book.h"

#define MAX_DETAILS 10

struct OrderDetail {
    Book book;
    int quantity;
    double subtotal;
};

struct Order {
    int code;
    Client client;
    OrderDetail details[MAX_DETAILS];
    int num_details = 0;
    double total = 0.0;
};

void menu_orders(int *opt, Client *list_clients, Book *list_books, Order *list_orders);
void insert_order(Order *ord, Client *list_clients, Book *list_books);
void insert_order_detail(OrderDetail *od, Book *list_books);
void print_list_orders(Order *list_orders);
void print_order(const Order &ord);
int get_num_orders();
