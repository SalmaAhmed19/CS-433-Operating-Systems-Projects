/**
* Assignment 3: CPU Scheduler
 * @file scheduler_rr.h
 * @author ??? (TODO: your name)
 * @brief This Scheduler class implements the RoundRobin (RR) scheduling algorithm.
 * @version 0.1
 */
//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code
//



#include "scheduler_rr.h"
#include <queue>
#include <vector>

 SchedulerRR::SchedulerRR(int time_quantum)
 {
    time_q = time_quantum;
    avgTt = 0.00;
    avgWt = 0.00;
 }

 SchedulerRR::~SchedulerRR()
 {
    while(rr.empty() != true){
        rr.pop();
    }
 }

 void SchedulerRR::init(std::vector<PCB>& process_list)
 {
    for(int i = 0; i < process_list.size(); i++){
        rr.push(process_list[i]);
    }
 }

 void SchedulerRR::print_results()
 {
    // use a boolean to run through each spot and check if it is time to print that process
    // run in terms of process.[id], where id == i is the print-worthy scenario
    for(int i = 0; i < postVec.size(); i++){
        bool found = false;
        while(found != true){
            for(int j = 0; j < postVec.size(); j++){
                if(postVec[j].id == i ){
                    cout << postVec[j].name << " turn-around time = " << postVec[j].turnaround << ", waiting time = " << postVec[j].waiting<< endl;
                    found = true;
                }
            }
        }
    }
    cout << "Average turn-around time = " << avgTt << ", Average waiting time = " << avgWt << endl;
 }

 void SchedulerRR::simulate()
 {
    int totalTt = 0;
    int totalWt = 0;
    int s = rr.size();
    

    int time = 0;
    while(rr.size() > 0){
        //first case: PCB releases involuntarily -> burst time greater than time quantum
        if(rr.front().burst_time > time_q){
            cout << "Running process " << rr.front().name << " for " << time_q << " time units\n";
            time += time_q;
            rr.front().waiting += time_q;
            rr.front().burst_time -= time_q;
            PCB prempted = rr.front();
            rr.pop();
            rr.push(prempted);
        }
        //second case: PCB releases voluntarily -> burst time equal to or less than time quantum
        else if(rr.front().burst_time <= time_q){
            cout << "Running process " << rr.front().name << " for " << time_q << " time units\n";
            rr.front().waiting += rr.front().burst_time;
            time += rr.front().burst_time;

            rr.front().turnaround = time;

            totalTt += time;    
            rr.front().waiting = time - rr.front().waiting;
            totalWt += rr.front().waiting;
            postVec.push_back(rr.front());
            rr.pop();
        }
    }
    avgTt = totalTt / (s * 1.0);
    avgWt = totalWt / (s * 1.0);
 }