#include<stdio.h>

int Jan1st_weekday_is(int x)
{
	return	(( (x)+(int)((float)(x-1)/(float)4)-(int)((float)(x-1)/(float)100)+(int)((float)(x-1)/(float)400))%7);
}

int isleap(int year)
{
	if(!(year%400)) return 1;
	else if(!(year%100)) return 0;
	else if(!(year%4)) return 1;
	else return 0;
}

int print_calendar_month(int month,int D,int days)
{
	int date,i;
	switch(month) 
	{
	    case 1:
	        printf("\nJAN\n");
	        break;
	    case 2:
	        printf("\nFEB\n");
	        break;
	    case 3:
	        printf("\nMAR\n");
	        break;
	    case 4:
	        printf("\nAPR\n");
	        break;
	    case 5:
	        printf("\nMAY\n");
	        break;
	    case 6:
	        printf("\nJUN\n");
	        break;
	    case 7:
	        printf("\nJUL\n");
	        break;
	    case 8:
	        printf("\nAUG\n");
	        break;
	    case 9:
	        printf("\nSEP\n");
	        break;
	    case 10:
	        printf("\nOCT\n");
	        break;
	    case 11:
	        printf("\nNOV\n");
	        break;
	    case 12:
	        printf("\nDEC\n");
	        break;
	}
	printf("----------------------------------------------------\n");
	printf("SUN\tMON\tTUE\tWED\tTHUR\tFRI\tSAT\n");
	date=1;
	for(i=0;i<D;i++) printf("\t");
	while(date<=days)
	{
		printf("%2d\t",date);
		D++;
		if(D>=7)
		{
			D%=7;
			printf("\n\n");
		}
		date+=1;
	}
	printf("\n");
	return D;
}

int main()
{
	int year,month,D,feb_days;
	while(1)
	{
		printf("YEAR:"); scanf("%d",&year);
		D=Jan1st_weekday_is(year);
		feb_days=(isleap(year))?29:28;
		D=print_calendar_month(1,D,31);
		D=print_calendar_month(2,D,feb_days);
		D=print_calendar_month(3,D,31);
		D=print_calendar_month(4,D,30);
		D=print_calendar_month(5,D,31);
		D=print_calendar_month(6,D,30);
		D=print_calendar_month(7,D,31);
		D=print_calendar_month(8,D,31);
		D=print_calendar_month(9,D,30);
		D=print_calendar_month(10,D,31);
		D=print_calendar_month(11,D,30);
		D=print_calendar_month(12,D,31);
		printf("\n");	
	}
	return 0;
}
