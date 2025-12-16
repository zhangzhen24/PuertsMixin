// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "PuertsMixinSettings.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodePuertsMixinSettings() {}

// ********** Begin Cross Module References ********************************************************
COREUOBJECT_API UClass* Z_Construct_UClass_UObject();
PUERTSMIXIN_API UClass* Z_Construct_UClass_UPuertsMixinSettings();
PUERTSMIXIN_API UClass* Z_Construct_UClass_UPuertsMixinSettings_NoRegister();
PUERTSMIXIN_API UEnum* Z_Construct_UEnum_PuertsMixin_EPuertsMixinEditorType();
UPackage* Z_Construct_UPackage__Script_PuertsMixin();
// ********** End Cross Module References **********************************************************

// ********** Begin Enum EPuertsMixinEditorType ****************************************************
static FEnumRegistrationInfo Z_Registration_Info_UEnum_EPuertsMixinEditorType;
static UEnum* EPuertsMixinEditorType_StaticEnum()
{
	if (!Z_Registration_Info_UEnum_EPuertsMixinEditorType.OuterSingleton)
	{
		Z_Registration_Info_UEnum_EPuertsMixinEditorType.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_PuertsMixin_EPuertsMixinEditorType, (UObject*)Z_Construct_UPackage__Script_PuertsMixin(), TEXT("EPuertsMixinEditorType"));
	}
	return Z_Registration_Info_UEnum_EPuertsMixinEditorType.OuterSingleton;
}
template<> PUERTSMIXIN_API UEnum* StaticEnum<EPuertsMixinEditorType>()
{
	return EPuertsMixinEditorType_StaticEnum();
}
struct Z_Construct_UEnum_PuertsMixin_EPuertsMixinEditorType_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * \xe5\xa4\x96\xe9\x83\xa8\xe4\xbb\xa3\xe7\xa0\x81\xe7\xbc\x96\xe8\xbe\x91\xe5\x99\xa8\xe7\xb1\xbb\xe5\x9e\x8b\xe6\x9e\x9a\xe4\xb8\xbe\n */" },
#endif
		{ "Custom.Comment", "/** \xe5\x85\xb6\xe4\xbb\x96\xe5\x9f\xba\xe4\xba\x8e VSCode \xe7\x9a\x84\xe7\xbc\x96\xe8\xbe\x91\xe5\x99\xa8\xef\xbc\x88\xe9\x9c\x80\xe6\x89\x8b\xe5\x8a\xa8\xe6\x8c\x87\xe5\xae\x9a\xe5\x8f\xaf\xe6\x89\xa7\xe8\xa1\x8c\xe6\x96\x87\xe4\xbb\xb6\xe5\x90\x8d\xef\xbc\x89 */" },
		{ "Custom.Name", "EPuertsMixinEditorType::Custom" },
		{ "Custom.ToolTip", "\xe5\x85\xb6\xe4\xbb\x96\xe5\x9f\xba\xe4\xba\x8e VSCode \xe7\x9a\x84\xe7\xbc\x96\xe8\xbe\x91\xe5\x99\xa8\xef\xbc\x88\xe9\x9c\x80\xe6\x89\x8b\xe5\x8a\xa8\xe6\x8c\x87\xe5\xae\x9a\xe5\x8f\xaf\xe6\x89\xa7\xe8\xa1\x8c\xe6\x96\x87\xe4\xbb\xb6\xe5\x90\x8d\xef\xbc\x89" },
		{ "ModuleRelativePath", "Public/PuertsMixinSettings.h" },
		{ "Qoder.Comment", "/** Qoder IDE */" },
		{ "Qoder.Name", "EPuertsMixinEditorType::Qoder" },
		{ "Qoder.ToolTip", "Qoder IDE" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe5\xa4\x96\xe9\x83\xa8\xe4\xbb\xa3\xe7\xa0\x81\xe7\xbc\x96\xe8\xbe\x91\xe5\x99\xa8\xe7\xb1\xbb\xe5\x9e\x8b\xe6\x9e\x9a\xe4\xb8\xbe" },
#endif
		{ "Trae.Comment", "/** Trae IDE */" },
		{ "Trae.Name", "EPuertsMixinEditorType::Trae" },
		{ "Trae.ToolTip", "Trae IDE" },
		{ "VSCode.Comment", "/** Visual Studio Code */" },
		{ "VSCode.Name", "EPuertsMixinEditorType::VSCode" },
		{ "VSCode.ToolTip", "Visual Studio Code" },
	};
