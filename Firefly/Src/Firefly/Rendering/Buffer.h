#pragma once
#include "FFLY_CORE.h"

namespace Firefly {
namespace Rendering {
struct VertexAttribute {
    enum AttrType { FLOAT = 0, FLOAT2, FLOAT3, FLOAT4, INT1, INT2, INT3, INT4 };

    VertexAttribute(const char* name, AttrType type, bool to_normalize = false)
        : Name(name), Type(type), Offset(0), ToNormalize(to_normalize) {}

    uint32 GetCount() {
        switch (Type) {
        case FLOAT:
            return 1;
        case FLOAT2:
            return 2;
        case FLOAT3:
            return 3;
        case FLOAT4:
            return 4;
        default:
            return 0;
        }
    }

    uint32 GetSize() {
        switch (Type) {
        case FLOAT:
            return 4 * 1;
        case FLOAT2:
            return 4 * 2;
        case FLOAT3:
            return 4 * 3;
        case FLOAT4:
            return 4 * 4;
        default:
            return 0;
        }
    }

    const char* Name;
    AttrType    Type;
    uint32      Offset;
    bool        ToNormalize;
};

struct AttributesDescription {
    AttributesDescription(std::vector<VertexAttribute> attributes)
        : Attributes(attributes) {
        uint32 offset = 0;
        Stride        = 0;

        for (uint i = 0; i < Attributes.size(); i++) {
            this->Attributes[i].Offset = offset;

            offset += Attributes[i].GetSize();
            this->Stride += Attributes[i].GetSize();
        }
    }

    uint32 Size() { return Attributes.size(); }

    VertexAttribute& operator[](uint32 index) { return Attributes[index]; }

    std::vector<VertexAttribute> Attributes;
    uint32                       Stride;
};

class VertexBuffer {
  public:
    VertexBuffer(float* vertices, uint32 size, std::vector<VertexAttribute> attributes);
    ~VertexBuffer() {}
    void Bind() const;
    void Unbind() const;

  private:
    uint                  m_handle;
    AttributesDescription m_layout;
};

class IndexBuffer {
  public:
    ~IndexBuffer() {}
    void Bind() const;
    void Unbind() const;
};
} // namespace Rendering

/* === FACTORY === */
namespace Factory {
namespace VertexBuffer {
Rendering::VertexBuffer* Create(float* vertices, uint32 size,
                                std::vector<Rendering::VertexAttribute> attributes);
} // namespace VertexBuffer

namespace IndexBuffer {
Rendering::IndexBuffer* Create(uint32 indices, uint32 size);
} // namespace IndexBuffer
} // namespace Factory

} // namespace Firefly