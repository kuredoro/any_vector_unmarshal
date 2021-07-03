#pragma once

#include <iostream>
#include <string>

#include "type_name.hpp"
#include "avu_fwd.hpp"

namespace avu
{

template <size_t ArgumentIndex, class Arg, class BlobItem>
void cast_error_message(std::string& msg, BlobItem& item)
{
    msg = "cannot coerce arg" + std::to_string(ArgumentIndex) + " of type "
        + blob_item_type_name(item) + " to type "
        + type_name<Arg>();
}

template <size_t ArgumentIndex, class BlobItem, class Arg>
bool unmarshal_one(std::string& msg, BlobItem& item, Arg& x)
{
    std::cout << "unmarshal_one<" << ArgumentIndex << ">\n";

    if (!can_cast<Arg>(item))
    {
        cast_error_message<ArgumentIndex, Arg>(msg, item);
        return false;
    }

    try
    {
        x = cast<Arg>(item);
    }
    catch (...)
    {
        cast_error_message<ArgumentIndex, Arg>(msg, item);
        return false;
    }

    return true;
}

template <size_t Pos, class Blob, class Arg, class... Args>
bool unmarshal_impl(std::string& msg, Blob& blob, Arg& x, Args&... rest)
{
    std::cout << "unmarshal_impl<" << Pos << ">\n";
    // We assume that blob was checked to contain at least Required number of
    // elements. Hence, if blob has run out of arguments, it means we're done.
    if (Pos >= blob_size(blob))
    {
        return true;
    }

    if (!unmarshal_one<Pos>(msg, blob[Pos], x))
    {
        return false;
    }

    return unmarshal_impl<Pos + 1>(msg, blob, rest...);
}

template <size_t Pos, class Blob>
bool unmarshal_impl(std::string& msg, Blob& blob)
{
    return true;
}

// TODO: If Required not specified, default to sizeof...(Args)
template <size_t Required, class Blob, class... Args>
std::string unmarshal(Blob& blob, Args&... args)
{
    static_assert(Required <= sizeof...(Args), "Required argument count is bigger than the number of provided arguments");

    if (blob_size(blob) < Required)
    {
        return "not enough arguments provided: got "
            + std::to_string(blob_size(blob)) + ", want at least "
            + std::to_string(Required);
    }

    std::string msg;

    unmarshal_impl(msg, blob, args...);

    return msg;
}

} // namespace avu
