#ifndef CONTACT_H                            // prevent multiple inclusion of same header file
#define CONTACT_H
#define MAX_CONTACTS 100                     // maximum contacts that can be saved

/*Structure (a box that holds related data) to store single contact info*/
typedef struct 
{
    char name[50];                            // persons name
    char phone[20];                           // persons phone no
    char email[50];                           //persons email
} Contact;

/* Structure to store list of many contacts & a count of how many there are*/
typedef struct 
{
    Contact contacts[100];                      // array (list) of Contact structures
    int contactCount;                           // number of contacts currently stored
} AddressBook;

/* Function declarations (only prototypes - actual code is in contact.c files) */
void initialize(AddressBook*addressBook);        // load contacts from file
void createContact(AddressBook *addressBook);    // add new contact
void listContacts(AddressBook *addressBook);     // show all contacts
void saveContactsToFile(AddressBook *addressBook);

int searchbyname(AddressBook *addressBook, char *name);    // find contact by name
int searchbyphone(AddressBook *addressBook, char *phone);  // find contact by phone no
int searchbymail(AddressBook *addressBook, char *email);   // find contact by email
void searchContact(AddressBook *addressBook);              // find contact

void editbyname(AddressBook *addressBook, char *name);     // change contact by name
void editbyphone(AddressBook *addressBook);                // change contact by phone
void editbymail(AddressBook *addressBook);                 // change contact by email
void editContact(AddressBook *addressBook);                // change contact

void deleteContact(AddressBook *addressBook);               // remove contact
void deletebyname(AddressBook *addressBook, char *name);    // remove contact by name
void deletebyphone(AddressBook *addressBook, char *phone);  // remove contact by ph no
void deletebymail(AddressBook *addressBook, char *email);   // remove contact by email
void confirmation(AddressBook *addressBook, int i);         // confirmation 

#endif                                                      // end of header protection
