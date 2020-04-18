
#include <iostream>
#include <fstream>
#include <pthread.h>
#include <iomanip>
#include <chrono>
#define no_thread 11;
using namespace std;
using namespace std::chrono;
int res [9];
int cvalid;
int rvalid;
struct sudokuinfo
{
    /* data */
    //column number to start for the 3x3 
    int row;
    //row number to start for the 3x3
    int col;
    int** grids;

} ;
// one function to check all rows
void * checkr(void* m);
// one function to check all columns
void * checkc(void* m);
// one function to check each of the 3x3 grids
void *  checkcol(void* m);
 int main(){


     int puzzle [9][9]={ {2, 4, 8, 3, 9, 5, 7, 1, 6},
                        {5, 7, 1, 6, 2, 8, 3, 4, 9},
                        {9, 3, 6, 7, 4, 1, 5, 8, 2},
                        {6, 8, 2, 5, 3, 9, 1, 7, 4},
                        {3, 5, 9, 1, 7, 4, 6, 2, 8},
                        {7, 1, 4, 8, 6, 2, 9, 5, 3},
                        {8, 6, 3, 4, 1, 7, 2, 9, 5},
                        {1, 9, 5, 2, 8, 6, 4, 3, 7},
                        {4, 2, 7, 9, 5, 3, 8, 6, 1}};

    int** arr = new int*[9];
    for(int p = 0; p<9;p++){
        arr[p]= new int[9];
        for (int u=0;u<9;u++){
            arr[p][u]=puzzle[p][u];
        }
    }
    steady_clock::time_point start_time = steady_clock::now();
    sudokuinfo info;
    bool rowc;
    int rn=0;
    int cn=0;
    info.col=0;
    info.row=0;
    info.grids=arr;
    pthread_t threads[11];
    int t_index=0;
    // thread to check all rows
    pthread_create(&threads[t_index++],NULL, checkr, (void*)&info);
    // pthread to check all columns
    pthread_create(&threads[t_index++],NULL, checkc, (void*)&info);
    //for loop to check for all 3x3 square and create threads for them 
    for (int m=0;m<3;m++){
         cn=0;
         

         for (int e=0;e<3;e++){


             sudokuinfo * info2=(sudokuinfo *)malloc(sizeof(sudokuinfo));

             info2->col=cn;
             info2->row=rn;
             info2->grids=arr;
             pthread_create(&threads[t_index++],NULL, checkcol, info2);
            
             cn=cn+3;
              
         }
         rn=rn+3;}
    int r_index=t_index;
    t_index=0;
    int* results=new int[r_index];
    
    
    // for loop to return the result of all the threads;
    for (int x=0;x<r_index;x++){
        
        
        pthread_join(threads[t_index++],NULL);
        
        
    }
    
    // checking that each of the 3x3 squares produces a valid result
    int rescountfin=0;
    for(int z=0;z<9;z++){
        if(res[z]==1){
            rescountfin++;
        }
    }
    // confirming that parts of the sudoku puzlle are valid and thus confirming the validity of the solution. 
    if(rescountfin==9 && rvalid==1 && cvalid==1){
        cout<<"all valid thread: "<<rescountfin+rvalid+cvalid<<endl;
        cout<<"The following is a valid solution to a sudoku puzzle"<<endl;

    }
    else{
        cout<<"The following is an invalid solution to the sudoku puzzle "<<endl;
    }
    steady_clock::time_point end_time = steady_clock::now();
    long time_taken=duration_cast<milliseconds>(end_time - start_time).count();
    cout<<"Total Time Taken for Sudoku puzzle validation is "<<time_taken<<"ms"<<endl;


    
    
 }
 /** fucntion to check if input array has all the variables from 1-9 in all of the rows
  * @params: void*m void pointer to the struct
  * @returns: bool true or false based if the check is valid or not. 
  * */

  void* checkr(void* m){
       // cast the data into the struct
      struct sudokuinfo * sudata;
      sudata=(struct sudokuinfo *)m;

      int* n = new int [9];
      int q=1;
      // Initialze an array to compare 1-9
      for (int p=0;p<9;p++){
          n[p]=q;
          
          q++;
      }
      int count=0;
      // for loop that loops through the input array m
      for (int u = 0; u < 9; u++)
     {
      q=1;
      //reset the compare array
      for (int p=0;p<9;p++){
          n[p]=q;
          
          q++;
      }
      // for loop to loop the row
      for (int i = 0; i < 9; i++)
      {
          // for loop 2 loops though the initialized array n
        for (int r = 0; r < 9; r++)
        {
            // check if they are equal and add to the count 
            if (sudata->grids[u][i] ==n[r] &&n[r]!=0){
              n[r]=0;
              count=count+1;
              
          }
        }   
      }}
      // if count is 81 then all the row contains all from 1-9 and return true or return false
     if (count==81){
          rvalid=1;   
      }
      else{
          rvalid=0;
      }
      pthread_exit(NULL);
  }
 /** fucntion to check if input array has all the variables from 1-9 in all of the columns
  * @params: void*m void pointer to the struct
  * @returns: bool true or false based if the check is valid or not. 
  * */
   void* checkc(void* m){
       // cast the data into the struct
       struct sudokuinfo * sudata;
      sudata=(struct sudokuinfo *)m;
      int* n = new int [9];
      
      int q=1;
      // Initialze an array to compare 1-9
      for (int p=0;p<9;p++){
          n[p]=q;
          
          q++;
      }
      int count=0;
      // for loop 1 loops through the input array m
      for (int u = 0; u < 9; u++)
     { 
        q=1;
      //reset the compare array
      for (int p=0;p<9;p++){
          n[p]=q;
          
          q++;
      }
      // for loop to loop the column
      for (int i = 0; i < 9; i++)
      {
          // for loop 2 loops though the initialized array n
        for (int r = 0; r < 9; r++)
        {
            // check if they are equal and add to the count 
            if (sudata->grids[i][u] ==n[r] &&n[r]!=0){
              n[r]=0;
              count=count+1;
              
          }
        }
      }}
      // if count is 81 then all the column contains all from 1-9 and return true or return false
 
      if (count==81){
          cvalid=1;
      }
      else{
          cvalid=0;
      }
      pthread_exit(NULL);
  }
   /** fucntion to check if input array has all the variables from 1-9 in a 3x3 grid
  * @params: void*m void pointer to the struct
  * @returns: bool true or false based if the check is valid or not. 
  * */
  void* checkcol(void* m){
      // take the pointer and cast the data into the struct
      struct sudokuinfo * sudata;
      sudata=(struct sudokuinfo *)m;
        int* n = new int [9];
      int q=1;
      // Initialze an array to compare 1-9
      for (int p=0;p<9;p++){
          n[p]=q;
          q++;
      }
      int count=0;
      // for loop 1 loops through the 3x3 based on the data in the struct
       for (int i = sudata->row; i < sudata->row+3; i++)
      { 
          for (int o = sudata->col; o < sudata->col+3; o++)
      {
           for (int r = 0; r < 9; r++)
        {
            // if the data matches the compare grid, then the compare grid index is set to 0 and count is increased
             if (sudata->grids[i][o] ==n[r] &&n[r]!=0){
              n[r]=0;
              count=count+1;
              }}}}
        // if count is 9, all 1-9 values are present in the thread.
         if (count==9){
          res[sudata->row+sudata->col/3]=1;
      }
      else{
          res[sudata->row+sudata->col/3]=0;
          
      }
      pthread_exit(NULL);
  }