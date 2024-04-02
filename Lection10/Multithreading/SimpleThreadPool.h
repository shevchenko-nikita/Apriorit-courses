#pragma once

#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <queue>
#include <functional>
#include <future>
#include <condition_variable>

class SimpleThreadPool {
public:
    explicit SimpleThreadPool(std::size_t threadCount);

    ~SimpleThreadPool();

    SimpleThreadPool(const SimpleThreadPool&) = delete;
    SimpleThreadPool& operator=(const SimpleThreadPool&) = delete;

    template <typename Fnc_T>
    auto Post(Fnc_T task) -> std::future<decltype(task())>;

    void WorkOn();

    void Destroy();

private:
//    std::thread CreateThread();

    size_t m_threadCount;
    std::vector<std::thread> threads;
    std::queue<std::function<void()>> tasks;
    std::condition_variable condition;
    std::mutex mut;
    bool stop = false;
};

template <typename Fnc_T>
auto SimpleThreadPool::Post(Fnc_T task) -> std::future<decltype(task())> {
    auto pck_task = std::make_shared<std::packaged_task<decltype(task())()>>(std::move(task));

    std::unique_lock<std::mutex> lock(mut);

    tasks.emplace([=] {
        (*pck_task)();
    });

    lock.unlock();

    condition.notify_one();
    return pck_task->get_future();
}