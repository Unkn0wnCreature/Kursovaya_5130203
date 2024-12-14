#include <iostream>
#include <cstring>
#include <iomanip>
#include <cstdio>
#include "client.h"
#include "output.h"
#include "input.h"
using namespace std;

static int num_clients = 0;
static int index = 0;

void menu_clients(int *opt, struct Client *list_clients)
{
   int pos;
   char search_name[30];
   struct Client c;
   
   do
   {
        cout<<left;
        cout<< setw(20) << "\n--- MANAGMENT OF CLIENTS ---" <<endl;
        cout<< "[1]. Insert client" <<endl;
        cout<< "[2]. Read list of clients" <<endl;
        cout<< "[3]. Update client" <<endl;
        cout<< "[4]. Delete client" <<endl;
        cout<< "[5]. Exit" <<endl;
        cout<< "----------------------------------------------" <<endl;
        cout<< "Enter option: ";
        cin>>*opt;

        switch (*opt)
        {
            case 1: //insert
                insert_client(&list_clients[get_num_clients()]);
                print_clients_file(list_clients);
                break;
            case 2: //read
                read_file_client("client.txt");
                break;
            case 3: //update
                update_client(search_name, list_clients);
                clean_file("client.txt");
                print_clients_file(list_clients);
                break;
            case 4: //delete
                delete_client(search_name, list_clients);
                clean_file("client.txt");
                print_clients_file(list_clients);
                break;
            case 5:
                cout<< "Exiting to main menu..." <<endl;
                break;
            default:
                cout<< "\nInvalid option" <<endl;
                break;
        }

    } while (*opt != 5);
}

void insert_client(struct Client *c)
{
    cout<< "\n*** INSERT CLIENT ***" << endl;
    index++;

    c -> code = index;

    cout<< "Name: ";
    cin>>c -> name;

    do
    {
        cout<< "Age: ";
        cin>>c -> age;
    } while (c -> age <= 0);
    
    do
    {
        cout<< "Salary: ";
        cin>>c -> salary;
    } while (c -> salary < 20000 || c -> salary > 500000);

    num_clients++;
};

int get_num_clients()
{
    return num_clients;
};

int search_client(char *search_name, struct Client *list_clients)
{
    int pos;

    cout<< "\nWhat client you want to find: ";
    cin>>search_name;

    for (int i = 0; i < get_num_clients(); i++)
    {
        if (strcmp(list_clients[i].name, search_name) == 0)
        {
            pos = i;
            break;
        }
        else {pos = -1;}
    };

    return pos;
}

struct Client get_client(int pos, struct Client *list_clients)
{
    if (pos != -1) {return list_clients[pos];}
    else {return default_client();};
};

struct Client default_client()
{
    struct Client c;

    c.code = 0;
    c.name[0] = '\0';

    return c;
};

void update_client(char *search_name, struct Client *list_clients)
{
    int pos;

    cout<< "\n***UPDATE CLIENT***" <<endl;

    pos = search_client(search_name, list_clients);

    if (pos != -1)
    {
       cout<< "Name: ";
    cin>>list_clients[pos].name;

    do
    {
        cout<< "Age: ";
        cin>>list_clients[pos].age;
    } while (list_clients[pos].age <= 0);
    
    do
    {
        cout<< "Salary: ";
        cin>>list_clients[pos].salary;
    } while (list_clients[pos].salary < 20000 || list_clients[pos].salary > 500000);

    cout<< "\nClient updated!" <<endl;
    }
    else {cout<< "\nClient not found!" <<endl;};
};

void delete_client(char *search_name, struct Client *list_clients)
{
    int pos;

    cout<< "\n***DELETE CLIENT***" <<endl;

    pos = search_client(search_name, list_clients);

    if (pos != -1)
    {
        for (int i = 0; i < get_num_clients(); i++)
        {
            list_clients[i] = list_clients[i+1];
        };

        num_clients--;

        cout<< "\nClient deleted!" <<endl;
    }
    else {cout<< "\nClient not found!" <<endl;};
};