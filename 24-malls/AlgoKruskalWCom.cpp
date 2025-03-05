#include <iostream>
#include <cstdlib>
#include <chrono>
#include <iomanip>  

using namespace std;

#define NUM_VERTICES 25

// comparator function to use in sorting
int comparator(const void* p1, const void* p2) 
{
    // p1 and p2 to float (*)[3] to interpret as pointers to arrays of 3 float values, used to access the edge  weight/cost (km) stored in the third position [2]
    float(*x)[3] = (float(*)[3])p1;
    float(*y)[3] = (float(*)[3])p2;

    // (*x)[2] and (*y)[2] access the weights of the two edges being compared
    /*   
         1 if (*x)[2] (weight of the first edge) is greater than (*y)[2]
        -1 if (*x)[2] is less than (*y)[2]
         0 if the weights are equal
    */
    return ((*x)[2] > (*y)[2]) - ((*x)[2] < (*y)[2]); // compare float values; return 1 / 0 / -1

}

// initialization of parent[] and rank[] arrays
void makeSet(int parent[], int rank[], int n)
{
    for (int i = 0; i < n; i++) 
    {
        parent[i] = i; // each vertex is initially its own parent
        rank[i] = 0;  // initialize rank (used to balance the tree)
    }
}

// function to find the parent of a node
int findParent(int parent[], int component)
{
    if (parent[component] == component)
    {
        return component;
    }

    return parent[component] = findParent(parent, parent[component]);
}

// function to unite two sets
void unionSet(int u, int v, int parent[], int rank[])
{
    u = findParent(parent, u);
    v = findParent(parent, v);

    if (rank[u] < rank[v])
    {
        parent[u] = v;
    }
    else if (rank[u] > rank[v])
    {
        parent[v] = u;
    }
    else
    {
        parent[v] = u;
        rank[u]++;
    }
}

// function to find the MST
void kruskalMST(int vertices, float edges[][3], int numEdges)
{
    qsort(edges, numEdges, sizeof(edges[0]), comparator);

    int parent[vertices];
    int rank[vertices];
    makeSet(parent, rank, vertices);
    float minCost = 0.0;

    cout << "Edges in the Minimum Spanning Tree (Kruskal):\n";
    cout << "-----------------------------------\n";
    cout << setw(10) << "Vertex 1" << setw(10) << "Vertex 2" << setw(10) << "Edge Weight\n";
    cout << "-----------------------------------\n";
    
    for (int i = 0; i < numEdges; i++)
    {
        int v1 = findParent(parent, (int)edges[i][0]);
        int v2 = findParent(parent, (int)edges[i][1]);
        float wt = edges[i][2];

        if (v1 != v2)
        {
            unionSet(v1, v2, parent, rank);
            minCost += wt;
            cout << setw(10) << (int)edges[i][0] << setw(10) << (int)edges[i][1] << setw(10) << fixed << setprecision(1) << wt << "\n";
        }
    }

    cout << "-----------------------------------\n";
    cout << "Total Minimum Cost (Kruskal)'s Algo: " << fixed << setprecision(1) << minCost << " km" << "\n";
}

// driver code
int main()
{
    float edges[][3] = 
    {
        {0, 1, 4.5}, {0, 20, 2.4}, {0, 21, 2.4},
        {1, 2, 5.5}, {1, 3, 10.5}, {1, 20, 2.9}, {1, 21, 2.0}, {1, 22, 2.5},
        {2, 3, 6.0}, {2, 8, 6.2}, {2, 18, 4.6}, {2, 22, 3.5}, {2, 24, 15.7},
        {3, 4, 9.2}, {3, 20, 12.6}, {3, 24, 9.9},
        {4, 5, 2.7}, {4, 19, 25.4}, {4, 24, 5.0},
        {5, 6, 3.5}, {5, 24, 3.1},
        {6, 7, 8.1}, {6, 24, 2.0},
        {7, 8, 7.3}, {7, 10, 8.2}, {7, 11, 9.8}, {7, 24, 7.1},
        {8, 9, 1.9}, {8, 10, 3.8},
        {9, 10, 2.8}, {9, 17, 8.3}, {9, 18, 5.6},
        {10, 11, 3.1}, {10, 17, 8.4},
        {11, 12, 9.5}, {11, 17, 8.3},
        {12, 13, 5.5}, {12, 17, 5.8},
        {13, 14, 3.7}, {13, 15, 5.6}, {13, 17, 9.4},
        {14, 15, 2.1}, {14, 17, 8.8},
        {15, 16, 4.8}, {15, 17, 9.9},
        {16, 17, 7.5}, {16, 18, 9.4}, {16, 19, 9.5},
        {17, 18, 3.2},
        {18, 19, 13.1}, {18, 22, 4.5}, {18, 23, 3.5},
        {19, 20, 4.8},
        {21, 22, 1.5}, {21, 23, 1.8}
    };

    int numEdges = sizeof(edges) / sizeof(edges[0]);

    // start timing
    auto start = chrono::high_resolution_clock::now();

    kruskalMST(NUM_VERTICES, edges, numEdges);

    // end timing
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;

    cout << "\nRuntime: " << fixed << setprecision(6) << duration.count() << " seconds\n";

    return 0;
}
