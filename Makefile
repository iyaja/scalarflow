# Executable names:
EXE = computation graph
TEST = test

# Add all object files needed for compiling:
EXE_OBJ = main.o
OBJS = graph.o main.o 

# Generated files
# CLEAN_RM = path of generated file

# Use the cs225 makefile template:
include cs225/make/cs225.mk
