#pragma once

#include "sombrero/shared/FastVector3.hpp"

struct Element
{
    Sombrero::FastVector3 pointStart;
    Sombrero::FastVector3 pointEnd;
    Sombrero::FastVector3 get_pos() { return (pointStart + pointEnd) * 0.5f; }

    Element() {}
    Element(const Sombrero::FastVector3& start, const Sombrero::FastVector3& end) : pointStart(start), pointEnd(end){};
};