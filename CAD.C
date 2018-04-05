#include "c:\borlandc\PROJECTS\CAD\CAD.h"
 char ungc;
 char ungs;
 long INFSZ;
 long OVER;
 char VS_;
 char FS_;
 long THERE;
 char PEN;
 int ARC_ANGL;
 long TICK;
 double S_A;
 long S_W;
 long S_H;
 char TERM;
 int PRES;
 char IGNORESP;
 char SETVS;
 char NOTGET;
 char CONVERT;
 char AUTO;
 char CHANGED;
 float SCX,SCY;
 int COL;
 long ORX;
 long ORY;
 char cmd;
 char *path;
 char pathold[50];
 FILE *in_plt;
 int used;
 struct PEN PENS[8];
 enum CM CMD_TYPE;
 char CURPEN;
 char TYPE;
 char TYPE_;
 long X,Y;
 char buffer[100];
 char UNGETB[4][100];
 char DBL;
 int n_parm;
 char parm[20][10];
 long MAXX,MAXY,MINX,MINY;
 long XMIN,XMAX,YMIN,YMAX;
 long PX1,PX2,PY1,PY2;
 long XW1,XW2,YW1,YW2;
 long DX,DY;
 float KEGA;
 float VID;
 char SAVED;
unsigned int time;

char *CLR[]={"BLACK","BLUE","GREEN","CYAN",
		"RED","MAGENTA","BROWN","LIGHTGRAY"};


int main(int argc, char *argv[]){  //------------------ M A I N -----------
void drwrect(void);
int INT(long );
void analise(FILE *);
void status(char );
char ask(void);
char diabox(char );
void view(FILE *);


union KEY k;
int i;
UNGETB[0][0]=0;
UNGETB[1][0]=0;
UNGETB[2][0]=0;

printf(" Plot CAD    (C) 1995  ESCO ltd.                        v2.90 \n\n");
delay(500);

switch (argc) {

	   case 2:
			 in_plt=fopen(argv[1],"r");
			 if(in_plt==NULL){
				    printf("   Sorry, can`t open %s ...\n");
				    return 0;
				    };
			 path=argv[1];
			 SAVED=1;
			 break;

	   default:
			 printf("Usage :\n");
			 printf("cad[.exe] filename[.plt] \n");
			 return 0;
	   };

if(!initscr(1)){
	   printf("   Sorry, but needed EGA graphics mode not available ...\n");
	   return 0;
	   };
PX1=XMIN=XW1=PY1=YMIN=YW1=0;
PX2=XMAX=XW2=33600;
PY2=YMAX=YW2=24000;
DBL=0;
CMD_TYPE=Normal;
TERM=3;
IGNORESP=0;
SETVS=0;
NOTGET=0;
CONVERT=0;
AUTO=0;
SCX=SCY=1;
THERE=0;
ungc=ungs=0;

{
struct ffblk ff[1];
findfirst(argv[1],ff,0);
INFSZ=ff[0].ff_fsize;
}


rewind(in_plt);
MAXX=MAXY=0;
MINX=MINY=32767;
ARC_ANGL=1;
OVER=30;
for(i=0;i<8;i++){
	   PENS[i].use=0;
	   PENS[i].col=i;
	   PENS[i].VS_=12;
	   PENS[i].FS_=0;
	   };
PENS[0].use=1;
used=1;
TYPE=0;

analise(in_plt);
drwscr();

DX=0;
DY=0;
ORY=MINY/40;
ORX=MINX/40;
TYPE_=TYPE;

status(1);
drwrect();
while(1){
	   time=0;
	   while(!bioskey(1));
	   k.in=bioskey(0);
	   if(k.ch[0]==27){
			 char swit;
			 if(!SAVED){
				    if((swit=diabox(ASK))==1) diabox(SAVE);
				    if(swit==0){
						drwscr();
						status(1);
						goto cont;
						};
				    };
			 initscr(0);
			 fclose(in_plt);
			 sprintf(buffer,"del cad.$$$");
			 system(buffer);
			 return 0;
			 };
	   drwrect();
cont:
	   switch (k.ch[1]){
			 case ARL :
				    DX-=160;
				    status(0);
				    SAVED=0;
				    break;
			 case ARR :
				    DX+=160;
				    status(0);
				    SAVED=0;
				    break;
			 case ARD :
				    DY-=160;
				    status(0);
				    SAVED=0;
				    break;
			 case ARU :
				    DY+=160;
				    status(0);
				    SAVED=0;
				    break;
			 case F1 :
				    diabox(ABOUT);
				    drwscr();
				    status(1);
				    break;
                case F2 :
                        break;
			 case F3 :
				    diabox(SAVE);
				    drwscr();
				    status(1);
				    break;
			 case F4 :
				    diabox(MOVE);
				    drwscr();
				    status(1);
				    SAVED=0;
				    break;
			 case F5 :
				    rewind(in_plt);
				    view(in_plt);
				    drwscr();
				    status(1);
				    break;
			 case F6 :
				    diabox(SETUP);
				    SCX=(float)(PX2-PX1)/(XMAX-XMIN);
				    SCY=(float)(PY2-PY1)/(YMAX-YMIN);
				    drwscr();
				    status(1);
				    break;
			 case F7 : {
				char p;
				while((p=diabox(PENSS))<8){
						diabox(PENS_+p);
						drwscr();
						status(1);
						};
				    drwscr();
				    status(1);
				    break;
				    }
			 case F8 :
			 case F9 :
			 case F10 :{
				    char swit;
				    if(!SAVED){
						  if((swit=diabox(ASK))==1) diabox(SAVE);
						  if(swit==0){
							drwscr();
							status(1);
							  break;
							  };
						  };

				    initscr(0);
				    fclose(in_plt);
				    sprintf(buffer,"del cad.$$$");
				    system(buffer);
				    return 0;
				    }
			 };
	   drwrect();
	   status(0);
	   };

};

void drwrect(void){ //------------------ D R W R E C T --------------------
setwritemode(1);
RECT(   INT((DX+       PX1+(MINX-XMIN)*SCX  )/80+55l),
	   INT((345-(DY+  PY1+(MINY-YMIN)*SCY  )/80)*KEGA),
	   INT((DX+       PX2+(MAXX-XMAX)*SCX  )/80+55l),
	   INT((345-(DY+  PY2+(MAXY-YMAX)*SCY  )/80)*KEGA),
	   YELLOW);

setwritemode(0);
return ;
};

