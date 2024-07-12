#include <iomanip>
#include <iostream>
#include <string>
#include <type_traits>
#include <variant>
#include <vector>
#include <algorithm>
#include <random>
#include "gtest.h"
#include "utilcomp.h"

// test git patch
class player
{
public:
    player(int nLevel, int nAge)
        : m_nLevel(nLevel), m_nAge(nAge)
    {

    }

    int get_level()
    {
        return m_nLevel;
    }

    int get_age()
    {
        return m_nAge;
    }

    int m_nLevel;
    int m_nAge;
};

uint32_t GetRand(uint32_t dwMin, uint32_t dwMax)
{
    std::uniform_int_distribution<uint32_t> _dist(std::min(dwMin, dwMax), std::max(dwMin, dwMax));
    static std::mt19937 GenerateRand;
    return _dist(GenerateRand);
}

int count = 1000000;
std::vector<player*> vecPlayer;

TEST(dmsort_init, dmsort_init)
{
    vecPlayer.reserve(count);
    for (int i = 0; i < count; i++)
    {
        vecPlayer.push_back(new player(GetRand(1, count), GetRand(1, count)));
    }
}
TEST(dmsort, dmsort)
{
    std::sort(vecPlayer.begin(), vecPlayer.end(), [](player* p1, player* p2)
    {
        return (p1->get_level() < p2->get_level()) ||
            (p1->get_level() == p2->get_level() && p1->get_age() > p2->get_age());
    });

    std::sort(vecPlayer.begin(), vecPlayer.end(), [](player* p1, player* p2)
    {
        return (p1->get_level() > p2->get_level()) ||
            (p1->get_level() == p2->get_level() && p1->get_age() > p2->get_age());
    });
}

TEST(intersection, intersection)
{
    using namespace std;
    class Solution {
    public:
        vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
            std::vector<int> result;
            std::sort(nums1.begin(), nums1.end());
            std::sort(nums2.begin(), nums2.end());
            std::set_intersection(nums1.begin(), nums1.end(), nums2.begin(), nums2.end(), inserter(result, result.begin()));
            result.erase(unique(result.begin(), result.end()), result.end());
            return result;
        }
    };

    vector<int> nums1 = { 1,1,2,2 };
    vector<int> nums2 = { 2,2 };

    Solution s;
    auto ret = s.intersection(nums1, nums2);
}

#include <iostream>
#include <vector>
#include <string>
#include <time.h>
#include <algorithm>

typedef struct tagLineDetail
{
	tagLineDetail()
	{
		nGameId = 0;
		nLineId = 0;
		nPing = 0;
		bSelected = false;
		nLineAreaId = 0;
		nZPing = 0;
		nLinePing = 0;
	};

	int nLineId;            //线路 id
	int nGameId;            //游戏id
	std::wstring strName;        //线路名称
	int nPing;                //客户端显示 ping 值(接入点到出口点的ping值+线路偏移量+专线偏移量，再加以修正)
	int nLinePing;            // 接入点到出口点的ping值
	bool bSelected;            //是否默认线路
	int nLineAreaId;        // 线路区域id
	int nZPing;             //接入点到出口点的ping值+偏移量
}LineDetail, * PLineDetail;

TEST(LineDetail, LineDetail)
{


		srand((unsigned)time(NULL));
		std::vector<LineDetail> DetailVec;
		for (int i = 0; i < 20; i++)
		{
			LineDetail Detail;
			Detail.nLineAreaId = 10 + rand() % 10;
			Detail.nLinePing = 20 + rand() % 30;
			DetailVec.push_back(Detail);
		}

		for (int i = 0; i < 20; i++)
		{
			std::cout << DetailVec.at(i).nLineAreaId << "  " << DetailVec.at(i).nLinePing << std::endl;
		}

		std::cout << "------------------------" << std::endl;

        std::sort(DetailVec.begin(), DetailVec.end(), PP_COMBINECOMP_LESS_V2(&LineDetail::nLineAreaId, &LineDetail::nLinePing));

		for (int i = 0; i < 20; i++)
		{
			std::cout << DetailVec.at(i).nLineAreaId << "  " << DetailVec.at(i).nLinePing << std::endl;
		}

}