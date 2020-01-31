//
// Created by Riccardo Bernardi on 18/12/2019.
//

#include "TestLib.h"

#include<iostream>
#include"tensor.h"

using namespace Tensor;

int threads = 4;

std::ostream & operator << (std::ostream& out, Index_Set<>) { return out; }
template<unsigned id, unsigned... ids>
std::ostream & operator << (std::ostream& out, Index_Set<id, ids...>) {
    return out << id << ' ' << Index_Set<ids...>();
}


void test_indexlib(){
    //a bit of fun with the Index_Set library ;)
    typedef Index_Set<2,3,5,3> myset;
    std::cout << myset() << "-> " << index_count<myset>::value <<'\n';
}

void test_nonrepeat(){
    typedef Index_Set<2,3,5,3> myset;
    typedef non_repeat<myset>::set my_nonrepeat_set;
    std::cout << my_nonrepeat_set() << "-> " << index_count<my_nonrepeat_set>::value << "\n";
}

void test_diff(){
    typedef Index_Set<2,3,5,3> myset;
    typedef non_repeat<myset>::set my_nonrepeat_set;
    typedef Index_Set<2,3,5,3> myset;
    std::cout << set_diff<myset,my_nonrepeat_set>::type() << "\n";
}

void test_merge(){
    typedef Index_Set<2,3,5,3> myset;
    typedef non_repeat<myset>::set my_nonrepeat_set;

    std::cout << is_same_nonrepeat<my_nonrepeat_set,Index_Set<5,2>>::value << ' ' <<
    is_same_nonrepeat<my_nonrepeat_set,Index_Set<5,3,2>>::value << "\n\n";

    std::cout << merge<myset,set_diff<Index_Set<2,5,4,4>,my_nonrepeat_set>::type>::type() << "\n";
}

