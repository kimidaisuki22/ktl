#pragma once

#include <thread>
#include <condition_variable>
#include <queue>
#include <vector>
#include <functional>

#include <iostream>
namespace threadPool
{
    using namespace std;
    class Pool
    {
        queue<function<void()>> tasks_;
        vector<jthread> threads_;
        mutex m_;
        condition_variable cv_;

    public:
        Pool(int threadN = thread::hardware_concurrency());
        ~Pool();

        void push(function<void()> f);
        
        void cleanRemain()
        {
            unique_lock lock{m_};
            decltype(tasks_)().swap(tasks_);
        }

        bool empty() const noexcept
        {
            return tasks_.empty();
        }

        size_t remain() const noexcept
        {
            return tasks_.size();
        }
    };
}