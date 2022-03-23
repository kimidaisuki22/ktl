template <typename... Args>
void printsContinue(Args &&...args)
{
    (std::cout << ... << args) << ' ';
}

template <typename Ostream, typename First, typename... Args>
void sprints(Ostream &os, First &&frist, Args &&...args)
{
    os << frist;
    if constexpr (sizeof...(args) > 1)
    {
        os << ' ';
        sprints(os, args...);
    }
}

template <typename... Args>
void prints(Args &&...args)
{
    auto &os = std::cout;
    sprints(os, args...);
}
