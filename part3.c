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
	char process_by_date[100][100];
	int production_by_date[100];
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

char* filldatelist(struct Date start, struct Date end) {
    int y = start.year;
    int m = start.month;
    int d = start.day;
    char date[10] = "";
    char datelist[100][10]; // ex: 2020-01-01 is 10 chars, max amount of days in addPERIOD is assumed to be 100
    int startday, endday, totaldays;

    startday = datetoday(start.year, start.month, start.day);
    endday = datetoday(end.year, end.month, end.day);
    totaldays = startday - endday + 1; // +1 to include last day


    for(int i = 0; i < totaldays; i++){ // iterate day, update year & month
        sprintf(date, "%d-%d-%d", y, m, d);

        datelist[i] = date;
        
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

}

void OutputModule(struct Order resultstack, struct Date start, struct Date end, int length, char* alg){
    printf("Plant_%c (%d per day) \n", resultstack.plant, getplantvalue(resultstack.plant) );

    printf("%s to %s \n", start, end);

    printf("Date    Product_Name    Order_Number    Quantity(Produced)  Due_Date");

    int curr_order;
    char* datelist[];

    datelist = filldatelist(start, end);
  
    // print & iterate datelist through each line for Date
    // print & iterate name through each line for Product_Name
    // print & iterate process_by_date through each line for Order_Number
    // print & iterate production_by_date through each line for Quantity(Produced)
    // print & iterate order_due through each line for Due_Date
  

}

int main(){
    // assume max number of days is 100
    // get resultstack from part 2
    struct Order resultstack;
    struct Date start[20];
    struct Date end[20];
    int length;

    OutputModule(resultstack, start, end, length);


}

