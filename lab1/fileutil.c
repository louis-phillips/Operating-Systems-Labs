#include "mysyscall.h"
#include <sys/stat.h>
#include <sys/mman.h>

void util_start(void);

asm (".global util_start\r\n"
     "  .type util_start,@function\r\n"
     ".global main\r\n"
     "  .type main,@function\r\n");

/* Get the argc and argv values in the right registers */
asm ("util_start:\r\n"
     "movl %esp, %eax\r\n"
     "addl $4, %eax\r\n"
     "pushl %eax\r\n"
     "subl $4, %eax\r\n"
     "pushl (%eax)\r\n"
     "  call main\r\n");

int dFlag=0,cFlag=0,hFlag=0,rFlag=0,uFlag=0,stdoutFlag=0,stdinFlag=0;
char ttcarr[20];
char* ttcRet;

int length(char* string);
void stdinFlagSetter(char* string);
void stdoutFlagSetter(char* string);
void letterFlagSetter(char* string);
char* turnToChar(int number);



int main(int argc, char **argv){
  int flagLoop;
  //Set all letter flags
  if(argc>3)
  	for(flagLoop=1;flagLoop<argc-2;flagLoop++)
        	letterFlagSetter(*(argv+flagLoop));
  //Set stdin and stdout flags
  if(argc>2){
  	stdinFlagSetter( *(argv+argc-2));
        stdoutFlagSetter(*(argv+argc-1));
  }
  //Can't have DOS and Unix style newlines
  if(dFlag==1 && uFlag==1){
	char* errMsg = "ERROR: Cannot have DOS Style newlines and Unix Style newlines.\n";
	int resultsOfWrite=-4;//useless arg to sys_write. 	
	sys_write(4,1,errMsg,length(errMsg),resultsOfWrite);
	//printf("\nResults of Write=%d\n",resultsOfWrite);
	dFlag=uFlag=rFlag=cFlag=0;
        hFlag=1;
  }
  //Help flag
  if(hFlag==1){
	char* helpMsg = "Proper use is fileutil [-cdhru] infile|- outfile|-\n-c: Counts the newlines in the file and outputs to stderr.\n-d: Converts the output to use DOS-style newlines.\n-h: Prints a help message.\n-r: Reverses the contents of the file, on a line-by-line basis.\n-u: Converts the output to use Unix-style newlines.\n";
        int la;
	sys_write(4,1,helpMsg,length(helpMsg),la);
	dFlag=uFlag=rFlag=cFlag=0;
	int status=0;
  	sys_exit(status);
  }
  
  
//
  //char *name = "abc.txt";
  struct stat stbuf;
  struct stat *pointy=&stbuf;
  short fileSize=0;
//stat(name, &stbuf);
  if(stdinFlag==0){//outFlag==0){
  	statistics(195,*(argv+argc-2), pointy);
  	fileSize = stbuf.st_size;
  	//printf("\nThe size of the file is %d\n",fileSize);
  }
  
  
  int g=20;
  int* f=&g;
//Open File
  if(stdinFlag==0){//outFlag==0){
	g=-50;
	//open file
  	sys_write(5,*(argv+argc-2),0,0,g);//sys_write(5,*(argv+argc-1),0,0,g);
	//if input file doesn't exist
	if(g<0){
	     char* helpMsgOpenF = "Unable to open input file.\n";
             int flying;
	     sys_write(4,1,helpMsgOpenF,length(helpMsgOpenF),flying);
	     int status=1;
  	     sys_exit(status);
	}
	//printf("\nThe g = %d\n",g);
//	printf("\nThe string g =%s\n",g);
}else{
  	g=1;}
  //printf("fd is %d\n",g);
 

//malloc from file
//if stdin != 1
char bufferA[10000];
char* buffer;
/*
int howMuchRed=0;
int* ludo=&howMuchRed;
int flagMakegRed=0;
*/
//ghi
if(stdinFlag==0){
	//buffer = mmap(0, fileSize, PROT_READ, MAP_SHARED, g, 0);
	buffer=&bufferA;
	sys_read(3,g, buffer, 5000)
	 twoArg(6,g);
}else{
	buffer=&bufferA;
	
	/*az=0;
	while(1){
		*(buffer+az) = _getch();
		if ((ch == EOF) || (ch == 0) || (ch == -1) {
			break;}//currChar==EOF || currChar==0 || currChar ==-1
	} */
	//
	//printf("\nHow much red before =%d\n",howMuchRed);
	//copyIntoBuffer(buffer, );  //if(buffer == MAP_FAILED)
	//sys_read(3,0,buffer,9998);
	//printf("\n\n\nHey g might randomly fuck up idk. g=%d\n\n",g);
        sys_read(3,0, buffer,9998);
	//printf("\n\n\nThe first char in the buffer is %c\n\n\n",*(buffer+1));
	//printf("\n\nbuffer  = %s\n\n",buffer);
	/*
	printf("\nHow much red after =%d\n",howMuchRed);
	flagMakegRed=1;
	*/
        //sys_read(3,howMuchRed,buffer,9998);
	//printf("\n\nbuffer second char = %c\n\n",*(buffer+1));
	
	
	
}
  	//print bad map
//Close File
  
  /*char* helpMsgOpenF = "Unable to open input file.\n";
             int flying;
	     sys_write(4,1,helpMsgOpenF,length(helpMsgOpenF),flying);*/
  
  
  
  
  
  char currChar=*(buffer); 
  //printf("\nChar = %c\n",currChar);
  
//-c flag   
  int newLineCount=0,offset=0;
  if(cFlag==1 || rFlag==1)
	for(;;){
            currChar=*(buffer+offset++);
	    //printf("currChar = %x\n", currChar);
            if(10==(int)currChar)
                newLineCount++;
            if(currChar==0 || currChar<0)//currChar==EOF || ghi
                break;
        }
  if(cFlag==1){//ghi
	char* nlMsg = "The number of newlines =";// %d\n"";
	int resultsOfWritingNumber;
	sys_write(4,2,nlMsg,length(nlMsg),resultsOfWritingNumber);
	
//divide
	/*char nonl = (char)newLineCount;
	char* tryErr = &nonl;
	sys_write(4,2,tryErr,1,resultsOfWritingNumber);
*/
	char* numberToPrint = turnToChar(newLineCount);
	//printf("\nThe string is numberToPrint= %s\n",numberToPrint);
	//printf("\nThe actual number of newlines is = %d\n",newLineCount);
	sys_write(4,2,numberToPrint,length(numberToPrint),resultsOfWritingNumber);
	//if length(numberToPrint)!=resultsOfWritingNumber
	
	//takes int -> returns array with null byte at end
	//mod number by ten and place char equivalent in array then divide it by 10 and do it again
	char beir = '\n';
	char* beirErr = &beir;
	sys_write(4,2,beirErr,1,resultsOfWritingNumber);
}













  //printf("\ng =%d And is about to get turned to -50\n",g); 
  g=-50;
//Open File
struct stat ostbuf;
struct stat *opointy=&ostbuf;
short ofileSize=0;
int tfd=2;
if(stdoutFlag==0){
    //
    sys_write(5,*(argv+argc-1),100|1,511,g);//|1,511,g);
    tfd=g;
    //printf("\n\n\ng ============== %d\n\n\n\n\n",g);
    //sys_writeFile(*(argv+argc-1), 100|1, 511, g);//777,g);//this can't create a new file and put the handle in g
    /*if(flagMakegRed){
    	g=howMuchRed;}*/
	statistics(195,*(argv+argc-1), opointy);
	ofileSize = ostbuf.st_size;
	//printf("\nThe size of the file is %d\n",ofileSize);
	g=tfd;
}else{g=1;}

//printf("\n\ng after open is %d\n\n",g);
/*
int la;
sys_write(4,1,helpMsg,length(helpMsg),la);
*/

  char* cr = "\r";
  char* lf = "\n";
  char* crlf = "\r\n";
  offset=0;
  int amount=0;
  char null=0;
  char* ns=&null;
  int skip=0;
  if(dFlag && !rFlag)
  	while(1){
            currChar=*(buffer+offset);
            if((currChar == 0 || currChar<0)){//currChar==EOF || 
			if(stdoutFlag==0){
                
		//printf("\n\nDifference %d.\n\n",ofileSize-offset);
		int i=1;
	//doesn't have size of file
		int nuld=ofileSize-offset;
		
		//get size of output file
 		for(;i<nuld;i++){
			sys_write(4,g,ns,1,amount);
		}
		//while offset++<size then null 
		//sys_write(4,g,ns,1,amount);
			}		
				break;
}

	    if(13==(int)currChar){skip=1;}
            if((10==(int)currChar) && skip==0)//write//skip!=1 && 
		sys_write(4,g,cr,1,amount);
	   // skip=0;
	    sys_write(4,g,(buffer+offset),1,amount);
            //printf("I just put %x in the file\n",currChar);
	    offset++;
        }
//We already checked that d and u aren't both set so no offset=0;
  if(uFlag && !rFlag)
        while(1){
            currChar=*(buffer+offset);
            if((currChar == 0 || currChar ==-1)){//currChar==EOF || 
			if(stdoutFlag==0){

		//printf("\n\nDifference %d.\n\n",ofileSize-offset);
		int i=1;
		//doesn't have size of file
		int nuld=ofileSize-offset;
		//get size of output file
 		for(;i<nuld;i++){
			sys_write(4,g,ns,1,amount);
		}

		}
                break;
}
            if(13!=(int)currChar)
                sys_write(4,g,(buffer+offset),1,amount);
            //printf("I just put %x in the file\n",currChar);
	    offset++;
        }
  //At most number of newlines + 1 + sizeof buffer
  

  if(rFlag){
        //Get the offset of each newline
        offset=0;
        int nlaIndex=0;//ghi
        //int **newLineArray = malloc(newLineCount*sizeof(int *));
	
	//mmap(0, (newLineCount * sizeof(int *)));//malloc(newLineCount * sizeof(int *));//m 
//	unsigned long specialk = (newLineCount*sizeof(int *));     
//	int **newLineArray;//malloc fuckin impossible
//	brk(261, specialk, specialk);	
	int* array[10000];
        int** newLineArray = &array;

        *(newLineArray+nlaIndex)=0;

        int ttt=1;
        //Get offsets
        for(;;){
            currChar=*(buffer+offset++);
            //printf("currChar = %x\n", currChar);
            if(currChar == 0 || currChar<0)//currChar==EOF || 
                break;
            if(10==(int)currChar)
                nlaIndex++;
            else
                *(newLineArray+nlaIndex)=ttt;
            ttt++;
            //printf("Count is %d\n",*(newLineArray+nlaIndex));
        }
        /*
        int p;
        for(p=newLineCount-1;p>=0;p--){
            printf("The number to add to buffer is %d \n",(int)(*(newLineArray+p)));
            printf("Offset %d should be %x\n",p,*(buffer+(int)(*(newLineArray+p))));
        }
	*/
        //We have the offsets
        int dosFlag=0;
	offset=0;
        //Assuming CR won't be in a UNIX text file.
        if(!uFlag && !dFlag){
            for(;;){
                currChar=*(buffer+offset++);
                if(currChar==13)
                    dosFlag=1;
                if(currChar == 0 || currChar<0 || currChar == 10)//currChar==EOF || 
                    break;
            }
        }
        else
            dosFlag=dFlag;
	if(ofileSize==0){dosFlag=0;}
	//dosFlag=0;
	//printf("\ndosFlag=%d\n",dosFlag);        
	
	offset=0;
        int writeIt;//ghi fix writeIt
        int cobain=0;
        for(writeIt=newLineCount-1;writeIt>=-1;writeIt--){
            if(writeIt!=-1)
                cobain=(int)(*(newLineArray+writeIt))+1;
            else
                cobain=0;
            //
            offset=0;
            //
            for(;;){
            	currChar=*(buffer+cobain+offset);
            	if( currChar == 10 || currChar == 0 || currChar<0  ){//currChar == EOF || 
                	if( dosFlag && writeIt!=(newLineCount-1) ){
                    		sys_write(4,g,crlf,2,amount);
                	}
                	if(!dosFlag && writeIt != (newLineCount-1) ){
                    		sys_write(4,g,lf,1,amount);}
                	break;
                }
            	sys_write(4,g,(buffer+cobain+offset++),1,amount);
            }
        }
        
    }    
  //munmap(&buffer, fileSize);
  //printf("\n\n\nLast call to two arg gets g=%d.\n\n\n",g);
if(stdoutFlag==0){
  twoArg(6,g); }
//Exit
  int status=2;
  sys_exit(status);
  return(0);
}







