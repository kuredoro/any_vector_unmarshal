#pragma once

#include <string>

#include "avu/type_name.hpp"
#include "avu/avu_fwd.hpp"

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
template <int Required = -1, class Blob, class... Args>
std::string unmarshal(Blob& blob, Args&... args)
{
    static_assert(Required < 0 || Required <= sizeof...(Args), "Required argument count is bigger than the number of provided arguments");

    if (Required >= 0 && blob_size(blob) < (size_t)Required)
    {
        return "not enough arguments provided: got "
            + std::to_string(blob_size(blob)) + ", want at least "
            + std::to_string(Required);
    }

    if (Required < 0 && blob_size(blob) < sizeof...(Args))
    {
        return "not enough arguments provided: got "
            + std::to_string(blob_size(blob)) + ", want at least "
            + std::to_string(sizeof...(Args));
    }

    std::string msg;

    unmarshal_impl(msg, blob, args...);

    return msg;
}

} // namespace avu
