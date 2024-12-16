#include <iostream>
#include <cstring>
#include <iomanip>
#include <cstdio>
#include "book.h"
#include "input.h"
#include "output.h"
using namespace std;

int num_books = 0;
static int index_b = 0;

void menu_books(int *opt, struct Book *list_books)
{
    int pos;
    char search_title[40];
    struct Book b;

    do
    {
        cout << left;
        cout << setw(20) << "\n--- MANAGMENT OF BOOKS ---" << endl;
        cout << "[1]. Insert book" << endl;
        cout << "[2]. Read list of books" << endl;
        cout << "[3]. Update book" << endl;
        cout << "[4]. Delete book" << endl;
        cout << "[5]. Sort books" << endl;
        cout << "[6]. Search books" << endl;
        cout << "[7]. Exit" << endl;
        cout << "----------------------------------------------" << endl;
        cout << "Enter option: ";
        cin >> *opt;

        switch (*opt)
        {
            case 1: //insert
                insert_book(&list_books[get_num_books()]);
                print_books_file(list_books);
                break;
            case 2: //read and print
                read_file_book("book.txt", list_books);
                sort_books_by_code(list_books);
                clean_file("book.txt");
                print_books_file(list_books);
                read_file_book("book.txt", list_books);
                print_list_books(list_books);
                break;
            case 3: //update
                update_book(search_title, list_books);
                clean_file("book.txt");
                print_books_file(list_books);
                break;
            case 4: //delete
                delete_book(search_title, list_books);
                clean_file("book.txt");
                print_books_file(list_books);
                break;
            case 5: //sort
                sort_books(list_books);
                clean_file("book.txt");
                print_list_books(list_books);
                print_books_file(list_books);
                break;
            case 6: //search
                search_books(list_books);
                break;
            case 7: //exit
                cout << "Exiting to main menu..." << endl;
                break;
            default:
                cout << "\nInvalid option" << endl;
                break;
        }

    } while (*opt != 7);
}

void insert_book(struct Book *b)
{
    cout << "\n*** INSERT BOOK ***" << endl;
    index_b++;

    b -> code = index_b;

    cout << "Author: ";
    cin >> b -> author;

    cout << "Title: ";
    cin >> b -> title;

    do
    {
        cout << "Stock: ";
        cin >>b -> stock;
    } while (b -> stock <= 0);
    
    do
    {
        cout << "Price: ";
        cin >>b -> price;
    } while (b -> price < 100 || b -> price > 50000);

    do
    {
        cout << "Year: ";
        cin >>b -> year;
    } while (b -> year < 2000);

    do
    {
        cout << "Category (0-FANTASY, 1-FANTASTIC, 2-ROMAN, 3-HISTORY): ";
        cin >>b -> category;
    } while (b -> category < 0 || b -> category > 3);

    num_books++;
};

int get_num_books()
{
    return num_books;
};

int search_book(char *search_title, struct Book *list_books)
{
    int pos;

    cout << "\nWhat book you want to find: ";
    cin >> search_title;

    for (int i = 0; i < get_num_books(); i++)
    {
        if (strcmp(list_books[i].title, search_title) == 0)
        {
            pos = i;
            break;
        }
        else
        {
            pos = -1;
        }
    }

    return pos;
}

struct Book get_book(int pos, struct Book *list_books)
{
    if (pos != -1)
    {
        return list_books[pos];
    }
    else
    {
        return default_book();
    }
}

struct Book default_book()
{
    struct Book b;
    b.code = 0;
    b.title[0] = '\0';
    return b;
}

void print_book(struct Book b)
{
    cout << left;
    cout << setw(10) << b.code << setw(20) << b.author << setw(20) << b.title << setw(10)
    << b.stock << setw(10) << b.price << setw(10) << b.year;

    switch (b.category)
    {
        case 0:
            cout << setw(10) << "Fantasy" << endl;
            break;
        case 1:
            cout << setw(10) << "Fantastic" << endl;
            break;
        case 2:
            cout << setw(10) << "Roman" << endl;
            break;
        case 3:
            cout << setw(10) << "History" << endl;
            break;
    }
};

void print_list_books(struct Book *list_books)
{
    cout << "\n" << setw(10) << "Code" << setw(20) << "Author" << setw(20) << "Title" << setw(10)
    << "Stock" << setw(10) << "Price" << setw(10) << "Year" << setw(10) << "Category" << endl;

    for (int i = 0; i < get_num_books(); i++)
    {
        print_book(list_books[i]);
    }
}