void analise(FILE *plt){//--------------- A N A L I S E ---------------------
void check(long, long);
long x,y;
int i;
FILE *swp;
swp=fopen("cad.$$$","w");
fprintf(swp,"%c.Y",27);
fprintf(swp,"%c.@;3:",27);
fprintf(swp,"%c.I50;;17:",27);
fprintf(swp,"%c.N;19:",27);
fprintf(swp,"IN;IW;IP;SC;\n");

wind(100,100,300,175,"Analising...");
progr(1,0,0,0,0);
SET(0,0);
while(getstr(plt)!=EOF){
	   switch(cmd){
			 case AA :{
				    long xc,yc;
				    float angle;
				    double start;
				    int a=0;
				    double modul;
				    long x,y;

				    xc=atol(parm[0]);
				    yc=atol(parm[1]);
				    angle=atof(parm[2]);
				    modul=((xc-(double long)X)
						*(xc-(double long)X)
						+(yc-(double long)Y)
						*(yc-(double long)Y));
				    modul=sqrtl(modul);
				    if(n_parm>2) ARC_ANGL=atoi(parm[3]);

				    if(angle<0) ARC_ANGL=-abs(ARC_ANGL);
				    else ARC_ANGL=abs(ARC_ANGL);
				    start=atan2(Y-yc,X-xc);
				    do {
						  a+=ARC_ANGL;
						  x=xc+modul*cos(a*pi/180.0+start);
						  y=yc+modul*sin(a*pi/180.0+start);
						  if(PEN) check(x,y);
						  SET(x,y);
						  } while (abs(a)<abs(floor(angle)));

				    fprintf(swp,"AA%ld,%ld,%.0f",xc,yc,angle);
				    if(n_parm>2) fprintf(swp,",%d",ARC_ANGL);
				    fprintf(swp,";");
				    break;
				    }

			 case AR :{
				    long xc,yc;
				    long p1,p2;
				    float angle;
				    double start;
				    int a=0;
				    double modul;
				    long x,y;

				    p1=atol(parm[0]);
				    p2=atol(parm[1]);
				    xc=X+p1;
				    yc=Y+p2;
				    angle=atof(parm[2]);
				    modul=(p1*p1+p2*p2);
				    modul=sqrtl(modul);
				    if(n_parm>2) ARC_ANGL=atoi(parm[3]);

				    if(angle<0) ARC_ANGL=-abs(ARC_ANGL);
				    else ARC_ANGL=abs(ARC_ANGL);
				    start=atan2(Y-yc,X-xc);
				    do {
						  a+=ARC_ANGL;
						  x=xc+modul*cos(a*pi/180.0+start);
						  y=yc+modul*sin(a*pi/180.0+start);
						  if(PEN) check(x,y);
						  SET(x,y);
						  } while (abs(a)<abs(floor(angle)));

				    fprintf(swp,"AR%ld,%ld,%.0f",p1,p2,angle);
				    if(n_parm>2) fprintf(swp,",%d",ARC_ANGL);
				    fprintf(swp,";");
				    break;
				    }

			 case CI :{
				    long radius;
				    radius=atol(parm[0]);
				    ARC_ANGL=atoi(parm[1]);
				    check(X+radius,Y+radius);
				    check(X-radius,Y+radius);
				    check(X+radius,Y-radius);
				    check(X-radius,Y-radius);
				    fprintf(swp,"CI%ld",radius);
				    if(n_parm>1) fprintf(swp,",%d",ARC_ANGL);
				    fprintf(swp,";");
				    break;
				    }

			 case PA :{
				    for(i=0;i<n_parm; ){
						  x=atol(parm[i++]);
						  y=atol(parm[i++]);
						  if(PEN) check(x,y);
						  fprintf(swp,"PA%ld,%ld;",x,y);
						  SET(x,y);
						  };
				    break;
				    }

			 case PR :{
				    for(i=0;i<n_parm; ){
						  x=X+atol(parm[i++]);
						  y=Y+atol(parm[i++]);
						  if(PEN) check(x,y);
						  fprintf(swp,"PR%ld,%ld;",x-X,y-Y);
						  SET(x,y);
						  };
				    break;
				    }

			 case PD :{
				    if(!PEN) fprintf(swp,"PD;");
				    PEN=1;
				    check(X,Y);
				    for(i=0;i<n_parm; ){
						  x=atol(parm[i++]);
						  y=atol(parm[i++]);
						  if(PEN) check(x,y);
						  fprintf(swp,"PA%ld,%ld;",x,y);
						  SET(x,y);
						  };
				    break;
				    }

			 case PU :{
				    if(PEN) fprintf(swp,"PU;");
				    PEN=0;
				    for(i=0;i<n_parm; ){
						  x=atol(parm[i++]);
						  y=atol(parm[i++]);
						  fprintf(swp,"PA%ld,%ld;",x,y);
						  SET(x,y);
						  };
				    break;
				    }

			 case SP :{
				    if(buffer[2]!=';'){
						  int p;
						  p=atoi(parm[0]);
						  if(p>7) break;
						  if(PENS[p].use){
							CURPEN=p;
							break;
							};
						  PENS[p].use=1;
						  used++;
						  };
				    if(!n_parm) fprintf(swp,"SP0;");
				    else fprintf(swp,"SP%d;",atoi(parm[0]));
				    break;
				    }
			 case LB :{
					int i=0;
					while(buffer[i]!=TERM) fprintf(swp,"%c",buffer[i++]);
					fprintf(swp,"%c",TERM);
					}

			 case VS :{
				    VS_=atoi(parm[0]);
				    PENS[CURPEN].VS_=VS_;
				    break;
				    }

			 case FS :{
				    TYPE=1;
				    FS_=atol(parm[0]);
				    PENS[CURPEN].FS_=FS_;
				    break;
				    }

			 case SI :{
					S_W=12*atol(parm[0]);
					S_H=12*atol(parm[1]);
					fprintf(swp,"%s",buffer);
					break;
					}

			 case DI :{
					S_A=atan2(atol(parm[1]),atol(parm[0]));
					fprintf(swp,"%s",buffer);
					break;
					}

			 case SC :
				if(n_parm){
					XMIN=atol(parm[0]);
					XMAX=atol(parm[1]);
					YMIN=atol(parm[2]);
					YMAX=atol(parm[3]);
					};
				break;


			 case IP :{
				if(n_parm){
					PX1=atol(parm[0]);
					PY1=atol(parm[1]);
					PX2=atol(parm[2]);
					PY2=atol(parm[3]);
					};
				break;
				}

			 case IW :
				break;

			 case IN:
				break;

			 default:
				    fprintf(swp,"%s",buffer);
				    break;
			 };
			 if(bioskey(1)){
				union KEY k;
				k.in=bioskey(0);
				if(k.ch[0]==27){
					fclose(in_plt);
					sprintf(buffer,"del cad.$$$");
					system(buffer);
					initscr(0);
					exit(0);
					};
				};

	   progr(0,125,140,ftell(plt),INFSZ);
	   };
SCX=(float)(PX2-PX1)/(XMAX-XMIN);
SCY=(float)(PY2-PY1)/(YMAX-YMIN);


fclose(plt);
fclose(swp);
in_plt=fopen("cad.$$$","r");
};

void check(long x, long y){ //------------------ C H E C K -----------------
long min_(long,long);
long max_(long,long);
	   MAXX=max_(MAXX,x);
	   MAXY=max_(MAXY,y);
	   MINX=min_(MINX,x);
	   MINY=min_(MINY,y);
	   };

void view(FILE *plt){ //-------------------- V I E W ---------------------
cleardevice();
COLBK(RED);
BAR(0,0,639,479);
COLBK(WHITE);
BAR(3,3,636,476);
SET(0,0);
PEN=0;
ARC_ANGL=1;
while(getstr(plt)!=EOF){
	if(bioskey(1)){
		union KEY k;
		k.in=bioskey(0);
		if(k.ch[0]==27){
			return ;
			};
		};

	DRW(cmd);
	};
while(!bioskey(1));
bioskey(0);
};


void DRW(char cmd){//---------------------- D R W --------------------------
long x,y;

switch(cmd){
	   case AA :{
			 long xc,yc;
			 float angle;
			 xc=atol(parm[0]);
			 yc=atol(parm[1]);
			 angle=atof(parm[2]);
			 if(n_parm>2) ARC_ANGL=atoi(parm[3]);
			 ARRC(xc,yc,angle,COL);
			 break;
			 }

	   case AR:{
			 long xc,yc;
			 float angle;
			 xc=X+atol(parm[0]);
			 yc=Y+atol(parm[1]);
			 angle=atof(parm[2]);
			 if(n_parm>2) ARC_ANGL=atoi(parm[3]);
			 ARRC(xc,yc,angle,COL);
			 break;
			 }

	   case CI :{
			 long radius;
			 radius=atol(parm[0]);
			 if(n_parm>1) ARC_ANGL=atoi(parm[3]);
			 CIRCLE(X,Y,radius,COL);
			 break;
			 }

	   case HM :{
			 X=0;
			 Y=0;
			 break;
			 }

	   case PA :{
			 int i;
			 for(i=0;i<n_parm; ){
				    x=atol(parm[i++]);
				    y=atol(parm[i++]);
				    if(PEN) LINE(X,Y,x,y,COL);
				    SET(x,y);
				    };
			 break;
			 }

	   case PR :{
			 int i;
			 for(i=0;i<n_parm; ){
				    x=X+atol(parm[i++]);
				    y=Y+atol(parm[i++]);
				    if(PEN) LINE(X,Y,x,y,COL);
				    SET(x,y);
				    };
			 break;
			 }

	   case PD :{
			 int i;
			 PEN=1;
			 for(i=0;i<n_parm; ){
				    x=atol(parm[i++]);
				    y=atol(parm[i++]);
				    LINE(X,Y,x,y,COL);
				    SET(x,y);
				    };
			 break;
			 }

	   case PU :{
			 int i;
			 PEN=0;
			 for(i=0;i<n_parm;){
				    x=atol(parm[i++]);
				    y=atol(parm[i++]);
				    SET(x,y);
				    };
			 break;
			 }

	   case SP :{
			 if(n_parm){
				int p;
				p=atoi(parm[0]);
				if(p>7) break;
				COL=PENS[p].col;
				break;
				};
			 break;
			 }

	   case XT :{
			 LINE(X,Y-TICK/2,X,Y+TICK/2,COL);
			 break;
			 }

	   case YT :{
			 LINE(X-TICK/2,Y,X+TICK/2,Y,COL);
			 break;
			 }

	   case TL:{
			 TICK=atol(parm[0]);
			 // parm[1]-?
			 break;
			 }

	   case LB :{
			type_str(buffer+2,0);
			break;
			}

	   case SM :{
			type_str(buffer+2,1);
			break;
			}

	   case DI :{
			S_A=atan2(atof(parm[1]),atof(parm[0]));
			break;
			}

	   case SI :{
			 S_W=12*atof(parm[0]);
			 S_H=12*atof(parm[1]);
			 break;
			 }

	   case DT :{
			 TERM=parm[0][0];
			 break;
			 }

	   default: break;
	   };

};


char find(char *buf){ //----------------- F I N D ---------------------
char *com[]={
		 "AA","AR","CI","CT","FS","HM","LT","NR","PA","PD","PR","PU","SC",
		 "SP","XT","YT","CP","CS","DI","DR","DT","LB","SI","SL","SM","SR",
		 "DF","IN","IP","IW","OA","OC","OE","OF","OI","OO","OP","OS","OW",
		 "RO","TL","VS"
		 };

int find=0;
do {
	if(strncmp(com[find],buf,2)==0) return find+1;
	} while(find++<42);
return -1;
};




void progr(char res,int sx,int sy,long current,long total){ // --PROGR------
static long old;
if(res){
	   old=0;
	   return ;
	   };

if((float)(current-old)/total>0.05 ){
        RECT(sx,sy,sx+150,sy+20,BLUE);
	   COLBK(BLUE);
	   BAR(sx,sy,sx+(150*current)/(float)total,sy+20);
	   old=current;
        };
};

void wind(int x1,int y1,int x2,int y2,char *title){//---- W I N D -------

COLBK(DARKGRAY);
BAR(x1+10,y1+10,x2+10,y2+10);
COLBK(LIGHTBLUE);
BAR(x1,y1,x2,y2);
RECT(x1+5,y1+5,x2-5,y2-5,BLACK);
TEXT( (x2-x1-strlen(title)*8)/2.0+x1,y1+15,title,WHITE);
return ;
};

