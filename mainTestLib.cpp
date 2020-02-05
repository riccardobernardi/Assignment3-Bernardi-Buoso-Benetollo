#include "TestLib.h"

#include<iostream>
#include"tensor.h"

using namespace Tensor;

int threads = 8;
Tperf a;

std::ostream & operator << (std::ostream& out, Index_Set<>) { return out; }
template<unsigned id, unsigned... ids>
std::ostream & operator << (std::ostream& out, Index_Set<id, ids...>) {
    return out << id << ' ' << Index_Set<ids...>();
}


void test_invert_matrixes_1_thread(){
    tensor<int,rank<2>> t1(2,2), t2(2,2);

    int count=0;
    for(auto iter=t1.begin(); iter!=t1.end(); ++iter)
        *iter = count++;
    for(auto iter=t1.begin(); iter!=t1.end(); ++iter)
        std::cout << *iter << ' ';
    std::cout << '\n';

    auto i=new_index;
    auto j=new_index;

    t2(j,i) = t1(i,j);

    std::cout << "here the result of [t2(j,i) = t1(i,j)];" << std::endl;
    for(auto iter=t2.begin(); iter!=t2.end(); ++iter)
        std::cout << *iter << ' ';
    std::cout << '\n';
}

void test_invert_matrixes_n_threadss(){
    set_thread(threads);
    tensor<int,rank<2>> t1(2,2), t2(2,2);

    int count=0;
    for(auto iter=t1.begin(); iter!=t1.end(); ++iter)
        *iter = count++;
    for(auto iter=t1.begin(); iter!=t1.end(); ++iter)
        std::cout << *iter << ' ';
    std::cout << '\n';

    auto i=new_index;
    auto j=new_index;

    t2(j,i) = t1(i,j);

    std::cout << "here the result of [t2(j,i) = t1(i,j)];" << std::endl;
    for(auto iter=t2.begin(); iter!=t2.end(); ++iter)
        std::cout << *iter << ' ';
    std::cout << '\n';
}

void test_sum_mult_op_1_threads(){
    set_thread();
    tensor<int,rank<2>> t1(2,2);
    tensor<int> t3(2,2,2), t4(2);

    int count=0;
    for(auto iter=t1.begin(); iter!=t1.end(); ++iter)
        *iter = count++;
    count = 0;
    for(auto iter=t3.begin(); iter!=t3.end(); ++iter)
        *iter = count++;


    for(auto iter=t1.begin(); iter!=t1.end(); ++iter)
        std::cout << *iter << ' ';
    std::cout << '\n';

    for(auto iter=t3.begin(); iter!=t3.end(); ++iter)
        std::cout << *iter << ' ';
    std::cout << '\n';

    auto i=new_index;
    auto j=new_index;
    auto k=new_index;

    t4(i) = t3(i,j,k)*t1(j,k)+t3(i,k,k);

    std::cout << "here the result of [t4(i) = t3(i,j,k)*t1(j,k)+t3(i,k,k)];" << std::endl;
    for(auto iter=t4.begin(); iter!=t4.end(); ++iter)
        std::cout << *iter << ' ';
    std::cout << '\n';
}

void test_sum_mult_op_n_threads(){
    set_thread(threads);
    tensor<int,rank<2>> t1(2,2);
    tensor<int> t3(2,2,2), t4(2);

    int count=0;
    for(auto iter=t1.begin(); iter!=t1.end(); ++iter)
        *iter = count++;
    count = 0;
    for(auto iter=t3.begin(); iter!=t3.end(); ++iter)
        *iter = count++;


    for(auto iter=t1.begin(); iter!=t1.end(); ++iter)
        std::cout << *iter << ' ';
    std::cout << '\n';

    for(auto iter=t3.begin(); iter!=t3.end(); ++iter)
        std::cout << *iter << ' ';
    std::cout << '\n';

    auto i=new_index;
    auto j=new_index;
    auto k=new_index;

    t4(i) = t3(i,j,k)*t1(j,k)+t3(i,k,k);

    std::cout << "here the result of [t4(i) = t3(i,j,k)*t1(j,k)+t3(i,k,k)];" << std::endl;
    for(auto iter=t4.begin(); iter!=t4.end(); ++iter)
        std::cout << *iter << ' ';
    std::cout << '\n';
}

