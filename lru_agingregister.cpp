#include <iostream>
#include <vector>
#include <stdio.h>
#include <math.h>

int find_page_in_frames(int frames[], int aging_regs[], int page_num, int num_frames, int history_to_look)
{
    for(int i = 0; i < num_frames; i++) {
        aging_regs[i]  = aging_regs[i] >> 1;
    }
    for(int i = 0; i < num_frames; i++) {
        if(frames[i] == page_num) {
            aging_regs[i] += pow(2, history_to_look);
            return i;
        }
    }
    return -1;
}

int replace(int frames[], int aging_regs[], int new_page, int num_frames, int history_to_look)
{
    int min_idx = 0;
    int min = aging_regs[min_idx];
    for(int i = 0; i < num_frames; i++) {
        if(aging_regs[i] < min) {
            min_idx = i;
            min = aging_regs[min_idx];
        }
    }

    frames[min_idx] = new_page;
    aging_regs[min_idx] += pow(2, history_to_look);

    return min_idx;
}

void print_regs(int aging_regs[], int num_frames) {
    printf("Registers values now :\n");
    for(int i = 0; i < num_frames; i++) {
        printf("    %d\n", aging_regs[i]);
    }
}

void print_frame_state(int frames[], int num_frames)
{
    printf("Current values in frames are :\n");
    for (int i = 0; i < num_frames; i++) {
        printf("    %d\n", frames[i]);
    }
}

int lru_aging(int requests[], int num_frames_in_system, int history_to_look, int num_requests)
{
     int aging_regs[num_frames_in_system]={};
     int page_faults = 0;
     int index = 0;
     int frames[num_frames_in_system] = {};
     for(int j=0;j<num_requests;j++){
        index = find_page_in_frames(frames, aging_regs, requests[j], num_frames_in_system,
        history_to_look);
        if(index == -1) {
            page_faults++;
        int replaced_frames_idx = replace(frames, aging_regs, requests[j], num_frames_in_system,
        history_to_look);
        printf("we replaced number at %d\n", replaced_frames_idx);
        } else{
            printf("We replaced nothing !\n");
        }
        print_frame_state(frames, num_frames_in_system);
        print_regs(aging_regs, num_frames_in_system);
    }
//    printf("%d\n", page_faults);

    return page_faults;
}

int main() {
    FILE *fp;
    fp=fopen("Input.txt","r");
    int n;
    int i=0;
    printf("The number of elements in the reference string are :");
    fscanf(fp,"%d",&n);
    printf("%d",n);
    
	int requests[n];
    
    for(i=0;i<n;i++)
    	fscanf(fp,"%d",&requests[i]);
    printf("\nThe elements present in the string are\n");
    for(i=0;i<n;i++)
    printf("%d  ",requests[i]);
    printf("\n\n");
    
    // int requests[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
    // int requests[] = {7, 10, 1, 2, 10, 3, 5, 4, 2, 6, 9, 3, 8, 3, 2, 7, 9, 8, 6, 1};
    std::cout <<"\nPage faults: "<< lru_aging(requests, 1, 6, n) <<"\n"<< std::endl;
    return 0;
}
