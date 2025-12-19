#include "Widgets/SMixinPathDialog.h"
#include "Widgets/Input/SEditableTextBox.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "Framework/Application/SlateApplication.h"
#include "DesktopPlatformModule.h"
#include "Misc/Paths.h"

#define LOCTEXT_NAMESPACE "SMixinPathDialog"

void SMixinPathDialog::Construct(const FArguments& InArgs)
{
	BlueprintName = InArgs._BlueprintName;
	MixinName = InArgs._DefaultMixinName.IsEmpty() ? BlueprintName : InArgs._DefaultMixinName;

	// 解析默认路径，分离目录和文件名
	FString DefaultPath = InArgs._DefaultPath;
	if (DefaultPath.EndsWith(TEXT(".ts")))
	{
		// 从路径中提取目录部分
		CurrentDirectory = FPaths::GetPath(DefaultPath);
		if (!CurrentDirectory.IsEmpty() && !CurrentDirectory.EndsWith(TEXT("/")))
		{
			CurrentDirectory += TEXT("/");
		}
	}
	else
	{
		CurrentDirectory = DefaultPath;
		if (!CurrentDirectory.IsEmpty() && !CurrentDirectory.EndsWith(TEXT("/")))
		{
			CurrentDirectory += TEXT("/");
		}
	}

	// 构造完整路径
	SelectedPath = CurrentDirectory + MixinName + TEXT(".ts");

	ChildSlot
	[
		SNew(SBox)
		.MinDesiredWidth(500.0f)
		.Padding(16.0f)
		[
			SNew(SVerticalBox)

			// 标题
			+ SVerticalBox::Slot()
			.AutoHeight()
			.Padding(0, 0, 0, 16)
			[
				SNew(STextBlock)
				.Text(FText::Format(LOCTEXT("DialogTitle", "Export Mixin: {0}"), FText::FromString(BlueprintName)))
				.Font(FCoreStyle::GetDefaultFontStyle("Bold", 14))
			]

			// 类名输入
			+ SVerticalBox::Slot()
			.AutoHeight()
			.Padding(0, 0, 0, 8)
			[
				SNew(STextBlock)
				.Text(LOCTEXT("MixinNameLabel", "Mixin Class Name:"))
			]

			+ SVerticalBox::Slot()
			.AutoHeight()
			.Padding(0, 0, 0, 16)
			[
				SAssignNew(MixinNameTextBox, SEditableTextBox)
				.Text(FText::FromString(MixinName))
				.OnTextChanged_Lambda([this](const FText& NewText) {
					MixinName = NewText.ToString();
					UpdatePathFromMixinName();
				})
			]

			// 路径输入
			+ SVerticalBox::Slot()
			.AutoHeight()
			.Padding(0, 0, 0, 8)
			[
				SNew(STextBlock)
				.Text(LOCTEXT("PathLabel", "Target Path (relative to TypeScript/):"))
			]

			+ SVerticalBox::Slot()
			.AutoHeight()
			.Padding(0, 0, 0, 16)
			[
				SNew(SHorizontalBox)

				+ SHorizontalBox::Slot()
				.FillWidth(1.0f)
				[
					SAssignNew(PathTextBox, SEditableTextBox)
					.Text(FText::FromString(SelectedPath))
					.OnTextChanged_Lambda([this](const FText& NewText) {
						SelectedPath = NewText.ToString();
					})
				]

				+ SHorizontalBox::Slot()
				.AutoWidth()
				.Padding(8, 0, 0, 0)
				[
					SNew(SButton)
					.Text(LOCTEXT("Browse", "..."))
					.OnClicked(this, &SMixinPathDialog::OnBrowseClicked)
				]
			]

			// 预览
			+ SVerticalBox::Slot()
			.AutoHeight()
			.Padding(0, 0, 0, 16)
			[
				SNew(STextBlock)
				.Text_Lambda([this]() {
					FString PreviewPath = FPaths::Combine(TEXT("TypeScript"), SelectedPath);
					FPaths::MakeStandardFilename(PreviewPath);
					return FText::Format(LOCTEXT("Preview", "Preview: {0}"), FText::FromString(PreviewPath));
				})
				.ColorAndOpacity(FSlateColor(FLinearColor::Gray))
			]

			// 按钮
			+ SVerticalBox::Slot()
			.AutoHeight()
			.HAlign(HAlign_Right)
			[
				SNew(SHorizontalBox)

				+ SHorizontalBox::Slot()
				.AutoWidth()
				.Padding(0, 0, 8, 0)
				[
					SNew(SButton)
					.Text(LOCTEXT("Cancel", "Cancel"))
					.OnClicked(this, &SMixinPathDialog::OnCancelClicked)
				]

				+ SHorizontalBox::Slot()
				.AutoWidth()
				[
					SNew(SButton)
					.Text(LOCTEXT("Confirm", "Create"))
					.OnClicked(this, &SMixinPathDialog::OnConfirmClicked)
				]
			]
		]
	];
}

bool SMixinPathDialog::ShowDialog(const FString& DefaultPath, const FString& BlueprintName,
	FString& OutPath, FString& OutMixinName)
{
	TSharedRef<SMixinPathDialog> DialogContent = SNew(SMixinPathDialog)
		.DefaultPath(DefaultPath)
		.BlueprintName(BlueprintName)
		.DefaultMixinName(BlueprintName);

	TSharedRef<SWindow> Window = SNew(SWindow)
		.Title(LOCTEXT("WindowTitle", "Export Mixin File"))
		.SizingRule(ESizingRule::Autosized)
		.SupportsMaximize(false)
		.SupportsMinimize(false)
		[
			DialogContent
		];

	DialogContent->ParentWindow = Window;

	GEditor->EditorAddModalWindow(Window);

	if (DialogContent->IsConfirmed())
	{
		OutPath = DialogContent->GetSelectedPath();
		OutMixinName = DialogContent->GetMixinName();
		return true;
	}

	return false;
}

