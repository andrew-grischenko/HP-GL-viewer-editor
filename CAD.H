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
#define bufferr(i) (if((i)>100) error())


enum cmd { AA=1,AR,CI,CT,FS,HM,LT,NR,PA,PD,PR,PU,SC,
		SP,XT,YT,CP,CS,DI,DR,DT,LB,SI,SL,SM,SR,
		DF,IN,IP,IW,OA,OC,OE,OF,OI,OO,OP,OS,OW,
		RO,TL,VS };

enum boxs { ABOUT=0, SAVE, SETUP, MOVE, PENSS, ASK, PENS_ };

enum keys { ARR=0x4D, ARL=0x4B, ARU=0x48, ARD=0x50,
		TAB=0x09,ENTER=0x0D, ESC=0x1B,BKSPC=0x08,SPC=0x20,
		F1=0x3B,F2,F3,F4,F5,F6,F7,F8,F9,F10 };

enum but { OK=254,CANCEL };

enum CM { Normal, Escape, Label, String };

struct OLD {
    char TYPE;
    char AUTO;
    char CONVERT;
    long PX1;
    long PY1;
    long PX2;
    long PY2;
    long XMIN;
    long YMIN;
    long XMAX;
    long YMAX;
    long XW1;
    long YW1;
    long XW2;
    long YW2;
    };

union KEY {
	   int in;
	   char ch[2];
	   };

struct PEN {
	char use;
	char VS_;
	char FS_;
	int col;
	};

void LINE(long ,long ,long ,long ,int );
void BAR(int ,int ,int ,int );
void RECT(int , int , int , int , int );
void ARRC(long , long , float , int );
void CIRCLE(long , long , float, int );
void TEXT(int , int , const char *, int );
void COLBK(int );
void SET(long , long );
void BUT(int ,int ,char * ,int  );

void wind(int ,int ,int, int, char *);
void error(void);
double arctan(long ,long);
void progr(char ,int ,int ,long, long);
void drwscr(void);
char find(char *);
void save(void);
char initscr(char );
void DRW(char );
void type_c(char );
void type_str(char *, char );
int fget_(FILE *);
int getstr(FILE *);
char initscr(char );
void drwscr(void);
void status(char );
void ungetstr(void);
void unget_(char);


extern char ungc;
extern char ungs;
extern long INFSZ;
extern long OVER;
extern char VS_;
extern char FS_;
extern long THERE;
extern char PEN;
extern int ARC_ANGL;
extern long TICK;
extern double S_A;
extern long S_W;
extern long S_H;
extern char TERM;
extern int PRES;
extern char IGNORESP;
extern char SETVS;
extern char NOTGET;
extern char CONVERT;
extern char AUTO;
extern char CHANGED;
extern float SCX,SCY;
extern int COL;
extern long ORX;
extern long ORY;
extern char cmd;
extern char *path;
extern char pathold[50];
extern FILE *in_plt;
extern int used;
extern struct PEN PENS[8];
extern enum CM CMD_TYPE;
extern char CURPEN;
extern char TYPE;
extern char TYPE_;
extern long X,Y;
extern char buffer[100];
extern char UNGETB[4][100];
extern char DBL;
extern int n_parm;
extern char parm[20][10];
extern long MAXX,MAXY,MINX,MINY;
extern long XMIN,XMAX,YMIN,YMAX;
extern long PX1,PX2,PY1,PY2;
extern long XW1,XW2,YW1,YW2;
extern long DX,DY;
extern float KEGA;
extern float VID;
extern char SAVED;
