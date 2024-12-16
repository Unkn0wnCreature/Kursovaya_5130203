#pragma once
#include "client.h"
#include "book.h"
#include "order.h"


void read_file_client(char file_name[30], struct Client *list_clients);
void print_client_console();

void read_file_book(const char file_name[30], struct Book *list_books);

void read_file_order(const char file_name[30], struct Order *list_orders, struct Client *list_clients, struct Book *list_books);
