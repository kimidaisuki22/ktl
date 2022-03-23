#include <span>
template <typename T>
auto getBytes(T &Elem) -> std::span<std::byte, sizeof(T)>
{
    return std::span<std::byte, sizeof(T)>(reinterpret_cast<std::byte *>(&Elem), sizeof(T));
}
