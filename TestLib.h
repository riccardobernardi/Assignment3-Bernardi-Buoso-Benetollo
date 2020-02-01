//
// Created by rr on 08/11/2019.
//

#ifndef TENSORLIB_TESTLIB_H
#define TENSORLIB_TESTLIB_H

#include <functional>
#include <vector>
#include <iostream>
#include <chrono>
#include <unistd.h>

/*void test(const std::function<void()>& callback, const std::string& name, int number){
    pid_t pid = fork();

    if (pid == 0) {
        std::cout << "vvvv---------------TEST " << number << "-----------------------vvvv" << std::endl;
        callback();
        std::cout << std::endl << "***Concluso test [" << name << "]" << std::endl;
        std::cout << "^^^^---------------TEST " << number << "-----------------------^^^^" << std::endl;
        // std::cout << "***Errore al test [" << name << "]" << std::endl;
    }else {
        // std::cout << "sono il capo" << std::endl;
    }
}*/

class Tperf{
public:
    Tperf() = default;
    std::chrono::time_point<std::chrono::steady_clock> init;

    void tic(){
        this->init = std::chrono::steady_clock::now();
    }

    void toc(){
        std::chrono::time_point<std::chrono::steady_clock> stop = std::chrono::steady_clock::now();

        if(std::chrono::duration_cast<std::chrono::seconds>(stop - this->init).count() == 0){
            if(std::chrono::duration_cast<std::chrono::milliseconds>(stop - init).count() == 0){
                if(std::chrono::duration_cast<std::chrono::microseconds>(stop - init).count() == 0){
                    std::cout << "Elapsed time in nanoseconds : "
                              << std::chrono::duration_cast<std::chrono::nanoseconds>(stop - init).count()
                              << " ns" << std::endl;
                }else{
                    std::cout << "Elapsed time in microseconds : "
                              << std::chrono::duration_cast<std::chrono::microseconds>(stop - init).count()
                              << " µs" << std::endl;
                }
            }else{
                std::cout << "Elapsed time in milliseconds : "
                          << std::chrono::duration_cast<std::chrono::milliseconds>(stop - init).count()
                          << " ms" << std::endl;
            }
        }else{
            std::cout << "Elapsed time in seconds : "
                      << std::chrono::duration_cast<std::chrono::seconds>(stop - this->init).count()
                      << " sec" << std::endl;
        }


    }
};

class Test{
private:
    std::vector<std::function<void()>> _functions;
    std::vector<std::string> _names;

public:
    void launch_test(int x){
        Tperf b{};
        if(x == -1){
            for(unsigned long i=0; i<_functions.size();++i){
                //pid_t pid = fork();
                //if (pid == 0) {
                std::cout << "vvvv---------------TEST " << i+ 1<< "-----------------------vvvv" << std::endl;
                b.tic();
                _functions[i]();
                std::cout << std::endl << "***Concluso test [" << _names[i] << "]" << std::endl;
                b.toc();
                std::cout << "^^^^---------------TEST " << i+1 << "-----------------------^^^^" << std::endl;
                //}else{}
                sleep(1);
            }
        }else{
            //pid_t pid = fork();
            //if (pid == 0) {
            std::cout << "vvvv---------------TEST " << x << "-----------------------vvvv" << std::endl;
            b.tic();
            _functions[x-1]();
            std::cout << std::endl << "***Concluso test [" << _names[x-1] << "]" << std::endl;
            b.toc();
            std::cout << "^^^^---------------TEST " << x << "-----------------------^^^^" << std::endl;
            //}else{}
        }
    }
    void add(const std::function<void()>& a, const std::string& name){
        _functions.push_back(a);
        _names.push_back(name);
    }
};

#endif //TENSORLIB_TESTLIB_H
