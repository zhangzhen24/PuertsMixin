// 插件头文件：声明 PuertsMixin 模块接口与命令注册函数
// 规范要求：头文件注释使用 /** ... */ 置于变量或函数上方
// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Modules/ModuleManager.h"

class FBlueprintToolbar;

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

	/** 蓝图工具栏实例 */
	TSharedPtr<FBlueprintToolbar> BlueprintToolbar;
};
