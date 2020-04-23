#include <iostream>
#include <fstream>
#include <chrono>
#include <iomanip>
using namespace std;
using namespace std::chrono;
struct data
{
    /* data */
    int row;
    int col;
    int** s;

};

bool checkr(int ** m, int rn);
bool checkc(int ** m, int cn);
bool checkcol(int ** m, int rn,int cn);
 int main(){
     int array [9][9]={ {2, 4, 8, 3, 9, 5, 7, 1, 6},
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
            arr[p][u]=array[p][u];
        }
    }
    steady_clock::time_point start_time = steady_clock::now();
    // for loop to crete array and comulm data into arrays to be tested.
    bool rc;
    bool cc;
    bool rowc;
    int rn=0;
    int cn=0;
     for (int i = 0; i < 9; i++)
     {   
           
        rc =checkr(arr, i);
        cc=checkc(arr,i);
       
        if (rc==0 || cc==0){
            cout<<"invalid solution";
            break;
        }     
     }
     for (int m=0;m<3;m++){
         cn=0;
         

         for (int e=0;e<3;e++){
             rowc=checkcol(arr,rn,cn);
             cn=cn+3;
             //cout<<rn<<"  "<<cn<<"  "<<endl;
             if(rowc==0){
                  cout<<"The Following is an invalid solution to the sudoku puzzle"<< endl;
                    break;
             }
         }
         rn=rn+3;}
     if(rc==1 && cc==1&&rowc==1){
         cout<<"Number of valid threads: 1"<<endl;
         cout<<"The following is a valid solution to the sudoku puzzle"<< endl;    
     }
    steady_clock::time_point end_time = steady_clock::now();
    long time_taken=duration_cast<nanoseconds>(end_time - start_time).count();
    cout<<"Total Time Taken for Sudoku puzzle validation is "<<time_taken<<"ns"<<endl;
 }
 /** fucntion to check if input array has all the variables from 1-9
  * @params: int*m int array pointer to the array to be checked
  * @returns: bool true or false based if the check is valid or not. 
  * */

  bool checkr(int** m,int rn){
      int* n = new int [9];
      int q=1;
      // Initialze an array to compare 1-9
      for (int p=0;p<9;p++){
          n[p]=q;
          q++;
      }
      int count=0;
      // for loop 1 loops through the input array m
      for (int i = 0; i < 9; i++)
      {
          // for loop 2 loops though the initialized array n
        for (int r = 0; r < 9; r++)
        {
            // check if they are equal and add to the count 
            if (m[rn][i] ==n[r] &&n[r]!=0){
              n[r]=0;
              count=count+1;
          }
        }   
      }
      // if count is 9 then the row contains all from 1-9 and return true or return false
      if (count==9){
          return true;
      }
      return false;
  }
   bool checkc(int** m,int cn){
      int* n = new int [9];
      int q=1;
      // Initialze an array to compare 1-9
      for (int p=0;p<9;p++){
          n[p]=q;
          q++;
      }
      int count=0;
      // for loop 1 loops through the input array m
      //cout<<"newrow"<<endl;
      for (int i = 0; i < 9; i++)
      {
          // for loop 2 loops though the initialized array n
        for (int r = 0; r < 9; r++)
        {
            //cout<<m[i][cn]<<"  "<<n[r]<<endl;
            // check if they are equal and add to the count 
            if (m[i][cn] ==n[r] &&n[r]!=0){
              n[r]=0;
              count=count+1;
              //cout<<count<<endl;
          }
        }
      }
      // if count is 9 then the row contains all from 1-9 and return true or return false
      if (count==9){
          return true;
      }
      return false;
  }
  bool checkcol(int** m,int rn,int cn){
        int* n = new int [9];
      int q=1;
      // Initialze an array to compare 1-9
      for (int p=0;p<9;p++){
          n[p]=q;
          q++;
      }
      int count=0;
      // for loop 1 loops through the input array m
      //cout<<"newrow"<<endl;
       for (int i = rn; i < rn+3; i++)
      {
          for (int o = cn; o < cn+3; o++)
      {
           for (int r = 0; r < 9; r++)
        {
            //cout<<m[i][o]<<"  "<<n[r]<<endl;
             if (m[i][o] ==n[r] &&n[r]!=0){
              n[r]=0;
              count=count+1;
              //cout<<count<<endl;
              }}}}
         if (count==9){
          return true;
      }
      return false;
  }