char diabox(char name){ // ---------- D I A B O X -----------------------
float inp_long(int ,int, int ,long );
void inp_b(void);
char *inp_str(int ,int ,int, char *);
void change(int *,int);
void setold(struct OLD *);

int ptrField=1;

switch(name){

	   case ABOUT:
			wind(200,200,390,320,"About...");
			TEXT(220,235,"Plot CAD    HP-GL",WHITE);
			TEXT(225,250,"plot/cutter mode",WHITE);
			TEXT(240,265,"Version 2.90",LIGHTRED);
			BUT(260,280,"Ok !",LIGHTBLUE);
			inp_b();
			return 0;

	   case PENS_:
	   case PENS_+1:
	   case PENS_+2:
	   case PENS_+3:
	   case PENS_+4:
	   case PENS_+5:
	   case PENS_+6:
	   case PENS_+7:{
			char wb[256];
			char p;
			struct PEN old;
			p=name-PENS_;
			old.col=PENS[p].col;
			old.VS_=PENS[p].VS_;
			old.FS_=PENS[p].FS_;

			wind(155,150,410,270,"Pen setup...");
			TEXT(165,185,"Pen    Color      VS     FS",WHITE);
			TEXT(165,195,"-----------------------------",WHITE);
			COLBK(DARKGRAY);
			BAR(205,205,280,223);
			COLBK(BLACK);
			BAR(290,205,340,223);
			BAR(350,205,400,223);
			sprintf(wb,"%d",p);
			TEXT(170,210,wb,WHITE);
			TEXT(210,210,CLR[ PENS[p].col ],PENS[p].col);
			sprintf(wb,"%2d",PENS[p].VS_);
			TEXT(303,210,wb,YELLOW);
			sprintf(wb,"%d",PENS[p].FS_);
			TEXT(358,210,wb,YELLOW);

			BUT(210,233,"Set",BLACK);
			BUT(290,233,"Cancel",BLACK);
			swp2:
			switch(ptrField){
				case 1:
					BUT(290,233,"Cancel",BLACK);
					inp_b();
					if(PRES==ESC){
							PENS[p].col=old.col;
							PENS[p].VS_=old.VS_;
							PENS[p].FS_=old.FS_;
							return 0;
							};
					if(PRES==SPC){
							COLBK(DARKGRAY);
							BAR(205,205,280,223);
							PENS[p].col++;
							if(PENS[p].col>7) PENS[p].col=0;
							TEXT(210,210,CLR[ PENS[p].col ],PENS[p].col);
							break;
							};
					  if( (PRES==TAB)||(PRES==ENTER) ){
							change(&ptrField,3);
							break;
							};
					  break;


				    case 2:
						  PENS[p].VS_=inp_long(300,210,2,PENS[p].VS_);
						  change(&ptrField,3);
						  break;

				    case 3:
						  PENS[p].FS_=inp_long(355,210,3,PENS[p].FS_);
						  change(&ptrField,3);
						  break;

				    case OK:
						  BUT(210,233,"Set",LIGHTBLUE);
						  inp_b();
						  if(PRES==TAB) change(&ptrField,3);
						  if(PRES==ENTER){
								return 0;
								};
						  break;

				    case CANCEL:
						  BUT(210,233,"Set",BLACK);
						  BUT(290,233,"Cancel",LIGHTBLUE);
						  inp_b();
						  if(PRES==ENTER){
							PENS[p].col=old.col;
							PENS[p].VS_=old.VS_;
							PENS[p].FS_=old.FS_;
							return 0;
								};
						  if(PRES==TAB) change(&ptrField,3);
						  break;
				    };
				    if(PRES==ESC){
					PENS[p].col=old.col;
							PENS[p].VS_=old.VS_;
							PENS[p].FS_=old.FS_;
							return 0;
						  };
				    goto swp2;
			}
	   case SAVE:{

			 strcpy(pathold,path);
			 wind(100,100,400,178,"Save As...");
			 BUT(320,110,"Save",BLACK);
			 BUT(320,140,"Cancel",BLACK);
			 ssw:
			 COLBK(BLACK);
			 switch(ptrField){
				    case 1:
						  BUT(320,140,"Cancel",BLACK);
						  strcpy(path,inp_str(110,133,20,path));
						  change(&ptrField,1);
						  break;
				    case OK:
						  BUT(320,110,"Save",LIGHTBLUE);
						  inp_b();
						  if(PRES==TAB) change(&ptrField,2);
						  if(PRES==ENTER){
								wind(100,100,300,175,"Saving ...");
								progr(1,0,0,0,0);
								save();
								SAVED=1;
								return 0;
								};
						  break;

				    case CANCEL:
						  BUT(320,110,"Save",BLACK);
						  BUT(320,140,"Cancel",LIGHTBLUE);
						  inp_b();
						  if(PRES==ENTER){
								strcpy(path,pathold);
								return 0;
								};
						  if(PRES==TAB) change(&ptrField,2);
						  break;
				    };
				    if(PRES==ESC){
						  strcpy(path,pathold);
						  return 0;
						  };
				    goto ssw;
				    }

	   case SETUP:{
			 struct OLD old;
			 old.PX1=PX1;
			 old.PY1=PY1;
			 old.PX2=PX2;
			 old.PY2=PY2;
			 old.XMIN=XMIN;
			 old.YMIN=YMIN;
			 old.XMAX=XMAX;
			 old.YMAX=YMAX;
			 old.XW1=XW1;
			 old.YW1=YW1;
			 old.XW2=XW2;
			 old.YW2=YW2;
			 old.TYPE=TYPE;
			 old.AUTO=AUTO;
			 old.CONVERT=CONVERT;

			 wind(100,50,350,430,"Parameters Setup...");
			 TEXT(110,90, "      File Type",WHITE);
			 TEXT(110,110,"     Scale Mode",WHITE);
			 TEXT(110,130,"    Convert Arc",WHITE);
			 TEXT(110,150,"IP value   P1 x",WHITE);
			 TEXT(110,170,"              y",WHITE);
			 TEXT(110,190,"           P2 x",WHITE);
			 TEXT(110,210,"              y",WHITE);
			 TEXT(110,230,"SC value   Xmin",WHITE);
			 TEXT(110,250,"           Ymin",WHITE);
			 TEXT(110,270,"           Xmax",WHITE);
			 TEXT(110,290,"           Ymax",WHITE);
			 TEXT(110,310,"IW value   Xmin",WHITE);
			 TEXT(110,330,"           Ymin",WHITE);
			 TEXT(110,350,"           Xmax",WHITE);
			 TEXT(110,370,"           Ymax",WHITE);
			 BUT(120,395,"Accept",BLACK);
			 BUT(195,395,"Default",BLACK);
			 BUT(270,395,"Cancel",BLACK);
			 COLBK(BLACK);

			 setold(&old);

			 swset:
			 switch(ptrField){
				    case 1:
						  BUT(270,395,"Cancel",BLACK);
						  TEXT(245,90,(TYPE) ? "Cut":"Plot",WHITE);
						  inp_b();
						  switch(PRES){
								case ESC:
									   setold(&old);
									   return 0;
								case TAB:
								case ENTER:
									   change(&ptrField,16);
									   break;
								case SPC:
									   TYPE=!TYPE;
									   COLBK(BLACK);
									   CHANGED=TYPE-TYPE_;
									   BAR(240,87,310,102);
									   TEXT(245,90,(TYPE) ? "Cut":"Plot",WHITE);
									   break;
								};
						  break;

				    case 2:
						  TEXT(245,90,(TYPE) ? "Cut":"Plot",YELLOW);
						  TEXT(245,110,(AUTO) ? "Auto":"Manual",WHITE);
						  inp_b();
						  switch(PRES){
								case ESC:
									setold(&old);
									   return 0;
								case TAB:
								case ENTER:
									   change(&ptrField,16);
									   break;
								case SPC:
									   AUTO=!AUTO;
									   COLBK(BLACK);
									   BAR(240,107,310,122);
									   TEXT(245,110,(AUTO) ? "Auto":"Manual",WHITE);
									   break;
								};
						  break;

				    case 3:
						  TEXT(245,110,(AUTO) ? "Auto":"Manual",YELLOW);
						  TEXT(245,130,(CONVERT) ? "Yes":"No",WHITE);
						  inp_b();
						  switch(PRES){
								case ESC:
									setold(&old);
									   return 0;
								case TAB:
								case ENTER:
									   change(&ptrField,16);
									   break;
								case SPC:
									   CONVERT=!CONVERT;
									   COLBK(BLACK);
									   BAR(240,127,310,142);
									   TEXT(245,130,(CONVERT) ? "Yes":"No",WHITE);
									   break;
								};
						  break;

				    case 4:
						  TEXT(245,130,(CONVERT) ? "Yes":"No",YELLOW);
						  PX1=inp_long(245,150,6,PX1);
						  change(&ptrField,16);
						  break;

				    case 5:
						  PY1=inp_long(245,170,6,PY1);
						  change(&ptrField,16);
						  break;

				    case 6:
						  PX2=inp_long(245,190,6,PX2);
						  change(&ptrField,16);
						  break;

				    case 7:
						  PY2=inp_long(245,210,6,PY2);
						  change(&ptrField,16);
						  break;

				    case 8:
						  XMIN=inp_long(245,230,6,XMIN);
						  change(&ptrField,16);
						  break;

				    case 9:
						  YMIN=inp_long(245,250,6,YMIN);
						  change(&ptrField,16);
						  break;

				    case 10:
						  XMAX=inp_long(245,270,6,XMAX);
						  change(&ptrField,16);
						  break;

				    case 11:
						  YMAX=inp_long(245,290,6,YMAX);
						  change(&ptrField,16);
						  break;

				    case 12:
						  XW1=inp_long(245,310,6,XW1);
						  change(&ptrField,16);
						  break;

				    case 13:
						  YW1=inp_long(245,330,6,YW1);
						  change(&ptrField,16);
						  break;

				    case 14:
						  XW2=inp_long(245,350,6,XW2);
						  change(&ptrField,16);
						  break;

				    case 15:
						  YW2=inp_long(245,370,6,YW2);
						  change(&ptrField,16);
						  break;

				    case 16:
						  BUT(120,395,"Accept",LIGHTBLUE);
						  inp_b();
						  switch(PRES){
								case ESC:
									setold(&old);
									   return 0;
								case TAB:
									   change(&ptrField,16);
									   break;
								case ENTER:
									   return 1;
								};
						  break;

				    case OK:
						  BUT(120,395,"Accept",BLACK);
						  BUT(195,395,"Default",LIGHTBLUE);
						  inp_b();
						  switch(PRES){
								case ESC:
									setold(&old);
									   return 0;
								case TAB:
									   change(&ptrField,16);
									   break;
								case ENTER:
									   setold(&old);
									   break;
								};
						  break;

				    case CANCEL:
						  BUT(195,395,"Default",BLACK);
						  BUT(270,395,"Cancel",LIGHTBLUE);
						  inp_b();
						  switch(PRES){
								case ESC:
								case ENTER:
									setold(&old);
									   return 0;
								case TAB:
									   change(&ptrField,16);
									   break;
								};
						  break;
						  };
				    if(PRES==ESC){
						setold(&old);
						  return 0;
						  };
				    goto swset;
			 }

	   case ASK:{
			 wind(100,100,380,180,"File has been changed. Save ?");
			 BUT(130,140,"Yes",LIGHTBLUE);
			 BUT(210,140,"No",BLACK);
			 BUT(290,140,"Cancel",BLACK);

			 swa:
			 switch(ptrField){
				    case 1:
						  BUT(290,140,"Cancel",BLACK);
						  BUT(130,140,"Yes",LIGHTBLUE);
						  inp_b();
						  switch(PRES){
								case ESC:
									   return 0;
								case TAB:
									   change(&ptrField,1);
									   break;
								case ENTER:
									   return 1;
								};
                                break;

				    case OK:
						  BUT(130,140,"Yes",BLACK);
						  BUT(210,140,"No",LIGHTBLUE);
						  inp_b();
						  switch(PRES){
								case ESC:
									   return 0;
								case TAB:
                                                change(&ptrField,1);
									   break;
								case ENTER:
									   return 2;
								};
						  break;

                        case CANCEL:
						  BUT(210,140,"No",BLACK);
						  BUT(290,140,"Cancel",LIGHTBLUE);
                                inp_b();
                                switch(PRES){
								case ESC:
								case ENTER:
									   return 0;
								case TAB:
									   change(&ptrField,1);
									   break;
								};
						  break;
						  };
				    goto swa;
				    }

	   case MOVE:{
			 long DXOLD;
			 long DYOLD;
			 long ORY2;
			 long ORX2;
			 char wb[20];

			 DXOLD=DX;
			 DYOLD=DY;
			 wind(100,100,275,235,"Move origin...");
			 TEXT(110,140," X          mm",WHITE);
			 TEXT(110,160," Y          mm",WHITE);
			 COLBK(BLACK);
			 BAR(140,137,198,152);
			 sprintf(wb,"%ld",ORX+DX/40);
			 TEXT(143,140,wb,YELLOW);
			 BAR(140,157,198,172);
			 sprintf(wb,"%ld",ORY+DY/40);
			 TEXT(143,160,wb,YELLOW);
			 BUT(120,190,"Ok",BLACK);
			 BUT(190,190,"Cancel",BLACK);
			 sw:
			 switch(ptrField){
				    case 1:
						  BUT(190,190,"Cancel",BLACK);
						  ORX2=inp_long(140,140,5,ORX+DX/40);
						  DX=40*(ORX2-ORX);
						  change(&ptrField,2);
						  break;

				    case 2:
						  ORY2=inp_long(140,160,5,ORY+DY/40);
						  DY=40*(ORY2-ORY);
						  change(&ptrField,2);
						  break;

				    case OK:
						  BUT(120,190,"Ok",LIGHTBLUE);
						  inp_b();
						  if(PRES==TAB) change(&ptrField,2);
						  if(PRES==ENTER){
								return 0;
								};
						  break;

				    case CANCEL:
						  BUT(120,190,"Ok",BLACK);
						  BUT(190,190,"Cancel",LIGHTBLUE);
						  inp_b();
						  if(PRES==ENTER){
								DY=DYOLD;
								DX=DXOLD;
								return 0;
								};
						  if(PRES==TAB) change(&ptrField,2);
						  break;
				    };
				    if(PRES==ESC){
						  DY=DYOLD;
						  DX=DXOLD;
						  return 0;
						  };
				    goto sw;
				    }

			case PENSS:{
				long ovold;
				char ign;
				char selpen=0;
				int i;
				char wb[256];
				wind(150,100,400,430,"Pens definition...");
				TEXT(160,140,"Pen          Used    VS   FS",WHITE);
				TEXT(160,150,"-----------------------------",WHITE);
				for(i=0;i<8;i++){
					sprintf(wb,"%d             %s    %2d  %3d",
						i,
						(PENS[i].use) ? "Yes":"No ",
						PENS[i].VS_,
						PENS[i].FS_
						);
					TEXT(160,170+i*18,wb,WHITE);
					TEXT(190,170+i*18,CLR[PENS[i].col],PENS[i].col);
					};
				TEXT(160,315,"-----------------------------",WHITE);
				TEXT(170,330,"Ignore 'SP..;'",WHITE);
				TEXT(170,350,"      OverCut          steps",WHITE);
				TEXT(170,370,"Optimize PU/PD         steps",WHITE);
				RECT(157,165,390,182,RED);

				COLBK(BLACK);
				BAR(290,326,350,342);
				BAR(290,345,350,362);
				BAR(290,365,350,382);
				TEXT(295,330,(IGNORESP) ? "Yes":"No",YELLOW);
				sprintf(wb,"%d",OVER);
				TEXT(298,350,wb,YELLOW);
				sprintf(wb,"%ld",THERE);
				TEXT(298,370,wb,YELLOW);

				BUT(200,395,"Ok",BLACK);
				BUT(280,395,"Cancel",BLACK);
				ign=IGNORESP;
				ovold=OVER;
				swps:
				switch(ptrField){
				    case 1: {

						  BUT(280,395,"Cancel",BLACK);
						  RECT(157,165+selpen*18,390,182+selpen*18,RED);
						  inp_b();
						  switch(PRES){
							case ARU:
								RECT(157,165+selpen*18,390,182+selpen*18,LIGHTBLUE);
								selpen--;
								if(selpen>8) selpen=7;
								RECT(157,165+selpen*18,390,182+selpen*18,RED);
								break;

							case ARD:
								RECT(157,165+selpen*18,390,182+selpen*18,LIGHTBLUE);
								selpen++;
								if(selpen>7) selpen=0;
								RECT(157,165+selpen*18,390,182+selpen*18,RED);
								break;

							case ESC:
								IGNORESP=ign;
								OVER=ovold;
								return 8;

							case TAB:
								RECT(157,165+selpen*18,390,182+selpen*18,LIGHTBLUE);
								change(&ptrField,4);
								break;

							case ENTER:
								return selpen;
							};
						  break;
						  }

				    case 2:
						RECT(157,165+selpen*18,390,182+selpen*18,LIGHTBLUE);
						TEXT(295,330,(IGNORESP) ? "Yes":"No",WHITE);
						inp_b();
						  switch(PRES){
								case ESC:
									IGNORESP=ign;
									OVER=ovold;
									return 8;
								case TAB:
								case ENTER:
									   change(&ptrField,4);
									   break;
								case SPC:
									   IGNORESP=!IGNORESP;
									   COLBK(BLACK);
									   BAR(290,326,350,342);
									   TEXT(295,330,(IGNORESP) ? "Yes":"No",WHITE);
									   break;
								};
						  break;

				    case 3:
					TEXT(295,330,(IGNORESP) ? "Yes":"No",YELLOW);
					OVER=inp_long(295,350,4,OVER);
					change(&ptrField,4);
					break;

				    case 4:
					THERE=inp_long(295,370,3,THERE);
					change(&ptrField,4);
					break;

				    case OK:
						  BUT(200,395,"Ok",LIGHTBLUE);
						  inp_b();
						  if(PRES==TAB) change(&ptrField,4);
						  if(PRES==ENTER){
								return 9;
								};
						  break;

				    case CANCEL:
						  BUT(200,395,"Ok",BLACK);
						  BUT(280,395,"Cancel",LIGHTBLUE);
						  inp_b();
						  if(PRES==ENTER){
								IGNORESP=ign;
								OVER=ovold;
								return 8;
								};
						  if(PRES==TAB) change(&ptrField,4);
						  break;
				    };
				    if(PRES==ESC){
						IGNORESP=ign;
						OVER=ovold;
						  return 8;
						  };
				    goto swps;
				}
	   };
return 0;
};

