#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>


int datetoday(int y, int m, int d){
    m = (m + 9) % 12; 
    y = y - m/10; 
    return 365*y + y/4 - y/100 + y/400 + (m*306 + 5)/10 + ( d - 1 ); 
}

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


void AnalysisModule (struct Order resultx, struct Order resulty, struct Order resultz, struct Order rejectedstack, char* alg, int accepted, int rejected) {
    printf("***PLS Schedule Analysis Report*** \n");
    printf("Algorithm used: %s \n", alg);
    printf("There are %d orders ACCEPTED. Details are as follows: \n", accepted);
    printf("ORDER_NUMBER    START   END     DAYS    QUANTITY    PLANT \n");

    for(int i = 0; i < accepted; i++){
        
    }

}

int main() {
    struct Order resultx, resulty, resultz, rejectedstack;
    char alg[10];
    int accepted, rejected;
    AnalsysisModule(resultx, resulty, resultz, rejectedstack, alg, accepted, rejected);
}

