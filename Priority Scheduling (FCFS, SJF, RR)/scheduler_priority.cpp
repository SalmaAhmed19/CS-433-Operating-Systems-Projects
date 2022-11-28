/**
* Assignment 3: CPU Scheduler
 * @file scheduler_priority.cpp
 * @author Taya Wongsalong and Salma Rashed
 * @brief This Scheduler class implements the Priority scheduling algorithm.
 * @version 0.1
 */
//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code


#include "scheduler_priority.h"
#include <iomanip>
#include <iostream>

// TODO: add implementation of SchedulerFCFS constructor, destrcutor and 
// member functions init, print_results, and simulate here

//Purpose: constructor 
 SchedulerPriority::SchedulerPriority(){
   count = 0; //setting count to 0
   average_turn = 0.0; //setting avergae turn to 0
   average_waiting = 0.0; //setting average waiting to 0
   completion = 0; //setting completion time to 0
   waiting=0.0; //setting waiting time to 0
   turnaround=0; //setting turnaround to 0
  
}

//Purpose: destructor 
 SchedulerPriority::~SchedulerPriority(){
   while(!myQueue.empty()){ //while vector is not empty 
     myQueue.pop_back();//removes the last element in the vector
  }
}
   
// Purpose: called once before the simulation starts.It is used to initialize the scheduler.
// parameter : process_list The list of processes in the simulation.
void SchedulerPriority::init(std::vector<PCB>& process_list){

  int index = 0;  //setting index to 0
  int q_size = process_list.size(); //setting q size ti the vector size 

  while(index != q_size){ //while the index is not equal to q_size
    myQueue.push_back(process_list[index]); //Adds a new element at the end of the vector
    index++; //increment index
    count++;//increment count 
  }
  
}

void SchedulerPriority::print_results(){

  int queue_size = myQueue.size(); //setting q size to the pcb vevtor size 

  for(int i = 0;i < queue_size; i++){ 
    //outputting 
    cout << myQueue[i].name << " turn-around time = " << myQueue[i].turnaround << ", waiting time = " << myQueue[i].waiting << endl;
  }
 //outputting average turnaround time and average waiting time
   cout << "Average turn-around time =" << fixed << showpoint << setprecision(3)<< average_turn << ", Average waiting time = " << fixed << showpoint << setprecision(3) << average_waiting << endl;

}

//Purpose: This function simulates the scheduling of processes in the ready queue.It stops when all processes are finished.

void SchedulerPriority::simulate(){
  bool done = false; //setting a condition for our while loop 
  double total_wait=0;//setting total wait to 0
  double total_turn=0; //setting total turn to 0
  int shortest_num = 0;//setting shortest num to 0
  int save_index=0; //setting save index to 0
  int temp_counter = 0; //setting temp counter to 0

  while(!done) { //while done is not false/ as long as its true
    shortest_num = 0;
    for(int i = 0; i < count; i++){
     if(myQueue[i].priority > shortest_num) { //if priority is greater than shortest num
       shortest_num = myQueue[i].priority; //set shortest num to priority 
       save_index = i;//set save index to i 
       
     } 
    }

    //cout << "current pcb is: " << myQueue[save_index].name << endl; 


    //output
    cout<<"Running Process " << myQueue[save_index].name << " for " << myQueue[save_index].burst_time << " time units"<< endl;


    //completion formula
    completion = completion + myQueue[save_index].burst_time;


    //turnaround time formula and total turnaround formula
    myQueue[save_index].turnaround = completion - myQueue[save_index].arrival_time;
    //the total turnaround time 
    total_turn = total_turn + myQueue[save_index].turnaround;




    
     //waiting time formula and total wait formula
    myQueue[save_index].waiting = myQueue[save_index].turnaround - myQueue[save_index].burst_time;
        total_wait = total_wait+ myQueue[save_index].waiting;

    //here 
    myQueue[save_index].priority = 0; 



    
    temp_counter++;//incrementing temp counter 
    if(temp_counter == count) { 
      done = true; //once temp counter is equal our counter done is set to true and the while loop will stop 
    }
  }
    average_turn = total_turn/ count; //average turnaround formula 
    average_waiting= total_wait/ count;//average waiting formula 
	  
  }