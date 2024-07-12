
#include <iostream>
#include <tuple>
#include <string>
#include <vector>
#include <cstdint>
#include <type_traits>
#include <regex>
#include <string.h>

#include "gtest.h"

#include "dmstrtk.hpp"

template<typename... Args>
inline void append(std::string& s, Args&& ... args)
{
    ((s += std::forward<Args>(args), s += ", "), ...);
}

//template<typename... Args>
//void print(Args... Args){
//    std::initializer_list<int>{(std::cout << args << std::endl, 0)...};
//}

//c++17 unary fold
template<typename... Args>
void print(Args... args)
{
    ((std::cout << args << std::endl), ...);
}
//
////c++17 binary fold
//template<typename ...Args> void print(Args&&... args) {
//    (std::cout << ... << args) << '\n';
//}

TEST(dmstring, dmstring)
{
    std::string s;
    append(s, "1", "2", "3");
    print("1", "2", "3");

    std::string strData = R"(C:\dfajf\name)";
    std::vector<std::string> vecData;
    strtk::parse(strData, "\\", vecData);

    strtk::ext_string ext("123");
    int a=ext.as_type<int>();

    strtk::build_string bs;
    bs << "123" << 123;
    auto str = bs.as_string();
    
}

std::string replace_post(std::string_view src, std::string_view new_post)
{
    auto pos = src.find(".") + 1;
    std::string_view sub = src.substr(0, pos);
    std::string str(sub);
    return str + new_post.data();
}

TEST(replace_string, replace_string)
{
    std::string_view sv = "abcdefg.xxx";
    std::string s = replace_post(sv, "yyy");

    std::cout << sv << " replaced post by yyy result is:" << s << std::endl;

    std::stringstream ss;
    ss << "123455";
    const std::string& str = ss.str();
}

TEST(re, re)
{
    std::string str = R"(<div><!--s-data:{"title":"�����оŷ���ѧ�ٿ���������ʦ��������<em>����</em>","titleUrl":"https://3g.163.com/dy/article/H6PIRLF10514EV7Q.html","dataClick":"{\n            'f0':'77A717EA',\n            'f1':'9F73F1E4',\n            'f2':'4CA6DE6A',\n            'f3':'54E5243F',\n            't':'1651916932',\n        }","leftImgSrc":"","hasImg":false,"summary":"<em>����</em>�ֳ��� ����ʱ������5��7��Ѷ(ͨѶԱ ��־÷ �Ӿ��� ���)�����ʦ��ѧУ��δ����ϣ����Ϊ���ý���ѧУ�����ʦ����,�ƶ�ѧУ������ѧ�����Ȳ���չ,5��5������,�����оŷ���ѧ���������ʦ��������<em>����</em>�� ����,�����оŷ���ѧ��ʦ��...","showKuaizhao":true,"docType":-1,"resIndex":1,"queryId":"9fdff463001045e2","queryUbs":"%BB%E1%D2%E9","snapshootKey":"m=ljeqzS-WrLRkmW0sPbjzPMb3AmrT89rkgC_nMm6UGzxjPY7lg-YlD3GThv4AJ2QBn3j5edmEdeIR-X-fAhCNeizhQgcw-xmIieRK5-A3T9cTulmqT3OEp-9Lt9U84UCCZtpHXsTSfjtI97wZxnk2uq&p=877fc316d9c115f14ebd9b7d0b54&newp=853dc80a85cc43ff57ee920c1e5792695912c10e3fd1c44324b9d71fd325001c1b69e3b823281603d4c6786c15e9241dbdb239256b55&s=cfcd208495d565ef","dispTime":"4����ǰ","sourceIcon":"","rtses":"����","sourceName":"��������","accessibilityData":{"titleAriaLabel":"���⣺�����оŷ���ѧ�ٿ���������ʦ������������","absAriaLabel":"ժҪ �����ֳ��� ����ʱ������5��7��Ѷ(ͨѶԱ ��־÷ �Ӿ��� ���)�����ʦ��ѧУ��δ����ϣ����Ϊ���ý���ѧУ�����ʦ����,�ƶ�ѧУ������ѧ�����Ȳ���չ,5��5������,�����оŷ���ѧ���������ʦ�����������顣 ����,�����оŷ���ѧ��ʦ�� ժҪ����������鿴����","sourceAriaLabel":"������Դ����������","timeAriaLabel":"�����ڣ�4����ǰ"},"$style":{"news-title":"news-title_1YtI1","newsTitle":"news-title_1YtI1","title-hover":"title-hover_1NW7q","titleHover":"title-hover_1NW7q","content-wrapper":"content-wrapper_1SuJ0","contentWrapper":"content-wrapper_1SuJ0","content":"content_BL3zl","news-title-font":"news-title-font_1xS-F","newsTitleFont":"news-title-font_1xS-F"},"titleHover":false,"cacheDomain":"http://cache.baidu.com","cinfoUrl":"http://cache.baidu.com/c?m=ljeqzS-WrLRkmW0sPbjzPMb3AmrT89rkgC_nMm6UGzxjPY7lg-YlD3GThv4AJ2QBn3j5edmEdeIR-X-fAhCNeizhQgcw-xmIieRK5-A3T9cTulmqT3OEp-9Lt9U84UCCZtpHXsTSfjtI97wZxnk2uq&p=877fc316d9c115f14ebd9b7d0b54&newp=853dc80a85cc43ff57ee920c1e5792695912c10e3fd1c44324b9d71fd325001c1b69e3b823281603d4c6786c15e9241dbdb239256b55&s=cfcd208495d565ef&user=baidu&fm=sc&query=%BB%E1%D2%E9&qid=9fdff463001045e2&p1=1"}--><h3 class="news-title_1YtI1 "><a href="https://3g.163.com/dy/article/H6PIRLF10514EV7Q.html" target="_blank" class="news-title-font_1xS-F" aria-label="���⣺�����оŷ���ѧ�ٿ���������ʦ������������" data-click="{")";

    std::regex e("data:(.*?)titleUrl");

    std::smatch cm;
    std::vector<std::string> vec;
    std::string strData = str;
    for (; std::regex_search(strData, cm, e, std::regex_constants::match_default);)
    {
        vec.push_back(cm.str());

        strData = cm.suffix().str();
    }

}

