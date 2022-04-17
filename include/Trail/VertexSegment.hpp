#pragma once

namespace Qosmetics::Sabers
{
    class VertexPool;
}

struct VertexSegment
{
    int VertStart = 0;
    int IndexStart = 0;
    int VertCount = 0;
    int IndexCount = 0;
    Qosmetics::Sabers::VertexPool* Pool = nullptr;

    constexpr VertexSegment(int start, int count, int istart, int icount, Qosmetics::Sabers::VertexPool* pool) : VertStart(start), IndexStart(count), VertCount(istart), IndexCount(icount), Pool(pool) {}
    constexpr VertexSegment() = default;;
};
