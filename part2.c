#include <stdio.h>
#include <stdlib.h>
#include <string.h>


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

void dateinput(struct Date date, int y, int m, int d) {
	date.year = y;
	date.month = m;
	date.day = d;
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

    printf("start %d %d %d", orderstack.startorder.year, orderstack.startorder.month, orderstack.startorder.day);
    printf(", end %d %d %d\n", orderstack.endorder.year, orderstack.endorder.month, orderstack.endorder.day);
	int startint = datetoday(orderstack.startorder.year, orderstack.startorder.month, orderstack.startorder.day);
	int endint = datetoday(orderstack.endorder.year, orderstack.endorder.month, orderstack.endorder.day);
    printf("date start %d, date end %d\n", startint, endint);
	int currday = 0;
    int endday = endint - startint;
	printf("reached here\n");
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
            
			strcpy(resultx.process_by_date[currday], resultx.order_id[xiter-1]);
            printf("testing\n");
			resultx.production_by_date[currday] = 300;
            printf("Plant X is doing order %s\n", resultx.process_by_date[currday]);
			if (prodx < 300)
			{
				resultx.production_by_date[currday] = prodx;
			}

			prodx = prodx - 300;
            if(prodx < 0){
                printf("x is reset\n");
                prodx = 0;
            }
        }
		else
		{
			resultx.production_by_date[currday] = 0;
			strcpy(resultx.process_by_date[currday], "NA");

		}

		if (endprody == 0)
		{
			strcpy(resulty.process_by_date[currday], resulty.order_id[yiter-1]);
			resulty.production_by_date[currday] = 400;
            printf("Plant Y is doing order %s\n", resulty.process_by_date[currday]);

			if (prody < 400)
			{
				resulty.production_by_date[currday] = prody;
			}

			prody = prody - 400;
            if(prody < 0){ 
                printf("y is reset\n");
                prody = 0;
            }
		}
		else
		{
			resulty.production_by_date[currday] = 0;
			strcpy(resulty.process_by_date[currday], "NA");

		}

		if (endprodz == 0)
		{
			strcpy(resultz.process_by_date[currday], resultz.order_id[ziter-1]);
			resultz.production_by_date[currday] = 500;
            printf("Plant Z is doing order %s\n", resultz.process_by_date[currday]);

			if (prodz < 500)
			{
				resultz.production_by_date[currday] = prodz;
			}

			prodz = prodz - 500;
            if(prodz < 0) prodz = 0;
		}
		else
		{
			resultz.production_by_date[currday] = 0;
			strcpy(resultz.process_by_date[currday], "NA");

		}

		currday++;
		

	}
    printf("checkcheck\n");
	for (int i = 0; i < endday; i++)
	{
		// printf("`");
        printf("day %d, Plant X is doing %d, the product is %s\n", i+1, resultx.production_by_date[i], resultx.process_by_date[i]);
		printf("day %d, Plant Y is doing %d, the product is %s\n", i+1, resulty.production_by_date[i], resulty.process_by_date[i]);
        printf("day %d, Plant Z is doing %d, the product is %s\n", i+1, resultz.production_by_date[i], resultz.process_by_date[i]);
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
    input.endorder.day = 26;
	// dateinput(input.endorder, 2020, 5, 20);

	//

   //FCFS, SJF, PR
   //get alg from outside

	struct Order resultx;
	struct Order resulty;
	struct Order resultz;
    // struct Order
	//struct Order orderstack, struct Order resultx, struct Order resulty, struct Order resultz, int length
	inputlength = 4;
	if ((strcmp(alg, "FCFS") == 0) || (strcmp(alg, "SJF") == 0))
	{
		printf("here\n");

		FCFS(input, resultx, resulty, resultz, inputlength);

		/*This is SJF now*/
        for(int i = 0; i < inputlength; i++){
            for(int j = 0; j < inputlength-i-1; j++){
                if(input.quantity[j] > input.quantity[j+1]){
                    // swapping, its not easy on the eye
                    char tempchar[100]; 
                    int tempint; 
                    struct Date tempdate; 
                    strcpy(tempchar, input.order_id[j]);
                    strcpy(input.order_id[j], input.order_id[j+1]);
                    strcpy(input.order_id[j+1], tempchar);

                    //reset 
                    memset(tempchar, 0, 100);
                    strcpy(tempchar, input.name[j]);
                    strcpy(input.name[j], input.name[j+1]);
                    strcpy(input.name[j+1], tempchar);

                    //reset char
                    memset(tempchar, 0, 100);
                    tempdate = input.order_due[j];
                    input.order_due[j] = input.order_due[j+1];
                    input.order_due[j+1] = tempdate;

                    tempint = input.quantity[j];
                    input.quantity[j] = input.quantity[j+1];
                    input.quantity[j+1] = tempint;

                    //order_id_by_date and production_by_date no need to swap\
                    // the rest too

                }
            }
        }

        // SJF LMAO
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
