#include<iostream>
#include<cstdio>
#include<windows.h>
#include<conio.h>
#include<time.h>
#include<iomanip>

#define W 28 
#define H 8 

using namespace std;

int frame[4][4];
int round=0,MAX=0;

//void gotoxy(int xpos, int ypos);//

int rand_num();//
void rand_axis(int);//fix

void refresh();//
bool full();//
bool gg();//

bool w();
bool a();
bool s();
bool d();


int main()
{
	int x,y,i,j,mv;
	
	//清空frame
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			frame[i][j]=0;
		}
	} 
	//印框框 
	/*for(x=0;x<=W;x++)
	{
		for(y=0;y<=H;y++)
		{
			gotoxy(x,y);
			if(!(x%7)&&!(y%2))		cout<<"+";
			else if(!(x%7)&&(y%2))	cout<<"|";
			else if((x%7)&&!(y%2))	cout<<"-";
			else 					cout<<" ";
		}
	}*/
	//初始化遊戲 A.K.A 產生隨機的開局畫面->產生兩個位置放上2 
	rand_axis(1);
	rand_axis(1);
	//讀鍵盤
	char c;
	while(1)
	{
		c=getch();
		//移動位置 
		if(c=='w')		mv=a();
		else if(c=='a') mv=w();
		else if(c=='s') mv=d();
		else if(c=='d') mv=s();
		else if(c=='q') break;
		if(mv) round++;
		refresh();
		if(!full()&&mv) rand_axis(0);//generate a new number
		if((MAX==2048)||gg()) break;
	}
	

	return 0;
} 

/*(Y,X)
+------+------+------+------+ 
|(1, 3)|(1,10)|(1,17)|(1,24)|
+------+------+------+------+ 
|(3, 3)|(3,10)|(3,17)|(3,24)|
+------+------+------+------+ 
|(5, 3)|(5,10)|(5,17)|(5,24)|
+------+------+------+------+ 
|(7, 3)|(7,10)|(7,17)|(7,24)|
+------+------+------+------+
*/
/*
[0,0,0,0],
[0,0,0,0],
[0,0,0,0],
[0,0,0,0]
*/


/*void gotoxy(int xpos, int ypos)
{
  COORD scrn;
  HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
  scrn.X = xpos; scrn.Y = ypos;
  SetConsoleCursorPosition(hOuput,scrn);
}*/

int rand_num()
{
	srand((unsigned)time(NULL));
	int num;
	num= (rand()%2);
	return (num+1)*2;
}
void rand_axis(int init)
{
	int i, j;
	while (frame[i][j])                           //該位置上的數不是0，重新產生
	{
		i = (rand() % (4)) ;
		j = (rand() % (4)) ;
	}
	if(init)	frame[i][j]=2;
	else		frame[i][j]=rand_num();
	//將結果同步到螢幕上 
	refresh();
}

void refresh()
{
	system("cls");
	int i,j,x,y;
	for(i=0;i<4;i++)
	{
		printf("-----------------------------\n");
		for(j=0;j<4;j++)
		{
			if(frame[i][j] > MAX) MAX=frame[i][j];
			printf("| ");
			if(frame[i][j])printf("%4d",frame[i][j]);
			else printf("    ");
			printf(" ");
		}
		
		printf("|\n");
	}
	printf("-----------------------------\n");
	cout<<"\n\tROUND:"<<round<<"  "<<"MAX:"<<MAX<<"\n"<<endl;
	if(MAX==2048) printf("\tCONGRATULATIONS!\n");
	if(gg()) printf("\n\tGAMEOVER\n\n");
}

bool full()
{
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<4;j++)
		{
			if(frame[i][j]==0)
				return 0;
		}
	}
	return 1;
}

