#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"apc_header.h"

void division(Dlist **head1,Dlist **tail1,Dlist **head2,Dlist **tail2,Dlist **result_head,Dlist **result_tail)
{
    Dlist *temp1=*head1;
    Dlist *temp2=*head2;
    int res,c=0;
    long long int num1=0,num2=0;
    while(temp1!=NULL)
    {
        num1=num1*10000+temp1->data;
        temp1=temp1->next;
    }
    while(temp2!=NULL)
    {
        num2=num2*10000+temp2->data;
        temp2=temp2->next;
    }
    if(num2==0)
    {
        printf("Division by zero is not permitted\n");

        return;
    }
    /* run the loop till num1 is greater equal to num2*/
    while(num1>=num2)
    {
        /* performing subtraction operation */
        num1=num1-num2;
        /* incrementing c */
        c++;
    }
    /* calling inser_first function to store resultant in double list */
    insert_first(result_head,result_tail,c);
}