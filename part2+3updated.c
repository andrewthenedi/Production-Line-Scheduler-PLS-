#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <time.h>
#include <math.h>

struct Date //YYYY-MM-DD
{
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
int getplantvalue(char plant)
{
	if (plant == 'X') return 300;
	else if (plant == 'Y') return 400;
	else if (plant == 'Z') return 500;
}

int datetoday(int y, int m, int d)
{
	m = (m + 9) % 12;
	y = y - m / 10;
	return 365 * y + y / 4 - y / 100 + y / 400 + (m * 306 + 5) / 10 + (d - 1);
}

void dateinput(struct Date date, int y, int m, int d)
{
	date.year = y;
	date.month = m;
	date.day = d;
}


//--------------------------PRINTING OUTPUT MODULE --------------------------

void OutputModule(struct Order resultstack, char* alg) {

	char *NA = "NA";
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

	printf("Plant_%c (%d per day) \n", resultstack.plant, getplantvalue(resultstack.plant));
	printf("%s to %s \n \n", startdate, enddate);

	printf("Date    Product_Name    Order_Number    Quantity(Produced)  Due_Date \n");

	startday = datetoday(resultstack.startorder.year, resultstack.startorder.month, resultstack.startorder.day);
	endday = datetoday(resultstack.endorder.year, resultstack.endorder.month, resultstack.endorder.day);
	totaldays = endday - startday + 1; // +1 to include last day
	//printf("totaldays is %d \n", totaldays);

	// fill datelist with datelist_element
	for (int i = 0; i < totaldays; i++) { // iterate day, update year & month
		sprintf(datelist_element, "%d-%d-%d", y, m, d);

		strcpy(datelist[i], datelist_element);

		d++;

		if (d > 31) {
			if ((m == 1) || (m == 3) || (m == 5) || (m == 7) || (m == 8) || (m == 10) || (m == 12)) {
				m++;
				d = 1;
				if (m > 12) { // new year
					y++;
					m = 1;
				}
			}
		}

		if (d > 30) {
			if ((m == 4) || (m == 6) || (m == 9) || (m == 11)) {
				m++;
				d = 1;
			}
		}

		if ((y % 4 == 0) && (y % 400 == 0) && (y % 100 == 0)) { // y is a leap year (mod is 0 when divided by 4 AND 400 AND 100)
			if ((d > 29) && (m == 2)) { // feb 30 @ leap year
				m++;
				d = 1;
			}
		}

		else if ((y % 4 == 0) && (y % 100 != 0) && (y % 400 != 0)) { // y is a leap year (mod is 0 when divided by 4 AND (NOT 400) AND (NOT 100))
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


	for (int i = 0; i < totaldays; i++) {

		strcpy(curr_order_id, resultstack.order_id_by_date[i]); // GET curr_order_id

		if (strcmp(curr_order_id, NA) == 0) {
			strcpy(curr_name, NA);
			strcpy(order_due_str, NA);
		}
		else {
			// GET synchronized_index
			for (int j = 0; j < 100; j++) {
				if (strcmp(curr_order_id, resultstack.order_id[j]) == 0) {
					synchronized_index = j;
					break;
				}
			}

			// GET curr_name
			strcpy(curr_name, resultstack.name[synchronized_index]);

			// convert Date resultstack.order_due[synchronized_index] to String order_due_str
			sprintf(order_due_str, "%d-%d-%d", resultstack.order_due[synchronized_index].year, resultstack.order_due[synchronized_index].month, resultstack.order_due[synchronized_index].day);
		}
		// print & iterate datelist through each line for Date
		// print & iterate name through each line for Product_Name
		// print & iterate order_id_by_date through each line for Order_Number
		// print & iterate production_by_date through each line for Quantity(Produced)
		// print & iterate order_due through each line for Due_Date

		printf("%s %s %s %d %s \n", datelist[i], curr_name, resultstack.order_id_by_date[i], resultstack.production_by_date[i], order_due_str);


	}


}

//------------------------------------------------------SCHEDULING KERNEL--------------------------------------------------------
void FCFS(struct Order orderstack, struct Order resultx, struct Order resulty, struct Order resultz, int length)
{

	printf("start %d %d %d", orderstack.startorder.year, orderstack.startorder.month, orderstack.startorder.day);
	printf(", end %d %d %d\n", orderstack.endorder.year, orderstack.endorder.month, orderstack.endorder.day);
	int startint = datetoday(orderstack.startorder.year, orderstack.startorder.month, orderstack.startorder.day);
	int endint = datetoday(orderstack.endorder.year, orderstack.endorder.month, orderstack.endorder.day);
	printf("date start %d, date end %d\n", startint, endint);
	int currday = 0;
	int endday = endint - startint;
	printf("reached here\n");

	//construct struct note that it is all shallow copies---------

	resultx.startorder = orderstack.startorder;
	resulty.startorder = orderstack.startorder;
	resultz.startorder = orderstack.startorder;
	resultx.endorder = orderstack.endorder;
	resulty.endorder = orderstack.endorder;
	resultz.endorder = orderstack.endorder;

	resultx.plant = 'X';
	resulty.plant = 'Y';
	resultz.plant = 'Z';

	//------------------------------------------------------------


	int plant_x = 300;
	int plant_y = 400;
	int plant_z = 500;

	//plant production queue

	int prodx = 0;
	int prody = 0;
	int prodz = 0;

	int xiter = 0;
	int yiter = 0;
	int ziter = 0;

	int endprodx = 0;
	int endprody = 0;
	int endprodz = 0;

	int curr = 0;

	while (currday <= endday)
	{
		//assign production to factories x to y to z

		if (prodx == 0)
		{
			if (curr < length)
			{
				//initialize starting values 
				printf("Check\n");
				strcpy(resultx.order_id[xiter], orderstack.order_id[curr]);
				strcpy(resultx.name[xiter], orderstack.name[curr]);
				resultx.order_due[xiter] = orderstack.order_due[curr];		//shallow copy
				resultx.quantity[xiter] = orderstack.quantity[curr];
				printf("Order for plant x %s\n", resultx.name[xiter]);
				prodx = orderstack.quantity[curr];
				xiter++;
				curr++;
			}
			else
			{
				endprodx = 1;
				printf("x is ending\n");
			}
		}
		if (prody == 0)
		{
			if (curr < length)
			{
				//initialize starting values 
				strcpy(resulty.order_id[yiter], orderstack.order_id[curr]);
				strcpy(resulty.name[yiter], orderstack.name[curr]);
				resulty.order_due[yiter] = orderstack.order_due[curr];		//shallow copy
				resulty.quantity[yiter] = orderstack.quantity[curr];

				prody = orderstack.quantity[curr];
				yiter++;
				curr++;
			}
			else
			{
				endprody = 1;
				printf("y is ending\n");
			}
		}
		if (prodz == 0)
		{
			if (curr < length)
			{
				//initialize starting values 
				strcpy(resultz.order_id[ziter], orderstack.order_id[curr]);
				strcpy(resultz.name[ziter], orderstack.name[curr]);
				resultz.order_due[ziter] = orderstack.order_due[curr];		//shallow copy
				resultz.quantity[ziter] = orderstack.quantity[curr];

				prodz = orderstack.quantity[curr];
				ziter++;
				curr++;
			}
			else
			{
				endprodz = 1;
				printf("z is ending\n");
			}
		}


		//process values

		if (endprodx == 0)
		{

			strcpy(resultx.order_id_by_date[currday], resultx.order_id[xiter - 1]);
			printf("testing\n");
			resultx.production_by_date[currday] = 300;
			printf("Plant X is doing order %s\n", resultx.order_id_by_date[currday]);
			if (prodx < 300)
			{
				resultx.production_by_date[currday] = prodx;
			}

			prodx = prodx - 300;
			if (prodx < 0) {
				printf("x is reset\n");
				prodx = 0;
			}
		}
		else
		{
			resultx.production_by_date[currday] = 0;
			strcpy(resultx.order_id_by_date[currday], "NA");

		}

		if (endprody == 0)
		{
			strcpy(resulty.order_id_by_date[currday], resulty.order_id[yiter - 1]);
			resulty.production_by_date[currday] = 400;
			printf("Plant Y is doing order %s\n", resulty.order_id_by_date[currday]);

			if (prody < 400)
			{
				resulty.production_by_date[currday] = prody;
			}

			prody = prody - 400;
			if (prody < 0) {
				printf("y is reset\n");
				prody = 0;
			}
		}
		else
		{
			resulty.production_by_date[currday] = 0;
			strcpy(resulty.order_id_by_date[currday], "NA");

		}

		if (endprodz == 0)
		{
			strcpy(resultz.order_id_by_date[currday], resultz.order_id[ziter - 1]);
			resultz.production_by_date[currday] = 500;
			printf("Plant Z is doing order %s\n", resultz.order_id_by_date[currday]);

			if (prodz < 500)
			{
				resultz.production_by_date[currday] = prodz;
			}

			prodz = prodz - 500;
			if (prodz < 0) prodz = 0;
		}
		else
		{
			resultz.production_by_date[currday] = 0;
			strcpy(resultz.order_id_by_date[currday], "NA");

		}

		currday++;


	}
	printf("checkcheck\n");
	for (int i = 0; i < endday; i++)
	{
		// printf("`");
		printf("day %d, Plant X is doing %d, the product is %s\n", i + 1, resultx.production_by_date[i], resultx.order_id_by_date[i]);
		printf("day %d, Plant Y is doing %d, the product is %s\n", i + 1, resulty.production_by_date[i], resulty.order_id_by_date[i]);
		printf("day %d, Plant Z is doing %d, the product is %s\n", i + 1, resultz.production_by_date[i], resultz.order_id_by_date[i]);
	}
	printf("------------------SUMARY RESULT------------------ \n");

	OutputModule(resultx, "FCFS");
	OutputModule(resulty, "FCFS");
	OutputModule(resultz, "FCFS");
}



int main() {

	int plant_x = 300;
	int plant_y = 400;
	int plant_z = 500;

	//-----------------------GET INFO FROM PART 1--------------------------
	struct Order input;
	int inputlength;
	struct Date end;
	struct Date start;
	char *alg = "SJF";    // dummy data

	//--------------------------------------------------------------------
	//dummy data

	strcpy(input.order_id[0], "P001");
	strcpy(input.order_id[1], "P002");
	strcpy(input.order_id[2], "P003");
	strcpy(input.order_id[3], "P004");
	strcpy(input.name[0], "Product_A");
	strcpy(input.name[1], "Product_B");
	strcpy(input.name[2], "Product_C");
	strcpy(input.name[3], "Product_D");

	// dateinput(input.order_due[0], 2020, 4, 20);
	input.order_due[0].year = 2020;
	input.order_due[0].month = 4;
	input.order_due[0].day = 21;

	input.order_due[1].year = 2020;
	input.order_due[1].month = 4;
	input.order_due[1].day = 22;

	input.order_due[2].year = 2020;
	input.order_due[2].month = 4;
	input.order_due[2].day = 23;

	input.order_due[3].year = 2020;
	input.order_due[3].month = 4;
	input.order_due[3].day = 24;

	// dateinput(input.order_due[1], 2020, 4, 21);
	// dateinput(input.order_due[2], 2020, 4, 22);
	// dateinput(input.order_due[3], 2020, 4, 23);

	input.quantity[0] = 800;
	input.quantity[1] = 600;
	input.quantity[2] = 1200;
	input.quantity[3] = 400;

	// dateinput(input.startorder, 2020, 3, 20);
	input.startorder.year = 2020;
	input.startorder.month = 3;
	input.startorder.day = 20;

	input.endorder.year = 2020;
	input.endorder.month = 3;
	input.endorder.day = 28;
	// dateinput(input.endorder, 2020, 5, 20);

	//

   //FCFS, SJF, PR
   //get alg from outside

	struct Order resultx;
	struct Order resulty;
	struct Order resultz;

	//struct Order orderstack, struct Order resultx, struct Order resulty, struct Order resultz, int length
	
	
	inputlength = 4; //dummy data


	if (strcmp(alg, "FCFS") == 0)
	{
		printf("here\n");

		FCFS(input, resultx, resulty, resultz, inputlength);
	}
	else if (strcmp(alg, "SJF") == 0)
	{
		/*This is SJF now*/
		for (int i = 0; i < inputlength; i++) {
			for (int j = 0; j < inputlength - i - 1; j++) {
				if (input.quantity[j] > input.quantity[j + 1]) {
					// swapping, its not easy on the eye
					char tempchar[100];
					int tempint;
					struct Date tempdate;
					strcpy(tempchar, input.order_id[j]);
					strcpy(input.order_id[j], input.order_id[j + 1]);
					strcpy(input.order_id[j + 1], tempchar);

					//reset 
					memset(tempchar, 0, 100);
					strcpy(tempchar, input.name[j]);
					strcpy(input.name[j], input.name[j + 1]);
					strcpy(input.name[j + 1], tempchar);

					//reset char
					memset(tempchar, 0, 100);
					tempdate = input.order_due[j];
					input.order_due[j] = input.order_due[j + 1];
					input.order_due[j + 1] = tempdate;

					tempint = input.quantity[j];
					input.quantity[j] = input.quantity[j + 1];
					input.quantity[j + 1] = tempint;

					//order_id_by_date and production_by_date no need to swap\
                    // the rest too

				}
			}
		}
		//pass sjf to fcfs for processing 
		FCFS(input, resultx, resulty, resultz, inputlength);
		
	}
	else
	{
		printf("error input");
	}

	

	return 0;
}