void test_subtract_mult_1_thread(){
    set_thread();
    tensor<int,rank<2>> t1(2,2);
    tensor<int> t3(2,2,2,2);
    tensor<int> t4(2,2);

    int count=0;
    for(auto iter=t1.begin(); iter!=t1.end(); ++iter)
        *iter = count++;
    count = 0;
    for(auto iter=t3.begin(); iter!=t3.end(); ++iter)
        *iter = count++;


    for(auto iter=t1.begin(); iter!=t1.end(); ++iter)
        std::cout << *iter << ' ';
    std::cout << '\n';

    for(auto iter=t3.begin(); iter!=t3.end(); ++iter)
        std::cout << *iter << ' ';
    std::cout << '\n';

    auto i=new_index;
    auto j=new_index;
    auto k=new_index;

    t4(i,j) = t1(i,j) - t3(i,j,k,k);

    std::cout << "here the result of [t4(i,j) = t1(i,j) - t3(i,j,k,k)];" << std::endl;
    for(auto iter=t4.begin(); iter!=t4.end(); ++iter)
        std::cout << *iter << ' ';
    std::cout << '\n';
}

void test_subtract_mult_4_thread(){
    set_thread(threads);
    tensor<int,rank<2>> t1(2,2);
    tensor<int> t3(2,2,2,2);
    tensor<int> t4(2,2);

    int count=0;
    for(auto iter=t1.begin(); iter!=t1.end(); ++iter)
        *iter = count++;
    count = 0;
    for(auto iter=t3.begin(); iter!=t3.end(); ++iter)
        *iter = count++;

    for(auto iter=t1.begin(); iter!=t1.end(); ++iter)
        std::cout << *iter << ' ';
    std::cout << '\n';

    for(auto iter=t3.begin(); iter!=t3.end(); ++iter)
        std::cout << *iter << ' ';
    std::cout << '\n';

    auto i=new_index;
    auto j=new_index;
    auto k=new_index;

    t4(i,j) = t1(i,j) - t3(i,j,k,k);

    std::cout << "here the result of [t4(i,j) = t1(i,j) - t3(i,j,k,k)];" << std::endl;
    for(auto iter=t4.begin(); iter!=t4.end(); ++iter)
        std::cout << *iter << ' ';
    std::cout << '\n';
}

void test_sum_2244_2442_1_thread(){
    set_thread();
    tensor<int> t1(2,2), t3(2,2,4,4), t4(2,4,4,2);

    int count=0;
    for(auto iter= t3.begin(); iter!=t3.end(); ++iter)
        *iter = count++;
    count = 0;
    for(auto iter= t4.begin(); iter!=t4.end(); ++iter)
        *iter = count++;

    auto i=new_index;
    auto j=new_index;
    auto k=new_index;

    t1(i,j) = t3(i,j,k,k)+t4(i,k,k,j);

    std::cout << "here the result of [t1(i,j) = t3(i,j,k,k)+t4(i,k,k,j)];" << std::endl;
    for(auto iter=t4.begin(); iter!=t4.end(); ++iter)
        std::cout << *iter << ' ';
    std::cout << '\n';
}

void test_sum_2244_2442_n_threads(){
    set_thread(threads);
    tensor<int> t1(2,2), t3(2,2,4,4), t4(2,4,4,2);

    int count=0;
    for(auto iter=t3.begin(); iter!=t3.end(); ++iter)
        *iter = count++;
    count = 0;
    for(auto iter=t4.begin(); iter!=t4.end(); ++iter)
        *iter = count++;

    auto i=new_index;
    auto j=new_index;
    auto k=new_index;

    t1(i,j) = t3(i,j,k,k)+t4(i,k,k,j);

    std::cout << "here the result of [t1(i,j) = t3(i,j,k,k)+t4(i,k,k,j)];" << std::endl;
    for(auto iter=t4.begin(); iter!=t4.end(); ++iter)
        std::cout << *iter << ' ';
    std::cout << '\n';
}

void test_invert_indexes_mult_1_thread(){
    set_thread();
    tensor<int,rank<2>> t1(2,2), t2(2,2);

    int count = 0;
    for(auto iter=t1.begin(); iter!=t1.end(); ++iter)
        *iter = count++;

    auto i=new_index;
    auto j=new_index;
    auto k=new_index;

    t2(i,j) = t1(i,k)*t1(k,j);

    std::cout << "here the result of [t2(i,j) = t1(i,k)*t1(k,j)];" << std::endl;
    for(auto iter=t2.begin(); iter!=t2.end(); ++iter)
        std::cout << *iter << ' ';
    std::cout << '\n';
}

void test_invert_indexes_mult_n_threads(){
    set_thread(threads);
    tensor<int,rank<2>> t1(2,2), t2(2,2);

    int count = 0;
    for(auto iter=t1.begin(); iter!=t1.end(); ++iter)
        *iter = count++;

    auto i=new_index;
    auto j=new_index;
    auto k=new_index;

    t2(i,j) = t1(i,k)*t1(k,j);

    std::cout << "here the result of [t2(i,j) = t1(i,k)*t1(k,j)];" << std::endl;
    for(auto iter=t2.begin(); iter!=t2.end(); ++iter)
        std::cout << *iter << ' ';
    std::cout << '\n';
}

