#include "c:\borlandc\PROJECTS\CAD\CAD.h"
int getstr(FILE *fp){//---------------- G E T S T R ------------------------
char islegal(int );

int c,i;
char k;
if(fp==NULL) perror("File handler loosed ");
killESC:
i=0;
buffer[0]=0;
while( islegal(c=fget_(fp)) ){
	if((i<3)&&(isspace(c))) continue;
	buffer[i++]=c;
	if(i>100) error();
	if(c==27){
		while((c=fget_(fp))!=':');
		i=0;
		buffer[0]=0;
		continue;
		};

	if(i==2) if(strncmp(buffer,"LB",2)==0){
			while( ((c=fget_(fp))!=TERM)&&(c!=EOF) ){
				buffer[i++]=c;
				if(i>100) error();
				};
			cmd=LB;
			buffer[i++]=TERM;
			buffer[i]=0;
			goto exi_;
			};
	if(i==2) if(strncmp(buffer,"SM",2)==0){
			while( ((c=fget_(fp))!=';')&&(c!=EOF) ){
				buffer[i++]=c;
				if(i>100) error();
				};
			cmd=SM;
			buffer[i++]=';';
			buffer[i]=0;
			goto exi_;
			};
	};
if( (c==EOF)&&(i<2) ){
	return EOF;
	};

if(i>1){
	buffer[i++]=';';
	buffer[i]='\0';
	};

while( !isalnum(c) && (c!=27) && (c!=EOF) ) c=fget_(fp);
unget_(c);

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
if(!DBL){
	strcpy(UNGETB[3],UNGETB[2]);
	strcpy(UNGETB[2],UNGETB[1]);
	strcpy(UNGETB[1],buffer);
	};
return 1;
};

char islegal(int ci){
if(ci==';') return 0;
if(ci=='\n') return 0;
if(ci==EOF) return 0;
return 1;
};
