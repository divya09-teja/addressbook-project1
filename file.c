#include <stdio.h>            // for file handling functions
#include "file.h"             // include file header

/* --------------------- SAVE CONTACTS FUNCTION --------------------- */
void saveContactsToFile(AddressBook *addressBook)
{
    FILE *fp = fopen("contacts.txt", "w");     // open file in write mode (creates new or replaces old)

    if (fp == NULL)                            // if file cannot be opened
    {
        printf("Error opening file to save contacts.\n");
        return;                                 // stop function
    }

    // loop through all contacts one by one
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        // write name, phone, and email separated by commas in one line
        fprintf(fp, "%s,%s,%s\n",
                addressBook->contacts[i].name,
                addressBook->contacts[i].phone,
                addressBook->contacts[i].email);
    }

    fclose(fp);                                  // close file after writing
    printf("Contacts saved successfully to file.\n");   
}