#include <stdio.h>
#include<stdlib.h>
#include <time.h>
// #include <unistd.h>
#include <string.h>


/*
 apparently strtok does not works well in this situation 
 The pointer is such a mess 
 
*/ 




struct Date 
{
    int day;
    int month;
    int year;
};

struct Order
{
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

void getsubstring(char origin[], char cpy[], int from, int end){
    if(end < 0){
        end = strlen(origin);
    }
    // printf("from %d to %d", from, end);
    // printf("%d\n", end-from);
    strncpy(cpy, &origin[from], end - from);
    cpy[end] = 0;
    // printf("test %s, from %d to %d\n", cpy, from, end);
}

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

	printf("\n Plant_%c (%d per day) \n", resultstack.plant, getplantvalue(resultstack.plant));
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

	// printf("start %d %d %d", orderstack.startorder.year, orderstack.startorder.month, orderstack.startorder.day);
	// printf(", end %d %d %d\n", orderstack.endorder.year, orderstack.endorder.month, orderstack.endorder.day);
	int startint = datetoday(orderstack.startorder.year, orderstack.startorder.month, orderstack.startorder.day);
	int endint = datetoday(orderstack.endorder.year, orderstack.endorder.month, orderstack.endorder.day);
	// printf("date start %d, date end %d\n", startint, endint);
	int currday = 0;
	int endday = endint - startint;

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
				strcpy(resultx.order_id[xiter], orderstack.order_id[curr]);
				strcpy(resultx.name[xiter], orderstack.name[curr]);
				resultx.order_due[xiter] = orderstack.order_due[curr];		//shallow copy
				resultx.quantity[xiter] = orderstack.quantity[curr];
				// printf("Order for plant x %s\n", resultx.name[xiter]);
				prodx = orderstack.quantity[curr];
				xiter++;
				curr++;
			}
			else
			{
				endprodx = 1;
				//printf("x is ending\n");
			}
		}
		if (prody == 0)
		{
			if (curr < length)
			{
				// initialize starting values 
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
				// printf("y is ending\n");
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
				// printf("z is ending\n");
			}
		}


		//process values

		if (endprodx == 0)
		{

			strcpy(resultx.order_id_by_date[currday], resultx.order_id[xiter - 1]);
			//printf("testing\n");
			resultx.production_by_date[currday] = 300;
			//printf("Plant X is doing order %s\n", resultx.order_id_by_date[currday]);
			if (prodx < 300)
			{
				resultx.production_by_date[currday] = prodx;
			}

			prodx = prodx - 300;
			if (prodx < 0) {
				//printf("x is reset\n");
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
			// printf("Plant Y is doing order %s\n", resulty.order_id_by_date[currday]);

			if (prody < 400)
			{
				resulty.production_by_date[currday] = prody;
			}

			prody = prody - 400;
			if (prody < 0) {
				//printf("y is reset\n");
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
			// printf("Plant Z is doing order %s\n", resultz.order_id_by_date[currday]);

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
	for (int i = 0; i < endday; i++)
	{
		// printf("`");
		// printf("day %d, Plant X is doing %d, the product is %s\n", i + 1, resultx.production_by_date[i], resultx.order_id_by_date[i]);
		// printf("day %d, Plant Y is doing %d, the product is %s\n", i + 1, resulty.production_by_date[i], resulty.order_id_by_date[i]);
		// printf("day %d, Plant Z is doing %d, the product is %s\n", i + 1, resultz.production_by_date[i], resultz.order_id_by_date[i]);
	}
	printf("------------------SUMMARY RESULT------------------ \n");

	OutputModule(resultx, "FCFS");
	OutputModule(resulty, "FCFS");
	OutputModule(resultz, "FCFS");
}

int main()
{
    

    // buffers
    char* from, userInput[100];
    char req[30];
    char * startDate[100];
    char * endDate[100];
    char * dueDate[100];
    char alg[100][100];
    
    // for addBATCH
    char batch[100][30];
    int batch_n = 0; 
    int isbatch = 0; // boolean value to check if there is addBATCH command
    int batch_i = 0;

    // status codes    
    int i = 0, status = 0, n, j = 0;
    char * blank = " ";
    char * stp = "-";
    char * token;

    // orders 
    struct Date start[20];
    struct Date end[20];
    struct Date due[20];
    struct Order input;

    printf("~~WELCOME TO PLS~~\n");
    while (status == 0)
    {
       

        if(isbatch){
            if(batch_i < batch_n){
                strcpy(from, batch[batch_i++]);
            }
            else{
                isbatch = 0; 
                continue; 
            }
        }
        else{
             printf("\n Please enter:\n");
            fgets(userInput, sizeof userInput, stdin);
            from = userInput;
        }
        // token = strtok(from, blank);

    
        int from1, end1;

        // find the space
        for(int k = 0; k < strlen(from); k++){
            if(from[k] != ' '){
                from1 = k; 
                end1 = k; 
                while(from[end1] != ' ' && end1 < strlen(from))   end1++;
                // printf("from is %d, end is %d\n", from1, end1); 
                getsubstring(from, req, from1, end1);
                // printf("its %s\n", req);
                break;
            }
        }

        // req[j] = token;
        // token = strtok(NULL, blank);
        // printf("%s\n", req);
        if (strcmp(req, "addPERIOD") == 0)
        {
            
            char tempdate[30];
            /*Split again*/
            for(int k = end1; k < strlen(from); k++){
                
                if(from[k] != ' '){
                    from1 = k; 
                    end1 = k; 
                    while(from[end1] != ' ' && end1 < strlen(from)) end1++;
                    getsubstring(from, tempdate, from1, end1);
                    break;
                }
            }
            
            char date1[15];
            
            int from2, end2; 
            /* split the - in the date */
             for(int k = 0; k < strlen(tempdate); k++){ 
                if(tempdate[k] != '-'){
                    from2 = k; 
                    end2 = k; 
                    while(tempdate[end2] != '-' && end2 < strlen(tempdate)) end2++;
                    getsubstring(tempdate, date1, from2, end2);
                    break;
                }
            }
            input.startorder.year = atoi(date1);
            

            memset(date1, 0, 30);

            for(int k = end2; k < strlen(tempdate); k++){ 
                if(tempdate[k] != '-'){
                    from2 = k; 
                    end2 = k; 
                    while(tempdate[end2] != '-' && end2 < strlen(tempdate)) end2++;
                    getsubstring(tempdate, date1, from2, end2);
                    break;
                }
            }
            
            input.startorder.month = atoi(date1);

            memset(date1, 0, 30);

            for(int k = end2; k < strlen(tempdate); k++){ 
                if(tempdate[k] != '-'){
                    from2 = k; 
                    end2 = k; 
                    while(tempdate[end2] != '-' && end2 < strlen(tempdate)) end2++;
                    getsubstring(tempdate, date1, from2, end2);
                    break;
                }
            }
            
            input.startorder.day = atoi(date1);

            /* DATE 1 IS DONE */ 

            memset(tempdate, 0, 30);

            /*Split again*/
            for(int k = end1; k < strlen(from); k++){
                
                if(from[k] != ' '){
                    from1 = k; 
                    end1 = k; 
                    while(from[end1] != ' ' && end1 < strlen(from)) end1++;
                    getsubstring(from, tempdate, from1, end1);
                    break;
                }
            }
            
            
            from2 = end2 = 0;
            // int from2, end2; 
            /* split the - in the date */
             for(int k = 0; k < strlen(tempdate); k++){ 
                if(tempdate[k] != '-'){
                    from2 = k; 
                    end2 = k; 
                    while(tempdate[end2] != '-' && end2 < strlen(tempdate)) end2++;
                    getsubstring(tempdate, date1, from2, end2);
                    break;
                }
            }
            input.endorder.year = atoi(date1);
            // printf("check2 %d\n", start->year[0]);

            memset(date1, 0, 30);

            for(int k = end2; k < strlen(tempdate); k++){ 
                if(tempdate[k] != '-'){
                    from2 = k; 
                    end2 = k; 
                    while(tempdate[end2] != '-' && end2 < strlen(tempdate)) end2++;
                    getsubstring(tempdate, date1, from2, end2);
                    break;
                }
            }
            // printf("check %s\n", date1);
            input.endorder.month = atoi(date1);

            memset(date1, 0, 30);

            for(int k = end2; k < strlen(tempdate); k++){ 
                if(tempdate[k] != '-'){
                    from2 = k; 
                    end2 = k; 
                    while(tempdate[end2] != '-' && end2 < strlen(tempdate)) end2++;
                    getsubstring(tempdate, date1, from2, end2);
                    break;
                }
            }
            input.endorder.day = atoi(date1);
        }
        else if (strcmp(req, "addORDER") == 0)
        {
            // printf("request is %s\n", from);
            char tempdate[30];
            memset(tempdate, 0, 30);
            /*Split again*/
            for(int k = end1; k < strlen(from); k++){
                
                if(from[k] != ' '){
                    from1 = k; 
                    end1 = k; 
                    while(from[end1] != ' ' && end1 < strlen(from)) end1++;
                    getsubstring(from, tempdate, from1, end1);
                    break;
                }
            }

            // printf("ez %s\n", tempdate);
            strcpy(input.order_id[i], tempdate);
            // input->orderID[i] = tempdate; 
            // printf("%s\n", input->orderID[i]);
            memset(tempdate, 0, 30);

            // the date 
            for(int k = end1; k < strlen(from); k++){
                
                if(from[k] != ' '){
                    from1 = k; 
                    end1 = k; 
                    while(from[end1] != ' ' && end1 < strlen(from)) end1++;
                    getsubstring(from, tempdate, from1, end1);
                    break;
                }
            }
            
            char date1[15];
            // printf("%s\n", tempdate);
            int from2, end2; 
            /* split the - in the date */
             for(int k = 0; k < strlen(tempdate); k++){ 
                if(tempdate[k] != '-'){
                    from2 = k; 
                    end2 = k; 
                    while(tempdate[end2] != '-' && end2 < strlen(tempdate)) end2++;
                    getsubstring(tempdate, date1, from2, end2);
                    break;
                }
            }
            input.order_due[i].year = atoi(date1);
            // printf("check2 %d\n", start->year[0]);

            memset(date1, 0, 30);

            for(int k = end2; k < strlen(tempdate); k++){ 
                if(tempdate[k] != '-'){
                    from2 = k; 
                    end2 = k; 
                    while(tempdate[end2] != '-' && end2 < strlen(tempdate)) end2++;
                    getsubstring(tempdate, date1, from2, end2);
                    break;
                }
            }
            // printf("check %s\n", date1);
            input.order_due[i].month = atoi(date1);
            memset(date1, 0, 30);

            for(int k = end2; k < strlen(tempdate); k++){ 
                if(tempdate[k] != '-'){
                    from2 = k; 
                    end2 = k; 
                    while(tempdate[end2] != '-' && end2 < strlen(tempdate)) end2++;
                    getsubstring(tempdate, date1, from2, end2);
                    break;
                }
            }
            // printf("check %s\n", date1);
            input.order_due[i].day = atoi(date1);

            memset(tempdate, 0, 30);

            for(int k = end1; k < strlen(from); k++){
                
                if(from[k] != ' '){
                    from1 = k; 
                    end1 = k; 
                    while(from[end1] != ' ' && end1 < strlen(from)) end1++;
                    getsubstring(from, tempdate, from1, end1);
                    break;
                }
            }

            // printf("ez %s\n", tempdate);
            input.quantity[i] = atoi(tempdate);


            memset(tempdate, 0, 30);
            // printf("end1 is in = %d\n", end1);
            for(int k = end1; k < strlen(from); k++){
                
                if(from[k] != ' '){
                    from1 = k; 
                    end1 = k; 
                    while(from[end1] != ' ' && end1 < strlen(from)) end1++;
                    getsubstring(from, tempdate, from1, end1);
                    break;
                }
            }

            // printf("name is %s\n", tempdate);
            // input->productName[i] = tempdate;
            strcpy(input.name[i], tempdate);
            i++;
            // split the date
        }
        else if (strcmp(req, "exitPLS") == 0)
        {
            printf("Bye-bye!\n");
            status = 1;
            
        }
        else if (strcmp(req, "runPLS") == 0)
        {
            char tempalg[30];
            memset(tempalg, 0, 30);
            /*Split again*/
            for(int k = end1; k < strlen(from); k++){
                
                if(from[k] != ' '){
                    from1 = k; 
                    end1 = k; 
                    while(from[end1] != ' ' && end1 < strlen(from)) end1++;
                    getsubstring(from, tempalg, from1, end1);
                    break;
                }
            }


            strcpy(alg[i], tempalg);
            // for(int n = 0; n < i; n++){
            //     printf("Order id is %s\n", input.order_id[n]);
            //     printf("Product name is %s\n", input.name[n]);
            //     printf("Quantity is %d\n", input.quantity[n]);
            //     printf("Year is %d %d %d\n", input.order_due[n].year, input.order_due[n].month, input.order_due[n].day);
            // }
            // printf("%d %d %d\n", input.startorder.year, input.startorder.month, input.startorder.day);
            // printf("%d %d %d\n", input.endorder.year, input.endorder.month, input.endorder.day);


    struct Order resultx;
	struct Order resulty;
	struct Order resultz;

	//struct Order orderstack, struct Order resultx, struct Order resulty, struct Order resultz, int length
	
	
	 


	if (strcmp(tempalg, "FCFS") == 0)
	{

		FCFS(input, resultx, resulty, resultz, i);
	}
	else if (strcmp(tempalg, "SJF") == 0)
	{
		/*This is SJF now*/
		for (int k = 0; k < i; k++) {
			for (int j = 0; j < i - k - 1; j++) {
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
		FCFS(input, resultx, resulty, resultz, i);
		
	}
	else
	{
		printf("error input");
	}

            // Schedule(input, start, end, due, alg, i);    dal's function
        }
        else if(strcmp(req, "addBATCH") == 0){
            char tempdate[30];
            memset(tempdate, 0, 30);
            /*Split again*/
            for(int k = end1; k < strlen(from); k++){
                 
                if(from[k] != ' '){
                    from1 = k; 
                    end1 = k; 
                    while(from[end1] != ' ' && end1 < strlen(from)) end1++;
                    getsubstring(from, tempdate, from1, end1);
                    break;
                }
            }
            FILE *fd;
            char s[100];
            fd = fopen(tempdate, "r"); 
            while(fgets(s, 50, fd) != NULL) batch_n++;
            
            rewind(fd);

            for(int k = 0; k < batch_n; k++){
                memset(s, 0, 100);
                fgets(s, 100, fd);
                int len = strlen(s);
                
                strcpy(batch[k], s);
                batch[k][len] = 0;
                // printf("copied string %s\n The array string %s\n", s, batch[k]);
                // for(int t = 0; t <= k; t++){
                //     printf("array %s\n", batch[t]);
                // }     
            }
            isbatch = 1;

            // printf("%s test\n", tempdate);
        }
        else
        {
            printf("Invalid Input!\n");   
        }
        // for (n = 0; n < 3; n++)
        // {
        //     printf("%s",req[n]);
        // }  
        // printf("%d", j);
        j++;
    }
}
