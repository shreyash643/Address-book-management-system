#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<ctype.h>
#include "contact.h"
#include "file.h"
#include <stdio_ext.h>




void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0;
   // populateAddressBook(addressBook);
    
   
   loadContactsFromFile(addressBook);
}


int uniqe(char*estr,AddressBook *addressBook)
{
  for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (strcasecmp(addressBook->contacts[i].email, estr) == 0)
        {
            return 1; 
        }
    }
    return 0;
}

int validemail(char*estr,AddressBook *addressBook)      
{
   if(uniqe(estr,addressBook))
   {
    printf(RED"❌ Email is already saved to other contact\n please enter unique email\n"RESET);
    return 0;
   }
  int posa=0;
  int posd=0;
  int len =strlen(estr);
  if(estr[0]=='.'||estr[0]=='@')
  {
    return 0;
  }
   if (len<5 ||strncmp(estr + len - 4, ".com", 4) != 0)
   {
        return 0;
   }

  for(int i=0;i<len;i++)
  {
    if(estr[i]=='@'&&estr[i+1]!='.')
    {
          posa=i;
    }
    if(estr[i]=='.'&&posa!=0)
    {
      posd=i;
    }
    
  }
  if(posa<posd&&posa!=0 &&posd!=0)
  {
    return 1;
  }
  return 0;
}


  int uniqn(char*arr1,AddressBook*addressBook)
  {
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (strcasecmp(addressBook->contacts[i].phone, arr1) == 0) // if numbers are same than return 1 
        {
            return 1; 
        }
    }
    return 0;
    
  }
int validnum(char *arr1,AddressBook*addressBook)
{
  if(uniqn(arr1,addressBook))
   {
    printf(RED"❌ Number is already saved to other contact\n please enter unique Number\n"RESET);
    return 0;
   }
  int len = strlen(arr1);
  if(len!=10)
  {
    return 0;
  }
  if(len==10)
  {
    for(int i=0;i<10;i++)
    {

           if(!isdigit(arr1[i]))      
           {
            return 0;
           }
    }
    return 1;
     
  }
  else
  {
    return 0;
  }
  
   
}

int validname(char*str)         // this loop is used for cheack the given name is valid or not   
{
  int len =strlen(str);
  
    
  
    for(int i=0;i<len;i++)
    {
       if (!isalpha(str[i])&& str[i]!='.'&&str[i]!=' ')
       {
        return 0;
       }
    }
    return 1;

}

void createContact(AddressBook *addressBook)
{      
  char name[20];
  printf(YELLOW"Enter name: "RESET);

    while (1)
  {
     scanf(" %19[^\n]", name);

     if(validname(name))
      { 
        break;
      }
      else
      {
        printf(RED"Enter valid name: "RESET);
      }
  }
 
  char number[12];
printf(YELLOW"Enter mobile number:\n"RESET);
  while(1)
  {
    scanf(" %[^\n]",number);
    if(validnum(number,addressBook))
    {
        break;
    }
    else
    {
        printf(RED"Enter valid number: "RESET);
    }
  }
  char estr[50];
  printf(YELLOW"Enter Email: "RESET);
  while (1)
  {
    scanf("  %[^\n]", estr);

    if(validemail(estr,addressBook))
    {
      break;
    }
    printf(RED"Enter valid email:\n"RESET);
    
  }
  
  strcpy(addressBook->contacts[addressBook->contactCount].name,name);
  strcpy(addressBook->contacts[addressBook->contactCount].phone,number);
  strcpy(addressBook->contacts[addressBook->contactCount].email,estr);

  (addressBook->contactCount)++;


}