void test_mult_all_ranked_1_thread(){
    set_thread();
    tensor<int,rank<2>> t2(2,2);
    tensor<int,rank<3>> t3(2,2,2);
    tensor<int,rank<1>> t4(2);

    int count=0;
    for(auto iter=t3.begin(); iter!=t3.end(); ++iter)
        *iter = count++;
    count = 0;
    for(auto iter=t4.begin(); iter!=t4.end(); ++iter)
        *iter = count++;

    auto i=new_index;
    auto j=new_index;
    auto k=new_index;

    t2(i,k) = t3(i,j,j)*t4(k);

    std::cout << "here the result of [t2(i,k) = t3(i,j,j)*t4(k)];" << std::endl;
    for(auto iter=t2.begin(); iter!=t2.end(); ++iter)
        std::cout << *iter << ' ';
    std::cout << '\n';
}

void test_mult_all_ranked_n_threads(){
    set_thread(threads);
    tensor<int,rank<2>> t2(2,2);
    tensor<int,rank<3>> t3(2,2,2);
    tensor<int,rank<1>> t4(2);

    int count=0;
    for(auto iter=t3.begin(); iter!=t3.end(); ++iter)
        *iter = count++;
    count = 0;
    for(auto iter=t4.begin(); iter!=t4.end(); ++iter)
        *iter = count++;

    auto i=new_index;
    auto j=new_index;
    auto k=new_index;

    t2(i,k) = t3(i,j,j)*t4(k);

    std::cout << "here the result of [t2(i,k) = t3(i,j,j)*t4(k)];" << std::endl;
    for(auto iter=t2.begin(); iter!=t2.end(); ++iter)
        std::cout << *iter << ' ';
    std::cout << '\n';
}

void test_simple_assignment_1_thread(){
    set_thread();
    tensor<int,rank<2>> t1(2,2);
    tensor<int> t5(2,2); // if it was tensor<int,rank<2>> it was wrong, why? // because it have to be assigned in that moment

    for(auto iter=t1.begin(); iter!=t1.end(); ++iter)
        *iter = 1;

    auto i=new_index;
    auto j=new_index;

    t5 = t1(i,j);
    std::cout << "here the result of [t5=t1(i,j)];" << std::endl;
    for(auto iter=t5.begin(); iter!=t5.end(); ++iter)
        std::cout << *iter << ' ';
    std::cout << '\n';
}

void test_simple_assignment_n_threads(){
    set_thread(threads);
    tensor<int,rank<2>> t1(2,2), t2(2,2);
    tensor<int> t5(2,2); // if it was tensor<int,rank<2>> it was wrong, why? // because it have to be assigned in that moment

    for(auto iter=t1.begin(); iter!=t1.end(); ++iter)
        *iter = 1;

    auto i=new_index;
    auto j=new_index;

    t5 = t1(i,j);
    std::cout << "here the result of [t5=t1(i,j)];" << std::endl;
    for(auto iter=t5.begin(); iter!=t5.end(); ++iter)
        std::cout << *iter << ' ';
    std::cout << '\n';
}

void test_simple_mult_222_2_1_thread(){
    set_thread();
    tensor<int> t3(2,2,2), t4(2);

    int count=0;
    for(auto iter=t3.begin(); iter!=t3.end(); ++iter)
        *iter = count++;
    count=0;
    for(auto iter=t4.begin(); iter!=t4.end(); ++iter)
        *iter = count++;

    auto i=new_index;
    auto j=new_index;
    auto k=new_index;

    tensor<int,rank<2>> t6=t3(i,j,k)*t4(j);
    std::cout << "here the result of [t6=t3(i,j,k)*t4(j)];" << std::endl;
    for(auto iter=t6.begin(); iter!=t6.end(); ++iter)
        std::cout << *iter << ' ';
    std::cout << '\n';
}

void test_simple_mult_222_2_n_threads(){
    set_thread(threads);
    tensor<int> t3(2,2,2), t4(2);

    int count=0;
    for(auto iter=t3.begin(); iter!=t3.end(); ++iter)
        *iter = count++;
    count=0;
    for(auto iter=t4.begin(); iter!=t4.end(); ++iter)
        *iter = count++;

    auto i=new_index;
    auto j=new_index;
    auto k=new_index;

    tensor<int,rank<2>> t6=t3(i,j,k)*t4(j);
    std::cout << "here the result of [t6=t3(i,j,k)*t4(j)];" << std::endl;
    for(auto iter=t6.begin(); iter!=t6.end(); ++iter)
        std::cout << *iter << ' ';
    std::cout << '\n';
}

