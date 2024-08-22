/*******************************************************
 * @project:   Simula                                  *
 * @author:    classzheng: github.com                  *
 * @brief:     A Scp079 simulate                       *
 * @date:      2024/7/23                               *
 * @basemodel: Scp-079 OldAI                           *
 * @releaseud: MIT License Y                         *
 *******************************************************/
#if !defined(__SIMULA__)                                    //
#define __SIMULA__  \
((const char*)"www.github.com/classzheng/simula")

#define IncludeHeaders() : //////////////////////////////
#include <Iostream.H>                                  //
#include <Graphics.H>                                  //
#include <Conio.H>                                     //
#include <Dos.H>                                       //
#include <Alloc.H>                                     //
#include <Limits.H>                                    //
#include <Errno.H>                                     //
#include <Ctype.H>                                     //
#include <Stdio.H>                                     //
#include <Stdlib.H>                                    //
#include <String.H>                                    //
#include <Stdarg.H>                                    //
enum {EMT_HAPPY, EMT_ANGRY, EMT_SAD, EMT_SCARED, EMT_SUM=4};
typedef struct worddig {
	float emoti[EMT_SUM];
	char * word;
	unsigned char usedc;
	worddig() {
		// ...Nothing happend
	}
	worddig(char* wrd) {
		word=new char[16],strcpy(word,wrd);
		memset(emoti,0,sizeof(emoti));
		// Data Initializes
	}
} worddig;

worddig *wordtab;
char*symbol(char* word);

void main (int argc, char*argv[], char*env[]) {
// Usage 'Simula [source] [dump]'
	if(argc<3)       perror("Enough Argument!\n  "),        exit(errno);
	FILE *testdt=fopen(argv[1],"r"),
			 *dump=fopen(argv[2],"w");
	short wordsum=-1,idx=-1,ask=-1,emt,etv,wsm,seekv,serc=0;
	char *stmp=new char[24],*sentc=new char[256],*wrdtmp=new char[16];
	if(NULL==testdt) perror("Missing test data file!\n  "), exit(errno);
	if(NULL==testdt)   perror("Missing testdtionary file!\n  "),exit(errno);

	fscanf(testdt,"[:%d,%d",&wordsum,&ask);
	wordtab=new worddig[wordsum];
	for(idx=0; idx<wordsum; idx++) {
		fscanf(testdt,"%s",stmp);
		wordtab[idx]=worddig(stmp);
		strcpy(stmp,"");
	}
	clrscr();
	puts("[ Simula>Simlab] Now you can reasoning this HM~");
	do {
		printf("Wordsum: ");
		scanf("%d",&wsm);
		printf("EmotionC: ");
		scanf("%d",&emt);
		printf("Sentence: ");
		while(wsm--) {
			scanf("%s",wrdtmp);
			strcpy(wrdtmp,symbol(wrdtmp));
			for(idx=0; idx<wordsum; idx++) {
				if(!strcmp(wordtab[idx].word,wrdtmp)) {
					wordtab[idx].emoti[abs(emt)] = (wordtab[idx].emoti[abs(emt)]+(emt<0?-1.0:1.0))/2;
					wordtab[idx].usedc=1;
					serc++;
					break ;
				}
			}
			seekv+=strlen(wrdtmp);
		}
		printf("-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-\n","");
	} while(--ask);
	for(idx=0; idx<wordsum; idx++) {
		if(wordtab[idx].usedc)
			fprintf(dump,"[%-10s] EMT: %.1f, %.1f, %.1f, %.1f\n",wordtab[idx].word,wordtab[idx].emoti[0],wordtab[idx].emoti[1],wordtab[idx].emoti[2],wordtab[idx].emoti[3]);
	}

	clog << "Idea dumped. " << serc << " success." << "\r\n";

	fclose(dump),fclose(testdt);
	delete stmp;
	delete wordtab;
	delete sentc;

	return ;
}
char* symbol(char* word) {
	char* newwrd=new char[16];
	for(char i=0,j=0; i<strlen(word); i++)
		if(isalpha(word[i])) newwrd[j]=word[i],j++;
	return newwrd;
}
#endif
