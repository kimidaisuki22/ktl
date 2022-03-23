#include <unordered_map>
#include <unordered_set>
#include <climits>
#include <queue>
#include <vector>
template <>
struct std::hash<std::pair<int, int>>
{
    size_t operator()(std::pair<int, int> p) const noexcept
    {
        return ((size_t)p.first << 32) | p.second;
    }
};
using std::max;
using std::min;
using std::swap;
class undirectGraph
{
public:
    using NumType = int;

private:
    std::unordered_map<NumType, std::unordered_set<NumType>> graph_;

public:
    undirectGraph(/* args */);
    ~undirectGraph();
    void connect(int src, int dest);
    std::unordered_map<NumType, NumType> distance(int dest);
};

undirectGraph::undirectGraph(/* args */)
{
}

undirectGraph::~undirectGraph()
{
}

void undirectGraph::connect(int src, int dest)
{
    graph_[src].insert(dest);
    graph_[dest].insert(src);
}

std::unordered_map<undirectGraph::NumType, undirectGraph::NumType> undirectGraph::distance(int dest)
{
    std::unordered_map<NumType, NumType> result;
    std::queue<NumType> next;
    std::queue<NumType> nextBuffer;
    std::unordered_set<NumType> checked;

    next.push(dest);
    NumType depth = 0;
    while (!next.empty() || !nextBuffer.empty())
    {

        while (!next.empty())
        {
            if (!checked.count(next.front()))
            {
                checked.insert(next.front());
                result[next.front()] = depth;
                for (auto near : graph_[next.front()])
                {
                    if (!checked.count(near))
                    {
                        nextBuffer.push(near);
                    }
                }
            }

            next.pop();
        }
        swap(nextBuffer, next);
        depth++;
    }
    return result;
}

class undirectGraph
{
public:
    using NumType = int;

private:
    std::vector<std::vector<NumType>> graph_;
    int size_;

public:
    undirectGraph(int s);
    ~undirectGraph();
    void connect(int src, int dest);
    std::vector<NumType> distance(int dest);
};

undirectGraph::undirectGraph(int s) : graph_(s), size_{s}
{
}

undirectGraph::~undirectGraph()
{
}

void undirectGraph::connect(int src, int dest)
{
    graph_[src].push_back(dest);
    graph_[dest].push_back(src);
}

std::vector<undirectGraph::NumType> undirectGraph::distance(int dest)
{
    std::vector<NumType> result(size_,0);
    std::queue<NumType> next;
    std::queue<NumType> nextBuffer;
    std::vector<char> checked(size_,0);

    next.push(dest);
    checked[0] =1;
    NumType depth = 0;
    while (!next.empty() || !nextBuffer.empty())
    {

        while (!next.empty())
        {
            auto niStart = next.front();
            result[niStart] = depth;
            for (auto near : graph_[niStart])
            {
                if (!checked[near])
                {
                    checked[near] =1;
                    nextBuffer.push(near);
                }
            }
        

            next.pop();
        }
        swap(nextBuffer, next);
        depth++;
    }
    return result;
}
