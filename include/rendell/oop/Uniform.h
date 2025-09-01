#pragma once
#include <rendell/DataType.h>
#include <rendell/ResourceId.h>
#include <rendell/rendell.h>

#include <cassert>
#include <string>

namespace rendell {
bool isValid(UniformId uniformId);
UniformId createUniform(const std::string &name, UniformType type);

namespace oop {
template <typename T> class Uniform {
public:
    Uniform(std::string name, UniformType type)
        : _name(std::move(name))
        , _type(type) {
        assert(!_name.empty());
        _id = static_cast<T>(rendell::createUniform(_name, type));
    }

    virtual ~Uniform() { rendell::destroy(_id); }

    inline const std::string &getName() const { return _name; }

    inline T getId() const { return _id; }

    inline bool isValid() const { return rendell::isValid(_id); }

protected:
    T _id;
    std::string _name;
    UniformType _type;
};

class Int1Uniform final : public Uniform<UniformInt1Id> {
public:
    Int1Uniform(std::string name)
        : Uniform(std::move(name), UniformType::int1) {}

    inline void set(int value) { rendell::setUniform(_id, value); }
};

class Int2Uniform final : public Uniform<UniformInt2Id> {
public:
    Int2Uniform(std::string name)
        : Uniform(std::move(name), UniformType::int2) {}

    inline void set(int val1, int val2) { rendell::setUniform(_id, val1, val2); }
};

class Int3Uniform final : public Uniform<UniformInt3Id> {
public:
    Int3Uniform(std::string name)
        : Uniform(std::move(name), UniformType::int3) {}

    inline void set(int val1, int val2, int val3) { rendell::setUniform(_id, val1, val2, val3); }
};

class Int4Uniform final : public Uniform<UniformInt4Id> {
public:
    Int4Uniform(std::string name)
        : Uniform(std::move(name), UniformType::int4) {}

    inline void set(int val1, int val2, int val3, int val4) {
        rendell::setUniform(_id, val1, val2, val3, val4);
    }
};

class Float1Uniform final : public Uniform<UniformFloat1Id> {
public:
    Float1Uniform(std::string name)
        : Uniform(std::move(name), UniformType::float1) {}

    inline void set(float value) { rendell::setUniform(_id, value); }
};

class Float2Uniform final : public Uniform<UniformFloat2Id> {
public:
    Float2Uniform(std::string name)
        : Uniform(std::move(name), UniformType::float2) {}

    inline void set(float val1, float val2) { rendell::setUniform(_id, val1, val2); }
};

class Float3Uniform final : public Uniform<UniformFloat3Id> {
public:
    Float3Uniform(std::string name)
        : Uniform(std::move(name), UniformType::float3) {}

    inline void set(float val1, float val2, float val3) {
        rendell::setUniform(_id, val1, val2, val3);
    }
};

class Float4Uniform final : public Uniform<UniformFloat4Id> {
public:
    Float4Uniform(std::string name)
        : Uniform(std::move(name), UniformType::float4) {}

    inline void set(float val1, float val2, float val3, float val4) {
        rendell::setUniform(_id, val1, val2, val3, val4);
    }
};

class Mat4Uniform final : public Uniform<UniformMat4Id> {
public:
    Mat4Uniform(std::string name)
        : Uniform(std::move(name), UniformType::mat4) {}

    inline void set(const float *data) { rendell::setUniform(_id, data); }
};

class Sampler2DUniform final : public Uniform<UniformSampler2DId> {
public:
    Sampler2DUniform(std::string name)
        : Uniform(std::move(name), UniformType::sampler2D) {}
};

// mat4, sampler2D, sampler2DArray,
} // namespace oop
} // namespace rendell