void setold(struct OLD *old){  // ------- S E T O L D --------------
char wb[256];
int i;

TYPE=(*old).TYPE;
AUTO=(*old).AUTO;
CONVERT=(*old).CONVERT;
PX1=(*old).PX1;
PY1=(*old).PY1;
PX2=(*old).PX2;
PY2=(*old).PY2;
XMIN=(*old).XMIN;
YMIN=(*old).YMIN;
XMAX=(*old).XMAX;
YMAX=(*old).YMAX;
XW1=(*old).XW1;
YW1=(*old).YW1;
XW2=(*old).XW2;
YW2=(*old).YW2;
CHANGED=0;
COLBK(BLACK);
for(i=0;i<15;i++)
	BAR(240,87+i*20,312,102+i*20);

TEXT(245,90,((*old).TYPE) ? "Cut":"Plot",YELLOW);
TEXT(245,110,((*old).AUTO) ? "Auto":"Manual",YELLOW);
TEXT(245,130,((*old).CONVERT) ? "Yes":"No",YELLOW);

sprintf(wb,"%ld",(*old).PX1);
TEXT(248,150,wb,YELLOW);

sprintf(wb,"%ld",(*old).PY1);
TEXT(248,170,wb,YELLOW);

sprintf(wb,"%ld",(*old).PX2);
TEXT(248,190,wb,YELLOW);

sprintf(wb,"%ld",(*old).PY2);
TEXT(248,210,wb,YELLOW);

sprintf(wb,"%ld",(*old).XMIN);
TEXT(248,230,wb,YELLOW);

sprintf(wb,"%ld",(*old).YMIN);
TEXT(248,250,wb,YELLOW);

sprintf(wb,"%ld",(*old).XMAX);
TEXT(248,270,wb,YELLOW);

sprintf(wb,"%ld",(*old).YMAX);
TEXT(248,290,wb,YELLOW);

sprintf(wb,"%ld",(*old).XW1);
TEXT(248,310,wb,YELLOW);

sprintf(wb,"%ld",(*old).YW1);
TEXT(248,330,wb,YELLOW);

sprintf(wb,"%ld",(*old).XW2);
TEXT(248,350,wb,YELLOW);

sprintf(wb,"%ld",(*old).YW2);
TEXT(248,370,wb,YELLOW);
};


