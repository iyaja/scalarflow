# generate strategy
# first, generate all the constants of computation graph

# secondly, generate all the operator vertices of computation graph
# 1. generate 100 random integers set and assign them "label" (may be uuid)
# 2. generate 100 random "add" "mul" "sub" "div" (this is our goal, 100 times computation is a good start)
# 3. pick a arbitrary combination from random integers two operands combination set
# which is generated initially from random integers set (n * (n - 1)/2,
# pick one operand from set and combine with rest of operands)
# 4. generate a uuid (label of operator vertices) and assign to our operator
# 5. arbitrarily pick a operator (from four operators)
# 6. combine with generated uuid in step 4 and all of other existed labels in random integers set,
# and add all the possible combinations to random integers two operands combination set
# 7. add generated uuid in step 4 to random integers set
# 8. execute 100 times from step 3 to step 6


import random
import string
import os.path
from os import path
import uuid 



default_ops = ['add', 'mul', 'sub', 'div'] 

class CodeGen:

    def __init__(self, file, inodes, cnodes, onodes, symlen = 6, ops = default_ops):

        self.file = file
        self.inodes = inodes
        self.onodes = onodes
        self.cnodes = cnodes
        self.ops = ops

        self.symcount = -1
        self.symbols = [uuid.uuid4().hex[:symlen].upper() for i in range(inodes + cnodes + onodes)]
        self.assigned = []

    def genSym(self):
        self.symcount += 1;
        assert(self.symcount <= len(self.symbols))
        self.assigned.append(self.symbols[self.symcount])
        return self.symbols[self.symcount]

    def genConst(self, value):
        self.file.write("@const ")
        self.file.write("%")
        self.file.write(self.genSym() + " ")
        self.file.write(str(value))
        self.file.write("\n")


    def genOp(self, func, arg1, arg2):
        self.file.write("@" + func + " ")
        self.file.write("%" + self.genSym() + " ")
        self.file.write("$" + str(arg1) + " ")
        self.file.write("$" + str(arg2))
        self.file.write("\n")


    def genOut(self, sym):
        self.file.write("@output %" + self.genSym() + " $" + sym)
        self.file.write("\n")
    
    def genRandomGraph(self):
        
        for i in range(self.inodes):
            self.genConst(random.random())
        
        for i in range(self.cnodes):
            op = random.choice(self.ops)
            arg1 = random.choice(self.assigned)
            arg2 = random.choice(self.assigned)
            self.genOp(op, arg1, arg2)
        
        for i in range(self.onodes):
            self.genOut(random.choice(self.assigned))



if __name__ == "__main__":

    balanced = "data/balanced.sfg"
    data = {
        "data/random.sfg" : (10, 10, 10),
        "data/balanced.sfg" : (400, 400, 400),
        "data/input_pressure.sfg" : (1000, 100, 100),
        "data/output_pressure.sfg" : (100, 100, 1000),
        "data/compute_pressure.sfg" : (100, 1000, 100),
    }

    for filename, params in data.items() :
        
        print(f"generating {filename} ...")

        # remove file for regenerating
        if path.exists(filename):
            os.remove(filename)

        f = open(filename, "a")
        cg = CodeGen(f, *params)
        cg.genRandomGraph()
        f.close()