void test_very_long_mult_1_thread(){
    set_thread();
    tensor<int,rank<2>> t1(2,2), t2(2,2);
    tensor<int> t6(2);

    int count = 0;
    for(auto iter=t1.begin(); iter!=t1.end(); ++iter)
        *iter = count++;
    count = 0;
    for(auto iter=t2.begin(); iter!=t2.end(); ++iter)
        *iter = count++;

    auto i=new_index;
    auto j=new_index;
    auto k=new_index;

    t6(k)=t1(k,j)*t1(i,i)*t2(j,j)*t2(j,j)*t1(i,i)*t2(j,j)*t2(j,j)*t1(i,i)*t2(j,j)*t2(j,j)*t1(i,i);
    std::cout << "here the result of [t6(k)=t1(k,j)*t1(i,i)*t2(j,j)*t2(j,j)*t1(i,i)*t2(j,j)*t2(j,j)*t1(i,i)*t2(j,j)*t2(j,j)*t1(i,i)];" << std::endl;
    for(auto iter=t6.begin(); iter!=t6.end(); ++iter)
        std::cout << *iter << ' ';
    std::cout << '\n';
}

void test_very_long_mult_n_thread(){
    set_thread(threads);
    tensor<int,rank<2>> t1(2,2), t2(2,2);
    tensor<int> t6(2);

    int count = 0;
    for(auto iter=t1.begin(); iter!=t1.end(); ++iter)
        *iter = count++;
    count = 0;
    for(auto iter=t2.begin(); iter!=t2.end(); ++iter)
        *iter = count++;

    auto i=new_index;
    auto j=new_index;
    auto k=new_index;

    t6(k)=t1(k,j)*t1(i,i)*t2(j,j)*t2(j,j)*t1(i,i)*t2(j,j)*t2(j,j)*t1(i,i)*t2(j,j)*t2(j,j)*t1(i,i);
    std::cout << "here the result of [t6(k)=t1(k,j)*t1(i,i)*t2(j,j)*t2(j,j)*t1(i,i)*t2(j,j)*t2(j,j)*t1(i,i)*t2(j,j)*t2(j,j)*t1(i,i)];" << std::endl;
    for(auto iter=t6.begin(); iter!=t6.end(); ++iter)
        std::cout << *iter << ' ';
    std::cout << '\n';
}

void test_very_long_mult_1_thread_second_try(){
    set_thread();
    tensor<int,rank<2>> t1(2,2), t2(2,2);
    tensor<int> t6(2);

    for(auto iter=t1.begin(); iter!=t1.end(); ++iter)
        *iter = 1;
    for(auto iter=t2.begin(); iter!=t2.end(); ++iter)
        *iter = 1;

    auto i=new_index;
    auto j=new_index;
    auto k=new_index;

    t6(k)=t1(k,j)*t1(i,i)*t2(j,j)*t2(j,j)*t1(i,i)*t2(j,j)*t2(j,j)*t1(i,i)*t2(j,j)*t2(j,j)*t1(i,i)*t1(i,i)*t2(j,j)*t1(i,i)*t2(j,j)*t2(j,j)*t1(i,i)*t1(i,i)*t2(j,j)*t2(j,j)*t1(i,i)*t2(j,j)*t2(j,j)*t1(i,i);
    std::cout << "here the result of [t6(k)=t1(k,j)*t1(i,i)*t2(j,j)*t2(j,j)*t1(i,i)*t2(j,j)*t2(j,j)*t1(i,i)*t2(j,j)*t2(j,j)*t1(i,i)*t1(i,i)*t2(j,j)*t1(i,i)*t2(j,j)*t2(j,j)*t1(i,i)*t1(i,i)*t2(j,j)*t2(j,j)*t1(i,i)*t2(j,j)*t2(j,j)*t1(i,i)];" << std::endl;

    std::cout << "here the result;" << std::endl;
    for(auto iter=t6.begin(); iter!=t6.end(); ++iter)
        std::cout << *iter << ' ';
    std::cout << '\n';
}

void test_very_long_mult_n_thread_second_try(){
    set_thread(threads);
    tensor<int,rank<2>> t1(2,2), t2(2,2);
    tensor<int> t6(2);

    for(auto iter=t1.begin(); iter!=t1.end(); ++iter)
        *iter = 1;
    for(auto iter=t2.begin(); iter!=t2.end(); ++iter)
        *iter = 1;

    auto i=new_index;
    auto j=new_index;
    auto k=new_index;

    t6(k)=t1(k,j)*t1(i,i)*t2(j,j)*t2(j,j)*t1(i,i)*t2(j,j)*t2(j,j)*t1(i,i)*t2(j,j)*t2(j,j)*t1(i,i)*t1(i,i)*t2(j,j)*t1(i,i)*t2(j,j)*t2(j,j)*t1(i,i)*t1(i,i)*t2(j,j)*t2(j,j)*t1(i,i)*t2(j,j)*t2(j,j)*t1(i,i);
    std::cout << "here the result of [t6(k)=t1(k,j)*t1(i,i)*t2(j,j)*t2(j,j)*t1(i,i)*t2(j,j)*t2(j,j)*t1(i,i)*t2(j,j)*t2(j,j)*t1(i,i)*t1(i,i)*t2(j,j)*t1(i,i)*t2(j,j)*t2(j,j)*t1(i,i)*t1(i,i)*t2(j,j)*t2(j,j)*t1(i,i)*t2(j,j)*t2(j,j)*t1(i,i)];" << std::endl;

    std::cout << "here the result;" << std::endl;
    for(auto iter=t6.begin(); iter!=t6.end(); ++iter)
        std::cout << *iter << ' ';
    std::cout << '\n';
}

