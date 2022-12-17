/*==================
Your Name: Nicholas Wilson
Your Login ID: nbwilson
==================*/
#include <iostream> 
#include <fstream> 
#include <vector> 
#include <iterator> 
using namespace std; 

void showHeap(vector<int> h)
{
  /*
    vector <int> :: iterator it; 
    for(it = h.begin(); it != h.end(); ++it) 
        cout << '\t' << *it; 
    cout << '\n';
  */

    for(int i=1; i < h.size(); ++i) 
        cout << '\t' << h[i]; 
    cout << '\n';

}
/*
Percolates the node at index index (of the array, so starting at one) down
*/
void heapDown(vector<int> &h, int index){
    while(index * 2 + 1 < h.size()){ //Case: has two children
        if(h[index * 2] < h[index * 2 + 1]){ //Left child is smaller
            if(h[index] < h[index * 2]){
                return;
            }
            int temp = h[index * 2];
            h[index * 2] = h[index];
            h[index] = temp;
            index = index * 2;
        }
        else{ // Right child is smaller
            if(h[index] < h[index * 2 + 1]){
                return;
            }
            int temp = h[index * 2 + 1];
            h[index * 2 + 1] = h[index];
            h[index] = temp;
            index = index * 2 + 1;
        }
    }
    if(index * 2 < h.size() && h[index] > h[index * 2]){ //Case: Left child is last element in heap
        int temp = h[index * 2];
        h[index * 2] = h[index];
        h[index] = temp;
    }
}
/*
Percolates the node at index index (of the array, so starting at one) up
*/
void heapUp(vector<int> &h, int index){
    while(index > 1 && h[index] < h[index / 2]){
        int temp = h[index / 2];
        h[index / 2] = h[index];
        h[index] = temp;
        index = index / 2;
    }
}
void buildHeap1(vector<int> &h1)
{
  //your program here
  for(int i = 1; i < h1.size(); i++){
      heapUp(h1, i);
  }
}

void buildHeap2(vector<int> &h2)
{
  //your program here
  for(int i = (h2.size() - 1) / 2; i >= 1; i--){
      heapDown(h2, i);
  }
}

/*
Removes/returns the root of the min heap and rebuilds the heap
*/
int getMin(vector<int> &h){
    int min = h[1];
    h[1] = h.back();
    h.pop_back();
    heapDown(h, 1);
    return min;
}
/*
Adds a new entry to the heap
*/
void addValue(vector<int> &h, int value){
    h.push_back(value);
    heapUp(h, (h.size() - 1));
}
/*====================================================
Compare the running time of both algorithms in a and b 
for sorted, reverse-ordered, and random inputs. 

For random inputs, b is faster because it runs in O(n) time
worst case rather than O(nlogn) time. 

For sorted inputs (lowest to highest), both are O(n), because every
entered input will be larger than its parents, requiring O(n) additions
to the heap but no heapify operations.

For reverse-ordered inputs, b is against faster because every entry will need
to be heapified (O(nlogn))in a whereas only ~half of the entries will need to be
heapified in b (O(n)). 
====================================================*/

/*for i=k+1 .. n
     If A[i]>A[1], deleteMin, insert(A[i]) to the heap
*/
int findKthLargest(vector<int> &h, int k)
{
  // first build a heap with the first k numbers
    vector<int> kHeap (1, 0);
  //your program here
    for(int i = 1; i <= k; i++){
        addValue(kHeap, h[i]);
    }
  //compare the new number with the top and 
  //decide whether we should insert the new number. 
    for(int i = k + 1; i < h.size(); i++){
        if(h[i] > kHeap[1]){
            getMin(kHeap);
            addValue(kHeap, h[i]);
        }
    }
  //your program here

  return kHeap[1];
}
//i is the index of the node we are looking at in the heap
void findAllLessThanXHelper(vector<int> &h, int x, int i){
    if(x <= h[i]){ //Exclude nodes greater than X
        return;
    }
    cout << '\t' << h[i];
    if(i * 2 >= h.size()){ //No children
        return;
    }
    else if(i * 2 + 1 >= h.size()){ //One child
        findAllLessThanXHelper(h, x, i * 2);
    }
    else{//Two children
        findAllLessThanXHelper(h, x, i * 2);
        findAllLessThanXHelper(h, x, i * 2 + 1);
    }
}
void findAllLessThanX(vector<int> &h, int x)
{
  //your program here
  findAllLessThanXHelper(h, x, 1);
  cout << '\n';
}

int main() 
{ 

  ifstream dataFile;
  vector<int> heap, heap1, heap2;
  int num;

  // READING NUMBERS FROM A FILE
  dataFile.open("data.txt");

      heap.push_back(0);
      heap1.push_back(0);
      heap2.push_back(0);

  if (dataFile.is_open()) 
    while (dataFile>>num)
      {
      heap.push_back(num);
      heap1.push_back(num);
      heap2.push_back(num);
      }
  dataFile.close();

  buildHeap1(heap1);
  showHeap(heap1);

  buildHeap2(heap2);
  showHeap(heap2);

  int k, x;
  cout<<"Please input a number k: ";
  cin>>k;

  cout<<k<<"-th largest number is "<<findKthLargest(heap,k)<<endl;

  cout<<"Please input a number X: ";
  cin>>x;
  findAllLessThanX(heap1, x);

  return 0; 
  
} 