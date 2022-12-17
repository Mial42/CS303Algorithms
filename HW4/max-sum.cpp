/*
NAME: Nicholas Wilson 
CS Account id: nbwilson
 */

#include <iostream>
#include<fstream>
#include <vector>
#include <climits>
using namespace std;

int maxSub( const vector<int> & a )
{

  int maxSum = 0;
  int tempMax = INT_MIN;
  for(int i: a){
    // cout<<i;
    // cout<<"\n";
    if(i < tempMax + i){
      tempMax += i;
    }
    else{
      tempMax = i;
    }
    if(tempMax > maxSum){
      maxSum = tempMax;
    }
  }
  return maxSum;
}



int main()
{
  int num;
  ifstream dataFile;
  vector<int> data;

  // READING NUMBERS FROM A FILE
  dataFile.open("data.txt");

  if (dataFile.is_open()) {
    while (dataFile>>num)
      data.push_back(num);
  }

  dataFile.close();

  //  for (int i=0; i<data.size(); i++)
  //    cout<<"Number "<<i<<" is "<< data[i]<<endl;


  int result;
  result = maxSub( data );
  cout << "Max sum is " <<  result << endl;

  return 0;
}
