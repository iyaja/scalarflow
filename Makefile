# Executable names:
EXE = main
TEST = test

# Add all object files needed for compiling:
EXE_OBJ = src/main.o
OBJS = src/scalarflow/graph.o src/scalarflow/edge.o src/main.o

# Incldue scalarflow library directory
CXXFLAGS += -Isrc

# Use the cs225 makefile template:
include make/ews.mk
