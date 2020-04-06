#pragma once
#include "FFLY_CORE.h"

namespace Firefly {
namespace Rendering {
struct VertexAttribute {
    enum AttrType { FLOAT = 0, FLOAT2, FLOAT3, FLOAT4, INT1, INT2, INT3, INT4 };

    VertexAttribute(const char* name, AttrType type, const bool& to_normalize = false)
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
    AttributesDescription() {}
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

    VertexAttribute& operator[](const uint32& index) { return Attributes[index]; }

    std::vector<VertexAttribute> Attributes;
    uint32                       Stride;
};

class VertexBuffer {
  public:
    VertexBuffer() {}
    ~VertexBuffer() {}

    void Bind() const;
    void Unbind() const;

    void SetAPIHandleAndLayout(const uint32&                handle,
                               const AttributesDescription& layout) {
        if (!initialized) {
            m_handle    = handle;
            m_layout    = layout;
            initialized = true;
        }
    }

    AttributesDescription GetLayout() const { return m_layout; }

  private:
    uint32                m_handle = 0;
    AttributesDescription m_layout;
    bool                  initialized = false;
};

class IndexBuffer {
  public:
    IndexBuffer() {}
    ~IndexBuffer() {}

    void Bind() const;
    void Unbind() const;

    void SetAPIHandleAndCount(const uint32& handle, const uint32 count) {
        if (!initialized) {
            m_handle    = handle;
            m_count     = count;
            initialized = true;
        }
    }

    uint32 GetVerticeCount() { return m_count; }

  private:
    uint32 m_handle    = 0;
    uint32 m_count     = 0;
    bool   initialized = false;
};
} // namespace Rendering

/* === FACTORY === */
namespace Factory {
namespace VertexBuffer {
Rendering::VertexBuffer* Create(float* vertices, const uint32& size,
                                std::vector<Rendering::VertexAttribute> attributes);
} // namespace VertexBuffer

namespace IndexBuffer {
Rendering::IndexBuffer* Create(const uint32* indices, const uint32& count);
} // namespace IndexBuffer
} // namespace Factory

} // namespace Firefly