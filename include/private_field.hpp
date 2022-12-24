#ifndef DECLARE_INSTANCE_PRIVATE_FIELD
#define DECLARE_INSTANCE_PRIVATE_FIELD(type_, name_)                                                                         \
private:                                                                                                                     \
    struct ___FieldRegistrator_##name_ : ::custom_types::FieldRegistrator                                                    \
    {                                                                                                                        \
        ___FieldRegistrator_##name_()                                                                                        \
        {                                                                                                                    \
            ___TargetType::___TypeRegistration::addField(this);                                                              \
        }                                                                                                                    \
        constexpr const char* name() const override                                                                          \
        {                                                                                                                    \
            return #name_;                                                                                                   \
        }                                                                                                                    \
        const Il2CppType* type() const override                                                                              \
        {                                                                                                                    \
            ::il2cpp_functions::Init();                                                                                      \
            return ::il2cpp_functions::class_get_type(::il2cpp_utils::il2cpp_type_check::il2cpp_no_arg_class<type_>::get()); \
        }                                                                                                                    \
        constexpr uint16_t fieldAttributes() const override                                                                  \
        {                                                                                                                    \
            return FIELD_ATTRIBUTE_PRIVATE;                                                                                  \
        }                                                                                                                    \
        constexpr size_t size() const override                                                                               \
        {                                                                                                                    \
            return sizeof(type_);                                                                                            \
        }                                                                                                                    \
        int32_t offset() const override                                                                                      \
        {                                                                                                                    \
            return offsetof(___TargetType, name_);                                                                           \
        }                                                                                                                    \
    };                                                                                                                       \
    static inline ___FieldRegistrator_##name_ ___##name_##_FieldRegistrator;                                                 \
                                                                                                                             \
public:                                                                                                                      \
    type_ name_
#endif