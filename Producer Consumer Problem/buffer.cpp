/**
* Assignment 4: Producer Consumer Problem
 * @file buffer.cpp
 * @author Salma Rashed and Taya Wongsalong
 * @brief Implementation file for the buffer class
 * @version 0.1
 */

//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code
#include "buffer.h"
#include<iostream>
#include<iomanip>

using namespace std;





//Purpose: constructor 
Buffer::Buffer(int size ){


  
  buffer[0]=0; //setting the buffer size to the given size 
  front = 0; //intializing front to 0
  back = -1; //intializing back to 0 
  count = 0; //intializing count to 0 //return in the coun t function
  s=size;//in th get size function return it 



  

  //need to double check this one!!!!!!! here or in the.h?
   //buffer[buffer_size]; // to create the circular buffer 
  
  
}


//Purpose: destructor
Buffer::~Buffer(){

  while(!is_empty()){
    buffer_item temp=buffer[front];
    remove_item(&temp);
  }
}

//Purpose: inserts an item into the circular buffer by updating back pointer 
// Parameter: the item to insert into the buffer
//returns -1 if the insert fails 
bool Buffer::insert_item(buffer_item item){


  
  if(!is_full()){


    
    back=(back+1)% buffer_size;
    buffer[back]=item;
    count++;

    return true;//return 0;
  }else{

    return false;//return -1;
  }




  
}


//Purpose:removes an item from circular buffer by updating the front pointer 
//Parameter: *item: tje item removed from the buffer 
//return 0 if insert was successful and -1 if it fails 
 bool Buffer::remove_item(buffer_item *item){
   if(!is_empty()){
     *item=buffer[front];
     front=(front+1)%buffer_size;
     count--;

     return true;//return 0;
   }
   return false;//return -1;
 }

//Purpose: get the size of the buffer 
 int Buffer::get_size(){

   return s ;
 }



//Purpose: gets the count that will helps us determine if its full or if its empty 
int Buffer::get_count(){
  return count;
}



//Purpose: checks if the buffer is empty
bool Buffer::is_empty(){
  if(count==0){
    return true;
  }else{
    return false;
  }
  
}


//purpose : checks if the buffer is full
bool Buffer::is_full(){
  if(count==buffer_size){
    return true;
  }else{
    return false;
  }
  
}



//Purpose: Prints the buffer elements and if deleting/inserting 

void Buffer::print_buffer(){

  if(is_empty()){ //incase it's empty 
    cout<<"[empty]"<<endl;
  }else{

  
    int j=front; //set j to the front 
    cout<<"Buffer[ ";

    for(int i=0;i<count;i++){
      cout<<buffer[j]; //output the elements in the buffer one by one till we reach the end 

      j=(j+1)%buffer_size; //to make sure it's circular 
    }

   cout<<"]"<<endl; 
  }


  
}