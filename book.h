#pragma once

struct Book
{
    int code;
    char author[40];
    char title[40];
    int stock;
    double price;
    int year;
    int category;
    enum Category {FANTASY, FANTASTIC, ROMAN, HISTORY};
};

void menu_books(int *opt, struct Book *list_books);
void insert_book(struct Book *b);
int get_num_books();
int search_book(char *search_title, struct Book *list_books);
struct Book get_book(int pos, struct Book *list_books);
struct Book default_book();
void print_book(struct Book b);
void print_list_books(struct Book *list_books);
void update_book(char *search_title, struct Book *list_books);
void delete_book(char *search_title, struct Book *list_books);
void sort_by_author(struct Book *list_books);
void sort_by_title(struct Book *list_books);
void sort_by_price(struct Book *list_books);
void sort_by_year(struct Book *list_books);
void sort_by_category(struct Book *list_books);
void sort_books(struct Book *list_books);
void search_by_author(struct Book *list_books);
void search_by_title(struct Book *list_books);
void search_by_price(struct Book *list_books);
void search_by_year(struct Book *list_books);
void search_by_category(struct Book *list_books);
void search_books(struct Book *list_books);
int search_book_by_title(char *book_title, struct Book *list_books);
void sort_books_by_code(struct Book *list_books);