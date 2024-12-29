#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"apc_header.h"

int addition(Dlist **t1, Dlist **t2, Dlist **result_head, Dlist **result_tail)
{
    /*Initialize carry to 0*/
    int carry = 0;  

    /* Loop until both lists are fully traversed */
    while ((*t1) != NULL || (*t2) != NULL)
    {
        /* Retrieve the data from each list node, or 0 if the node is NULL */
        int data1 = ((*t1) != NULL) ? (*t1)->data : 0;  
        int data2 = ((*t2) != NULL) ? (*t2)->data : 0;

        /* Calculate the sum of the two nodes' data plus any carry */
        int sum = data1 + data2 + carry;
        
        /* Calculate new carry for next iteration ,if sum exceeds 4 digits*/
        carry = sum / 10000;
        
        /* Get the last 4 digits of the sum to store in the result list */
        int digit = sum % 10000;

        /* Insert the computed digit at the beginning of the result list */
        int ret = insert_first(result_head, result_tail, digit);

        /* Move to the previous node in the first list, if it exists */
        if (*t1 != NULL) 
            *t1 = (*t1)->prev;
        
        /* Move to the previous node in the second list, if it exists */
        if (*t2 != NULL) 
            *t2 = (*t2)->prev;
    } 
    
    /* If there is a carry left after the final addition, add it to the result list */
    if (carry > 0)
    {
        insert_first(result_head, result_tail, carry);
    }

    /*Return SUCCESS upon completing the addition*/
    return SUCCESS;  
}