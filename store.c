#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>

#define TRUE 1
#define FALSE 0
#define database "/home/COIS/3380/lab2/grocery_items.db"

void display();

int main(int argc, char *argv[]) {
    
    int fd_item_list;

    if(argc < 2) {
        printf("This program requires an item list, exiting...\n");
        exit(1);
    }

    if((fd_item_list=open(argv[1], O_RDONLY)) == -1) {
        printf("Could not open item list, exiting...\n");    
        exit(1);
    } else {
        printf("File opened: %s\n", argv[1]);
    }

    int last_byte = lseek(fd_item_list, 0, SEEK_END);
    int position;
    char vals[512];
    for (position = 0; position <= last_byte; ++position) {
        int curr_byte = lseek(fd_item_list, position, SEEK_SET);
        read(fd_item_list, &vals[position], curr_byte);
    }

    printf("READ: %s\n", &vals);

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