void update_book(char *search_title, struct Book *list_books)
{
    int pos;

    cout << "\n***UPDATE BOOK***" << endl;

    pos = search_book(search_title, list_books);

    if (pos != -1)
    {
        cout << "Author: ";
        cin >>list_books[pos].author;

        cout << "Title: ";
        cin >>list_books[pos].title;

        do
        {
            cout << "Stock: ";
            cin >>list_books[pos].stock;
        } while (list_books[pos].stock <= 0);
        
        do
        {
            cout << "Price: ";
            cin >>list_books[pos].price;
        } while (list_books[pos].price < 100 || list_books[pos].price > 50000);

        do
        {
            cout << "Year: ";
            cin >>list_books[pos].year;
        } while (list_books[pos].year < 2000);

        do
        {
            cout << "Category (0-FANTASY, 1-FANTASTIC, 2-ROMAN, 3-HISTORY): ";
            cin >>list_books[pos].category;
        } while (list_books[pos].category < 0 || list_books[pos].category > 3);
        cout << "\nBook updated!" << endl;
    } 
    else
    {
        cout << "\nBook not found!" << endl;
    }
};

void delete_book(char *search_title, struct Book *list_books)
{
    int pos;

    cout << "\n***DELETE BOOK***" << endl;

    pos = search_book(search_title, list_books);

    if (pos != -1)
    {
        for (int i = pos; i < get_num_books(); i++)
        {
            list_books[i] = list_books[i+1];
        };

        num_books--;
        index_b--;

        cout << "\nBook deleted!" << endl;
    }
    else
    {
        cout << "\nBook not found!" << endl;
    }
}

void sort_books(struct Book *list_books)
{
    enum Criteria {AUTHOR, TITLE, PRICE, YEAR, CATEGORY};
    int criterion;

    do
    {
        cout << "Enter the sort criteion (0-author, 1-title, 2-price, 3-year, 4-category): ";
        cin >> criterion;
    } while (criterion < 0 || criterion > 4);

    switch (criterion)
    {
        case AUTHOR:
            sort_by_author(list_books);
            break;
        case TITLE:
            sort_by_title(list_books);
            break;
        case PRICE:
            sort_by_price(list_books);
            break;
        case YEAR:
            sort_by_year(list_books);
            break;
        case CATEGORY:
            sort_by_category(list_books);
            break;
    }
}

void sort_by_author(struct Book *list_books)
{
    struct Book aux;

    for (int i = 0; i < get_num_books() - 1; i++)
    {
        for (int j = i + 1; j < get_num_books(); j++)
        {
            if (strcmp(list_books[i].author, list_books[j].author) > 0)
            {
                aux = list_books[i];
                list_books[i] = list_books[j];
                list_books[j] = aux;
            }
        }
    }
}

void sort_by_title(struct Book *list_books)
{
    struct Book aux;

    for (int i = 0; i < get_num_books() - 1; i++)
    {
        for (int j = i + 1; j < get_num_books(); j++)
        {
            if (strcmp(list_books[i].title, list_books[j].title) > 0)
            {
                aux = list_books[i];
                list_books[i] = list_books[j];
                list_books[j] = aux;
            }
        }
    }
}

void sort_by_price(struct Book *list_books)
{
    struct Book aux;

    for (int i = 0; i < get_num_books() - 1; i++)
    {
        for (int j = i + 1; j < get_num_books(); j++)
        {
            if (list_books[i].price > list_books[j].price)
            {
                aux = list_books[i];
                list_books[i] = list_books[j];
                list_books[j] = aux;
            }
        }
    }
}

void sort_by_year(struct Book *list_books)
{
    struct Book aux;

    for (int i = 0; i < get_num_books() - 1; i++)
    {
        for (int j = i + 1; j < get_num_books(); j++){
            if (list_books[i].year > list_books[j].year)
            {
                aux = list_books[i];
                list_books[i] = list_books[j];
                list_books[j] = aux;
            }
        }
    }
}

void sort_by_category(struct Book *list_books)
{
    struct Book aux;

    for (int i = 0; i < get_num_books() - 1; i++)
    {
        for (int j = i + 1; j < get_num_books(); j++)
        {
            if (list_books[i].category > list_books[j].category)
            {
                aux = list_books[i];
                list_books[i] = list_books[j];
                list_books[j] = aux;
            }
        }
    }
}

