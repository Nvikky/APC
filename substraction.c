#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"apc_header.h"

int substraction(Dlist **t1, Dlist **t2, Dlist **head1, Dlist **head2, Dlist **result_head, Dlist **result_tail)
{
    /* Create temporary pointers to count the number of nodes in each list */
    Dlist *temp1 = *head1;
    Dlist *temp2 = *head2;
    int c1 = 0, c2 = 0;
    /*initialize borrow*/
    int borrow = 0, sum;

    /* Count the number of nodes in the first list */
    while (temp1 != NULL)
    {
        c1++;
        temp1 = temp1->next;
    }
    
    /* Count the number of nodes in the second list */
    while (temp2 != NULL)
    {
        c2++;
        temp2 = temp2->next;
    }

    /* If the second list is larger, swap the lists to ensure positive result */
    if (c2 > c1)
    {
        Dlist *t = *t1;
        *t1 = *t2;
        *t2 = t;
    }
    /* If both lists have the same length, compare the head node data to determine larger number */
    else if (c1 == c2)
    {
        if ((*head1)->data < (*head2)->data)
        {
            Dlist *t = *t1;
            *t1 = *t2;
            *t2 = t;
        }
    }

    /* Traverse both lists from the tail nodes */
    while (*t1 != NULL || *t2 != NULL)
    {
        /* Get the data from each node, or 0 if the node is NULL */
        int data1 = (*t1 != NULL) ? (*t1)->data : 0;  
        int data2 = (*t2 != NULL) ? (*t2)->data : 0;

        /* Calculate the difference between nodes, adjusting for any borrow */
        sum = data1 - data2 - borrow;
        
        /* If the result is negative, borrow from the next higher place value */
        if (sum < 0)
        {
            /*Adjust the sum by adding 10000 (to simulate borrowing)*/
            sum += 10000; 
            /*Set borrow for the next iteration*/
            borrow = 1;   
        }
        else
        {
            /*Reset borrow if no borrowing is needed*/
            borrow = 0;   
        }

        /* Insert the computed difference at the beginning of the result list */
        int ret = insert_first(result_head, result_tail, sum);

        /* Move to the previous node in each list, if it exists */
        if (*t1 != NULL) 
            *t1 = (*t1)->prev;
        if (*t2 != NULL) 
            *t2 = (*t2)->prev;
    }
    
    /* If there is a borrow left, add it to the result list (handles negative results) */
    if (borrow > 0)
    {
        insert_first(result_head, result_tail, -sum);
    }

    /*Return SUCCESS upon completing the substraction*/
    return SUCCESS;  
}