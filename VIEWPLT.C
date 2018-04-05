#include "c:\borlandc\projects\cad\viewplt.h"

void main(int argc, char *argv[]){  //------------------ M A I N -----------
void analise(FILE *);
void view(FILE *);

int i;
FILE *plt;

printf("PLT Viewer   (C) 1995  ESCO ltd.                        v2.75 Betta\n\n");
delay(500);

switch (argc) {
	case 2:
		plt=fopen(argv[1],"r");
		if(plt==NULL){
			printf("   Sorry, can`t open %s ...\n");
			return ;
			};
		break;

	default:
		printf("Usage :\n");
		printf("viewplt[.exe] filename.ext \n");
		return ;
	};

if(!initscr(1)){
	printf("   Sorry, but needed EGA graphics mode not available ...\n");
	return ;
	};
{
struct ffblk ff[1];
findfirst(argv[1],ff,0);
INFSZ=ff[0].ff_fsize;
}

rewind(plt);

MAXX=MAXY=0;
MINX=MINY=32767;
ARC_ANGL=1;
for(i=0;i<8;i++)
	   PENS[i].col=i;

analise(plt);
DX=-MINX;
DY=-MINY;
SCX=640.0/(MAXX-MINX+100)/VID;
SCY=480.0/KEGA/(MAXY-MINY+100)/VID;
if(SCX>SCY) SCX=SCY;
else SCY=SCX;

rewind(plt);
view(plt);

while(!bioskey(1));
bioskey(0);
initscr(0);
fclose(plt);
return ;

};



void analise(FILE *plt){//--------------- A N A L I S E ---------------------
void check(long, long);
long x,y;
int i;

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
			modul=((xc-(double long)X)*(xc-(double long)X)+(yc-(double long)Y)*(yc-(double long)Y));
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
			break;
			}

		case PA :{
			for(i=0;i<n_parm; ){
				x=atol(parm[i++]);
				y=atol(parm[i++]);
				if(PEN) check(x,y);
				SET(x,y);
				};
			break;
			}

		case PR :{
			for(i=0;i<n_parm; ){
				x=X+atol(parm[i++]);
				y=Y+atol(parm[i++]);
				if(PEN) check(x,y);
				SET(x,y);
				};
			break;
			}

		case PD :{
			PEN=1;
			check(X,Y);
			for(i=0;i<n_parm; ){
				x=atol(parm[i++]);
				y=atol(parm[i++]);
				if(PEN) check(x,y);
				SET(x,y);
				};
			break;
			}

		case PU :{
			PEN=0;
			for(i=0;i<n_parm; ){
				x=atol(parm[i++]);
				y=atol(parm[i++]);
				SET(x,y);
				};
			break;
			}

		default:
			break;
		};
	if(bioskey(1)){
		union KEY k;
		k.in=bioskey(0);
		if(k.ch[0]==27){
			fclose(plt);
			initscr(0);
			exit(0);
			};
		};

	progr(0,125,140,ftell(plt),INFSZ);
	};
};

void check(long x, long y){ //------------------ C H E C K -----------------
long min_(long,long);
long max_(long,long);

MAXX=max_(MAXX,x);
MAXY=max_(MAXY,y);
MINX=min_(MINX,x);
MINY=min_(MINY,y);
};

long max_(long x1, long x2){
	   if(x1>x2) return x1;
	   return x2;
	   };

long min_(long x1, long x2){
	   if(x1>x2) return x2;
	   return x1;
	   };