bool gg()	//0:continue  1:gameover
{
	if(!full()) return 0;
	else
	{
		for(int i=0;i<4;i++)
		{
			for(int j=0;j<4;j++)
			{
				if((i!=0)&&(frame[i][j]==frame[i-1][j])) return 0;	//check i-1, j
				if((i!=3)&&(frame[i][j]==frame[i+1][j])) return 0;	//check i+1, j
				if((j!=0)&&(frame[i][j]==frame[i][j-1])) return 0;	//check i, j-1
				if((j!=3)&&(frame[i][j]==frame[i][j+1])) return 0;	//check i, j+1
			} 
		}
	}
	return 1;
}

bool w()//UP 由上往下掃描 
{
	int x,y,i,j,flag=1;
	bool mv=0;
	bool merge[4]={0};
	while(flag)
	{
		flag=0;
		for(i=0;i<4;i++)//掃描 
		{
			for(j=1;j<4;j++)//掃描 
			{
				if((frame[i][j]!=0)&&(frame[i][j-1]==0))//移動 
				{
					frame[i][j-1]=frame[i][j];
					frame[i][j]=0;
					flag++;
					mv=1;
				}
				else if((frame[i][j]!=0)&&(frame[i][j-1]==frame[i][j])&&(!merge[i]))//合併 
				{
					frame[i][j-1]*=2;
					frame[i][j]=0;
					flag++;
					merge[i]=1;
					mv=1;
				}
			}
		}
	}
	return mv;
}

bool a()//LEFT
{
	int x,y,i,j,flag=1;
	bool merge[4]={0};
	bool mv;
	while(flag)
	{
		flag=0;
		for(i=1;i<4;i++)//掃描 
		{
			for(j=0;j<4;j++)//掃描 
			{
				if((frame[i][j]!=0)&&(frame[i-1][j]==0))//移動 
				{
					frame[i-1][j]=frame[i][j];
					frame[i][j]=0;
					flag++;
					mv=1;
				}
				else if((frame[i][j]!=0)&&(frame[i-1][j]==frame[i][j])&&(!merge[j]))//合併 
				{
					frame[i-1][j]*=2;
					frame[i][j]=0;
					flag++;
					mv=1;
					merge[j]=1;
				}
			}
		}
	}
	return mv;
}


bool s()//DOWN 由下往上掃描 
{
	int x,y,i,j,flag=1;
	bool mv=0;
	bool merge[4]={0};
	while(flag)
	{
		flag=0;
		for(i=0;i<4;i++)//掃描 
		{
			for(j=2;j>=0;j--)//掃描 
			{
				if((frame[i][j]!=0)&&(frame[i][j+1]==0))//移動 
				{
					frame[i][j+1]=frame[i][j];
					frame[i][j]=0;
					flag++;
					mv=1;
				}
				else if((frame[i][j]!=0)&&(frame[i][j+1]==frame[i][j])&&(!merge[i]))//合併 
				{
					frame[i][j+1]*=2;
					frame[i][j]=0;
					flag++;
					merge[i]=1;
					mv=1;
				}
			}
		}
	}
	return mv;
}

bool d()//Right
{
	int x,y,i,j,flag=1;
	bool merge[4]={0};
	bool mv=0;
	while(flag)
	{
		flag=0;
		for(i=2;i>=0;i--)//掃描 
		{
			for(j=0;j<4;j++)//掃描 
			{
				if((frame[i][j]!=0)&&(frame[i+1][j]==0))//移動 
				{
					frame[i+1][j]=frame[i][j];
					frame[i][j]=0;
					flag++;
					mv=1;
				}
				else if((frame[i][j]!=0)&&(frame[i+1][j]==frame[i][j])&&(!merge[j]))//合併 
				{
					frame[i+1][j]*=2;
					frame[i][j]=0;
					flag++;
					merge[j]=1;
					mv=1;
				}
			}
		}
	}
	return mv;
}
/*
system("Pause");
system("cls");
printf(" Round: score:");
system("color a");
  ____    ____
 /    \  /    \         ___
 |       |         O   | __\
 |  ___  |  ___        |___/
 \____/  \____/    O   |
*/
