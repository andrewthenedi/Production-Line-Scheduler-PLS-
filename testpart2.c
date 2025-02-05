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
	char *order_id[100];
	char *name[100];
	struct Date order_due[100];
	int quantity[100];
	struct Date dates[100];
	char *process_by_date[100];
	struct Date startorder;
	struct Date endorder;
	char plant[2][100];
	
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
void FCFS(struct Order orderstack, struct Date start, struct Date end, int plantprod, int length)
{

	struct Date currlow;

	int startint = datetoday(start.year, start.month, start.day);
	int endint = datetoday(end.year, end.month, end.day);

	int plant_x = 300;
	int plant_y = 400;
	int plant_z = 500;

	int prodx = ;
	int prody;
	int prodz;

	int i = 0;
	for (int totalprod = 0; totalprod < 0; i++)
	{
		prod
		

		for (int currday = startint; currday <= endint; currday++)
		{



		}
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


	if (strcmp(alg, "FCFS") == 0 || strcmp(alg, "SJF") == 0)
	{
		FCFS(input, start, end, plant_x, inputlength);
		FCFS(input, start, end, plant_y, inputlength);
		FCFS(input, start, end, plant_z, inputlength);
		//send to part3
		SJF(input, start, end, plant_x, inputlength);
		SJF(input, start, end, plant_y, inputlength);
		SJF(input, start, end, plant_z, inputlength);
	}
	else
	{
		printf("error input");
	}

	//send result stack to part 3

	return 0;
}
