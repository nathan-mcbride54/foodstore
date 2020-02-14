//====================================================================
// Name: FoodStore
//
// Written By: Nathan McBride
//
// Purpose: To read item information from a file and print data from an associated database.
//
// Usage: ./foodstore # Path to item list
//    eg: ./foodstore /home/COIS/3380/lab2/item_list_1.txt
//
// Description of parameters: argv[1] - The item list being read
//
//====================================================================
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <fcntl.h>
#include <string.h>

// Path to the database file
#define DATABASE "/home/COIS/3380/lab2/grocery_items.db"

// This function prints the current time using printf
void currentTime();

// Reads the item list file to query the db file
// Prints the information of the struct from the db using printf
int printItems(FILE *item_list, FILE *db);

// Number of items purchased
int itemsPurchased = 0;

// Total price of the item list
float totalPrice = 0.0;

// This struct is used to read information from the database
struct sku {
    char description[40];
    char unitOfMeasure[15];
    float price;
}; 

// This struct encapsulates the sku and relates it to an id and quantity
struct item {
    struct sku info;
    int quantity;
    int id;
};

int main(int argc, char *argv[]) {

    // Check if the user supplied a item list
    if(argc < 2) {
        printf("This program requires an item list, exiting...\n");
        exit(1);
    }

    // Open the item list for reading
    FILE *item_list;
    item_list = fopen (argv[1], "r");
    if(item_list == NULL) {
        // Exit with error if item list read failed
        fprintf(stderr, "Could not open item list, exiting...\n");    
        exit(-1);
    }

    // Open the database for reading
    FILE *db;
    db = fopen (DATABASE, "r");
    if(db == NULL) {
        // Exit with error if database read failed
        fprintf(stderr, "Could not open database, exiting...\n");
        exit(-1);
    } 

    printf("=====================================================================================\n\n");
    printf("                             Welcome to the Food Store!                              \n");
    currentTime();
    printf("                                        Unit of        Unit       # of    Extended   \n");
    printf(" Description                            Measure        Price      items     Price    \n");
    printf(" -----------                            -------        -----      -----    -------   \n");
    printItems(item_list, db);
    printf("							            ---------------                                  \n");
    printf("								     Total: %.2f                                         \n\n",totalPrice);
    printf("              Thank you for purchasing %d items from our fine store.                  \n",itemsPurchased);
    printf("                            Have a great day eh?                                      \n");
    printf("======================================================================================\n");

    // Close the files before exiting
    fclose(item_list);
    fclose(db);
    return 0;
}


int printItems(FILE *item_list, FILE *db) {

    // Read until an eof character is reached
    while(!feof(item_list))
    {
        // Read the character from the item list
        char ch = fgetc(item_list);

        // Check if's a newline character
        if(ch == '\n')
        {
            // Increment the number of items purchased
            itemsPurchased++;
        }
    }
    // Set the seek back to the top of the file
    rewind(item_list);

    // Iterate over the file based on the number of rows
    int counter;
    for(counter = 0; counter < itemsPurchased; counter++) {

        // Initialize an empty struct for the current item
        struct item currItem = {{"", "", 0.0}, 0, 0};

        // Scan a row of the file into the structs id and quantity
        fscanf(item_list, "%d %d", &currItem.id, &currItem.quantity);

        // Locate the position of the struct in the db by multiplying the id by the width of the struct in memory
        int db_index = currItem.id * sizeof(struct sku);

        // Move to the position in the database to read the struct
        fseek(db, db_index, SEEK_SET);

        // Read the sku struct into the current item
        fread(&currItem.info, sizeof(struct sku), 1, db);

        // Print out the item information
        printf(" %-40s", currItem.info.description);
        printf("%-15s", currItem.info.unitOfMeasure);
        printf("%-12.2f", currItem.info.price);
        printf("%-8d", currItem.quantity);
        printf("%-15.2f\n", currItem.quantity * currItem.info.price);

        // Increase the total price by the value of the current item
        totalPrice = totalPrice + currItem.info.price;
    }
}

// Taken from: https://stackoverflow.com/questions/1442116/how-to-get-the-date-and-time-values-in-a-c-program
void currentTime() {

    // Set the time variable to be right now
    time_t t = time(NULL);

    // Add the time information to a struct for easy manipulation
    struct tm time = *localtime(&t);

    printf(" Date: %d-%02d-%02d %02d:%02d\n", time.tm_year + 1900, time.tm_mon + 1, time.tm_mday, time.tm_hour, time.tm_min);
}
