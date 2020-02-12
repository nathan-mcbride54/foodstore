#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <fcntl.h>

#define TRUE 1
#define FALSE 0

void display();

int main(int argc, char *argv[]) {
    
    int item_list;

    if(argc < 2) {
        printf("This program requires an item list, exiting...\n");
        exit(1);
    }

    if((item_list=open(argv[2], O_RDONLY)) == -1) {
        printf("Could not open item list, exiting...\n");    
        exit(1);
    } else {
        printf("File opened");
    }

    struct sku {
        char description[40];
        char unitofmeasure[15];
        float price;
    } sku_record;


return 0;
}

void display() {
    
    printf("===================================================================\n");
    printf("                      Welcome to Food Mart!                        \n");
    printf(" Date:                                                             \n");
    printf("                        Unit of        Unit       # of    Extended \n");
    printf(" Description            Measure        Price      items     Price  \n");
    printf(" ------------           -------        -----      -----    ------- \n");
    

    printf("       Thank you for purchasing X items from our fine store.       \n");
    printf("                        Have a great day eh?                       \n");
    printf("===================================================================\n");
}
