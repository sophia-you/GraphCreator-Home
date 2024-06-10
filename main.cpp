#include <iostream>
#include <cstring>
#include <limits.h> // included to be able to use "infinity" aka INT_MAX
using namespace std;

/*
 * Author | Sophia You
 * Date | 06/11/2024
 * Description |  This project, graph creator, is a program that creates
 * and displays graphs as adjacency matrices on the console. Within the 
 * program, the user can call on Dijkstra's algorithm to find the shortest
 * path.
 * Sources: https://pubs.opengroup.org/onlinepubs/009695399/basedefs/limits.h.html
 */

// NOTE: in this context, the terms "node" and "vertex" are interchangeable

void addVertex(int adjacency[][20], char* nodeList[20], char* label, int i);
void print(int adjacency[][20], char* nodeList[20]);
void addEdge(int adjacency[][20], char* nodeList[20], char* origin, char* destination, int weight);
void removeVertex(int adjacency[][20], char* nodeList[20], char* toRemove);
void removeEdge(int adjacency[][20], char* nodeList[20], char* origin, char* destination);
void shortestPath(int adjacency[][20], char* nodeList[20], int distance[20], char* start, char* end, int current);
int main()
{
  cout << "This algorithm allows you to create a graph and use " << endl;
  cout << "Dijkstra's algorithm to construct the shortest path." << endl;
  int max = 20; // maximum number of nodes
  int adjacency[max][20]; // adjacency matrix for the nodes
  char* nodeList[20]; // keep track of node names;
  int numNodes = 0; // keeps track of number of nodes
  bool wantToQuit = false;

  // clear the adjacency matrix by setting every value to -1
  for (int r = 0; r < max - 1; r++) // r = row
    {
      for (int c = 0; c < max - 1; c++) // c = column
	{
	  if (r == c) // if the adjacency is on itself
	    {
	      adjacency[r][c] = 0;
	    }
	  else
	    {
	      adjacency[r][c] = -1;
	    }
	}
    }
  for (int i = 0; i < max - 1; i++) // clear the node list too
    {
      nodeList[i] = NULL;
    }
  while (!wantToQuit)
    {
      cout << "Enter a command (LOWERCASE ONLY!):" << endl;
      cout << "add vertex" << endl;
      cout << "add edge" << endl;
      cout << "remove vertex" << endl;
      cout << "remove edge" << endl;
      cout << "shortest path" << endl;
      cout << "print" << endl;
      cout << "quit" << endl;
      int length = 50;
      char* input = new char[length];
      cin.getline(input, length);
      if (strcmp(input, "add vertex") == 0)
	{
	  char* label = new char[length];
	  cout << "adding vertex" << endl;
	  cout << "Enter a label for your vertex: " << endl;
	  cin.getline(label, length);
	  addVertex(adjacency, nodeList, label, numNodes);
	  numNodes++;
	  print(adjacency, nodeList);
	}
      else if (strcmp(input, "add edge") == 0)
       	{
	  // prompt user for information
       	  cout << "adding edge" << endl;
	  char* origin = new char[length];
	  char* destination = new char[length];
	  int edgeWeight = 0;
	  cout << "Which node is the edge coming from?" << endl;
	  cin.getline(origin, max);
	  cout << "Which node is the edge pointing to?" << endl;
	  cin.getline(destination, max);
	  cout << "What is the weight of this edge?" << endl;
	  cin >> edgeWeight;
	  cin.ignore(max, '\n');
	  cout << "edgeweight: " << edgeWeight << endl;
	  addEdge(adjacency, nodeList, origin, destination, edgeWeight);
	  print(adjacency, nodeList); // visualize the graph
       	}
      else if (strcmp(input, "remove vertex") == 0)
        {
          char* toRemove = new char[length];
	  cout << "Which vertex would you like to remove?" << endl;
	  cin.getline(toRemove, max);
	  removeVertex(adjacency, nodeList, toRemove);
	  print(adjacency, nodeList);
        }
      else if (strcmp(input, "remove edge") == 0)
        {
	  char* origin = new char[max];
	  char* destination = new char[max];
	  cout << "What is the origin of the edge you are removing?" << endl;
	  cin.getline(origin, max);
	  cout << "What is the ending vertex of this edge?" << endl;
	  cin.getline(destination, max);
	  removeEdge(adjacency, nodeList, origin, destination);
	  print(adjacency, nodeList);
        }
      else if (strcmp(input, "shortest path") == 0)
	{
	  char* start = new char[max]; // starting vertex
	  char* end = new char[max]; // ending vertex
	  int distance[max]; // keeps track of the shortest distance between vertices
	  for (int i = 0; i < max - 1; i++)
	    {
	      distance[i] = INT_MAX;
	    }
	  cout << "The shortest path algorithm finds the shortest" << endl;
	  cout << "path from one node to the other. Please specify" << endl;
	  cout << "your starting and ending node." << endl;
	  cout << endl;
	  cout << "Start node: " << endl;
	  cin.getline(start, max);
	  cout << "End node: " << endl;
	  cin.getline(end, max);
	  shortestPath(adjacency, nodeList, distance, start, end, 0);
	}
      else if (strcmp(input, "print") == 0)
	{
	  cout << "printing" << endl;
	  print(adjacency, nodeList);

	}
      else if (strcmp(input, "quit") == 0)
	{
	  wantToQuit = true;
	}
      else
	{
	  cout << "Command not found. Maybe check your spelling?" << endl;
	}
      cout << endl;
    }
  cout << "Bye" << endl;
  
}

