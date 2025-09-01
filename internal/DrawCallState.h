#pragma once
#include <rendell/ResourceId.h>
#include <vector>

namespace rendell {
struct DrawCallState final {
    void reset() { vertexBufferCount = 0; }

    //void addVertexBuffer(VertexBufferId vertexBufferId) {
    //    if (vertexBufferCount >= vertexBuffers.size()) {
    //        vertexBuffers.resize(vertexBufferCount + 1);
    //    }
    //    vertexBuffers[vertexBufferCount++] = vertexBufferId;
    //}

    ShaderProgramId shaderProgramId;
    //IndexBufferId indexBufferId;
    //std::vector<VertexBufferId> vertexBuffers{5};
    VertexBufferId vertexBuffer;
    VertexArrayBufferId vertexArrayBuffer;
    uint16_t uniformBufferIndex;
    uint16_t vertexBufferCount{0};
};
} // namespace rendell
