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

	while (currday != endint)
	{
		//assign production to factories x to y to z
		
			if (prodx == 0)
			{
				if (curr < length)
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
				else
				{
					endprodx = 1;
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
				}
			}


			//process values
			
			if (endprodx == 0) 
			{
				strcpy(resultx.process_by_date[currday], resultx.order_id[xiter]);
				resultx.production_by_date[currday] = 300;
				
				if (prodx < 300)
				{
					resultx.production_by_date[currday] = prodx;
				}
				
				prodx = prodx - 300;
			}
			else
			{
				resultx.production_by_date[currday] = 0;
				strcpy(resultx.process_by_date[currday], "NA");

			}

			if (endprody == 0)
			{
				strcpy(resulty.process_by_date[currday], resulty.order_id[yiter]);
				resulty.production_by_date[currday] = 400;

				if (prody < 400)
				{
					resulty.production_by_date[currday] = prody;
				}
				
				prody = prody - 400;
			}
			else
			{
				resulty.production_by_date[currday] = 0;
				strcpy(resulty.process_by_date[currday], "NA");

			}

			if (endprodz == 0)
			{
				strcpy(resultz.process_by_date[currday], resultz.order_id[ziter]);
				resultz.production_by_date[currday] = 500;
				
				if (prodz < 500)
				{
					resultz.production_by_date[currday] = prodz;
				}

				prodz = prodz - 500;
			}
			else
			{
				resultz.production_by_date[currday] = 0;
				strcpy(resultz.process_by_date[currday], "NA");

			}

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
		//OutputModule(resultx, "FCFS")
		//OutputModule(resulty, "FCFS")
		//OutputModule(resultz, "FCFS")
	}
	else
	{
		printf("error input");
	}

	//send result stack to part 3

	return 0;
}
