#include "polynom.h"
#include <stdio.h>
#include <stdlib.h>


polynom* create_polynom(int power, int coeff)
{
	polynom* Node = (polynom*)malloc(sizeof(polynom));
	if (Node == NULL)
	{
		printf("Memory allocation error!\n");
		return NULL;
	}
	Node->coeff = coeff;
	Node->power = power;
	Node->next = NULL;
	return Node;
}


void add_polynom(polynom** head, int power, int coeff)
{
	if (coeff == 0)
	{
		return;
	}
	polynom* current = *head;
	polynom* prev = NULL;
	while (current != NULL && current->power > power)
	{
		prev = current;
		current = current->next;
	}
	if (current != NULL && current->power == power)
	{
		current->coeff += coeff;
		if (current->coeff == 0)
		{
			if (prev == NULL)
			{
				*head = current->next;
			}
			else {
				prev->next = current->next;
			}
			free(current);
		}
		return;
	}

	polynom* next_node = create_polynom(power, coeff);
	if (prev == NULL)
	{
		next_node->next = *head;
		*head = next_node;
	}
	else
	{
		next_node->next = current;
		prev->next = next_node;
	}
	return;
}


void print_polynom_node(polynom* head)
{
	int first = 1;
	if (head == NULL)
	{
		printf("Polynomial is empty!\n");
		return;
	}
	while (head != NULL)
	{
		int coeff = head->coeff;
		int power = head->power;

		if (first)
		{
			if (coeff < 0)
			{
				printf("-");
			}
			first = 0;
		}
		else
		{
			if (coeff > 0)
			{
				printf(" + ");
			}
			else
			{
				printf(" - ");
			}
		}
		int abs_coeff = abs(coeff);
		if (abs_coeff != 1 || power == 0)
		{
			printf("%d", abs_coeff);
		}
		if (power > 0)
		{
			printf("x");
			if (power > 1)
			{
				printf("^%d", power);
			}
		}
		head = head->next;
	}
}