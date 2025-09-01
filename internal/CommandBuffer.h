#pragma once
#include <atomic>
#include <mutex>
#include <vector>
#include <raii.h>

namespace rendell {
class CommandBuffer final {
public:
    using data_t = uint8_t;
    using RawBufferId = int;

    CommandBuffer(size_t capacity = 1024, size_t threadCount = 10);
    ~CommandBuffer();

    size_t getSize() const;

    void setThreadCount(size_t count);

    bool write(const data_t *data, size_t size);
    bool read(data_t *data, size_t size);

    template <typename T> bool write(T value) {
        const data_t *data = reinterpret_cast<const data_t *>(&value);
        write(data, sizeof(value));
    }

    RawBufferId startRawWriting();
    bool writeRaw(RawBufferId rawWritingId, const data_t *data, size_t size);
    bool commitRawWriting(RawBufferId rawBufferId);

private:
    bool isFull() const;

    void setWriteCursorPosition(size_t value);
    void setReadCursorPosition(size_t value);

    void writeData(const data_t *data, size_t size, size_t startIndex);
    void readData(data_t *data, size_t size, size_t startIndex);

    data_t *_data;
    size_t _capacity;

    struct RawBuffer final {
        std::atomic<bool> isBusy{false};
        data_t *data;
        size_t currentSize{0};

        inline void release() { delete[] data; }
    };

    std::vector<RawBuffer> _rawBuffers{};

    std::atomic<size_t> _writeCursorPosition{0};
    std::atomic<size_t> _readCursorPosition{0};
    std::atomic<int> _ringNumber{0};

    std::mutex _writeMutex;
    std::mutex _readMutex;
    std::mutex _rawWritingMutex;
};
RENDELL_USE_RAII_FACTORY(CommandBuffer)
}; // namespace rendell