void test_iter_tensor(){
    //testing Einstein notation
    tensor<int,rank<2>> t1(2,2), t2(2,2);

    int count=0;
    for(auto iter=t1.begin(); iter!=t1.end(); ++iter)
        *iter = count++;
    for(auto iter=t1.begin(); iter!=t1.end(); ++iter)
        std::cout << *iter << ' ';
    std::cout << '\n';
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
    count=0;
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

void test_sum_mult_op_n_threadss(){
    set_thread(threads);
    tensor<int,rank<2>> t1(2,2);
    tensor<int> t3(2,2,2), t4(2);

    int count=0;
    for(auto iter=t1.begin(); iter!=t1.end(); ++iter)
        *iter = count++;
    count=0;
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

/*void test_subtract_mult_op(){
    tensor<int,rank<2>> t1(2,2);
    tensor<int> t3(2,2,2);

    int count=0;
    for(auto iter=t1.begin(); iter!=t1.end(); ++iter)
        *iter = count++;
    count=0;
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

    tensor<int> t4 = t1(j)-t3(i,k,k);

    std::cout << "here the result of [t4(i) = t3(i,j,k)*t1(j,k)+t3(i,k,k)];" << std::endl;
    for(auto iter=t4.begin(); iter!=t4.end(); ++iter)
        std::cout << *iter << ' ';
    std::cout << '\n';
}*/

void test_sum_2244_2442_1_thread(){
    set_thread();
    tensor<int> t1(2,2), t3(2,2,4,4), t4(2,4,4,2);

    int count=0;
    for(auto iter=t3.begin(); iter!=t3.end(); ++iter)
        *iter = count++;
    count=0;
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

void test_sum_2244_2442_n_threads(){
    set_thread(threads);
    tensor<int> t1(2,2), t3(2,2,4,4), t4(2,4,4,2);

    int count=0;
    for(auto iter=t3.begin(); iter!=t3.end(); ++iter)
        *iter = count++;
    count=0;
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

void test_sum_2244_2442_smaller_1_thread(){
    set_thread();
    tensor<int> t1(2,2), t3(2,2,3,3), t4(2,3,3,2);

    int count=0;
    for(auto iter=t3.begin(); iter!=t3.end(); ++iter)
        *iter = count++;
    count=0;
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

void test_sum_2244_2442_smaller_n_threads(){
    set_thread(threads);
    tensor<int> t1(2,2), t3(2,2,3,3), t4(2,3,3,2);

    int count=0;
    for(auto iter=t3.begin(); iter!=t3.end(); ++iter)
        *iter = count++;
    count=0;
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

    int count=0;
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

    int count=0;
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
    count=0;
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
    count=0;
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

/*void test_mult_all_ranked_1_thread(){
    tensor<int,rank<2>,thread<2>> t2(2,2);
    tensor<int,rank<3>> t3(2,2,2);
    tensor<int,rank<1>> t4(2);

    int count=0;
    for(auto iter=t3.begin(); iter!=t3.end(); ++iter)
        *iter = count++;
    count=0;
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
}*/

void test_simple_assignment_1_thread(){
    set_thread();
    tensor<int,rank<2>> t1(2,2), t2(2,2);
    tensor<int> t5(2,2); // if it was tensor<int,rank<2>> it was wrong, why? // because it have to be assigned in that moment

    int count=0;
    for(auto iter=t1.begin(); iter!=t1.end(); ++iter)
        *iter = count++;

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

    int count=0;
    for(auto iter=t1.begin(); iter!=t1.end(); ++iter)
        *iter = count++;

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

/*void test_very_long_mult(){
    tensor<int,rank<2>> t1(2,2), t2(2,2);

    int count=0;
    for(auto iter=t1.begin(); iter!=t1.end(); ++iter)
        *iter = count++;
    count=0;
    for(auto iter=t2.begin(); iter!=t2.end(); ++iter)
        *iter = count++;

    auto i=new_index;
    auto j=new_index;

    tensor<int> t6=t1(i,i)*t2(j,j)*t2(j,j)*t1(i,i)*t2(j,j)*t2(j,j)*t1(i,i)*t2(j,j)*t2(j,j)*t1(i,i);
    std::cout << "here the result of [t6=t1(i,i)*t2(j,j)];" << std::endl;
    for(auto iter=t6.begin(); iter!=t6.end(); ++iter)
        std::cout << *iter << ' ';
    std::cout << '\n';
}*/


void test_mega_sum_1_threads(){
    set_thread();
    tensor<int,rank<4>> t1(2,2,8,10);
    tensor<int,rank<4>> t3(2,2,8,9);

    int count=0;
    for(auto iter=t1.begin(); iter!=t1.end(); ++iter)
        *iter = count++;
    count=0;
    for(auto iter=t3.begin(); iter!=t3.end(); ++iter)
        *iter = count++;

    auto i=new_index;
    auto j=new_index;
    auto k=new_index;

    tensor<int> t4 = t3(i,j,k,k)+t1(i,j,k,k);
}

void test_mega_sum_n_threads(){
    set_thread(threads);
    tensor<int,rank<4>> t1(2,2,8,10);
    tensor<int,rank<4>> t3(2,2,8,9);

    int count=0;
    for(auto iter=t1.begin(); iter!=t1.end(); ++iter)
        *iter = count++;
    count=0;
    for(auto iter=t3.begin(); iter!=t3.end(); ++iter)
        *iter = count++;

    auto i=new_index;
    auto j=new_index;
    auto k=new_index;

    tensor<int> t4 = t3(i,j,k,k)+t1(i,j,k,k);
}


int main(){
    Test a{};
    a.add(test_indexlib, "test_indexlib");
    a.add(test_nonrepeat, "test_nonrepeat");
    a.add(test_sum_2244_2442_1_thread, "test_sum_2244_2442_1_thread");
    a.add(test_sum_2244_2442_n_threads,"test_sum_2244_2442_n_threads");
    a.add(test_diff, "test_diff");
    a.add(test_merge, "test_merge");
    a.add(test_iter_tensor, "test_iter_tensor");
    a.add(test_invert_matrixes_1_thread, "test_invert_matrixes_1_thread");
    a.add(test_invert_matrixes_n_threadss,"test_invert_matrixes_n_threadss");
    a.add(test_sum_mult_op_1_threads, "test_sum_mult_op_1_threads");
    a.add(test_sum_mult_op_n_threadss,"test_sum_mult_op_n_threadss");
    // a.add(test_subtract_mult_op, "test_subtract_mult_op");
    a.add(test_invert_indexes_mult_1_thread, "test_invert_indexes_mult_1_thread");
    a.add(test_invert_indexes_mult_n_threads,"test_invert_indexes_mult_n_threads");
    a.add(test_sum_2244_2442_smaller_1_thread, "test_sum_2244_2442_smaller_1_thread");
    a.add(test_sum_2244_2442_smaller_n_threads,"test_sum_2244_2442_smaller_n_threads");
    a.add(test_mult_all_ranked_1_thread, "test_mult_all_ranked_1_thread");
    a.add(test_mult_all_ranked_n_threads,"test_mult_all_ranked_n_threads");
    a.add(test_simple_assignment_1_thread, "test_simple_assignment_1_thread");
    a.add(test_simple_assignment_n_threads,"test_simple_assignment_n_threads");
    a.add(test_simple_mult_222_2_1_thread, "test_simple_mult_222_2_1_thread");
    a.add(test_simple_mult_222_2_n_threads,"test_simple_mult_222_2_n_threads");
    a.add(test_mega_sum_1_threads,"test_mega_sum_1_threads");
    a.add(test_mega_sum_n_threads,"test_mega_sum_n_threads");
    // a.add(test_very_long_mult, "test_very_long_mult");

    a.launch_test(-1);
}