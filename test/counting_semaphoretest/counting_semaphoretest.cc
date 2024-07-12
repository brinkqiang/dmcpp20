#include <semaphore>
#include <thread>
#include <vector>
#include <atomic>
#include "gtest.h"

class CountingSemaphoreTest : public ::testing::Test {
protected:
	static void WorkerFunction(std::counting_semaphore<>& semaphore, std::atomic<int>& counter, int iterations) {
		for (int i = 0; i < iterations; ++i) {
			semaphore.acquire();
			// 模拟使用资源
			counter.fetch_add(1, std::memory_order_relaxed);
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
			semaphore.release();
		}
	}
};

TEST_F(CountingSemaphoreTest, SemaphoreLimitsResourceAccess) {
	const int max_concurrent = 3;
	const int num_threads = 10;
	const int iterations = 5;
	std::counting_semaphore semaphore(max_concurrent);
	std::atomic<int> counter(0);

	std::vector<std::thread> threads;
	for (int i = 0; i < num_threads; ++i) {
		threads.emplace_back(WorkerFunction, std::ref(semaphore), std::ref(counter), iterations);
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