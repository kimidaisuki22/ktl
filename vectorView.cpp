#include <vector>
using namespace std;

template <typename T>
class vectorView
{
    vector<T> &vec;
    int base;
    int newEnd;

public:
    vectorView(vector<T> &v, int s, int e) : vec{v}, base{s}, newEnd{e} {}
    vectorView(vectorView<T> &v, int s, int e) : vec{v.vec}, base{s + v.base}, newEnd{v.base + e} {}

    auto begin()
    {
        return vec.begin() + base;
    }
    auto end()
    {
        return begin() + newEnd;
    }
    auto size()
    {
        return newEnd - base;
    }
    auto empty()
    {
        return newEnd <= base;
    }
    auto operator[](auto index)
    {
        return vec[index + base];
    }
};