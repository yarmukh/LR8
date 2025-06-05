#include "menu.h"
#include <stdio.h>
#include <stdlib.h>
#include "polynom.h"
#include "string.h"

static List* string_head = NULL;
static List* string_tail = NULL;


void menu()
{
	functions sw = add;
	int power;
	int coeff;
	polynom* head = NULL;
	do
	{
		printf("Choose function from list:\n"
			"1 - Add an element to a polynomial\n"
			"2 - Print polynom\n"
			"3 - Enter a string of lowercase Latin letters\n"
			"4 - Split words with hyphens\n"
			"5 - Exit out of program\n");
		scanf_s("%d", &sw);
		switch (sw)
		{
        case add: {
            printf("Enter the power of the element to add: ");
            if (scanf_s("%d", &power) != 1 || power < 0)
            {
                while (getchar() != '\n');
                printf("Input error!\n");
                break;
            }

            printf("Enter the coefficient of the element to add: ");
            if (scanf_s("%d", &coeff) != 1)
            {
                while (getchar() != '\n');
                printf("Input error!\n");
                break;
            }

            if (head != NULL)
            {
                printf("Current polynomial: ");
                print_polynom_node(head);

                if (coeff > 0)
                {
                    printf(" + ");
                }
                else
                {
                    printf(" - ");
                }

                printf("%dx^%d\n", abs(coeff), power);
            }
            add_polynom(&head, power, coeff);
            printf("\nPolynomial added successfully!\n");
            break;
        }
		case print_polynom:
			print_polynom_node(head);
			printf("\n");
			break;
        case input_string: {
            while (getchar() != '\n');
            printf("Enter a string of lowercase Latin letters ending with '.': ");
            char input[1000];
            printf("\n");
            if (fgets(input, sizeof(input), stdin) == NULL)
            {
                printf("Input error!\n");
                break;
            }

            char* dot = strchr(input, '.');
            if (dot==NULL)
            {
                printf("Error.\n");
                break;
            }
            *dot = '\0';
            size_t len = strlen(input);
            if (len > 0 && input[len - 1] == '\n')
            {
                input[len - 1] = '\0';
                len--;
            }

            if (strlen(input) == 0)
            {
                printf("Error. Empty string!\n");
                break;
            }

            int valid = is_valid_string(input);
            if (!valid)
            {
                printf("Error. String must contain only lowercase letters and spaces!\n");
                break;
            }

            if (string_head)
            {
                free_list(string_head);
                string_head = NULL;
                string_tail = NULL;
            }

            char* context = NULL;
            char* token = strtok_s(input, " ", &context);
            while (token != NULL)
            {
                append_list(&string_head, &string_tail, token);
                token = strtok_s(NULL, " ", &context);
            }

            printf("\nOriginal string: ");
            print_list(string_head);
            break;
        }
        case modify_string: {
            if (string_head == NULL)
            {
                printf("Error. String didn't enter!\n");
                break;
            }

            if (string_head == string_tail && strcmp(string_head->word, "") == 0)
            {
                printf("Error. String is empty.\n");
                break;
            }

            process_list(&string_head, &string_tail);
            printf("Modified string: ");
            print_list(string_head);
            break;
        }
		case exit1:
		{
			polynom* tmp;
			while (head != NULL)
			{
				tmp = head;
				head = head->next;
				free(tmp);
			}
            if (string_head)
            {
                free_list(string_head);
                string_head = NULL;
                string_tail = NULL;
            }
			return;
		}
		default:
			printf("Input error!\n");
			break;
		}
	} while (sw != exit1);
	return;
}