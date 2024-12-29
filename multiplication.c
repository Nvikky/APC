#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"apc_header.h"

int multiplication(Dlist **t1, Dlist **t2, Dlist **head1, Dlist **head2, Dlist **head3, Dlist **tail3)
{
    /*declaring temporary pointer and initializing with head1*/
    Dlist *temp = *head1;
    long long num = 0;

    /* Convert the first linked list to an integer value */
    while (temp != NULL) 
    {
        num = num * 10000 + temp->data;
        temp = temp->next;
    }

    /* Initialize result list pointers */
    Dlist *result_head1 = NULL;
    Dlist *result_head2 = NULL;
    Dlist *result_head3 = NULL;
    Dlist *result_tail1 = NULL;
    Dlist *result_tail2 = NULL;
    Dlist *result_tail3 = NULL;

    /* Start from the second list's tail for multiplication */
    temp = *t2;
    long long int res;
    long long int num1 = temp->data;
    
    /* Multiply the integer from the first list with each node of the second list */
    res = num * num1;
    for (int i = 0; res > 0; i++)
    {
        /* Extract 4-digit segments to store in the result list */
        int rem = res % 10000;
        insert_first(&result_head1, &result_tail1, rem);
        res = res / 10000;
    }
    temp = temp->prev;
    int j = 1;

    /* Continue multiplying each remaining node of the second list */
    while (temp != NULL)
    {
        /* Shift result by inserting zeroes as place holders */
        for (int i = 0; i < j; i++)
        {
            insert_first(&result_head2, &result_tail2, 0);
        }

        num1 = temp->data;
        res = num * num1;

        /* Extract 4-digit segments for the partial result */
        for (int i = 0; res > 0; i++)
        {
            int rem = res % 10000;
            insert_first(&result_head2, &result_tail2, rem);
            res = res / 10000;
        }

        /* Add current partial result to the cumulative result */
        addition(&result_tail1, &result_tail2, &result_head3, &result_tail3);

        /* Update cumulative result lists for the next iteration */
        result_head1 = result_head3;
        result_tail1 = result_tail3;

        /* Reset intermediate result lists */
        result_head2 = NULL;
        result_tail2 = NULL;
        result_head3 = NULL;
        result_tail3 = NULL;

        /* Move to the previous node and increment the place value position */
        temp = temp->prev;
        j++;
    }
    *head3 = result_head1;
    *tail3 = result_tail3;
    return SUCCESS; 
}
