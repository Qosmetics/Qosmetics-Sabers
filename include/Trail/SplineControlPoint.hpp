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

    [[nodiscard]] Sombrero::FastVector3 const & NextPosition() const;
    [[nodiscard]] Sombrero::FastVector3 const & PreviousPosition() const;
    [[nodiscard]] Sombrero::FastVector3 const & NextNormal() const;
    [[nodiscard]] Sombrero::FastVector3 const & PreviousNormal() const;

    [[nodiscard]] bool IsValid() const;
    [[nodiscard]] Sombrero::FastVector3 const & GetNext2Position() const;
    [[nodiscard]] Sombrero::FastVector3 const & GetNext2Normal() const;
    [[nodiscard]] Sombrero::FastVector3 Interpolate(float localF) const;
    [[nodiscard]] Sombrero::FastVector3 InterpolateNormal(float localF) const;
    void Init(Spline* owner);
};