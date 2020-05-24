#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

// testing
// testing github againn

struct Date{ 
    int day; 
    int year; 
    int month;
};

struct Order{
    char *order_id;
    char *name; 
    struct Date order_due; 
    int quantity;
};

/*
Plant x = 300 per day
Plant y = 400 per day
Plant z = 500 per day

==== What do I need 
*/
int main(){
    int datetoday(int y, int m, int d);

    printf("***PLS Schedule Analysis Report***\n");
    char *alg = "SJF"; // change if neede
    int date1[3];
    int date2[3];
    
    printf("\nAlgorithm used: %s\n", alg);

    /* 
    ---------- This part is not needed anymore since the date is already parsed -------------- 
    char test[] = "2020-05-06"; // change the date to the date input 
    char test2[] = "2020-05-10";
    char *temp; 
    int n = 0; 
    
    char *ptr = strtok(test, "-");
    
    while(ptr){
        // printf("%s ", ptr);
        date1[n++] = atoi(ptr);
        ptr = strtok(NULL, "-");
    }

    char *ptr2 = strtok(test2, "-");
    n = 0;
    printf("\n");
    while(ptr2){
        // printf("%s ", ptr2);
        date2[n++] = atoi(ptr2);
        ptr2 = strtok(NULL, "-");
    }

    */

    // put the above code to a for loop
    // int valid[][] //not sure how many spaces needed, for the valid processes
    // order is valid if the number of day x plant capability <= order amt 
    int diff = datetoday(date1[0], date1[1], date1[2]) - datetoday(date2[0], date2[1], date2[2]);
    // printf("the difference between date 2  and date 1 is %d  \n", diff);
    printf("%-20s %-15s %-10s %-8s %-12s %-12s\n", "ORDER NUMBER", "START", "END", "DAYS", "QUANTITY", "PLANT");
    printf("=================================================================================\n");
}

int datetoday(int y, int m, int d){
    m = (m + 9) % 12; 
    y = y - m/10; 
    return 365*y + y/4 - y/100 + y/400 + (m*306 + 5)/10 + ( d - 1 );
}
