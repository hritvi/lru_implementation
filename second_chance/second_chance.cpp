#include<stdio.h>
#include<conio.h>
#define SIZE 3

FILE *fin=fopen("Input.txt","r");
FILE *fout=fopen("Output.txt","w");

int full=0;
int a[21];
int ref[SIZE];
int frame[SIZE];
int repptr=0;
int count=0;

int display(){
	int i;
	fprintf(fout, "\nThe elements in the frame are\n");
	for(i=0;i<full;i++)
	fprintf(fout, "%d\n",frame[i]);        
}

int Pagerep(int ele)
{
 int temp;

while(ref[repptr]!=0)
{ 
    ref[repptr++]=0;
    if(repptr==SIZE)
    repptr=0;
}                     
 
 temp=frame[repptr];
 frame[repptr]=ele;
 ref[repptr]=1;

 return temp;   
}
int Pagefault(int ele){
    if(full!=SIZE)
    {
        ref[full]=1;
        frame[full++]=ele;
    }
    else
        fprintf(fout, "The page replaced is %d\n",Pagerep(ele));
}
int Search(int ele){
    int i,flag;
    flag=0;
    if(full!=0)
    {
        for(i=0;i<full;i++)
        if(ele==frame[i]){   
            flag=1;ref[i]=1;
            break;
        }
    }
     return flag;   
}

int main()
{
    int n,i;
    fprintf(fout, "The number of elements in the reference string are :");
    fscanf(fin,"%d",&n);
    fprintf(fout, "%d",n);
    for(i=0;i<n;i++)
        fscanf(fin,"%d",&a[i]);
    fprintf(fout, "\nThe elements present in the string are\n");
    for(i=0;i<n;i++)
        fprintf(fout, "%d  ",a[i]);
    fprintf(fout, "\n\n");
    
    for(i=0;i<n;i++){
        if(Search(a[i])!=1){
            Pagefault(a[i]);
            display();
             count++;
        }                    
    }
    fprintf(fout, "\nThe number of page faults are %d\n",count);
//                    getche();
return 0;
}
