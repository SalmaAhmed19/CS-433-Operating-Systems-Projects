
/**
 * Assignment 2: Simple UNIX Shell
 * @file pcbtable.h
 * @author Salma Rashed and Taya Wongsalong
 * @brief This is the main function of a simple UNIX Shell. You may add
 * additional functions in this file for your implementation
 * @version 0.1
 */
// You must complete the all parts marked as "TODO". Delete "TODO" after you are
// done. Remember to add sufficient and clear comments to your code

// This program is not fully functional

#include <cstring>
#include <fcntl.h>
#include <iostream>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

#include <vector>

using namespace std;

#define MAX_LINE 80 // The maximum length command

// global variables (Function prototypes)
int should_run = 1;     // should_run(like true/false) when 1, exit when 0
bool ampersand = false; // should return false if & is not part of the parameter
vector<string> history;
// void parse_command(char command[], char *args[])i


void redirectIN(const char *file) {
  int in = open(file, O_RDONLY);
  //dup2(in, STDIN_FILENO); // 0
  close(in);
}

// Redirection for > operator
void redirectOUT(const char *file) {
  int out = open(file, O_WRONLY | O_APPEND);
  dup2(out, STDOUT_FILENO);
  close(out);
}



/**
 * @brief parse out the command and arguments from the input command separated
 * by spaces
 *
 * @param command
 * @param args
 * @return int
 */
// Purpose: This function parses the buffer ino arguments
// Parameter: command[]=the command, args[]=the argument in the command
int parse_command(char command[], char *args[]) {
  // TODO: implement this function
  int i = 0;
  char *p = strtok(command, " "); // strtok returns a string when it encounters and empty space

  while (p != NULL) {

    args[i] = p;
    p = strtok(NULL, " "); // gets the second token after the second empty space , NULLindicates we are using the same pointer we used before
    i++;
  }

  // if it has & at the end of the argument list, remove it and NULL terminate
  if (strcmp(args[i - 1], "&") == 0) {// strcmp compares two strings charachter by character
    // seg
    args[i - 1] = NULL; // removing
    ampersand = true; // will return true because ampersand is part of the parameter

  } else {
    // terminate
    args[i] = NULL;
    ampersand = false; // not in the argument list
  }
  return i;
}



//may need to delete 
void execShellCommand(char * args[])
{
	/*
	* After reading user input, the steps are:
	* (1) fork a child process using fork()
	* (2) the child process will invoke execvp()
	* (3) if command not included &, parent will invoke wait()
	*/

	pid_t pid = fork();			// step 1

	// child process
	if (pid < 0) {
    cout << "fork: failed to fork process" << endl;
		exit(1);
  }else if(pid == 0){
    // if (execvp(args[0], args) == -1)
		execvp(args[0], args);	// step 2  
	  if(execvp(args[0], args) < 0){
		  cout<<"Command not found\n";
      exit(0);
    }
  } else {// parent process
		if (ampersand) {
			wait(NULL);			// step 3
		}
  }
}



// Purpose: this function saves the command into history
// Parameter: command[] =the command to save
void saveCommand(char command[]) {
  string save(command);    // saving the command using a save function
  history.push_back(save); // push the saved element into the back the vector
}



// Purpose: the user will have four command : exit,!! , < , >
// Parameter:  args[] = the arguments in the command.
void userCommand(char *args[]) {

  string command(args[0]);
  if (command == "exit") { 
    exit(0); // when should run is 0 it exits the p ifam
  
  }
  if (command == "!!") {
    char buffer[MAX_LINE];
    char *args[MAX_LINE / 2 + 1]; 
    int histsize = history.size();


    
   if (history.size() > 1) {
     //saveCommand(buffer);
     
     strcpy(buffer, history[histsize - 1].c_str());
     parse_command(buffer, args);
     cout << history[histsize - 1] << endl;
     execShellCommand(args);
    }else {
     printf("No command history");
    }
  }
  
}


// Purpose: boolean function that checks if the command entered is a user command (will return true) or  execShellCommand (will return false) 
//Parameter:arg[] the arguments in the command
bool typeofcommand(char *args[]) {
  string command(args[0]);
  if (command == "exit" || command == "!!" || command == "<" || command == ">") {// if command is user command return true
    return true;
  } else { // if it's execShellCommand return false
    return false;
  }
}


/**
 * @brief The main function of a simple UNIX Shell. You may add additional
 * functions in this file for your implementation
 * @param argc The number of arguments
 * @param argv The array of arguments
 * @return The exit status of the program
 */
int main(int argc, char *argv[]) {

  char command[MAX_LINE];       // the command that was entered
  char *args[MAX_LINE / 2 + 1]; // parsed out command line arguments
  char buffer_save[MAX_LINE];   // used to save the command
  
  int should_run = 1; /* flag to determine when to exit program */

  while (should_run) {
    printf("osh> ");
    fflush(stdout);

    
    // Read the input command
    // char* get=
    fgets(command, MAX_LINE, stdin); // get user input
    
    command[strlen(command) - 1] = '\0';
      
    saveCommand(buffer_save);
    // Parse the input command
    strcpy(buffer_save, command);			// copy the buffer
    int num_args = parse_command(command, args);
   
		if (typeofcommand(args)) {
			userCommand(args);			// command is user command.
    }else {
			saveCommand(command);		// save command if shell command.
		  execShellCommand(args);		// command is sheand.
		}

  }
  // maybe remove later
  // redirectIN("/dev/tty");
  // redirectOUT("/dev/tty");

  return 0;
} // end of main





// Dont delete TAYA'S NOTES ----okkkkkkk
// Get it compiling step by step

// userCommand function - is not used or called. Needs to be called in the main
// may cause redundancy

// redirection only (step 4)
// Redirect first
// then call execvp() - execute commands
// after user enters the command, inspect command to see if there's a
// redirection operator, if yes, then split/parse if someone types ls -l >
// somefile.txt: will get 2 parse “ls -l”
// output redirection
// somefile.txt
// 1. process the redirection 2. execvp on “ls -l”
// then go back to main

// step 5: piping
// call fork twice

/**
  Pseudo-code a basic shell (not real C++ code):
  while (1) {
    parse_command_line; //get command, args, redirect, etc.
    if(cmd == exit) exit();
    p = fork( );
    if (p == 0) {
    execvp (cmd, args)
  } else {
    if (command doesn't end with &)
    wait( );
  }
}
**/


