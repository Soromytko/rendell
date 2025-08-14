#pragma once
#include <cstdint>

namespace rendell {
class Specification {
public:
    virtual void setViewport(int x, int y, int width, int height, int windowWidth,
                             int windowHeight) = 0;
    virtual void setClearBits(uint32_t clearBits) = 0;
    virtual void clear() = 0;
    virtual void clearColor(float r, float g, float b, float a) const = 0;

    virtual void setPixelUnpackAlignment(int param) const = 0;

    virtual void startScissors(int x, int y, int width, int height) const = 0;
    virtual void endScissors() const = 0;

    virtual void drawLineArrays(uint32_t firstIndex, uint32_t count) const = 0;
    virtual void drawLineArraysInstanced(uint32_t firstIndex, uint32_t length,
                                         uint32_t instanceCount) const = 0;
    virtual void drawLineElements(uint32_t primitiveCount) const = 0;
    virtual void drawLineElementsInstanced(uint32_t primitiveCount,
                                           uint32_t instanceCount) const = 0;

    virtual void drawTriangleArrays(uint32_t firstIndex, uint32_t count) const = 0;
    virtual void drawTriangleArraysInstanced(uint32_t firstIndex, uint32_t length,
                                             uint32_t instanceCount) const = 0;
    virtual void drawTriangleElements(uint32_t primitiveCount) const = 0;
    virtual void drawTriangleElementsInstanced(uint32_t primitiveCount,
                                               uint32_t instanceCount) const = 0;

    virtual void drawTriangleStripArrays(uint32_t firstIndex, uint32_t length) const = 0;
    virtual void drawTriangleStripArraysInstanced(uint32_t firstIndex, uint32_t length,
                                                  uint32_t instanceCount) const = 0;
    virtual void drawTriangleStripElements(uint32_t primitiveCount) const = 0;
    virtual void drawTriangleStripElementsInstanced(uint32_t primitiveCount,
                                                    uint32_t instanceCount) const = 0;

protected:
    uint32_t _clearBits;
};
} // namespace rendell