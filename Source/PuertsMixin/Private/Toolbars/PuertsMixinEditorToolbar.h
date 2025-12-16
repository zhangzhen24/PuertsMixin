/** PuertsMixin 工具栏基类：绑定命令与构建按钮 */
#pragma once

#include "CoreMinimal.h"
#include "Framework/MultiBox/MultiBoxBuilder.h"
#include "Framework/Commands/UICommandList.h"

class FPuertsMixinEditorToolbar
{
public:

	virtual ~FPuertsMixinEditorToolbar() = default;

	FPuertsMixinEditorToolbar();

	/** 获取命令列表（用于工具栏扩展构建） */
	TSharedRef<FUICommandList> GetCommandList() const
	{
		return CommandList;
	}

	/** 初始化：绑定命令 */
	virtual void Initialize();

	/** Mixin 按钮执行回调：生成/打开 TS 混入文件 */
	void Mixin_Executed();

protected:

	/** 绑定命令（命令到执行代理） */
	virtual void BindCommands();

	/** 构建工具栏并添加按钮，同时保存上下文对象（蓝图） */
	void BuildToolbar(FToolBarBuilder& ToolbarBuilder, UObject* InContextObject);

	/** 获取工具栏扩展器，插入到蓝图编辑器的特定扩展点 */
	TSharedRef<FExtender> GetExtender(UObject* InContextObject);

	/** 命令列表（用于加到工具栏扩展） */
	const TSharedRef<FUICommandList> CommandList;

	/** 当前上下文对象（蓝图资产） */
	UObject* ContextObject;
};
