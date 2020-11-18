# CS 225 Final Project Goals
The primary goal of our project is to implement a parser for computational graphs. The parser will read a file of a specific format and generate a graph data structure which can then be used for varipus algorithms. This document describes the dataset and algorithms we plan to implement, subject to potential extension if time permits.

## Dataset & File Format

Our dataset will consist of multiple comutational graphs stored in individual files. We may choose to either come up with our own format for saving the graphs in a file or implement a subset of an existing specificcation such as ONNX (open neural network exchange) after further evalutation.

The computations we wish to represent in our graph structure are those that can be modelled as DAGs (directed acyclic graphs). Each node/vertex in the graph will represent a single operator (such add binary add) and the edges will represent numeric values of a specific type (`float64`, `int8`, etc.). Additionally, there will be a set of “leaf nodes” in the graph that represent the input numeric values we pass into the computational graph. The leaf nodes are not treated as operators, despite being called “nodes.”

Our documentation will describe the specific operators and numeric datatypes supported, as well as instructions on how to parse the files and run the algorithms we implement.

## Algorithms

We have selected a number of algorithms we plan to implement on our parsed computational graph data structure. From the following, we plan to implement depth-first search, and two from the forward propogation, traversal/analysis, and optimization sub-categories.


1. **Depth First Search:** We choose to implement depth first search because it will useful for implementing critial path analysis (described in #3).
2. **Forward Propogation:** The graph specifies a collection of computations. Forward propogation would execute these computations to calculate the values of each edge given the values of the leaf nodes.
3. **Traversal/Analysis Algorithm:** The combination of the below algorithms would allow us to produce some interesting analyses on the wall time complexity vs. work complexity of different computational graphs.
    - **Topological Sort:** Return a list of all nodes in order of dependancy. If node `a` requires the output of nide `b`, `a` will appear after `b` in the list.
    - **Critical Path Analysis:** Determine the minimum “time” (or a similar metric like FLOPs) required to complete a computation given maximum possible parallelism. This task requires constructing the maximum-length or critical path through the graph.
4. **Optimization Algorithm:** We will implement some algorithm that transforms the graph into one that performs a similar computation more efficiently. Some ideas we have include:
    - **Common Subexpression Elimination:** A common optimization used in compilers that caches results for computations for later use. For example, in the expression `(a + b) * (a + b)` the value of `(a + b)` only needs to be computed once.
    - **Subgraph Pruning/Approximation:** Certain nodes/subgraphs may represent expensive computations. This optimization would replace (or potentially even remove) these comonents with alternatives that result in minimal changes to. For example, `sin(x)` can be approximated by `x` for small values of `x`.
    - **Dead Node Elimination:** Remove nodes in the graph which do not contribute to the calculation of a particular value.
## Test Cases

Creating test cases for our project should be relatively simple. For each algorithm, we provide an outline of the test cases we plan to implement.


1. **Depth First Search:** Compare generated traversal with manually verified, hard-coded solution for a small, simple graph.
2. **Forward Propogation:** Verify that the computed outputs are correct (compared to manually verified calculations for simple arithmetic expressions).
3. **Traversal/Analysis Algorithm:** Again, a few simple cases could be checked using manually computed traversals.
4. **Optimization Algorithm:** The optimizations would be harder to test, but at the very least we can ensure that the computed values of forward propogation on the optimized graphs are very close to the values on the unoptimized graph.

