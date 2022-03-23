#include "split.h"
#include <iostream>

#define PRINT(word) std::cout << word << " ";
#define PRINTL() std::cout << "\n";

int main()
{
    auto s1 = "1,23,456,7890,aed,,dfeds";
    auto s2 = ",,,,,,,";
    auto s3 = "";
    auto s4 = "aaaa";

    auto s5 = "fds&&fdsf&&fdsio&&1234&&&&";
   
    auto f = [](auto in)
    {
        for (auto s : ktl::split(in, ','))
            PRINT(s);
        PRINTL();

        for (auto s : ktl::splitSP(in, ','))
            PRINT(s);
        PRINTL();
    };
   
    f(s1);
    f(s2);
    f(s3);
    f(s4);

    for(auto s:ktl::split(s5,"&&")){
        PRINT(s);
    }
    PRINTL();
}