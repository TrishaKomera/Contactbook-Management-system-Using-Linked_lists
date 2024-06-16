
#include <stdio.h>
/*BT21CSE051_DSPD_II_Using_Linked_lists.c*/
#include <stdlib.h>
#include<string.h>
//Assumtion: All firstnames and lastnames are either in capital or lower case and phone number is of 10 digits

typedef enum {FAILURE,SUCCESS}status_code;//enum for getting status

typedef struct calldetails_node
{
    struct calldetails_node* next;
    struct calldetails_node* prev;
    char date[9];
    int duration;
}calldetails;
//creating a history node
typedef struct contact_node
{
    char firstname[20];
    char lastname[20];
    int mobilenumber;
    char emailid[50];
    int officenumber;
    char address[100];
    calldetails *callhistory;
    struct contact_node* next;
    struct contact_node* prev;
}contact;
//creating a contact node
typedef struct contact_list_tag
{
    contact *personal;
    contact *professional;
}contact_list;
//creating phonebook
typedef struct database_tags
{
    char name[100];
    struct database_tags* next;
    struct database_tags* prev;
    long int total_time;
    contact_list contactlist;
}database;
//linked lists of phonebooks
void initialize_contact_list(contact_list *list)
{
    contact_list *ptr=list;
    ptr->personal=NULL;
    ptr->professional=NULL;
    list=ptr;
}
//Initializing contact list
status_code insert_contact_history(calldetails **history_list)
{
    calldetails *new_call_node=(calldetails*)malloc(sizeof(calldetails));
    calldetails *ptr=*history_list;
    status_code status=SUCCESS;
    if(new_call_node==NULL)
    {
        status==FAILURE;
    }
    else
    { 
        printf("Enter the date of the call: ");
        scanf("%s",new_call_node->date);
        printf("Enter the duration of the call in minutes: ");
        scanf("%d",&new_call_node->duration);
        if(ptr==NULL)
        {
            *history_list=new_call_node;
            new_call_node->next=NULL;
            new_call_node->prev=NULL;
        }
        else
        {
            while(ptr->next!=NULL)
            {
                ptr=ptr->next;
            }
            ptr->next=new_call_node;
            new_call_node->prev=ptr;
            new_call_node->next=NULL;
        }
    }
    return status;
}
//fn to insert contact history
void sorted_insert_name(contact** list,contact* nptr)
{
    contact *ptr=*list;
    int flag=0;
    while(ptr!=NULL&&flag==0)
    {
        if(strcmp(ptr->firstname,nptr->firstname)>0)
        {
            flag=1;
        }
        else if(strcmp(ptr->firstname,nptr->firstname)==0)
        {
            if(strcmp(ptr->lastname,nptr->lastname)>0)
            {
                flag=1;
            }
            else if(strcmp(ptr->lastname,nptr->lastname)==0)
            {
                if(ptr->mobilenumber>nptr->mobilenumber)
                {
                    flag=1;
                }
                else
                {
                    ptr=ptr->next;
                }
            }
        }
        else
        {
            ptr=ptr->next;
        }
    }
    if(flag==1)
    {
        contact *prev_node=ptr->prev;
        if(prev_node==NULL)
        {
            *list=nptr;
            nptr->next=ptr;
            ptr->prev=nptr;
        }
        else
        {
            prev_node->next=nptr;
            nptr->prev=prev_node;
            nptr->next=ptr;
            ptr->prev=nptr;
        }
    }
    else
    {
        ptr=*list;
        while(ptr->next!=NULL)
        {
            ptr=ptr->next;
        }
        ptr->next=nptr;
        nptr->prev=ptr;
    }
}
//as we need to insert in sorted format so fn to add in sorted way
status_code Insert_the_newcontact(contact_list * list)
{
    status_code status=SUCCESS;
    contact* newcontact;
    contact_list *ptrlist=list;
    contact *ptr_personal=ptrlist->personal;
    contact *ptr_professional=ptrlist->professional;
    newcontact=(contact*)malloc(sizeof(contact));
    if(newcontact==NULL)
    {
        status=FAILURE;
    }
    else
    {
        printf("Enter the first name of the contact:");
        scanf("%s",newcontact->firstname);
        printf("Enter the last name of the contact:");
        scanf("%s",newcontact->lastname);
        printf("Enter the mobile number of the contact:");
        scanf("%d",&newcontact->mobilenumber);
        printf("Enter the email id of the contact:");
        scanf("%s",newcontact->emailid);
        printf("Enter the office number of the contact:");
        scanf("%d",&newcontact->officenumber);
        printf("Enter the address of the contact:");
        scanf("%s",newcontact->address);
        printf("Enter 1 to store as personal contact or 2 to store as professional contact:");
        int select;
        scanf("%d",&select);
        while(!(select==1||select==2))
        {
            printf("\nEnter 1 to store as personal contact or 2 to store as professional contact:");
            scanf("%d",&select);
        }
        status_code sc2 = SUCCESS;
        if(select==1)
        {
            if(ptr_personal==NULL)
            {
                ptrlist->personal=newcontact;
            }
            else
            {
                sorted_insert_name(&ptrlist->personal,newcontact);
            }
            select=1;
            while(sc2==SUCCESS&&!(select==2))
            {
                printf("Enter 1 to store contact history or 2 to skip:");
                scanf("%d",&select);
                if(select==1)
                {
                    sc2=insert_contact_history(&newcontact->callhistory);
                    if(sc2==FAILURE)
                    {
                        printf("Malloc failed in adding contact history\n");
                    }
                }
                else if(select==2)
                {
                    sc2=FAILURE;
                }
                else
                {
                    printf("Select Valid input\nEnter 1 to store contact history or 2 to skip:");
                    scanf("%d",&select);
                }
            }
        }
        else
        {
            if(ptr_professional==NULL)
            {
                ptrlist->professional=newcontact;
            }
            else
            {
                sorted_insert_name(&ptrlist->professional,newcontact);
            }
            select=1;
            while(sc2==SUCCESS&&!(select==2))
            {
                printf("Enter 1 to store contact history or 2 to skip:");
                scanf("%d",&select);
                if(select==1)
                {
                    printf("\nEnter 1 to store contact history or 2 to skip:");
                    scanf("%d",&select);
                    sc2=insert_contact_history(&newcontact->callhistory);
                    if(sc2==FAILURE)
                    {
                        printf("Malloc failed in adding contact history\n");
                    }
                }
                else if(select==2)
                {
                    sc2=FAILURE;
                }
                else
                {
                    printf("Select Valid input\nEnter 1 to store contact history or 2 to skip:");
                    scanf("%d",&select);
                }
            }
        }
    }
    list = ptrlist;
    return status;
}
//fn to add new contact
void free_contact_history(calldetails **history_list)
{
    calldetails *ptr=*history_list;
    calldetails *fptr;
    while(ptr!=NULL)
    {
        fptr=ptr;
        ptr=ptr->next;
        free(fptr);
    }
    *history_list=NULL;
}
//free function to delete history
void delete_contact(contact ** listptr, contact * nptr)
{
    contact *ptr_list=*listptr;
    contact *prevnode=nptr->prev;
    contact *nextnode=nptr->next;
    if(prevnode==NULL)
    {
        *listptr=nextnode;
        if(nextnode!=NULL)
        {
            nextnode->prev=NULL;
        }
    }
    else
    {
        prevnode->next=nextnode;
        if(nextnode!=NULL)
        {
            nextnode->prev=prevnode;
        }
    }
    if(nptr->callhistory!=NULL)
    {
        free_contact_history(&nptr->callhistory);
    }
    free(nptr);
}
//deleting a contact matched with number
status_code search_and_delete_based_on_number(contact_list* listpointer)
{
    status_code status=SUCCESS;
    contact_list * listptr=listpointer;
    contact *ptr_personal=listptr->personal;
    contact *ptr_professional=listptr->professional;
    int flag=0;
    int number;
    printf("Enter the mobile number of the contact to be deleted:");
    scanf("%d",&number);
    while(ptr_personal!=NULL&&flag==0)
    {
        
        if(ptr_personal->mobilenumber==number)
        {
            flag=1;
            delete_contact(&listptr->personal,ptr_personal);
        }
        else
        {
            ptr_personal=ptr_personal->next;
        }
    }
    while(ptr_professional!=NULL&&flag==0)
    {
        if(ptr_professional->mobilenumber==number)
        {
            flag=1;
            delete_contact(&ptr_professional,ptr_professional);
        }
        else
        {
            ptr_professional=ptr_professional->next;
        }
    }
    if(flag==0)
    {
        status =FAILURE;
    }
    listpointer=listptr;
    return status;
}
//searching and deleting function
void display_history(calldetails *history_list)
{
    calldetails *ptr=history_list;
    while(ptr!=NULL)
    {
        printf("\nDate:%s\n",ptr->date);
        printf("Duration:%d\n\n",ptr->duration);
        ptr=ptr->next;
    }
}
//display fn to display history
void display_contact(contact *ptr)
{
    printf("\nFirst Name:%s\n",ptr->firstname);
    printf("Last Name:%s\n",ptr->lastname);
    printf("Mobile Number:%d\n",ptr->mobilenumber);
    printf("Email Id:%s\n",ptr->emailid);
    printf("Office Number:%d\n",ptr->officenumber);
    printf("Address:%s\n",ptr->address);
    printf("Call History:\n");
    calldetails *ptr_history=ptr->callhistory;
    display_history(ptr_history);
    printf("\n");
}
//display function to display contact
void display_phone_book(contact_list list, int num_list)
{
    contact_list ptr_list=list;
    contact *ptr_personal=ptr_list.personal;
    contact *ptr_professional=ptr_list.professional;
    if(num_list==1)
    {
        if(ptr_personal==NULL)
        {
            printf("\nNo contacts in personal list\n");
        }
        int flag=0;
        while(ptr_personal!=NULL)
        {
            if(flag==0)
            {
                printf("\nPersonal Phone Book:\n");
                flag=1;
            }
            display_contact(ptr_personal);
            ptr_personal=ptr_personal->next;
        }
    }
    else if(num_list==2)
    {
        int flag=0;
        if(ptr_professional==NULL)
        {
            printf("\nNo contacts in professional list\n");
        }
        while(ptr_professional!=NULL)
        {
            if(flag==0)
            {
                printf("\nProfessional Phone Book:\n");
                flag=1;
            }
            display_contact(ptr_professional);
            ptr_professional=ptr_professional->next;
        }
    }
    else
    {
        int flag=0;
        if(ptr_personal==NULL)
        {
            printf("\nNo contacts in personal list\n");
        }
        while(ptr_personal!=NULL)
        {
            if(flag==0)
            {
                printf("\nPersonal Phone Book:\n");
                flag=1;
            }
            display_contact(ptr_personal);
            ptr_personal=ptr_personal->next;
        }
        if(ptr_professional==NULL)
        {
            printf("\nNo contacts in professional list\n");
        }
        flag=0;
        while(ptr_professional!=NULL)
        {
            if(flag==0)
            {
                printf("\nProfessional Phone Book:\n");
                flag=1;
            }
            display_contact(ptr_professional);
            ptr_professional=ptr_professional->next;
        }
    }
}
//diaplay fn to display phonebook
void search_based_on_number(contact_list list,int number)
{
    int flag=0;
    contact *ptr_personal=list.personal;
    contact *ptr_professional=list.professional;
    while(ptr_personal!=NULL&&flag==0)
    {
        if(ptr_personal->mobilenumber==number)
        {
            printf("\nThis is a contact in personal list\n");
            display_contact(ptr_personal);
            printf("\n");
            flag=1;
        }
        else
        {
            ptr_personal=ptr_personal->next;
        }
    }
    while(ptr_professional!=NULL&&flag==0)
    {
        if(ptr_professional->mobilenumber==number)
        {
            printf("\nThis is a contact in professional list\n");
            display_contact(ptr_professional);
            printf("\n");
            flag=1;
        }
        else
        {
            ptr_professional=ptr_professional->next;
        }
    }
    if(flag==0)
    {
        printf("\nContact not found\n");
    }
    else
    {
        printf("\nContacts searched and displayed\n");
    }
}
//searching based on number
void search_based_on_name(contact_list list,char *fname,char *lname)
{
    int flag=0;
    contact *ptr_personal=list.personal;
    contact *ptr_professional=list.professional;
    while(ptr_personal!=NULL)
    {
        if(strcmp(ptr_personal->firstname,fname)==0&&strcmp(ptr_personal->lastname,lname)==0)
        {
            printf("\nThis is a contact in personal list\n");
            display_contact(ptr_personal);
            printf("\n");
            flag=1;
        }
        ptr_personal=ptr_personal->next;
    }
    while(ptr_professional!=NULL)
    {
        if(strcmp(ptr_professional->firstname,fname)==0&&strcmp(ptr_professional->lastname,lname)==0)
        {
            printf("\nThis is a contact in professional list\n");
            display_contact(ptr_professional);
            printf("\n");
            flag=1;
        }
        ptr_professional=ptr_professional->next;
    }
    if(flag==0)
    {
        printf("\nContact not found\n");
    }
    else
    {
        printf("\nContacts searched and displayed\n");
    }
}
//searching based on name
status_code edit_contact(contact_list* listpointer,int number)
{
    status_code status=SUCCESS;
    contact_list * listptr=listpointer;
    contact *ptr_personal=listptr->personal;
    contact *ptr_professional=listptr->professional;
    int flag=0,select,can_change_order=0;
    while(ptr_personal!=NULL&&flag==0)
    {
        if(ptr_personal->mobilenumber==number)
        {
            display_contact(ptr_personal);
            printf("\n");
            flag=1;
            printf("Enter 1 to edit first name or 2 to skip:");
            scanf("%d",&select);
            if(select==1)
            {
                printf("\nEnter the new first name:");
                scanf("%s",ptr_personal->firstname);
                can_change_order=1;
            }
            printf("Enter 1 to edit last name or 2 to skip:");
            scanf("%d",&select);
            if(select==1)
            {
                can_change_order=1;
                printf("\nEnter the new last name:");
                scanf("%s",ptr_personal->lastname);
            }
            printf("Enter 1 to edit mobile number or 2 to skip:");
            scanf("%d",&select);
            if(select==1)
            {
                can_change_order=1;
                printf("\nEnter the new mobile number:");
                scanf("%d",&ptr_personal->mobilenumber);
            }
            printf("Enter 1 to edit email id or 2 to skip:");
            scanf("%d",&select);
            if(select==1)
            {
                printf("\nEnter the new email id:");
                scanf("%s",ptr_personal->emailid);
            }
            printf("Enter 1 to edit office number or 2 to skip:");
            scanf("%d",&select);
            if(select==1)
            {
                printf("\nEnter the new office number:");
                scanf("%d",&ptr_personal->officenumber);
            }
            printf("Enter 1 to edit address or 2 to skip:");
            scanf("%d",&select);
            if(select==1)
            {
                printf("\nEnter the new address:");
                scanf("%s",ptr_personal->address);
            }
            if(can_change_order==1)
            { 
                contact*prev_node=ptr_personal->prev;
                contact*next_node=ptr_personal->next;
                contact*nptr=ptr_personal;
                if(prev_node!=NULL)
                {
                    prev_node->next=next_node;
                    if(next_node!=NULL)
                    {
                        next_node->prev=prev_node;
                    }
                }
                else
                {
                    listptr->personal=next_node;
                    if(next_node!=NULL)
                    {
                        next_node->prev=NULL;
                    }
                }
                sorted_insert_name(&listptr->personal,nptr);
                listpointer=listptr;
            }
        }
        else
        {
            ptr_personal=ptr_personal->next;
        }
    }
    while(ptr_professional!=NULL&&flag==0)
    {
        if(ptr_professional->mobilenumber==number)
        {
            display_contact(ptr_professional);
            printf("\n");
            flag=1;
            printf("Enter 1 to edit first name or 2 to skip:");
            scanf("%d",&select);
            if(select==1)
            {
                printf("\nEnter the new first name:");
                scanf("%s",ptr_professional->firstname);
                can_change_order=1;
            }
            printf("Enter 1 to edit last name or 2 to skip:");
            scanf("%d",&select);
            if(select==1)
            {
                can_change_order=1;
                printf("\nEnter the new last name:");
                scanf("%s",ptr_professional->lastname);
            }
            printf("Enter 1 to edit mobile number or 2 to skip:");
            scanf("%d",&select);
            if(select==1)
            {
                can_change_order=1;
                printf("\nEnter the new mobile number:");
                scanf("%d",&ptr_professional->mobilenumber);
            }
            printf("Enter 1 to edit email id or 2 to skip:");
            scanf("%d",&select);
            if(select==1)
            {
                printf("\nEnter the new email id:");
                scanf("%s",ptr_professional->emailid);
            }
            printf("Enter 1 to edit office number or 2 to skip:");
            scanf("%d",&select);
            if(select==1)
            {
                printf("\nEnter the new office number:");
                scanf("%d",&ptr_professional->officenumber);
            }
            printf("Enter 1 to edit address or 2 to skip:");
            scanf("%d",&select);
            if(select==1)
            {
                printf("\nEnter the new address:");
                scanf("%s",ptr_professional->address);
            }
            if(can_change_order==1)
            { 
                contact*prev_node=ptr_personal->prev;
                contact*next_node=ptr_personal->next;
                contact*nptr=ptr_personal;
                if(prev_node!=NULL)
                {
                    prev_node->next=next_node;
                    next_node->prev=prev_node;
                }
                else
                {
                    listptr->personal=next_node;
                    if(next_node!=NULL)
                    {
                        next_node->prev=NULL;
                    }
                }
                sorted_insert_name(&listptr->personal,nptr);
                listpointer=listptr;
            }
        }
    }
    if(flag==0)
    {
        printf("\nContact not found\n");
        status=FAILURE;
    }
    return status;
}
//option to edit contact
contact* divide(contact* list)
{
    contact* nptr;
    contact* slow=list;
    contact* fast=list->next;
    while(fast!=NULL&&fast->next!=NULL)
    {
        fast=fast->next;
        fast=fast->next;
        slow=slow->next;
    }
    nptr=slow->next;
    slow->next=NULL;
    nptr->prev=NULL;
    return nptr;
}
//divide fn in merge sort
contact* merge(contact* lptr,contact *nptr)
{
    contact *result;
    contact *ptr1=lptr;
    contact *ptr2=nptr;
    contact *tail;
    int flag=0;
    if(ptr1==NULL)
    {
        result=ptr2;
        flag=1;
    }
    else if(ptr2==NULL)
    {
        result=ptr1;
        flag=1;
    }
    else if((ptr1->mobilenumber<ptr2->mobilenumber))
    {
        result=ptr1;
        ptr1=ptr1->next;
    }
    else
    {
        result=ptr2;
        ptr2=ptr2->next;
    }
    tail=result;
    if(flag==0)
    {
        while(ptr1!=NULL&&ptr2!=NULL)
        {
            if(ptr1->mobilenumber<ptr2->mobilenumber)
            {
                tail->next=ptr1;
                ptr1->prev=tail;
                tail=tail->next;
                ptr1=ptr1->next;
            }
            else
            {
                tail->next=ptr2;
                ptr2->prev=tail;
                tail=tail->next;
                ptr2=ptr2->next;
            }
        }
        if(ptr1!=NULL)
        {    
            tail->next=ptr1;
        }
        else
        {
            tail->next=ptr2;
        }
    }
    return result;
}
//merge fn to merge 2 sorted lists
contact* merge_sort(contact* list)
{
    contact* nptr,*lptr;
    lptr=list;
    if((lptr!=NULL)&&(lptr->next!=NULL))
    {
        nptr=divide(lptr);
        lptr=merge_sort(lptr);
        nptr=merge_sort(nptr);
        lptr=merge(lptr,nptr);
    }
    
    return lptr;
}
//merge sort function for soting the list
void reverse_contacts(contact** list)
{
    contact* prev=NULL;
    contact* curr=*list;
    while(curr!=NULL)
    {
        prev=curr->prev;
        curr->prev=curr->next;
        curr->next=prev;
        curr=curr->prev;
    }
    if(prev!=NULL)
    {
        *list=prev->prev;
    }
}
//reversing the list
status_code insert_contact_based_on_selection(contact_list* contactlist,int selection)
{
    status_code status=SUCCESS,sc2=SUCCESS;
    contact* newcontact;
    contact_list *ptrlist=contactlist;
    contact *ptr_personal=ptrlist->personal;
    contact *ptr_professional=ptrlist->professional;
    newcontact=(contact*)malloc(sizeof(contact));
    if(newcontact==NULL)
    {
        status=FAILURE;
    }
    else
    {
        printf("Enter the first name of the contact:");
        scanf("%s",newcontact->firstname);
        printf("Enter the last name of the contact:");
        scanf("%s",newcontact->lastname);
        printf("Enter the mobile number of the contact:");
        scanf("%d",&newcontact->mobilenumber);
        printf("Enter the email id of the contact:");
        scanf("%s",newcontact->emailid);
        printf("Enter the office number of the contact:");
        scanf("%d",&newcontact->officenumber);
        printf("Enter the address of the contact:");
        scanf("%s",newcontact->address);
        int select=1;
        while(sc2==SUCCESS&&!(select==2))
        {
            printf("Enter 1 to store contact history or 2 to skip:");
            scanf("%d",&select);
            if(select==1)
            {
                sc2=insert_contact_history(&newcontact->callhistory);
                if(sc2==FAILURE)
                {
                    printf("Malloc failed in adding contact history\n");
                }
            }
            else if(select==2)
            {
                sc2=FAILURE;
            }
            else
            {
                printf("Select Valid input\nEnter 1 to store contact history or 2 to skip:");
                scanf("%d",&select);
            }
        }
        if(selection==1)
        {
            if(ptr_personal==NULL)
            {
                newcontact->prev = NULL;
                newcontact->next = NULL;
                ptr_personal=newcontact;
            }
            else
            {
                newcontact->prev = NULL;
                newcontact->next = ptr_personal;
                ptr_personal->prev = newcontact;
                ptr_personal=newcontact;
            }
        }
        else
        {
            if(ptr_professional==NULL)
            {
                newcontact->prev = NULL;
                newcontact->next = NULL;
                ptr_professional=newcontact;
            }
            else
            {
                newcontact->prev = NULL;
                newcontact->next = ptr_professional;
                ptr_professional->prev = newcontact;
                ptr_professional=newcontact;
            }
        }
        ptrlist->personal=ptr_personal;
        ptrlist->professional=ptr_professional;
        contactlist=ptrlist;
    }
    return status;
}
//inserting in personal /professional based on selection
void remove_duplicate(contact * list)
{
    int flag=0;
    contact *current = list;
    contact *next = NULL;
    if(current==NULL)
    {
        flag=1;
    }
    while(current->next!=NULL)
    { 
        if(current->mobilenumber==current->next->mobilenumber)
        { 
            next=current->next->next;
            free(current->next);
            current->next=next;
            if(next!=NULL)
            {
                next->prev=current->next;
            }
            
        }
        else
        { 
            current=current->next;
        }
    }
}
//remove duplicate fn
void freecontactbook(contact_list * contactlist)
{
    contact_list *ptr=contactlist;
    contact *ptr_personal=ptr->personal;
    contact *ptr_professional=ptr->professional;
    contact *ptr_personal_prev;
    contact *ptr_professional_prev;
    while(ptr_personal!=NULL)
    {
        ptr_personal_prev=ptr_personal;
        ptr_personal=ptr_personal->next;
        free_contact_history(&ptr_personal_prev->callhistory);
        free(ptr_personal_prev);
    }
    while(ptr_professional!=NULL)
    {
        ptr_professional_prev=ptr_professional;
        ptr_professional=ptr_professional->next;
        free_contact_history(&ptr_professional_prev->callhistory);
        free(ptr_professional_prev);
    }
    ptr->personal=NULL;
    ptr->professional=NULL;
    contactlist=ptr;
}
//freeing up contact book fn to de allocate memory
long int get_total_time(database *data)
{
    long int total_time=0;
    contact_list ptr=data->contactlist;
    contact *ptr_personal=ptr.personal;
    contact *ptr_professional=ptr.professional;
    while(ptr_personal!=NULL)
    {
        while(ptr_personal->callhistory!=NULL)
        {
            total_time=total_time+ptr_personal->callhistory->duration;
            ptr_personal->callhistory=ptr_personal->callhistory->next;
        }
        ptr_personal=ptr_personal->next;
    }
    while(ptr_professional!=NULL)
    {
        while(ptr_professional->callhistory!=NULL)
        {
            total_time=total_time+ptr_professional->callhistory->duration;
            ptr_professional->callhistory=ptr_professional->callhistory->next;
        }
    }
    return total_time;
}
//fn to get total time user had a conversation
void sorted_insert_time(database **data,database *nptr)
{
    database *ptr=*data;
    int flag=0;
    while(ptr!=NULL&&flag==0)
    { 
        if(ptr->total_time<nptr->total_time)
        {
            nptr->next=ptr;
            nptr->prev=ptr->prev;
            ptr->prev->next=nptr;
            ptr->prev=nptr;
            flag=1;
        }
        else
        {
            ptr=ptr->next;
        }
    }
    if(flag==1)
    {    
        database* prev_node=ptr->prev;
        if(prev_node==NULL)
        { 
            *data=nptr;
            nptr->next=ptr;
            ptr->prev=nptr;
        }
        else
        {
            prev_node->next=nptr;
            nptr->prev=prev_node;
            nptr->next=ptr;
            ptr->prev=nptr;
        }
    }
    else
    {
        ptr=*data;
        while(ptr->next!=NULL)
        {
            ptr=ptr->next;
        }
        ptr->next=nptr;
        nptr->prev=ptr;
    }
}
//sorted insert of phone book based on time spent in conversation
void add_phonebook(database ** datalist)
{
    database *ptr=*datalist;
    database *newnode=(database*)malloc(sizeof(database));
    if(newnode==NULL)
    {
        printf("Malloc failed in adding phonebook\n");
    }
    else
    {
        printf("Enter the name of the phonebook owner:");
        scanf("%s",newnode->name);
        int choice=1;
        while(choice!=2)
        { 
            printf("Enter 1 to add contacts or 2 to stop:");
            scanf("%d",&choice);
            if(choice==1)
            {
                status_code sc=Insert_the_newcontact(&newnode->contactlist);
            }
            else if(choice!=2)
            {
                printf("Select Valid input\nEnter 1 to add contacts or 2 to stop:");
            }
        }
        newnode->total_time=get_total_time(newnode);
        newnode->next=NULL;
        newnode->prev=NULL;
        if(ptr==NULL)
        {
            newnode->next=NULL;
            newnode->prev=NULL;
            ptr=newnode;
        }
        else
        {
            sorted_insert_time(&ptr,newnode);
        }
    }
    *datalist=ptr;
}
//creating adding new phone book
void print_database(database *data)
{
    database* ptr=data;
    if(ptr==NULL)
    {
        printf("Database is empty\n");
    }
    else
    {
        while(ptr!=NULL)
        {
            printf("Name of the owner:%s-----Total time they spent in speaking to others:%ld\n",ptr->name,ptr->total_time);
            ptr=ptr->next;
        }
    }
}
//printing lists of phonebooks

