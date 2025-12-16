// Copyright Epic Games, Inc. All Rights Reserved.

#include "PuertsMixinStyle.h"
#include "PuertsMixin.h"
#include "Framework/Application/SlateApplication.h"
#include "Styling/SlateStyleRegistry.h"
#include "Slate/SlateGameResources.h"
#include "Interfaces/IPluginManager.h"
#include "Styling/SlateStyleMacros.h"

#define RootToContentDir Style->RootToContentDir

TSharedPtr<FSlateStyleSet> FPuertsMixinStyle::StyleInstance = nullptr;

void FPuertsMixinStyle::Initialize()
{
	if (!StyleInstance.IsValid())
	{
		StyleInstance = Create();
		FSlateStyleRegistry::RegisterSlateStyle(*StyleInstance);
	}
}

void FPuertsMixinStyle::Shutdown()
{
	FSlateStyleRegistry::UnRegisterSlateStyle(*StyleInstance);
	ensure(StyleInstance.IsUnique());
	StyleInstance.Reset();
}

FName FPuertsMixinStyle::GetStyleSetName()
{
	static FName StyleSetName(TEXT("PuertsMixinStyle"));
	return StyleSetName;
}


const FVector2D Icon16x16(16.0f, 16.0f);
const FVector2D Icon20x20(20.0f, 20.0f);

TSharedRef<FSlateStyleSet> FPuertsMixinStyle::Create()
{
	TSharedRef<FSlateStyleSet> Style = MakeShareable(new FSlateStyleSet("PuertsMixinStyle"));
	Style->SetContentRoot(IPluginManager::Get().FindPlugin("PuertsMixin")->GetBaseDir() / TEXT("Resources"));

	Style->Set("PuertsMixin.PluginAction", new IMAGE_BRUSH_SVG(TEXT("PlaceholderButtonIcon"), Icon20x20));
	return Style;
}

void FPuertsMixinStyle::ReloadTextures()
{
	if (FSlateApplication::IsInitialized())
	{
		FSlateApplication::Get().GetRenderer()->ReloadTextureResources();
	}
}

const ISlateStyle& FPuertsMixinStyle::Get()
{
	return *StyleInstance;
}
