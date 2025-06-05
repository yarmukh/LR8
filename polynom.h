#pragma once

typedef struct polynom
{
	//каждый элемент имеет вид An*x^n
	int power; //степень
	int coeff; //коэфициент
	struct polynom* next; //указатель на следующий элемент списка
} polynom;

polynom* create_polynom(int power, int coeff);

void add_polynom(polynom** head, int power, int coeff);

void print_polynom_node(polynom* head);