int searchname(char*str,AddressBook *addressBook)
{
  int match[100];  //taking one array to store matched contacts
int tmat=0;       // total match

  if((addressBook->contactCount)==0)
{
    printf(MAGENTA"Contact List is Empty ❌"RESET);
    return -1;
}

for(int i=0;i<addressBook->contactCount;i++)
{
 if (strcasestr(addressBook->contacts[i].name, str) != NULL)
  {
   
    
    match[tmat]=i;
    tmat++;

  }
}

if(tmat==0)
{
printf(WHITE"Contact not found\n"RESET);
return -1; 
}

if(tmat==1)
{
  int j=match[0];
      printf(GREEN"\ncontact 1\t"RESET);
      printf(GREEN"%s\t"RESET,addressBook->contacts[j].name);
      printf(GREEN"%s\t"RESET,addressBook->contacts[j].phone);
      printf(GREEN"%s\n"RESET,addressBook->contacts[j].email);
    
  return j;
}


  int choice;

  printf(MAGENTA"\nMultiple match found Select one\n"RESET);
  printf(MAGENTA"Sr.No.\tName\tNumber\tEmail id\n"RESET);
  for(int i=0;i<tmat;i++)
  {
    int j=match[i];
    printf(GREEN"\ncontact %d\t"RESET,i+1);
      printf(GREEN"%s\t"RESET,addressBook->contacts[j].name);
      printf(GREEN"%s\t"RESET,addressBook->contacts[j].phone);
      printf(GREEN"%s\n"RESET,addressBook->contacts[j].email);
    
  }
  while(1)
  {
    printf(YELLOW"Enter your choice :"RESET);
    scanf("%d",&choice);
    getchar();

  if(choice>=1 && choice<=tmat)
  {
    return match[choice-1]; // we did -1 here because we are going to return arrays value that start from 0 
  }
   else
   {
    printf(RED"\nInvalid choice, choice valid option:\n"RESET);
   }
  }


}

int searchnum(char*str,AddressBook *addressBook)
{
   if((addressBook->contactCount)==0)
{
    printf(MAGENTA"Contact List is Empty ❌"RESET);
    return -1;
}

for(int i=0;i<addressBook->contactCount;i++)
{
  if(strcasecmp(addressBook->contacts[i].phone,str)==0)
  {
      printf(GREEN"\n\ncontact %d\n"RESET,i+1);
      printf(GREEN"%s\n"RESET,addressBook->contacts[i].name);
      printf(GREEN"%s\n"RESET,addressBook->contacts[i].phone);
      printf(GREEN"%s\n\n\n"RESET,addressBook->contacts[i].email);
    return i;
  }
}
printf(WHITE"Contact not found\n"RESET);
return -1; 
}

int searchmail(char*str,AddressBook *addressBook)
{
  if((addressBook->contactCount)==0)
{
    printf(MAGENTA"Contact List is Empty ❌"RESET);
    return -1;
}

for(int i=0;i<addressBook->contactCount;i++)
{
  if(strcasecmp(addressBook->contacts[i].email,str)==0)
  {
    printf(GREEN"\n\ncontact %d\n"RESET,i+1);
      printf(GREEN"%s\n"RESET,addressBook->contacts[i].name);
      printf(GREEN"%s\n"RESET,addressBook->contacts[i].phone);
      printf(GREEN"%s\n\n\n"RESET,addressBook->contacts[i].email);
    return i;
  }
}
printf(WHITE"Contact not found\n"RESET);
return -1; 
}

void searchContact(AddressBook *addressBook)
{ int a=0;
  char str[90];
  do{

   
  printf(MAGENTA"\n1.search by name\n2.search by number\n3.search by email\n4.Exit\n"RESET);
  printf(YELLOW"\nEnter your choice:"RESET);
 int op;
  scanf("%d",&op);
  getchar();
  switch(op)
  {
    case 1:
    {
        printf(YELLOW"\nEnter your name:"RESET);

      scanf(" %[^\n]", str);
     a++;
     int in=searchname(str,addressBook);

   
    
    break;
    }
    case 2:
    {
        printf(YELLOW"\nEnter your phone number:"RESET);

        scanf(" %[^\n]", str);
     a++;
     int in=searchnum(str,addressBook);
    
    break;
    }
    case 3:
    {
        printf(YELLOW"\nEnter your email:"RESET);

      scanf(" %[^\n]", str);
     a++;
     int in=searchmail(str,addressBook);
    
    break;
    }
    case 4:
    {
      a++;
      break;
    }
    default:
    printf(RED"Enter valid choice\n"RESET);
    break;

  }
  }while (a==0);
}



