#include <stdio.h>
#include<stdlib.h>
#include <time.h>
// #include <unistd.h>
#include <string.h>

// int valid_date(int day, int mon, int year)    
// {
//     int is_valid = 1, is_leap = 0;
    
//     if (year >= 1800 && year <= 9999) 
//     {
 
//         //  check whether year is a leap year
//         if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) 
//         {
//             is_leap = 1;
//         }
        
//         // check whether mon is between 1 and 12
//         if(mon >= 1 && mon <= 12)
//         {
//             // check for days in feb
//             if (mon == 2)
//             {
//                 if (is_leap && day == 29) 
//                 {
//                     is_valid = 1;
//                 }
//                 else if(day > 28) 
//                 {
//                     is_valid = 0;
//                 }
//             }
            
//             // check for days in April, June, September and November
//             else if (mon == 4 || mon == 6 || mon == 9 || mon == 11) 
//             {
//                 if (day > 30)
//                 {
//                     is_valid = 0;
//                 }
//             }
 
//             // check for days in rest of the months 
//             // i.e Jan, Mar, May, July, Aug, Oct, Dec
//             else if(day > 31)
//             {            
//                 is_valid = 0;
//             }        
//         }
        
//         else
//         {
//             is_valid = 0;
//         }
 
//     }
//     else
//     {
//         is_valid = 0;
//     }
    
//     return is_valid;
// }

// int* remaining(int yyNow, int mmNow, int ddNow, int yy, int mm, int dd)
// {
//     int dd_diff, mm_diff, yy_diff;
//     int *diff = malloc(sizeof (char) * 3);

//     // time_t t = time(NULL);
//     // struct tm tm = *localtime(&t);

//     // ddNow = tm.tm_mday;
//     // mmNow = tm.tm_mon + 1;
//     // yyNow = tm.tm_year + 1900;

//     if(!valid_date(ddNow, mmNow, yyNow))
//     {
//         printf("First date is invalid.\n");
//         // return 0;
//     }
    
//     if(!valid_date(dd, mm, yy))
//     {
//         printf("Second date is invalid.\n");
//         // return 0;
//     }       
    
//     if(dd < ddNow)
//     {      
//         // borrow days from february
//         if (mm == 3)
//         {
//             //  check whether year is a leap year
//             if ((yy % 4 == 0 && yy % 100 != 0) || (yy % 400 == 0)) 
//             {
//                 dd += 29;
//             }
            
//             else
//             {
//                 dd += 28;
//             }                        
//         }
        
//         // borrow days from April or June or September or November
//         else if (mm == 5 || mm == 7 || mm == 10 || mm == 12) 
//         {
//            dd += 30; 
//         }
                
//         // borrow days from Jan or Mar or May or July or Aug or Oct or Dec
//         else
//         {
//            dd += 31;
//         }
        
//         mm = mm - 1;
//     }
    
//     if (mm < mmNow)
//     {
//         mm += 12;
//         yy -= 1;
//     }       
    
//     dd_diff = dd - ddNow;
//     diff[0] = dd_diff;
//     mm_diff = mm - mmNow;
//     diff[1] = mm_diff;
//     yy_diff = yy - yyNow;
//     diff[2] = yy_diff;
    
//     return diff;
// }

// int stringToInteger(char string[])
// {
//     int digit, j = 1, m = 0;
//     for (int i = strlen(string)-1; i >=0; i--)
//     {
//         digit = string[i];
//         digit = digit - 48;
//         m = m + (digit * j);
//         j = j * 10;
//     }
//     return m;
// }

// void remove_all_chars(char* str, char c) {
//     char *pr = str, *pw = str;
//     while (*pr) {
//         *pw = *pr++;
//         pw += (*pw != c);
//     }
//     *pw = '\0';
// }

// void delchar(char *x,int a, int b)
// {
// 	if ((a+b-1) <= strlen(x))
// 	{
// 		strcpy(&x[b-1],&x[a+b-1]);
// 		puts(x);
// 	}
// }

// void remchar(char *s, char chr)
// {
//    int i, j = 0;
//    for ( i = 0; s[i] != '\0'; i++ ) /* 'i' moves through all of original 's' */
//    {
//       if ( s[i] != chr )
//       {
//          s[j++] = s[i]; /* 'j' only moves after we write a non-'chr' */
//       }
//    }
//    s[j] = '\0'; /* re-null-terminate */
// }

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

    char* from, userInput[100];
    char * req[100];
    char * startDate[100];
    char * endDate[100];
    char * dueDate[100];
    int i, status, n, j;
    char * blank = " ";
    char * stp = "-";
    char * token;

    struct Date start[20];
    struct Date end[20];
    struct Date due[20];
    struct Order input[20];

    printf("~~WELCOME TO PLS~~\n");
    while (status == 0)
    {
        printf("Please enter:\n");
        fgets(userInput, sizeof userInput, stdin);

        from = userInput;
        token = strtok(from, blank);

        req[j] = token;
        token = strtok(NULL, blank);

        if (strcmp(req[j], "addPERIOD") == 0)
        {
            startDate[0] = token;
            token = strtok(NULL, blank);
            endDate[0] = token;

            token = strtok(startDate[0], stp);
            start->year[0] = atoi(token); 
            token = strtok(NULL, stp);
            start->mon[0] = atoi(token);
            token = strtok(NULL, stp);
            start->day[0] = atoi(token);
            // printf("%d\n", start->year[0]);
            // printf("%d\n", start->mon[0]);
            // printf("%d\n", start->day[0]);

            token = strtok(endDate[0], stp);
            end->year[0] = atoi(token); 
            token = strtok(NULL, stp);
            end->mon[0] = atoi(token);
            token = strtok(NULL, stp);
            end->day[0] = atoi(token);
            // printf("%d\n", end->year[0]);
            // printf("%d\n", end->mon[0]);
            // printf("%d\n", end->day[0]);
        }
        else if (strcmp(req[j], "addORDER") == 0)
        {
            input->orderID[i] = token;
            token = strtok(NULL, blank);
            dueDate[i] = token;
            token = strtok(NULL, blank);
            input->quantity[i] = atoi(token);
            token = strtok(NULL, blank);
            input->productName[i] = token;
            // printf("%s\n", input->orderID[i]);
            // printf("%s\n", dueDate[i]);
            // printf("%d\n", input->quantity[i]);
            // printf("%s\n", input->productName[i]);

            token = strtok(dueDate[i], stp);
            due->year[i] = atoi(token); 
            token = strtok(NULL, stp);
            due->mon[i] = atoi(token);
            token = strtok(NULL, stp);
            due->day[i] = atoi(token);
            // printf("%d\n", due->year[i]);
            // printf("%d\n", due->mon[i]);
            // printf("%d\n", due->day[i]);

            // for (n = 0; n < 3; n++)
            // {
            //     printf("%s",input->orderID[n]);
            // }  
            i++;
        }
        else if (strcmp(req[i], "exitPLS") == 0)
        {
            printf("Bye-bye!\n");
            status = 1;
        }
        else if (strcmp(req, "runPLS") == 0)
        {
            char * alg = token;
            token = strtok(NULL, blank);
            printf("%s\n", alg);
            // Schedule(input, start, end, due, alg, i);    dal's function
        }
        else
        {
            printf("Invalid Input!");   
        }
        // for (n = 0; n < 3; n++)
        // {
        //     printf("%s",req[n]);
        // }  
        // printf("%d", j);
        j++;
    }
}
