
/*==================
Your Name: Nicholas Wilson
Your Login ID: nbwilson
==================*/

#include <iostream> 
#include<fstream>
#include <vector> 
#include <iterator> 
using namespace std; 


void showData(vector<int> h)
{
  /*
    vector <int> :: iterator it; 
    for(it = h.begin(); it != h.end(); ++it) 
        cout << '\t' << *it; 
    cout << '\n';
  */

    for(int i=0; i < h.size(); ++i) 
        cout <<"  " << h[i]; 
    cout << '\n';

}

//merge d[low,middle] (inclusive) and d[middle+1,high]
void merge(vector<int> &d, int low, int middle, int high)
{
  //Your program here
  vector<int> d1;//(d.begin() + low, d.begin() + middle);
  vector<int> d2;//(d.begin() + middle + 1, d.begin() + high);
  for(int i = low; i <= middle; i++){
    d1.push_back(d[i]);
  }
  for(int i = middle + 1; i <= high; i++){
    d2.push_back(d[i]);
  }
  vector<int> result;
  int lowPtr = 0;
  int highPtr = 0;
  while(lowPtr < d1.size() && highPtr < d2.size()){ //Merge d1 and d2 into result
    if(d1[lowPtr] < d2[highPtr]){
      result.push_back(d1[lowPtr]);
      lowPtr++;
    }
    else{
      result.push_back(d2[highPtr]);
      highPtr++;
    }
  }
  while(lowPtr < d1.size()){ //Copy excess elements of the first sorted array if they exist
    result.push_back(d1[lowPtr]);
    lowPtr++;
  }
  while(highPtr < d2.size()){ //Copy excess elements of the second sorted array if they exist
    result.push_back(d2[highPtr]);
    highPtr++;
  }
  //Copy the sorted elements from result back into d
  for(int i = low; i <= high; i++){
    d[i] = result[i - low];
  }
}

void mergeSort(vector<int> &d, int low, int high)
{
  //Your program here
  if(low < high){ //Base case is low == high
    int center = (low + high) / 2;
    mergeSort(d, low, center);
    mergeSort(d, center + 1, high);
    merge(d, low, center, high);
  }
}
void swap(vector<int> &d, int a, int b){
  int temp = d[a];
  d[a] = d[b];
  d[b] = temp;
}
//partition d[low,high] into (left, pivot, right)
//return the position of the pivot such that all smaller numbers 
// are on the left and all bigger numbers on the right
int partition(vector<int> &d, int low, int high)
{ 
  //Your program here
  int range = high - low;
  int randPartition = rand() % range + low; //Random partition point within the range
  //swap the partition element and the very last element in the array
  swap(d, randPartition, high);
  int i = low;
  int j = high - 1;
  while(i < j){
    if(d[i] > d[high] && d[j] < d[high]){ //Once both i and j are out an out place elem
      //swap them
      swap(d, i, j);
    }
    if(d[i] < d[high]){ //Move i and j to out of place pairs
      i++;
    }
    if(d[j] > d[high]){
      j--;
    }
  }
  while(d[i] < d[high]){
    i++;
  }
  swap(d, i, high);
  return i;
}

void quickSort(vector<int> &d, int low, int high)
{
  //Your program here
  if(low < high){ //Base case is low == high
    int partitionPoint = partition(d, low, high);
    quickSort(d, low, partitionPoint - 1);
    quickSort(d, partitionPoint + 1, high);
  }

}


int main() 
{ 
  ifstream dataFile;
  vector<int> data1, data2;
  int num;

  // READING NUMBERS FROM A FILE
  dataFile.open("data.txt");

  if (dataFile.is_open()) 
    while (dataFile>>num)
      {
      data1.push_back(num);
      data2.push_back(num);
      }
  dataFile.close();

  mergeSort(data1, 0, data1.size()-1);
  showData(data1);

  quickSort(data2, 0, data2.size()-1);
  showData(data2);

  return 0; 
  
} 
