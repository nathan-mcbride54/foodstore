#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>

#define TRUE 1
#define FALSE 0
#define DATABASE "/home/COIS/3380/lab2/grocery_items.db"



void display(int itemsPurchased);

struct sku {
    char description[40];
    char unitofmeasure[15];
    float price;
}; 

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
        fprintf(stderr, "Could not open item list, exiting...\n");    
        exit(1);
    } 
    else { printf("File opened: %s\n", argv[1]); }
 

    // Open the database for reading
    FILE *db;
    db = fopen (DATABASE, "R");
    if(db = NULL) {
        fprintf(stderr, "Could not open database, exiting...\n");
        exit(1);
    } 
    else { printf("database opened\n"); }
    
    // Taken from: https://stackoverflow.com/questions/1442116/how-to-get-the-date-and-time-values-in-a-c-program
    time_t t = time(NULL);
    struct tm time = *localtime(&t);
    printf("===================================================================\n");
    printf("                      Welcome to Food Mart!                        \n");
    printf(" Date: %d-%02d-%02d %02d:%02d                                      \n", time.tm_year + 1900, time.tm_mon + 1, time.tm_mday, time.tm_hour, time.tm_min );
    printf("                        Unit of        Unit       # of    Extended \n");
    printf(" Description            Measure        Price      items     Price  \n");
    printf(" ------------           -------        -----      -----    ------- \n");
    
    // Count the number of items being purchased in the list
    int itemsPurchased = 0;
    while(!feof(item_list)){
	char ch = fgetc(item_list);
	if(ch == '\n'){
	    itemsPurchased++;
	}
    }
    rewind(item_list);

 
    int counter;
    for(counter = 0; counter < itemsPurchased; counter++) {
        struct item currItem = {{"", "", 0.0}, 0, 0};
        fscanf(item_list, "%d %d", &currItem.id, &currItem.quantity);
        //printf("curritem.id: %d\ncurritem.quantity: %d\n", currItem.id, currItem.quantity);
	
	int db_index = currItem.id * sizeof(struct sku);
	lseek(db, db_index, SEEK_SET);
	read(db, currItem.info, sizeof(struct sku));

	printf("info.des: %s\ninfo.uom: %s\nprice: %f\n", currItem.info.description, currItem.info.unitofmeasure, currItem.info.price);
 
    } 


    printf("       Thank you for purchasing %d items from our fine store.      \n", itemsPurchased);
    printf("                        Have a great day eh?                       \n");
    printf("===================================================================\n");

    return 0;
}
