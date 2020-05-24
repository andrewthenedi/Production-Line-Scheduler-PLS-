#include <stdio.h>
#include<stdlib.h>
#include <time.h>


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
	char process_by_date[100][100];
	int production_by_date[100];
	struct Date startorder;
	struct Date endorder;
	char plant;
	
};

int datetoday(int y, int m, int d) {
	m = (m + 9) % 12;
	y = y - m / 10;
	return 365 * y + y / 4 - y / 100 + y / 400 + (m * 306 + 5) / 10 + (d - 1);
}

int datecompare(struct Date date1, struct Date date2) // Compares to date
{
	int y1 = date1.year;
	int m1 = date1.month;
	int d1 = date1.day;
	int y2 = date2.year;
	int m2 = date2.month;
	int d2 = date2.day;

	int temp = 0;
	
	temp = datetoday(y1, m1, d1) - datetoday(y2, m2, d2);
	return temp;
	

	//return 0 = dates are same, n = date1 before date2, -n = date1 after date2
}
/*
	orderstack comes from input
	resultstack is the result you send to output
	plantprod is plant production rate e.g, 200 products per day
*/
void FCFS(struct Order orderstack, struct Order resultx, struct Order resulty, struct Order resultz, int length)
{
	

	int startint = datetoday(orderstack.startorder.year, orderstack.startorder.month, orderstack.startorder.day);
	int endint = datetoday(orderstack.endorder.year, orderstack.endorder.month, orderstack.endorder.day);
	int currday = startint;
	/*
	char order_id[100][100];
	char name[100][100];
	struct Date order_due[100];
	int quantity[100];

	char process_by_date[100][100];
	int production_by_date[100];

	struct Date startorder;
	struct Date endorder;
	char plant;*/

	//construct struct note that it is all shallow copies---------

	resultx.startorder = orderstack.startorder;
	resulty.startorder = orderstack.startorder;
	resultz.startorder = orderstack.startorder;
	resultx.endorder = orderstack.endorder;
	resulty.endorder = orderstack.endorder;
	resultz.endorder = orderstack.endorder;

	resultx.plant = "X";
	resulty.plant = "Y";
	resultz.plant = "Z";

	//------------------------------------------------------------


	int plant_x = 300;
	int plant_y = 400;
	int plant_z = 500;

	//plant production queue

	int prodx=0;
	int prody=0;
	int prodz=0;

	int xiter = 0;
	int yiter = 0;
	int ziter = 0;

	int curr = 0;

	while(currday != endint)
	{
		//assign production to factories x to y to z
		if (prodx == 0)
		{
			//initialize starting values 
			strcpy(resultx.order_id[xiter], orderstack.order_id[curr]);
			strcpy(resultx.name[xiter], orderstack.name[curr]);
			resultx.order_due[xiter] = orderstack.order_due[curr];		//shallow copy
			resultx.quantity[xiter] = orderstack.quantity[curr];

			prodx = orderstack.quantity[curr];
			xiter++;
			curr++;
		}
		if (prody == 0)
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
		if (prodz == 0)
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

		//process values


		char process_by_date[100][100];
		int production_by_date[100];


		strcpy(resultx.process_by_date[currday],resultx.order_id[xiter]);
		strcpy(resulty.process_by_date[currday], resulty.order_id[yiter]);
		strcpy(resultz.process_by_date[currday], resultz.order_id[ziter]);

		resultx.production_by_date[currday] = prodx;
		resulty.production_by_date[currday] = prody;
		resultz.production_by_date[currday] = prodz;

		if (prodx < 300) {
			resultx.production_by_date[currday] = prodx;
		}
		if (prody < 400) {
			resulty.production_by_date[currday] = prody;
		}
		if (prodz < 500) {
			resultz.production_by_date[currday] = prodz;
		}


		prodx = prodx - 300;
		prody = prody - 400;
		prodz = prodz - 500;

		currday++;
	}


}
void SJF(struct Order orderstack, struct Date start, struct Date end, int plantprod, int length)
{
	for (int i = 0; i < length; i++)
	{

	}

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

	char *alg = "FCFS";

	//--------------------------------------------------------------------


   //FCFS, SJF, PR
   //get alg from outside

	struct Order resultx;
	struct Order resulty;
	struct Order resultz;

	//struct Order orderstack, struct Order resultx, struct Order resulty, struct Order resultz, int length

	if (strcmp(alg, "FCFS") == 0 || strcmp(alg, "SJF") == 0)
	{
		FCFS(input, resultx, resulty, resultz, inputlength);
		
		//send to part3
		
	}
	else
	{
		printf("error input");
	}

	//send result stack to part 3

	return 0;
}
