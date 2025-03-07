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

#include <iostream>
#include <cstdlib>
#include <chrono>
#include <iomanip>
#ifdef _WIN32
#else
#include <sys/resource.h>
#include <sys/time.h>
#endif

using namespace std;

#define NUM_VERTICES 25

//comparator for qsort (compares the weight in element [2])
int comparator(const void* p1, const void* p2) 
{
    float(*x)[3] = (float(*)[3])p1;
    float(*y)[3] = (float(*)[3])p2;
    return ((*x)[2] > (*y)[2]) - ((*x)[2] < (*y)[2]);
}

void makeSet(int parent[], int rank[], int n)
{
    for (int i = 0; i < n; i++) {
        parent[i] = i;
        rank[i] = 0;
    }
}

int findParent(int parent[], int component)
{
    if (parent[component] == component)
        return component;
    return parent[component] = findParent(parent, parent[component]);
}

void unionSet(int u, int v, int parent[], int rank[])
{
    u = findParent(parent, u);
    v = findParent(parent, v);
    if (rank[u] < rank[v])
        parent[u] = v;
    else if (rank[u] > rank[v])
        parent[v] = u;
    else {
        parent[v] = u;
        rank[u]++;
    }
}

float kruskalMST(int vertices, float edges[][3], int numEdges, bool printOutput = true)
{
    qsort(edges, numEdges, sizeof(edges[0]), comparator);
    int parent[vertices];
    int rank[vertices];
    makeSet(parent, rank, vertices);
    float minCost = 0.0;

    if (printOutput) {
        cout << "Edges in the Minimum Spanning Tree (Kruskal):\n";
        cout << "-----------------------------------\n";
        cout << setw(10) << "Vertex 1" 
             << setw(10) << "Vertex 2" 
             << setw(10) << "Weight" << "\n";
        cout << "-----------------------------------\n";
    }
    
    for (int i = 0; i < numEdges; i++) {
        int v1 = findParent(parent, (int)edges[i][0]);
        int v2 = findParent(parent, (int)edges[i][1]);
        float wt = edges[i][2];

        if (v1 != v2) {
            unionSet(v1, v2, parent, rank);
            minCost += wt;
            if (printOutput)
                cout << setw(10) << (int)edges[i][0] 
                     << setw(10) << (int)edges[i][1] 
                     << setw(10) << fixed << setprecision(1) << wt << "\n";
        }
    }
    
    if (printOutput) {
        cout << "-----------------------------------\n";
        cout << "Total Minimum Cost (Kruskal)'s Algo: " 
             << fixed << setprecision(1) << minCost << " km" << "\n";
        cout.flush();
    }
    return minCost;
}

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
    };
    int numEdges = sizeof(edges) / sizeof(edges[0]);

    float initialCost = kruskalMST(NUM_VERTICES, edges, numEdges, true);

    const int iterations = 1000000;  // 1,000,000 iterations
    volatile float dummyCost = 0.0f;  // Prevent optimization.
    auto perfStart = chrono::steady_clock::now();
    for (int i = 0; i < iterations; i++) {
         dummyCost += kruskalMST(NUM_VERTICES, edges, numEdges, false);
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
    //get CPU times using Windows API.
    FILETIME creationTime, exitTime, kernelTime, userTime;
    double userSeconds = 0.0, kernelSeconds = 0.0;
    if (GetProcessTimes(GetCurrentProcess(), &creationTime, &exitTime, &kernelTime, &userTime)) {
         ULARGE_INTEGER uKernel, uUser;
         uKernel.LowPart = kernelTime.dwLowDateTime;
         uKernel.HighPart = kernelTime.dwHighDateTime;
         uUser.LowPart = userTime.dwLowDateTime;
         uUser.HighPart = userTime.dwHighDateTime;
         kernelSeconds = uKernel.QuadPart / 10000000.0;
         userSeconds = uUser.QuadPart / 10000000.0;
         cout << "User CPU time: " << userSeconds << " seconds\n";
         cout << "Kernel CPU time: " << kernelSeconds << " seconds\n";
    } else {
         cout << "GetProcessTimes failed.\n";
    }
    double totalCPU = userSeconds + kernelSeconds;
    //normalize CPU usage by dividing by the number of logical processors
    SYSTEM_INFO sysInfo;
    GetSystemInfo(&sysInfo);
    int numProcessors = sysInfo.dwNumberOfProcessors;
    double normalizedCpuPercent = (totalCPU / totalDuration) * 100.0 / numProcessors;
    cout << "% CPU used by process (normalized to total capacity): " 
         << fixed << setprecision(2) << normalizedCpuPercent << "%" << "\n";

    //load psapi.dll and obtain current memory usage
    HMODULE hPsapi = GetModuleHandleA("psapi.dll");
    if (!hPsapi)
         hPsapi = LoadLibraryA("psapi.dll");
    typedef BOOL (WINAPI *LPFN_GetProcessMemoryInfo)(HANDLE, PPROCESS_MEMORY_COUNTERS, DWORD);
    LPFN_GetProcessMemoryInfo fnGetProcessMemoryInfo =
        (LPFN_GetProcessMemoryInfo)GetProcAddress(hPsapi, "GetProcessMemoryInfo");
    if(fnGetProcessMemoryInfo != NULL) {
         PROCESS_MEMORY_COUNTERS pmc;
         pmc.cb = sizeof(pmc);
         if(fnGetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc))) {
             cout << "Current Memory usage: " << pmc.WorkingSetSize / 1024 << " kilobytes\n";
         } else {
             cout << "Current Memory usage: not available (call failed)\n";
         }
    } else {
         cout << "Current Memory usage: not available (function not loaded)\n";
    }
#else
    //unix-like systems: use getrusage for CPU and memory usage
    struct rusage usage;
    if(getrusage(RUSAGE_SELF, &usage) == 0) {
        cout << "User CPU time: " << usage.ru_utime.tv_sec << "."
             << setfill('0') << setw(6) << usage.ru_utime.tv_usec << " seconds\n";
        cout << "System CPU time: " << usage.ru_stime.tv_sec << "."
             << setfill('0') << setw(6) << usage.ru_stime.tv_usec << " seconds\n";
        double totalCPU = usage.ru_utime.tv_sec + usage.ru_utime.tv_usec/1e6 +
                          usage.ru_stime.tv_sec + usage.ru_stime.tv_usec/1e6;
        double cpuPercent = (totalDuration > 0.0 ? (totalCPU / totalDuration) * 100.0 : 0.0);
        cout << "% CPU used by process: " << fixed << setprecision(2) << cpuPercent << "%" << "\n";
        cout << "Max memory usage: " << usage.ru_maxrss << " kilobytes\n";
    } else {
        perror("getrusage");
    }
#endif
    cout.flush();
    return 0;
}
