#include <iostream>
#include <cstdlib>
#include <chrono>
#include <iomanip>  

using namespace std;

#define NUM_VERTICES 60

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
        {21, 22, 1.5}, {21, 23, 1.8},
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