void test_very_long_mult_1_thread_third_try(){
    set_thread();
    tensor<int,rank<2>> t1(2,2), t2(2,2);
    tensor<int> t6(2);

    for(auto iter=t1.begin(); iter!=t1.end(); ++iter)
        *iter = 1;
    for(auto iter=t2.begin(); iter!=t2.end(); ++iter)
        *iter = 1;

    auto i=new_index;
    auto j=new_index;
    auto k=new_index;

    t6(k)=t1(k,j)*t1(i,i)*t2(j,j)*t2(j,j)*t1(i,i)*t2(j,j)*t2(j,j)*t1(i,i)*t2(j,j)*t2(j,j)*t1(i,i)*t1(i,i)*t2(j,j)*t1(i,i)*t2(j,j)*t2(j,j)*t1(i,i)*t1(i,i)*t2(j,j)*t2(j,j)*t1(i,i)*t2(j,j)*t2(j,j)*t1(i,i)+t1(k,j)*t1(i,i)*t2(j,j)*t2(j,j)*t1(i,i)*t2(j,j)*t2(j,j)*t1(i,i)*t2(j,j)*t2(j,j)*t1(i,i)*t1(i,i)*t2(j,j)*t1(i,i)*t2(j,j)*t2(j,j)*t1(i,i)*t1(i,i)*t2(j,j)*t2(j,j)*t1(i,i)*t2(j,j)*t2(j,j)*t1(i,i);
    std::cout << "here the result of [t6(k)=t1(k,j)*t1(i,i)*t2(j,j)*t2(j,j)*t1(i,i)*t2(j,j)*t2(j,j)*t1(i,i)*t2(j,j)*t2(j,j)*t1(i,i)*t1(i,i)*t2(j,j)*t1(i,i)*t2(j,j)*t2(j,j)*t1(i,i)*t1(i,i)*t2(j,j)*t2(j,j)*t1(i,i)*t2(j,j)*t2(j,j)*t1(i,i)+t1(k,j)*t1(i,i)*t2(j,j)*t2(j,j)*t1(i,i)*t2(j,j)*t2(j,j)*t1(i,i)*t2(j,j)*t2(j,j)*t1(i,i)*t1(i,i)*t2(j,j)*t1(i,i)*t2(j,j)*t2(j,j)*t1(i,i)*t1(i,i)*t2(j,j)*t2(j,j)*t1(i,i)*t2(j,j)*t2(j,j)*t1(i,i)];" << std::endl;
    for(auto iter=t6.begin(); iter!=t6.end(); ++iter)
        std::cout << *iter << ' ';
    std::cout << '\n';
}

void test_very_long_mult_n_thread_third_try(){
    set_thread(threads);
    tensor<int,rank<2>> t1(2,2), t2(2,2);
    tensor<int> t6(2);

    for(auto iter=t1.begin(); iter!=t1.end(); ++iter)
        *iter = 1;
    for(auto iter=t2.begin(); iter!=t2.end(); ++iter)
        *iter = 1;

    auto i=new_index;
    auto j=new_index;
    auto k=new_index;

    t6(k)=t1(k,j)*t1(i,i)*t2(j,j)*t2(j,j)*t1(i,i)*t2(j,j)*t2(j,j)*t1(i,i)*t2(j,j)*t2(j,j)*t1(i,i)*t1(i,i)*t2(j,j)*t1(i,i)*t2(j,j)*t2(j,j)*t1(i,i)*t1(i,i)*t2(j,j)*t2(j,j)*t1(i,i)*t2(j,j)*t2(j,j)*t1(i,i)+t1(k,j)*t1(i,i)*t2(j,j)*t2(j,j)*t1(i,i)*t2(j,j)*t2(j,j)*t1(i,i)*t2(j,j)*t2(j,j)*t1(i,i)*t1(i,i)*t2(j,j)*t1(i,i)*t2(j,j)*t2(j,j)*t1(i,i)*t1(i,i)*t2(j,j)*t2(j,j)*t1(i,i)*t2(j,j)*t2(j,j)*t1(i,i);
    std::cout << "here the result of [t6(k)=t1(k,j)*t1(i,i)*t2(j,j)*t2(j,j)*t1(i,i)*t2(j,j)*t2(j,j)*t1(i,i)*t2(j,j)*t2(j,j)*t1(i,i)*t1(i,i)*t2(j,j)*t1(i,i)*t2(j,j)*t2(j,j)*t1(i,i)*t1(i,i)*t2(j,j)*t2(j,j)*t1(i,i)*t2(j,j)*t2(j,j)*t1(i,i)+t1(k,j)*t1(i,i)*t2(j,j)*t2(j,j)*t1(i,i)*t2(j,j)*t2(j,j)*t1(i,i)*t2(j,j)*t2(j,j)*t1(i,i)*t1(i,i)*t2(j,j)*t1(i,i)*t2(j,j)*t2(j,j)*t1(i,i)*t1(i,i)*t2(j,j)*t2(j,j)*t1(i,i)*t2(j,j)*t2(j,j)*t1(i,i)];" << std::endl;
    for(auto iter=t6.begin(); iter!=t6.end(); ++iter)
        std::cout << *iter << ' ';
    std::cout << '\n';
}

