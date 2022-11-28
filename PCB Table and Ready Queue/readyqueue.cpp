#include <iostream>
#include "readyqueue.h"
using namespace std;

//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient comments to your code


/**
 * @brief Constructor for the ReadyQueue class.
 */
 ReadyQueue::ReadyQueue():heap{} {
  //TODO: add your code here
  // heap = new PCB[cap];
  curr_size = 0; 
   /*
  this->cap = 5000;  //set default to 5000 ?
  for(int i = 0; i < MAX_COUNT;i++){
   //PCB** heap = new PCB[cap];  //??
   curr_size = 0;  //initialize currrent size to 0
  } */

}

/**
 * @brief COPY Constructor for the ReadyQueue class.
 */     //??????
/*
 ReadyQueue::ReadyQueue(int cap) {
  //TODO: add your code here
  this->cap = cap;   // ??
  //heap = new PCB[cap];  //?? --heap array initialize
  //PCB* heap = new PCB[cap];  //??
  curr_size = 0;  //initialize currrent size to 0
  
}
*/
//Destructor
ReadyQueue::~ReadyQueue() {}

/**
 * @brief Add a PCB representing a process into the ready queue.
 *
 * @param pcbPtr: the pointer to the PCB to be added
 */
void ReadyQueue::addPCB(PCB *pcbPtr) {

  heap[curr_size] = pcbPtr;
  heap[curr_size]->setState(ProcState::READY);  
  trickleUp();  
  curr_size++;  //increment the currnt size

}

bool ReadyQueue::even(int i)
{
  if ((i % 2) ==  0) return true; else return false; 
}

// Purpose: find the location of the parent 
// The child location is given.  Need to call even.
int ReadyQueue::getParent(int childloc)
{
  int parent;
  //  return the parent location based on the child loc
  if(even(childloc)) { //even
      parent = (childloc - 2)/2;
      
    }
    else {
      parent = (childloc - 1)/2;  //odd
    }
    return parent;
}


  void ReadyQueue::trickleUp() {
  int x = curr_size - 1;  // the very last job's location
  int parent = getParent(x);
  // While x is > 0   
  //    compare Q[x] with the parent value (*)
  //    and if the parent value is bigger call swap & update x 
  //    to be the parent location. Otherwise stop the loop.
  // (*) Call getParent to get the location of the parent
  //            based on the child's location.
  while(x > 0){
    if(heap[x]->priority > heap[parent]->priority){
      //TESTING
      //cout << "Swapping x and parent";
      swap(x, parent);
      x = parent;
      parent = getParent(x); //keep comparing the elem of x
    }
    else return;
    }
  }

    
/**
 * @brief Remove and return the PCB with the highest priority from the queue
 *
 * @return PCB*: the pointer to the PCB with the highest priority
 */

int ReadyQueue::getSmallerchild(int i)
{ int LC, RC; // locations of children
  int smallest;
 // ** // set LC and RC first.
  LC=(2*i)+1;
  RC=(2*i)+2;

//    return the location of the smaller child 
//    Be careful because one or both of them may be
//    beyond count-1 or just the RC is beyond count-1.
//    Check boundaries before you 
//    compare Q contents!!!!
//    If both are beyond count-1, you want to return a special value.
// **
  if(LC>curr_size-1&& RC>curr_size-1){//both beyond count -1
    return -1;
  }else if (LC>curr_size-1 && RC<curr_size-1){//LC beyound count-1
    return RC;
  }else if(LC<curr_size-1 && RC>curr_size-1){//RC beyond count-1
    return RC;
  }else{//regular case-both NOT  beyond count-1
    if(heap[LC]->priority < heap[RC]->priority){
      return RC;
    }else{
      return LC;
    }
  }//end of 1st else
}



void ReadyQueue::reheapify()
{ 

  
  int X;   // the current location
  heap[0] = heap[curr_size-1];  // move the last job to the front
  
  curr_size--;
  //  Start X at 0 (the root)
  // **
  X=0;
  //  While X is within the array (the used portion):
  //       Find the location of the smaller child by calling getSmallerchild.
  //       (if the location of both children are off the tree, stop the loop).
  //       If the smaller child is larger than the parent value,
  //          call swap and X becomes the smaller child's location.
  //       else no swaps so stop to loop.
  //  **


  while(X < curr_size) {
    int child = getSmallerchild(X);
    
    if(child != -1 && heap[child]->priority > heap[X]->priority){  //-1 means that both children are beyond -1 
       //testing
      //cout << heap[child]->priority << ", " << heap[X]->priority << endl;
      
      swap(child, X);
      X = child;
    }else{
      return ;

    }//end of the else 
  }//end of the while loop 
}



PCB* ReadyQueue::removePCB() {
  //TODO: add your code here
  // When removing a PCB from the queue, you must change its state to RUNNING.

  heap[0]->state=ProcState::RUNNING;
  PCB* temp = heap[0];
  reheapify();
  return temp;

}



// PURPOSE: Swap the positions of two PCB's on the PCB array
void ReadyQueue::swap(int l1, int l2) {
  PCB* temp = heap[l1];
  heap[l1] = heap[l2];
  heap[l2] = temp;
}
  
  

/**
 * @brief Returns the number of elements in the queue.
 *
 * @return int: the number of PCBs in the queue
 */
int ReadyQueue::size() {
  //TODO: add your code here
  return curr_size; 

}

/**
 * @brief Display the PCBs in the queue.
 */
void ReadyQueue::displayAll() {
  //TODO: add your code here

  //call the display function in pcb.h
  cout << "Display Processes in ReadyQueue" << endl;
 for (int i = 0; i < curr_size; i++) {
     heap[i]->display(); //display() was already done in pcb.h all we have to is to call it
   }
  
}

// Added this function in .h too, but not sure if it's neded - TW
/**
 * @brief checks if the queue is empty then returns if it is.
 */
bool ReadyQueue::isEmpty() {
  return (curr_size == 0); //returning the current size as 0
}