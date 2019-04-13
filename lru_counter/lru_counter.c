#include<stdio.h>
 
int findLRU(int time[], int n){
	int i, minimum = time[0], pos = 0;
 
	for(i = 1; i < n; ++i){
		if(time[i] < minimum){
			minimum = time[i];
			pos = i;
		}
	}
	
	return pos;
}
 
int main()
{
	FILE *fin;
	FILE *fout;
    fin=fopen("Input.txt","r");
    fout=fopen("Output.txt","w");
	// printf("Enter number of frames: ");
	// scanf("%d", &no_of_frames);
	int no_of_frames=3;
	int no_of_pages, frames[no_of_frames], pages[30], counter = 0, time[no_of_frames], flag1, flag2, i, j, pos, faults = 0;
	
	// printf("Enter number of pages: ");
	// scanf("%d", &no_of_pages);
//	no_of_pages=20;
	fprintf(fout, "The number of elements in the reference string are :");
    fscanf(fin,"%d",&no_of_pages);
    fprintf(fout, "%d",no_of_pages);
    for(i=0;i<no_of_pages;i++)
    fscanf(fin,"%d",&pages[i]);
    fprintf(fout, "\nThe elements present in the string are\n");
    for(i=0;i<no_of_pages;i++)
    fprintf(fout, "%d  ",pages[i]);
	
//	printf("Enter reference string: ");
//	
//    for(i = 0; i < no_of_pages; ++i){
//    	scanf("%d", &pages[i]);
//    }
    
	for(i = 0; i < no_of_frames; ++i){
    	frames[i] = -1;
    }
    
    for(i = 0; i < no_of_pages; ++i){
    	flag1 = flag2 = 0;
    	
    	for(j = 0; j < no_of_frames; ++j){
    		if(frames[j] == pages[i]){
	    		counter++;
	    		time[j] = counter;
	   			flag1 = flag2 = 1;
	   			break;
   			}
    	}
    	
    	if(flag1 == 0){
			for(j = 0; j < no_of_frames; ++j){
	    		if(frames[j] == -1){
	    			counter++;
	    			faults++;
	    			frames[j] = pages[i];
	    			time[j] = counter;
	    			flag2 = 1;
	    			break;
	    		}
    		}	
    	}
    	
    	if(flag2 == 0){
    		pos = findLRU(time, no_of_frames);
    		counter++;
    		faults++;
    		frames[pos] = pages[i];
    		time[pos] = counter;
    	}
    	
    	fprintf(fout, "\n");
    	
    	for(j = 0; j < no_of_frames; ++j){
    		fprintf(fout, "%d\t", frames[j]);
    	}
	}
	
	fprintf(fout, "\n\nTotal Page Faults for no. of frames %d = %d",no_of_frames, faults);
    
    return 0;
}
