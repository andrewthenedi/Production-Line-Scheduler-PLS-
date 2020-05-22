#include <stdio.h>
#include<stdlib.h>
#include <time.h>
// #include <unistd.h>
#include <string.h>

int valid_date(int day, int mon, int year)    
{
    int is_valid = 1, is_leap = 0;
    
    if (year >= 1800 && year <= 9999) 
    {
 
        //  check whether year is a leap year
        if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) 
        {
            is_leap = 1;
        }
        
        // check whether mon is between 1 and 12
        if(mon >= 1 && mon <= 12)
        {
            // check for days in feb
            if (mon == 2)
            {
                if (is_leap && day == 29) 
                {
                    is_valid = 1;
                }
                else if(day > 28) 
                {
                    is_valid = 0;
                }
            }
            
            // check for days in April, June, September and November
            else if (mon == 4 || mon == 6 || mon == 9 || mon == 11) 
            {
                if (day > 30)
                {
                    is_valid = 0;
                }
            }
 
            // check for days in rest of the months 
            // i.e Jan, Mar, May, July, Aug, Oct, Dec
            else if(day > 31)
            {            
                is_valid = 0;
            }        
        }
        
        else
        {
            is_valid = 0;
        }
 
    }
    else
    {
        is_valid = 0;
    }
    
    return is_valid;
}

int* remaining(int yyNow, int mmNow, int ddNow, int yy, int mm, int dd)
{
    int dd_diff, mm_diff, yy_diff;
    int *diff = malloc(sizeof (char) * 3);

    // time_t t = time(NULL);
    // struct tm tm = *localtime(&t);

    // ddNow = tm.tm_mday;
    // mmNow = tm.tm_mon + 1;
    // yyNow = tm.tm_year + 1900;

    if(!valid_date(ddNow, mmNow, yyNow))
    {
        printf("First date is invalid.\n");
        // return 0;
    }
    
    if(!valid_date(dd, mm, yy))
    {
        printf("Second date is invalid.\n");
        // return 0;
    }       
    
    if(dd < ddNow)
    {      
        // borrow days from february
        if (mm == 3)
        {
            //  check whether year is a leap year
            if ((yy % 4 == 0 && yy % 100 != 0) || (yy % 400 == 0)) 
            {
                dd += 29;
            }
            
            else
            {
                dd += 28;
            }                        
        }
        
        // borrow days from April or June or September or November
        else if (mm == 5 || mm == 7 || mm == 10 || mm == 12) 
        {
           dd += 30; 
        }
                
        // borrow days from Jan or Mar or May or July or Aug or Oct or Dec
        else
        {
           dd += 31;
        }
        
        mm = mm - 1;
    }
    
    if (mm < mmNow)
    {
        mm += 12;
        yy -= 1;
    }       
    
    dd_diff = dd - ddNow;
    diff[0] = dd_diff;
    mm_diff = mm - mmNow;
    diff[1] = mm_diff;
    yy_diff = yy - yyNow;
    diff[2] = yy_diff;
    
    return diff;
}

int stringToInteger(char string[])
{
    int digit, j = 1, m = 0;
    for (int i = strlen(string)-1; i >=0; i--)
    {
        digit = string[i];
        digit = digit - 48;
        m = m + (digit * j);
        j = j * 10;
    }
    return m;
}

void remove_all_chars(char* str, char c) {
    char *pr = str, *pw = str;
    while (*pr) {
        *pw = *pr++;
        pw += (*pw != c);
    }
    *pw = '\0';
}

void delchar(char *x,int a, int b)
{
	if ((a+b-1) <= strlen(x))
	{
		strcpy(&x[b-1],&x[a+b-1]);
		puts(x);
	}
}

void remchar(char *s, char chr)
{
   int i, j = 0;
   for ( i = 0; s[i] != '\0'; i++ ) /* 'i' moves through all of original 's' */
   {
      if ( s[i] != chr )
      {
         s[j++] = s[i]; /* 'j' only moves after we write a non-'chr' */
      }
   }
   s[j] = '\0'; /* re-null-terminate */
}

int main()
{
    struct Date 
    {
        int day[100];
        int mon[100];
        int year[100];
    };
    struct Order
    {
        char *orderID[100];
        char *productName[100]; 
        int quantity[100];
    };

    struct Date start[20];
    struct Date end[20];
    struct Date due[20];
    struct Order input[20];

    int dayStart[100], monStart[100], yearStart[100];
    int dayDue[100], monDue[100], yearDue[100];
    int dayEnd[100], monEnd[100], yearEnd[100];

    int i, j, k, ctr;
    char *alg;
    int status = 0;
    int inputLength;
    char* str[100];
    char str1[100];
    int str2[100];
    char str3[100];
    char temp[100];
    char newString[10][10]; 

    while (status == 0)
    {

        printf("~~WELCOME TO PLS~~\n");

        printf("Please enter:\n");
        fgets(str1, sizeof str1, stdin);

        char* from = str1;
        char * ch = " ";
        char * token = strtok(from, ch);
        int count;
        while(token!=NULL)
        {
            // printf("%s\n", token);
            str[i++] = token;
            token = strtok(NULL, ch);
            count++;
        }
        strcpy(str1,str[0]);
        // int ret = strcmp(str1, "addPeriod");

        if (strcmp(str1, "addPERIOD") == 0)
        {   
            char * ch1 = "-";

            char* token1 = strtok(str[1], ch1);
            start->year[i] = atoi(token1);
            token1 = strtok(NULL, ch1);
            start->mon[i] = atoi(token1);
            token1 = strtok(NULL, ch1);
            start->day[i] = atoi(token1);
            // printf("%d\n", start->year);
            // printf("%d\n", start->mon);
            // printf("%d\n", start->day);

            char* token2 = strtok(str[2], ch1);
            end->year[i] = atoi(token2);
            token2 = strtok(NULL, ch1);
            end->mon[i] = atoi(token2);
            token2 = strtok(NULL, ch1);
            end->day[i] = atoi(token2);
            // printf("%d\n", end->year);
            // printf("%d\n", end->mon);
            // printf("%d\n", end->day);
            i++;
        }
        else if (strcmp(str1, "addORDER") == 0)
        {
            char * ch1 = "-";

            char* token1 = strtok(str[2], ch1);
            due->year[j] = atoi(token1);
            token1 = strtok(NULL, ch1);
            due->mon[j] = atoi(token1);
            token1 = strtok(NULL, ch1);
            due->day[j] = atoi(token1);
            // printf("%d\n", due->year);
            // printf("%d\n", due->mon);
            // printf("%d\n", due->day);

            input->orderID[j] = str[1];
            input->quantity[j] = atoi(str[3]);
            input->productName[j] = str[4];
            // printf("%s\n", input->orderID);
            // printf("%d\n", input->quantity);
            // printf("%s\n", input->productName);
            inputLength++;
            printf("%d", inputLength);
            j++;
            for (k = 0; k < 3; k++)
            {
                printf("%s",input->orderID[k]);
            }
        }
        else if (strcmp(str1, "runPLS") == 0)
        {
            char * alg = str[1];
            printf("%s\n", alg);
            // Schedule(input, start, end, due, alg, inputLength);
        }
        else if (strcmp(str1, "addBATCH") == 0)
        {

        }
        else if (strcmp(str1, "exitPLS") == 0)
        {
            printf("Bye-bye!");
            status = 1;
        }
        else
        {
            printf("Invalid Input!");   
        }
    }
}
