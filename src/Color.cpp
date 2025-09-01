#include <rendell/Color.h>

#include <algorithm>
#include <cstdint>
#include <iomanip>
#include <sstream>
#include <stdexcept>

namespace rendell {
Color::Color(float r, float g, float b, float a)
    : r(r)
    , g(g)
    , b(b)
    , a(a) {
}

Color::Color(std::string_view hex) {
    setHex(hex);
}

std::string Color::getHex() const {
    auto toInt = [](float c) {
        return static_cast<int>(std::clamp(c, 0.0f, 1.0f) * 255.0f + 0.5f);
    };

    std::ostringstream ss;
    ss << "#" << std::uppercase << std::hex << std::setfill('0') << std::setw(2) << toInt(r)
       << std::setw(2) << toInt(g) << std::setw(2) << toInt(b);

    if (a < 1.0f) {
        ss << std::setw(2) << toInt(a);
    }
    return ss.str();
}

void Color::setHex(std::string_view hex) {
    if (hex.size() != 7 && hex.size() != 9) {
        throw std::invalid_argument("Invalid hex color format");
    }
    auto fromHex = [&](size_t pos) -> float {
        return static_cast<float>(std::stoi(std::string(hex.substr(pos, 2)), nullptr, 16)) / 255.0f;
    };
    r = fromHex(1);
    g = fromHex(3);
    b = fromHex(5);
    a = (hex.size() == 9) ? fromHex(7) : 1.0f;
}

} // namespace rendell