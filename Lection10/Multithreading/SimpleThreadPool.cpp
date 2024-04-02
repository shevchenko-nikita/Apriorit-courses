#include "SimpleThreadPool.h"

SimpleThreadPool::SimpleThreadPool(std::size_t threadCount) : m_threadCount(threadCount) {
    for (int i = 0; i < threadCount; ++i) {
        auto func = [this] {
            while (true) {
                std::function<void()> task;
                std::unique_lock<std::mutex> lock(mut);

                condition.wait(lock, [this] {
                    return stop || !tasks.empty();
                });

                if (stop && tasks.empty()) {
                    return;
                }

                if(!tasks.empty()) {
                    task = std::move(tasks.front());
                    tasks.pop();
                }

                lock.unlock();

                if(task) {
                    task();
                }
            }
        };

        threads.emplace_back(func);
    }
}


SimpleThreadPool::~SimpleThreadPool() {
    Destroy();
}

void SimpleThreadPool::WorkOn() {
    std::cout << "Function WorkOn executing on thread - " << std::this_thread::get_id() << std::endl;
}

void SimpleThreadPool::Destroy() {
    std::unique_lock<std::mutex> lock(mut);

    if(stop) {
        return;
    }

    stop = true;
    lock.unlock();

    condition.notify_all();

    for (auto& th : threads) {
        //std::cout << "Finished thread - " << th.get_id() << std::endl;
        th.join();
    }

    threads.clear();

}