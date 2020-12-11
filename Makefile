# Executable names:
EXE = main
TEST = test

# Parser file
PARSER = src/lexer.cpp
PARSER_SRC = src/lexer.l

# Add all object files needed for compiling:
EXE_OBJ = src/parser.o
OBJS = src/scalarflow/graph.o src/scalarflow/sfg.o src/main.o

# Incldue scalarflow library directory
CXXFLAGS += -Isrc

# Extra files to clean
CLEAN_RM += src/lexer.cpp src/lexer.h

# Use the cs225 makefile template:
include make/ews.mk
