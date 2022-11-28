/**
* Assignment 3: CPU Scheduler
 * @file scheduler_sjf.cpp
 * @author Taya Wongsalong and Salma Rashed
 * @brief This Scheduler class implements the SJF scheduling algorithm.
 * @version 0.1
 */
//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code

#include "scheduler_sjf.h"
#include <iomanip>
#include <iostream>


//Purpose: constructor
 SchedulerSJF::SchedulerSJF(){
   count = 0; //intializing count
   average_turn = 0.0; //intializing avergae turnaround time
   average_waiting = 0.0;  //intializing average waiting time 
   completion = 0; // intializing completion time 
   
   turnaround=0; //intializing turnaround time 
   waiting=0; //intializing waiting time 
}

//Purpose: destructor 
 SchedulerSJF::~SchedulerSJF(){
   while(!myQueue.empty()){ // while the vector is not empty 
     myQueue.pop_back(); //removes the last element in the vector
  }
}
   
// Purpose: called once before the simulation starts.It is used to initialize the scheduler.
// parameter : process_list The list of processes in the simulation.
void SchedulerSJF::init(std::vector<PCB>& process_list){

  int index=0; //intializing index

  int q_size=process_list.size(); //setting q size to the pcb vevtor size 

  while(index!=q_size){   //while our index is not equal to the vector
    myQueue.push_back(process_list[index]); //Adds a new element at the end of the vector
    index++; //increment index
    count++; //increment count 
  }
}

void SchedulerSJF::print_results(){

  int queue_size=myQueue.size(); //setting queue_size to the vector size 
    //for loop to print 
  for(int i=0;i<queue_size;i++){
    cout<<myQueue[i].name<<" turn-around time = "<<myQueue[i].turnaround<<", waiting time = "<<myQueue[i].waiting<<endl;
  }
  //average output 
   cout<<"Average turn-around time ="<<fixed<<showpoint<<setprecision(2)<<average_turn<<", Average waiting time = "<<fixed<<showpoint<<setprecision(2)<<average_waiting<<endl;

}


//Purpose: This function simulates the scheduling of processes in the ready queue.It stops when all processes are finished.

void SchedulerSJF::simulate(){
  bool done = false; //setting a condition for our while loop 
  double total_wait=0; //setting total wait to 0
  double total_turn=0; //setting total turn to 0
  int shortest_num = 1000;//setting shortest_num to 1000
  int save_index=0; //setting save index to 0
  int temp_counter = 0; //setting temp_counter=0

  while(!done) {  //while done is not false/ as long as its true

    shortest_num = 1000;
    for(int i = 0; i < count; i++){ //for loop to keep on running 

     if(myQueue[i].burst_time < shortest_num) { //if burst is less than the shortes num 
       shortest_num = myQueue[i].burst_time; //then we will set shortest num to the burst time
       save_index = i; //update save index
       
     } 
    }

   //outputting 
    cout<<"Running Process "<<myQueue[save_index].name<<" for "<<myQueue[save_index].burst_time<<" time units"<<endl; 


    //completion formula
    completion = completion + myQueue[save_index].burst_time;

    //calculation turn around and total turnaround  
    myQueue[save_index].turnaround = completion - myQueue[save_index].arrival_time;
    total_turn = total_turn+myQueue[save_index].turnaround;

    //waiting time formula and the total waiting formula 
    myQueue[save_index].waiting=myQueue[save_index].turnaround-myQueue[save_index].burst_time;
        total_wait = total_wait+ myQueue[save_index].waiting;
    myQueue[save_index].burst_time = 5000; 
    temp_counter++; //increment temp counter 
    if(temp_counter == count) { 
      done = true;
    }
  }
    average_turn = total_turn/ count; //calculating average turn 
    average_waiting= total_wait/ count; //calculating average waiting
	  
  }
 
