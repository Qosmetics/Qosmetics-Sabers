#pragma once

#include "CustomTypes/VertexPool.hpp"
#include "Trail/Element.hpp"
#include "Trail/ElementPool.hpp"
#include "Trail/Spline.hpp"
#include "Trail/SplineControlPoint.hpp"
#include "Trail/TrailInitData.hpp"

#include "UnityEngine/Material.hpp"
#include "UnityEngine/MonoBehaviour.hpp"
#include "UnityEngine/Transform.hpp"
#include "custom-types/shared/macros.hpp"

#include "sombrero/shared/ColorUtils.hpp"

DECLARE_CLASS_CODEGEN(Qosmetics::Sabers, TrailComponent, UnityEngine::MonoBehaviour,
                      DECLARE_INSTANCE_FIELD(StringW, SortingLayerName);
                      DECLARE_INSTANCE_FIELD(UnityEngine::Transform*, PointStart);
                      DECLARE_INSTANCE_FIELD(UnityEngine::Transform*, PointEnd);
                      DECLARE_INSTANCE_FIELD(UnityEngine::Material*, MyMaterial);

                      DECLARE_INSTANCE_FIELD(Qosmetics::Sabers::VertexPool*, vertexPool);

                      DECLARE_INSTANCE_METHOD(void, OnDestroy);
                      DECLARE_INSTANCE_METHOD(void, LateUpdate);
                      DECLARE_INSTANCE_METHOD(void, OnDisable);
                      DECLARE_INSTANCE_METHOD(void, OnEnable);
                      DECLARE_INSTANCE_METHOD(void, Reset, bool addNewElemsToSnap);

                      DECLARE_CTOR(ctor);
                      DECLARE_SIMPLE_DTOR();

                      public
                      :

                      int SortingOrder;
                      int TrailLength = 30;
                      int Granularity = 60;
                      float WhiteStep = 0.2f;
                      Sombrero::FastColor MyColor = Sombrero::FastColor::white();
                      static bool CapFps;
                      Sombrero::FastVector3 get_CurHeadPos() const;
                      void Setup(const TrailInitData& initData, UnityEngine::Transform* pointStart, UnityEngine::Transform* pointEnd, UnityEngine::Material* material, bool editor);
                      void SetColor(Sombrero::FastColor color);
                      void Collapse();
                      static float trailIntensity;
                      bool get_inited() const;

                      private
                      : float get_TrailWidth() const;
                      std::vector<std::unique_ptr<Element>> snapshotList;
                      ElementPool elemPool;
                      Spline spline;
                      VertexSegment vertexSegment;
                      bool inited = false;
                      int skipFirstFrames = 4;
                      int frameNum = 0;
                      float time = 0.0f;

                      void UpdateTrailData();
                      void RefreshSpline();
                      void UpdateVertex();
                      void UpdateIndices() const;
                      void UpdateHeadElem();
                      void RecordCurElem();

)