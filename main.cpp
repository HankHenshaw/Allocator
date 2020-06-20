#include <iostream>
#include <map>
#include <cmath>
#include <iterator>

#include "hard.h"
#include "myallocator.h"
#include "mylist.h"

const int SIZE = 11;

int fa(int num)
{
    if(num < 0) throw std::logic_error("num < 0");
    if(num == 1 || num == 0) return 1;
    return num * fa(num - 1);
}

int fi(int num)
{
    if(num < 0) throw std::logic_error("num < 0");
    double golden_ratio = 1.61803;
    return std::round(std::pow(golden_ratio, num)/std::sqrt(5));
}

int main()
{
    /*-----------1-------------*/
    std::map<int, hard, std::less<int>, std::allocator<std::pair<const int, hard>>> m1;
    for(int i = 0; i < SIZE; ++i)
    {
        m1.emplace(std::piecewise_construct,
                   std::forward_as_tuple(i),
                   std::forward_as_tuple(fa(i), fi(i)));
    }

    for(const auto &x : m1)
    {
        std::cout << x.first << ":" << x.second << '\n';
    }

    /*-----------2-------------*/
    std::map<int, hard, std::less<int>, MyAlloc<std::pair<const int, hard>>> m2;
    for(int i = 0; i < SIZE; ++i)
    {
        m2.emplace(std::piecewise_construct,
                   std::forward_as_tuple(i),
                   std::forward_as_tuple(fa(i), fi(i)));
    }

    for(const auto &x : m2)
    {
        std::cout << x.first << ":" << x.second << '\n';
    }

    /*-----------3-------------*/
    MyList<hard> m3;
    for(int i = 0; i < SIZE; ++i)
    {
        m3.emplace(fa(i), fi(i));
    }

    for(const auto &x: m3)
    {
        std::cout << x << '\n';
    }

    /*-----------4-------------*/
    MyList<hard, MyAlloc<hard>> m4;
    for(int i = 0; i < SIZE; ++i)
    {
        m4.emplace(fa(i), fi(i));
    }

    for(const auto &x: m4)
    {
        std::cout << x << '\n';
    }
    return 0;
}
