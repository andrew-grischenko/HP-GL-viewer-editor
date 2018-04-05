#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>
#include <bios.h>
#include <math.h>
#include <dir.h>
#include <conio.h>
#include <process.h>
#include <string.h>
#include <dos.h>
#include <ctype.h>

#define pi 3.1415926


enum cmd { AA=1,AR,CI,CT,FS,HM,LT,NR,PA,PD,PR,PU,SC,
		SP,XT,YT,CP,CS,DI,DR,DT,LB,SI,SL,SM,SR,
		DF,IN,IP,IW,OA,OC,OE,OF,OI,OO,OP,OS,OW,
		RO,TL,VS };

void LINE(long ,long ,long ,long ,int );
void BAR(int ,int ,int ,int );
void RECT(int , int , int , int , int );
void ARRC(long , long , float , int );
void CIRCLE(long , long , float, int );
void TEXT(int , int , const char *, int );
void COLBK(int );
void SET(long , long );

void wind(int ,int ,int, int, char *);
void progr(char ,int ,int ,long, long);
int getstr(FILE *);
char find(char *);
char initscr(char );
void DRW(char );
void type_c(char );
void type_str(char *, char );

long INFSZ;
char PEN;
int ARC_ANGL;
long TICK;
double S_A;
long S_W;
long S_H;
char TERM=3;
int PRES;
float SCX=1,SCY=1;
int COL;
char cmd;
int used;
union KEY {
	   int in;
	   char ch[2];
	   };

struct PEN {
	int col;
	};

struct PEN PENS[8];
char CURPEN;
long X,Y;
char buffer[256];
int n_parm;
char parm[20][10];
long MAXX,MAXY,MINX,MINY;
float KEGA;
float VID;
long DX;
long DY;
