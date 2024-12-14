#pragma once
#include "client.h"
#include "book.h"
#define MAX 10

struct OrderDetail
{
    Book book;
    int num;
    double subtotal;
};

struct Order
{
    int code;
    Client client;
    OrderDetail details[MAX];
    int num_details;
    double total;
};