char* turnToChar(int number){
  long int ttci;
  int ttclength=1;
  for(ttci=1;ttci<1000000;ttci*=10){
	if(   (number-(ttci*10))    <0){
		break;}
	ttclength++;
  }
  ttcarr[ttclength]=0;
  //for(;ttcLength)
  //if length is 3
  //0 1 2
  //965
  //mod 10 -> 5 ---> ttcLength-1
  //number=number/10;
  //...tccLength-2
  int ttcindexfl=1;
  int ttcleftover=-1;
  while(ttclength-ttcindexfl>=0){
	ttcleftover=number%10;
	ttcleftover+=48;
	ttcarr[ttclength-ttcindexfl]=(char)ttcleftover;
	number/=10;
        ttcindexfl++;
  }
  ttcRet = &ttcarr;
  return ttcRet;
}


void letterFlagSetter(char* string){
  int flagLoop=1;
  for(;flagLoop<length(string);flagLoop++)
    switch(*(string+flagLoop)){
        case 'd':
            dFlag=1;
            break;
        case 'c':
            cFlag=1;
            break;
        case 'h':
            hFlag=1;
            break;
        case 'r':
            rFlag=1;
            break;
        case 'u':
            uFlag=1;
        default:
            break;
    }
}

void stdinFlagSetter(char* string){
    if(length(string)==1 && *string==45)
        stdinFlag=1;
}

void stdoutFlagSetter(char* string){
    if(length(string)==1 && *string==45)
        stdoutFlag=1;
}

int length(char* string){
    int length=1;
    for(;;){
        if(*(string+length)==0)break;
        length++;
    }
    return length;
}
