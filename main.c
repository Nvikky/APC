/*
Name : N Venkata prasad
Date : 27.11.2024
File name : main.c 
*/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"apc_header.h"

/*main function*/
int main(int argc,char *argv[])
{
    /*creating the variable*/
    Apc apc;
    /*calling read_validate function*/
    int ret = read_validation(argc,argv,&apc);
    /*if return value is FAILURE, return Failure*/
    if(ret==FAILURE)
    {
        return FAILURE;
    }
    /*declaring head and tail variable for 2 lists*/
    Dlist *head1 = NULL; 
	Dlist *tail1 = NULL;
    Dlist *head2 = NULL; 
	Dlist *tail2 = NULL;
    /*storing first operand obtained from CLA argument, in first linked list*/
    int return_res1 = store(apc.operand1_len,apc.operand1,&head1,&tail1);
    if(return_res1==FAILURE)
    {
        return FAILURE;
    }
    /*storing second operand obtained from CLA argument, in second linked list*/
    int return_res2 = store(apc.operand2_len,apc.operand2,&head2,&tail2);
    if(return_res2==FAILURE)
    {
        return FAILURE;
    }
    /*calling operation function */
    int return_res3 = operation(&apc,&head1,&tail1,&head2,&tail2);
    if(return_res3 == FAILURE)
    {
        return FAILURE;
    }
    return SUCCESS;
}

/*read_validate function*/
int read_validation(int argc,char *argv[], Apc *apc)
{
    /*checking whether the argument count is 4*/
    if(argc == 4)
    {
        /*loop to check second CLA*/
        for(int i=0;argv[1][i]!=0;i++)
        {
            /*condition to check whether the argument contains any letter*/
            if(((argv[1])[i]>='a' && (argv[1])[i]<='z') || ((argv[1])[i]>='A' && (argv[1])[i]<='Z'))
            {
                /*printing error message if argument contains any character other than digit*/
                printf("Invalid argument!\noperand should be integer type");
                return FAILURE;
            }
        }
        /*array of operators*/
        char *valid_ops[] = {"+", "-", "/", "x"};
        int valid = 0;
        /*loop to check the presence any operator*/
        for (int i = 0; i < 4; i++)
        {
            /*condition to check the presence any operator*/
            if (strcmp(argv[2], valid_ops[i]) == 0)
            {
                valid = 1;
                break;
            }
        }
        
        /*if operator is invalid print error message and return*/
        if (!valid)
        {
            printf("Invalid argument!\noperator should be selected among : +,-,/,x\n");
            return FAILURE;
        }
        /*loop to check fourth CLA*/
        for(int i=0;argv[3][i]!=0;i++)
        {
            /*condition to check whether the argument contains any letter*/
            if(((argv[3])[i]>='a' && (argv[3])[i]<='z') || ((argv[3])[i]>='A' && (argv[3])[i]<='Z'))
            {
                /*printing error message if argument contains any character other than digit*/

                printf("Invalid argument!\noperand should be integer type");
                return FAILURE;
            }
        }
        /*copying operands and their length and opeartor in structure variable*/
        apc->operand1_len=strlen(argv[1]);
        apc->operand2_len=strlen(argv[3]);
        apc->oper_len=strlen(argv[2]);
        strcpy(apc->operand1,argv[1]);
        strcpy(apc->operand2,argv[3]);
        strcpy(apc->oper,argv[2]);
    }
    else
    {
        /*printing error message when argument count is less or more than 4*/

        printf("ERROR: ./a.out : INVALID ARGUMENTS\nUSAGE :\n");
        printf("Please pass like: ./a.out operand1 operator operand2\n");

        return FAILURE;
    }
}

/* Converts a string into nodes of a doubly linked list */
int store(int len, char *operand, Dlist **head, Dlist **tail)
{
    /* Declaring a string to temporarily hold each 4-digit segment */
    char str[5]; 

    /* Loop to store the operand in the list as 4-digit segments */
    for (int i = len; i > 0; i -= 4)
    {
        int start;
        
        /* Determine the starting index for the 4-digit segment */
        if ((i - 4) >= 0)
        {
            /*If there are 4 or more characters, take a 4-digit segment*/
            start = i - 4;  
        }
        else
        {
            /* Otherwise, start from index 0 for the last segment*/
            start = 0;  
        }
        
        /* Calculate the size of the segment whether it is 4 or the remaining number of digits*/
        int size = i < 4 ? i : 4;
        
        /* Copy the segment from the operand to the temporary string */
        for (int j = 0; j < size; j++)
        {
            str[j] = operand[start + j];
        }
        
        /* terminate the string with NULL */
        str[size] = '\0';
        
        /* Convert the 4-digit string to an integer */
        int num = atoi(str);
        
        /* Insert at the beginning of the double linked list */
        int ret = insert_first(head, tail, num);
        
        /* Check if the insertion failed */
        if (ret == FAILURE)
        {
            return FAILURE;
        }
        
        /* Check for a negative sign at the position just before the current segment */
        if (operand[i - 5] == '-')
        {
            /* if a '-' sign is found */
            (*head)->data = -(*head)->data;
            /*Exit the loop as the negative sign only applies to the first number*/
            break;  
        }
    }
}

/*create node function*/
int create_node(Dlist **new,int data)
{
    /*creating new node by allocating the memory*/
    *new=malloc(sizeof(Dlist));
    /*validating the new node memory*/
    if(*new==NULL)
    {
        return FAILURE;
    }
    /*updating the new node data and links*/
    (*new)->data=data;
    (*new)->prev=NULL;
    (*new)->next=NULL;
    return SUCCESS;
}

/*insert_first function*/
int insert_first(Dlist **head, Dlist **tail, int data)
{
    /*declaring pointer*/
    Dlist *new=NULL;
    /*calling create_node function*/
    int ret = create_node(&new,data);
    if(ret==FAILURE)
    {
        return FAILURE;
    }
    /*validating the head and linking node when it is NULL*/
    if(*head==NULL)
    {
        /*updating head and tail*/
        *head=new;
        *tail=new;
        return SUCCESS;
    }
    /*if list is not empty updating the head and first node prev link*/
    (*head)->prev=new;
    /*updating new node next link*/
    new->next=*head;
    /*updating head with new*/
    *head=new;
    return SUCCESS;
}

/* Function to print the doubly linked list */
void print_list(Dlist *head)
{
    /* Checking if the list is empty */
    if (head == NULL)
    {
        printf("INFO : List is empty\n");
    }
    else
    {
        /* Print the data of the first node */
        printf("%d", head->data);
        
        /* Move to the next node */
        head = head->next;
        
        /* Loop through the list and print each node's data */
        while (head)
        {
            printf("%04d", head->data);    
            /* Move to the next node in the list */
            head = head->next;
        }
    }
    printf("\n");
}