void change(int *ptr,int tot){  //------------ C H A N G E ----------
if(*ptr==tot){
        *ptr=OK;
	   return ;
        };
if(*ptr==OK){
	   *ptr=CANCEL;
	   return ;
	   };
if(*ptr==CANCEL){
	   *ptr=1;
        return ;
	   };
(*ptr)++;
return ;
};

float inp_long(int sx,int sy, int leng, long val){ //---- I N P L O N G ---
char wb[50];
int p;
union KEY k;
COLBK(BLACK);
BAR(sx,sy-3,sx+leng*10+6,sy+12);
sprintf(wb,"%ld_",val);
p=strlen(wb)-1;

wtk:
BAR(sx,sy-3,sx+leng*10+6,sy+12);
TEXT(sx+3,sy,wb,YELLOW);
while(!bioskey(1));
k.in=bioskey(0);
switch(k.ch[0]){
	   case BKSPC:
			 if(!p) break;
			 wb[--p]='_';
			 wb[p+1]='\0';
			 PRES=BKSPC;
			 break;
	   case TAB:
	   case ENTER:
			 wb[p]='\0';
			 BAR(sx,sy-3,sx+leng*10+6,sy+12);
			 TEXT(sx+3,sy,wb,YELLOW);
			 PRES=0;
			 return atof(wb);
	   case ESC:
			 PRES=ESC;
			 return 0;
	   default :
			 PRES=0;
			 if(k.ch[0]){
				    if(isdigit(k.ch[0])){
						  if(p<leng){
								wb[p++]=k.ch[0];
								wb[p]='_';
								wb[p+1]='\0';
								break;
								};
						  break;

				    };

			 if(k.ch[0]=='-'){
				    int i;
				    if(wb[0]=='-'){
						  for(i=0;i<=p;i++) wb[i]=wb[i+1];
						  p--;
						  }
				    else {
						  for(i=p;i>0;i--) wb[i]=wb[i-1];
						  wb[0]='-';
						  wb[++p]='_';
						  wb[p+1]='\0';
						  };
				    };
			 };

	   };
goto wtk;
};


char *inp_str(int sx,int sy, int leng, char *val){ //---- I N P S T R  ---
static char wb[50];
int p;
union KEY k;
COLBK(BLACK);
BAR(sx,sy-3,sx+leng*8,sy+12);
sprintf(wb,"%s_",val);
p=strlen(wb)-1;

wtk:
BAR(sx,sy-3,sx+leng*8,sy+12);
TEXT(sx+3,sy,wb,YELLOW);
while(!bioskey(1));
k.in=bioskey(0);
switch(k.ch[0]){
        case BKSPC:
			 if(!p) break;
                wb[--p]='_';
			 wb[p+1]='\0';
                PRES=BKSPC;
                break;
	   case TAB:
        case ENTER:
			 wb[p]='\0';
                BAR(sx,sy-3,sx+leng*8,sy+12);
			 TEXT(sx+3,sy,wb,YELLOW);
			 PRES=0;
                return wb;
	   case ESC:
                PRES=ESC;
                return NULL;
	   default :
			 PRES=0;
			 if(k.ch[0]){
                        if(isprint(k.ch[0])){
                                if(p<leng){
								wb[p++]=k.ch[0];
                                        wb[p]='_';
								wb[p+1]='\0';
                                        break;
                                        };
						  break;
                        };

                };

	   };
goto wtk;
};

void inp_b(void){// ------- I N P _ B -----------------------------------
union KEY k;
while(bioskey(1)) bioskey(0);

ww:
while(!bioskey(1));
k.in=bioskey(0);
if(k.ch[0]){
        switch(k.ch[0]){
                case TAB:
			 case ENTER:
			 case BKSPC:
			 case ESC:
			 case SPC:
				    PRES=k.ch[0];
				    return ;
		  };

	   };
if(!k.ch[0]){
	switch(k.ch[1]){
		case ARR:
		case ARL:
		case ARU:
		case ARD:
			PRES=k.ch[1];
			return ;
		};
	};

goto ww;
};


void LINE(long x1, long y1, long x2, long y2, int color){
	   setcolor(color);
	   line( INT((           PX1+(x1-XMIN)*SCX  +DX)*VID+5),
		    INT((474-VID*(  PY1+(y1-YMIN)*SCY  +DY))*KEGA),
		    INT((           PX2+(x2-XMAX)*SCX  +DX)*VID+5),
		    INT((474-VID*(  PY2+(y2-YMAX)*SCY  +DY))*KEGA)
		    );
	   setcolor(BLACK);
	   };

void BAR(int x1, int y1, int x2, int y2){
	   bar(x1,y1*KEGA,x2,y2*KEGA);
	   };

void RECT(int x1, int y1, int x2, int y2, int color){
	   setcolor(color);
	   rectangle(x1,y1*KEGA,x2,y2*KEGA);
	   setcolor(BLACK);
	   };

void CIRCLE(long xc, long yc, float rad, int color){
	   setcolor(color);
	   circle( INT((xc*SCX+DX)*VID+5),
			 INT((474-VID*(yc*SCY+DY))*KEGA),
			 INT(rad*VID*SCX)
			 );
	   setcolor(BLACK);
	   };

void TEXT(int x, int y, const char *text, int color){
	   setcolor(color);
	   outtextxy(x,y*KEGA,text);
	   setcolor(BLACK);
	   };

void COLBK(int color){
	   setfillstyle(SOLID_FILL,color);
	   };

void SET(long x, long y){
	   X=x;
	   Y=y;
	   };

void BUT(int x, int y, char *txt, int col){
	   COLBK(DARKGRAY);
	   BAR(x+3,y+3,x+63,y+25);
	   COLBK(LIGHTGRAY);
	   BAR(x,y,x+60,y+22);
	   RECT(x+2,y+2,x+58,y+21,BLACK);
	   TEXT((60-strlen(txt)*8)/2.0+1+x,y+8,txt,WHITE);
	   TEXT((60-strlen(txt)*8)/2.0+x,y+7,txt,col);
	   };

void ARRC(long xc, long yc, float angle, int color){
	   double start;
	   int a=0;
	   double modul;
	   long x,y;
	   modul= ((xc-(double long)X)
			*(xc-(double long)X)
			+(yc-(double long)Y)
			*(yc-(double long)Y));
	   modul=sqrtl(modul);
	   if(angle<0) ARC_ANGL=-abs(ARC_ANGL);
	   else ARC_ANGL=abs(ARC_ANGL);
	   start=atan2(Y-yc,X-xc);
	   do {
			 a+=ARC_ANGL;
			 x=xc+modul*cos(a*pi/180.0+start);
			 y=yc+modul*sin(a*pi/180.0+start);
			 if(PEN)
				    LINE(X,Y,x,y,color);
			 SET(x,y);
			 } while (abs(a)<abs(floor(angle)));
	   };





char ask(void){
	   return 1;
	   };

long max_(long x1, long x2){
	   if(x1>x2) return x1;
	   return x2;
	   };

long min_(long x1, long x2){
	   if(x1>x2) return x2;
	   return x1;
	   };

void save(void){//--------------------------- S A V E -----------------------
void plot(FILE *);
void cut(FILE *, FILE *);
char buf[128];
char buf2[128];
char drive[2];
char dir[120];
char name[12];
char ext[5];
FILE *out;
struct ffblk data[1];

char *exts[]={".bak",".plt",".cut"};

if(findfirst(path,data,0)==0){
	   fnsplit(path,drive,dir,name,ext);
	   fnmerge(buf,drive,dir,name,exts[0]);
	   if(findfirst(buf,data,0)==0){
			 sprintf(buf2,"del %s",buf);
			 if(system(buf2)==-1){
				    perror("system");
				    exit(0);
				    };
			 };
	   rename(path,buf);
	   };
out=fopen(path,"w");
rewind(in_plt);
ARC_ANGL=1;
fprintf(out,"%c.Y",27);
fprintf(out,"%c.@;3:",27);
fprintf(out,"%c.I50;;17:",27);
fprintf(out,"%c.N;19:\n",27);

if(CHANGED==1)
	   cut(in_plt,out);
else while(getstr(in_plt)!=EOF)
		plot(out);

fclose(out);
};

