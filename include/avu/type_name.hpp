#pragma once

#include <type_traits>
#include <typeinfo>
#ifndef _MSC_VER
#   include <cxxabi.h>
#endif
#include <memory>
#include <string>
#include <cstdlib>


namespace avu
{

/// From: https://stackoverflow.com/a/20170989/5799035
template <class T>
std::string type_name()
{
    typedef typename std::remove_reference<T>::type TR;
    std::unique_ptr<char, void(*)(void*)> own(
#ifndef _MSC_VER
        abi::__cxa_demangle(typeid(TR).name(), nullptr,
                            nullptr, nullptr),
#else
        nullptr,
#endif
        std::free);

    return own != nullptr ? own.get() : typeid(TR).name();
}

inline std::string type_name(const std::type_info& info)
{
    std::unique_ptr<char, void(*)(void*)> own(
#ifndef _MSC_VER
        abi::__cxa_demangle(info.name(), nullptr,
                            nullptr, nullptr),
#else
        nullptr,
#endif
        std::free);

    return own != nullptr ? own.get() : info.name();
}

} // namespace avu
