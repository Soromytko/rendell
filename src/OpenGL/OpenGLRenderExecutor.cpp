#include <OpenGL/OpenGLRenderExecutor.h>

#include <Command.h>
#include <OpenGL/OpenGLResourceStorage.h>
#include <logging.h>
#include <rendell/consts.h>
#include <rendell/hash.h>

namespace rendell {
static ShaderProgramId s_currentShaderProgramId;
static VertexAssemblyId s_currentVertexAssemblyId;
} // namespace rendell

namespace rendell {
void OpenGLRenderExecutor::execute(const DrawCallStateList &drawCallStateList,
                                   const ByteBuffer &uniformBuffer,
                                   const ByteBuffer &commandBuffer) {
    for (const DrawCallState &drawCallState : drawCallStateList) {
        // ShaderProgram
        OpenGLShaderProgram *shaderProgram = processShaderProgram(drawCallState);
        if (!shaderProgram) {
            // TODO: warning or error
            continue;
        }

        // VertexAssembly
        OpenGLVertexArray *vertexArray = processVertexAssembly(drawCallState);
        if (!vertexArray) {
            // TODO: warning or error;
            continue;
        }

        // Uniforms
        setUniforms(drawCallState, uniformBuffer, shaderProgram);

        // Commands
        executeCommands(drawCallState, commandBuffer, shaderProgram);

        // Draw
        draw(drawCallState, vertexArray);
    }
}

OpenGLShaderProgram *
OpenGLRenderExecutor::processShaderProgram(const DrawCallState &drawCallState) {
    OpenGLShaderProgram *shaderProgram = shaderProgram =
        getShaderProgramStorage().find(drawCallState.shaderProgramId.index).get();
    if (drawCallState.shaderProgramId != s_currentShaderProgramId) {
        shaderProgram->bind();
        s_currentShaderProgramId = drawCallState.shaderProgramId;
    }
    return shaderProgram;
}

OpenGLVertexArray *OpenGLRenderExecutor::processVertexAssembly(const DrawCallState &drawCallState) {
    OpenGLVertexArray *vertexArray =
        getVertexArrayBufferStorage().find(drawCallState.vertexAssemblyId.index).get();
    if (drawCallState.vertexAssemblyId != s_currentVertexAssemblyId) {
        vertexArray->bind();
        s_currentVertexAssemblyId = drawCallState.vertexAssemblyId;
    }
    return vertexArray;
}

void OpenGLRenderExecutor::setUniforms(const DrawCallState &drawCallState,
                                       const ByteBuffer &uniformBuffer,
                                       OpenGLShaderProgram *shaderProgram) {
    if (drawCallState.uniformBufferSize == 0) {
        return;
    }

    ByteBufferReader bufferReader(uniformBuffer, drawCallState.uniformBufferOffset);
    while (bufferReader.getOffset() - drawCallState.uniformBufferOffset <
           drawCallState.uniformBufferSize) {
        const UniformType uniformType = bufferReader.read<UniformType>();
        const UniformId uniformId = bufferReader.read<UniformId>();
        const size_t hashedUniformId = hash(uniformId);
        const std::string &uniformName = getUniformName(hashedUniformId);
        const GLint uniformIndex = shaderProgram->getUniformIndex(uniformName);
        assert(uniformIndex >= 0);
        switch (uniformType) {
        case UniformType::int1: {
            const int value = bufferReader.read<int>();
            shaderProgram->setUniformInt1(uniformIndex, value);
        } break;
        case UniformType::int2: {
            const int *values = bufferReader.readArrayAsRef<int>(2);
            shaderProgram->setUniformInt2(uniformIndex, values[0], values[1]);
        } break;
        case UniformType::int3: {
            const int *values = bufferReader.readArrayAsRef<int>(3);
            shaderProgram->setUniformInt3(uniformIndex, values[0], values[1], values[2]);
        } break;
        case UniformType::int4: {
            const int *values = bufferReader.readArrayAsRef<int>(4);
            shaderProgram->setUniformInt4(uniformIndex, values[0], values[1], values[3], values[3]);
        } break;
        case UniformType::float1: {
            const float value = bufferReader.read<float>();
            shaderProgram->setUniformFloat1(uniformIndex, value);
        } break;
        case UniformType::float2: {
            const float *values = bufferReader.readArrayAsRef<float>(2);
            shaderProgram->setUniformFloat2(uniformIndex, values[0], values[1]);
        } break;
        case UniformType::float3: {
            const float *values = bufferReader.readArrayAsRef<float>(3);
            shaderProgram->setUniformFloat3(uniformIndex, values[0], values[1], values[2]);
        } break;
        case UniformType::float4: {
            const float *values = bufferReader.readArrayAsRef<float>(4);
            shaderProgram->setUniformFloat4(uniformIndex, values[0], values[1], values[2],
                                            values[3]);
        } break;
        case UniformType::mat4: {
            const float *mat = bufferReader.readArrayAsRef<float>(16);
            shaderProgram->setUniformMat4(uniformIndex, mat);
        } break;
        default: {
            RENDELL_CRITICAL("Unknown uniform type {}", static_cast<int>(uniformType));
            assert(false);
        }
        }
    }
}

static GLbitfield getGLClearBits(bitfield clearBits) {
    GLbitfield result = 0;
    result |= (clearBits & c::colorBufferBit) ? GL_COLOR_BUFFER_BIT : 0;
    result |= (clearBits & c::depthBufferBit) ? GL_DEPTH_BUFFER_BIT : 0;
    return result;
}

void OpenGLRenderExecutor::executeCommands(const DrawCallState &drawCallState,
                                           const ByteBuffer &commandBuffer,
                                           OpenGLShaderProgram *shaderProgram) {
    ByteBufferReader bufferReader(commandBuffer, drawCallState.commandBufferOffset);
    while (bufferReader.getOffset() - drawCallState.commandBufferOffset <
           drawCallState.commandBufferSize) {
        assert(bufferReader.canRead(sizeof(RenderCmdType), alignof(RenderCmdType)));
        const RenderCmdType cmdType = bufferReader.read<RenderCmdType>();
        switch (cmdType) {
        case RenderCmdType::clearColorCmdType: {
            assert(bufferReader.canRead(sizeof(ClearColorCmdData), alignof(ClearColorCmdData)));
            const ClearColorCmdData cmdData = bufferReader.read<ClearColorCmdData>();
            glClearColor(cmdData.r, cmdData.g, cmdData.b, cmdData.a);
        } break;
        case RenderCmdType::setViewportCmdType: {
            assert(bufferReader.canRead(sizeof(SetViewportCmdData), alignof(SetViewportCmdData)));
            const SetViewportCmdData cmdData = bufferReader.read<SetViewportCmdData>();
            const Rect newViewport{
                .x = cmdData.x,
                .y = cmdData.y,
                .width = cmdData.width,
                .height = cmdData.height,
            };
            if (setViewport(newViewport)) {
                if (_isScissorsUsed) {
                    // Reapply the current scissor rectangle to match the new viewport.
                    setScissors(_scissors, true);
                }
            }
        } break;
        case RenderCmdType::setScissorsCmdType: {
            assert(bufferReader.canRead(sizeof(SetScissorsCmdData), alignof(SetScissorsCmdData)));
            const SetScissorsCmdData cmdData = bufferReader.read<SetScissorsCmdData>();
            const Rect scissors{
                .x = cmdData.x,
                .y = cmdData.y,
                .width = cmdData.width,
                .height = cmdData.height,
            };
            setScissors(scissors);
        } break;
        case RenderCmdType::useShaderBufferCmdType: {
            assert(bufferReader.canRead(sizeof(UseShaderBufferCmdData),
                                        alignof(UseShaderBufferCmdData)));
            const UseShaderBufferCmdData cmdData = bufferReader.read<UseShaderBufferCmdData>();
            OpenGLShaderBuffer *shaderBuffer =
                getShaderBufferStorage().find(cmdData.id.index).get();
            assert(shaderBuffer);
            shaderBuffer->bind(cmdData.binding);
        } break;
        case RenderCmdType::useUniformBufferCmdType: {
            assert(bufferReader.canRead(sizeof(UseUniformBufferCmdData),
                                        alignof(UseUniformBufferCmdData)));
            const UseUniformBufferCmdData cmdData = bufferReader.read<UseUniformBufferCmdData>();
            OpenGLUniformBuffer *uniformBuffer =
                getUniformBufferStorage().find(cmdData.id.index).get();
            assert(uniformBuffer);
            uniformBuffer->bind(cmdData.binding);
        } break;
        case RenderCmdType::setTexture2DCmdType: {
            assert(bufferReader.canRead(sizeof(SetTexture2DCmdData), alignof(SetTexture2DCmdData)));
            const SetTexture2DCmdData cmdData = bufferReader.read<SetTexture2DCmdData>();
            // Texture
            OpenGLTexture2D *texture = getTexture2DStorage().find(cmdData.textureId.index).get();
            assert(texture);
            texture->bind(static_cast<GLuint>(cmdData.stage));
            // Sampler
            const std::string &samplerName =
                getUniformName(hash(static_cast<UniformId>(cmdData.samplerId)));
            assert(shaderProgram);
            const GLint uniformIndex = shaderProgram->getUniformIndex(samplerName);
            assert(uniformIndex >= 0);
            shaderProgram->setUniformInt1(uniformIndex, static_cast<int>(cmdData.stage));
        } break;
        case RenderCmdType::setTexture2DArrayCmdType: {
            assert(bufferReader.canRead(sizeof(SetTexture2DArrayCmdData),
                                        alignof(SetTexture2DArrayCmdData)));
            const SetTexture2DArrayCmdData cmdData = bufferReader.read<SetTexture2DArrayCmdData>();
            // Texture
            OpenGLTexture2DArray *texture =
                getTexture2DArrayStorage().find(cmdData.textureId.index).get();
            assert(texture);
            texture->bind(static_cast<GLuint>(cmdData.stage));
            // Sampler
            const std::string &samplerName =
                getUniformName(hash(static_cast<UniformId>(cmdData.samplerId)));
            assert(shaderProgram);
            const GLint uniformIndex = shaderProgram->getUniformIndex(samplerName);
            assert(uniformIndex >= 0);
            shaderProgram->setUniformInt1(uniformIndex, static_cast<int>(cmdData.stage));
        } break;
        default:
            RENDELL_CRITICAL("Unknown render command {}", static_cast<int>(cmdType));
            assert(false);
        }
    }
}

static GLenum getGLMode(PrimitiveTopology primitiveTopology) {
    switch (primitiveTopology) {
    case PrimitiveTopology::Triangles:
        return GL_TRIANGLES;
    case PrimitiveTopology::TriangleStrip:
        return GL_TRIANGLE_STRIP;
    case PrimitiveTopology::TriangleFan:
        return GL_TRIANGLE_FAN;
    case PrimitiveTopology::Lines:
        return GL_LINES;
    case PrimitiveTopology::LineStrip:
        return GL_LINE_STRIP;
    case PrimitiveTopology::Points:
        return GL_POINTS;
    }

    // TODO: debug error?
    return GL_TRIANGLES;
}

void OpenGLRenderExecutor::draw(const DrawCallState &drawCallState,
                                OpenGLVertexArray *vertexArray) {
    updateScissorsState();

    glClear(getGLClearBits(drawCallState.clearBits));

    const GLenum glMode = getGLMode(drawCallState.primitiveTopology);
    const int count = static_cast<int>(vertexArray->getIndexCount());
    switch (drawCallState.drawMode) {
    case DrawMode::Arrays: {
        glDrawArrays(glMode, 0, count);
    } break;
    case DrawMode::ArraysInstanced: {
        glDrawArraysInstanced(glMode, 0, count, static_cast<int>(drawCallState.instanceCount));
    } break;
    case DrawMode::Elements: {
        glDrawElements(glMode, count, GL_UNSIGNED_INT, 0);
    } break;
    case DrawMode::ElementsInstanced: {
        glDrawElementsInstanced(glMode, count, GL_UNSIGNED_INT, 0,
                                static_cast<int>(drawCallState.instanceCount));
    } break;
    }
}

void OpenGLRenderExecutor::updateScissorsState() {
    setScissorsActivity(_isScissorsUsed);
    _isScissorsUsed = false;
}

void OpenGLRenderExecutor::setScissorsActivity(bool active) {
    if (!_isScissorsActive != active) {
        if (active) {
            glEnable(GL_SCISSOR_TEST);
        } else {
            glDisable(GL_SCISSOR_TEST);
        }
        _isScissorsActive = active;
    }
}

bool OpenGLRenderExecutor::setViewport(Rect newViewport) {
    if (_viewport == newViewport) {
        return false;
    }
    _viewport = newViewport;
    glViewport(static_cast<GLint>(_viewport.x), static_cast<GLint>(_viewport.y),
               static_cast<GLsizei>(_viewport.width), static_cast<GLsizei>(_viewport.height));
    return true;
}

bool OpenGLRenderExecutor::setScissors(Rect newScissors, bool isPermanently) {
    if (!isPermanently) {
        if (_scissors == newScissors) {
            return false;
        }
    }
    _scissors = newScissors;
    // Set the origin to the center for consistency.
    const int x = _scissors.x + (_viewport.width - _scissors.width) / 2;
    const int y = _scissors.y + (_viewport.height - _scissors.height) / 2;

    glScissor(static_cast<GLint>(x), static_cast<GLint>(y), static_cast<GLsizei>(_scissors.width),
              static_cast<GLsizei>(_scissors.height));
    _isScissorsUsed = true;
    return true;
}

} // namespace rendell