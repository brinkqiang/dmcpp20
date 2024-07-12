
#ifndef __PYSTL_TUPLE_H_INCLUDE__
#define __PYSTL_TUPLE_H_INCLUDE__

#include <tuple>
#include <stdexcept>

template <typename T>
int tuple_length(const T&)
{
    return std::tuple_size<T>::value;
}


template <int cidx, typename V, typename ... ARG>
typename std::enable_if < cidx >= sizeof...(ARG), void>::type
set_tuple_item_(std::tuple<ARG...>& v, int idx, V val)
{
    throw std::out_of_range{ "set_tuple_item out_of_range" };
}


template <int cidx, typename V, typename ... ARG>
typename std::enable_if < cidx < sizeof...(ARG), void>::type
set_tuple_item_(std::tuple<ARG...>& v, int idx, V val)
{
    using TUPLE_TYPES = std::tuple<ARG...>;
    using TUPLE_FILED = std::remove_reference_t<std::tuple_element_t<cidx, TUPLE_TYPES> >;

    if (idx == cidx)
    {
        std::get<cidx>(v) = val;
    }
    else
    {
        set_tuple_item_<cidx + 1>(v, idx, val);
    }
}

template <typename T, typename V>
void set_tuple_item(T& v, int index, V val)
{
    set_tuple_item_<0>(v, index, val);
}

#endif // __PYSTL_TUPLE_H_INCLUDE__
