// resultstack[] is array of Orders
// start and end are start/end dates
// plantprod is production rate of the plant
// length is the length of resultstack

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <time.h>
#include <math.h>

struct Date { //YYYY-MM-DD
    int year; 
    int month;
    int day; 
};

struct Order {

    char order_id[100][100];
	char name[100][100];
	struct Date order_due[100];
	int quantity[100];
    // order_id, name, order_due and quantity has synchronized indexes.
	char order_id_by_date[100][100];
	int production_by_date[100];
    // each element in order_id_by_date and production_by_date corresponds to one day
  	struct Date startorder;
	struct Date endorder;
	char plant;
};

int datetoday(int y, int m, int d){
    m = (m + 9) % 12; 
    y = y - m/10; 
    return 365*y + y/4 - y/100 + y/400 + (m*306 + 5)/10 + ( d - 1 ); 
    // when counting difference between 2 dates, add 1
}


int getplantvalue(char plant){
    if (plant == 'X') return 300;
    else if (plant == 'Y') return 400;
    else if (plant == 'Z') return 500;
}

// char* filldatelist(struct Date start, struct Date end, int totaldays) {
//     int y = start.year;
//     int m = start.month;
//     int d = start.day;
//     char date[10] = "";
//     char datelist[100][10]; // ex: 2020-01-01 is 10 chars, max amount of days in addPERIOD is assumed to be 100



//     for(int i = 0; i < totaldays; i++){ // iterate day, update year & month
//         sprintf(date, "%d-%d-%d", y, m, d);

//         strcpy(datelist[i], date);
        
//         d++;

//         if(d > 31){
//             if((m == 1) || (m == 3) || (m == 5) || (m == 7) || (m == 8) || (m == 10) || (m == 12)){
//                 m++;
//                 d = 1;
//                 if (m > 12){ // new year
//                     y++;
//                     m = 1;
//                 }
//             }
//         }

//         if(d > 30) {
//             if((m == 4) || (m == 6) || (m== 9) || (m == 11)){
//                 m++;
//                 d = 1;
//             }
//         }

//         if((y%4 == 0) && (y%400 == 0) && (y%100 == 0)){ // y is a leap year (mod is 0 when divided by 4 AND 400 AND 100)
//             if ((d > 29) && (m == 2)) { // feb 30 @ leap year
//                 m++;
//                 d = 1;
//             }
//         }

//         else if ((y%4 == 0) && (y%100 != 0) && (y%400 != 0)){ // y is a leap year (mod is 0 when divided by 4 AND (NOT 400) AND (NOT 100))
//             if ((d > 29) && (m == 2)) { // feb 30 @ leap year
//                 m++;
//                 d = 1;
//             }
//         }
        
//         else { // y is not a leap year
//             if ((d > 28) && (m == 2)) { // feb 29 @ non-leap year
//                 m++;
//                 d = 1;
//             }
//         }
//     }

// }

