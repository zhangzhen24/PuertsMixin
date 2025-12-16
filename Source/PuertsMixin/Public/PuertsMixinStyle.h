// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Styling/SlateStyle.h"

class FPuertsMixinStyle
{
public:

	static void Initialize();

	static void Shutdown();

	/** 重新加载slate渲染器使用的纹理 */
	static void ReloadTextures();

	/** @return 获取射击游戏的Slate样式集 */
	static const ISlateStyle& Get();

	static FName GetStyleSetName();

private:

	static TSharedRef<FSlateStyleSet> Create();

private:

	static TSharedPtr<FSlateStyleSet> StyleInstance;
};
