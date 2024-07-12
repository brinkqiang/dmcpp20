#include <barrier>
#include <thread>
#include <vector>
#include <atomic>
#include <iostream>
#include <functional>
#include "gtest.h"

class BarrierTest : public ::testing::Test {
protected:
	template<typename Barrier>
	static void WorkerFunction(Barrier& barrier, std::atomic<int>& counter, int iterations) {
		for (int i = 0; i < iterations; ++i) {
			// 模拟一些工作
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
			counter.fetch_add(1, std::memory_order_relaxed);
			barrier.arrive_and_wait();
		}
	}
};

TEST_F(BarrierTest, BarrierWithCompletionFunction) {
	const int num_threads = 5;
	const int iterations = 5;
	std::atomic<int> counter(0);
	std::atomic<int> phase(0);

	auto completion = [&phase, &counter]() noexcept {
		std::cout << "Phase " << phase << " completed. Counter: " << counter << std::endl;
		phase++;
	};

	std::barrier<decltype(completion)> sync_point(num_threads, completion);

	std::vector<std::thread> threads;
	for (int i = 0; i < num_threads; ++i) {
		threads.emplace_back(WorkerFunction<decltype(sync_point)>, std::ref(sync_point), std::ref(counter), iterations);
	}

	for (auto& t : threads) {
		t.join();
	}

	EXPECT_EQ(counter.load(), num_threads * iterations);
	EXPECT_EQ(phase.load(), iterations);
}
