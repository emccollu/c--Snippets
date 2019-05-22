#include <iostream>
#include <fstream>
#include<bits/stdc++.h>

using namespace std;

// Function to add an edge in an undirected graph:
void addEdge(vector<int> E[],  int u,  int v) {
    E[u].push_back(v);
    E[v].push_back(u);
}

// Function to print the adjacency list of each node:
void printGraph(vector<int> E[],  int V){
  cout << "Adjacency list of nodes:" << endl;
  for (int v = 0; v < V; ++v){
    cout << "Node " << v+1 << " : " << v;
    for (auto x : E[v])
      cout << "-> " << x;
    cout << endl;
    }
}

int main(){
  string line;
  ifstream infile;
  int verts;
  int i=0, u=0, v=0;
  char k;

  // Input - The input should be read from the file graph.txt
  // Use file redirection for this.
  infile.open("graph.txt");
  getline(infile, line); // Get first line, int n
  verts = stoi(line); //Cvt str to int and store
  vector<int> edge[verts]; //Create vector for adjacency
  cout << "Vertexes: " << verts << endl;

  //Goes threw data in while loop, grabs a line while not at end
  while (!infile.eof()) {
    getline(infile, line);
    //Loops through line, vert*2 times to skip space between numbers
    for (int j=0; j<verts*2; j++){
      //Picks each char of line, calls addEdge function if char == 1
      k = line[j];
      if (k=='1' && u < verts)
        addEdge(edge, u, v);
      //Inc v if char wasn't a space
      if (k=='1' || k=='0')
        v++;
    }
    //Reset v, increment u for next line;
    v=0;
    u++;
  }
  // Print the adjacent nodes for each node of the graph.
  printGraph(edge,  verts);
  return 0;
};

/* Graph

	  v =	 0  1  2  3  4  5  6
	   ---------------------
	0	 |	 0  1  0  0  1  0  0    = (-, -), (0, 1), (-, -), (-, -), (0, 4), (-, -), (-, -)
	1	 |	 1  0  1  0  0  1  0    = (1, 0), (-, -), (1, 2), (-, -), (-, -), (1, 5), (-, -)
	2	 |	 0  1  0  1  0  0  0    = (-, -), (2, 1), (-, -), (2, 3), (-, -), (-, -), (-, -)
	3	 |	 0  0  1  0  1  0  1    = (-, -), (-, -), (3, 2), (-, -), (3, 4), (-, -), (3, 6)
	4	 |	 1  0  0  1  0  1  0    = (4, 0), (-, -), (-, -), (4, 3), (-, -), (4, 5), (-, -)
	5	 | 	 0  1  0  0  1  0  1    = (-, -), (5, 1), (-, -), (-, -), (5, 4), (-, -), (5, 6)
	6	 | 	 0  0  0  1  0  1  0    = (-, -), (-, -), (-, -), (6, 3), (-, -), (6, 5), (-, -),

7 points =

  1 ---- 2 ---- 3
  \       \  /
    \    / \
     /\     \
  /    \     \
4 ----- 5 --- 6
  \         /
   \      /
      7
 */
