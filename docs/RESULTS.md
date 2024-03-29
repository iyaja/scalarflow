# Results

> **TL;DR:** We implemented our initial project goals as documented in `GOALS.md`, as well a few additional things that we didn't have planned when we started. Our compilation is reproduceable on EWS. Towards the end of our project, we realized that the scope of our code was larger than the specific dataset we choose analyze, and refactored our code accodingly to work on general DAGs.

> **Show me the code:** The important stuff is in `src/` and `src/scalarflow/`. Experimental results are summaried at the end of this file.

For our final project, we choose to implement a collection of algorithms based on computational graphs. These are directed acyclic graphs (DAG for short, which is what we'll call them for the remainder of this report) where each node represents a single function/operator/computation and each (directed and unweighted) edge represents the flow of values between nodes.

Computational graphs (DAGs, more generally) are a very useful as a general contruct to represent a variety of important real-world data, such as intermediate representations in compilers, dependancies in a large software packages, or timelines in a product management workflow. More recently, computational graphs form a core component of modern deep learning frameworks.

Details on the build process, file format, and examples can be found on the README. Here, we focus on describing and analyzing our implemented algorithms.

## Code

We strived to make our codebase as clean and simple as possible. Directories are structured using best practices from popular C++ open-source projects, and we use CMake for reproducible builds across platforms.

### Parser

We created a simple lexer using the code generation tool `flex`. `flex` generates a C/C++ scanner/lexer that is far more efficient than anything we could hope to implement in the time available. Note that this is just a lexer and not a actual "parser" parser, so it doesn't throw syntax errors and does not have a specified grammar. We chose this approach because the `.sfg` files are expected to be generated by client-side code generation tools and not hand-written by users, and a "real" parser introduced additional complexity in our codebase.

The `.sfg` files are expected to be formatted with the following loose rules:

1. One node per line.
2. Do not contruct cycles.
3. Do not use undefined nodes as sources for an edge

The general format of each line is:

```
@function %output $input_1 $input_2
```

Examples can be found in the `data/` directory. See `data/simple.sfg` for a simple example.

The parser reads the file in and contructs a `ScalarFlowGraph` object which we use for all algorithms and analysis.


### Graph Implementation

We reused large portions of the `Graph` class from `lab_ml` as a base, and subclasses it to implement specific functionality for our computational graphs. Our `ScalarFlowGraph` class 

An interesting change we made mid-way was to make all functions developer-definable. Instead of having a rigied set of operators like **only** `add`, `sub`, etc. like most assembly languages do, all operators/functions can be defined in a function registry (located at `src/scalarflow/ops.hpp`). We kept the bare minimum in the library -- constants, input, addition, subtraction, multiplication, division, and output. These base operators can also be overwritten and customized.

## Algorithms

We implemented four core algorithms (with minor variants):

1. Traversal - BFS
2. Traversal - DFS
3. Forward Propogation
4. Lazy Evaluation

All of these algorithms are implemented as methods of our `ScalarFlowGraph` class, which can be found at `src/scalaflow/sfg.h` and `src/scalaflow/sfg.cpp`. The specific functions of interest are:

```
map<Vertex, float> forward(Vertex);
map<Vertex, float> forwardAll();
map<Vertex, float> eval(Vertex);
map<Vertex, float> evalAll();
vector<Edge> traverse(Vertex, string);
vector<Edge> traverseAll(string);
```

The base functions have a `Vertex` (our type for a node of the graph) argument that is the entry point for the algorithm. The functions ending in `--All` run the same algorithm across all relavent nodes (this is different for each algorithm but is explained below), thereby covering every node in the graph.

Apart from these, we also implemented functions in our code to generate visualizations and timing statistics.

### Traversal

We decalred our intent to work on depth-first search in our project goals. However, we later realized that breadth-first search and other traversals followed a similar pattern, so we refactored all traversals into a single method - `traverse` that takes a string argument to pick a particular algorithm.

For example, `traverseAll(Vertex v, "BFS")` returns a `vector<Edge>` that contains the edges of the BFS traversal starting a `v`. To switch to DFS, simply use `traverseAll(Vertex v, "DFS")`.

`traverseAll(string method)` takes a string (again, the traversal algorithm option) and runs it on all input nodes, which are special "leaf" nodes that don't have an in-edges.

### Forward Propogation

Forward propogation is an algorithm specific to computational graphs that takes the input for a node, passes the inputs through that node's function/operator, and "propogates" the the resulting value to the nodes that are linked via out-edges.

This method benefits from simplicity: you specify the inputs, and forward propogation generates the outputs.

Our implementation of `forwardAll()` calls the internal forward propogation method on all input nodes. Since the input nodes are the only possible entry points to the computations on an empty graph, this effetively calculates all possible values in the graph in a somewhat efficient way.

We handle the case of a node's dependancies not being at the time it is expected to compute by simply terminating that branch of forward propogation then and there. If a node requires another input value that han't propogated yet, it will cancel it's own propogation with the knowledge that computation can resume when the required input is propogated. This, along with a cache of previously computed values, prevents errors and re-computation.

In the worst case, full forward propogation (i.e. `forwardAll()`)takes `O(n)` time where there are `n` nodes in the graph, since each node propogates forward only once, and every node must propogate forward.

### Lazy Evaluation

An alternate method of computation is lazy evaluation. Instead of specifying a collection of input nodes and propogated their values forward, we can specify a desired output node to "evaluate" the value of, and recursively build a stack of computations to perform. For each node, we request for the values of it's dependacies recursively. When the value of an input node is requested, the stack is collapsed into a single value, which is the output of the specified node.

Lazy evaluation can be much more efficient when computing values for subgraphs. In forward propogation, many values may be computed that are never used. Lazy evaluation, on the other hand, only calculates a value when it is required either directly or indirectly by an output node.

However, lazy evaluation is not always more efficient. There is re-computing that can be avoided by forward propogation when there are distinct output nodes that share similar dependancies. Lazy evaluation recomputes these dependancies for each output nodes, whereas forward propogation uses cached values.

Our implementation of `evalAll()` calls the internal lazy evaluation method on all output nodes, thereby calculating every value in the graph that eventually leads to some output. At "compile-time" (for the graph, not the c++ code we wrote) we build a second graph with edges reversed to model the dependancies between nodes, and traverse this graph at eval time.

### Visualizations

We use graphviz `.dot` files to render our computational graphs as png files. We included special attributes on some nodes to clearly identify input, compute, and output nodes. Furthermore, the rendered graphs are topologically sorted (a node's dependancies will always appear on it's left in the image). However, we did not implement topological sorting ourselves -- this is build into graphviz. 

## Analysis

We analyzed our algorithms on a colection of different types of computational graphs that have different properties to stress-test the different algorithms (specifically forawrd prop vs. lazy eval).

Our datasets contains computational graphs that are either balanced or have an disproportionate number of either inputs, outputs, or computations. The files used for analysis can be found in the `data/` directory. The ones we use here are:

```
data/balanced.sfg
data/input_pressure.sfg
data/output_pressure.sfg
data/compute_pressure.sfg
```

The `balanced` dataset has an equal number of input, compute, and output nodes, and the `--_pressure` datasets have more of the prefix node type.

### Code Generation

We initially thought of analyzing computational graphs of common neural network architecures, since they are a fixed set of computations repeated many times and are well understood. However, most neural networks rely on custom tensor compuations, which would have 

Instead, we opted to create a code generation tool (the `scripts/codegen.py` script) that generated large graphs with our provided specification and randomizes the operators. Our script quickly generates correct (i.e. no cycles and properly defined operators/nodes) computational graphs of arbitrary size.

Code generation was also unplanned initially, but we are excited that we created this simple tool to easily generate scalarflow graph representations of complex computations with a intuitive python API. 

### Experiments

Here, we summarize our experimental results on the graphs mentioned above. We analyzed a few computational graphs with different "presurres" and provide statistics below.

All graphs analyzed had the same number of nodes. The balanced graph has an equal number of all nodes, and the other variants hav 10x that node type as they do other nodes.

Our initial hypothesis was that the graphs with more input nodes would work better with lazy evaluation, and those with many output nodes would compute their values faster with forward propogation. We did not expect BFS or DFS to favor any graph type specifically.

Our results indicate that lazy evaluation is much more efficient than we thought it would be, but this could very well be a result of our specific implementation and the C++ compiler optimizations. 

> Note: we wanted to include the images for the graphs used here, but they are too large. You can find the exact ones used in `docs/images/`

#### Balanced

```
INFO: Registered 1200 nodes.
INFO: output graph saved as images/data/balanced.sfg.png
INFO: completed forward prop in 282ms
INFO: completed lazy eval in 9ms
INFO: DFS visited 2105 edges
INFO: completed depth-first search in 26ms
INFO: BFS visited 2105 edges
INFO: completed breadth-first search in 37ms
```

#### More Input Nodes

```
INFO: Registered 1200 nodes.
INFO: output graph saved as images/data/input_pressure.sfg.png
INFO: completed forward prop in 84ms
INFO: completed lazy eval in 2ms
INFO: DFS visited 327 edges
INFO: completed depth-first search in 13ms
INFO: BFS visited 327 edges
INFO: completed breadth-first search in 19ms
```

#### More Output Nodes

```
INFO: Registered 1199 nodes.
INFO: output graph saved as images/data/output_pressure.sfg.png
INFO: completed forward prop in 283ms
INFO: completed lazy eval in 23ms
INFO: DFS visited 2000 edges
INFO: completed depth-first search in 11ms
INFO: BFS visited 2000 edges
INFO: completed breadth-first search in 14ms
```

#### More Compute Nodes

```
INFO: Registered 1200 nodes.
INFO: output graph saved as images/data/compute_pressure.sfg.png
INFO: completed forward prop in 392ms
INFO: completed lazy eval in 10ms
INFO: DFS visited 11854 edges
INFO: completed depth-first search in 72ms
INFO: BFS visited 11854 edges
INFO: completed breadth-first search in 81ms
```

## Final thoughts

Wow, that was a mouthful! Thanks for reading all the way through. In summary, here's what we did in our project:

1. Created `.sfg` file format specification
2. Implemented `.sfg` parser using `flex`
3. Extended cs225's `Graph` for computational graphs
4. Implemented BFS for either one or all nodes
5. Implemented DFS for either one or all nodes
6. Implented forward propogation for one and all nodes
7. Implented lazy evaluation for either one or all nodes
8. Used graphviz to visualize scalarflow computational graphs
9. Create codegen tool to generate large computational graphs from a few parameters
10.  The other stuff discussed above
11. A whole lotta refactoring and time ~~wasted~~ well-spent trying to get CMake to work

Thank you CS 225 course staff for giving us the opportunity to try something we think is cool in a group for a grade. It really did make this semester more enjoyable.