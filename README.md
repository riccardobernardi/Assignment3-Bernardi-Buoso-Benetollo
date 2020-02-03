

# Advanced algorithms and programming methods - 2 [CM0470]

### Third assignment's report: Einstein's Concurrency

### Group members:

- Bernardi Riccardo     864018
- Buoso Tommaso       864055
- Benetollo Lorenzo    864882

## Table of contents

1. Introduction and general structure
2. The move operator
3. The eval operator
4. Performances
5. Examples

## 1 Introduction and general structure

### 1.1 Parsing of the expression

### 1.2 Move concept

### 1.3 Eval concept

## 2 Multithreading Move

### 2.1 Before

Before our modification the move was sequential and the operations that was performed is here below:

-------CODE

The meaning of the code above is that when a move is performed then every operation that is involved has to evaluate itself and then has to move the pointer on the next position until the entire move is performed. The eval and next are overloaded in every expression that inherit from the base class so we put many attention in modifying correctly also them.

We come up with the fact of modifying this part adding multi-threading because from our previous experience we know that to parallelise matrix operations you have to split the matrix in N_THREADS parts that are independent and only then launching threads on them. This part of the code in the move was the part of the code that seems to necessitate this kind of improvement since inside it is performed a sum between the resulting tensor and the right-expression of the move operator.

### 2.2 After



## 3 Threaded-Eval

### 3.1 Before

### 3.1 After

## 4 Performances

##  5 Examples


