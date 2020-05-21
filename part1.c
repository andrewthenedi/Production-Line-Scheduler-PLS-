#include <stdio.h>
#include<stdlib.h>
#include <time.h>
#include <unistd.h>
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

int main()
{
    struct Start 
    {
        int day;
        int mon;
        int year;
    };
    struct Due
    {
        int day;
        int mon;
        int year;
    };
    struct End
    {
        int day;
        int mon;
        int year;
    };
    struct Input
    {
        char *orderID;
        char *productName; 
        int quantity;
    };

    struct Start start[20];
    struct End end[20];
    struct Due due[20];
    struct Input input[20];
    int dayStart[100], monStart[100], yearStart[100];
    int dayDue[100], monDue[100], yearDue[100];
    int dayEnd[100], monEnd[100], yearEnd[100];
    int i, j, ctr;
    char *alg;
    int inputLength;
    char str1[100];
    char newString[10][10]; 

    printf("~~WELCOME TO PLS~~");

    while (true)
    {

        printf("Please enter:\n");
        fgets(str1, sizeof str1, stdin);
        j=0; ctr=0;
        for (i = 0; i<=(strlen(str1)); i++)
        {
            if(str1[i]==' '||str1[i]=='\0')
            {
                newString[ctr][j]='\0';
                ctr++;  //for next word
                j=0;    //for next word, init index to 0
            }
            else
            {
                newString[ctr][j]=str1[i];
                j++;
            }
        }
        if (newString[0] == "addPERIOD")
        {
            int n = strlen(newString[0]);

            for (i=j=0; i<n; i++) 
            {
                if (newString[1][i] != '-') 
                {
                    newString[1][j++] = newString[1][i]; 
                }
            }
            newString[1][j] = '\0';
            for (i = 0; i < 4; i++)
            {
                yearStart[i] = newString[1][i];
            }
            int yearStart_int;
            for (i = 0; i < sizeof(yearStart); i++)
            {
                yearStart_int *= 10;
                yearStart_int += yearStart[i];
            }

            for (i = 4; i < 6; i++)
            {
                monStart[i] = newString[1][i];
            }
            int monStart_int;
            for (i = 0; i < sizeof(monStart); i++)
            {
                monStart_int *= 10;
                monStart_int += monStart[i];
            }

            for (i = 6; i < 8; i++)
            {
                dayStart[i] = newString[1][i];
            }
            int dayStart_int;
            for (i = 0; i < sizeof(dayStart); i++)
            {
                dayStart_int *= 10;
                dayStart_int += dayStart[i];
            }

            printf("%d",yearStart_int);
            start->year = yearStart_int;
            start->mon = monStart_int;
            start->day = dayStart_int;

            for (i=j=0; i<n; i++) 
            {
                if (newString[2][i] != '-') 
                {
                    newString[2][j++] = newString[2][i]; 
                }
            }
            newString[2][j] = '\0';
            for (i = 0; i < 4; i++)
            {
                yearEnd[i] = newString[2][i];
            }
            int yearEnd_int;
            for (i = 0; i < sizeof(yearEnd); i++)
            {
                yearEnd_int *= 10;
                yearEnd_int += yearEnd[i];
            }

            for (i = 4; i < 6; i++)
            {
                monEnd[i] = newString[2][i];
            }
            int monEnd_int;
            for (i = 0; i < sizeof(monEnd); i++)
            {
                monEnd_int *= 10;
                monEnd_int += monEnd[i];
            }

            for (i = 6; i < 8; i++)
            {
                dayEnd[i] = newString[2][i];
            }
            int dayEnd_int;
            for (i = 0; i < sizeof(dayEnd); i++)
            {
                dayEnd_int *= 10;
                dayEnd_int += dayEnd[i];
            }            

            end->year = yearEnd_int;
            end->mon = monEnd_int;
            end->day = dayEnd_int;
            
        }
        else if (newString[0] == "addORDER")
        {
            int n = strlen(newString[0]);

            for (i=j=0; i<n; i++) 
            {
                if (newString[1][i] != '-') 
                {
                    newString[1][j++] = newString[1][i]; 
                }
            }
            newString[1][j] = '\0';

            char orderID_string[100];
            memcpy(orderID_string, newString[1], sizeof(newString[1]));
            orderID_string[sizeof(newString[1])] = '\0'; 

            input->orderID = orderID_string;

            for (i = 0; i < 4; i++)
            {
                yearDue[i] = newString[2][i];
            }
            int yearDue_int;
            for (i = 0; i < sizeof(yearDue); i++)
            {
                yearDue_int *= 10;
                yearDue_int += yearDue[i];
            }    

            for (i = 4; i < 6; i++)
            {
                monDue[i] = newString[2][i];
            }
            int monDue_int;
            for (i = 0; i < sizeof(monDue); i++)
            {
                monDue_int *= 10;
                monDue_int += monDue[i];
            }    

            for (i = 6; i < 8; i++)
            {
                dayDue[i] = newString[2][i];
            }        
            int dayDue_int;
            for (i = 0; i < sizeof(dayDue); i++)
            {
                dayDue_int *= 10;
                dayDue_int += dayDue[i];
            }       

            due->year = yearDue_int;
            due->mon = monDue_int;
            due->day = dayDue_int;

            char quantity_string[100];
            memcpy(quantity_string, newString[3], sizeof(newString[3]));
            quantity_string[sizeof(newString[3])] = '\0'; 
            int quantity_int;
            quantity_int = stringToInteger(quantity_string);
            input->quantity = quantity_int;

            char productName_string[100];
            memcpy(productName_string, newString[4], sizeof(newString[4]));
            productName_string[sizeof(newString[4])] = '\0'; 
            input->productName = productName_string;

        }
        else if (newString[0] == "runPLS" && newString[3] == "printREPORT")
        {
            alg = newString[1];
            inputLength = sizeof(input) / sizeof(input[0]);
            Schedule(input, start, end, due, alg, inputLength);
        //     int pid = 1, fd[2], n;
        //     char algorithm = newString[1], filename = newString[5];
        //     Input.alg = newString[1];
            
        //     if (pipe(fd) < 0)
        //     {
        //         printf("Pipe creation error\n");
        //         exit(1);
        //     }

        //     pid = fork();

        //     if (pid < 0)
        //     {
        //         printf("Fork Failed\n");
        //         exit(1);
        //     }
        //     else if (pid == 0)
        //     {
        //         filename = Schedule(data, algorithm);     //  randall function
        //         write(fd[1], filename, 100);
        //     }
        //     else
        //     {
        //         n = read(fd[0], filename, 100);
        //         wait(NULL);
        //         // printf("");      kev function
        //         exit(0);
        //     }
        //     printf("bye bye\n");
        //     close(fd[0]);
        //     close(fd[1]);
        //     exit(0);
        // }
        }
        else if (newString[0] == "addBATCH")
        {

        }
        else if (newString[0] == "exitPLS")
        {
            break;
        }
        else
        {
            printf("Invalid input. Please input a valid input.");
        }
    }
}
