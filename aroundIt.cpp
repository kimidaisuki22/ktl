#include <span>
#include <array>

namespace pointsSpace
{
    using steps = std::pair<uint8_t, uint8_t>;
}

std::array<pointsSpace::steps, 4> basicMoves = {
    pointsSpace::steps{1, 0},
    pointsSpace::steps{-1, 0},
    pointsSpace::steps{0, 1},
    pointsSpace::steps{0, -1},
};

template <typename AxisType, typename MovesType>
class AroundIter
{
    using Point = pair<AxisType, AxisType>;
    Point start;
    Point now_;
    std::span<MovesType> moves_;
    short step = 0;

    Point add(Point raw, MovesType step)
    {
        raw.first += step.first;
        raw.second += step.second;
        return raw;
    }

public:
    AroundIter(Point pt, std::span<MovesType> moves = basicMoves) : start{pt}, step{0}, moves_{moves}
    {
    }
    template <class T>
    bool operator!=(const T &t)
    {
        return step < sp.size();
    }
    Point operator*() { return now_; }
    void operator++()
    {
        now_ = add(start, moves_[step++]);
        return;
    }
};

template <typename AxisType>
class AroundWrap
{
public:
    using Point = pair<AxisType, AxisType>;
    Point pt;
    AroundWrap(Point p) : pt{p} {}
    auto begin()
    {
        return AroundIter(pt);
    }
    auto end()
    {
        return nullptr;
    }
};

