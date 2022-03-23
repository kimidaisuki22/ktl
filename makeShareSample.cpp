#include <iostream>
#include <memory>

using namespace std;

void operator delete(void *pt, std::size_t s) noexcept
{
    printf("deallocate momery %lu Bytes.\n", s);
    delete(pt);
}
class A
{
    int _[1024*1024];
public:
    ~A()
    {
        printf("A died.\n");
    }
};

int main()
{
    printf("build.\n");
    auto a = make_shared<A>();
    printf("build weak.\n");
    weak_ptr pa = a;

    printf("release share.\n");
    a.reset();
    printf("release b\n");
    pa.reset();
    printf("\n");

    {
        printf("build.\n");
        auto a = shared_ptr<A>(new A());
        printf("build weak.\n");
        weak_ptr pa = a;

        printf("release share.\n");
        a.reset();
        printf("release b\n");
        pa.reset();
        printf("\n");
    }
}