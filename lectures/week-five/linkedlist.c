#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int number;
    struct node *next;
} node;

int main(void)
{
    // Always initialize the value to avoid 'garbage' data
    node *list = NULL;

    // Insert
    node *n = malloc(sizeof(node));
    if (n == NULL) return 1;

    // Update new node values
    n->number = 1;
    n->next = NULL;

    // Update list to point to new node
    // Adds at head
    list = n;

    // Insert another node
    n = malloc(sizeof(node));
    if (n == NULL)
    {
        free(list);
        return 1;
    }

    n->number = 2;
    n->next = NULL;
    list->next = n;

    // Insert a third number
    n = malloc(sizeof(node));
    if (n == NULL)
    {
        free(list->next);
        free(list);
        return 1;
    }

    n->number = 3;
    n->next = NULL;
    list->next->next = n;

    // Look through the node list one by one
    for (node *tmp = list; tmp != NULL; tmp = tmp->next)
    {
        printf("%i\n", tmp->number);
    }

    // I'm free
    while (list != NULL)
    {
        // Remember the next node as it contains the next node information
        node *tmp = list->next;
        // Free the current node
        free(list);
        // Set the new current node, to the next node
        list = tmp;
    }
}