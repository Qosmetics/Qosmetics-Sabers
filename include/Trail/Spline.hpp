#pragma once

#include "sombrero/shared/Vector3Utils.hpp"
#include <vector>

class SplineControlPoint;

class Spline
{
public:
    std::vector<std::shared_ptr<SplineControlPoint>> controlPoints;
    std::vector<std::shared_ptr<SplineControlPoint>> segments;
    int Granularity = 20;
    Spline();
    Spline(int preCount);

    constexpr operator bool()
    {
        return !controlPoints.empty() && !segments.empty();
    }

    void Reserve(int count);
    SplineControlPoint const* operator[](int index);
    std::vector<std::shared_ptr<SplineControlPoint>>& get_ControlPoints();
    SplineControlPoint* NextControlPoint(SplineControlPoint const &controlPoint);
    SplineControlPoint* PreviousControlPoint(SplineControlPoint const &controlPoint);

    Sombrero::FastVector3 const & NextPosition(SplineControlPoint const &controlPoint);
    Sombrero::FastVector3 const & PreviousPosition(SplineControlPoint const &controlPoint);

    Sombrero::FastVector3 const & NextNormal(SplineControlPoint const &controlPoint);
    Sombrero::FastVector3 const & PreviousNormal(SplineControlPoint const &controlPoint);

    SplineControlPoint* LenToSegment(float t, float& localF);

    static Sombrero::FastVector3 CatmulRom(const Sombrero::FastVector3& T0, const Sombrero::FastVector3& P0, const Sombrero::FastVector3& P1, const Sombrero::FastVector3& T1, float f);
    Sombrero::FastVector3 InterpolateByLen(float tl);
    Sombrero::FastVector3 InterpolateNormalByLen(float tl);
    SplineControlPoint* AddControlPoint(const Sombrero::FastVector3& pos, const Sombrero::FastVector3& up);
    void Clear();
    void RefreshSpline();

private:
    void RefreshDistance();
};