#include<iostream>
#include<chrono>

#include"tensor.h"




int main() {

	
        Tensor::tensor<int> td(2,2,3);
    Tensor::tensor<int, Tensor::rank<3>> tr(2,2,3);
    
    int count=0;
    Tensor::tensor<int> t2 = td;
    for(auto iter=t2.begin(); iter!=t2.end(); ++iter) 
		*iter = count++;
   
    t2 = tr;
    for(auto iter=t2.begin(); iter!=t2.end(); ++iter) 
		*iter = count++;
	

	
	
	for(auto iter=td.begin(); iter!=td.end(); ++iter)
		std::cout << *iter << ' ';
    std:: cout << '\n';
    
    for(auto iter=tr.begin(); iter!=tr.end(); ++iter)
		std::cout << *iter << ' ';
    std:: cout << '\n';

    
    
  
    for(auto iter=tr.begin(2,{0,0,1}); iter!=tr.end(2,{0,0,1}); ++iter)
        std::cout << *iter << ' ';
    std:: cout << '\n';

    for(auto iter=td.begin(1,{0,0,1}); iter!=td.end(1,{0,0,1}); ++iter)
        std::cout << *iter << ' ';
    std:: cout << '\n';
    
    
    t2 = td.window(2,0,2);
    for(auto iter=t2.begin(); iter!=t2.end(); ++iter)
		std::cout << *iter << ' ';
    std:: cout << '\n';
    
    
 //*
    const int rep=1000;
	const int size=100;
    Tensor::tensor<int, Tensor::rank<2>> A(size,size);
    {
        std::cout << "ranked tensor:\n";
        auto start_time = std::chrono::high_resolution_clock::now();
        for (int n=0; n!=rep; ++n) {
            for (int i=0; i!=size; ++i)
                for (int j=0; j!=size; ++j)
                    A[i][j] += 1;
        }
        auto end_time = std::chrono::high_resolution_clock::now();
        double elapsed_time = std::chrono::duration<double>(end_time-start_time).count();
        
        std::cout << "multi-slice elapsed time: " << elapsed_time << '\n';
    }
     {
        auto start_time = std::chrono::high_resolution_clock::now();
        for (int n=0; n!=rep; ++n) {
            for (int i=0; i!=size; ++i)
                for (int j=0; j!=size; ++j)
                    A(i,j) += 1;
        }
        auto end_time = std::chrono::high_resolution_clock::now();
        double elapsed_time = std::chrono::duration<double>(end_time-start_time).count();
        
        std::cout << "direct-access elapsed time: " << elapsed_time << '\n';
    }
    {
        auto start_time = std::chrono::high_resolution_clock::now();
        for (int n=0; n!=rep; ++n) {
            for (int i=0; i!=size; ++i) {
                auto Ai=A[i];
                for (int j=0; j!=size; ++j)
                    Ai[j] += 1;
            }
        }
        auto end_time = std::chrono::high_resolution_clock::now();
        double elapsed_time = std::chrono::duration<double>(end_time-start_time).count();
        
        std::cout << "stored-slice elapsed time: " << elapsed_time << '\n';
    }
    {
        std::cout << "ranked iterator:\n";
        auto start_time = std::chrono::high_resolution_clock::now();
        for (int n=0; n!=rep; ++n) {
            const auto Aend=A.end();
            for (auto iter=A.begin(); iter!=Aend; ++iter)
                *iter += 1;
        }  
        auto end_time = std::chrono::high_resolution_clock::now();
        double elapsed_time = std::chrono::duration<double>(end_time-start_time).count();
        
        std::cout << "elapsed time: " << elapsed_time << '\n';
    }
        
    int B[size][size];
    {
        std::cout << "standard array:\n";
        auto start_time = std::chrono::high_resolution_clock::now();
        for (int n=0; n!=rep; ++n) {
            for (int i=0; i!=size; ++i)
                for (int j=0; j!=size; ++j)
                    B[i][j] += 1;
        }
        auto end_time = std::chrono::high_resolution_clock::now();
        double elapsed_time = std::chrono::duration<double>(end_time-start_time).count();
        
        std::cout << "multi-slice elapsed time: " << elapsed_time << '\n';
    }
    {
        auto start_time = std::chrono::high_resolution_clock::now();
        for (int n=0; n!=rep; ++n) {
            for (int i=0; i!=size; ++i) {
                auto Bi=B[i];
                for (int j=0; j!=size; ++j)
                    Bi[j] += 1;
            }
        }
        auto end_time = std::chrono::high_resolution_clock::now();
        double elapsed_time = std::chrono::duration<double>(end_time-start_time).count();
        
        std::cout << "stored-slice elapsed time: " << elapsed_time << '\n';
    }
    
    Tensor::tensor<int> C(size,size);
        {
        std::cout << "generic tensor:\n";
        auto start_time = std::chrono::high_resolution_clock::now();
        for (int n=0; n!=rep; ++n) {
            for (int i=0; i!=size; ++i)
                for (int j=0; j!=size; ++j)
                    C(i,j) += 1;
        }
        auto end_time = std::chrono::high_resolution_clock::now();
        double elapsed_time = std::chrono::duration<double>(end_time-start_time).count();
        
        std::cout << "direct-access elapsed time: " << elapsed_time << '\n';
    }
    {
        auto start_time = std::chrono::high_resolution_clock::now();
        for (int n=0; n!=rep; ++n) {
            for (int i=0; i!=size; ++i) {
                auto Ci=C[i];
                for (int j=0; j!=size; ++j)
                    Ci(j) += 1;
            }
        }
        auto end_time = std::chrono::high_resolution_clock::now();
        double elapsed_time = std::chrono::duration<double>(end_time-start_time).count();
        
        std::cout << "stored-slice elapsed time: " << elapsed_time << '\n';
    }
    {
        std::cout << "generic iterator:\n";
        auto start_time = std::chrono::high_resolution_clock::now();
        for (int n=0; n!=rep; ++n) {
            const auto Cend=C.end();
            for (auto iter=C.begin(); iter!=Cend; ++iter)
                *iter += 1;
        }
        auto end_time = std::chrono::high_resolution_clock::now();
        double elapsed_time = std::chrono::duration<double>(end_time-start_time).count();
        
        std::cout << "elapsed time: " << elapsed_time << '\n';
    }
   
//*/
}
