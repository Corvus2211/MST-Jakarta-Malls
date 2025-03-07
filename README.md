# Optimizing MRT Pathways between Jakarta Malls: Comparative Study of Kruskal and Prim Algorithms

This GitHub repository serves as a platform for a research journal exploring the Design and Analysis of Algorithms (DAA), specifically focusing on a comparative study of Prim’s and Kruskal’s algorithms in optimizing MRT pathways in Jakarta. This project is a collaborative effort between a lecturer and undergraduate students from the Informatics Bachelor’s Program at Universitas Pelita Harapan, Lippo Village, Banten, Indonesia.
- Robertus Hudi
- Annabel Kineta Jovinne Caron
- Mikael Silvano
- Bryan Susanto Yo

This research focuses on optimizing the Mass Rapid Transit (MRT) network in Jakarta by creating efficient pathways that link major shopping malls, aiming to enhance transit accessibility and reduce congestion in the city. The study explores the application of Minimum Spanning Tree (MST) algorithms, specifically Kruskal's and Prim's, to design cost-effective transport routes. By analyzing the time and space complexity of these algorithms, the research seeks to understand how they perform under different input conditions, such as the size of the network. Kruskal's algorithm, which operates in O(e log n), is edge-based and selects the smallest available edge regardless of vertex connectivity. Prim's algorithm, on the other hand, operates in O(V²) and is vertex-based, starting from an arbitrary vertex and expanding by selecting the smallest connecting edge from visited vertices. 

The goal is to compare the effectiveness of these algorithms in constructing pathways that minimize construction costs (in kilometers) while maximizing coverage of urban malls. Kruskal's approach, using a union-find data structure or DFS to prevent cycles, is simpler but requires attention to edge selection. Prim's algorithm uses a greedy approach, adding the smallest cost edge to the visited list and continuing from there. By implementing these algorithms in C/C++, the research will provide insights into the performance and efficiency of each in designing optimized MRT routes for Jakarta's in-mall transit system.

## Algorithms;
This repository includes our implementation of the following algorithms:
1. Kruskal's algorithm: https://ieeexplore.ieee.org/document/9077616
2. Prim's algorithm   : https://ieeexplore.ieee.org/document/9077616

## Journal
Link: [bit.ly/DAA-Prim-Kruskal](https://bit.ly/DAA-Prim-Kruskal)
