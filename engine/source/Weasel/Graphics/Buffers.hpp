#pragma once

#include "Weasel/Graphics/RenderUtils.hpp"

namespace Weasel {
    struct VertexBuffer {
        u32 BufferID;
        u32 VertexCount;
    };

    struct IndexBuffer {
        u32 BufferID;
        u32 IndexCount;
    };
}