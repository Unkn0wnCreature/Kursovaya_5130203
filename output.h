#pragma once

void print_file_client(char file_name[30], struct Client c);
void clean_file(char file_name[30]);
void print_num_clients(char file_name[30], int num_cl);
void print_clients_file(struct Client *list_clients);