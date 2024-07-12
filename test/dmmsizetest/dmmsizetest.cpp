#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <map>
#include "gtest.h"

#ifdef WIN32
#define msize _msize
#else
#include <malloc.h>
#define msize malloc_usable_size
#endif

TEST(dmmsize, dmmsize)
{
    uint64_t* pData = (uint64_t* )malloc(sizeof(uint64_t) * 1000);

    std::cout << msize((void*)pData) / sizeof(uint64_t);
}
