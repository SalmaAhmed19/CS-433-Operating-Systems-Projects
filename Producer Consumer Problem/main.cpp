/**
* Assignment 4: Producer Consumer Problem
 * @file main.cpp
 * @author Salma Rashed and Taya Wongsalong
 * @brief The main program for the producer consumer problem.
 * @version 0.1
 */
//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code
#include<pthread.h>
#include<semaphore.h>
#include <iostream>
#include<time.h>
#include "buffer.h"
#include <unistd.h>

#include <iostream> //added

using namespace std;

//sempahores needed for synchronization
pthread_mutex_t mutux; //mutux lock
sem_t full;  //counting semaphores
sem_t empty; //counting semaphores 


//here 
pthread_attr_t attr;//set of thread attributes 




// global buffer object
Buffer buffer;

// Producer thread function
// TODO: Add your implementation of the producer thread here






void *producer(void *param) {
    // Each producer insert its own ID into the buffer
    // For example, thread 1 will insert 1, thread 2 will insert 2, and so on.
    buffer_item item = *((int *) param);

    while (true) {
        /* sleep for a random period of time */
        usleep(rand()%1000000);

      
        // TODO: Add synchronization code here
         //item=rand()%5;

         sem_wait(&empty); //acquire the semaphore, wait till not full
         pthread_mutex_lock(&mutux); //enforcing the mutux to access critical section




      

         //critical section starts here 
        if (buffer.insert_item(item)) {
            cout << "Producer " << item << ": Inserted item " << item << endl;
            buffer.print_buffer();
        } else {
            cout << "Producer error condition"  << endl;    // shouldn't come here
        }




      
         //critical section ends here 
         pthread_mutex_unlock(&mutux);  //unlock the mutux
         sem_post(&full);      
    }
}

// Consumer thread function
// TODO: Add your implementation of the consumer thread here
void *consumer(void *param) {
    buffer_item item;

    while (true) {
        /* sleep for a random period of time */
        usleep(rand() % 1000000);
        // TODO: Add synchronization code here

        sem_wait(&full);
        pthread_mutex_lock(&mutux);


      
        //critical section starts here       
        if (buffer.remove_item(&item)) {
            cout << "Consumer " << item << ": Removed item " << item << endl;
            buffer.print_buffer();
        } else {
            cout << "Consumer error condition" << endl;    // shouldn't come here
        }

      // critical section ends here 
      pthread_mutex_unlock(&mutux);
      sem_post(&empty);
    }
}

int main(int argc, char *argv[]) {
 //double check here 
  
  //to verify the correct number of arguments were passed im
 if(argc!=4){
    cout<<"Usage: ./assign4 <sleeptime> <pthreadc> <cthreadc>"<<endl;

    exit(1);
  }




  
    /* TODO: 1. Get command line arguments argv[1],argv[2],argv[3] */
   //atoi converts from string to integar  
   int sleeptime=atoi(argv[1]); // 1st argument is the sleep time 
   int pthreadc=atoi(argv[2]); //2nd argument is the number of producer threads 
   int cthreadc=atoi(argv[3]); //3rd argument is the number of consumer threads 


  
    /* TODO: 2. Initialize buffer and synchronization primitives */
  
    pthread_t producer_threads;
    pthread_t consumer_threads ;

  
    pthread_mutex_init(&mutux, NULL); //creating the mutux lock 

   
    sem_init(&full,0,0); //full now is intialized to 0 
  
    sem_init(&empty,0, 5/*buffer_size*/ ); //empty is intialized to buffer size 



  // //here 
  //pthread_attr_init(&attr);


  
    /* TODO: 3. Create producer thread(s).
     * You should pass an unique int ID to each producer thread, starting from 1 to number of threads */
   

   for(int i=0; i< pthreadc;i++){
     int *arg=new int;

     if(arg==NULL){
       cout<<"Cannot allocate memory"<<endl;
       exit (0);
     }
     *arg=i+1;//value that will be producaed onto *producer 

     //pthread_attr_t attr;//set of thread attributes 

     pthread_create(&producer_threads, &attr, producer, (void*) arg);
   }


    /* TODO: 4. Create consumer thread(s) */
    for(int i=0;i<cthreadc;i++){
      pthread_create(&consumer_threads, &attr, consumer, NULL);
    }
    /* TODO: 5. Main thread sleep */
  sleep(sleeptime);

  
    /* TODO: 6. Exit */
  cout<<"\n Threads finished! Exiting..."<<endl;
  exit(0);
}
