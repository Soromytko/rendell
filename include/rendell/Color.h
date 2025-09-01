#pragma once
#include <string>
#include <string_view>

namespace rendell {
struct Color final {
    float r;
    float g;
    float b;
    float a;

    Color(float r, float g, float b, float a = 1.0f);
    Color(std::string_view hex);

    std::string getHex() const;

    void setHex(std::string_view hex);

    constexpr bool operator==(const Color &other) const = default;

    static inline Color white() { return Color(1.0f, 1.0f, 1.0f, 1.0f); }

    static inline Color black() { return Color(0.0f, 0.0f, 0.0f, 1.0f); }

    static inline Color red() { return Color(1.0f, 0.0f, 0.0f, 1.0f); }

    static inline Color green() { return Color(0.0f, 1.0f, 0.0f, 1.0f); }

    static inline Color blue() { return Color(0.0f, 0.0f, 1.0f, 1.0f); }

    static inline Color yellow() { return Color(1.0f, 1.0f, 0.0f, 1.0f); }

    static inline Color magenta() { return Color(1.0f, 0.0f, 1.0f, 1.0f); }

    static inline Color cyan() { return Color(0.0f, 1.0f, 1.0f, 1.0f); }

    static inline Color pink() { return Color(1.0f, 0.4f, 0.7f, 1.0f); }
};
} // namespace rendell