#endif // WITH_METADATA
	static constexpr UECodeGen_Private::FEnumeratorParam Enumerators[] = {
		{ "EPuertsMixinEditorType::VSCode", (int64)EPuertsMixinEditorType::VSCode },
		{ "EPuertsMixinEditorType::Trae", (int64)EPuertsMixinEditorType::Trae },
		{ "EPuertsMixinEditorType::Qoder", (int64)EPuertsMixinEditorType::Qoder },
		{ "EPuertsMixinEditorType::Custom", (int64)EPuertsMixinEditorType::Custom },
	};
	static const UECodeGen_Private::FEnumParams EnumParams;
};
const UECodeGen_Private::FEnumParams Z_Construct_UEnum_PuertsMixin_EPuertsMixinEditorType_Statics::EnumParams = {
	(UObject*(*)())Z_Construct_UPackage__Script_PuertsMixin,
	nullptr,
	"EPuertsMixinEditorType",
	"EPuertsMixinEditorType",
	Z_Construct_UEnum_PuertsMixin_EPuertsMixinEditorType_Statics::Enumerators,
	RF_Public|RF_Transient|RF_MarkAsNative,
	UE_ARRAY_COUNT(Z_Construct_UEnum_PuertsMixin_EPuertsMixinEditorType_Statics::Enumerators),
	EEnumFlags::None,
	(uint8)UEnum::ECppForm::EnumClass,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UEnum_PuertsMixin_EPuertsMixinEditorType_Statics::Enum_MetaDataParams), Z_Construct_UEnum_PuertsMixin_EPuertsMixinEditorType_Statics::Enum_MetaDataParams)
};
UEnum* Z_Construct_UEnum_PuertsMixin_EPuertsMixinEditorType()
{
	if (!Z_Registration_Info_UEnum_EPuertsMixinEditorType.InnerSingleton)
	{
		UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_EPuertsMixinEditorType.InnerSingleton, Z_Construct_UEnum_PuertsMixin_EPuertsMixinEditorType_Statics::EnumParams);
	}
	return Z_Registration_Info_UEnum_EPuertsMixinEditorType.InnerSingleton;
}
// ********** End Enum EPuertsMixinEditorType ******************************************************

