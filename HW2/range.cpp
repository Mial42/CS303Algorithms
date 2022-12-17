/*
NAME: Nicholas Wilson 
CS Account id: nbwilson
 */

#include <iostream>
#include<fstream>
#include <vector>
using namespace std;

//You only need to change this function.
void query(vector<int> & data)
{
  int i,j;

  //Setup/preparation phase
  int sum = 0;
  int processedArray[data.size()];
  for(int k = 0; k < data.size(); k++){
    sum+=data[k];
    processedArray[k]=sum;
  }
  do {
    cout<<"please input two numbers: "<<endl; 

    cin>>i>>j;
    int result;
    if(i == 0){
      result = processedArray[j];
    }
    else{
      result = processedArray[j] - processedArray[i-1];
    }

    if (i>=0)    
      cout<<"sumRange("<<i<<","<<j<<") is "<<result<<endl;
  } while ((i>=0) && (j>=0));

}

int main()
{
  int num;
  ifstream dataFile;
  vector<int> data;

  // READING NUMBERS FROM A FILE
  dataFile.open("range.txt");

  if (dataFile.is_open()) {
    while (dataFile>>num)
      data.push_back(num);
  }

  dataFile.close();

  //  for (int i=0; i<data.size(); i++)
  //    cout<<"Number "<<i<<" is "<< data[i]<<endl;

  query(data);

  return 0;
}
