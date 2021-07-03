#pragma once

#include <cstddef>
#include <vector>
#include <boost/any.hpp>

#include "type_name.hpp"
#include "avu_fwd.hpp"

namespace avu
{

template <class T>
inline size_t blob_size(const std::vector<T>& vec) { return vec.size(); }

template <class T>
inline size_t blob_size(std::vector<T>& vec) { return vec.size(); }

// -----------------------------------------------------------------------------

template <class To>
bool can_cast(const boost::any& x)
{
    return true;
}

template <class To>
bool can_cast(boost::any& x)
{
    return true;
}

// -----------------------------------------------------------------------------

template <class To>
To cast(const boost::any& x)
{
    return boost::any_cast<To>(x);
}

template <class To>
To cast(boost::any& x)
{
    return boost::any_cast<To>(x);
}

// -----------------------------------------------------------------------------

template <>
inline std::string blob_item_type_name(const boost::any& item)
{
    return type_name(item.type());
}

template <>
inline std::string blob_item_type_name(boost::any& item)
{
    return type_name(item.type());
}

} // namespace avu

#include "avu.hpp"
