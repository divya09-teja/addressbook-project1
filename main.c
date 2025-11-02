#include <stdio.h>         // for printing text & reading user input
#include "contact.h"       // include our header file where all functions & structures are declared

/* ----------------------------- MAIN FUNCTION ----------------------------- */
int main()                   // every C program starts from here
{
    int choice;                  // variable to store user menu choice
    AddressBook addressBook;     // create address book variable to hold contacts

    initialize(&addressBook);    // load all old contacts from file (contacts.txt)
    
    do                           // start a loop to keep showing menu again & again
    {
        printf("\n=============================ADDRESS BOOK MENU:=========================================\n");
        printf("1. Create contact\n");        // add new contact
        printf("2. Search contact\n");        // find a contact
        printf("3. Edit contact\n");          // update existing contact
        printf("4. Delete contact\n");        // remove a contact
        printf("5. List all contacts\n");     // show all contacts
        printf("6. Save \n");                 // save all contacts to file
        printf("7. Exit without Saving\n");   //  just exit without saving
        printf("=============================================================================\n");
        printf("Enter your choice: ");        // ask user for choice
        scanf("%d", &choice);                 // read user choice

        // check user choice using switch-case
        switch (choice) 
        {
            case 1:                                          // if user pressed 1
                createContact(&addressBook);                 // call function to add new contact
                break;                                       // exit switch 

            case 2:                                          // if user pressed 2
                searchContact(&addressBook);                 // call function to find contact
                break;                                       

            case 3:                                           // if user pressed 3                                   
                editContact(&addressBook);                   // call function to edit contact
                break;

            case 4:                                           // if user pressed 4                
                deleteContact(&addressBook);                  // call function to delete contact
                break;

            case 5:                                            // if user pressed 5
                listContacts(&addressBook);                   // call function to show all contacts
                break;

            case 6:                                             // if user pressed 6
                printf("Saving contact\n");                    // save all contacts to contacts.txt file
                saveContactsToFile(&addressBook);
                break;
 
            case 7:                                             // if user pressed 7
                printf(" Exiting...\n"); 

            default:                                            // if user entered something else
                printf("Invalid choice. Please try again.\n");
        }// end of switch
    } 
    while (choice != 7);                                         // repeat menu until user chooses 7
    
    return 0;                                                    // end of main function

} // end of program

