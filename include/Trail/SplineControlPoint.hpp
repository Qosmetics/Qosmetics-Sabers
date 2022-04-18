#pragma once

#include "sombrero/shared/Vector3Utils.hpp"

class Spline;

class SplineControlPoint
{
public:
    int ControlPointIndex = -1;
    float Dist;

    Sombrero::FastVector3 Normal;
    Sombrero::FastVector3 Position;
    int SegmentIndex = -1;
    Spline* spline;

    [[nodiscard]] SplineControlPoint* NextControlPoint() const;
    [[nodiscard]] SplineControlPoint* PreviousControlPoint() const;

    [[nodiscard]] const Sombrero::FastVector3& NextPosition() const;
    [[nodiscard]] const Sombrero::FastVector3& PreviousPosition() const;
    [[nodiscard]] const Sombrero::FastVector3& NextNormal() const;
    [[nodiscard]] const Sombrero::FastVector3& PreviousNormal() const;

    [[nodiscard]] bool IsValid() const;
    [[nodiscard]] const Sombrero::FastVector3& GetNext2Position() const;
    [[nodiscard]] const Sombrero::FastVector3& GetNext2Normal() const;
    [[nodiscard]] Sombrero::FastVector3 Interpolate(float localF) const;
    [[nodiscard]] Sombrero::FastVector3 InterpolateNormal(float localF) const;
    void Init(Spline* owner);
};