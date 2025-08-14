#include "OpenGLSpecification.h"
#include "OpenGLIndexBuffer.h"
#include "OpenGLShaderBuffer.h"
#include "OpenGLShaderProgram.h"
#include "OpenGLTexture2D.h"
#include "OpenGLTexture2DArray.h"
#include "OpenGLUniformBuffer.h"
#include "OpenGLVertexArray.h"
#include "OpenGLVertexBuffer.h"
#include <glad/glad.h>

namespace rendell {
static uint32_t s_viewportWidth{0};
static uint32_t s_viewportHeight{0};

void OpenGLSpecification::setViewport(int x, int y, int width, int height, int windowWidth,
                                      int windowHeight) {
    s_viewportWidth = width;
    s_viewportHeight = height;

    y = windowHeight - y - height;
    glViewport(x, y, width, height);
}

void OpenGLSpecification::setClearBits(uint32_t clearBits) {
    _clearBits = 0;
    _clearBits |= (clearBits & colorBufferBit) ? GL_COLOR_BUFFER_BIT : 0;
    _clearBits |= (clearBits & depthBufferBit) ? GL_DEPTH_BUFFER_BIT : 0;
}

void OpenGLSpecification::clear() {
    glClear(_clearBits);
}

void OpenGLSpecification::clearColor(float r, float g, float b, float a) const {
    glClearColor(r, g, b, a);
}

void OpenGLSpecification::setPixelUnpackAlignment(int param) const {
    glPixelStorei(GL_UNPACK_ALIGNMENT, param);
}

void OpenGLSpecification::startScissors(int x, int y, int width, int height) const {
    // Set the origin to the center for consistency.
    x = x + (s_viewportWidth - width) / 2;
    y = y + (s_viewportHeight - height) / 2;

    glEnable(GL_SCISSOR_TEST);
    glScissor(x, y, width, height);
}

void OpenGLSpecification::endScissors() const {
    glDisable(GL_SCISSOR_TEST);
}

void OpenGLSpecification::drawLineArrays(uint32_t firstIndex, uint32_t length) const {
    glDrawArrays(GL_LINES, firstIndex, length);
}

void OpenGLSpecification::drawLineArraysInstanced(uint32_t firstIndex, uint32_t length,
                                                  uint32_t instanceCount) const {
    glDrawArraysInstanced(GL_LINES, firstIndex, length, instanceCount);
}

void OpenGLSpecification::drawLineElements(uint32_t primitiveCount) const {
    glDrawElements(GL_LINES, primitiveCount, GL_UNSIGNED_INT, 0);
}

void OpenGLSpecification::drawLineElementsInstanced(uint32_t primitiveCount,
                                                    uint32_t instanceCount) const {
    glDrawElementsInstanced(GL_LINES, primitiveCount, GL_UNSIGNED_INT, 0, instanceCount);
}

void OpenGLSpecification::drawTriangleArrays(uint32_t firstIndex, uint32_t length) const {
    glDrawArrays(GL_TRIANGLES, firstIndex, length);
}

void OpenGLSpecification::drawTriangleArraysInstanced(uint32_t firstIndex, uint32_t length,
                                                      uint32_t instanceCount) const {
    glDrawArraysInstanced(GL_TRIANGLES, firstIndex, length, instanceCount);
}

void OpenGLSpecification::drawTriangleElements(uint32_t primitiveCount) const {
    glDrawElements(GL_TRIANGLES, primitiveCount, GL_UNSIGNED_INT, 0);
}

void OpenGLSpecification::drawTriangleElementsInstanced(uint32_t primitiveCount,
                                                        uint32_t instanceCount) const {
    glDrawElementsInstanced(GL_TRIANGLES, primitiveCount, GL_UNSIGNED_INT, 0, instanceCount);
}

void OpenGLSpecification::drawTriangleStripArrays(uint32_t firstIndex, uint32_t length) const {
    glDrawArrays(GL_TRIANGLE_STRIP, firstIndex, length);
}

void OpenGLSpecification::drawTriangleStripArraysInstanced(uint32_t firstIndex, uint32_t length,
                                                           uint32_t instanceCount) const {
    glDrawArraysInstanced(GL_TRIANGLE_STRIP, firstIndex, length, instanceCount);
}

void OpenGLSpecification::drawTriangleStripElements(uint32_t primitiveCount) const {
    glDrawElements(GL_TRIANGLE_STRIP, primitiveCount, GL_UNSIGNED_INT, 0);
}

void OpenGLSpecification::drawTriangleStripElementsInstanced(uint32_t primitiveCount,
                                                             uint32_t instanceCount) const {
    glDrawElementsInstanced(GL_TRIANGLE_STRIP, primitiveCount, GL_UNSIGNED_INT, 0, instanceCount);
}

} // namespace rendell
