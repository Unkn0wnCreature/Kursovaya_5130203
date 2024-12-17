#pragma once
#include "client.h"
#include "book.h"

#define MAX_DETAILS 10

// Структура для детали заказа
struct OrderDetail {
    Book book;          // Книга, связанная с заказом
    int quantity;       // Количество экземпляров
    double subtotal;    // Промежуточный итог = цена * количество
};

// Структура для заказа
struct Order {
    int code;                       // Уникальный код заказа
    Client client;                  // Клиент, связанный с заказом
    OrderDetail details[MAX_DETAILS]; // Массив деталей заказа
    int num_details = 0;            // Количество деталей в заказе
    double total = 0.0;             // Общая стоимость заказа
};

// Основные функции для управления заказами
void menu_orders(int *opt, Client *list_clients, Book *list_books, Order *list_orders);
void insert_order(Order *ord, Client *list_clients, Book *list_books);
void insert_order_detail(OrderDetail *detail, Book *list_books);
void print_list_orders(const Order *list_orders, int num_orders);
void print_order(const Order &ord);
void delete_order(Order *list_orders);
int get_num_orders();
int search_order(Order *list_orders);
void sort_orders_by_code(struct Order *list_orders);