TEST(dmzero, dmstring)
{
    std::string strData = "123";
    strData.append(1, '\0');
    strData.append("123");
    std::string strTemp;
    strTemp.append(strData);

}

TEST(swap_ranges, swap_ranges)
{
	char szBuf[5] = "1234";
	char szBuf2[5] = "4321";

	for (int i = 1; i < 10000000; i++)
	{
		std::swap_ranges(szBuf, szBuf + sizeof(szBuf), szBuf2);
	}
}

void memswap(void* ptr1, void* ptr2, size_t size) {
    // ����̶���С�Ļ�����
    const size_t bufferSize = 4096;
    char temp[bufferSize];

    // ����ڴ�ָ���Ƿ���Ч
    if (ptr1 != NULL && ptr2 != NULL) {
        size_t remainingSize = size;
        char* p1 = (char*)ptr1;
        char* p2 = (char*)ptr2;

        while (remainingSize > 0) {
            size_t swapSize = (remainingSize < bufferSize) ? remainingSize : bufferSize;

            memcpy(temp, p1, swapSize);
            memcpy(p1, p2, swapSize);
            memcpy(p2, temp, swapSize);

            p1 += swapSize;
            p2 += swapSize;
            remainingSize -= swapSize;
        }
    }
}
TEST(memswap, memswap)
{
	char szBuf[5] = "1234";
	char szBuf2[5] = "4321";

	for (int i = 1; i < 10000000; i++)
	{
        memswap(szBuf, szBuf2, sizeof(szBuf));
	}
}

void cswap_ranges(char* first1, char* last1, char* first2) {
	while (first1 != last1) {
		char temp = *first1;
		*first1++ = *first2++;
		*first2 = temp;
	}
}
TEST(cswap_ranges, cswap_ranges)
{
	char szBuf[5] = "1234";
	char szBuf2[5] = "4321";

	for (int i = 1; i < 10000000; i++)
	{
        cswap_ranges(szBuf, szBuf+sizeof(szBuf), szBuf2);
	}
}

void cswap_ranges2(char* first1, char* last1, char* first2) {
	while (first1 != last1) {
		*first1 ^= *first2;
		*first2 ^= *first1;
		*first1 ^= *first2;
		first1++;
		first2++;
	}
}
TEST(cswap_ranges2, cswap_ranges2)
{
	char szBuf[5] = "1234";
	char szBuf2[5] = "4321";

	for (int i = 1; i < 10000000; i++)
	{
        cswap_ranges2(szBuf, szBuf + sizeof(szBuf), szBuf2);
	}
}