bool SMixinPathDialog::ShowDirectoryDialog(FString& OutDirectory, const FString& DefaultDirectory)
{
	IDesktopPlatform* DesktopPlatform = FDesktopPlatformModule::Get();
	if (!DesktopPlatform)
	{
		return false;
	}

	FString TypeScriptDir = FPaths::ConvertRelativePathToFull(FPaths::Combine(FPaths::ProjectDir(), TEXT("TypeScript")));
	FString StartDirectory = DefaultDirectory.IsEmpty() ? TypeScriptDir : FPaths::Combine(TypeScriptDir, DefaultDirectory);

	FString OutFolder;
	if (!DesktopPlatform->OpenDirectoryDialog(
		FSlateApplication::Get().GetActiveTopLevelWindow().IsValid()
			? FSlateApplication::Get().GetActiveTopLevelWindow()->GetNativeWindow()->GetOSWindowHandle()
			: nullptr,
		TEXT("Select Target Folder for Mixin Files"),
		StartDirectory,
		OutFolder))
	{
		return false;
	}

	// 转换为完整路径
	OutFolder = FPaths::ConvertRelativePathToFull(OutFolder);

	// 尝试获取相对路径
	FString RelativePath = OutFolder;
	if (!FPaths::MakePathRelativeTo(RelativePath, *FPaths::Combine(TypeScriptDir, TEXT("/"))))
	{
		// 如果无法获取相对路径（选择了 TypeScript 目录外的文件夹），返回失败
		return false;
	}

	// 移除开头的 "./" 如果有的话
	if (RelativePath.StartsWith(TEXT("./")))
	{
		RelativePath.RightChopInline(2);
	}

	// 如果是 "." 表示选择了根目录
	if (RelativePath == TEXT(".") || RelativePath.IsEmpty())
	{
		OutDirectory = TEXT("");
	}
	else
	{
		// 确保以 / 结尾
		if (!RelativePath.EndsWith(TEXT("/")))
		{
			RelativePath += TEXT("/");
		}
		OutDirectory = RelativePath;
	}

	return true;
}

FString SMixinPathDialog::GetSelectedPath() const
{
	return SelectedPath;
}

FString SMixinPathDialog::GetMixinName() const
{
	return MixinName;
}

void SMixinPathDialog::UpdatePathFromMixinName()
{
	SelectedPath = CurrentDirectory + MixinName + TEXT(".ts");
	if (PathTextBox.IsValid())
	{
		PathTextBox->SetText(FText::FromString(SelectedPath));
	}
}

FReply SMixinPathDialog::OnPresetPathClicked(FString PresetPath)
{
	CurrentDirectory = PresetPath;
	if (!CurrentDirectory.IsEmpty() && !CurrentDirectory.EndsWith(TEXT("/")))
	{
		CurrentDirectory += TEXT("/");
	}
	UpdatePathFromMixinName();
	return FReply::Handled();
}

FReply SMixinPathDialog::OnConfirmClicked()
{
	bConfirmed = true;
	CloseDialog();
	return FReply::Handled();
}

FReply SMixinPathDialog::OnCancelClicked()
{
	bConfirmed = false;
	CloseDialog();
	return FReply::Handled();
}

FReply SMixinPathDialog::OnBrowseClicked()
{
	IDesktopPlatform* DesktopPlatform = FDesktopPlatformModule::Get();
	if (DesktopPlatform)
	{
		FString TypeScriptDir = FPaths::ConvertRelativePathToFull(FPaths::Combine(FPaths::ProjectDir(), TEXT("TypeScript")));

		FString OutFolder;

		if (DesktopPlatform->OpenDirectoryDialog(
			FSlateApplication::Get().FindBestParentWindowHandleForDialogs(AsShared()),
			TEXT("Select Target Folder"),
			TypeScriptDir,
			OutFolder))
		{
			// 转换为完整路径
			OutFolder = FPaths::ConvertRelativePathToFull(OutFolder);

			// 尝试获取相对路径
			FString RelativePath = OutFolder;
			if (FPaths::MakePathRelativeTo(RelativePath, *FPaths::Combine(TypeScriptDir, TEXT("/"))))
			{
				// 成功获取相对路径
				// 移除开头的 "./" 如果有的话
				if (RelativePath.StartsWith(TEXT("./")))
				{
					RelativePath.RightChopInline(2);
				}
				// 如果是 "." 表示选择了根目录
				if (RelativePath == TEXT(".") || RelativePath.IsEmpty())
				{
					CurrentDirectory = TEXT("");
				}
				else
				{
					// 确保以 / 结尾
					if (!RelativePath.EndsWith(TEXT("/")))
					{
						RelativePath += TEXT("/");
					}
					CurrentDirectory = RelativePath;
				}

				UpdatePathFromMixinName();
			}
		}
	}
	return FReply::Handled();
}

void SMixinPathDialog::CloseDialog()
{
	if (ParentWindow.IsValid())
	{
		ParentWindow->RequestDestroyWindow();
	}
}

#undef LOCTEXT_NAMESPACE
