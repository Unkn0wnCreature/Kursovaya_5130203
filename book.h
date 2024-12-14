#pragma once

struct Book
{
    int code;
    char author[40];
    char name[40];
    int stock;
    double cost;
    int year;
    int category;
    enum Category {FANTASY, FANTASTIC, ROMAN, HISTORY};
};
