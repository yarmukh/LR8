#include "string.h"


int is_lower_latin(char c)
{
    return ((c >= 'a' && c <= 'z')||(c == '-')||(c=='.')||(c == ' '));
}


int is_valid_string(const char* str)
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (!is_lower_latin(str[i]))
        {
            return 0;
        }
    }
    return 1;
}


List* create_list(const char* word)
{
    if (!word) return NULL;

    List* new_node = (List*)malloc(sizeof(List));
    if (!new_node)
    {
        printf("Memory allocation failed for node\n");
        return NULL;
    }

    new_node->word = _strdup(word);
    if (!new_node->word)
    {
        printf("Memory allocation failed for word\n");
        free(new_node);
        return NULL;
    }

    new_node->prev = NULL;
    new_node->next = NULL;
    return new_node;
}


void append_list(List** head, List** tail, const char* word)
{
    if (!head || !tail || !word)
    {
        return;
    }
    List* new_node = create_list(word);
    if (!new_node)
    {
        return;
    }
    if (*head == NULL)
    {
        *head = new_node;
        *tail = new_node;
    }
    else
    {
        (*tail)->next = new_node;
        new_node->prev = *tail;
        *tail = new_node;
    }
}


void split_hyphenated_word(List** current, List** tail, List** head)
{
    char* word = (*current)->word;
    char* hyphen = strchr(word, '-');
    if (!hyphen)
    {
        return;
    }
    *hyphen = '\0';
    char* first_part = word;
    char* second_part = hyphen + 1;
    List* first_node = create_list(first_part);
    List* second_node = create_list(second_part);
    first_node->prev = (*current)->prev;
    first_node->next = second_node;
    second_node->prev = first_node;
    second_node->next = (*current)->next;

    if ((*current)->prev)
    {
        (*current)->prev->next = first_node;
    }
    else
    {
        *head = first_node;
    }

    if ((*current)->next)
    {
        (*current)->next->prev = second_node;
    }
    else
    {
        *tail = second_node;
    }

    free((*current)->word);
    free(*current);

    *current = second_node;
    while (strchr((*current)->word, '-'))
    {
        split_hyphenated_word(current, tail, head);
    }
}

void process_list(List** head, List** tail)
{
    List* current = *head;
    while (current)
    {
        if (strchr(current->word, '-'))
        {
            List* next_node = current->next;
            split_hyphenated_word(&current, tail, head);
            current = next_node;
        }
        else
        {
            current = current->next;
        }
    }
}


void print_list(List* head)
{
    List* current = head;
    while (current)
    {
        printf("%s", current->word);
        if (current->next)
        {
            printf(" ");
        }
        current = current->next;
    }
    printf(".\n");
}


void free_list(List* head)
{
    List* current = head;
    while (current)
    {
        List* next = current->next;
        free(current->word);
        free(current);
        current = next;
    }
}