void OutputModule(struct Order resultstack, char* alg){

    char NA[2] = "NA";
    char curr_order_id[100];
    char curr_name[100];
    int synchronized_index;
    char order_due_str[10];
    char datelist[100][10]; // MAX_NUMBER_OF_DAYS = 100
    char datelist_element[10];
    int startday, endday, totaldays;
    char startdate[10];
    char enddate[10];
    int y = resultstack.startorder.year;
    int m = resultstack.startorder.month;
    int d = resultstack.startorder.day;


    sprintf(startdate, "%d-%d-%d", resultstack.startorder.year, resultstack.startorder.month, resultstack.startorder.day);
    sprintf(enddate, "%d-%d-%d", resultstack.endorder.year, resultstack.endorder.month, resultstack.endorder.day);

    printf("Plant_%c (%d per day) \n", resultstack.plant, getplantvalue(resultstack.plant) );
    printf("%s to %s \n \n", startdate, enddate);

    printf("Date    Product_Name    Order_Number    Quantity(Produced)  Due_Date \n");

    startday = datetoday(resultstack.startorder.year, resultstack.startorder.month, resultstack.startorder.day);
    endday = datetoday(resultstack.endorder.year, resultstack.endorder.month, resultstack.endorder.day);
    totaldays = endday - startday + 1; // +1 to include last day
    //printf("totaldays is %d \n", totaldays);

    // fill datelist with datelist_element
    for(int i = 0; i < totaldays; i++){ // iterate day, update year & month
        sprintf(datelist_element, "%d-%d-%d", y, m, d);

        strcpy(datelist[i], datelist_element);
        
        d++;

        if(d > 31){
            if((m == 1) || (m == 3) || (m == 5) || (m == 7) || (m == 8) || (m == 10) || (m == 12)){
                m++;
                d = 1;
                if (m > 12){ // new year
                    y++;
                    m = 1;
                }
            }
        }

        if(d > 30) {
            if((m == 4) || (m == 6) || (m== 9) || (m == 11)){
                m++;
                d = 1;
            }
        }

        if((y%4 == 0) && (y%400 == 0) && (y%100 == 0)){ // y is a leap year (mod is 0 when divided by 4 AND 400 AND 100)
            if ((d > 29) && (m == 2)) { // feb 30 @ leap year
                m++;
                d = 1;
            }
        }

        else if ((y%4 == 0) && (y%100 != 0) && (y%400 != 0)){ // y is a leap year (mod is 0 when divided by 4 AND (NOT 400) AND (NOT 100))
            if ((d > 29) && (m == 2)) { // feb 30 @ leap year
                m++;
                d = 1;
            }
        }
        
        else { // y is not a leap year
            if ((d > 28) && (m == 2)) { // feb 29 @ non-leap year
                m++;
                d = 1;
            }
        }
    }


    for (int i = 0; i < totaldays; i++){

        strcpy(curr_order_id, resultstack.order_id_by_date[i]); // GET curr_order_id

        if ( strcmp(curr_order_id, NA) == 0 ){
            strcpy(curr_name, NA);
            strcpy(order_due_str, NA);
        }
        else {
            // GET synchronized_index
            for(int j = 0; j < 100; j++){
                if( strcmp(curr_order_id, resultstack.order_id[j]) == 0 ) {
                    synchronized_index = j;
                    break;
                }
            }

            // GET curr_name
            strcpy(curr_name, resultstack.name[synchronized_index]);

            // convert Date resultstack.order_due[synchronized_index] to String order_due_str
            sprintf(order_due_str,"%d-%d-%d", resultstack.order_due[synchronized_index].year, resultstack.order_due[synchronized_index].month, resultstack.order_due[synchronized_index].day);
        }
        // print & iterate datelist through each line for Date
        // print & iterate name through each line for Product_Name
        // print & iterate order_id_by_date through each line for Order_Number
        // print & iterate production_by_date through each line for Quantity(Produced)
        // print & iterate order_due through each line for Due_Date

        printf("%s %s %s %d %s \n", datelist[i], curr_name, resultstack.order_id_by_date[i], resultstack.production_by_date[i], order_due_str);

        
    }
  

}

int main(){
    // assume MAX_NUMBER_OF_DAYS = 100
    // assume MAX_NUMBER_OF_ORDERS = 100
    // ORDER_ID_LENGTH = 100
    // get resultstack from part 2
    struct Order resultstack;
    struct Date start[20];
    struct Date end[20];
    int length;
    char alg[10]; // name of alg as String

    // dummy values 
    resultstack.startorder.year = 2020;
    resultstack.startorder.month = 5;
    resultstack.startorder.day = 24;
    resultstack.endorder.year = 2020;
    resultstack.endorder.month = 5;
    resultstack.endorder.day = 30;

    char order_id_dummy[10] = "P0001";
    strcpy(resultstack.order_id[0], order_id_dummy);
    char name_dummy[100] = "Product_A";
    strcpy(resultstack.name[0], name_dummy);
    resultstack.order_due[0].year = 2020;
    resultstack.order_due[0].month = 5;
    resultstack.order_due[0].day = 25;
    strcpy(resultstack.order_id_by_date[0], order_id_dummy);
    resultstack.production_by_date[0] = 300;
    resultstack.plant = 'X';

    
    OutputModule(resultstack, alg);


}
