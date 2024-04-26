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

namespace Qosmetics::Sabers
{
    class TrailComponent;

}

DECLARE_CLASS_CODEGEN(Qosmetics::Sabers, VertexPool, Il2CppObject,

                      DECLARE_INSTANCE_FIELD_PRIVATE(ArrayW<Sombrero::FastVector3>, _vertices);
                      DECLARE_INSTANCE_FIELD_PRIVATE(ArrayW<int>, _indices);
                      DECLARE_INSTANCE_FIELD_PRIVATE(ArrayW<Sombrero::FastVector2>, _uvs);
                      DECLARE_INSTANCE_FIELD_PRIVATE(ArrayW<Sombrero::FastColor>, _colors);
                      DECLARE_INSTANCE_FIELD_PRIVATE(UnityEngine::MeshFilter*, _meshFilter);
                      DECLARE_INSTANCE_FIELD_PRIVATE(UnityEngine::Material*, _material);
                      DECLARE_INSTANCE_FIELD_PRIVATE(UnityEngine::GameObject*, _gameObject);

                      DECLARE_CTOR(ctor, UnityEngine::Material* material, TrailComponent* owner);
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

                      ArrayW<Sombrero::FastVector3> get_Vertices();
                      ArrayW<int> get_Indices();
                      ArrayW<Sombrero::FastVector2> get_UVs();
                      ArrayW<Sombrero::FastColor> get_Colors();

                      __declspec(property(get = get_Vertices)) ArrayW<Sombrero::FastVector3> Vertices;
                      __declspec(property(get = get_Indices)) ArrayW<int> Indices;
                      __declspec(property(get = get_UVs)) ArrayW<Sombrero::FastVector2> UVs;
                      __declspec(property(get = get_Colors)) ArrayW<Sombrero::FastColor> Colors;

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
