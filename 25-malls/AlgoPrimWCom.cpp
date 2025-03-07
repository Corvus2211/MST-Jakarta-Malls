#ifdef _WIN32
#define _WIN32_WINNT 0x0600
#include <windows.h>
#ifndef PPROCESS_MEMORY_COUNTERS
typedef struct _PROCESS_MEMORY_COUNTERS {
    DWORD cb;
    DWORD PageFaultCount;
    SIZE_T PeakWorkingSetSize;
    SIZE_T WorkingSetSize;
    SIZE_T QuotaPeakPagedPoolUsage;
    SIZE_T QuotaPagedPoolUsage;
    SIZE_T QuotaPeakNonPagedPoolUsage;
    SIZE_T QuotaNonPagedPoolUsage;
    SIZE_T PagefileUsage;
    SIZE_T PeakPagefileUsage;
} PROCESS_MEMORY_COUNTERS, *PPROCESS_MEMORY_COUNTERS;
#endif
#endif

#include <bits/stdc++.h>
#include <chrono>
#include <iomanip>
#ifdef _WIN32
// We'll load GetProcessMemoryInfo dynamically.
#else
#include <sys/resource.h>
#include <sys/time.h>
#endif

using namespace std;

#define V 25  

// Function to find the vertex with the minimum key value not yet included in MST.
int minKey(double key[], bool mstSet[]) 
{
    double minVal = DBL_MAX;
    int min_index = -1;
    for (int v = 0; v < V; v++) {
        if (!mstSet[v] && key[v] < minVal) {
            minVal = key[v];
            min_index = v;
        }
    }
    return min_index;
}

// Modified Prim MST function that returns the computed total cost.
// The printOutput flag controls whether MST details are printed.
double primMSTPerf(double graph[V][V], bool printOutput = true)
{
    int parent[V];
    double key[V];
    bool mstSet[V];
    for (int i = 0; i < V; i++) {
        key[i] = DBL_MAX;
        mstSet[i] = false;
    }
    key[0] = 0;
    parent[0] = -1;
    
    for (int count = 0; count < V - 1; count++) {
        int u = minKey(key, mstSet);
        mstSet[u] = true;
        for (int v = 0; v < V; v++) {
            if (graph[u][v] && !mstSet[v] && graph[u][v] < key[v]) {
                parent[v] = u;
                key[v] = graph[u][v];
            }
        }
    }
    
    double totalCost = 0.0;
    if (printOutput) {
        cout << "\nMinimum Spanning Tree (MST) Edges and Weights (Prim):\n";
        cout << "-----------------------------------------\n";
        cout << "Vertex 1\tVertex 2\t Weight\n";
        cout << "-----------------------------------------\n";
    }
    for (int i = 1; i < V; i++) {
        if (printOutput)
            cout << setw(8) << parent[i] << "\t" 
                 << setw(8) << i << "\t" 
                 << setw(12) << graph[i][parent[i]] << "\n";
        totalCost += graph[i][parent[i]];
    }
    if (printOutput) {
        cout << "-----------------------------------------\n";
        cout << "Total Minimum Cost (Prim)'s Algo: " << totalCost << " km\n";
        cout.flush();
    }
    return totalCost;
}

int main() 
{
    double graph[V][V] = {0};  // Initialize the graph matrix with zeros.

    // Define edges with weights (undirected graph)
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
        {18, 22, 4.5}, {18, 23, 3.5}, {19, 20, 4.8}, {21, 22, 1.5}, {21, 23, 1.8}
    };
    int numEdges = sizeof(edges) / sizeof(edges[0]);

    // Populate the graph matrix from the edge list.
    for (auto &edge : edges) {
        int u = edge[0];
        int v = edge[1];
        double weight = edge[2];
        graph[u][v] = weight;
        graph[v][u] = weight;
    }

    // Run the Prim algorithm once with output to show the MST.
    double initialCost = primMSTPerf(graph, true);

    // To obtain measurable CPU time, run the Prim MST repeatedly.
    const int iterations = 1000000;  // 1,000,000 iterations
    volatile double dummyCost = 0.0;   // Prevent optimization.
    auto perfStart = chrono::steady_clock::now();
    for (int i = 0; i < iterations; i++) {
         dummyCost += primMSTPerf(graph, false);
    }
    auto perfEnd = chrono::steady_clock::now();
    chrono::duration<double> perfDuration = perfEnd - perfStart;
    double totalDuration = perfDuration.count();
    double avgDuration = totalDuration / iterations;
    cout << "\nTotal runtime for " << iterations << " iterations: " 
         << fixed << setprecision(6) << totalDuration << " seconds\n";
    cout << "Average runtime per iteration: " 
         << fixed << setprecision(9) << avgDuration << " seconds\n";
    cout.flush();

