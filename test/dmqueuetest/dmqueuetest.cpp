
#include "gtest.h"

#include <queue>
#include <map>
#include <ctime>
#include <iostream>
#include <atomic>
#include <mutex>

#include "dmos.h"
struct Data {
    time_t time;
    std::map<std::string, std::string> info;
};

bool operator<(const Data& a, const Data& b) {
    return a.time < b.time;
}

std::mutex m_lock;

std::atomic_bool m_bStop = true;
TEST(dmqueuetest, dmqueuetest)
{
    std::queue<Data> q;
    Data data1 = { time(0), {{"key1", "value1"}, {"key2", "value2"}} };
    Data data2 = { time(0) + 1, {{"key3", "value3"}, {"key4", "value4"}} };
    {
        std::lock_guard guard(m_lock);
        q.push(data1); 
    }
    {
        std::lock_guard guard(m_lock);
        q.push(data2);
    }

    while (m_bStop) {

        m_lock.lock();
        if (q.empty())
        {
            m_lock.unlock();
            SleepMs(1);
            m_bStop = false;
            continue;
        }
        
        Data& data = q.front();

        std::cout << ctime(&data.time) << std::endl;
        for (auto& node : data.info) {
            std::cout << node.first << ": " << node.second << std::endl;
        }
        
        q.pop();

        m_lock.unlock();
    }

}
