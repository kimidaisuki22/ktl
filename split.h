#include <string_view>
#include <vector>

namespace ktl
{
    // split string by a character,
    // a empty string be split with be add into result
    template <typename CharType>
    std::vector<std::basic_string_view<CharType>>
    basic_split(std::basic_string_view<CharType> str, CharType delim)
    {
        std::vector<std::basic_string_view<CharType>>
            splitedStrings;
        size_t len{};
        auto point = str.begin();
        auto end = str.end();
        while (point + len != end)
        {
            if (point[len] == delim)
            {
                splitedStrings.emplace_back(point, len);
                point += len + 1;
                len = 0;
            }
            else
            {
                len++;
            }
        }
        if (len != 0)
        {
            splitedStrings.emplace_back(point, len);
        }
        return splitedStrings;
    }

    template <typename CharType>
    std::vector<std::basic_string_view<CharType>>
    basic_split(std::basic_string_view<CharType> str, std::basic_string_view<CharType> delim)
    {
        using sv = std::basic_string_view<CharType>;
        std::vector<sv>
            splitedStrings;
        auto point = str.begin();
        auto end = str.end();
        while (point != end)
        {
            auto newEnd = sv(point, end).find(delim, 0);
            if (newEnd != sv::npos)
            {
                splitedStrings.emplace_back(point, newEnd);
                point = point + newEnd + delim.size();
            }
            else
            {
                splitedStrings.emplace_back(point, end);
                break;
            }
        }

        return splitedStrings;
    }

    // invaild for overload
    // constexpr inline auto split = basic_split<char>;

    template <typename... Args>
    auto split(Args &&...args)
    {
        return basic_split<char>(std::forward<Args>(args)...);
    }

    template <typename... Args>
    auto wsplit(Args &&...args)
    {
        return basic_split<wchar_t>(std::forward<Args>(args)...);
    }

    // CheckAble require ( dict.coutain(elem) )
    // auto split(std::basic_stringview str,const checkAble& dict)
}

namespace ktl
{
    template <typename CharType>
    struct splitWithIterator
    {
        std::basic_string_view<CharType> str;
        CharType delim;

        splitWithIterator(std::basic_string_view<CharType> s, CharType d) : str{s}, delim{d}
        {
        }

        auto begin()
        {
            struct Iter
            {
                const CharType *point, *end;
                size_t len{};
                CharType delim;

                Iter(std::basic_string_view<CharType> str, CharType d) : point{str.begin()}, end{str.end()}, delim{d}
                {
                }
                std::basic_string_view<CharType> operator*() const noexcept
                {
                    return std::basic_string_view<CharType>(point, len);
                }
                Iter &operator++() noexcept
                {
                    if (len || point[len] == delim)
                        point += len + 1;
                    len = 0;
                    while (point + len < end)
                    {
                        if (point[len] == delim)
                        {
                            break;
                        }
                        else
                        {
                            len++;
                        }
                    }
                    return *this;
                }
                // return false if finish
                bool operator!=(bool) const noexcept
                {
                    return point < end;
                }
            };
            return ++Iter(str, delim);
        }
        auto end()
        {
            return bool(true);
        }
    };

    // only support split with single chracter.
    // no dynamic memory allcate.
    using splitSP = splitWithIterator<char>;
}


