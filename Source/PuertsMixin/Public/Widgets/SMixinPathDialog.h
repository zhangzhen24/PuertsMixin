#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "Widgets/DeclarativeSyntaxSupport.h"

class SEditableTextBox;

/**
 * Mixin 文件路径选择对话框
 */
class PUERTSMIXIN_API SMixinPathDialog : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SMixinPathDialog)
		: _DefaultPath()
		, _BlueprintName()
		, _DefaultMixinName()
	{}
		SLATE_ARGUMENT(FString, DefaultPath)
		SLATE_ARGUMENT(FString, BlueprintName)
		SLATE_ARGUMENT(FString, DefaultMixinName)
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

	/** 显示对话框并返回用户选择的路径和类名，如果取消则返回 false */
	static bool ShowDialog(const FString& DefaultPath, const FString& BlueprintName,
		FString& OutPath, FString& OutMixinName);

	/** 显示目录选择对话框（用于批量导出），返回是否成功选择，OutDirectory 为相对于 TypeScript/ 的目录路径 */
	static bool ShowDirectoryDialog(FString& OutDirectory, const FString& DefaultDirectory = TEXT(""));

	/** 获取用户选择的路径 */
	FString GetSelectedPath() const;

	/** 获取用户输入的类名 */
	FString GetMixinName() const;

	/** 是否确认 */
	bool IsConfirmed() const { return bConfirmed; }

private:
	FReply OnPresetPathClicked(FString PresetPath);
	FReply OnConfirmClicked();
	FReply OnCancelClicked();
	FReply OnBrowseClicked();
	void CloseDialog();
	void UpdatePathFromMixinName();

private:
	TSharedPtr<SEditableTextBox> PathTextBox;
	TSharedPtr<SEditableTextBox> MixinNameTextBox;
	TSharedPtr<SWindow> ParentWindow;
	FString BlueprintName;
	FString SelectedPath;
	FString MixinName;
	FString CurrentDirectory;  // 当前选择的目录（不含文件名）
	bool bConfirmed = false;
};
