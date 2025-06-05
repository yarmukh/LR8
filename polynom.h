#pragma once

typedef struct polynom
{
	//������ ������� ����� ��� An*x^n
	int power; //�������
	int coeff; //����������
	struct polynom* next; //��������� �� ��������� ������� ������
} polynom;

polynom* create_polynom(int power, int coeff);

void add_polynom(polynom** head, int power, int coeff);

void print_polynom_node(polynom* head);