/*
Name : N Venkata prasad
Date : 27.11.2024
File name : operation.c
*/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"apc_header.h"

int operation(Apc *apc, Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2)
{
    /* Initialize pointers to the tails of the lists */
    Dlist *t1 = *tail1;
    Dlist *t2 = *tail2;
    
    /* Initialize result list head and tail pointers to NULL */
    Dlist *result_head = NULL;
    Dlist *result_tail = NULL;
    
    /* Check if the operation is addition */
    if (strcmp(apc->oper, "+") == 0)
    {
        /* If both numbers are negative */
        if ((*head1)->data < 0 && (*head2)->data < 0)
        {
            /* Make both numbers positive for addition */
            (*head1)->data = -(*head1)->data;
            (*head2)->data = -(*head2)->data;
            
            /* Perform addition */
            addition(&t1, &t2, &result_head, &result_tail);
            
            /* Make the result negative */
            result_head->data = -result_head->data;
        }
        /* If only the first number is negative */
        else if ((*head1)->data < 0)
        {
            /*Make the first number positive*/
            (*head1)->data = -(*head1)->data;  
            
            /* Perform substraction as (second number - first number) */
            substraction(&t2, &t1, head2, head1, &result_head, &result_tail);
        }
        /* If only the second number is negative */
        else if ((*head2)->data < 0)
        {
            /*Make the second number positive*/
            (*head2)->data = -(*head2)->data; 
            
            /* Perform substraction as (first number - second number) */
            substraction(&t1, &t2, head1, head2, &result_head, &result_tail);
        }
        else
        {
            /* Both numbers are positive, perform addition */
            addition(&t1, &t2, &result_head, &result_tail);
        }
        
        /* Printing the addition result */
        printf("Addition : %s + %s\n", apc->operand1, apc->operand2);
    }
    /* Check if the operation is substraction */
    else if (strcmp(apc->oper, "-") == 0)
    {
        /* If both numbers are negative */
        if ((*head1)->data < 0 && (*head2)->data < 0)
        {
            /* Make both numbers positive for substraction */
            (*head1)->data = -(*head1)->data;  
            (*head2)->data = -(*head2)->data;  
            
            /* Perform substraction as (first number - second number) */
            substraction(&t1, &t2, head1, head2, &result_head, &result_tail);
            
            /* Make the result negative */
            result_head->data = -result_head->data;
        }
        /* If only the first number is negative */
        else if ((*head1)->data < 0)
        {
            /*Make the first number positive*/
            (*head1)->data = -(*head1)->data; 
            
            /* Perform addition and make the result negative */
            addition(&t1, &t2, &result_head, &result_tail);
            result_head->data = -result_head->data;
        }
        /* If only the second number is negative */
        else if ((*head2)->data < 0)
        {
            /*Make the second number positive*/
            (*head2)->data = -(*head2)->data; 
            
            /* Perform addition */
            addition(&t1, &t2, &result_head, &result_tail);
        }
        else
        {
            /* Both numbers are positive, perform substraction */
            substraction(&t1, &t2, head1, head2, &result_head, &result_tail);
        }
        
        /* Print the substraction result */
        printf("substraction : %s - %s\n", apc->operand1, apc->operand2);
       
    }
    /* Check if the operation is division */
    else if (strcmp(apc->oper, "/") == 0)
    {
        /* checking is two operands are negative value */
        if((*head1)->data<0 && (*head2)->data<0)
        {
            /* making two operands value positive */
            (*head1)->data=-(*head1)->data;
            (*head2)->data=-(*head2)->data;
            /* calling division function to perform Division */
            division(head1,tail1,head2,tail2,&result_head,&result_tail);
        }
        /* checking is first operand is negative value */
        else if((*head1)->data<0)
        {
            (*head1)->data=-(*head1)->data;
            /* calling division function to perform Division */
            division(head1,tail1,head2,tail2,&result_head,&result_tail);
            /* making resultant value negative */
            result_head->data=-result_head->data;
        }
        /* checking is second operand is negative value */
        else if((*head2)->data<0)
        {
            /* making second operands value positive */
            (*head2)->data=-(*head2)->data;
            /* calling division function to perform Division */
            division(head1,tail1,head2,tail2,&result_head,&result_tail);
            /* making resultant value negative */
            result_head->data=-result_head->data;
        }
        else
        {
        /* calling division function to perform Division */
           division(head1,tail1,head2,tail2,&result_head,&result_head);
        }

        printf("Division : %s / %s\n", apc->operand1, apc->operand2);
       
    }
    /* Check if the operation is multiplication */
    else if (strcmp(apc->oper, "x") == 0)
    {
        /* If both numbers are negative */
        if ((*head1)->data < 0 && (*head2)->data < 0)
        {
            /* Make both numbers positive for multiplication */
            (*head1)->data = -(*head1)->data;  
            (*head2)->data = -(*head2)->data;  
            
            /* Perform multiplication */
            multiplication(&t1, &t2, head1, head2, &result_head, &result_tail);
        }
        /* If only the first number is negative */
        else if ((*head1)->data < 0)
        {
            /*Make the first number positive*/
            (*head1)->data = -(*head1)->data; 
            
            multiplication(&t1, &t2, head1, head2, &result_head, &result_tail);
            result_head->data = -result_head->data;
        }
        /* If only the second number is negative */
        else if ((*head2)->data < 0)
        {
            /*Make the second number positive*/
            (*head2)->data = -(*head2)->data; 
            
            /* Perform multiplication and make the result negative */
            multiplication(&t1, &t2, head1, head2, &result_head, &result_tail);
            result_head->data = -result_head->data;
        }
        else
        {
            /* Both numbers are positive, perform multiplication */
            multiplication(&t1, &t2, head1, head2, &result_head, &result_tail);
        }
        
        /* Print the multiplication result */

        printf("Multiplication : %s x %s\n", apc->operand1, apc->operand2);

    }

    printf("Result : ");
    /* Print the resulting list */
    print_list(result_head);
}
