#include "c:\borlandc\PROJECTS\CAD\CAD.h"
char initscr(char ON){ //------------------- I N I T S C R ----------------
static int gdriver = DETECT, gmode, errorcode;

if(!ON){
	   closegraph();
        return 1;
	   };
registerbgidriver(EGAVGA_driver);
registerbgifont(sansserif_font);
registerbgifont(small_font);
initgraph(&gdriver, &gmode, "");
errorcode = graphresult();
if (errorcode != grOk) return 0;
KEGA=getmaxy()/479.0;
VID=1.0/60.0;
drwscr();
return 1;
};



void drwscr(void){ // -------------  D R W S C R --------------------------
int i;
char *menus[]={"F1","F2","F3","F4","F5","F6","F7","F8",
			    "About"," ","Write","Move","View","Setup","Pens","Quit"};

cleardevice();

COLBK(LIGHTGRAY);
BAR(0,0,639,459);
COLBK(DARKGRAY);
BAR(45,35,505,355);
COLBK(WHITE);
BAR(50,40,500,350);
COLBK(BLACK);
BAR(505,35,550,355);
COLBK(WHITE);
BAR(515,100,540,140);

RECT(55,196,160,345,RED);
RECT(55,196,265,345,RED);
RECT(55,135,352,345,RED);
RECT(55,48,475,345,RED);

COLBK(WHITE);
for(i=0;i<8;i++){
	   BAR(i*80+20,460,i*80+70,479);
	   TEXT(i*80+2,466,menus[i],WHITE);
	   TEXT(i*80+24,466,menus[8+i],BLACK);
	   };
};


void status(char FULL){ //------------- S T A T U S --------------------
char buf[50];
int i;
if(FULL){
	   COLBK(DARKGRAY);
	   BAR(100,380,540,440);
	   COLBK(WHITE);
	   BAR(95,375,535,435);
	   RECT(97,377,532,432,BLACK);

	   TEXT(110,385,"Drawing:              Type:",BLACK);
	   sprintf(buf,"%s",path);
	   TEXT(180,385,buf,LIGHTRED);
	   TEXT(325,385,(TYPE) ? "Cut":"Plot",LIGHTRED);

	   TEXT(400,385,"Size:     ",BLACK);
	   sprintf(buf,"%8ld",INFSZ);
	   TEXT(430,385,buf,LIGHTRED);

	   TEXT(110,400,"Used pens:                              (    total)",BLACK);

	   TEXT(110,415,"Origin:  X=          Y=",BLACK);

	   for(i=0;i<8;i++){
			 if(PENS[i].use){
				    sprintf(buf,"%d ",i);
				    TEXT(200+i*15,400,buf,PENS[i].col);
				    };
			 };
	   sprintf(buf,"%2d",used);
	   TEXT(450,400,buf,LIGHTRED);
	   };

COLBK(WHITE);
BAR(200,414,275,424);
BAR(295,414,370,424);
sprintf(buf,"%ld mm",ORX+DX/40);
TEXT(203,415,buf,LIGHTRED);
sprintf(buf,"%ld mm",ORY+DY/40);
TEXT(298,415,buf,LIGHTRED);

};
