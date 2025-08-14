#pragma once
#include "../Specification.h"

namespace rendell {
class OpenGLSpecification : public Specification {
public:
    void setViewport(int x, int y, int width, int height, int windowWidth,
                     int windowHeight) override;
    void setClearBits(uint32_t clearBits) override;
    void clear() override;
    void clearColor(float r, float g, float b, float a) const override;

    void setPixelUnpackAlignment(int param) const override;

    void startScissors(int x, int y, int width, int height) const override;
    void endScissors() const override;

    void drawLineArrays(uint32_t firstIndex, uint32_t length) const override;
    void drawLineArraysInstanced(uint32_t firstIndex, uint32_t length,
                                 uint32_t instanceCount) const override;
    void drawLineElements(uint32_t primitiveCount) const override;
    void drawLineElementsInstanced(uint32_t primitiveCount, uint32_t instanceCount) const override;

    void drawTriangleArrays(uint32_t firstIndex, uint32_t length) const override;
    void drawTriangleArraysInstanced(uint32_t firstIndex, uint32_t length,
                                     uint32_t instanceCount) const override;
    void drawTriangleElements(uint32_t primitiveCount) const override;
    void drawTriangleElementsInstanced(uint32_t primitiveCount,
                                       uint32_t instanceCount) const override;

    void drawTriangleStripArrays(uint32_t firstIndex, uint32_t length) const override;
    void drawTriangleStripArraysInstanced(uint32_t firstIndex, uint32_t length,
                                          uint32_t instanceCount) const override;
    void drawTriangleStripElements(uint32_t primitiveCount) const override;
    void drawTriangleStripElementsInstanced(uint32_t primitiveCount,
                                            uint32_t instanceCount) const override;
};
} // namespace rendell