void plot(FILE *out){ //------------------- P L O T -------------------------
char chkPU(void);
long x,y;
progr(0,125,140,ftell(in_plt),INFSZ);
switch(cmd){
	   case AA :{
			 long xc,yc;
			 float angle;
			 double start;
			 int a=0;
			 double modul;
			 xc=atol(parm[0]);
			 yc=atol(parm[1]);
			 angle=atof(parm[2]);
			 if(n_parm>2) ARC_ANGL=atoi(parm[3]);
			 if(CONVERT){
				modul=((xc-(double long)X)
					*(xc-(double long)X)
					+(yc-(double long)Y)
					*(yc-(double long)Y));
				modul=sqrtl(modul);

				if(angle<0) ARC_ANGL=-abs(ARC_ANGL);
				else ARC_ANGL=abs(ARC_ANGL);

				start=atan2(Y-yc,X-xc);
				do {
					a+=ARC_ANGL;
					x=xc+modul*cos(a*pi/180.0+start);
					y=yc+modul*sin(a*pi/180.0+start);
					fprintf(out,"PA%ld,%ld;",x+DX,y+DY);
					SET(x,y);
					} while (abs(a)<abs(floor(angle)));
				break;
				};
			 fprintf(out,"AA%ld,%ld,%.0f",xc+DX,yc+DY,angle);
			 if(n_parm>3){
				ARC_ANGL=atoi(parm[3]);
				fprintf(out,",%d",ARC_ANGL);
				};
			 fprintf(out,";");
			 break;
			 }


	   case AR :{
			 long xc,yc;
			 long p1,p2;
			 float angle;
			 double start;
			 int a=0;
			 double modul;
			 p1=atol(parm[0]);
			 p2=atol(parm[1]);
			 xc=X+p1;
			 yc=Y+p2;
			 angle=atof(parm[2]);
			 if(n_parm>2) ARC_ANGL=atoi(parm[3]);
			 if(CONVERT){
				modul=(p1*p1+p2*p2);
				modul=sqrtl(modul);

				if(angle<0) ARC_ANGL=-abs(ARC_ANGL);
				else ARC_ANGL=abs(ARC_ANGL);

				start=atan2(Y-yc,X-xc);
				do {
					a+=ARC_ANGL;
					x=xc+modul*cos(a*pi/180.0+start);
					y=yc+modul*sin(a*pi/180.0+start);
					fprintf(out,"PA%ld,%ld;",x+DX,y+DY);
					SET(x,y);
					} while (abs(a)<abs(floor(angle)));
				break;
				};
			 fprintf(out,"AR%ld,%ld,%.0f",p1,p2,angle);
			 if(n_parm>3){
				ARC_ANGL=atoi(parm[3]);
				fprintf(out,",%d",ARC_ANGL);
				};
			 fprintf(out,";");
			 break;
			 }

	   case PA :{
			 int i;
			 fprintf(out,"PA");
			 for(i=0;i<n_parm; ){
				    if(i) fprintf(out,",");
				    x=atol(parm[i++]);
				    y=atol(parm[i++]);
				    fprintf(out,"%ld,%ld",x+DX,y+DY);
				    };
			 SET(x,y);
			 fprintf(out,";");
			 break;
			 }


	   case PR :{
			 int i;
			 fprintf(out,"PR");
			 for(i=0;i<n_parm; ){
				    if(i) fprintf(out,",");
				    x=atol(parm[i++]);
				    y=atol(parm[i++]);
				    fprintf(out,"%ld,%ld",x,y);
				    };
			 SET(X+x,Y+y);
			 fprintf(out,";");
			 break;
			 }



	   case PD :{
			 int i;
			 fprintf(out,"PD");
			 for(i=0;i<n_parm; ){
				    if(i) fprintf(out,",");
				    x=atol(parm[i++]);
				    y=atol(parm[i++]);
				    fprintf(out,"%ld,%ld",x+DX,y+DY);
				    };
			 fprintf(out,";");
			 break;
			 }

	   case PU :{
			 int i;
			 if(chkPU()) break;
			 fprintf(out,"PU");
			 for(i=0;i<n_parm; ){
				    if(i) fprintf(out,",");
				    x=atol(parm[i++]);
				    y=atol(parm[i++]);
				    fprintf(out,"%ld,%ld",x+DX,y+DY);
				    };
			 fprintf(out,";");
			 break;
			 }


	   case SP :{
			 if(!IGNORESP){
				int p;
				p=atoi(parm[0]);
				fprintf(out,"SP%d;\n",p);
				fprintf(out,"VS%d;\n",PENS[p].VS_);
				if(TYPE)
					fprintf(out,"FS%d;\n",PENS[p].FS_);
				};
			 break;
			 }

	   case SC :{
			if(AUTO)
			fprintf(out,"SC%ld,%ld,%ld,%ld;",
					XMIN,
					XMAX,
					YMIN,
					YMAX
					);
			 break;
			 }

	   case IP :{
		if(AUTO)
			fprintf(out,"IP%ld,%ld,%ld,%ld;",
			 PX1,
			 PY1,
			 PX2,
			 PY2
			 );
			 break;
			 }

	   case IW :{
		if(AUTO)
			fprintf(out,"IW%ld,%ld,%ld,%ld;",
			 XW1,
			 YW1,
			 XW2,
			 YW2
			 );
			 break;
			 }

	   default:
			 fprintf(out,"%s",buffer);
			 break;
	   };
};

void cut(FILE *in,FILE *out){//--------------- C U T -------------------
void plot(FILE *);
enum st { MOVE=0, CUT, PUT, RISE } STATE;

long x1,y1,x2,y2;
long ddx,ddy;
double run=0,nrun,obert;

rewind(in);
progr(0,125,140,ftell(in),INFSZ);
X=0;
Y=0;
STATE=MOVE;

while( getstr(in)!=EOF ){

switch(STATE){
	case MOVE:
		switch(cmd){
			case PU:
				break;
			case PD:
				STATE=PUT;
				PEN=1;
				fprintf(out,"PD;");
				break;
			case PA:
				x1=atol(parm[0]);
				y1=atol(parm[1]);
				x2=x1+OVER/2.0*cos(run);
				y2=y1+OVER/2.0*sin(run);
				fprintf(out,"PA%ld,%ld;",x2+DX,y2+DY);
				SET(x1,y1);
				break;
			default:
				plot(out);
				break;
			};
		break;

	case CUT:
		switch(cmd){
			case PU:
				STATE=RISE;
				PEN=0;
				fprintf(out,"PU;");
				break;
			case PD:
				break;
			case PA:
				x1=atol(parm[0]);
				y1=atol(parm[1]);
				ddx=x1-X;
				ddy=y1-Y;
				nrun=atan2(ddy,ddx);
				obert=nrun-run;
				if(obert<-pi) obert+=2.0*pi;
				if(obert>pi) obert-=2.0*pi;
				if(abs(obert)>1.0/180.0*pi)
					fprintf(out,"AA%ld,%ld,%.0f;\n",X+DX,Y+DY,180*obert/pi);

				run=nrun;
				x2=x1+OVER*cos(run);
				y2=y1+OVER*sin(run);
				fprintf(out,"PA%ld,%ld;",x2+DX,y2+DY);
				SET(x1,y1);
				break;

			default:
				plot(out);
				break;
			};
		break;

	case PUT:
		switch(cmd){
			case PU:
				STATE=RISE;
				PEN=0;
				break;
			case PD:
				break;
			case PA:
				STATE=CUT;
				x1=atol(parm[0]);
				y1=atol(parm[1]);
				ddx=x1-X;
				ddy=y1-Y;
				nrun=atan2(ddy,ddx);
				obert=nrun-run;
				if(obert<-pi) obert+=2.0*pi;
				if(obert>pi) obert-=2.0*pi;
				if(abs(obert)>1.0/180.0*pi)
					fprintf(out,"AA%ld,%ld,%.0f;\n",X+DX,Y+DY,180*obert/pi);

				run=nrun;
				x2=x1+OVER*cos(run);
				y2=y1+OVER*sin(run);
				fprintf(out,"PA%ld,%ld;",x2+DX,y2+DY);
				SET(x1,y1);
				break;
			default:
				plot(out);
				break;
			};
		break;

	case RISE:
		switch(cmd){
			case PU:
				break;
			case PD:
				STATE=PUT;
				PEN=1;
				fprintf(out,"PD;");
				break;
			case PA:
				STATE=MOVE;
				x1=atol(parm[0]);
				y1=atol(parm[1]);
				x2=x1+OVER/2.0*cos(run);
				y2=y1+OVER/2.0*sin(run);
				fprintf(out,"PA%ld,%ld;",x2+DX,y2+DY);
				SET(x1,y1);
				break;
			default:
				plot(out);
				break;
			};
		break;
	};
};


};


void type_str(char *str, char mod){//--------------  T Y P E _ S T R --------------
if(!mod){
	while((*str)!=TERM){
		type_c(*str++);
		X+=S_W*cos(S_A)*40;
		Y+=S_W*sin(S_A)*40;
		};
	};
if(mod){
	while((*str)!=';'){
		type_c(*str++);
		X+=S_W*cos(S_A)*40;
		Y+=S_W*sin(S_A)*40;
		};
	};

};

