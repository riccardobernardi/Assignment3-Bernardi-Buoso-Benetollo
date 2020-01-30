//
// Created by rr on 08/11/2019.
//

#ifndef TENSORLIB_TESTLIB_H
#define TENSORLIB_TESTLIB_H

#include <functional>
#include <vector>
#include <iostream>
#include <zconf.h>

class Test{
private:
    std::vector<std::function<void()>> _functions;
    std::vector<std::string> _names;

public:
    void launch_test(int x){
        if(x == -1){
            for(unsigned long i=0; i<_functions.size();++i){
                //pid_t pid = fork();
                //if (pid == 0) {
                std::cout << "vvvv---------------TEST " << i << "-----------------------vvvv" << std::endl;
                _functions[i]();
                std::cout << std::endl << "***Concluso test [" << _names[i] << "]" << std::endl;
                std::cout << "^^^^---------------TEST " << i << "-----------------------^^^^" << std::endl;
                //}else{}
            }
        }else{
            //pid_t pid = fork();
            //if (pid == 0) {
            std::cout << "vvvv---------------TEST " << x << "-----------------------vvvv" << std::endl;
            _functions[x]();
            std::cout << std::endl << "***Concluso test [" << _names[x] << "]" << std::endl;
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

