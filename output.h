#pragma once

void print_file_client(const char file_name[30], struct Client c);
void clean_file(const char file_name[30]);
void print_num_clients(const char file_name[30], int num_cl);
void print_clients_file(struct Client *list_clients);
//void sort_clients(struct Client *list_clients);
//void codes_clients(struct Client *list_clients);
void print_file_book(const char file_name[30], struct Book b);
void print_num_books(const char file_name[30], int num_books);
void print_books_file(struct Book *list_books);