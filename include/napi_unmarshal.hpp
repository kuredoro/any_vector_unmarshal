#pragma once

#include <string>
#include <cstddef>
#include <chrono>

#include "avu/avu_fwd.hpp"
#include <napi.h>
#include <type_traits>

namespace avu
{

template <>
inline size_t blob_size(const Napi::CallbackInfo& info) { return info.Length(); }

template <>
inline size_t blob_size(Napi::CallbackInfo& info) { return info.Length(); }

// -----------------------------------------------------------------------------

template <>
inline bool can_cast<int32_t>(const Napi::Value& x)
{
    return x.IsNumber();
}

template <>
inline bool can_cast<int64_t>(const Napi::Value& x)
{
    return x.IsNumber();
}

template <>
inline bool can_cast<uint32_t>(const Napi::Value& x)
{
    return x.IsNumber();
}

template <>
inline bool can_cast<float>(const Napi::Value& x)
{
    return x.IsNumber();
}

template <>
inline bool can_cast<double>(const Napi::Value& x)
{
    return x.IsNumber();
}

template <>
inline bool can_cast<std::string>(const Napi::Value& x)
{
    return x.IsString();
}

template <>
inline bool can_cast<std::u16string>(const Napi::Value& x)
{
    return x.IsString();
}

template <>
inline bool can_cast<bool>(const Napi::Value& x)
{
    return x.IsBoolean();
}
template <>
bool can_cast<std::chrono::microseconds>(const Napi::Value& x);

template <>
inline bool can_cast<std::chrono::microseconds>(const Napi::Value& x)
{
    return x.IsNumber();
}

// -----------------------------------------------------------------------------

template <>
int32_t cast<int32_t>(const Napi::Value& x)
{
    return x.As<Napi::Number>().Int32Value();
}

template <>
int64_t cast<int64_t>(const Napi::Value& x)
{
    return x.As<Napi::Number>().Int64Value();
}

template <>
uint32_t cast<uint32_t>(const Napi::Value& x)
{
    return x.As<Napi::Number>().Uint32Value();
}

template <>
float cast<float>(const Napi::Value& x)
{
    return x.As<Napi::Number>().FloatValue();
}

template <>
double cast<double>(const Napi::Value& x)
{
    return x.As<Napi::Number>().DoubleValue();
}

template <>
std::string cast<std::string>(const Napi::Value& x)
{
    return x.As<Napi::String>().Utf8Value();
}

template <>
std::u16string cast<std::u16string>(const Napi::Value& x)
{
    return x.As<Napi::String>().Utf16Value();
}

template <>
bool cast<bool>(const Napi::Value& x)
{
    return x.As<Napi::Boolean>().Value();
}

template <>
std::chrono::microseconds cast<std::chrono::microseconds>(const Napi::Value& x)
{
    return std::chrono::microseconds(x.As<Napi::Number>().Int64Value());
}

// -----------------------------------------------------------------------------

template <>
inline std::string blob_item_type_name(const Napi::Value& item)
{
    if (item.IsNumber())
        return "Number";
    else if (item.IsString())
        return "String";
    else if (item.IsBoolean())
        return "Boolean";
    else if (item.IsObject())
        return "Object";
    else if (item.IsArray())
        return "Array";
    else if (item.IsTypedArray())
        return "TypedArray";
    else if (item.IsUndefined())
        return "Undefined";
    else if (item.IsArrayBuffer())
        return "ArrayBuffer";
    else if (item.IsDataView())
        return "DataView";
    else if (item.IsDate())
        return "Date";
    else if (item.IsExternal())
        return "External";
    else if (item.IsFunction())
        return "Function";
    else if (item.IsPromise())
        return "Promise";
    else if (item.IsSymbol())
        return "Symbol";

    return "???";
}

} // namespace avu


#include "avu/avu.hpp"