// ********** Begin Class UPuertsMixinSettings *****************************************************
void UPuertsMixinSettings::StaticRegisterNativesUPuertsMixinSettings()
{
}
FClassRegistrationInfo Z_Registration_Info_UClass_UPuertsMixinSettings;
UClass* UPuertsMixinSettings::GetPrivateStaticClass()
{
	using TClass = UPuertsMixinSettings;
	if (!Z_Registration_Info_UClass_UPuertsMixinSettings.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("PuertsMixinSettings"),
			Z_Registration_Info_UClass_UPuertsMixinSettings.InnerSingleton,
			StaticRegisterNativesUPuertsMixinSettings,
			sizeof(TClass),
			alignof(TClass),
			TClass::StaticClassFlags,
			TClass::StaticClassCastFlags(),
			TClass::StaticConfigName(),
			(UClass::ClassConstructorType)InternalConstructor<TClass>,
			(UClass::ClassVTableHelperCtorCallerType)InternalVTableHelperCtorCaller<TClass>,
			UOBJECT_CPPCLASS_STATICFUNCTIONS_FORCLASS(TClass),
			&TClass::Super::StaticClass,
			&TClass::WithinClass::StaticClass
		);
	}
	return Z_Registration_Info_UClass_UPuertsMixinSettings.InnerSingleton;
}
UClass* Z_Construct_UClass_UPuertsMixinSettings_NoRegister()
{
	return UPuertsMixinSettings::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UPuertsMixinSettings_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * PuertsMixin \xe6\x8f\x92\xe4\xbb\xb6\xe8\xae\xbe\xe7\xbd\xae\xe7\xb1\xbb\n * \xe7\x94\xa8\xe4\xba\x8e\xe9\x85\x8d\xe7\xbd\xae\xe7\x94\x9f\xe6\x88\x90\xe7\x9a\x84 TypeScript \xe6\x96\x87\xe4\xbb\xb6\xe8\xb7\xaf\xe5\xbe\x84\xe3\x80\x81\xe4\xbd\xbf\xe7\x94\xa8\xe7\x9a\x84\xe5\xa4\x96\xe9\x83\xa8\xe7\xbc\x96\xe8\xbe\x91\xe5\x99\xa8\xe7\xad\x89\n */" },
#endif
		{ "IncludePath", "PuertsMixinSettings.h" },
		{ "ModuleRelativePath", "Public/PuertsMixinSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "PuertsMixin \xe6\x8f\x92\xe4\xbb\xb6\xe8\xae\xbe\xe7\xbd\xae\xe7\xb1\xbb\n\xe7\x94\xa8\xe4\xba\x8e\xe9\x85\x8d\xe7\xbd\xae\xe7\x94\x9f\xe6\x88\x90\xe7\x9a\x84 TypeScript \xe6\x96\x87\xe4\xbb\xb6\xe8\xb7\xaf\xe5\xbe\x84\xe3\x80\x81\xe4\xbd\xbf\xe7\x94\xa8\xe7\x9a\x84\xe5\xa4\x96\xe9\x83\xa8\xe7\xbc\x96\xe8\xbe\x91\xe5\x99\xa8\xe7\xad\x89" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_EditorType_MetaData[] = {
		{ "Category", "Editor Integration" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** \xe9\x80\x89\xe6\x8b\xa9\xe8\xa6\x81\xe4\xbd\xbf\xe7\x94\xa8\xe7\x9a\x84\xe5\xa4\x96\xe9\x83\xa8\xe4\xbb\xa3\xe7\xa0\x81\xe7\xbc\x96\xe8\xbe\x91\xe5\x99\xa8 */" },
#endif
		{ "DisplayName", "External Editor" },
		{ "ModuleRelativePath", "Public/PuertsMixinSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe9\x80\x89\xe6\x8b\xa9\xe8\xa6\x81\xe4\xbd\xbf\xe7\x94\xa8\xe7\x9a\x84\xe5\xa4\x96\xe9\x83\xa8\xe4\xbb\xa3\xe7\xa0\x81\xe7\xbc\x96\xe8\xbe\x91\xe5\x99\xa8" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CustomEditorExecutable_MetaData[] = {
		{ "Category", "Editor Integration" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * \xe8\x87\xaa\xe5\xae\x9a\xe4\xb9\x89\xe7\xbc\x96\xe8\xbe\x91\xe5\x99\xa8\xe5\x8f\xaf\xe6\x89\xa7\xe8\xa1\x8c\xe6\x96\x87\xe4\xbb\xb6\xe5\x90\x8d\xe6\x88\x96\xe8\xb7\xaf\xe5\xbe\x84\n\x09 * \xe4\xbb\x85\xe5\xbd\x93 EditorType \xe4\xb8\xba Custom \xe6\x97\xb6\xe7\x94\x9f\xe6\x95\x88\n\x09 * \xe4\xbe\x8b\xe5\xa6\x82\xef\xbc\x9a""cursor.cmd, windsurf.exe \xe7\xad\x89\n\x09 */" },
#endif
		{ "DisplayName", "Custom Editor Executable" },
		{ "EditCondition", "EditorType == EPuertsMixinEditorType::Custom" },
		{ "ModuleRelativePath", "Public/PuertsMixinSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe8\x87\xaa\xe5\xae\x9a\xe4\xb9\x89\xe7\xbc\x96\xe8\xbe\x91\xe5\x99\xa8\xe5\x8f\xaf\xe6\x89\xa7\xe8\xa1\x8c\xe6\x96\x87\xe4\xbb\xb6\xe5\x90\x8d\xe6\x88\x96\xe8\xb7\xaf\xe5\xbe\x84\n\xe4\xbb\x85\xe5\xbd\x93 EditorType \xe4\xb8\xba Custom \xe6\x97\xb6\xe7\x94\x9f\xe6\x95\x88\n\xe4\xbe\x8b\xe5\xa6\x82\xef\xbc\x9a""cursor.cmd, windsurf.exe \xe7\xad\x89" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MainEntryFileName_MetaData[] = {
		{ "Category", "Code Generation" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * TypeScript \xe5\x85\xa5\xe5\x8f\xa3\xe6\x96\x87\xe4\xbb\xb6\xe5\x90\x8d\xe7\xa7\xb0\n\x09 * \xe7\x94\xa8\xe4\xba\x8e\xe8\x87\xaa\xe5\x8a\xa8\xe6\xb3\xa8\xe5\x86\x8c Mixin \xe7\xb1\xbb\xe7\x9a\x84\xe5\xbc\x95\xe7\x94\xa8\n\x09 * \xe9\xbb\x98\xe8\xae\xa4\xe5\x80\xbc\xef\xbc\x9aMain.ts\n\x09 */" },
#endif
		{ "DisplayName", "Main Entry File Name" },
		{ "ModuleRelativePath", "Public/PuertsMixinSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "TypeScript \xe5\x85\xa5\xe5\x8f\xa3\xe6\x96\x87\xe4\xbb\xb6\xe5\x90\x8d\xe7\xa7\xb0\n\xe7\x94\xa8\xe4\xba\x8e\xe8\x87\xaa\xe5\x8a\xa8\xe6\xb3\xa8\xe5\x86\x8c Mixin \xe7\xb1\xbb\xe7\x9a\x84\xe5\xbc\x95\xe7\x94\xa8\n\xe9\xbb\x98\xe8\xae\xa4\xe5\x80\xbc\xef\xbc\x9aMain.ts" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FBytePropertyParams NewProp_EditorType_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_EditorType;
	static const UECodeGen_Private::FStrPropertyParams NewProp_CustomEditorExecutable;
	static const UECodeGen_Private::FStrPropertyParams NewProp_MainEntryFileName;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UPuertsMixinSettings>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FBytePropertyParams Z_Construct_UClass_UPuertsMixinSettings_Statics::NewProp_EditorType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UClass_UPuertsMixinSettings_Statics::NewProp_EditorType = { "EditorType", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UPuertsMixinSettings, EditorType), Z_Construct_UEnum_PuertsMixin_EPuertsMixinEditorType, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_EditorType_MetaData), NewProp_EditorType_MetaData) }; // 4071945649
const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UPuertsMixinSettings_Statics::NewProp_CustomEditorExecutable = { "CustomEditorExecutable", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UPuertsMixinSettings, CustomEditorExecutable), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CustomEditorExecutable_MetaData), NewProp_CustomEditorExecutable_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UPuertsMixinSettings_Statics::NewProp_MainEntryFileName = { "MainEntryFileName", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UPuertsMixinSettings, MainEntryFileName), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MainEntryFileName_MetaData), NewProp_MainEntryFileName_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UPuertsMixinSettings_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UPuertsMixinSettings_Statics::NewProp_EditorType_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UPuertsMixinSettings_Statics::NewProp_EditorType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UPuertsMixinSettings_Statics::NewProp_CustomEditorExecutable,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UPuertsMixinSettings_Statics::NewProp_MainEntryFileName,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UPuertsMixinSettings_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_UPuertsMixinSettings_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UObject,
	(UObject* (*)())Z_Construct_UPackage__Script_PuertsMixin,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UPuertsMixinSettings_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UPuertsMixinSettings_Statics::ClassParams = {
	&UPuertsMixinSettings::StaticClass,
	"PuertsMixin",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	Z_Construct_UClass_UPuertsMixinSettings_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_UPuertsMixinSettings_Statics::PropPointers),
	0,
	0x001000A6u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UPuertsMixinSettings_Statics::Class_MetaDataParams), Z_Construct_UClass_UPuertsMixinSettings_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UPuertsMixinSettings()
{
	if (!Z_Registration_Info_UClass_UPuertsMixinSettings.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UPuertsMixinSettings.OuterSingleton, Z_Construct_UClass_UPuertsMixinSettings_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UPuertsMixinSettings.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR(UPuertsMixinSettings);
UPuertsMixinSettings::~UPuertsMixinSettings() {}
// ********** End Class UPuertsMixinSettings *******************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_All_Project_UE_ViviGame_Plugins_PuertsMixin_Source_PuertsMixin_Public_PuertsMixinSettings_h__Script_PuertsMixin_Statics
{
	static constexpr FEnumRegisterCompiledInInfo EnumInfo[] = {
		{ EPuertsMixinEditorType_StaticEnum, TEXT("EPuertsMixinEditorType"), &Z_Registration_Info_UEnum_EPuertsMixinEditorType, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 4071945649U) },
	};
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UPuertsMixinSettings, UPuertsMixinSettings::StaticClass, TEXT("UPuertsMixinSettings"), &Z_Registration_Info_UClass_UPuertsMixinSettings, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UPuertsMixinSettings), 3760985680U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_All_Project_UE_ViviGame_Plugins_PuertsMixin_Source_PuertsMixin_Public_PuertsMixinSettings_h__Script_PuertsMixin_2350792720(TEXT("/Script/PuertsMixin"),
	Z_CompiledInDeferFile_FID_All_Project_UE_ViviGame_Plugins_PuertsMixin_Source_PuertsMixin_Public_PuertsMixinSettings_h__Script_PuertsMixin_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_All_Project_UE_ViviGame_Plugins_PuertsMixin_Source_PuertsMixin_Public_PuertsMixinSettings_h__Script_PuertsMixin_Statics::ClassInfo),
	nullptr, 0,
	Z_CompiledInDeferFile_FID_All_Project_UE_ViviGame_Plugins_PuertsMixin_Source_PuertsMixin_Public_PuertsMixinSettings_h__Script_PuertsMixin_Statics::EnumInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_All_Project_UE_ViviGame_Plugins_PuertsMixin_Source_PuertsMixin_Public_PuertsMixinSettings_h__Script_PuertsMixin_Statics::EnumInfo));
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
