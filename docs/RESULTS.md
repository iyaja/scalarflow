# Results

> **TL;DR:** We implemented our initial project goals as documented in `GOALS.md`, as well a few additional things that we didn't have planned when we started. Our compilation is reproduceable and works across many devices and platforms. Towards the end of our project, we realized that the scope of our code was larger than the specific dataset we choose analyze, and refactored our code accodingly to work on general DAGs.

For . These are directed acyclic graphs (DAG for short, which is what we'll call them for the remainder of this report) where each node represents a single function/operator/computation and each (directed and unweighted) edge represents the flow of values between nodes.

Details on the build process, file format, and examples can be found on the README. Here, we focus on describing and analyzing our implemented algorithms.

## Algorithms

We implemented four core algorithms:

1. BFS Traversal
2. DFS Traversal
3. Forward Propogation (Eager)
4. Lazy Evaluation

## Parser
Our graph parser is implemented in ... files. THe parser

## Graph
The graph class declared in graph.h and graph.cpp features a basic graph that could be directed and/or weighted. 

## ScalarFlowGraph
ScalarFlowGraph is a class that inherits from the basic Graph class we had previously made. Unlike the basic graph, ScalarFlowGraph is a computational graph that could compute its internals using forward propagation with forwardAll() or forward(Vertex v), or reverse-mode evaluation with 

## Final thoughts
