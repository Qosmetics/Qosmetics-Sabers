#include "MaterialUtils.hpp"
#include "PropertyID.hpp"

#include "UnityEngine/Renderer.hpp"
#include "beatsaber-hook/shared/utils/il2cpp-utils.hpp"

#define HAS_FLOAT(theFloat) material->HasProperty(PropertyID::theFloat())
#define CHECK_FLOAT(theFloat) (material->GetFloat(PropertyID::theFloat()) > 0)

using namespace UnityEngine;

namespace Qosmetics::Sabers::MaterialUtils
{
    bool ShouldCC(Material* material)
    {
        if (!material)
            return false;
        else if (HAS_FLOAT(_CustomColors))
            return CHECK_FLOAT(_CustomColors);
        else if (HAS_FLOAT(_Glow))
            return CHECK_FLOAT(_Glow);
        else if (HAS_FLOAT(_Bloom))
            return CHECK_FLOAT(_Bloom);
        return false;
    }

    void PrewarmAllShadersOnObject(GameObject* object)
    {
        if (!object)
            return;
        auto renderers = object->GetComponentsInChildren<UnityEngine::Renderer*>(true);

        // all shader variant stuff is stripped so resolve icall
        static auto createFunc = reinterpret_cast<function_ptr_t<void, Il2CppObject*>>(il2cpp_functions::resolve_icall("UnityEngine.ShaderVariantCollection::Internal_Create"));
        static auto addFunc = reinterpret_cast<function_ptr_t<bool, Il2CppObject*, Il2CppObject*, int, ArrayW<StringW>>>(il2cpp_functions::resolve_icall("UnityEngine.ShaderVariantCollection::AddVariant"));
        static auto warmupFunc = reinterpret_cast<function_ptr_t<void, Il2CppObject*>>(il2cpp_functions::resolve_icall("UnityEngine.ShaderVariantCollection::WarmUp"));
        Il2CppObject* obj = UnityEngine::Object::New_ctor();
        createFunc(obj);
        for (auto renderer : renderers)
        {
            for (auto material : renderer->materials)
            {
                addFunc(obj, material->shader, 0, material->shaderKeywords);
            }
        }

        warmupFunc(obj);
    }
}
