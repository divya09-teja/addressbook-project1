#include <stdio.h>                  // Standard input/output
#include <stdlib.h>                 // Standard library for general functions
#include <string.h>                 // string functions(strcmp,strcpy,etc)
#include<ctype.h>                   // character checks (isalpha,strcpy,etc)
#include "contact.h"                // include our own header file(contains structs,prototypes)
#include "file.h"                   // another custom header

/* Fuction  to prints all saved contacts with serial number. */
void listContacts(AddressBook *addressBook) 
{
    // Sort contacts based on the chosen criteria
    printf("\n---------------- LIST OF CONTACTS ----------------\n");
    printf("\n%s\t %s\t %s\t %s\n","S.NO","NAME","Ph.NO","Email");
    // loop through every contact and print details
    for (int i = 0; i <addressBook->contactCount&& addressBook->contactCount< 100; i++)  
    {
        printf("%d\t %s\t %s\t %s\n",i+1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }
}
void initialize(AddressBook *addressBook)
{
    FILE *fp = fopen("contacts.txt", "r");   // open file for reading
    addressBook->contactCount = 0;           // start contact count at 0

    // if (fp == NULL)                          
    // {
    //     printf(" ERROR in opening file"\n");
    //     return;                             
    // }

    // Read each line: name, phone, email (3 fields separated by commas)
    while (fscanf(fp, "%[^,],%[^,],%[^\n]\n",
                  addressBook->contacts[addressBook->contactCount].name,
                  addressBook->contacts[addressBook->contactCount].phone,
                  addressBook->contacts[addressBook->contactCount].email) == 3)
    {
        addressBook->contactCount++;          // count increases after each contact

        if (addressBook->contactCount >= MAX_CONTACTS)
            break;                            // stop if list is full
    }

    fclose(fp);                              // close file
    printf("%d contacts loaded successfully from file.\n", addressBook->contactCount);
}

/* Check validity of phone number */
int checkphone(AddressBook*addressBook,char*phone) //Function definition To check valid ph or not(10 digits & unique)
{
    int count=0;
    for(int i=0;phone[i]!='\0';i++)
    {
        count++;
        if(!isdigit(phone[i])) //isdigit is built-in function to check given string is contain only digits or not
        {
            return 0;
        }
    }
    if(count!=10)   // Check if phone number Must be exactly 10 digits
    {
        return 0;
    }
    for (int i = 0; i < addressBook->contactCount; i++) // Check if phone number already exists
    {
        if (!strcmp(addressBook->contacts[i].phone, phone))  //strcmp is built-in function to compare to strings
        {
            return 0;
        }
    }
    return 1;  // Valid phone number
}

/* Check validity of email ID */
int checkEmail(AddressBook *addressBook, char *email) 
{
    int Count = 0;
    int len = strlen(email);

    // Must end with ".com"
    if (strcmp(email + len - 4, ".com") != 0) // if last 4 characters aren't .com - invalid
    {
        return 0;
    }

    // Check every character
    for (int i = 0; i < len; i++) 
    {
        if (isupper(email[i]))      // if any uppercase letter is found - invalid
        {
            return 0;   // No uppercase letters
        } 
        if (email[i] == '@')        // count how many @ symbols appear
        {
            Count++;    // Count '@' symbols
        }
    }

    // Must contain exactly one '@'
    if (Count != 1)
    {
        return 0;
    }

    // Must be unique (not already in AddressBook)
    for (int i = 0; i < addressBook->contactCount; i++) 
    {
        if (strcmp(addressBook->contacts[i].email, email) == 0)
            return 0;
    }

    return 1;  // Valid email
}

/* Create a new contact */
//(ask user for name,ph,mail-validates them-saves contact if confirmed.)
void createContact(AddressBook *addressBook)
{
    Contact newcontact;                                              // temporary variable to hold new data          
    printf("ENTER CONTACT NAME:");                                   // ask for name
	scanf(" %[^\n]",newcontact.name);                                // read name with spaces

    if(!isalpha(newcontact.name[0]))
    {
        printf("Enter a valid name");
        return;
    }
    printf("ENTER PHONE NUMBER: ");                                  // ask for phone
    scanf("%s",newcontact.phone);                                    // read phone number
    if(!checkphone(addressBook,newcontact.phone))
    {
        printf("Enter a valid phone number");
        return;
    }
    printf("ENTER EMAIL ID: ");                                       // ask for email
    scanf("%s",newcontact.email);                                     // read email id
    if(!checkEmail(addressBook,newcontact.email))
    {
        printf("Enter a valid mail");
        return;
    }
    printf("ENTER OPTION:\n1. SAVE CONTACT\n2. CANCEL SAVING CONTACT\n");
    int option;
    scanf("%d",&option);
    switch(option)
    {
        case 1:
        // add this new contact to address book array
        addressBook->contacts[addressBook->contactCount] = newcontact;
        addressBook->contactCount++;                                 // increase total contact count by 1
        printf("CONTACT SAVED SUCCESSFULLY.");
        break;
        case 2:
        printf("CONTACT NOT SAVED.");
        break;
        default:
        printf("ENTER A VALID OPTION.");  
        
    }
}

/* Function to display all contacts that match a given name */
void displayMatchingContacts(AddressBook *addressBook, char *name) 
{
    printf("\n---- Matching Contacts ----\n");
    printf("%s\t %s\t %s\t %s\t\n","S.NO","NAME","PHONE","EMAIL");  // print column titles
    int count = 0; 
    // Loop through every contact in the address book
    for (int i = 0; i < addressBook->contactCount; i++) 
    {
        // check if contact name is exactly same as the given name
        if (!strcmp(addressBook->contacts[i].name, name)) 
        {
            // Print details of the contact that matches
            printf("%d\t %s\t %s\t %s\t\n",i + 1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
            count++;    // increase the match counter
        }
    }
    if (count == 0)   // if no contact matched the given name, show message
    {
        printf("No matching contacts found.\n");
    }
    printf("----------------------------\n");
}

/*--- SEARCH FUCTION ---*/
/* ------SEARCH BY NAME ---*/ //find & display matching contact.
int searchbyname(AddressBook *addressBook,char *name)
{
    int count=0;
    // go through every contact stored in the address book
    for(int i=0;i<addressBook->contactCount;i++)
    {
        // check if the current contact name exactly matches the given name
        if(!strcmp(addressBook->contacts[i].name, name))      // strcmp returns 0 if both names are same    
        {
            count++;   // increase the number of matches found
            // Print the contact details (Name, Phone, Email)
            printf("%s %s %s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
        }
    }
    // if no matching contact found, show message
    if(count==0)
    {
        printf("CONTACT IS NOT FOUND.");                     // if no match found
    }
    // if more than one contact has the same name, show them all clearly
    else if(count>1)
    {
        printf("MULTIPLE CONTACTS FOUND WITH NAME %s :\n",name);
        displayMatchingContacts(addressBook,name);    // call another function to show all matches neatly
    }
    return count;                   // Send back how many matches were found

}

/* ----- SEARCH BY PHONE NO -----*/           //find & display matching contact.
int searchbyphone(AddressBook *addressBook,char *phone)
{
    // Go through every contact in the address book
    for(int i=0;i<addressBook->contactCount;i++)
    {
        // Check if the given phone number matches this contact's phone
        if(!strcmp(addressBook->contacts[i].phone, phone))           // strcmp returns 0 when both are same
        {
            printf("%s %s %s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
            return i;                  // Return the position (index) of the found contact
        }
    }
    printf("Contact is NOT Found.\n");              // if no match found
    return -1;       //Return -1 to show that no contact was found
}

/* ------ SEARCH BY MAIL ID  ------ */ //find & display matching contact.
int searchbymail(AddressBook *addressBook,char *email)
{
    // Loop through each saved contact
    for(int i=0;i<addressBook->contactCount;i++)
    {
        // Check if the given email matches this contact's email
        if(!strcmp(addressBook->contacts[i].email, email))
        {
            printf("%s %s %s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
            return i;     // Return index of the matching contact
        }
    }
    printf("Contact is NOT Found.\n");                       // if no match found
    return -1;                                              // Return -1 meaning no contact found
}

/* ------- MENU TO SEARCH CONTACTS -------- */ // Lets user choose how they want to search (name/phone/email)
void searchContact(AddressBook *addressBook) 
{
    Contact searchcontact;             // Temporary contact to hold search input
    int option;
    printf("ENTER A OPTION TO SEARCH CONTACT:\n1. SEARCH BY NAME\n2. SEARCH BY PHONE NUMBER\n3. SEARCH BY EMAIL\n");
    scanf("%d",&option);    // Take the user's choice
    // Do different actions based on user's option
    switch(option)
    {
        case 1:
        printf(" ENTER NAME TO SEARCH: ");
        scanf(" %[^\n]",searchcontact.name);              // Take full name input
        searchbyname(addressBook,searchcontact.name);    // Call name search function
        break;
        case 2:
        printf(" ENTER PHONE NUMBER TO SEARCH: ");
        scanf("%s",searchcontact.phone);                   // Take phone no input
        searchbyphone(addressBook,searchcontact.phone);    // Call phone search function
        break;
        case 3:
        printf(" ENTER EMAIL ID TO SEARCH: ");
        scanf("%s",searchcontact.email);                   // Take email input
        searchbymail(addressBook,searchcontact.email);    // Call email search function
        break;
        default:
        printf("invalid option");
    }
}

/* edi contacts*/
void editContact(AddressBook *addressBook)
{
    Contact searchcontact;
    int option;
    printf("ENTER A OPTION TO EDIT  CONTACT:\n1. EDIT BY NAME\n2. EDIT BY PHONE NUMBER\n3. EDIT BY EMAIL\n");
    scanf("%d",&option);
    switch(option)
    {
        case 1:
        printf(" ENTER NAME TO SEARCH: ");
        scanf(" %[^\n]",searchcontact.name);
        editbyname(addressBook,searchcontact.name);
        break;
        case 2:
        printf(" ENTER PHONE NUMBER TO SEARCH: ");
        //scanf("%s",searchcontact.phone);
        editbyphone(addressBook);
        break;
        case 3:
        printf(" ENTER EMAIL ID TO SEARCH: ");
        editbymail(addressBook);
        break;
        default:
        printf("invalid option");
    }
}

/* ---EDIT FUCTIONS with confirmation ---*/ //updates 1 specific contact(confirmation).
void editdetails(AddressBook *addressBook, int i)
{
    Contact newdetails;  //Temporary structure to store new info
    int option;
    printf("ENTER OPTION TO EDIT:\n1.EDIT NAME\n2.EDIT PHONE NUMBER\n3.EDIT MAIL\n");
    scanf("%d",&option);
    switch(option)
    {
        case 1:
        printf("ENTER A NEW NAME: ");
        scanf(" %[^\n]",newdetails.name);
        if(!isalpha(newdetails.name[0]))                // Check if the first character is an alphabet
        {
            printf("ENTER A VALID NAME\n");
            return;                                      // Stop if invalid
        }
        strcpy(addressBook->contacts[i].name,newdetails.name);            // Copy new name to the contact list
        printf("CONTACT UPDATED SUCCESSFULLY");
        break;
        case 2:
        printf("ENTER A NEW PHONENUMBER: ");
        scanf(" %s",newdetails.phone);
        if(!checkphone(addressBook,newdetails.phone))            //Check if phone number format is valid and not duplicated
        {
            printf("ENTER A VALID PHONE NUMBER\n");
            return;
        }
        strcpy(addressBook->contacts[i].phone,newdetails.phone);     // Copy new phone number to the contact list
        printf("CONTACT UPDATED SUCCESSFULLY");
        break;
        case 3:
        printf("ENTER A NEW MAIL: ");
        scanf("%s",newdetails.email);
        if(!checkEmail(addressBook,newdetails.email))
        {
          printf("ENTER A VALID MAIL\n");
          return;
        }
       strcpy(addressBook->contacts[i].email,newdetails.email);
       printf("CONTACT UPDATED SUCCESSFULLY");
       break;
       default:
       printf("INVALID OPTION.");
    }
}

/* --- EDIT BY NAME ---*/ //search for a contact & call editcontact.
void editbyname(AddressBook *addressBook,char*name)
{
    int count=searchbyname(addressBook,name);          // Search for contacts with this name
    if(count==0)                                      // If no contact found
    {
        printf("CONTACT IS NOT FOUND.");
        return;
    }
    else if(count==1)                                  // If only one contact found       
    {  
       for(int i=0;i<addressBook->contactCount;i++)
       {
          if(!strcmp(addressBook->contacts[i].name,name))                 
          {
            printf("CONTACT IS FOUND.\n");
            editdetails(addressBook,i);                  // Call function to edit that contact                     
            return;
          }
       }
    }
    else  // If multiple contacts have same name
                       
    { 
        printf("MULTIPLE CONTACTS DETECTED.");
        displayMatchingContacts(addressBook,name);
        // Ask user to choose another way to identify contact
        printf("\n CHOOSE ANOTHER OPTION:\n1.PHONE NUMBER\n2.EMAIL ID\n");
        int option;
        scanf("%d",&option);
        switch(option)
        {
            case 1:
            editbyphone(addressBook);          // Search again using phone no
            break;
            case 2:
            editbymail(addressBook);          // Search again using email
            break;
            default:
            printf("INVALID OPTION.");
        }
    }

}

/* --- EDIT BY PHONE NO --- */ // Finds contact using phone number and edits it
void editbyphone(AddressBook *addressBook)
{
    char phone[20];              // To store the phone number entered by use
    printf("\nENTER A PHONENUMBER: ");
    scanf("%s",phone);
    int i=searchbyphone(addressBook,phone);        // Search for contact with this phone number
    if(i!=-1)                                      // If contact found, call edit function
    {
        editdetails(addressBook,i);
        return;
    }       
}

/* --- EDIT BY MAIL ID ---*/ //search for a contact & call editcontact.
void editbymail(AddressBook *addressBook)
{
    char email[50];                                      // To store the email entered by user
    printf("\nENTER A EMAIL: ");
    scanf("%s",email);                                    //Search for contact with this email ID
    int i=searchbymail(addressBook,email);
    if(i!=-1)                                             // If found, open editing options
    {
        editdetails(addressBook,i);
        return;
    }
}

/* --- DELETE FUCTIONS with confirmation ---*/ 
void deleteContact(AddressBook *addressBook)              // Lets the user delete a contact safely after confirmation
{
	Contact deletecontact;                                // Temporary contact to store user input
    int option;                                           // User's choice of how to delete
    printf("Delete by: \n1.DELETE NAME\n2.DELETE PHONE NUMBER\n3.DELETE EMAIL ID\n");     // Show menu to choose how the user wants to delete
    scanf("%d",&option);
    switch(option)
    {
        case 1:                                           // Delete using name
        printf(" ENTER NAME TO SEARCH: ");
        scanf(" %[^\n]",deletecontact.name);
        deletebyname(addressBook,deletecontact.name);     // Call function to delete by name
        break;
        case 2:                                           // Delete using phone number
        printf(" ENTER PHONE NUMBER TO DEETE: ");
        scanf("%s",deletecontact.phone);
        deletebyphone(addressBook,deletecontact.phone);      // Call function to delete by phone
        break;
        case 3:                                                //Delete using email
        printf(" ENTER EMAIL ID TO DELETE: ");
        scanf("%s",deletecontact.email);
        deletebymail(addressBook,deletecontact.email);        // Call function to delete by email
        break;
        default:
        printf("invalid option");
    }
}
/* Menu for deleteing a contact */  // Final step to confirm before deleting  
void confirmation(AddressBook *addressBook,int i)
{
    // Ask user if they really want to delete this contact
	printf("ENTER OPTION:\n1. DELETE CONTACT\n2. CANCEL DELETING CONTACT\n");
    int option;
    scanf("%d",&option);
    switch(option)
    {
        case 1:              // If user confirms deletion
        // Move all contacts one step up to remove selected contact
        for(int j=i;j<addressBook->contactCount;j++)
        {
            addressBook->contacts[j]=addressBook->contacts[j+1];
        }
        addressBook->contactCount--;                       // Reduce total count by 1
        printf("CONTACT DELETED SUCCESSFULLY."); 
        break;
        case 2:                                           // If user cancels deletion
        printf("CONTACT NOT DELETED.");
        break;
        default:
        printf("ENTER A VALID OPTION");
    }  

}

/*-------DELETE BY NAME ------*/ //Finds a contact by name and deletes it (with confirmation)
void deletebyname(AddressBook *addressBook,char*name)
{
    int count=searchbyname(addressBook,name);                  // Find contacts with this name
    if(count==0)                                               // If no matching contact found
    {
        printf("CONTACT IS NOT FOUND.");
        return;
    }
    else if(count==1)                                          // If only one contact found
    {
       for(int i=0;i<addressBook->contactCount;i++)           // find matching contact
       {
          if(!strcmp(addressBook->contacts[i].name,name))      // Match found
          {
            printf("CONTACT IS FOUND.\n");
            confirmation(addressBook,i);                     // Ask user for delete confirmation            
            return;
          }
       }
    }
    else                                                   // If multiple contacts have same name 
    {
        printf("MULTIPLE CONTACTS DETECTED.");
        printf("\nCHOOSE ANOTHER OPTION:\n1.PHONE NUMBER\n2.EMAIL ID\n");
        int option;
        scanf("%d",&option);
        char input[60];                                     //Temporary variable for user input
        switch(option)
        {
            case 1:                                        // If user chooses to delete by phone
            {
                printf("ENTER PHONE NUMBER :");
                scanf("%s",input);
                deletebyphone(addressBook,input);           // Call delete by phone (pass argument)
                break;
            }
            case 2:                                          // If user chooses to delete by email
            {
                printf("ENTER EMAIL :");
                scanf("%s",input);
                deletebymail(addressBook,input);               // Call delete by email (pass argument)
                break;
            }
            default:
            printf("INVALID OPTION.");
        }
    }

}

/*-------DELETE BY PHONE NO ------*/ // Finds a contact by phone and deletes it(with confirmation).
void deletebyphone(AddressBook *addressBook,char *phone)
{
    int i=searchbyphone(addressBook,phone);                      // Search for matching phone number
    if(i != -1)                                                  // If contact found
    {
        confirmation(addressBook, i);                            // Ask for delete confirmation
        return;
    }  
}

/*-------DELETE BY EMAIL ID ------*/ // Finds a contact by email and deletes it (with confirmation)
void deletebymail(AddressBook *addressBook,char *email)
{
    int i=searchbymail(addressBook,email);                        // Search for matching email ID
    if(i != -1)                                                  // If contact found
    {
        confirmation(addressBook, i);                           // Ask for delete confirmation
        return;
    }  
}


