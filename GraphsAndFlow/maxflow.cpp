
/*
//Edmond-Karp Algorithm

maxflow()
{
set f-total = 0
repeat
{
  run bfs() from s to find a flow path to t
  if there is no path from s to t, return;
  let f be the minimum residual capacity value on the path
  increase f-total by f
  for each edge (u,v) on the path
   {
      increase flow f(u,v) by f
      change flow on reverse edge f(v,u)=-f(u,v)
      decrease residual_capacity(u,v) by f
      increase residual_capacity(v,u) by f
   }
}
}
 */

#include <iostream> 
#include <fstream>
#include <vector> 
#include <queue>
#include <list> 
#include <iterator> 
#include <climits>
using namespace std; 


struct Edge
{
  int capacity; //edge capacity
  int residual_capacity; //capacity in residual graph
  int flow; //how much flow is on this edge
};

struct Vertex
{
  bool visited; //has been visited in BFS?
  int path; //previous node on the path; 
  //use path to track the BFS path from s to the sink
};


//run breadth first search to find an augmenting path
void bfs(vector<Vertex> & nodes, vector<vector<Edge> > & adj_matrix, int s, int t)
{
  queue<int> bfs_queue;

  for (int i=0; i< nodes.size(); i++)
    {
      nodes[i].visited = 0;
      nodes[i].path = -1;
    }

  //push the first node (source) to the queue. 
  //every time you push a node in the queue, mark it visited.
  //do not push viisted node in the queue
  nodes[s].visited = 1;
  bfs_queue.push(s);


  //put your program here

  while(bfs_queue.size()){
    int v = bfs_queue.front();
    bfs_queue.pop();
    for(int i = 0; i < adj_matrix.size(); i++){
      if(adj_matrix[v][i].residual_capacity > 0 && nodes[i].visited == 0){
        nodes[i].visited = 1;
        nodes[i].path = v;
        bfs_queue.push(i);
      }
    }
  }
}
// /*
// Returns an int vector which contains the max flow of a path in index 0 and the path itself in reverse order
// afterwards
// */
// vector<int> find_path(vector<Vertex> & nodes, vector<vector<Edge> > & adj_matrix, int s, int t){
//   vector<int> result;
//   result.push_back(INT_MAX);
//   result.push_back(t);
//   int temp = t;
//   while(nodes[temp].path != -1){
//     if(adj_matrix[nodes[temp].path][temp].residual_capacity < result[0]){
//       result[0] = adj_matrix[nodes[temp].path][temp].residual_capacity; 
//     }
//     result.push_back(nodes[temp].path);
//     temp = nodes[temp].path;
//   }
// }
/*
Function finds the minimum residual flow on the path
*/
int find_min_residual(vector<Vertex> & nodes, vector<vector<Edge> > & adj_matrix, int t){
  int minRes = INT_MAX;
  int temp = t;
  while(nodes[temp].path != -1){
    if(adj_matrix[nodes[temp].path][temp].residual_capacity < minRes){
       minRes = adj_matrix[nodes[temp].path][temp].residual_capacity; 
     }
    temp = nodes[temp].path;
  }
  return minRes;
}
//find max-flow by modifying residual_capacity and flow
void max_flow(vector<Vertex> & nodes, vector<vector<Edge> > & adj_matrix, int s, int t)
{
 /*
 set f-total = 0
repeat
{
  run bfs() from s to find a flow path to t
  if there is no path from s to t, return;
  let f be the minimum residual capacity value on the path
  increase f-total by f
  for each edge (u,v) on the path
   {
      increase flow f(u,v) by f
      change flow on reverse edge f(v,u)=-f(u,v)
      decrease residual_capacity(u,v) by f
      increase residual_capacity(v,u) by f
   }
}
 */
  //put your program here
  int totalFlow = 0;
  while(true){
    bfs(nodes, adj_matrix, s, t);
    if(nodes[t].path == -1){
      return;
    }
    int minRes = find_min_residual(nodes, adj_matrix, t);
    totalFlow += minRes;
    int temp = t;
    while(nodes[temp].path != -1){
      adj_matrix[nodes[temp].path][temp].flow += minRes;
      adj_matrix[temp][nodes[temp].path].flow = -1 * adj_matrix[nodes[temp].path][temp].flow;
      adj_matrix[nodes[temp].path][temp].residual_capacity -= minRes;
      adj_matrix[temp][nodes[temp].path].residual_capacity += minRes;
      temp = nodes[temp].path;
   }
  }

}

void show_graph(vector<vector<Edge> > adj_matrix)
{
  cout<<"comes show"<<endl;

  for (int i=0;i<adj_matrix.size();i++)
    {
      for (int j=0; j< adj_matrix.size(); j++)
	{
	  cout<<"["<<i<<","<<j<<"] "<<adj_matrix[i][j].capacity<<" "<<adj_matrix[i][j].residual_capacity<<" "<< adj_matrix[i][j].flow<<endl;
	}

    }
}

// show flow on each edge and show total flow
void show_flow(vector<vector<Edge> > adj_matrix, int s)
{
  cout<<"Flow on each edge:"<<endl;

  for (int i=0;i<adj_matrix.size();i++)
    {
      for (int j=0; j< adj_matrix.size(); j++)
	{
	  if (adj_matrix[i][j].flow > 0) 
	  cout<<"["<<i<<","<<j<<"] "<<adj_matrix[i][j].capacity<<" "<<adj_matrix[i][j].residual_capacity<<" "<< adj_matrix[i][j].flow<<endl;
	}

    }

  int flow=0;
      for (int j=0; j< adj_matrix.size(); j++)
	{
	  if (adj_matrix[s][j].flow > 0) 
	    flow += adj_matrix[s][j].flow;
	}

      cout<<"Total flow is "<<flow<<endl;

}

int main() 
{ 

  ifstream dataFile;
  int NUM_VERTICES, v1, v2, v3;

  dataFile.open("gdata4.txt");

  if (!dataFile.is_open()) return 0;
 
  if (!(dataFile>>NUM_VERTICES)) return 0;

  cout<<NUM_VERTICES<<endl;

  vector<Vertex> nodes(NUM_VERTICES);

  //In this program, we use adjacency matrix to represent the graph
  vector<vector<Edge> > adj_matrix(NUM_VERTICES);


  cout<<"here1"<<endl;

  int source=4, sink=NUM_VERTICES-1;

  for (int i=0;i<NUM_VERTICES;i++)
    {
  cout<<"here2"<<endl;

      adj_matrix[i] = vector<Edge> (NUM_VERTICES);

      for (int j=0; j< NUM_VERTICES; j++)
	{
	  adj_matrix[i][j].capacity=0;
	  adj_matrix[i][j].residual_capacity=0;
	  adj_matrix[i][j].flow=0;
	}

    }

  cout<<"here"<<endl;

  while ((dataFile>>v1) && (dataFile>>v2) && (dataFile>>v3))
    {

      adj_matrix[v1][v2].capacity=v3;
      adj_matrix[v1][v2].residual_capacity=v3;
      adj_matrix[v1][v2].flow=0;
      }

 dataFile.close();


 show_graph(adj_matrix);


 //run maxflow
 max_flow(nodes, adj_matrix, source, sink);

 
 show_flow(adj_matrix, source);

 return 0; 
 
} 
