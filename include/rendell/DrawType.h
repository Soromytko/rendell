#pragma once

namespace rendell {
enum class DrawMode {
    Arrays,
    ArraysInstanced,
    Elements,
    ElementsInstanced,
};

enum class PrimitiveTopology {
    Triangles,
    TriangleStrip,
    TriangleFan,
    Lines,
    LineStrip,
    Points,
};
} // namespace rendell