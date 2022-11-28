/**
* Assignment 3: CPU Scheduler
 * @file scheduler_fcfs.cpp
 * @author Taya Wongsalong and Salma Rashed
 * @brief This Scheduler class implements the FCSF scheduling algorithm.
 * @version 0.1
 */
//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code

#include "scheduler_fcfs.h"
#include <iostream>
#include <iomanip>
// TODO: add implementation of SchedulerFCFS constructor, destrcutor and 
// member functions init, print_results, and simulate here



//Purpose: Constructor
 SchedulerFCFS::SchedulerFCFS(){

   curr_size = 0;    //setting curr_size to 0
   average_turn = 0.0; //setting average turn to 0 
   average_waiting = 0.0; //setting average waiting to 0
   completion = 0; //setting completion time to 0

}

//Purpose: destructor to destroy the schedulerFCFS object
 SchedulerFCFS::~SchedulerFCFS(){
 
   while(!myQueue.empty()){ //while the vector is not empty 
     myQueue.pop_back();//removes the last element in the vector
  }
  
}



// Purpose: called once before the simulation starts.It is used to initialize the scheduler.
// parameter : process_list The list of processes in the simulation.
void SchedulerFCFS::init(std::vector<PCB>& process_list){

  int index=0; //intializing the index

  int q_size=process_list.size(); //setting q_size to the size of the process_list->vector size 
  
  while(index!=q_size){ // as long as the index is not equal to the pcb vector size 
    myQueue.push_back(process_list[index]); //Adds a new element at the end of the vector
    index++; //incrementing the index 
    curr_size++; //incrementing the curr size
  }
  

}





//Purpose: called once after the simulation ends and prints result of the stimulation.
  
void SchedulerFCFS::print_results(){

   
  int queue_size=myQueue.size(); //setting queue_size to the size of the vector
  
  
  //for loop to print 
  for(int i=0;i<queue_size;i++){ 
    cout<<myQueue[i].name<<" turn-around time = "<<myQueue[i].turnaround<<", waiting time = "<<myQueue[i].waiting<<endl;
  }


  //average output
   cout<<"Average turn-around time ="<<fixed<<showpoint<<setprecision(3)<<average_turn<<", Average waiting time = "<<fixed<<showpoint<<setprecision(3)<<average_waiting<<endl;

   
}





  
//Purpose: This function simulates the scheduling of processes in the ready queue.It stops when all processes are finished.

void SchedulerFCFS::simulate(){

  int total_wait=0; //intializing total wait 
  int total_turn=0; //intializing total turn


  for(int i=0;i<curr_size;i++){  // for loop that keeps on running while less than curr size to print and do the equation 




    //printing 
    cout<<"Running Process "<<myQueue[i].name<<" for "<<myQueue[i].burst_time<<" time units"<<endl;


    //completion formula
    completion=completion+myQueue[i].burst_time;


    //Formulas: calculating turnaround,total, and average 
    myQueue[i].turnaround = completion - myQueue[i].arrival_time;
    total_turn = total_turn+myQueue[i].turnaround;
    average_turn = total_turn/ double(curr_size);

    

    //Formulas: calculating waiting, total, and average 
    myQueue[i].waiting=myQueue[i].turnaround-myQueue[i].burst_time;
  	total_wait = total_wait+ myQueue[i].waiting;
    average_waiting= total_wait/ double(curr_size);
	  
  }
 
}



