
#include <iostream>
#include <tuple>
#include <string>
#include "dmcast.h"
#include "dmformat.h"
#include "gtest.h"
#include "pystl_tuple.hpp"

TEST(dmtupletest, dmtupletest)
{
    auto t = std::make_tuple(1, 2, "abc", "def", 4.0f);
    fmt::print(dmcast::lexical_cast(t));
}

auto return_tuple1()
{
    int a = 33;
    int b = 22;
    int c = 31;
    return std::tie(a, b, c);
}

auto return_tuple2()
{
    int a = 33;
    int b = 22;
    int c = 31;
    return std::make_tuple(a, b, c);
}

TEST(dmtietest, dmtietest)
{
    auto a = return_tuple1();

    auto b = return_tuple2();

    auto x = std::get<0>(a);
    auto y = std::get<0>(b);

    using TUPLE_TYPES = decltype(b);

    std::tuple_element<1, decltype(b)>::type data;

    data = 1;
    set_tuple_item(b, 0, 100);
}