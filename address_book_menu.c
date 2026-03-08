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
	if (type == NONE) {
		scanf("%c\n");
	}
	else if (type == NUM) {
		return scanf("%d\n");
	}
	return scanf("%c\n");
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

Status add_contacts(AddressBook *address_book)				// case e_add_contact will call this
{
	// to add a contact -> access address_book
	// increase count + 1
	// create a contact file (???) .csv
	// address_book->list->name = " "
	// address_book->list->phone_number = " "
	// address_book->list->email = " "
	// address_book->list->si_no (what is si_no?)
	// so we need to get name, phone_number, email, and si_no (?) inputted from the console

	
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
