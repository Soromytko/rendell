#pragma once
#include "Buffers/ByteBuffer.h"
#include "Buffers/ByteRingBuffer.h"
#include "Command.h"
#include "raii.h"

#include <cassert>

namespace rendell {
class ResourceCommandBuffer final {
public:
    using data_t = uint8_t;

    ResourceCommandBuffer() = default;
    ~ResourceCommandBuffer() = default;

    inline size_t getLength() const { return _buffer.getLength(); }

    inline bool isEmpty() const { return _buffer.isEmpty(); }

    inline bool canRead(size_t size) const { return false; }

    bool readCmdType(CmdType &type) {
        ByteBufferReader bufferReader(_buffer);
        if (!bufferReader.canRead(sizeof(type))) {
            return false;
        }
        bufferReader >> type;

        return true;
    }

    template <typename T> void writeCommand(CmdType type, T &command) {
        _buffer << type << command;
    }

    template <typename T> void readCmdData(T &commandData) {
        data_t *dataSource = reinterpret_cast<data_t *>(&commandData);
        _buffer >> commandData;
    }

    void reset() { _buffer.reset(); }

private:
    ByteBuffer _buffer;
};

RENDELL_USE_RAII_FACTORY(ResourceCommandBuffer)
} // namespace rendell