void test_mega_sum_1_threads_second_try(){
    set_thread();
    tensor<int,rank<5>> t1(2,2,8,200,100);
    tensor<int,rank<4>> t3(2,2,8,9);

    for(auto iter=t1.begin(); iter!=t1.end(); ++iter)
        *iter = 1;
    for(auto iter=t3.begin(); iter!=t3.end(); ++iter)
        *iter = 1;

    auto i=new_index;
    auto j=new_index;
    auto k=new_index;

    a.tic();
    tensor<int> t4 = t3(i,j,k,k)
                     +t1(i,j,k,k,k)
                     +t3(i,j,k,k)
                     +t1(i,j,k,k,k)
                     +t3(i,j,k,k)
                     +t1(i,j,k,k,k)
                     +t3(i,j,k,k)
                     +t1(i,j,k,k,k)
                     +t3(i,j,k,k)
                     +t1(i,j,k,k,k)
                     +t3(i,j,k,k)
                     +t1(i,j,k,k,k)
                     +t3(i,j,k,k)
                     +t1(i,j,k,k,k)
                     +t3(i,j,k,k)
                     +t1(i,j,k,k,k)
                     +t1(i,j,k,k,k)
                     +t3(i,j,k,k)
                     +t3(i,j,k,k)
                     +t1(i,j,k,k,k)
                     +t3(i,j,k,k)
                     +t1(i,j,k,k,k)
                     +t3(i,j,k,k)
                     +t1(i,j,k,k,k)
                     +t3(i,j,k,k)
                     +t1(i,j,k,k,k)
                     +t3(i,j,k,k)
                     +t1(i,j,k,k,k)
                     +t3(i,j,k,k)
                     +t1(i,j,k,k,k)
                     +t3(i,j,k,k)
                     +t1(i,j,k,k,k)
                     +t3(i,j,k,k)
                     +t1(i,j,k,k,k)
                     +t3(i,j,k,k)
                     +t1(i,j,k,k,k)
                     +t1(i,j,k,k,k)
                     +t3(i,j,k,k)
                     +t3(i,j,k,k)
                     +t1(i,j,k,k,k)
                     +t3(i,j,k,k)
                     +t1(i,j,k,k,k)
                     +t3(i,j,k,k)
                     +t1(i,j,k,k,k)
                     +t3(i,j,k,k)
                     +t1(i,j,k,k,k)
                     +t3(i,j,k,k)
                     +t1(i,j,k,k,k)
                     +t3(i,j,k,k)
                     +t1(i,j,k,k,k)
                     +t3(i,j,k,k)
                     +t1(i,j,k,k,k)
                     +t3(i,j,k,k)
                     +t1(i,j,k,k,k)
                     +t3(i,j,k,k)
                     +t1(i,j,k,k,k);
    a.toc();
}

