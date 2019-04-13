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
	FILE *fp;
    fp=fopen("Input.txt","r");
    // printf("Enter number of frames: ");
	// scanf("%d", &no_of_frames);
	no_of_frames=9;
	int no_of_frames, no_of_pages, frames[no_of_frames], pages[30], counter = 0, time[no_of_frames], flag1, flag2, i, j, pos, faults = 0;
	
	// printf("Enter number of pages: ");
	// scanf("%d", &no_of_pages);
//	no_of_pages=20;
	printf("The number of elements in the reference string are :");
    fscanf(fp,"%d",&no_of_pages);
    printf("%d",no_of_pages);
    for(i=0;i<no_of_pages;i++)
    fscanf(fp,"%d",&pages[i]);
    printf("\nThe elements present in the string are\n");
    for(i=0;i<no_of_pages;i++)
    printf("%d  ",pages[i]);
	
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
    	
    	printf("\n");
    	
    	for(j = 0; j < no_of_frames; ++j){
    		printf("%d\t", frames[j]);
    	}
	}
	
	printf("\n\nTotal Page Faults = %d", faults);
    
    return 0;
}
