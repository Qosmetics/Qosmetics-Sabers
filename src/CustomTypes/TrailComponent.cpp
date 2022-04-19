#include "CustomTypes/TrailComponent.hpp"

#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/Time.hpp"
#include "logging.hpp"

DEFINE_TYPE(Qosmetics::Sabers, TrailComponent);

using namespace UnityEngine;
using namespace Sombrero;

static constexpr const float frameRateTreshold = 1.0f / 90.0f;

namespace Qosmetics::Sabers
{
    bool TrailComponent::CapFps = false;
    float TrailComponent::trailIntensity = 1.0f;

    void TrailComponent::ctor()
    {
        INVOKE_CTOR();
        INFO("ctor");
    }

    bool TrailComponent::get_inited() const
    {
        return inited;
    }

    void TrailComponent::Setup(const TrailInitData& initData, UnityEngine::Transform* pointStart, UnityEngine::Transform* pointEnd, UnityEngine::Material* material, bool editor)
    {
        INFO("setup");

        PointStart = pointStart;
        PointEnd = pointEnd;
        MyMaterial = material;

        MyColor = initData.TrailColor;
        Granularity = initData.Granularity;
        // if it's size is not at least 4 it breaks
        TrailLength = initData.TrailLength;
        WhiteStep = initData.Whitestep;

        DEBUG("Trail data:\n"
              "\tlength: {}\n"
              "\twhitestep: {}\n"
              "\tgranularity: {}\n"
              "\tcolor: {}, {}, {}, {}\n",
              TrailLength,
              WhiteStep,
              Granularity,
              MyColor.r, MyColor.g, MyColor.b, MyColor.a);

        get_gameObject()->set_layer(12);
        if (editor)
            SortingOrder = 3;
        else
            SortingOrder = 0;

        if (!spline)
            spline.Reserve(TrailLength);
        snapshotList.reserve(TrailLength);

        if (!vertexPool)
            vertexPool = VertexPool::New_ctor(MyMaterial, this);
        snapshotList.reserve(TrailLength);

        vertexPool->SetMeshObjectActive(false);
        vertexSegment = vertexPool->GetVertices(Granularity * 3, (Granularity - 1) * 12);
        UpdateIndices();

        if (inited)
            UpdateTrailData();

        inited = true;
    }

    void TrailComponent::UpdateTrailData()
    {
        vertexPool->SetMaterial(MyMaterial);
        Collapse();
        vertexPool->SetMeshObjectActive(true);

        /*
        Reset(false);
        Collapse();
        */
    }

    void TrailComponent::OnDisable()
    {
        if (!inited)
            return;
        Collapse();
        if (vertexPool)
            vertexPool->SetMeshObjectActive(false);
    }

    void TrailComponent::OnEnable()
    {
        if (!inited)
            return;
        Collapse();
        if (vertexPool)
            vertexPool->SetMeshObjectActive(true);
    }

    void TrailComponent::LateUpdate()
    {
        if (!inited)
            return;

        if (CapFps)
        {
            time += Time::get_deltaTime();
            if (time < frameRateTreshold)
                return;
            time = 0.0f;
        }

        frameNum++;

        if (frameNum == skipFirstFrames + 1)
        {
            Reset(true);
            UpdateHeadElem();
            RecordCurElem();
            RefreshSpline();
            UpdateVertex();

            vertexPool->LateUpdate();
            vertexPool->SetMeshObjectActive(true);
            return;
        }
        else if (frameNum < (skipFirstFrames + 1))
            return;

        UpdateHeadElem();
        RecordCurElem();
        RefreshSpline();
        UpdateVertex();

        vertexPool->LateUpdate();
    }

    void TrailComponent::OnDestroy()
    {
        if (!inited)
            return;
        if (vertexPool)
            vertexPool->Destroy();

        // empty snapshot list
        snapshotList.clear();
    }

    float TrailComponent::get_TrailWidth() const
    {
        return ((FastVector3)get_startPos() - (FastVector3)get_endPos()).Magnitude() * 0.5f;
    }

    Sombrero::FastVector3 TrailComponent::get_CurHeadPos() const
    {
        return ((FastVector3)get_startPos() - (FastVector3)get_endPos()) / 2.0f;
    }

    void TrailComponent::RefreshSpline()
    {
        auto& controlPoints = spline.get_ControlPoints();
        int diff = snapshotList.size() - controlPoints.size();

        // if control points smaller than snapshots, add new control points
        while (diff > 0)
        {
            spline.AddControlPoint(get_CurHeadPos(), get_startPos() - get_endPos());
            diff--;
        }

        int index = 0;
        for (const auto& snap : snapshotList)
        {
            controlPoints[index]->Position = snap->get_pos();
            controlPoints[index]->Normal = snap->pointEnd - snap->pointStart;
            index++;
        }

        spline.RefreshSpline();
    }

