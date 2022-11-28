/**
 * Assignment 1: priority queue of processes
 * @file readyqueue.h
 * @author Salma Rashed and Taya Wongsalong (TODO: your name)
 * @brief ReadyQueue is a queue of PCB's that are in the READY state to be scheduled to run.
 * It should be a priority queue such that the process with the highest priority can be selected next.
 * @version 0.1
 */
//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient comments to your code
#pragma once
#include "pcb.h"
using namespace std;

/**
 * @brief A queue of PCB's that are in the READY state to be scheduled to run.
 * It should be a priority queue such that the process with the highest priority can be selected next.
 */
class ReadyQueue {
private:
  // TODO: add your private member variables here

  // choose a data structure for the ReadyQueue. No STL class is allowed.
  // constant declaration for max number of processes
  //PCB* heap;
  static const int MAX_COUNT = 20000;  
  PCB* heap[MAX_COUNT]; // minimum heap of all READY processes
  //PCB** heap ;
  int curr_size;  //current size of heap
//??
  //int cap;  //holds the max size for array caapcit
  

public:
    /**
     * @brief Construct a new ReadyQueue object
     *
     */
    ReadyQueue();
    //?
    ReadyQueue(int cap);  //copy constructor for new PCB array w/ given capacity

    /**
     * @brief Destructor
     */
    ~ReadyQueue();
    


  
	// You may add additional member functions, but don't change the definitions of the following four member functions.

  //Returns true if the queue is empty
  bool isEmpty();

    /**
     * @brief Add a PCB representing a process into the ready queue.
     *
     * @param pcbPtr: the pointer to the PCB to be added
     */
	void addPCB(PCB* pcbPtr);

    /**
     * @brief Remove and return the PCB with the highest priority from the queue
     *
     * @return PCB*: the pointer to the PCB with the highest priority
     */
	PCB* removePCB();

  /**
    * @brief Returns the number of elements in the queue.
    *
     * @return int: the number of PCBs in the queue
  */
  int size();

  /**
    * @brief Display the PCBs in the queue.
  */
	void displayAll();

  void trickleUp();
  void swap(int l1, int l2);
  int getSmallerchild(int i);
  void reheapify();
  int getParent(int childloc);
  bool even(int i);

};