void sortbyName(AddressBook *addressBook)
{
    Contact temp;
    int ret;
    for (int i = 0; i < addressBook->contactCount - 1; i++)
    {
        for (int j = i + 1; j < addressBook->contactCount; j++)
        {
            ret = strcasecmp(addressBook->contacts[i].name, addressBook->contacts[j].name);
            // printf("ret =%d\n",ret);
            if (ret > 0)
            {
                temp = addressBook->contacts[i];
                addressBook->contacts[i] = addressBook->contacts[j];
                addressBook->contacts[j] = temp;
            }
        }
    }
}

void sortbyPhone(AddressBook *addressBook)
{
    Contact temp;
    int ret;
    // printf("contact count = %d\n",addressBook->contactCount);
    for (int i = 0; i < addressBook->contactCount - 1; i++)
    {
        for (int j = i + 1; j < addressBook->contactCount; j++)
        {
            ret = strcasecmp(addressBook->contacts[i].phone, addressBook->contacts[j].phone);

            if (ret > 0)
            {
                temp = addressBook->contacts[i];
                addressBook->contacts[i] = addressBook->contacts[j];
                addressBook->contacts[j] = temp;
            }
        }
    }
}

void sortbyEmail(AddressBook *addressBook)
{
    Contact temp;
    int ret;
    // printf("contact count = %d\n",addressBook->contactCount);
    for (int i = 0; i < addressBook->contactCount - 1; i++)
    {
        for (int j = i + 1; j < addressBook->contactCount; j++)
        {
            ret = strcasecmp(addressBook->contacts[i].email, addressBook->contacts[j].email);

            if (ret > 0)
            {
                temp = addressBook->contacts[i];
                addressBook->contacts[i] = addressBook->contacts[j];
                addressBook->contacts[j] = temp;
            }
        }
    }
}

void print(AddressBook *addressBook)
{

    printf(CYAN"Serial No"RESET);
    printf(CYAN"                  Name             "RESET);
    printf(CYAN"       Contact Number        "RESET);
    printf(CYAN"            Email             "RESET);
    printf(CYAN"\n---------------------------------------------------------------------------------------------------\n"RESET);
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        printf(GREEN"%d"RESET, i + 1);
        printf(GREEN"%30s"RESET, addressBook->contacts[i].name);
        printf(GREEN"%30s"RESET, addressBook->contacts[i].phone);
        printf(GREEN"%30s"RESET, addressBook->contacts[i].email);
        printf(CYAN"\n-------------------------------------------------------------------------------------------------\n"RESET);
    }
}

void listContacts(AddressBook *addressBook, int sortCriteria) 
{
 
    if(sortCriteria<1 || sortCriteria>4)
        {
          printf(RED"Invalid choice\n"RESET);
          return;
        }

        switch (sortCriteria)
        {
        case 1:
            sortbyName(addressBook);
                        print(addressBook);

            break;
        case 2:
            sortbyPhone(addressBook);
                        print(addressBook);

            break;
        case 3:
            sortbyEmail(addressBook);
                        print(addressBook);

            break;


        default:
            printf(RED"Invalid choice ❌ Please try again.\n"RESET);
        }

    
}



void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}



void econn(int in,AddressBook*addressBook)
{
  char str[100];
 while(1)
 {
   printf(MAGENTA"\nEnter What you want to edit : \n"RESET);
  printf(MAGENTA"1.Name\n2.phone number\n3.Email\n4.Exit\n\n"RESET);
     printf(YELLOW"Enter your choice: \n"RESET);

  int opt;
  int a=0;
  scanf("%d",&opt);
  printf("\n");
  switch(opt)
  {
    case 1:
    { 
      a++;
      printf(YELLOW"Enter Name: "RESET);
      getchar();
      scanf(" %[^\n]",str);
     int jio=0;
     jio=validname(str);
     
     if(jio==1)
     {
      strcpy(addressBook->contacts[in].name,str);
      printf(CYAN"Contact Edited Suessfully\n"RESET);
     }

      break;
    }
    case 2:
    { 
      a++;
      printf(YELLOW"Enter phone number : "RESET);
      getchar();
      scanf(" %[^\n]",str);
     int jio=0; 
     jio=validnum(str,addressBook);
     
     if(jio==1)
     {
      strcpy(addressBook->contacts[in].phone,str);
      printf(CYAN"Contact Edited Suessfully\n"RESET);
     }
     break;
    }

    case 3:
    { 
      a++;
      printf(YELLOW"Enter Email: "RESET);
      getchar();
      scanf(" %[^\n]",str);
     int jio=0;
     jio=validemail(str,addressBook);
     
     if(jio==1)
     {
      strcpy(addressBook->contacts[in].email,str);
      printf(CYAN"Contact Edited Suessfully\n"RESET);
     }

      break;
    }
    case 4:
    {
      a++;
    }
    default:
    {
      printf(RED"Enter valid choice\n"RESET);
    }
  }
 
  if(a==1)
  {
    break;
  }
}
}