void test_mega_sum_n_threads_second_try(){
    set_thread(threads);
    tensor<int,rank<5>> t1(2,2,8,200,100);
    tensor<int,rank<4>> t3(2,2,8,9);

    for(auto iter=t1.begin(); iter!=t1.end(); ++iter)
        *iter = 1;
    for(auto iter=t3.begin(); iter!=t3.end(); ++iter)
        *iter = 1;

    auto i=new_index;
    auto j=new_index;
    auto k=new_index;

    a.tic();
    tensor<int> t4 = t3(i,j,k,k)
                     +t1(i,j,k,k,k)
                     +t3(i,j,k,k)
                     +t1(i,j,k,k,k)
                     +t3(i,j,k,k)
                     +t1(i,j,k,k,k)
                     +t3(i,j,k,k)
                     +t1(i,j,k,k,k)
                     +t3(i,j,k,k)
                     +t1(i,j,k,k,k)
                     +t3(i,j,k,k)
                     +t1(i,j,k,k,k)
                     +t3(i,j,k,k)
                     +t1(i,j,k,k,k)
                     +t3(i,j,k,k)
                     +t1(i,j,k,k,k)
                     +t1(i,j,k,k,k)
                     +t3(i,j,k,k)
                     +t3(i,j,k,k)
                     +t1(i,j,k,k,k)
                     +t3(i,j,k,k)
                     +t1(i,j,k,k,k)
                     +t3(i,j,k,k)
                     +t1(i,j,k,k,k)
                     +t3(i,j,k,k)
                     +t1(i,j,k,k,k)
                     +t3(i,j,k,k)
                     +t1(i,j,k,k,k)
                     +t3(i,j,k,k)
                     +t1(i,j,k,k,k)
                     +t3(i,j,k,k)
                     +t1(i,j,k,k,k)
                     +t3(i,j,k,k)
                     +t1(i,j,k,k,k)
                     +t3(i,j,k,k)
                     +t1(i,j,k,k,k)
                     +t1(i,j,k,k,k)
                     +t3(i,j,k,k)
                     +t3(i,j,k,k)
                     +t1(i,j,k,k,k)
                     +t3(i,j,k,k)
                     +t1(i,j,k,k,k)
                     +t3(i,j,k,k)
                     +t1(i,j,k,k,k)
                     +t3(i,j,k,k)
                     +t1(i,j,k,k,k)
                     +t3(i,j,k,k)
                     +t1(i,j,k,k,k)
                     +t3(i,j,k,k)
                     +t1(i,j,k,k,k)
                     +t3(i,j,k,k)
                     +t1(i,j,k,k,k)
                     +t3(i,j,k,k)
                     +t1(i,j,k,k,k)
                     +t3(i,j,k,k)
                     +t1(i,j,k,k,k);
    a.toc();
}

void test_great_matrix_low_rank_1_thread(){
    set_thread();
    tensor<int,rank<3>> t1(1000,1000,1000);

    for(auto iter=t1.begin(); iter!=t1.end(); ++iter)
        *iter = 1;

    auto i=new_index;
    auto j=new_index;

    a.tic();
    tensor<int> t4 = t1(i,i,j) + t1(i,i,j);
    a.toc();
}

void test_great_matrix_low_rank_n_thread(){
    set_thread(threads);
    tensor<int,rank<3>> t1(1000,1000,1000);

    for(auto iter=t1.begin(); iter!=t1.end(); ++iter)
        *iter = 1;

    auto i=new_index;
    auto j=new_index;

    a.tic();
    tensor<int> t4 = t1(i,i,j) + t1(i,i,j);
    a.toc();
}

void test_great_matrix22_low_rank_1_thread(){
    set_thread();
    tensor<int,rank<2>> t1(4000,4000);

    for(auto iter=t1.begin(); iter!=t1.end(); ++iter)
        *iter = 1;

    auto i=new_index;
    auto j=new_index;

    a.tic();
    tensor<int> t4 = t1(i,j) + t1(i,j);
    a.toc();
}

void test_great_matrix22_low_rank_n_thread(){
    set_thread(threads);
    tensor<int,rank<2>> t1(4000,4000);

    for(auto iter=t1.begin(); iter!=t1.end(); ++iter)
        *iter = 1;

    auto i=new_index;
    auto j=new_index;

    a.tic();
    tensor<int> t4 = t1(i,j) + t1(i,j);
    a.toc();
}

void test_big_contaction_1_thread(){
    set_thread();

    tensor<int> t1(1000,1000,1000), t2(1000);

    int count=0;
    for(auto iter=t1.begin(); iter!=t1.end(); ++iter)
        *iter = 1;

    auto i=new_index;
    auto j=new_index;

    a.tic();
    t2(i) = t1(i,j,j);
    a.toc();
}

void test_big_contaction_n_thread(){
    set_thread(8);

    tensor<int> t1(1000,1000,1000), t2(1000);

    int count=0;
    for(auto iter=t1.begin(); iter!=t1.end(); ++iter)
        *iter = 1;

    auto i=new_index;
    auto j=new_index;

    a.tic();
    t2(i) = t1(i,j,j);
    a.toc();
}

void test_big_multiplication_1_thread(){
    set_thread();

    tensor<int> t1(1000,1000), t2(1000, 1000);

    for(auto iter=t1.begin(); iter!=t1.end(); ++iter)
        *iter = 1;

    auto i=new_index;
    auto j=new_index;
    auto k=new_index;

    a.tic();
    t2(i, k) = t1(i, j) * t1(k, j);
    a.toc();
}

