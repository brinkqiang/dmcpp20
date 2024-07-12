#include <barrier>
#include <thread>
#include <vector>
#include <atomic>
#include "gtest.h"

class BarrierTest : public ::testing::Test {
protected:
	static void WorkerFunction(std::barrier<>& barrier, std::atomic<int>& counter, int iterations) {
		for (int i = 0; i < iterations; ++i) {
			// 模拟一些工作
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
			counter.fetch_add(1, std::memory_order_relaxed);
			barrier.arrive_and_wait();
		}
	}
};

TEST_F(BarrierTest, BarrierSynchronizesThreads) {
	const int num_threads = 5;
	const int iterations = 3;
	std::barrier sync_point(num_threads);
	std::atomic<int> counter(0);

	std::vector<std::thread> threads;
	for (int i = 0; i < num_threads; ++i) {
		threads.emplace_back(WorkerFunction, std::ref(sync_point), std::ref(counter), iterations);
	}

	for (auto& t : threads) {
		t.join();
	}

	// 验证所有线程都完成了所有迭代
	EXPECT_EQ(counter.load(), num_threads * iterations);
}

int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}