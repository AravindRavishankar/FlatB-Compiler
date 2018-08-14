# FlatB-Compiler

A front-end compiler for a subset of the C language called Flat-B. Specifications of Flat-B are specified in specifications.txt. Flat-B files are represented using ".b" notation. Generated LLVM intermediate representation for the same. Also generated intermediate AST representation for the same. 
Used flex(for tokens), bison(for grammar) and C++ for implementation. The compiler also generates output for the codes written 

How to run ?
Run the makefile present in the src directory on any of the ".b" files to generate the output.
Can also use the files present in test-units for testing.
