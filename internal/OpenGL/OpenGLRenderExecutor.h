#pragma once
#include "Buffers/ByteBuffer.h"
#include <DrawCallState.h>

namespace rendell {
class OpenGLShaderProgram;
class OpenGLVertexArray;

class OpenGLRenderExecutor final {
public:
    void execute(const DrawCallStateList &drawCallStateList, const ByteBuffer &uniformBuffer,
                 const ByteBuffer &commandBuffer);

private:
    OpenGLShaderProgram *processShaderProgram(const DrawCallState &drawCallState);
    OpenGLVertexArray *processVertexAssembly(const DrawCallState &drawCallState);

    void setUniforms(const DrawCallState &drawCallState, const ByteBuffer &uniformBuffer,
                     OpenGLShaderProgram *shaderProgram);
    void executeCommands(const DrawCallState &drawCallState, const ByteBuffer &commandBuffer,
                         OpenGLShaderProgram *shaderProgram);
    void draw(const DrawCallState &drawCallState, OpenGLVertexArray *vertexArray);

    void updateScissorsState();
    void setScissorsActivity(bool active);

    struct Rect {
        uint32_t x;
        uint32_t y;
        uint32_t width;
        uint32_t height;

        bool operator==(const Rect &other) const {
            return x == other.x && y == other.y && width == other.width && height == other.height;
        }

        bool operator!=(const Rect &other) const { return !(*this == other); }
    };

    bool setViewport(Rect newViewport);
    bool setScissors(Rect newScissors, bool isPermanently = false);

    Rect _viewport{};
    Rect _scissors{};

    bool _isScissorsUsed = false;
    bool _isScissorsActive = false;
};
} // namespace rendell