//driver code
int main()
{
    contact_list contactlist;
    initialize_contact_list(&contactlist);
    int select=1;
    while(select!=0)
    {
        printf("\nEnter 1 to create a new contact\nEnter 2 to edit\nEnter 3 to delete\nEnter 4 to search\nEnter 5 to sort\nEnter 6 to display\nEnter 7 to merge 2 sorted inputs\nEnter 8 to remove duplicates\nEnter 9 to Enter database and print names sorted based of call time\nEnter 0 to exit\nEnter the choice:");
        scanf("%d",&select);
        if(select==1)
        {
            status_code sc;
            sc=Insert_the_newcontact(&contactlist);
            if(sc==FAILURE)
            {
                printf("Malloc failed in adding contact\n");
            }
            else
            {
                printf("Contact added successfully\n");
            }
        }
        else if(select == 2)
        {
            int phonenumber;
            printf("Enter the phone number of the contact to be edited:");
            scanf("%d",&phonenumber);
            status_code sc=edit_contact(&contactlist,phonenumber);
            if(sc==SUCCESS)
            {
                printf("Contact edited successfully\n");
            }
        }
        else if(select == 3)
        {
            status_code sc=search_and_delete_based_on_number(&contactlist);
            if(sc==FAILURE)
            {
                printf("Contact not found\n");
            }
            else
            {
                printf("Contact deleted successfully\n");
            }
        }
        else if(select == 4)
        {
            int choice;
            printf("Enter 1 to search based on first name\nEnter 2 to search based on phone number\nEnter the choice:");
            scanf("%d",&choice);
            while(choice!=1 && choice!=2)
            {
                printf("Enter valid input\nEnter 1 to search based on first name and second name\nEnter 2 to search based on phone number\nEnter the choice:");
                scanf("%d",&choice);
            }
           if(choice==2)
           {
               int phonenumber;
                printf("Enter the phone number of the contact to be searched:");
                scanf("%d",&phonenumber);
                search_based_on_number(contactlist,phonenumber);
           }
           else if(choice==1)
           {
               char firstname[20];
               char lastname[20];
               printf("Enter the first name of the contact to be searched:");
               scanf("%s",firstname);
               printf("Enter the last name of the contact to be searched:");
               scanf("%s",lastname);
               search_based_on_name(contactlist,firstname,lastname);
           }
        }
        else if(select == 5)
        {
            contact_list unsorted;
            initialize_contact_list(&unsorted);
            int choice=1;
            while(choice!=2)
            {
                printf("Enter 1 to add new contact\nEnter 2 to exit\nEnter the choice:");
                scanf("%d",&choice);
                if(choice==1)
                {
                    status_code sc=Insert_the_newcontact(&unsorted);
                    if(sc==FAILURE)
                    {
                        printf("Malloc failed in adding contact so stopped\n");
                        choice=2;
                    }
                }
                else if(choice==2)
                {
                    printf("Requested to stop adding contacts\n");
                }
                else
                {
                    printf("Enter valid input\n");
                }
            }
            printf("\nEnter 1 to sort in ascending order\nEnter 2 to sort in descending order\nEnter the choice:");
            scanf("%d",&choice);
            while(choice!=1 && choice!=2)
            {
                printf("Enter valid input\nEnter 1 to sort in ascending order\nEnter 2 to sort in descending order\nEnter the choice:");
                scanf("%d",&choice);
            }
            if(choice==2)
            {
                reverse_contacts(&unsorted.personal);//if descending order then
                reverse_contacts(&unsorted.professional);
            }
            int option;
            printf("\nEnter 1 to display personal contacts\nEnter 2 to display professional contacts\nEnter 3 to display all contacts\nEnter the choice:");
            scanf("%d",&option);
            display_phone_book(unsorted,option);
            freecontactbook(&unsorted);
        }
        else if(select == 6)
        {
            int option;
            printf("\nEnter 1 to display personal contacts\nEnter 2 to display professional contacts\nEnter 3 to display all contacts\nEnter the choice:");
            scanf("%d",&option);
            display_phone_book(contactlist,option);
        }
        else if(select == 7)
        {
            contact_list sorted1,sorted2;
            initialize_contact_list(&sorted1);
            initialize_contact_list(&sorted2);
            printf("Enter the sortedlist1 based on numbers\n");
            int choice=1;
            while(choice!=2)
            {
                printf("Enter 1 to add new contact\nEnter 2 to exit\nEnter the choice:");
                scanf("%d",&choice);
                if(choice==1)
                {
                    printf("Enter 1 to add new contact in personal list\nEnter 2 to add in proffessional list\nEnter the choice:");
                    scanf("%d",&choice);
                    while(choice!=1 && choice!=2)
                    {
                        printf("Enter valid input\nEnter 1 to add new contact in personal list\nEnter 2 to add in proffessional list\nEnter the choice:");
                        scanf("%d",&choice);
                    }
                    status_code sc=insert_contact_based_on_selection(&sorted1,choice);//insert at start
                    choice=0;
                }
                else if(choice==2)
                {
                    printf("Requested to stop adding contacts\n");
                }
                else
                {
                    printf("Enter valid input\n");
                }
            }
            printf("\nEnter the sorted list2 based on numbers\n");
            choice=1;
            while(choice!=2)
            {
                printf("Enter 1 to add new contact\nEnter 2 to exit\nEnter the choice:");
                scanf("%d",&choice);
                if(choice==1)
                {
                    printf("Enter 1 to add new contact in personal list\nEnter 2 to add in proffessional list\nEnter the choice:");
                    scanf("%d",&choice);
                    while(choice!=1 && choice!=2)
                    {
                        printf("Enter valid input\nEnter 1 to add new contact in personal list\nEnter 2 to add in proffessional list\nEnter the choice:");
                        scanf("%d",&choice);
                    }
                    status_code sc=insert_contact_based_on_selection(&sorted2,choice);//insert at start
                    choice=0;
                }
                else if(choice==2)
                {
                    printf("Requested to stop adding contacts\n");
                }
                else
                {
                    printf("Enter valid input\n");
                }
            }
            reverse_contacts(&sorted1.personal);//as inputs are insert at start reversing them
            reverse_contacts(&sorted1.professional);
            reverse_contacts(&sorted2.personal);
            reverse_contacts(&sorted2.professional);
            contact_list merged;
            merged.personal=merge(sorted1.personal,sorted2.personal);//merging the two sorted lists
            merged.professional=merge(sorted1.professional,sorted2.professional);
            printf("The merged list sorted based on numbers is : \n");
            display_phone_book(merged,3);
        }
        else if(select == 8)
        {
            contact_list sorted1;
            initialize_contact_list(&sorted1);
            printf("Enter the sortedlist1\n");
            int choice=1;
            while(choice!=2)
            {
                printf("Enter 1 to add new contact\nEnter 2 to exit\nEnter the choice:");
                scanf("%d",&choice);
                if(choice==1)
                {
                    printf("Enter 1 to add new contact in personal list\nEnter 2 to add in proffessional list\nEnter the choice:");
                    scanf("%d",&choice);
                    while(choice!=1 && choice!=2)
                    {
                        printf("Enter valid input\nEnter 1 to add new contact in personal list\nEnter 2 to add in proffessional list\nEnter the choice:");
                        scanf("%d",&choice);
                    }
                    status_code sc=insert_contact_based_on_selection(&sorted1,choice);//inserted at start
                    choice=0;
                }
                else if(choice==2)
                {
                    printf("Requested to stop adding contacts\n");
                }
                else
                {
                    printf("Enter valid input\n");
                }
            }
            reverse_contacts(&sorted1.personal);//as inputs are insert at start reversing them
            reverse_contacts(&sorted1.professional);
            printf("The lists after removing duplicates:\n");
            if(sorted1.personal!=NULL)
            {
                remove_duplicate(sorted1.personal);
            }
            if(sorted1.professional!=NULL)
            {
                remove_duplicate(sorted1.professional);
            }
            display_phone_book(sorted1,3);//displaying all contacts
        }
        else if(select == 9)
        {
            database *data;
            data=NULL;
            int choice=1;
            while(choice!=2)
            { 
                printf("\nEnter 1 to add a new phonebook\nEnter 2 to stop adding phonebooks\nEnter the choice:");
                scanf("%d",&choice);
                while(choice!=1&&choice!=2)
                {
                    printf("Enter valid input\nEnter 1 to add a new phonebook\nEnter 2 to stop adding phonebooks\nEnter the choice:");
                    scanf("%d",&choice);
                }
                if(choice==1)
                {
                    add_phonebook(&data);
                }
            }
            print_database(data);
        }
        else if(select==0)
        {
            freecontactbook(&contactlist);
            printf("Exiting the phone book\n");
        }
        else
        {
            printf("Enter valid input\n");
        }
    }
}
