#include <stdio.h>
//#include <stdio_ext.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "address_book.h"
#include "address_book_menu.h"

//#include "abk_fileops.h"
//#include "abk_log.h"
//#include "abk_menus.h"
//#include "abk.h"

// all of these functions are in the context of the Console Menu

int get_option(int type, const char *msg)
{
	printf("%s", msg);

    int ret = 0;
	if (type == NONE) {
		scanf("%c", &ret);
	}
	else if (type == NUM) {
		scanf("%d", &ret);
	}
    else if (type == CHAR) {
        scanf("%c", &ret);
    }
    return ret;
	/*
	 * Mutilfuction user intractions like
	 * Just an enter key detection
	 * Read an number
	 * Read a charcter
	 */ 

	/* Fill the code to add above functionality */
}

// 																							This function, when called, prompts the user if he wants to save.
// 																							It returns a "status"; prompt successful? failed? so on
Status save_prompt(AddressBook *address_book)												// what does save_prompt do??
{
	char option;																			// option?

	do
	{
		main_menu();																		//prints the main menu

		option = get_option(CHAR, "\rEnter 'N' to Ignore and 'Y' to Save: ");				// option = response to "Y/N"

		if (option == 'Y')																	// if "Y" response; save file, and give feedback: "saving your data in the DEFAULT_FILE"
		{
			save_file(address_book);
			printf("Exiting. Data saved in %s\n", DEFAULT_FILE);

			break;
		}
	} while (option != 'N');																// and we just keep doing this									
// 																							while the response isnt "NO"
	free(address_book->list);																// afterwards, it free's the information from memory; it's now stored in a file

	return e_success;
}

// 																							When called this lists all the contacts in the address book in the console
Status list_contacts(AddressBook *address_book, const char *title, int *index, const char *msg, Modes mode)
{
	/* 
	 * Add code to list all the contacts availabe in address_book.csv file
	 * Should be menu based
	 * The menu provide navigation option if the entries increase the page size
	 */ 

	return e_success;
}

//																							this just prints out a "header". this is just for it to look cool
void menu_header(const char *str)
{
	fflush(stdout);

	system("clear");

	printf("#######  Address Book  #######\n");
	if (str != '\0')
	{
		printf("#######  %s\n", str);
	}
}

//																							prints out the main_menu
void main_menu(void)
{
	menu_header("Features:\n");

	printf("0. Exit\n");
	printf("1. Add Contact\n");
	printf("2. Search Contact\n");
	printf("3. Edit Contact\n");
	printf("4. Delete Contact\n");
	printf("5. List Contacts\n");
	printf("6. Save\n");
	printf("\n");
	printf("Please select an option: ");
}

// 																							runs all the logic for the menu
// 
Status menu(AddressBook *address_book)
{
	ContactInfo backup;							// ??
	Status ret;									// the status of the function; success, fail etc
	int option;									// the user input

	do
	{
		main_menu();							// prints main menu

		option = get_option(NUM, "");			// asks for input; expecting an int to be returned s

		if ((address_book-> count == 0) && (option != e_add_contact))	// if the address book it got has no contacts, and the user doesn't want to add a contact, then:
		{
			get_option(NONE, "No entries found!!. Would you like to add? Use Add Contacts");	// just waiting for the user to press "enter"

			continue;
		}

		switch (option)														// "if: then" for all the possible inputs the user could do
		{
			case e_add_contact:												// the code to add a contact
				/* Add your implementation to call add_contacts function here */
				break;
			case e_search_contact:											// the code to search for a contact
				search_contact(address_book);
				break;
			case e_edit_contact:											// so on
				edit_contact(address_book);
				break;
			case e_delete_contact:
				delete_contact(address_book);
				break;
			case e_list_contacts:
				break;
				/* Add your implementation to call list_contacts function here */
			case e_save:
				save_file(address_book);
				break;
			case e_exit:
				break;
		}
	} while (option != e_exit);

	return e_success;
}

Status add_contacts(AddressBook *address_book)
{
	int option;
	char name[NAME_LEN] = "";
	char number[NUMBER_LEN] = "";
	char email[EMAIL_ID_LEN] = "";
	do {
		// printing out the Add Contact menu
		menu_header("Add Contact:");
		printf("0. Back		   \n");
		printf("1. Name		  : %s\n", name);		
		printf("2. Phone No 1 : %s\n", number);
		printf("3. Email ID 1 : %s\n", email);

		//get user input
		option = get_option(NUM, "Please select an option: ");

		switch (option) {
			case e_second_opt:
				fgets(name, NAME_LEN, stdin);	//gets the input and limits the buffer to NAME_LEN so there's no overflow.
				break;
			case e_third_opt:
				fgets(number, NUMBER_LEN, stdin);
				break;
			case e_fourth_opt:
				fgets(email, EMAIL_ID_LEN, stdin);
				break;
			case e_exit:
				break;
		}

	} while (option != e_exit);

	if (name != "") strcpy(address_book->list->name[0][0], name);
	if (number != "") strcpy(address_book->list->phone_numbers[0][0], number);
	if (email != "") strcpy(address_book->list->email_addresses[0][0], email);

	return e_success;
} 

Status search(const char *str, AddressBook *address_book, int loop_count, int field, const char *msg, Modes mode)
{
	/* Add the functionality for adding contacts here */
}

Status search_contact(AddressBook *address_book)
{
	/* Add the functionality for search contacts here */
}

Status edit_contact(AddressBook *address_book)
{
	/* Add the functionality for edit contacts here */
}

Status delete_contact(AddressBook *address_book)
{
	/* Add the functionality for delete contacts here */
}
