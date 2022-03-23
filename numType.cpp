#include <numeric>

// the member Type is the min size's (unsigned)type that can contain this number.
template <unsigned long long Num>
class MininumType
{
    static auto typeDeduction()
    {
        using std::numeric_limits;
        if constexpr (Num <= numeric_limits<unsigned char>::max())
        {
            return static_cast<unsigned char>(0);
        }
        else if constexpr (Num <= numeric_limits<unsigned short>::max())
        {
            return static_cast<unsigned short>(0);
        }
        else if constexpr (Num <= numeric_limits<unsigned int>::max())
        {
            return static_cast<unsigned int>(0);
        }
        else if constexpr (Num <= numeric_limits<unsigned long>::max())
        {
            return static_cast<unsigned long>(0);
        }
        else
        {
            return static_cast<unsigned long long>(0);
        }
    }

public:
    using Type = decltype(typeDeduction());
};

#include <typeinfo>
#include <iostream>
int main()
{
    using namespace std;

    cout << typeid(MininumType<23>::Type).name() << " " << sizeof(MininumType<23>::Type) << "\n";
    cout << typeid(MininumType<2333>::Type).name() << " " << sizeof(MininumType<2333>::Type) << "\n";
    cout << typeid(MininumType<23334444>::Type).name() << " " << sizeof(MininumType<23334444>::Type) << "\n";
    cout << typeid(MininumType<23334444444444>::Type).name() << " " << sizeof(MininumType<23334444444444>::Type) << "\n";
    // compile error
    // cout << typeid(MininumType<2333444422222222444444>::Type).name() << " " << sizeof(MininumType<23334444444444>::Type) << "\n";
}