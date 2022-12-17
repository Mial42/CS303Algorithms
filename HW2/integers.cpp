/*
NAME: Nicholas Wilson 
CS Account id: nbwilson
 */

/*
To compile:
g++ -std=c++11 integers.cpp -o integers
To run:
./integers
 */


#include <iostream>
#include<fstream>
#include <vector>
using namespace std;

/* return the last number in vector a[]
This function shows you how to access the last number. You do not need to work on it. 
Here "& a" is call-by-reference (see pp. 26 in the textbook). 
When called in main(), the "a" in this function will be the same as "data" in main()
"const" means "a" cannot be changed in this function  */
int lastNum( const vector<int> & a )
{
  return a[a.size()-1];
}

//find the maximal number in vector a[]
int maxNum( const vector<int> & a )
{
  //Put your program here
  int i;
  int max = a[0];
  for(i = 1; i < a.size(); i++){
    if(a[i] > max){
      max = a[i];
    }
  }
  return max;
}

//find the minimal number in vector a[]
int minNum( const vector<int> & a )
{
  
  //Put your program here
  int i;
  int min = a[0];
  for(i = 1; i < a.size(); i++){
    if(a[i] < min){
      min = a[i];
    }
  }
  return min;
  return 0;
}

/*
//find the median number in vector a[]
double medianNum( const vector<int> & a )
{
  
  vector<int> b=a;
  bool swapped = true;

  //Put your program here

  return 0;
}
*/

//find the sum of all the  numbers in vector a[]
int sumNum( const vector<int> & a )
{
  
  //Put your program here
  int i;
  int sum = 0;
  for(i = 0; i < a.size(); i++){
    sum+=a[i];
  }
  return sum;
}



int main() 
{ 
  int num;
  ifstream dataFile;
  vector<int> data;

  // READING NUMBERS FROM A FILE
  dataFile.open("data1.txt"); //open data1.txt 

  if (dataFile.is_open()) { //if the file is open
    // next line read a number from the opened file
    while (dataFile>>num)
      //next line put the number to the vector
      data.push_back(num);
  }

  dataFile.close(); //close data1.txt

  cout<<"Number of integers read from the file is "<<data.size()<<endl;
  cout << "They are: ";
  for (int i=0; i<data.size(); i++)
    cout << data[i] << " ";

  cout << endl;

  cout << "The last number is " << lastNum(data) << endl;
  cout << "The maximal number is " << maxNum(data) << endl;
  cout << "The minimal number is " << minNum(data) << endl;
  //cout << "The median number is " << medianNum(data) << endl;
  cout << "The sum of all the numbers is " << sumNum(data) << endl;

}
