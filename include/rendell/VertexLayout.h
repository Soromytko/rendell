#pragma once
#include "DataType.h"

#include <vector>

namespace rendell {
struct VertexLayout final {
    struct Attribute {
        uint32_t index;
        ShaderDataType type;
        uint32_t offset;
        bool normalized;
    };

    inline const std::vector<Attribute> &getAttributes() const { return _attributes; }

    inline VertexLayout &addAttribute(uint32_t index, ShaderDataType type, bool normalized,
                                      uint32_t offset) {
        _attributes.push_back({
            index,
            type,
            offset,
            normalized,
        });
        return *this;
    }

private:
    std::vector<Attribute> _attributes;
};
} // namespace rendell