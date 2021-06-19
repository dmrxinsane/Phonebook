#include <stdio.h>
#include <string.h>


/* [BIG BUG FIX]: Declare file pointer Globally, or Declare file pointer in main() function will only solve the problem
Do no declare the FILE pointers inside the functions that are created*/
/* Successfully Compiled: But Program Crash at adding function at user_prompt */
//May need the addition of dynamic memory allocation????



/* !!!!!!!!!!! GLOBAL FILE POINTER VARIABLES DECLARED HERE !!!!!!!!!!!*/

FILE *static_pointer=NULL;
FILE *num_view_search=NULL;
FILE *namepointer=NULL;
FILE *addresspointer=NULL;
FILE *viewpointer=NULL;
FILE *printingpointer = NULL;
FILE *address_pointer = NULL;





/*Add Section*/ /*Contents entered Display purpose Only */
int adddisplay(char *name, char *num, char *email, char *nick)
{
    printf("The Details Entered Are\nName:%s\tNumber:%s\tEmail:%s\tNick:%s\n", name, num, email, nick);
}

int contactcreate(char *name, char *num, char *email, char *alias)
{
    // FILE *namepointer;
    // FILE *addresspointer;
    // FILE *viewpointer;

    //Making a dummy for name.txt file
    char *name_text[5];
    name_text[0] = name;
    strcat(name_text[0], ".txt");

    //Making a dummy for address.txt file
    char *address_text[3];
    address_text[0] = num;
    strcat(address_text[0], ".txt");

    //Static variable for noting the amount of contacts added
    static int count;
    count++;

    //Viewing Section code
    viewpointer = fopen("viewme.txt", "a+");
    fprintf(viewpointer, "%s", name);
    putc(' ', viewpointer);
    fclose(viewpointer);

    //Address Section Code
    addresspointer = fopen(address_text[0], "w+");
    fprintf(addresspointer, "%s", name);
    fclose(address_pointer);

    //Name Pointer Code
    namepointer = fopen(name_text[0], "w+");
    fprintf(namepointer, "%s", name); //Check the Bug occurance of can't implement full name
    fputc(' ', namepointer);
    fprintf(namepointer, "%s", num);
    fputc(' ', namepointer);
    fprintf(namepointer, "%s", email);
    fputc(' ', namepointer);
    fprintf(namepointer, "%s", alias);
    fclose(namepointer);
}

int searchsection(char *name, char *address_name_user)
{

    // FILE *printingpointer = NULL;
    // FILE *address_pointer = NULL;
    char *name_dummy[5];
    char contact_name[100];
    char number[15];
    char email[100];
    char alias[100];
    char choice_search;
    char *address_text[5];
    char name_copy[100];

    address_text[1] = address_name_user;
    strcat(address_text[1], ".txt");

    name_dummy[0] = name;

    strcat(name_dummy[0], ".txt");
    printingpointer = fopen(name_dummy[0], "r");

    if (printingpointer != NULL)
    {
        fscanf(printingpointer, "%s", contact_name);
        fscanf(printingpointer, "%s", number);
        fscanf(printingpointer, "%s", email);
        fscanf(printingpointer, "%s", alias);
    }

    else if (printingpointer == NULL)
    {
        printf("File not Found\nDo you want to search by Address?\nEnter Y to Proceed\n");
        scanf("%c", &choice_search);

        if (choice_search == 'Y' || choice_search == 'y')
        {
            address_pointer = fopen(address_text[1], "r");

            fscanf(address_pointer, "%s", name_copy);

            if (address_pointer != NULL)
            {

                fscanf(address_pointer, "%s", name_copy);
                strcat(name_copy, ".txt");
                //Create a DSA algorithm here for taking first name from the full name
                printingpointer = fopen(name_copy, "r");
                fscanf(printingpointer, "%s", contact_name);
                fscanf(printingpointer, "%s", number);
                fscanf(printingpointer, "%s", email);
                fscanf(printingpointer, "%s", alias);
                fclose(printingpointer);
            }

            else
            {
                printf("File Not Found\n");
            }

            fclose(address_pointer);
        }
        else
        {
            printf("File Not Found\n");
        }
    }

    fclose(printingpointer);
    printf("Name:%s\tNumber:%s\tEmail:%s\tNick:%s\n", contact_name, number, email, alias);
}

int view()
{
    // FILE *static_pointer;
    // FILE *num_view_search;
    int loop_static;
    char number_view[15];
    char *num_view_array[20];

    static_pointer = fopen("staticstoring.txt", "r");
    fscanf(static_pointer, "%d", loop_static);
    fclose(static_pointer);
    num_view_search = fopen("viewme.txt", "r");
    for (int i = 0; i < loop_static; i++)
    {
        fscanf(num_view_search, "%s", num_view_array[i]);
        // num_view_array[i] = number_view;
    }

    for (int i = 0; i < loop_static; i++)
    {
        printf("%s", num_view_array[i]);
    }
    fclose(num_view_search);
}

int main()
{
    //Add section
    char name[100];
    char number[15];
    char email_address[100];
    char alias[100];
    int user_choice_menu;
    char user_prompt;
    int search_sec_choice;

    printf("Welcome to Phonebook\n");
    while (user_choice_menu != 0)
    {
        printf("Enter 1 To Add Contact:\n");
        printf("Enter 2 to Search Contact\n");
        printf("Enter 3 To View Contacts\n");
        scanf("%d", &user_choice_menu);
        getchar();
        if (user_choice_menu == 1)
        {
            printf("Enter Name of the Contact:\n");
            gets(name);
            printf("Enter Contact Number:\n");
            gets(number);
            printf("Enter email:\n");
            gets(email_address);
            printf("Enter Alias:\n");
            gets(alias);
            //Add viewing function call
            adddisplay(name, number, email_address, alias);
            //User_Choice/Prompt:
            printf("Are you sure, you wan't to save changes\nEnter Y to accept, Enter N to decline\n");
            scanf("%c", &user_prompt);
            //User_Prompt entry action:
            if (user_prompt == 'Y' || user_prompt == 'y')
            {
                printf("Contact Created:\n");
                contactcreate(name, number, email_address, alias);
            }
            else
            {
                printf("Entries declined");
            }
        }

        else if (user_choice_menu == 2)
        {   
            printf("Enter Name of the Contact:\n");
            gets(name);
            //Search Section:
            printf("Enter 1 to search by name.....");
            scanf("%d", &search_sec_choice);
            //Add section/Contact creation section is done
            //All the pointers are made to create and store
            if (search_sec_choice == 1)
            {
                searchsection(name, number);
            }
        }
        else if (user_choice_menu == 3)
        {
            //View Section:
            printf("Viewing.....\n");
            // scanf("%d", &search_sec_choice);
            // if (search_sec_choice == 'Y' || search_sec_choice == 'y')
            // {
            //     view();
            // }
            view();
        }
    }

    return 0;
}