    void TrailComponent::UpdateVertex()
    {
        auto* pool = vertexSegment.Pool;

        for (int i = 0; i < Granularity; i++)
        {
            int baseIdx = vertexSegment.VertStart + i * 3;

            float uvSegment = (float)i / Granularity;

            FastColor color = MyColor;

            if (uvSegment < WhiteStep)
            {
                color = FastColor::LerpUnclamped(FastColor::white(), MyColor, uvSegment / WhiteStep);
            }

            FastVector3 pos = spline.InterpolateByLen(uvSegment);
            FastVector3 mul = FastVector3::Normalize(spline.InterpolateNormalByLen(uvSegment)) * get_TrailWidth(); //(NormalizeVal(spline.InterpolateNormalByLen(uvSegment)), get_TrailWidth());

            // offset half a trail width from pos
            pool->Vertices[baseIdx] = pos + mul;
            pool->UVs[baseIdx].x = 0.0f;

            // center
            pool->Vertices[baseIdx + 1] = pos;
            pool->UVs[baseIdx + 1].x = 0.5f;

            // offset half a trail width from pos
            pool->Vertices[baseIdx + 2] = pos - mul;
            pool->UVs[baseIdx + 2].x = 1.0f;

            pool->Colors[baseIdx] = pool->Colors[baseIdx + 1] = pool->Colors[baseIdx + 2] = color;
            pool->UVs[baseIdx].y = pool->UVs[baseIdx + 1].y = pool->UVs[baseIdx + 2].y = uvSegment;
        }

        vertexSegment.Pool->UVChanged = true;
        vertexSegment.Pool->VertChanged = true;
        vertexSegment.Pool->ColorChanged = true;
    }

    void TrailComponent::UpdateIndices() const
    {
        INFO("Updating indices");
        auto* pool = vertexSegment.Pool;

        for (int i = 0; i < Granularity - 1; i++)
        {
            int baseIdx = vertexSegment.VertStart + i * 3;
            int nextBaseIdx = vertexSegment.VertStart + (i + 1) * 3;

            int iidx = vertexSegment.IndexStart + i * 12;
            // triangle left
            pool->Indices->values[iidx + 0] = nextBaseIdx;
            pool->Indices->values[iidx + 1] = nextBaseIdx + 1;
            pool->Indices->values[iidx + 2] = baseIdx;
            pool->Indices->values[iidx + 3] = nextBaseIdx + 1;
            pool->Indices->values[iidx + 4] = baseIdx + 1;
            pool->Indices->values[iidx + 5] = baseIdx;

            // triangle right
            pool->Indices->values[iidx + 6] = nextBaseIdx + 1;
            pool->Indices->values[iidx + 7] = nextBaseIdx + 2;
            pool->Indices->values[iidx + 8] = baseIdx + 1;
            pool->Indices->values[iidx + 9] = nextBaseIdx + 2;
            pool->Indices->values[iidx + 10] = baseIdx + 2;
            pool->Indices->values[iidx + 11] = baseIdx + 1;
        }

        pool->IndiceChanged = true;
    }

    void TrailComponent::UpdateHeadElem()
    {
        // update the first element
        snapshotList.front()->pointStart = get_startPos();
        snapshotList.front()->pointEnd = get_endPos();
    }

    void TrailComponent::RecordCurElem()
    {
        // if list is small
        if (snapshotList.size() < TrailLength)
        {
            // add it after the first element
            auto itr = snapshotList.insert((snapshotList.begin()++), std::make_unique<Element>(get_startPos(), get_endPos()));
        }
        // if list too big, just release the back element
        else if (snapshotList.size() > TrailLength)
            snapshotList.pop_back();
        // if list exactly right, remove the last list element and put the new element after the first
        else // if (snapshotList.size() == TrailLength)
        {
            auto backElem = std::move(snapshotList.back());
            snapshotList.pop_back();
            backElem->pointStart = get_startPos();
            backElem->pointEnd = get_endPos();
            snapshotList.insert((snapshotList.begin()++), std::move(backElem));
        }
    }

    void TrailComponent::SetColor(FastColor color)
    {
        color.a *= trailIntensity;
        MyColor = color;
    }

    void TrailComponent::Reset(bool addNewElemsToSnap)
    {
        if (!spline)
            spline.Reserve(TrailLength);

        spline.Granularity = Granularity;
        spline.Clear();

        // make sure the spline contains enough control points for the trail length
        for (int i = 0; i < TrailLength; i++)
            spline.AddControlPoint(get_CurHeadPos(), (FastVector3)get_startPos() - (FastVector3)get_endPos());

        // if snapshot list contains elements, that is an issue, remove them!
        if (!snapshotList.empty())
        {
            snapshotList.clear();
            snapshotList.reserve(TrailLength);
        }

        // if hte pool already existed and we dont want to force new elements in, use this
        snapshotList.emplace_back(std::make_unique<Element>(get_startPos(), get_endPos()));
        snapshotList.emplace_back(std::make_unique<Element>(get_startPos(), get_endPos()));
        // collapse the trail to be basically 0 length
        Collapse();
    }

    void TrailComponent::Collapse()
    {
        FastVector3 start = get_startPos();
        FastVector3 end = get_endPos();
        // makes all parts of the trail end up at the same place, making it basically 0 length
        for (auto& snap : snapshotList)
        {
            snap->pointStart = start;
            snap->pointEnd = end;
        }

        RefreshSpline();
    }

    Sombrero::FastVector3 TrailComponent::get_startPos() const
    {
        return PointStart ? PointStart->get_position() : Sombrero::FastVector3::zero();
    }

    Sombrero::FastVector3 TrailComponent::get_endPos() const
    {
        return PointEnd ? PointEnd->get_position() : Sombrero::FastVector3::zero();
    }

}