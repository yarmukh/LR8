#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


typedef struct List
{
    char* word;
    struct List* prev;
    struct List* next;
} List;

int is_lower_latin(char c);

int is_valid_string(const char* str);

List* create_list(const char* word);

void append_list(List** head, List** tail, const char* word);

void split_hyphenated_word(List** current, List** tail);

void process_list(List** head, List** tail);

void print_list(List* head);

void free_list(List* head);