#ifdef _WIN32
    // Get CPU times using Windows API.
    FILETIME creationTime, exitTime, kernelTime, userTime;
    double userSeconds = 0.0, kernelSeconds = 0.0;
    if (GetProcessTimes(GetCurrentProcess(), &creationTime, &exitTime, &kernelTime, &userTime))
    {
         ULARGE_INTEGER uKernel, uUser;
         uKernel.LowPart = kernelTime.dwLowDateTime;
         uKernel.HighPart = kernelTime.dwHighDateTime;
         uUser.LowPart = userTime.dwLowDateTime;
         uUser.HighPart = userTime.dwHighDateTime;
         kernelSeconds = uKernel.QuadPart / 10000000.0;
         userSeconds = uUser.QuadPart / 10000000.0;
         cout << "User CPU time: " << userSeconds << " seconds\n";
         cout << "Kernel CPU time: " << kernelSeconds << " seconds\n";
    }
    else
    {
         cout << "GetProcessTimes failed.\n";
    }
    double totalCPU = userSeconds + kernelSeconds;
    double cpuPercent = (totalDuration > 0.0 ? (totalCPU / totalDuration) * 100.0 : 0.0);
    cout << "% CPU used by process: " << fixed << setprecision(2) << cpuPercent << "%" << "\n";

    // Ensure psapi.dll is loaded (try LoadLibrary if necessary)
    HMODULE hPsapi = GetModuleHandleA("psapi.dll");
    if (!hPsapi)
         hPsapi = LoadLibraryA("psapi.dll");
    typedef BOOL (WINAPI *LPFN_GetProcessMemoryInfo)(HANDLE, PPROCESS_MEMORY_COUNTERS, DWORD);
    LPFN_GetProcessMemoryInfo fnGetProcessMemoryInfo =
        (LPFN_GetProcessMemoryInfo)GetProcAddress(hPsapi, "GetProcessMemoryInfo");
    if(fnGetProcessMemoryInfo != NULL)
    {
         PROCESS_MEMORY_COUNTERS pmc;
         pmc.cb = sizeof(pmc);
         if(fnGetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc)))
         {
             cout << "Current Memory usage: " << pmc.WorkingSetSize / 1024 << " kilobytes\n";
         }
         else
         {
             cout << "Current Memory usage: not available (call failed)\n";
         }
    }
    else
    {
         cout << "Current Memory usage: not available (function not loaded)\n";
    }
#else
    // Unix-like systems: use getrusage for CPU times and memory usage.
    struct rusage usage;
    if(getrusage(RUSAGE_SELF, &usage) == 0)
    {
        cout << "User CPU time: " << usage.ru_utime.tv_sec << "."
             << setfill('0') << setw(6) << usage.ru_utime.tv_usec << " seconds\n";
        cout << "System CPU time: " << usage.ru_stime.tv_sec << "."
             << setfill('0') << setw(6) << usage.ru_stime.tv_usec << " seconds\n";
        double totalCPU = usage.ru_utime.tv_sec + usage.ru_utime.tv_usec/1e6 +
                          usage.ru_stime.tv_sec + usage.ru_stime.tv_usec/1e6;
        double cpuPercent = (totalDuration > 0.0 ? (totalCPU / totalDuration) * 100.0 : 0.0);
        cout << "% CPU used by process: " << fixed << setprecision(2) << cpuPercent << "%" << "\n";
        cout << "Max memory usage: " << usage.ru_maxrss << " kilobytes\n";
    }
    else
    {
        perror("getrusage");
    }
#endif
    cout.flush();
    return 0;
}