/**
 * This function adds a vertex to the graph.
 * @param adjacency is the adjacency matrix
 * @param nodeList is the list that keeps track of all vertices
 * @param label is what the user wants to name the new vertex
 * @param i indicates where this new vertex should be inserted
 */
void addVertex(int adjacency[][20], char* nodeList[20], char* label, int i)
{
  if (i <= 20)
    {
      nodeList[i] = label;
    }
  else
    {
      cout << "Maximum vertex capacity reached. You can only add 20 vertices.";
      cout << endl;
    }
}

/** 
 * This function creates an edge between two vertices on the graph.
 */
void addEdge(int adjacency[][20], char* nodeList[20], char* origin, char* destination, int weight)
{
  int max = 20;
  int a = -1; // index of the origin node
  int b = -1; // index of the destination node
  for (int i = 0; i < max - 1; i++) // locate the indices of each node
    {
      if (nodeList[i] && strcmp(nodeList[i], origin) == 0)
	{
	  a = i;
	}
      else if (nodeList[i] && strcmp(nodeList[i], destination) == 0)
	{
	  b = i;
	}
    }
  if (a != -1 && b != -1)
    {
      adjacency[a][b] = weight;
    }
}

/**
 * This function removes a vertex, and its associated edges, from the graph.
 */
void removeVertex(int adjacency[][20], char* nodeList[20], char* toRemove)
{
  int max = 20;
  int index = -1; // index of the vertex to remove
  for (int i = 0; i < max - 1; i++) // find the index of the vertex to remove
    {
      if (nodeList[i] && strcmp(nodeList[i], toRemove) == 0)
	{
	  index = i;
	}
    }
  if (index != -1)
    {
      // remove all edges!
      for (int i = 0; i < max - i; i++)
	{
	  if (i != index)
	    {
	      adjacency[index][i] = -1;
	      adjacency[i][index] = 0;
	    }
	}
      // remove the vertex itself
      nodeList[index] = NULL;
      delete toRemove;
    }
  else
    {
      cout << "Vertex not found." << endl;
    }
}

/**
 * This function removes the edge between two nodes.
 */
void removeEdge(int adjacency[][20], char* nodeList[20], char* origin, char* destination)
{
  int max = 20;
  int a = -1; // index of the origin node
  int b = -1; // index of the destination node      
  for (int i = 0; i < max - 1; i++) // locate the indices of each node          
    {
      if (nodeList[i] && strcmp(nodeList[i], origin) == 0)
        {
          a = i;
        }
      else if (nodeList[i] && strcmp(nodeList[i], destination) == 0)
        {
          b = i;
        }
    }
  if (a != -1 && b != -1 && a != b)
    {
      adjacency[a][b] = -1;
    }

}

/**
 * This function uses Dijkstra's algorithm to find the shortest path
 * between two nodes.
 */
void shortestPath(int adjacency[][20], char* nodeList[20], int distance[20], char* start, char* end, int current)
{
  int max = 20;
  bool visited[max];
  int a = -1; // index of the start node
  int b = -1; // index of the end node
  for (int i = 0; i < max - 1; i++) // locate the indices of each node
    {
      if (nodeList[i] && strcmp(nodeList[i], start) == 0)
        {
          a = i;
        }
      else if (nodeList[i] && strcmp(nodeList[i], end) == 0)
        {
          b = i;
        }
      visited[i] = false; // no vertices have been visited yet
    }
  distance[a] = 0; // the shortest path from a node to itself is always 0
  // while there are unvisited neighbors
  // if the shortest distance is the current node, go to all the neighbors and update
  // their shortest distances
  // otherwise
  // current node is the node we are working with
  // check for current node's neighbors and find the one with the shortest distance
  // you can check this by going across the row
  // add the current SHORTEST PATH DISTANCE (from a to the current node) to the new distance
  // if this NEW DISTANCE TOTAL is less than the SHORTEST DISTANCE for the new neighbor
  // update the shortest dstance
  // set the previous vertex as current
  // do this for every node, then set current to the neighbor with the smallest distance
  /*
  for (int c = 0; c < max - 1; c++)
    {
      //if (unvisited[c] && adjacency[a][c] != -1) // if an edge to a vertex exists
      //{
	  
      //}
      }*/
}
/**
 * This function prints the adjacency matrix of the graph.
 * @param adjacency is the adjacency matrix
 * @param nodeList is the list that keeps track of all vertices
 */
void print(int adjacency[][20], char* nodeList[20])
{
  cout << endl;
  cout << "Across = destination of edge, down = origin" << endl;
  int max = 20;
  for (int r = 0; r < max - 1; r++)
    {
      // print out the headers
      if (nodeList[r])
	{
	  cout << "\t" << nodeList[r];
	}
    }
  cout << endl;
  for (int r = 0; r < max - 1; r++)
    {
      if (nodeList[r])
	{
	  cout << nodeList[r];
	  for (int c = 0; c < max - 1; c++)
	    {
	      if (nodeList[c] && nodeList[r])
		{
		  cout << "\t" << adjacency[r][c];
		}
	    }
	  cout << endl;
	}
    }
}