void search_books(struct Book *list_books)
{
    enum Criteria {AUTHOR, TITLE, PRICE, YEAR, CATEGORY};
    int criterion;

    do
    {
        cout << "Enter the search criteion (0-author, 1-title, 2-price, 3-year, 4-category): ";
        cin >> criterion;
    } while (criterion < 0 || criterion > 4);

    switch (criterion)
    {
        case AUTHOR:
            search_by_author(list_books);
            break;
        case TITLE:
            search_by_title(list_books);
            break;
        case PRICE:
            search_by_price(list_books);
            break;
        case YEAR:
            search_by_year(list_books);
            break;
        case CATEGORY:
            search_by_category(list_books);
            break;
    } 
}

void search_by_author(struct Book *list_books)
{   
    char author[40];
    cout << "Author: ";
    cin >> author;

    cout << "\n" << setw(10) << "Code" << setw(20) << "Author" << setw(20) << "Title" << setw(10)
    << "Stock" << setw(10) << "Price" << setw(10) << "Year" << setw(10) << "Category" << endl;

    for (int i = 0; i < get_num_books(); i++)
    {
        if (strcmp(list_books[i].author, author) == 0)
        {
            print_book(list_books[i]);
        }
    }
}

void search_by_title(struct Book *list_books)
{
    char title[40];
    cout << "Title: ";
    cin >> title;

    cout << "\n" << setw(10) << "Code" << setw(20) << "Author" << setw(20) << "Title" << setw(10)
    << "Stock" << setw(10) << "Price" << setw(10) << "Year" << setw(10) << "Category" << endl;

    for (int i = 0; i < get_num_books(); i++)
    {
        if (strcmp(list_books[i].title, title) == 0)
        {
            print_book(list_books[i]);
        }
    }
}

void search_by_price(struct Book *list_books)
{
    double price;
    do
    {
        cout << "Price: ";
        cin >> price;
    } while (price < 100 || price > 50000);

    cout << "\n" << setw(10) << "Code" << setw(20) << "Author" << setw(20) << "Title" << setw(10)
    << "Stock" << setw(10) << "Price" << setw(10) << "Year" << setw(10) << "Category" << endl;

    for (int i = 0; i < get_num_books(); i++)
    {
        if (list_books[i].price == price)
        {
            print_book(list_books[i]);
        }
    }
}

void search_by_year(struct Book *list_books)
{
    int year;
    do
    {
        cout << "Year: ";
        cin >> year;
    } while (year < 2000);

    cout << "\n" << setw(10) << "Code" << setw(20) << "Author" << setw(20) << "Title" << setw(10)
    << "Stock" << setw(10) << "Price" << setw(10) << "Year" << setw(10) << "Category" << endl;

    for (int i = 0; i < get_num_books(); i++)
    {
        if (list_books[i].year == year)
        {
            print_book(list_books[i]);
        }
    }
}

void search_by_category(struct Book *list_books)
{
    int category;
    do
    {
        cout << "Category (0-FANTASY, 1-FANTASTIC, 2-ROMAN, 3-HISTORY): ";
        cin >> category;
    } while (category < 0 || category > 3);

    cout << "\n" << setw(10) << "Code" << setw(20) << "Author" << setw(20) << "Title" << setw(10)
    << "Stock" << setw(10) << "Price" << setw(10) << "Year" << setw(10) << "Category" << endl;

    for (int i = 0; i < get_num_books(); i++)
    {
        if (list_books[i].category == category)
        {
            print_book(list_books[i]);
        }
    }
}

int search_book_by_title(char *book_title, struct Book *list_books)
{
    int pos;

    for (int i = 0; i < get_num_books(); i++)
    {
        if (strcmp(list_books[i].title, book_title) == 0)
        {
            pos = i;
            break;
        }
        else {pos = -1;};
    };

    return pos;
};

void sort_books_by_code(struct Book *list_books)
{
    struct Book temp;

    for (int i = 0; i < get_num_books() - 1; i++)
    {
        for (int j = i + 1; j < get_num_books(); j++)
        {
            if (list_books[i].code > list_books[j].code)
            {
                temp = list_books[i];
                list_books[i] = list_books[j];
                list_books[j] = temp;
            }
            else if (list_books[i].code == list_books[j].code)
            {
                (list_books[j].code)++;
            };
        };
    };
};