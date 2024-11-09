#include <bits/stdc++.h>
#include <chrono>  // for measuring execution time
using namespace std;

#define V 25  

// function to find the vertex with the minimum key value, from the set of vertices not yet included in MST
int minKey(double key[], bool mstSet[]) 
{
    double min = DBL_MAX;
    int min_index;

    for (int v = 0; v < V; v++) 
    {
        if (!mstSet[v] && key[v] < min) 
        {
            min = key[v];
            min_index = v;
        }
    }

    return min_index;
}

// function to print the constructed MST stored in parent[] and calculate the total cost
void printMST(int parent[], double graph[V][V]) 
{
    double totalCost = 0.0;
    cout << "\nMinimum Spanning Tree (MST) Edges and Weights (Prim's Algorithm):\n";
    cout << "-----------------------------------------\n";
    cout << "Vertex 1\tVertex 2\tEdge Weight\n";
    cout << "-----------------------------------------\n";

    for (int i = 1; i < V; i++) 
    {
        cout << setw(8) << parent[i] << "\t" 
             << setw(8) << i << "\t" 
             << setw(12) << graph[i][parent[i]] << "\n";
        totalCost += graph[i][parent[i]];
    }

    cout << "-----------------------------------------\n";
    cout << "Total Minimum Spanning Cost: " << totalCost << "\n";
}

// function to construct and print MST for a graph represented using adjacency matrix representation
void primMST(double graph[V][V]) 
{
    int parent[V];     // array to store constructed MST
    double key[V];     // key values used to pick minimum weight edge
    bool mstSet[V];    // to represent set of vertices included in MST

    for (int i = 0; i < V; i++) 
    {
        key[i] = DBL_MAX;
        mstSet[i] = false;
    }

    key[0] = 0;       // make key 0 so that this vertex is picked as first vertex
    parent[0] = -1;   // first node is always root of MST

    for (int count = 0; count < V - 1; count++) 
    {
        int u = minKey(key, mstSet);
        mstSet[u] = true;
        for (int v = 0; v < V; v++) 
        {
            if (graph[u][v] && !mstSet[v] && graph[u][v] < key[v]) 
            {
                parent[v] = u;
                key[v] = graph[u][v];
            }
        }
    }
    printMST(parent, graph);
}

int main() 
{
    double graph[V][V] = {0};  // initialize the graph with zeroes

    // define the edges with weights
    double edges[][3] = 
    {
        {0, 1, 4.5}, {0, 20, 2.4}, {0, 21, 2.4}, {1, 2, 5.5}, {1, 3, 10.5},
        {1, 20, 2.9}, {1, 21, 2.0}, {1, 22, 2.5}, {2, 3, 6.0}, {2, 8, 6.2},
        {2, 18, 4.6}, {2, 22, 3.5}, {2, 24, 15.7}, {3, 4, 9.2}, {3, 20, 12.6},
        {3, 24, 9.9}, {4, 5, 2.7}, {4, 19, 25.4}, {4, 24, 5.0}, {5, 6, 3.5},
        {5, 24, 3.1}, {6, 7, 8.1}, {6, 24, 2.0}, {7, 8, 7.3}, {7, 10, 8.2},
        {7, 11, 9.8}, {7, 24, 7.1}, {8, 9, 1.9}, {8, 10, 3.8}, {9, 10, 2.8},
        {9, 17, 8.3}, {9, 18, 5.6}, {10, 11, 3.1}, {10, 17, 8.4}, {11, 12, 9.5},
        {11, 17, 8.3}, {12, 13, 5.5}, {12, 17, 5.8}, {13, 14, 3.7}, {13, 15, 5.6},
        {13, 17, 9.4}, {14, 15, 2.1}, {14, 17, 8.8}, {15, 16, 4.8}, {15, 17, 9.9},
        {16, 17, 7.5}, {16, 18, 9.4}, {16, 19, 9.5}, {17, 18, 3.2}, {18, 19, 13.1},
        {18, 22, 4.5}, {18, 23, 3.5}, {19, 20, 4.8}, {21, 22, 1.5}, {21, 23, 1.8},
    };

    // populate the adjacency matrix with the edges and weights
    for (auto& edge : edges) 
    {
        int u = edge[0];
        int v = edge[1];
        double weight = edge[2];
        graph[u][v] = weight;
        graph[v][u] = weight; // Since the graph is undirected
    }

    // measure the execution time of primMST function
    auto start = chrono::high_resolution_clock::now();
    primMST(graph);
    auto end = chrono::high_resolution_clock::now();

    // calculate the duration and display it
    chrono::duration<double> duration = end - start;
    cout << "Execution Time: " << duration.count() << " seconds\n";

    return 0;
}
