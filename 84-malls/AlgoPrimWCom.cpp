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
    cout << "\nMinimum Spanning Tree (MST) Edges and Weights (Prim):\n";
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
    cout << "Total Minimum Cost (Prim)'s Algo: " << totalCost << " km" << "\n";
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
        {9, 24, 14.6},
        {17, 24, 12.2},
        {4, 24, 5.3},
        {19, 24, 2.8},
        {14, 24, 12.0},
        {8, 25, 9.4},
        {10, 25, 11.7},
        {3, 25, 9.0},
        {22, 25, 8.7},
        {4, 26, 9.9},
        {6, 26, 9.1},
        {21, 26, 13.6},
        {18, 26, 10.3},
        {8, 27, 8.4},
        {20, 27, 2.1},
        {2, 27, 7.9},
        {4, 27, 11.1},
        {10, 27, 14.0},
        {8, 28, 2.4},
        {10, 28, 4.5},
        {20, 28, 7.2},
        {9, 28, 2.8},
        {26, 28, 15.0},
        {5, 29, 9.5},
        {19, 29, 3.4},
        {16, 29, 2.2},
        {26, 30, 13.9},
        {24, 30, 6.1},
        {1, 30, 11.4},
        {26, 31, 14.5},
        {16, 31, 7.7},
        {13, 31, 8.2},
        {20, 32, 11.1},
        {19, 32, 13.7},
        {14, 32, 12.3},
        {18, 32, 13.2},
        {8, 32, 12.6},
        {7, 33, 12.6},
        {22, 34, 8.3},
        {15, 35, 7.9},
        {20, 35, 13.9},
        {8, 35, 6.9},
        {33, 35, 14.3},
        {14, 36, 6.5},
        {34, 37, 14.8},
        {36, 37, 3.0},
        {15, 37, 2.5},
        {7, 37, 3.7},
        {29, 38, 7.0},
        {8, 39, 14.2},
        {21, 39, 14.0},
        {15, 39, 13.4},
        {23, 39, 11.9},
        {4, 40, 6.9},
        {34, 40, 3.3},
        {0, 40, 8.9},
        {14, 40, 13.9},
        {6, 41, 11.9},
        {5, 41, 4.8},
        {13, 42, 3.3},
        {8, 43, 7.7},
        {2, 43, 13.6},
        {14, 44, 5.7},
        {16, 45, 14.3},
        {11, 45, 6.5},
        {6, 45, 14.0},
        {10, 45, 3.5},
        {21, 45, 3.2},
        {14, 46, 8.3},
        {7, 46, 5.2},
        {21, 47, 12.4},
        {2, 48, 14.8},
        {15, 48, 4.2},
        {7, 48, 10.0},
        {14, 48, 11.6},
        {32, 49, 2.0},
        {24, 49, 1.8},
        {20, 49, 9.9},
        {1, 50, 10.5},
        {31, 50, 10.9},
        {36, 50, 10.3},
        {28, 50, 11.0},
        {44, 51, 10.0},
        {26, 51, 5.8},
        {21, 51, 2.3},
        {12, 51, 2.4},
        {7, 51, 6.1},
        {16, 52, 11.2},
        {0, 52, 3.7},
        {3, 52, 12.4},
        {34, 52, 14.4},
        {2, 52, 6.5},
        {1, 53, 13.6},
        {37, 53, 3.1},
        {12, 53, 9.5},
        {19, 53, 3.7},
        {18, 54, 10.3},
        {17, 54, 11.0},
        {37, 54, 12.0},
        {24, 55, 2.6},
        {25, 55, 10.2},
        {38, 55, 3.7},
        {45, 55, 6.7},
        {36, 55, 3.7},
        {3, 56, 10.5},
        {1, 56, 14.0},
        {4, 56, 4.4},
        {18, 57, 13.5},
        {20, 58, 10.7},
        {41, 58, 15.0},
        {39, 59, 5.9},
        {10, 59, 13.6},
        {46, 59, 3.2},
        {37, 60, 10.0},
        {17, 60, 3.3},
        {18, 60, 4.0},
        {2, 61, 12.5},
        {11, 61, 12.0},
        {19, 62, 4.0},
        {57, 62, 13.8},
        {39, 62, 2.4},
        {1, 62, 3.9},
        {18, 62, 8.8},
        {23, 63, 2.7},
        {5, 64, 7.4},
        {18, 64, 7.5},
        {60, 64, 14.3},
        {22, 64, 9.7},
        {37, 65, 7.5},
        {18, 65, 11.8},
        {44, 65, 4.7},
        {50, 65, 8.8},
        {55, 66, 14.3},
        {29, 66, 14.1},
        {47, 66, 2.7},
        {56, 66, 12.2},
        {59, 66, 14.9},
        {53, 67, 2.1},
        {29, 67, 2.5},
        {12, 67, 7.1},
        {61, 67, 14.7},
        {14, 67, 5.4},
        {58, 68, 11.7},
        {42, 68, 7.2},
        {50, 68, 8.8},
        {27, 68, 8.3},
        {0, 68, 9.0},
        {35, 69, 10.5},
        {25, 69, 2.0},
        {19, 69, 13.2},
        {46, 69, 1.8},
        {10, 70, 13.2},
        {15, 70, 3.7},
        {28, 70, 1.7},
        {56, 71, 10.3},
        {19, 71, 11.9},
        {67, 71, 5.4},
        {66, 72, 6.2},
        {60, 72, 10.4},
        {68, 72, 2.3},
        {63, 73, 5.6},
        {26, 73, 5.3},
        {45, 73, 12.8},
        {56, 74, 6.5},
        {8, 75, 8.0},
        {74, 76, 10.0},
        {1, 76, 11.1},
        {64, 76, 11.5},
        {35, 76, 2.7},
        {32, 77, 4.6},
        {53, 78, 14.8},
        {32, 78, 10.4},
        {45, 78, 8.0},
        {16, 79, 8.1},
        {6, 79, 6.9},
        {8, 79, 13.7},
        {0, 79, 4.0},
        {5, 79, 6.8},
        {19, 80, 3.4},
        {4, 81, 12.0},
        {21, 81, 8.7},
        {80, 81, 11.3},
        {1, 82, 10.0},
        {15, 82, 9.7},
        {12, 82, 10.3},
        {10, 83, 7.7},
        {63, 83, 11.7},
        {16, 83, 9.4},
        {11, 83, 10.7},
        {81, 83, 9.6},
    };

    // populate the adjacency matrix with the edges and weights
    for (auto& edge : edges) 
    {
        int u = edge[0];
        int v = edge[1];
        double weight = edge[2];
        graph[u][v] = weight;
        graph[v][u] = weight; // since the graph is undirected
    }

    // measure the execution time of primMST function
    auto start = chrono::high_resolution_clock::now();
    primMST(graph);
    auto end = chrono::high_resolution_clock::now();

    // calculate the duration and display it
    chrono::duration<double> duration = end - start;
    cout << "\nRuntime: " << fixed << setprecision(6) << duration.count() << " seconds\n";

    return 0;
}
