#pragma once

#include <cstddef>
#include <string>

namespace avu
{

template <class T>
size_t blob_size(T&);

// -----------------------------------------------------------------------------

template <size_t Pos = 0, class Blob, class Arg, class... Args>
bool unmarshal_impl(std::string& msg, Blob& blob, Arg& x, Args&... rest);

template <size_t Pos = 0, class Blob>
bool unmarshal_impl(std::string& msg, Blob& blob);

// -----------------------------------------------------------------------------

template <class To, class From>
bool can_cast(From&);

template <class To, class From>
To cast(From&);

// -----------------------------------------------------------------------------

template <class BlobItem>
std::string blob_item_type_name(BlobItem&);

} // namespace avu