void type_c(char c){ //-------------- T Y P E _ C -------------------------
char n;
int i;
char pen_;
long X_,Y_;
long x,y;
long x1,y1;
static signed char simb[][64]={ { 2, 15,15, 30,15 }, 		 // SPACE BAR
	{ 7, 1,45, 1,-25, 0,-17, 2,-17, 2,15, 0,15, 0,17},      // !
	{ 4, 6,48, 6,-37, 14,-48, 14,-37                },      // "
	{ 8, 3,15, 10,-45, 17,-45, 10,-15, 0,-34, 20,-34,       // #
								20,-26, 0,-26},
	{ 14,0,20,5,-15,15,15,20,20, 20,25, 15,30, 5,30,        // $
	0,35, 0,40, 5,45, 15,45, 20,40, 10,-50, 10,-10  },
	{ 28, 0,38,0,-42,1,44,3,45,6,45,8,44, 9,42, 9,38,
	8,36, 6,35,3,35,1,36,0,38,0,-15,20,-45, 20,-22,
	20,-18, 19,16, 17,15,14,15,12,16, 11,18, 11,22,
	12,24, 14,25, 17,25, 19,24, 20,22               },	// %
	{ 20, 20,24, 19,-20,17,18, 13,15, 7,15, 2,17,0,22,
	0,27, 3,32, 7,35, 10,38, 10,42, 8,45, 3,45,
	1,42, 1,37, 3,32, 7,27, 17,18, 20,15            },	// &
	{ 6, 12,45, 10,-45, 10,47, 12,47, 12,43, 11,40  },	// '
	{ 8, 20,10, 17,-15, 15,22, 14,28, 14,32, 15,38,
	17,45, 20,50							   },	// (
	{ 8, 0,10, 3,-15, 5,22, 6,28, 6,32, 5,38,
	3,45, 0,50							   },	// )
	{ 6, 0,30, 20,-30, 16,-20, 4,-40, 16,-40, 4,-20 },	// *
	{ 4, 10,15, 10,-45, 0,-30, 20,-30               },	// +
	{ 6, 2,15, 0,-15, 0,17, 2,17, 2,13, 1,10        },	// `
	{ 2, 0,30, 20,-30                               },  	// -
	{ 5, 10,15, 10,-17, 12,17, 12,15, 10,15         },  	// .
	{ 2, 0,10, 20,-50                               },	// /
	{ 14, 2,17, 0,-22, 0,38, 2,43, 7,45, 13,45, 18,43,
	20,38, 20,22, 18,18, 13,15, 7,15, 2,17, 18,43 },   	// 0
	{ 4, 8,33, 13,-45, 14,45, 14,15			   },	// 1
	{ 10, 0,40,5,-45,15,45,20,40,20,35, 15,30, 5,25,
	0,20, 0,15, 20,15                               },     // 2

	{ 13, 0,40, 5,-45, 15,45,19,41,19,37,15,33,10,33,
	15,-33, 20,-28, 20,20, 15,15, 5,15, 0,20        },	// 3
	{ 6, 20,23, 0,-23, 0,26, 15,45, 17,45, 17,15    },	// 4

	{ 10, 20,45,0,-45,0,30,5,35,15,35, 20,30, 20,20,
	15,15, 5,15, 0,20						   },	// 5
	{ 12, 20,40,15,-45,5,45,0,40,0,20, 5,15, 15,15,
	20,20, 20,30, 15,35, 5,35, 0,30                 },     // 6
	{ 4, 0,45, 19,-45, 19,42, 6,15                  }, 	// 7
	{ 16, 5,33,2,-35,2,42,5,45,15,45,18,42,18,35,15,33,
	5,33, 0,28, 0,20,5,15,15,15,20,20, 20,28, 15,33 },	// 8
	{ 12, 0,20,5,-15,15,15,20,20,20,40,15,45,5,45,
	0,40,0,30, 5,25, 15,25, 20,30,6,26, 16,26, 17,27,
	18,29,20,31                                     },	// 9
	{ 10, 0,35,2,-35,2,37,0,37,0,35,0,-17,0,-15, 2,15,
	2,17, 0,17                                      },     // :
	{ 11, 0,40,0,-42,2,42,2,40,0,40,2,-15,0,-15, 0,17,
	2,17, 2,13, 1,10                                },	// ;
	{ 3, 20,42, 0,-30, 20,18                        },	// <
	{ 4, 0,35, 20,-35, 0,-25, 20,-25                },     // =
	{ 3, 0,18, 20,-30, 0,42                         },	// >
	{ 12, 0,40, 5,-45, 15,45, 20,40, 20,33, 10,28,
	10,23,9,-17, 11,-17, 11,15, 9,15, 9,17          },	// ?
	{ 22, 20,33,17,-36,10,36,6,33,6,26,10,23,17,23,
	20,26,20,39,19,41,18,44,14,45,7,45,3,44,1,41,
	0,37, 0,22,1,19, 3,16, 6,15, 17,15, 20,17       },	// @
	{ 5, 0,15, 10,-45, 20,15, 3,-25, 17,-25         },	// A
	{ 12, 0,15,0,-45,15,45,20,40,20,35,15,30,0,30,
	15,-30, 20,-25, 20,20, 15,15, 0,15              },	// B
	{ 10, 20,40,15,-45,6,45,2,42,0,35,0,25,2,18,
	6,15,15,15, 20,20                               },	// C
	{ 9, 0,15,14,-15,18,18,20,25,20,35,18,42,14,45,
	0,45, 0,15                                      },	// D
	{ 6, 20,45,0,-45,0,15,20,15,0,-31,16,-31        },	// E
	{ 5, 0,15, 0,-45, 20,45, 0,-31, 15,-31          },	// F
	{ 13, 10,30,20,-30,20,25,18,18,14,15,6,15,2,18,
	0,25,0,35, 2,42, 6,45, 14,45, 19,41             },	// G
	{ 6, 0,15, 0,-45, 0,-31, 20,-31, 20,-45, 20,-15 },	// H
	{ 6, 5,45, 15,-45, 10,-45, 10,-15, 5,-15, 15,-15},	// I
	{ 8,0,25,2,-18,6,15,14,15,18,18,20,25,20,45,15,45},	// J
	{ 7, 0,15,0,-45,0,-31,7,-31,20,45,7,-31,20,-15  },	// K
	{ 3, 0,45, 0,-15, 20,15                         },	// L
	{ 5, 0,15, 0,-45, 10,22, 20,45, 20,15           }, 	// M
	{ 4, 0,15, 0,-45, 20,15, 20,45                  },	// N
	{ 13, 6,15,2,-18,0,25,0,35,2,42,6,45,14,45,
	18,42,20,35, 20,25, 18,18, 14,15, 6,15          },	// O
	{ 7, 0,15,0,-45,15,45,20,40,20,35,15,30,0,30    },   	// P
	{ 15, 6,15,2,-18,0,25,0,35,2,42,6,45,14,45,
	18,42,20,35, 20,25, 18,18, 14,15, 6,15, 10,-25,
	20,-15                                          },	// Q
	{ 9, 0,15,0,-45,15,45,20,40,20,35,15,30,0,30,
	10,-30,20,-15                                   },	// R
	{ 12, 0,20, 5,-15, 15,15, 20,20, 20,25, 15,30,
	5,30,0,35, 0,40, 5,45, 15,45, 20,40             },	// S
	{ 4, 0,45, 20,-45, 10,-45, 10,-15               },	// T
	{ 8, 0,45,0,-25,2,18,6,15,14,15,18,18,20,25,
	20,45 								   },	// U
	{ 3, 0,45, 10,-15, 20,45                        },	// V
	{ 5, 0,45, 3,-15, 10,37, 17,15, 20,45           },	// W
	{ 4, 0,15, 20,-45, 0,-45, 20,-15                },   	// X
	{ 5, 0,45, 10,-28, 20,45, 10,-28, 10,-15        },	// Y
	{ 4, 0,45, 20,-45, 0,15, 20,15                  }, 	// Z
	{ 4, 20,50, 14,-50, 14,10, 20,10                },	// [
	{ 2, 0,50, 20,-10                               },	// \
	{ 4, 0,50, 6,-50, 6,10, 0,10                    },	// ]
	{ 3, 3,43, 9,-49, 15,43                         },	// ^
	{ 2, 0,10, 30,-10                               }, 	// _
	{ 2, 5,50, 13,-43                               },	// `
	{ 14, 0,34,5,-37,13,37,18,34,18,18,20,15,18,-25,
	13,-28, 5,28, 0,25, 0,18, 5,15, 13,15, 18,18    },	// a
	{ 10, 0,34,5,-37,13,37,18,34,18,18,13,15,5,15,
	0,18,0,-45, 0,-15                               },	// b
	{ 8, 18,34,13,-37,5,37,0,34,0,18,5,15,13,15, 18,18},	// c
	{ 10, 18,34,13,-37,5,37,0,34,0,18,5,15,13,15,
	18,18,18,-45, 18,-15                            },	// d
	{ 10, 0,26,18,-26,18,34,13,37,5,37,0,34,0,18,
	5,15,13,15, 18,18                               },	// e
	{ 8, 0,35,16,-35,16,-45,13,-45,10,44,9,42,8,39,8,15},	// f
	{ 13, 18,34,13,-37,5,37,0,34,0,18,5,15,13,15, 18,18,
	18,-37, 18,-10, 13,7, 5,7, 0,10                 },   // g
	{ 7, 0,45, 0,-15, 0,-34, 5,-37, 13,37, 18,34, 18,15},	// h
	{ 7, 8,45,8,-42,3,-36,11,-36,11,15,3,-15,16,-15 },	// i
	{ 9, 8,45,8,-43,4,-36,11,-36,11,13,10,10,8, 8,
	6,7,4,7                                         },	// j
	{ 7, 0,45,0,-15,0,-27,4,-27,16,37,4,-27,18,-15  },	// k
	{ 5, 5,45, 12,-45, 12,15, 5,-15, 17,-15         },	// l
	{12, 0,37,0,-15,0,-34,3,-37,7,37,10,34,10,15,
	10,-34,13,-37, 17,37, 20,34, 20,15              },	// m
	{ 7, 0,37, 0,-15, 0,-34, 5,-37, 13,37, 18,34, 18,15},	// n
	{ 9, 5,15,0,-18,0,34,5,37,13,37,18,34,18,18,
	13,15,5,15							   },	// o
	{ 10, 0,34,5,-37,13,37,18,34,18,18,13,15,5,15,
	0,18, 0,-37, 0,-7                               }, 	// p
	{ 10, 18,34,13,-37,5,37,0,34,0,18,5,15,13,15,
	18,18,18,-37, 18,-7 					   },	// q
	{ 6, 0,15, 0,-37, 0,-34, 5,-37, 13,37, 18,34    },	// r
	{ 12, 0,18,5,-15,13,15,18,18,18,23,13,26,5,26,
	0,29,0,34, 5,37, 13,37, 18,34                   },     // s
	{ 9, 0,35,15,-35,5,-45,5,-21,6,18,8,16,10,15,
	15,15,18,17                                     },	// t
	{ 8, 0,37,0,-18,5,15,13,15,18,18,18,-37,18,-18,20,15},	// u
	{ 3, 0,37, 9,-15, 18,37                         },	// v
	{ 5, 0,37, 3,-15, 10,32, 17,15, 20,37           },    	// w
	{ 4, 0,15, 18,-37, 0,-37, 18,-15                },    	// x
	{ 7, 18,37, 9,-10, 7,8, 5,7, 3,7, 0,-37, 10,-15 },   	// y
	{ 4, 0,37, 17,-37, 0,15, 18,15                  },   	// z
	{ 7, 19,50,15,-47,15,34,12,30,15,26,15,13, 19,10},    	// {
	{ 2, 0,15, 0,-50                                },  	// |
	{ 7, 1,50, 5,-47, 5,34, 8,30, 5,26,  5,13,  1,10},    	// }
	{10, 0,43,3,-47,5,48,7,48,8,47,10,45, 12,44,
	14,44 ,16,45, 18,48                             },	// ~
	{ 11,0,37,0,-18,5,15,13,15,18,18,18,-37,18,-18,
	20,15,6,-42, 6,-39, 12,42                       },
	{ 9, 0,37,0,-18,5,15,13,15,18,18,18,-37,18,-18,
	20,15,20,10                                     },
	{ 6, 0,15, 0,-37, 0,-26, 18,-26, 18,-37, 18,-15 },
	{ 12, 0,34,5,-37,13,37,18,34,18,29,13,26,5,26,
	0,23,0,18, 5,15, 13,15, 18,18				   },
	{ 13, 0,37,0,-18,3,15,7,15,10,18,10,-37,10,-18,
	13,15, 17,15, 20,18, 20,-37, 20,-18, 23,15      },
	{ 14, 0,37,0,-18,3,15,7,15,10,18,10,-37,10,-18,
	13,15, 17,15, 20,18, 20,-37, 20,-18, 23,15, 23,10},
	{ 11, 0,34, 5,-37, 13,37, 18,34, 18,29, 13,26,
	18,23,18,18, 13,15, 5,15, 0,18                  },
	{ 17, 10,34,7,-37,3,37,0,34,0,18,3,15,7,15,
	10,18,13,15, 17,15, 20,18, 20,34, 17,37, 13,37,
	10,34,10,-37, 10,-10                            },
	{ 9, 0,37, 0,-15, 10,15, 15,18, 15,25, 10,28,
	0,28,20,-37, 20,-15                             },
	{ 16, 0,15,0,-37,13,37,16,36,17,34,17,31,16,29,
	13,28,0,28, 13,-28, 16,-26, 18,23, 18,20,16,16,13,15,0,15},
	{ 7, 0,37,0,-15,0,-27,4,-27,16,37,4,-27,18,-15  },
	{ 5, 0,15, 3,-15, 10,37, 18,37, 18,15           },
	{ 11, 18,34,13,-37,5,37,0,34,0,18,5,15,13,15,
	18,18,18,42, 13,45, 3,45                        },
	{ 6, 0,15, 20,-37, 0,-37, 20,-15, 10,-15, 10,-37},
	{ 10, 0,34, 5,-37, 13,37, 18,34, 18,18, 13,15,
	5,15,0,18, 5,-26, 18,-26                        },
	{ 9, 0,15,10,-24,18,-24,5,-24,0,27,0,34,5,37,
	18,37,18,15                                     },
	{ 6, 0,37, 0,-27, 5,24, 18,24, 18,-37, 18,-15   },
	{ 5, 0,15, 0,-37, 10,25, 20,37, 20,15           },
	{ 7, 0,37, 0,-15, 13,15, 18,18, 18,25, 13,28, 0,28},
	{ 13, 5,15,0,-18,0,34,5,37,13,37,18,34,18,18,
	13,15,5,15, 13,-37, 5,-43, 5,45, 15,45          },
	{ 13, 0,15, 0,-37, 0,-26, 5,-26, 5,18, 10,15,
	15,15,20,18, 20,34, 15,37, 10,37, 5,34, 5,26    },
	{ 4, 0,45, 0,-15, 20,45, 20,15                  },
	{ 7, 0,45, 0,-15, 20,45, 20,15, 5,-52, 10,-47, 15,52 },
	{ 6, 0,45, 0,-15, 23,15, 23,10, 20,-45, 20,-15       },
	{ 8, 0,45,0,-28,3,25,20,25,20,-45,20,-20,15,15, 0,15 },
	{ 3, 0,15, 0,-45, 20,45                         },
	{ 6, 0,45, 0,-15, 20,15, 20,45, 10,-45, 10,-15  },
	{ 9, 0,45, 0,-15, 20,15, 20,45, 10,-45, 10,-15,
	20,-15, 23,-15, 23,10                           },
	{ 11, 0,23,0,-42,3,45,18,45,20,42,20,23, 17,20,
	3,20, 0,23, 10,-45, 10,-15                      },
	{ 9, 0,45, 0,-15, 12,15, 15,18, 15,30, 12,33,
	0,33,20,-45, 20,-15                            },
	{ 4, 0,15, 0,-45, 20,45, 20,15                 },
	{ 5, 0,15, 5,-15, 12,45, 20,45, 20,15          },
	{ 8, 3,15,10,-45,20,45,20,15,0,-10,0,-15,23,15,23,10 },
	{ 9, 0,15,8,-35,0,-45,10,-32,20,45,12,-35,
	20,-15,10,-15, 10,-45                          },
	{ 12, 0,20,6,-15,14,15,18,18,20,25,20,35,18,42,
	14,45, 6,45, 0,40, 5,-30, 20,-30               },
	{ 9, 20,15,20,-45,5,45,0,40,0,30,5,25,20,25,
	10,-25,0,-15                                   },
	{ 6, 0,45, 0,-28, 3,25, 20,25, 20,-45, 20,-15  },
	{ 7, 0,35, 15,-35, 20,30, 20,20, 15,15, 0,15, 0,45  },
	{ 8, 0,35,15,-35,20,30,20,20,15,15,0,15,0,45, 20,45 },
	{ 13, 0,45,0,-15,0,-30,5,-30,5,42,8,45,17,45,
	20,42 ,20,18, 17,15, 8,15, 5,18, 5,30          },
	{ 8, 0,37,3,-37,3,15,13,15,18,18,18,25,13,28, 3,28  },
	{ 8, 0,45,5,-45,5,15,17,15,20,18,20,30,17,33, 5,33  },
	{ 6, 0,33, 20,-33, 10,-43, 10,-23, 0,-17, 20,-17    },	// +/-
	{ 5, 0,19, 0,-41, 20,41, 20,19, 0,19           },		// SQ.ROOT
	{ 5, 0,30, 10,-15, 20,30, 10,-45, 10,-15       },  	// ARROW DOWN
	{ 5, 0,30, 10,-45, 20,30, 10,-45, 10,-15       },     	// ARROW UP
	{ 5, 0,30, 20,-30, 10,-40, 20,-30, 10,20       },		// ARROW RIGHT
	{ 5, 10,40, 0,-30, 10,20, 0,-30, 20,-30        },     	// ARROW LEFT
	{ 8,  0,30, 5,-30,9,-33,7,-27,11,-27,13,-33,
	15,-30,20,-30                                  },		// -:-
	{ 9, 0,15,0,-45,15,15,15,45,18,-42,22,-42,
	22,35,18,35,18,42                              },    	//
	{ 20, 0,15, 4,-22, 2,26, 2,34, 4,38, 7,41,
	13,41, 16,38, 18,34,
	18,26, 16,22, 13,19, 7,19, 4,22, 0,-45,
	4,-38, 20,-45, 16,-38,
	16,-22, 20,-15                                 },
	{ 1, 177,177                                   } };


if((c<' ')||(c>190)) return ;
n=simb[c-' '][0];
X_=0;
Y_=0;
pen_=0;
for(i=1;i<=2*n;i+=2){
	x1=(simb[c-' '][i])*S_W;
	y1=(simb[c-' '][i+1])*S_H;
	if(y1<0){
		pen_=!pen_;
		y1=-y1;
		};
	x=x1*cos(S_A)-y1*sin(S_A);
	y=y1*cos(S_A)+x1*sin(S_A);
	if(pen_){
		LINE(X+X_,Y+Y_,X+x,Y+y,COL);
		X_=x;
		Y_=y;
		}
	 else {
		X_=x;
		Y_=y;
		};
	};
};

