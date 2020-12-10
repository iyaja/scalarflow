# Executable names:
EXE = main
TEST = test

# Parser file
PARSER = src/parser.cpp
PARSER_SRC = src/parser.l

# Add all object files needed for compiling:
EXE_OBJ = src/parser.o
OBJS = src/scalarflow/graph.o src/scalarflow/edge.o src/main.o

# Incldue scalarflow library directory
CXXFLAGS += -Isrc

# Extra files to clean
CLEAN_RM += src/parser.cpp src/parser.h

# Use the cs225 makefile template:
include make/ews.mk
