

# Advanced algorithms and programming methods - 2 [CM0470]

### Third assignment's report: Einstein's Concurrency

### Group members:

- Bernardi Riccardo     864018
- Buoso Tommaso       864055
- Benetollo Lorenzo    864882

## Table of contents

1. Introduction and general structure
2. The move operator
3. Eval Function
4. Performances
5. Examples

## 1 Introduction and general structure

- description of the library given from the professor
- parsing tree build
- description of the problem
- Tools used, testing library, thread library

This report describes the solution we ha have found of the thrid assignment about the parallelisation of addition, subtraction and contraction on tensors. We started from the solution provided by the professor and we noticed that the library was implemented to build a parsing tree of the Einstein expression given as input. The base class is 

```c++
template<typename T> class einstein_expression<T,dynamic,einstein_proxy>
```
and it takes as a template parameter an expression proxy, that can be another einstein expression in order to perform the basic operations described above, which are the following :

```c++
template<typename T, class E1, class E2> class einstein_expression<T,dynamic,einstein_multiplication<einstein_expression<T,dynamic,E1>,einstein_expression<T,dynamic,E2>>>
template<typename T, class E1, class E2> class einstein_expression<T,dynamic,einstein_binary<einstein_expression<T,dynamic,E1>,einstein_expression<T,dynamic,E2>>>
template<typename T, class E1, class E2> class einstein_expression<T,dynamic,einstein_addition<einstein_expression<T,dynamic,E1>,einstein_expression<T,dynamic,E2>>>
template<typename T, class E1, class E2> class einstein_expression<T,dynamic,einstein_subtraction<einstein_expression<T,dynamic,E1>,einstein_expression<T,dynamic,E2>>>
```

We were asked to trasform the current version of the library into a multithreaded one and avoiding to modify the multiplication operation. After that we were asked to parallelise only on non-repeated indexes of the tensors. 
We solved the problem by the mean of standard threads provided by the c++ standard library. Plus we also used a testing library developed by some students during this course available on github (see the references).

## 2 The move assignment operator

### 2.1 Before

Before our modification the move operator performed sequential operations as we can see below:

```c++
while(!end()) {
    eval() += x.eval();
    next();
    x.next();
}
```
As we can see in the code above, operations are performed iteratively calling the functions eval and next, which respectively write in the new expression and update the base pointer to data.
The eval function actually access data and is used in all of the classes involved in the operations, but slightly differs between them, depending one the mathematical operation to be performed.
Tne next function updates the pointer to data that will be accessed by eval funtion. 
Theese are to core operations we want to perform in parallel, so we need to coordinate multiple access to the base pointer in order to resolve race condition and avoid access to the same location.

Our idea is to create multiple threads, each of them performing the eval funtion over a specific location.
For this purpose we created a new function called teval, specifically designed for thread evaluation, which accepts an index as a parameter and calculates the correct location at which the thread needs to access. 

```c++
T& teval(std::vector<size_t> indxs) const {
    auto ptr = start_ptr;

    for(int i = indxs.size() - 1; i >= 0; --i){
        ptr += indxs[i] * strides[i];
    }

    return *ptr;
}
```
After calling teval, index is updated using by incrementing the current pointer by one.

From our previous experience we know that to parallelise matrix operations you have to split the matrix in N_THREADS parts that are independent and only then launching threads on them. This part of the code in the move was the part of the code that seems to necessitate this kind of improvement since inside it is performed a sum between the resulting tensor and the right-expression of the move operator.

- explain better why threading is here 

### 2.2 After

We added informations to the fields of the tensor to perform the parallelisation such as a matrix that contains N_threads rows and a column for every index that is present in the output tensor.

## 3 Eval Function

### 3.1 Before

### 3.1 After

## 4 Performances

##  5 Examples

## 6 Biblioraphy

https://github.com/riccardobernardi/TestLib