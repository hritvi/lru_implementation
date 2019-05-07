#include <iostream>
#include <math.h>
#include <chrono>
#define FRAMES 1
#define HISTORY 10

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
        }
    }
    return page_faults;
}

int main() {
    int n, i, requests[20];
    int pageFaultCount = 0;
    FILE *fp;
    fp = fopen("Input.txt", "r");
    fscanf(fp, "%d", &n);
    
    for (i = 0; i < n; i++)
    {
        fscanf(fp, "%d", &requests[i]);
    }

    auto start = std::chrono::high_resolution_clock::now();

    pageFaultCount = lru_aging(requests, FRAMES, HISTORY, n);

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "Page faults: " << pageFaultCount << std::endl;
    std::cout << "Time elapsed: " << duration.count() << std::endl;
    return 0;
}