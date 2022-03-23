#include "threadPool.h"

namespace threadPool
{

    Pool::Pool(int threadN)
    {
        for (int i = 0; i < threadN; i++)
        {
            threads_.emplace_back(
                [this](stop_token tk)
                {
                    while (!tasks_.empty() || !tk.stop_requested())
                    {
                        unique_lock lock{m_};
                        cv_.wait(lock, [&]
                                 { return !tasks_.empty() ||
                                          tk.stop_requested(); });
                        if (tasks_.empty())
                            continue;
                        auto task = move(tasks_.front());
                        tasks_.pop();
                        lock.unlock();
                        task();
                    }
                });
        }
    }

    Pool::~Pool()
    {
        for (auto &t : threads_)
        {
            t.request_stop();
        }
        cv_.notify_all();
    }
    void Pool::push(function<void()> f)
    {
        unique_lock lock{m_};
        tasks_.push(move(f));
        cv_.notify_one();
        lock.unlock();
    }
}
