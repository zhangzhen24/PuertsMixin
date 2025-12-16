// 命令注册源文件：定义工具栏按钮 “Mixin” 的显示文本与提示信息
// 说明：遵循中文注释规范，所有功能点均附带中文说明
// Copyright Epic Games, Inc. All Rights Reserved.

#include "PuertsMixinCommands.h"

#define LOCTEXT_NAMESPACE "FPuertsMixinModule"

void FPuertsMixinCommands::RegisterCommands()
{
	// 注册一个工具栏按钮命令：名称 “Mixin”，用于生成/打开当前蓝图的 TS Mixin 文件
	UI_COMMAND(
		PluginAction, "Mixin", "Generate Mixin TS file for current Blueprint",
		EUserInterfaceActionType::Button, FInputChord()
	);
}

#undef LOCTEXT_NAMESPACE
