#include "Trail/SplineControlPoint.hpp"
#include "Trail/Spline.hpp"
#include "sombrero/shared/MiscUtils.hpp"

using namespace Sombrero;

SplineControlPoint* SplineControlPoint::NextControlPoint() const
{
    return spline->NextControlPoint(*this);
}

SplineControlPoint* SplineControlPoint::PreviousControlPoint() const
{
    return spline->PreviousControlPoint(*this);
}

FastVector3 SplineControlPoint::NextPosition() const
{
    return spline->NextPosition(*this);
}

FastVector3 SplineControlPoint::PreviousPosition() const
{
    return spline->PreviousPosition(*this);
}

FastVector3 SplineControlPoint::NextNormal() const
{
    return spline->NextNormal(*this);
}

FastVector3 SplineControlPoint::PreviousNormal() const
{
    return spline->PreviousNormal(*this);
}

bool SplineControlPoint::IsValid() const
{
    return NextControlPoint();
}

FastVector3 SplineControlPoint::GetNext2Position() const
{
    auto cp = NextControlPoint();
    if (cp)
        return cp->NextPosition();
    return NextPosition();
}

FastVector3 SplineControlPoint::GetNext2Normal() const
{
    auto cp = NextControlPoint();
    if (cp)
        return cp->NextNormal();
    return NextNormal();
}

FastVector3 SplineControlPoint::Interpolate(float localF) const
{
    return Spline::CatmulRom(PreviousPosition(), Position, NextPosition(), GetNext2Position(), Clamp01(localF));
}

FastVector3 SplineControlPoint::InterpolateNormal(float localF) const
{
    return Spline::CatmulRom(PreviousNormal(), Normal, NextNormal(), GetNext2Normal(), Clamp01(localF));
}

void SplineControlPoint::Init(Spline* owner)
{
    spline = owner;
}