void editContact(AddressBook *addressBook)
{
    
int a=0;
  char str[90];
  do{

   int op;
  printf(MAGENTA"\nSearch contact that you want to Edit\n1.By Name \n2.By Number\n3.By Email\n4.Exit\n"RESET);
  printf(YELLOW"Enter your choice:"RESET);
 
  scanf("%d",&op);
  switch(op)
  {
    case 1:
    {
      printf(YELLOW"Enter name: "RESET);
      scanf(" %[^\n]", str);
     a++;
     int in=searchname(str,addressBook);
     if(in!=-1)
     {
       econn(in,addressBook);
     }
     
    break;
    }
    case 2:
    {
      printf(YELLOW"Enter phone number:"RESET);
      scanf(" %[^\n]", str);
     a++;
     int in=searchnum(str,addressBook);
     if(in!=-1)
     {
       econn(in,addressBook);
     }
     break;
    }
    case 3:
    {
      printf(YELLOW"Enter email:"RESET);
      scanf(" %[^\n]", str);
     a++;
     int in=searchmail(str,addressBook);
     if(in!=-1)
     {
       econn(in,addressBook);
     }
    
    break;
    }
    case 4:
    {
      a++;
      break;
    }
    default:
    printf(RED"Enter valid choice\n"RESET);
    break;

  }
  }while (a==0);
  

 
}



void dconn(int in,AddressBook*addressBook)
{
  int a=0;
  while (1)
  {
    
  
   printf(CYAN"\nDo you want to Delete this contact?\n1.Yes\n2.No\n"RESET);
   int o;
   scanf("%d",&o);
   switch(o)
   {
    case 1:
    {
      for(int i=in;i<(addressBook->contactCount)- 1;i++)
      {
        addressBook->contacts[i]=addressBook->contacts[i+1];
      }
      a++;
      printf(GREEN"Contact Deleted\n"RESET);
      addressBook->contactCount--;
      break;
    }
    case 2:
    {
      a++;
      break;
    }
    default:
    {
      printf(RED"Enter valid choice"RESET);
    }
   }
   if(a!=0)
  {
    break;
  }
}

}

void deleteContact(AddressBook *addressBook)
{
  int a=0;
  char str[90];
  do{

   int op;
  printf(MAGENTA"1.Enter name you want to Delete\n2.Enter number you want to Delete\n3.Enter email you want to Delete\n4.Exit\n"RESET);
  printf(YELLOW"Enter your choice:"RESET);
 
  scanf("%d",&op);
  switch(op)
  {
    case 1:
    {
      printf(YELLOW"Enter name: "RESET);
      scanf(" %[^\n]", str);
     a++;
     int in=searchname(str,addressBook);
     if(in!=-1)
     {
       dconn(in,addressBook);
     }
     
    break;
    }
    case 2:
    {
      printf(YELLOW"Enter phone number:"RESET);
      scanf(" %[^\n]", str);
     a++;
     int in=searchnum(str,addressBook);
     if(in!=-1)
     {
       dconn(in,addressBook);
     }
     break;
    }
    case 3:
    {
      printf(YELLOW"Enter email:"RESET);
      scanf(" %[^\n]", str);
     a++;
     int in=searchmail(str,addressBook);
     if(in!=-1)
     {
       dconn(in,addressBook);
     }
    
    break;
    }
    case 4:
    {
      a++;
      break;

    }
    default:
    printf(RED"Enter valid choice\n"RESET);
    break;

  }
  }while (a==0);
   
}
