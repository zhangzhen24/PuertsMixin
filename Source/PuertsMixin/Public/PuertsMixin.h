// 插件头文件：声明 PuertsMixin 模块接口与命令注册函数
// 规范要求：头文件注释使用 /** ... */ 置于变量或函数上方
// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Modules/ModuleManager.h"
#include "ContentBrowserDelegates.h"

class FBlueprintToolbar;
class FMenuBuilder;
struct FAssetData;

class FPuertsMixinModule : public IModuleInterface
{
public:

	/** 模块启动：初始化样式、注册命令与菜单 */
	virtual void StartupModule() override;

	/** 模块关闭：释放资源、反注册菜单与命令 */
	virtual void ShutdownModule() override;

private:

	/** 注册设置面板 */
	void RegisterSettings();

	/** 反注册设置面板 */
	void UnregisterSettings();

	/** 引擎初始化后回调 */
	void OnPostEngineInit();

	/** ContentBrowser 右键菜单扩展回调 */
	TSharedRef<FExtender> OnExtendContentBrowserAssetMenu(const TArray<FAssetData>& SelectedAssets);

	/** 添加 Mixin 菜单项 */
	void AddMixinMenuEntry(FMenuBuilder& MenuBuilder, TArray<FAssetData> SelectedAssets);

	/** 从单个资产创建 Mixin */
	void OnCreateMixinFromAsset(FAssetData AssetData);

	/** 从多个资产批量创建 Mixin */
	void OnCreateMixinFromAssets(TArray<FAssetData> SelectedAssets);

	/** 蓝图工具栏实例 */
	TSharedPtr<FBlueprintToolbar> BlueprintToolbar;

	/** ContentBrowser 扩展委托句柄 */
	FDelegateHandle ContentBrowserExtenderHandle;
};
