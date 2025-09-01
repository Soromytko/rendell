#pragma once
#include <memory>

#define RENDELL_USE_RAII(ClassName)                                                                \
    using ClassName##SharedPtr = std::shared_ptr<ClassName>;                                       \
    using ClassName##WeakPtr = std::weak_ptr<ClassName>;                                           \
    using ClassName##UniquePtr = std::unique_ptr<ClassName>;

#define RENDELL_USE_RAII_FACTORY(ClassName)                                                        \
    RENDELL_USE_RAII(ClassName)                                                                    \
    template <typename... Args> inline ClassName##SharedPtr make##ClassName(Args &&...args) {      \
        return std::make_shared<ClassName>(std::forward<Args>(args)...);                           \
    }                                                                                              \
    template <typename... Args>                                                                    \
    inline ClassName##UniquePtr makeUnique##ClassName(Args &&...args) {                            \
        return std::make_unique<ClassName>(std::forward<Args>(args)...);                           \
    }
