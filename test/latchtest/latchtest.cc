#include <latch>
#include <thread>
#include <vector>
#include "gtest.h"

class LatchTest : public ::testing::Test {
protected:
    static void WorkerFunction(std::latch& latch, int& counter) {
        // 模拟一些工作
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        ++counter;
        latch.count_down();
    }
};

TEST_F(LatchTest, LatchSynchronizesThreads) {
    const int num_threads = 5;
    std::latch completion_latch(num_threads);
    int counter = 0;

    std::vector<std::thread> threads;
    for (int i = 0; i < num_threads; ++i) {
        threads.emplace_back(WorkerFunction, std::ref(completion_latch), std::ref(counter));
    }

    // 等待所有线程完成
    completion_latch.wait();

    // 验证所有线程都增加了计数器
    EXPECT_EQ(counter, num_threads);

    for (auto& t : threads) {
        t.join();
    }
}
