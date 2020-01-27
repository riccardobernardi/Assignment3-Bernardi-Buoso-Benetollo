#include<iostream>
#include"tensor.h"

using namespace Tensor;


std::ostream & operator << (std::ostream& out, Index_Set<>) { return out; }
template<unsigned id, unsigned... ids>
std::ostream & operator << (std::ostream& out, Index_Set<id, ids...>) {
    return out << id << ' ' << Index_Set<ids...>();
}




int main() {
    //a bit of fun with the Index_Set library ;)
    typedef Index_Set<2,3,5,3> myset;
    std::cout << myset() << "-> " << index_count<myset>::value <<'\n';

    typedef non_repeat<myset>::set my_nonrepeat_set;
    std::cout << my_nonrepeat_set() << "-> " << index_count<my_nonrepeat_set>::value << "\n";

    std::cout << set_diff<myset,my_nonrepeat_set>::type() << "\n";

    std::cout << is_same_nonrepeat<my_nonrepeat_set,Index_Set<5,2>>::value << ' ' <<
                 is_same_nonrepeat<my_nonrepeat_set,Index_Set<5,3,2>>::value << "\n\n";


    std::cout << merge<myset,set_diff<Index_Set<2,5,4,4>,my_nonrepeat_set>::type>::type() << "\n";

///*

    //testing Einstein notation
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


    for(auto iter=t2.begin(); iter!=t2.end(); ++iter)
                std::cout << *iter << ' ';
    std::cout << '\n';

    tensor<int> t3(2,2,2), t4(2);
     auto k=new_index;
    count=0;
    for(auto iter=t3.begin(); iter!=t3.end(); ++iter)
                *iter = count++;

    t4(i) = t3(i,j,k)*t1(j,k)+t3(i,k,k);
    for(auto iter=t3.begin(); iter!=t3.end(); ++iter)
                std::cout << *iter << ' ';
    std::cout << '\n';
    for(auto iter=t4.begin(); iter!=t4.end(); ++iter)
                std::cout << *iter << ' ';
    std::cout << '\n';



    t2(i,j) = t1(i,k)*t1(k,j);
    for(auto iter=t2.begin(); iter!=t2.end(); ++iter)
                std::cout << *iter << ' ';
    std::cout << '\n';


    t2(i,k) = t3(i,j,j)*t4(k);
    for(auto iter=t2.begin(); iter!=t2.end(); ++iter)
                std::cout << *iter << ' ';
    std::cout << '\n';

    tensor<int,rank<2>> t5=t1(i,j);
    for(auto iter=t5.begin(); iter!=t5.end(); ++iter)
                std::cout << *iter << ' ';
    std::cout << '\n';

    tensor<int,rank<2>> t6=t3(i,j,k)*t4(j);
    for(auto iter=t6.begin(); iter!=t6.end(); ++iter)
                std::cout << *iter << ' ';
    std::cout << '\n';
//*/
}
