// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "PuertsMixinSettings.h"

#ifdef PUERTSMIXIN_PuertsMixinSettings_generated_h
#error "PuertsMixinSettings.generated.h already included, missing '#pragma once' in PuertsMixinSettings.h"
#endif
#define PUERTSMIXIN_PuertsMixinSettings_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin Class UPuertsMixinSettings *****************************************************
struct Z_Construct_UClass_UPuertsMixinSettings_Statics;
PUERTSMIXIN_API UClass* Z_Construct_UClass_UPuertsMixinSettings_NoRegister();

#define FID_Projects_WarlockWars_Plugins_PuertsMixin_Source_PuertsMixin_Public_PuertsMixinSettings_h_27_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUPuertsMixinSettings(); \
	friend struct ::Z_Construct_UClass_UPuertsMixinSettings_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend PUERTSMIXIN_API UClass* ::Z_Construct_UClass_UPuertsMixinSettings_NoRegister(); \
public: \
	DECLARE_CLASS2(UPuertsMixinSettings, UObject, COMPILED_IN_FLAGS(0 | CLASS_DefaultConfig | CLASS_Config), CASTCLASS_None, TEXT("/Script/PuertsMixin"), Z_Construct_UClass_UPuertsMixinSettings_NoRegister) \
	DECLARE_SERIALIZER(UPuertsMixinSettings) \
	static constexpr const TCHAR* StaticConfigName() {return TEXT("PuertsMixin");} \



#define FID_Projects_WarlockWars_Plugins_PuertsMixin_Source_PuertsMixin_Public_PuertsMixinSettings_h_27_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	UPuertsMixinSettings(UPuertsMixinSettings&&) = delete; \
	UPuertsMixinSettings(const UPuertsMixinSettings&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UPuertsMixinSettings); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UPuertsMixinSettings); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(UPuertsMixinSettings) \
	NO_API virtual ~UPuertsMixinSettings();


#define FID_Projects_WarlockWars_Plugins_PuertsMixin_Source_PuertsMixin_Public_PuertsMixinSettings_h_24_PROLOG
#define FID_Projects_WarlockWars_Plugins_PuertsMixin_Source_PuertsMixin_Public_PuertsMixinSettings_h_27_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Projects_WarlockWars_Plugins_PuertsMixin_Source_PuertsMixin_Public_PuertsMixinSettings_h_27_INCLASS_NO_PURE_DECLS \
	FID_Projects_WarlockWars_Plugins_PuertsMixin_Source_PuertsMixin_Public_PuertsMixinSettings_h_27_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class UPuertsMixinSettings;

// ********** End Class UPuertsMixinSettings *******************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Projects_WarlockWars_Plugins_PuertsMixin_Source_PuertsMixin_Public_PuertsMixinSettings_h

// ********** Begin Enum EPuertsMixinEditorType ****************************************************
#define FOREACH_ENUM_EPUERTSMIXINEDITORTYPE(op) \
	op(EPuertsMixinEditorType::VSCode) \
	op(EPuertsMixinEditorType::Custom) 

enum class EPuertsMixinEditorType : uint8;
template<> struct TIsUEnumClass<EPuertsMixinEditorType> { enum { Value = true }; };
template<> PUERTSMIXIN_NON_ATTRIBUTED_API UEnum* StaticEnum<EPuertsMixinEditorType>();
// ********** End Enum EPuertsMixinEditorType ******************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
