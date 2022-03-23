#include <cstdint>
#include <numeric>

#define CHECK_SIZE(Type, size) static_assert(sizeof(Type) == (size))

CHECK_SIZE(char, 1);
CHECK_SIZE(short, 2);
CHECK_SIZE(int, 4);
CHECK_SIZE(std::size_t, 8);

static_assert(std::numeric_limits<char>::max() == 127);
