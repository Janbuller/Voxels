#pragma once

#include <memory>

template<typename T>
using uptr = std::unique_ptr<T>;

template<typename T>
using sptr = std::shared_ptr<T>;

template<typename T, typename... Args>
constexpr uptr<T> MkUptr(Args &&...args) {
    return std::make_unique<T>(std::forward<Args>(args)...);
}

template<typename T, typename... Args>
constexpr sptr<T> MkSptr(Args &&...args) {
    return std::make_shared<T>(std::forward<Args>(args)...);
}
