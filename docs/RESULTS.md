# Final Results

> **TL;DR:** We implemented what we said we would in our initial project goals document, as well a few additional things that we didn't have planned when we started. Our codebase is compilation is reproduceable and works across many devices and platforms. Towards the end of our project, we realized that the scope of our code was larger than the specific dataset we choose analyze, and refactored our code to work on general DAGs.

As stated in the GOALS, we've created a computational graph that implements a parser to generate them. Additionally, we implemented both BFS and DFS traversals, forward propagation, and reverse-mode evaluation algorithms. 

## Main
As specified in the README file, the main function could be executed with the following command
```
mkdir build
cd build
cmake ../
cmake --build .
```
The user will pass in a file with the ".stg" extension, and the program will parse that file to generate the computational graph. If this was successful, the user could do implement different algorithms ranging from a basic graph's ability to traverse a graph to computing the values from the graph.

## Parser
Our graph parser is implemented in ... files. THe parser

## Graph
The graph class declared in graph.h and graph.cpp features a basic graph that could be directed and/or weighted. 

## ScalarFlowGraph
ScalarFlowGraph is a class that inherits from the basic Graph class we had previously made. Unlike the basic graph, ScalarFlowGraph is a computational graph that could compute its internals using forward propagation with forwardAll() or forward(Vertex v), or reverse-mode evaluation with 

## Final thoughts
