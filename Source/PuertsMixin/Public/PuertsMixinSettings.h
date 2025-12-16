#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PuertsMixinSettings.generated.h"

/**
 * 外部代码编辑器类型枚举
 */
UENUM()
enum class EPuertsMixinEditorType : uint8
{
	/** Visual Studio Code */
	VSCode,

	/** 其他基于 VSCode 的编辑器（需手动指定可执行文件名） */
	Custom
};

/**
 * PuertsMixin 插件设置类
 * 用于配置生成的 TypeScript 文件路径、使用的外部编辑器等
 */
UCLASS(config = PuertsMixin, defaultconfig)
class PUERTSMIXIN_API UPuertsMixinSettings : public UObject
{
	GENERATED_BODY()

public:

	UPuertsMixinSettings();

	/** 选择要使用的外部代码编辑器 */
	UPROPERTY(DisplayName="外部代码编辑器", EditAnywhere, config)
	EPuertsMixinEditorType EditorType;

	/**
	 * 自定义编辑器的绝对路径
	 * 仅当 EditorType 为 Custom 时生效
	 * 例如：E:\All-apps\Trae\Trae.exe 等
	 */
	UPROPERTY(
		EditAnywhere, config,
		meta = (EditCondition = "EditorType == EPuertsMixinEditorType::Custom", DisplayName =
			"类VScode编辑器可执行文件绝对路径")
	)
	FString CustomEditorExecutable;

	/**
	 * TypeScript 入口文件名称
	 * 用于自动导入 Mixin类
	 * 默认值：Main.ts
	 */
	UPROPERTY(
		EditAnywhere, config, Category = "Code Generation", meta = (DisplayName = "主入口文件名")
	)
	FString MainEntryFileName;

	/**
	 * 获取当前配置的编辑器启动命令
	 * @return 可执行文件名或路径
	 */
	FString GetEditorCommand() const;
};
