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

    operator bool()
    {
        return !controlPoints.empty() && !segments.empty();
    }

    void Reserve(int count);
    SplineControlPoint* operator[](int index);
    std::vector<std::shared_ptr<SplineControlPoint>>& get_ControlPoints();
    SplineControlPoint* NextControlPoint(SplineControlPoint* controlPoint);
    SplineControlPoint* PreviousControlPoint(SplineControlPoint* controlPoint);

    Sombrero::FastVector3 NextPosition(SplineControlPoint* controlPoint);
    Sombrero::FastVector3 PreviousPosition(SplineControlPoint* controlPoint);

    Sombrero::FastVector3 NextNormal(SplineControlPoint* controlPoint);
    Sombrero::FastVector3 PreviousNormal(SplineControlPoint* controlPoint);

    SplineControlPoint* LenToSegment(float t, float& localF);

    static Sombrero::FastVector3 CatmulRom(const Sombrero::FastVector3& T0, const Sombrero::FastVector3& P0, const Sombrero::FastVector3& P1, const Sombrero::FastVector3& T1, float f);
    Sombrero::FastVector3 InterpolateByLen(float tl);
    Sombrero::FastVector3 InterpolateNormalByLen(float tl);
    SplineControlPoint* AddControlPoint(const Sombrero::FastVector3& pos, const Sombrero::FastVector3& up);
    void Clear();
    void RefreshSpline();

    ~Spline();

private:
    void RefreshDistance();
};