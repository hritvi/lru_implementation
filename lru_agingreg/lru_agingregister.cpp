#include <iostream>
#include <vector>
#include <stdio.h>
#include <math.h>

FILE *fin=fopen("Input.txt","r");
FILE *fout=fopen("Output.txt","w");

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
    fprintf(fout, "Registers values now :\n");
    for(int i = 0; i < num_frames; i++) {
        fprintf(fout, "    %d\n", aging_regs[i]);
    }
}

void print_frame_state(int frames[], int num_frames)
{
    fprintf(fout, "Current values in frames are :\n");
    for (int i = 0; i < num_frames; i++) {
        fprintf(fout, "    %d\n", frames[i]);
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
        fprintf(fout, "we replaced number at %d\n", replaced_frames_idx);
        } else{
            fprintf(fout,"We replaced nothing !\n");
        }
        print_frame_state(frames, num_frames_in_system);
        print_regs(aging_regs, num_frames_in_system);
    }
//    printf("%d\n", page_faults);

    return page_faults;
}

int main() {
    int n;
    int i=0;
    
	fprintf(fout, "The number of elements in the reference string are :");
    fscanf(fin,"%d",&n);
    fprintf(fout, "%d",n);
    
	int requests[n];
    
    for(i=0;i<n;i++)
    	fscanf(fin,"%d",&requests[i]);
    fprintf(fout, "\nThe elements present in the string are\n");
    for(i=0;i<n;i++)
    	fprintf(fout, "%d  ",requests[i]);
    fprintf(fout, "\n\n");
    
    // int requests[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
    // int requests[] = {7, 10, 1, 2, 10, 3, 5, 4, 2, 6, 9, 3, 8, 3, 2, 7, 9, 8, 6, 1};
    fprintf(fout, "\nPage faults: %d\n" ,lru_aging(requests, 1, 6, n));
    return 0;
}
