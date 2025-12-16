/** 蓝图编辑器工具栏扩展：在蓝图编辑器中插入 Mixin 按钮 */
#pragma once

#include "PuertsMixinEditorToolbar.h"

class FBlueprintToolbar : public FPuertsMixinEditorToolbar
{
public:

	/** 初始化工具栏扩展（注册到 Kismet 蓝图编辑器的 Extender） */
	virtual void Initialize() override;
};
