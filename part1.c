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

int* remaining(int mmNow, int ddNow, int yyNow, int mm, int dd, int yy)
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

int main()
{
    int day1, mon1, year1;
    int day, mon, year;
    int quant;
    char orderNum[100];
    char productName[100];

    printf("\nEnter Order Number: ");
    scanf("%s", orderNum);

    printf("Enter Quantity: ");
    scanf("%d", &quant);

    printf("Enter Start Date (MM/DD/YYYY): ");
    scanf("%d/%d/%d", &mon, &day, &year);

    printf("Enter Due Date (MM/DD/YYYY): ");
    scanf("%d/%d/%d", &mon1, &day1, &year1);

    printf("Enter productName: ");
    scanf("%s", productName);

    int * diff = remaining(mon, day, year, mon1, day1, year1);

    printf("\nOrder Number: %s\n", orderNum);
    printf("Quantity (Produced): %d\n", quant);
    printf("Difference: %d years %02d months and %02d days.\n", *(diff + 2), *(diff + 1), *(diff + 0));
    printf("Product Name: %s\n", productName);

    int pid = 1, fd[2], n;
    char * output, output2;
    
    if (pipe(fd) < 0)
    {
        printf("Pipe creation error\n");
        exit(1);
    }

    while (pid == 0)
    {
        pid = fork();

        if (pid < 0)
        {
            printf("Fork Failed\n");
            exit(1);
        }
        else if (pid == 0)
        {
            output = Schedule(mon, day, year, mon1, day1, year1);
            write(fd[1], output, strlen(output));
        }
        else
        {
            n = read(fd[0], output2, strlen(output2));
            wait(NULL);
            printf("");
            exit(0);
        }
    }

    printf("bye bye\n");
    close(fd[0]);
    close(fd[1]);
    exit(0);

    // return 0;
}

