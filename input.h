#pragma once
#include "client.h"
#include "book.h"

void read_file_client(const char file_name[30], struct Client *list_clients);
void print_client_console();

void read_file_book(const char file_name[30], struct Book *list_books);