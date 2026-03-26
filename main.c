#include <stdio.h>
#include "contact.h"

int main() {
    int choice;
    AddressBook addressBook;
   initialize(&addressBook); // Initialize the address book

    do {
        printf(WHITE"\nAddress Book Menu:\n"RESET);
        printf(CYAN"1. Create contact\n"RESET);
        printf(CYAN"2. Search contact\n"RESET);
        printf(CYAN"3. Edit contact\n"RESET);
        printf(CYAN"4. Delete contact\n"RESET);
        printf(CYAN"5. List all contacts\n"RESET);
        printf(CYAN"6. Exit\n"RESET);
        printf(YELLOW"Enter your choice: \n"RESET);
        scanf("%d", &choice);
        getchar();
        
 
   
        switch (choice) {
            case 1:
                createContact(&addressBook);
                break;
            case 2:
                searchContact(&addressBook);
                break;
            case 3:
                editContact(&addressBook);
                break;
            case 4:
                deleteContact(&addressBook);
                break;
            case 5:
                printf(MAGENTA"Select sort criteria:\n"RESET);
                printf(MAGENTA"1. Sort by name & print\n"RESET);
                printf(MAGENTA"2. Sort by phone & print \n"RESET);
                printf(MAGENTA"3. Sort by email & print\n"RESET);
                printf(YELLOW"Enter your choice: "RESET);
                int sortChoice;
                scanf("%d", &sortChoice);
                listContacts(&addressBook, sortChoice);
                break;
            case 6:
                printf(WHITE"Saving and Exiting...\n"RESET);
                saveContactsToFile(&addressBook);
                break;
            default:
                printf(RED"Invalid choice ❌ Please try again.\n"RESET);
        }
    } while (choice != 6);
    
       return 0;
}
