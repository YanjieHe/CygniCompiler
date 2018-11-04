# CygniCompiler

The compiler project is my favorite project. I am very interested in Compiler Principles and Programming Language Design. This project contains a compiler for a statically typed language named Cygni, a bytecode disassembler and a virtual machine.

The compiler is consist of the following steps:

- lexical analysis (I wrote DFA to extract tokens)
- syntax analysis (I wrote a recursive descent parser by hand)
- semantic analysis (I implemented the visitor pattern, which is quite useful in this situation)
- code generation

Besides, I designed a bytecode instruction list, which is similar to the JVM instructions. And also, my implementation of the virtual machine taking JVM as a reference.

I implemented the compiler and the disassembler in C++, and I completed a virtual machine in ANSI C.