int INT(long lng){
int i;
i=(int)(lng&(long)0x00007FFF);
if(lng>=0) return i;
return -i;
};

char chkPU(void){
long nx,ny;
double mod;
int n_old;
n_old=n_parm;
getstr(in_plt);
if(cmd!=PA){
	ungetstr();
	n_parm=n_old;
	return 0;
	};
nx=atol(parm[0]);
ny=atol(parm[1]);
getstr(in_plt);
if(cmd!=PD){
	ungetstr();
	ungetstr();
	n_parm=n_old;
	return 0;
	};

mod=((nx-(double long)X)
	*(nx-(double long)X)
	+(ny-(double long)Y)
	*(ny-(double long)Y));
mod=sqrtl(mod);
if(mod<(THERE/1.0)){
	ungetstr();
	ungetstr();
	return 1;
     };
ungetstr();
ungetstr();
n_parm=n_old;
return 0;
};

void ungetstr(void){
DBL++;
};

void unget_(char c){
if(DBL==0){
	ungetc(c,in_plt);
	return ;
	};
ungs=1;
ungc=c;
return ;
};

int fget_(FILE *fstr){
static int pos=0;
int ic;
if(ungs){
	ungs=0;
	return ungc;
	};
ee:
if(DBL==0) return fgetc(fstr);
ic=UNGETB[DBL][pos++];
if(ic==0){
	DBL--;
	pos=0;
	goto ee;
	};
return ic;
};

void error(void){
wind(100,190,400,303,"Error ...");
COLBK(BLACK);
BAR(110,220,390,260);
TEXT(120,230,"Too long line !",LIGHTRED);
TEXT(120,240,"File may be not valid...",LIGHTRED);
BUT(220,270,"Exit",LIGHTBLUE);
inp_b();
closegraph();
initscr(0);
fclose(in_plt);
sprintf(buffer,"del cad.$$$");
system(buffer);
exit(0);

};



