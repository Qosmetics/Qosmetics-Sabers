#pragma once

#include "Trail/VertexSegment.hpp"
#include "custom-types/shared/macros.hpp"

#include "sombrero/shared/ColorUtils.hpp"
#include "sombrero/shared/Vector2Utils.hpp"
#include "sombrero/shared/Vector3Utils.hpp"

#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/Material.hpp"
#include "UnityEngine/Mesh.hpp"
#include "UnityEngine/MeshFilter.hpp"
#include "UnityEngine/Renderer.hpp"

#include <vector>

#include "private_field.hpp"
namespace Qosmetics::Sabers
{
    class TrailComponent;

}

DECLARE_CLASS_CODEGEN(Qosmetics::Sabers, VertexPool, Il2CppObject,

                      DECLARE_INSTANCE_PRIVATE_FIELD(ArrayW<Sombrero::FastVector3>, Vertices);
                      DECLARE_INSTANCE_PRIVATE_FIELD(ArrayW<int>, Indices);
                      DECLARE_INSTANCE_PRIVATE_FIELD(ArrayW<Sombrero::FastVector2>, UVs);
                      DECLARE_INSTANCE_PRIVATE_FIELD(ArrayW<Sombrero::FastColor>, Colors);

                      DECLARE_INSTANCE_PRIVATE_FIELD(UnityEngine::MeshFilter*, _meshFilter);
                      DECLARE_INSTANCE_PRIVATE_FIELD(UnityEngine::Material*, _material);
                      DECLARE_INSTANCE_PRIVATE_FIELD(UnityEngine::GameObject*, _gameObject);

                      DECLARE_CTOR(ctor);
                      DECLARE_SIMPLE_DTOR();

                      public
                      :

                      bool IndiceChanged = false;
                      bool ColorChanged = false;
                      bool UVChanged = false;
                      bool VertChanged = false;
                      bool UV2Changed = false;
                      bool FirstUpdate = true;

                      const int BlockSize = 108;

                      float BoundsScheduleTime;
                      float ElapsedTime;

                      void RecalculateBounds();
                      UnityEngine::Mesh * get_MyMesh() const;
                      void SetMeshObjectActive(bool flag) const;
                      void Destroy() const;
                      VertexSegment GetVertices(int vcount, int icount);
                      void EnlargeArrays(int count, int icount);
                      void LateUpdate();
                      void SetMaterial(UnityEngine::Material* material);
                      void Init(UnityEngine::Material* material, TrailComponent* owner);

                      private
                      :

                      int vertexTotal = 0;
                      int vertexUsed = 0;
                      int indexTotal = 0;
                      int indexUsed = 0;
                      bool vertCountChanged;

                      Qosmetics::Sabers::TrailComponent* owner = nullptr;

                      void CreateMeshObj(TrailComponent* owner, UnityEngine::Material* material);
                      void InitArrays();

)