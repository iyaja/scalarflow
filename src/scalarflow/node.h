#include "graph.h"
#include "edge.hpp"

#include <vector>
#include <string>

using namespace std;

class Node {

    private:
        string id;
        string fname;
        vector<Node> inputs;
        vector<Node> outputs;

    public:
        Node(std::string);
        
        void addInputNode(Node);
        void addOutputNode(Node);
        vector<Node> getInputs();
        vector<Node> getOutputs();
        float compute();
};