int getstr(FILE *fp){//---------------- G E T S T R ------------------------
char islegal(int );

int c,i;
char k;
if(fp==NULL) perror("File handler loosed ");
killESC:
i=0;
while( islegal(c=fgetc(fp)) ){
	buffer[i++]=c;
	if(c==27){
		while((c=fgetc(fp))!=':');
		i=0;
		continue;
		};

	if(i==2) if(strncmp(buffer,"LB",2)==0){
			while( ((c=fgetc(fp))!=TERM)&&(c!=EOF) ) buffer[i++]=c;
			cmd=LB;
			buffer[i++]=TERM;
			buffer[i]=0;
			goto exi_;
			};
	if(i==2) if(strncmp(buffer,"SM",2)==0){
			while( ((c=fgetc(fp))!=';')&&(c!=EOF) ) buffer[i++]=c;
			cmd=SM;
			buffer[i++]=';';
			buffer[i]=0;
			goto exi_;
			};
	};
if( (c==EOF)&&(i<2) ){
	return EOF;
	};

while( !islegal(c=fgetc(fp))&&(c!=EOF) );
ungetc(c,fp);

buffer[i++]=';';
buffer[i]='\0';

buffer[0]=toupper(buffer[0]);
buffer[1]=toupper(buffer[1]);

cmd=find(buffer);
k=0;
i=2;
n_parm=0;
while(buffer[i]){
	   while((buffer[i]!=',')&&(buffer[i]!=' ')){
			 if(buffer[i]==';'){
				    parm[n_parm][k]='\0';
				    if(i==3) n_parm++;
				    goto exi_;
				    };
			  parm[n_parm][k++]=buffer[i++];
			  };
	   parm[n_parm++][k]='\0';
	   i++;
	   k=0;
	   };
exi_:
return 1;
};

char islegal(int ci){
if(ci==';') return 0;
if(ci=='\n') return 0;
if(ci==EOF) return 0;
return 1;
};






/*
int getstr(FILE *fp){//---------------- G E T S T R ------------------------
char lb(int ,FILE *);
int c,i=0;
char k;
	while( ((c=fgetc(fp))!=';')&&(c!=EOF) ){
		if(isspace(c)) continue;
		if((i==2)&&lb(c,fp)){
			cmd=LB;
			return 1;
			};
		while(c==27){
			while((c=fgetc(fp))!=':');
			c=fgetc(fp);
			};
		while(c==';') c=fgetc(fp);
		buffer[i++]=c;
		};
	if( (c==EOF)&&(!i) ) return EOF;
	buffer[i++]=';';
	buffer[i]='\0';

	while( isspace(c=fgetc(fp)) );
	ungetc(c,fp);
buffer[0]=toupper(buffer[0]);
buffer[1]=toupper(buffer[1]);
cmd=find(buffer);
k=0;
i=2;
n_parm=0;
while(buffer[i]){
	while((buffer[i]!=',')&&(buffer[i]!=' ')){
		if(buffer[i]==';'){
			parm[n_parm][k]='\0';
			if(i==3) n_parm++;
			return 1;
			};
		parm[n_parm][k++]=buffer[i++];
		};
	parm[n_parm++][k]='\0';
	i++;
	k=0;
	};
return 1;
};

char lb(int cc,FILE *fp){
int i=2;
int c;
c=cc;
buffer[0]=toupper(buffer[0]);
buffer[1]=toupper(buffer[1]);
if( (buffer[0]=='L')&&(buffer[1]=='B') ){
	while( (c!=TERM)&&(c!=EOF) ){
		buffer[i++]=c;
		c=fgetc(fp);
		};
	buffer[i]=TERM;
	buffer[i+1]='\0';
	if( ((c=fgetc(fp))!=';')&&(c!='\n') ) ungetc(c,fp);
	return 1;
	};
return 0;
};
*/

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
VID=1.0/50.0;
return 1;
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
return ;
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

void LINE(long x1, long y1, long x2, long y2, int color){
	   setcolor(color);
	   line( (x1+DX)*SCX*VID+5,
		    (474-VID*(y1+DY)*SCY)*KEGA,
		    (x2+DX)*SCX*VID+5,
		    (474-VID*(y2+DY)*SCY)*KEGA
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
	   circle( (xc+DX)*SCX*VID+5,
			 (474-VID*(yc+DY)*SCY)*KEGA,
			 rad*VID*SCX
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
	   modul=((xc-(double long)X)*(xc-(double long)X)+(yc-(double long)Y)*(yc-(double long)Y));
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