void test_big_multiplication_n_thread(){
    set_thread(8);

    tensor<int> t1(1000,1000), t2(1000, 1000);

    for(auto iter=t1.begin(); iter!=t1.end(); ++iter)
        *iter = 1;

    auto i=new_index;
    auto j=new_index;
    auto k=new_index;

    a.tic();
    t2(i, k) = t1(i, j) * t1(k, j);
    a.toc();
}

int main(){
    int n_test = 1;

    std::cout << "Test " << n_test << " sequential" << std::endl;
    test_invert_matrixes_1_thread();
    std::cout << "Test " << n_test << " parallel" << std::endl;
    test_invert_matrixes_n_threadss();
    n_test++;
    std::cout << std::endl;


    std::cout << "Test " << n_test << " sequential" << std::endl;
    test_sum_mult_op_1_threads();
    std::cout << "Test " << n_test << " parallel" << std::endl;
    test_sum_mult_op_n_threads();
    n_test++;
    std::cout << std::endl;

    std::cout << "Test " << n_test << " sequential" << std::endl;
    test_subtract_mult_1_thread();
    std::cout << "Test " << n_test << " parallel" << std::endl;
    test_subtract_mult_4_thread();
    n_test++;
    std::cout << std::endl;

    std::cout << "Test " << n_test << " sequential" << std::endl;
    test_invert_indexes_mult_1_thread();
    std::cout << "Test " << n_test << " parallel" << std::endl;
    test_invert_indexes_mult_n_threads();
    n_test++;
    std::cout << std::endl;

    std::cout << "Test " << n_test << " sequential" << std::endl;
    test_sum_2244_2442_1_thread();
    std::cout << "Test " << n_test << " parallel" << std::endl;
    test_sum_2244_2442_n_threads();
    n_test++;
    std::cout << std::endl;

    std::cout << "Test " << n_test << " sequential" << std::endl;
    test_mult_all_ranked_1_thread();
    std::cout << "Test " << n_test << " parallel" << std::endl;
    test_mult_all_ranked_n_threads();
    n_test++;
    std::cout << std::endl;

    std::cout << "Test " << n_test << " sequential" << std::endl;
    test_simple_assignment_1_thread();
    std::cout << "Test " << n_test << " parallel" << std::endl;
    test_simple_assignment_n_threads();
    n_test++;
    std::cout << std::endl;

    std::cout << "Test " << n_test << " sequential" << std::endl;
    test_simple_mult_222_2_1_thread();
    std::cout << "Test " << n_test << " parallel" << std::endl;
    test_simple_mult_222_2_n_threads();
    n_test++;
    std::cout << std::endl;

    std::cout << "Test " << n_test << " sequential" << std::endl;
    test_very_long_mult_1_thread();
    std::cout << "Test " << n_test << " parallel" << std::endl;
    test_very_long_mult_n_thread();
    n_test++;
    std::cout << std::endl;

    std::cout << "Test " << n_test << " sequential" << std::endl;
    test_very_long_mult_1_thread_second_try();
    std::cout << "Test " << n_test << " parallel" << std::endl;
    test_very_long_mult_n_thread_second_try();
    n_test++;
    std::cout << std::endl;

    std::cout << "Test " << n_test << " sequential" << std::endl;
    test_very_long_mult_1_thread_third_try();
    std::cout << "Test " << n_test << " parallel" << std::endl;
    test_very_long_mult_n_thread_third_try();
    n_test++;
    std::cout << std::endl;

    std::cout << "Test " << n_test << " sequential" << std::endl;
    test_mega_sum_1_threads_second_try();
    std::cout << "Test " << n_test << " parallel" << std::endl;
    test_mega_sum_n_threads_second_try();
    n_test++;
    std::cout << std::endl;

    std::cout << "Test " << n_test << " sequential" << std::endl;
    test_great_matrix_low_rank_1_thread();
    std::cout << "Test " << n_test << " parallel" << std::endl;
    test_great_matrix_low_rank_n_thread();
    n_test++;
    std::cout << std::endl;

    std::cout << "Test " << n_test << " sequential" << std::endl;
    test_great_matrix22_low_rank_1_thread();
    std::cout << "Test " << n_test << " parallel" << std::endl;
    test_great_matrix22_low_rank_n_thread();
    n_test++;
    std::cout << std::endl;

    std::cout << "Test " << n_test << " sequential" << std::endl;
    test_big_contaction_1_thread();
    std::cout << "Test " << n_test << " parallel" << std::endl;
    test_big_contaction_n_thread();
    n_test++;
    std::cout << std::endl;

    std::cout << "Test " << n_test << " sequential" << std::endl;
    test_big_multiplication_1_thread();
    std::cout << "Test " << n_test << " parallel" << std::endl;
    test_big_multiplication_n_thread();
    n_test++;
    std::cout << std::endl;

}