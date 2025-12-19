#include "Toolbars/PuertsMixinEditorToolbar.h"
#include "PuertsMixinCommands.h"
#include "PuertsMixinStyle.h"
#include "Engine/Blueprint.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "HAL/PlatformFileManager.h"
#include "HAL/PlatformProcess.h"
#include "Misc/MessageDialog.h"
#include "UObject/Package.h"
#include "Editor.h"
#include "PuertsMixinSettings.h"
#include "Interfaces/IPluginManager.h"
#include "Widgets/SMixinPathDialog.h"

#define LOCTEXT_NAMESPACE "FPuertsMixinEditorToolbar"

// 静态成员初始化：记录上次导出目录
FString FPuertsMixinEditorToolbar::LastExportDirectory = TEXT("");

FPuertsMixinEditorToolbar::FPuertsMixinEditorToolbar()
	: CommandList(new FUICommandList),
	  ContextObject(nullptr)
{}

void FPuertsMixinEditorToolbar::Initialize()
{
	BindCommands();
}

void FPuertsMixinEditorToolbar::BindCommands()
{
	const auto& Commands = FPuertsMixinCommands::Get();
	CommandList->MapAction(
		Commands.PluginAction, FExecuteAction::CreateRaw(this, &FPuertsMixinEditorToolbar::Mixin_Executed)
	);
}

void FPuertsMixinEditorToolbar::BuildToolbar(FToolBarBuilder& ToolbarBuilder, UObject* InContextObject)
{
	if (!InContextObject)
		return;

	ToolbarBuilder.BeginSection(NAME_None);

	// 保存上下文对象
	ContextObject = InContextObject;

	ToolbarBuilder.AddToolBarButton(
		FPuertsMixinCommands::Get().PluginAction,
		NAME_None,
		TAttribute<FText>(),
		TAttribute<FText>(),
		FSlateIcon(FPuertsMixinStyle::GetStyleSetName(), "PuertsMixin.PluginAction")
	);

	ToolbarBuilder.EndSection();
}

TSharedRef<FExtender> FPuertsMixinEditorToolbar::GetExtender(UObject* InContextObject)
{
	TSharedRef<FExtender> ToolbarExtender(new FExtender());
	const auto ExtensionDelegate = FToolBarExtensionDelegate::CreateLambda(
		[this, InContextObject](FToolBarBuilder& ToolbarBuilder) {
			BuildToolbar(ToolbarBuilder, InContextObject);
		}
	);

	// 添加到 "Asset" 区域之后
	ToolbarExtender->AddToolBarExtension("Asset", EExtensionHook::After, CommandList, ExtensionDelegate);
	return ToolbarExtender;
}

void FPuertsMixinEditorToolbar::Mixin_Executed()
{
	UBlueprint* TargetBP = Cast<UBlueprint>(ContextObject);
	if (!TargetBP)
	{
		FMessageDialog::Open(EAppMsgType::Ok, FText::FromString(TEXT("No Blueprint context found.")));
		return;
	}

	// Blueprint 名称
	FString BPName = TargetBP->GetName();

	// Blueprint 所在 Package 路径，例如：/Game/NPC/Services/BTS_Shoot
	FString PackageName = TargetBP->GetOutermost()->GetName();

	// 去掉 /Game/ 前缀，得到相对于 Content 的路径
	FString ContentRelativePath = PackageName;
	if (ContentRelativePath.StartsWith(TEXT("/Game/")))
	{
		ContentRelativePath.RightChopInline(6); // 移除 "/Game/"
	}

	// 默认路径：使用上次导出的目录 + 蓝图名称
	FString DefaultRelativePath = LastExportDirectory + BPName + TEXT(".ts");

	// 用户选择的相对路径和类名
	FString UserSelectedPath;
	FString MixinName;

	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();

	// 显示路径选择对话框
	if (!SMixinPathDialog::ShowDialog(DefaultRelativePath, BPName, UserSelectedPath, MixinName))
	{
		// 用户取消
		return;
	}

	// 确保路径以 .ts 结尾
	if (!UserSelectedPath.EndsWith(TEXT(".ts")))
	{
		UserSelectedPath = FPaths::Combine(UserSelectedPath, MixinName + TEXT(".ts"));
	}

	// 记录本次导出的目录（供下次使用）
	FString ExportDir = FPaths::GetPath(UserSelectedPath);
	if (!ExportDir.IsEmpty() && !ExportDir.EndsWith(TEXT("/")))
	{
		ExportDir += TEXT("/");
	}
	LastExportDirectory = ExportDir;

	// 构造绝对路径
	FString AbsFilePath = FPaths::Combine(FPaths::ProjectDir(), TEXT("TypeScript"), UserSelectedPath);
	FPaths::MakeStandardFilename(AbsFilePath);

	// 计算相对路径（用于 import 路径计算）
	FString RelativePath = UserSelectedPath;
	if (RelativePath.EndsWith(TEXT(".ts")))
	{
		RelativePath.LeftChopInline(3); // 移除 ".ts"
	}

	// 确保目录存在
	FString FileDir = FPaths::GetPath(AbsFilePath);

	if (!PlatformFile.DirectoryExists(*FileDir))
	{
		PlatformFile.CreateDirectoryTree(*FileDir);
	}

	// 获取设置
	const UPuertsMixinSettings* Settings = GetDefault<UPuertsMixinSettings>();

	// 如果文件不存在，则生成 TS 模板
	if (!PlatformFile.FileExists(*AbsFilePath))
	{
		// 根据用户选择路径的层级深度计算 Mixin 的相对导入路径
		// 例如：Actors/BP_Test -> ../mixin（1层目录）
		// 例如：Blueprints/Project/Blueprint/BP_Test -> ../../../mixin（3层目录）
		TArray<FString> PathParts;
		RelativePath.ParseIntoArray(PathParts, TEXT("/"), true);

		// 目录深度 = 路径部分数量 - 1（最后一个是文件名，不计入目录深度）
		int32 DirectoryDepth = PathParts.Num() - 1;

		FString MixinImportPath;
		if (DirectoryDepth <= 0)
		{
			// 文件在 TypeScript 根目录
			MixinImportPath = TEXT("./mixin");
		}
		else
		{
			MixinImportPath = TEXT("..");
			for (int32 i = 1; i < DirectoryDepth; ++i)
			{
				MixinImportPath += TEXT("/..");
			}
			MixinImportPath += TEXT("/mixin");
		}

		// Blueprint 生成类路径（Puerts 使用）
		FString ClassPath = TargetBP->GetPathName() + TEXT("_C");

		// 生成 TS 类型路径（UE.Game.[目录].[蓝图名].[蓝图名]_C）
		// 注意：这里使用蓝图的 Content 路径，而不是用户选择的 TypeScript 路径
		TArray<FString> ContentPathParts;
		ContentRelativePath.ParseIntoArray(ContentPathParts, TEXT("/"), true);

		FString TsTypePath = TEXT("UE.Game");
		if (ContentPathParts.Num() > 0)
		{
			for (int32 i = 0; i < ContentPathParts.Num() - 1; ++i)
			{
				TsTypePath += TEXT(".");
				TsTypePath += ContentPathParts[i];
			}
			const FString& BPShortName = ContentPathParts.Last();
			TsTypePath += TEXT(".");
			TsTypePath += BPShortName;
			TsTypePath += TEXT(".");
			TsTypePath += BPShortName;
			TsTypePath += TEXT("_C");
		}
		else
		{
			TsTypePath += TEXT(".");
			TsTypePath += BPName;
			TsTypePath += TEXT(".");
			TsTypePath += BPName;
			TsTypePath += TEXT("_C");
		}

		// 查找并应用模板
		// 1. 从当前类开始向上遍历继承链
		// 2. 查找 Config/TSTemplates/<ClassName>.ts
		// 3. 优先查找 ProjectConfigDir，其次查找 PluginConfigDir
		static FString BaseDir = IPluginManager::Get().FindPlugin(TEXT("PuertsMixin"))->GetBaseDir();

		UClass* Class = TargetBP->GeneratedClass;
		FString Content;
		bool bTemplateFound = false;

		for (auto TemplateClass = Class; TemplateClass; TemplateClass = TemplateClass->GetSuperClass())
		{
			// 处理类名后缀（_C）
			FString TemplateClassName = TemplateClass->GetName();
			if (TemplateClassName.EndsWith(TEXT("_C")))
			{
				TemplateClassName.LeftChopInline(2);
			}

			// 构造相对路径：Config/TSTemplates/ClassName.ts
			FString RelativeFilePath = FPaths::Combine(
				TEXT("Config/TSTemplates"), TemplateClassName + TEXT(".ts")
			);

			// 检查项目配置目录
			FString FullFilePath = FPaths::Combine(FPaths::ProjectConfigDir(), RelativeFilePath);
			if (!FPaths::FileExists(FullFilePath))
			{
				// 检查插件配置目录
				FullFilePath = FPaths::Combine(BaseDir, RelativeFilePath);
			}

			// 如果找到了模板文件
			if (FPaths::FileExists(FullFilePath))
			{
				if (FFileHelper::LoadFileToString(Content, *FullFilePath))
				{
					// 替换占位符
					Content = Content.Replace(TEXT("{BPName}"), *BPName)
									 .Replace(TEXT("{MixinName}"), *MixinName)
									 .Replace(TEXT("{PackageName}"), *PackageName)
									 .Replace(TEXT("{MixinImportPath}"), *MixinImportPath)
									 .Replace(TEXT("{AssetPath}"), *ClassPath)
									 .Replace(TEXT("{TsTypePath}"), *TsTypePath);

					bTemplateFound = true;
					break;
				}
			}
		}

		// 如果没有找到特定模板，使用默认 Object 模板
		if (!bTemplateFound)
		{
			// 尝试加载 Object.ts 作为默认回退
			FString DefaultTemplatePath = FPaths::Combine(BaseDir, TEXT("Config/TSTemplates/Object.ts"));
			if (FPaths::FileExists(DefaultTemplatePath))
			{
				if (FFileHelper::LoadFileToString(Content, *DefaultTemplatePath))
				{
					Content = Content.Replace(TEXT("{BPName}"), *BPName)
									 .Replace(TEXT("{MixinName}"), *MixinName)
									 .Replace(TEXT("{PackageName}"), *PackageName)
									 .Replace(TEXT("{MixinImportPath}"), *MixinImportPath)
									 .Replace(TEXT("{AssetPath}"), *ClassPath)
									 .Replace(TEXT("{TsTypePath}"), *TsTypePath);
					bTemplateFound = true;
				}
			}
		}

		// 如果依然没有内容（极少情况），使用硬编码的回退内容
		if (!bTemplateFound)
		{
			Content = FString::Printf(
				TEXT(
					"import * as UE from \"ue\";\n"
					"import mixin from \"%s\";\n\n"
					"const AssetPath = \"%s\";\n\n"
					"@mixin(AssetPath)\n"
					"export class %s implements %s {\n"
					"}\n"
				),
				*MixinImportPath,
				*ClassPath,
				*MixinName,
				*TsTypePath
			);
		}

		// 写入文件
		FFileHelper::SaveStringToFile(Content, *AbsFilePath);

		// -------------------------------------------------------------------------
		// 自动注册 Mixin 类到注册文件
		// -------------------------------------------------------------------------
		FString RegistryFileName = Settings->MixinRegistryFileName;
		if (RegistryFileName.IsEmpty())
		{
			RegistryFileName = TEXT("MixinRegistry.ts");
		}

		// 注册文件绝对路径：<Project>/TypeScript/MixinRegistry.ts
		FString RegistryFilePath = FPaths::Combine(FPaths::ProjectDir(), TEXT("TypeScript"), RegistryFileName);
		FPaths::MakeStandardFilename(RegistryFilePath);

		FString RegistryContent;

		// 如果文件不存在，创建并添加注释头
		if (!PlatformFile.FileExists(*RegistryFilePath))
		{
			RegistryContent = TEXT("// Mixin Registry - 自动生成，请勿手动编辑\r\n// Auto-generated Mixin imports\r\n\r\n");
		}
		else
		{
			FFileHelper::LoadFileToString(RegistryContent, *RegistryFilePath);
		}

		// 计算相对导入路径
		// Generated TS: TypeScript/Actors/BP_Test.ts
		// Registry TS: TypeScript/MixinRegistry.ts
		// Relative: ./Actors/BP_Test
		FString ImportPath = TEXT("./") + RelativePath;
		// 将 Windows 路径分隔符替换为 /
		ImportPath.ReplaceInline(TEXT("\\"), TEXT("/"));

		// 检查是否已经包含该导入
		if (!RegistryContent.Contains(ImportPath))
		{
			FString ImportStmt = FString::Printf(TEXT("import '%s';"), *ImportPath);

			// 解析文件：分离注释头和 import 语句
			TArray<FString> Lines;
			RegistryContent.ParseIntoArrayLines(Lines);

			TArray<FString> HeaderLines;
			TArray<FString> ImportLines;

			for (const FString& Line : Lines)
			{
				FString TrimmedLine = Line.TrimStartAndEnd();
				if (TrimmedLine.StartsWith(TEXT("import ")))
				{
					ImportLines.Add(TrimmedLine);
				}
				else if (TrimmedLine.StartsWith(TEXT("//")) || TrimmedLine.IsEmpty())
				{
					// 只有在还没有遇到 import 语句时才添加到 header
					if (ImportLines.Num() == 0)
					{
						HeaderLines.Add(Line);
					}
				}
			}

			// 添加新的 import
			ImportLines.Add(ImportStmt);

			// 排序 import 语句
			ImportLines.Sort();

			// 重建文件内容
			FString NewContent;
			for (const FString& HeaderLine : HeaderLines)
			{
				NewContent += HeaderLine + TEXT("\r\n");
			}
			if (HeaderLines.Num() > 0 && !HeaderLines.Last().IsEmpty())
			{
				NewContent += TEXT("\r\n");
			}
			for (const FString& ImportLine : ImportLines)
			{
				NewContent += ImportLine + TEXT("\r\n");
			}

			FFileHelper::SaveStringToFile(NewContent, *RegistryFilePath);
		}
	}

	// 从配置获取编辑器启动命令与类型
	const FString EditorCommand             = Settings->GetEditorCommand();
	const EPuertsMixinEditorType EditorType = Settings->EditorType;

	// 根据类型构造命令行
	FString ProcExecutable;
	FString ProcArgs;

	if (EditorType == EPuertsMixinEditorType::VSCode)
	{
		// 标准 VSCode 类编辑器：-r -g "file:line"
		const FString CmdArgs = FString::Printf(TEXT("-r -g \"%s:%d\""), *AbsFilePath, 1);

		// 检查是否是脚本文件
		if (EditorCommand.EndsWith(TEXT(".cmd")) || EditorCommand.EndsWith(TEXT(".bat")))
		{
			ProcExecutable = TEXT("cmd.exe");
			ProcArgs       = FString::Printf(TEXT("/c %s %s"), *EditorCommand, *CmdArgs);
		}
		else
		{
			ProcExecutable = EditorCommand;
			ProcArgs       = CmdArgs;
		}
	}
	else // Custom
	{
		// 自定义编辑器
		FString CmdArgs = FString::Printf(TEXT("\"%s\""), *AbsFilePath); // 默认只传文件路径

		// 如果自定义编辑器也支持 code 风格参数，可以在这里扩展逻辑，暂时按最安全的方式处理

		if (EditorCommand.EndsWith(TEXT(".cmd")) || EditorCommand.EndsWith(TEXT(".bat")))
		{
			ProcExecutable = TEXT("cmd.exe");
			ProcArgs       = FString::Printf(TEXT("/c %s %s"), *EditorCommand, *CmdArgs);
		}
		else
		{
			ProcExecutable = EditorCommand;
			ProcArgs       = CmdArgs;
		}
	}

	// 执行外部进程
	{
		FProcHandle Handle = FPlatformProcess::CreateProc(
			*ProcExecutable,
			*ProcArgs,
			true,
			false,
			false,
			nullptr,
			0,
			nullptr,
			nullptr
		);

		// 1. 执行 Puerts.Gen 命令，确保 TS 类型定义是最新的
		// 这样生成的 TS 文件中引用的 Blueprint 类型才有效
		if (GEditor)
		{
			GEditor->Exec(nullptr, TEXT("Puerts.Gen"), *GLog);
		}
		
		if (!Handle.IsValid())
		{
			FMessageDialog::Open(
				EAppMsgType::Ok, FText::Format(
					FText::FromString(TEXT("Failed to launch editor: {0}")), FText::FromString(EditorCommand)
				)
			);
		}
	}
}

void FPuertsMixinEditorToolbar::CreateMixinForBlueprint(UBlueprint* TargetBP)
{
	if (!TargetBP)
	{
		FMessageDialog::Open(EAppMsgType::Ok, FText::FromString(TEXT("No Blueprint provided.")));
		return;
	}

	// Blueprint 名称
	FString BPName = TargetBP->GetName();

	// Blueprint 所在 Package 路径，例如：/Game/NPC/Services/BTS_Shoot
	FString PackageName = TargetBP->GetOutermost()->GetName();

	// 去掉 /Game/ 前缀，得到相对于 Content 的路径
	FString ContentRelativePath = PackageName;
	if (ContentRelativePath.StartsWith(TEXT("/Game/")))
	{
		ContentRelativePath.RightChopInline(6); // 移除 "/Game/"
	}

	// 默认路径：使用上次导出的目录 + 蓝图名称
	FString DefaultRelativePath = LastExportDirectory + BPName + TEXT(".ts");

	// 用户选择的相对路径和类名
	FString UserSelectedPath;
	FString MixinName;

	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();

	// 显示路径选择对话框
	if (!SMixinPathDialog::ShowDialog(DefaultRelativePath, BPName, UserSelectedPath, MixinName))
	{
		// 用户取消
		return;
	}

	// 确保路径以 .ts 结尾
	if (!UserSelectedPath.EndsWith(TEXT(".ts")))
	{
		UserSelectedPath = FPaths::Combine(UserSelectedPath, MixinName + TEXT(".ts"));
	}

	// 记录本次导出的目录（供下次使用）
	FString ExportDir = FPaths::GetPath(UserSelectedPath);
	if (!ExportDir.IsEmpty() && !ExportDir.EndsWith(TEXT("/")))
	{
		ExportDir += TEXT("/");
	}
	LastExportDirectory = ExportDir;

	// 构造绝对路径
	FString AbsFilePath = FPaths::Combine(FPaths::ProjectDir(), TEXT("TypeScript"), UserSelectedPath);
	FPaths::MakeStandardFilename(AbsFilePath);

	// 计算相对路径（用于 import 路径计算）
	FString RelativePath = UserSelectedPath;
	if (RelativePath.EndsWith(TEXT(".ts")))
	{
		RelativePath.LeftChopInline(3); // 移除 ".ts"
	}

	// 确保目录存在
	FString FileDir = FPaths::GetPath(AbsFilePath);

	if (!PlatformFile.DirectoryExists(*FileDir))
	{
		PlatformFile.CreateDirectoryTree(*FileDir);
	}

	// 获取设置
	const UPuertsMixinSettings* Settings = GetDefault<UPuertsMixinSettings>();

	// 如果文件不存在，则生成 TS 模板
	if (!PlatformFile.FileExists(*AbsFilePath))
	{
		// 根据用户选择路径的层级深度计算 Mixin 的相对导入路径
		TArray<FString> PathParts;
		RelativePath.ParseIntoArray(PathParts, TEXT("/"), true);

		int32 DirectoryDepth = PathParts.Num() - 1;

		FString MixinImportPath;
		if (DirectoryDepth <= 0)
		{
			MixinImportPath = TEXT("./mixin");
		}
		else
		{
			MixinImportPath = TEXT("..");
			for (int32 i = 1; i < DirectoryDepth; ++i)
			{
				MixinImportPath += TEXT("/..");
			}
			MixinImportPath += TEXT("/mixin");
		}

		// Blueprint 生成类路径（Puerts 使用）
		FString ClassPath = TargetBP->GetPathName() + TEXT("_C");

		// 生成 TS 类型路径
		TArray<FString> ContentPathParts;
		ContentRelativePath.ParseIntoArray(ContentPathParts, TEXT("/"), true);

		FString TsTypePath = TEXT("UE.Game");
		if (ContentPathParts.Num() > 0)
		{
			for (int32 i = 0; i < ContentPathParts.Num() - 1; ++i)
			{
				TsTypePath += TEXT(".");
				TsTypePath += ContentPathParts[i];
			}
			const FString& BPShortName = ContentPathParts.Last();
			TsTypePath += TEXT(".");
			TsTypePath += BPShortName;
			TsTypePath += TEXT(".");
			TsTypePath += BPShortName;
			TsTypePath += TEXT("_C");
		}
		else
		{
			TsTypePath += TEXT(".");
			TsTypePath += BPName;
			TsTypePath += TEXT(".");
			TsTypePath += BPName;
			TsTypePath += TEXT("_C");
		}

		// 查找并应用模板
		static FString BaseDir = IPluginManager::Get().FindPlugin(TEXT("PuertsMixin"))->GetBaseDir();

		UClass* Class = TargetBP->GeneratedClass;
		FString Content;
		bool bTemplateFound = false;

		for (auto TemplateClass = Class; TemplateClass; TemplateClass = TemplateClass->GetSuperClass())
		{
			FString TemplateClassName = TemplateClass->GetName();
			if (TemplateClassName.EndsWith(TEXT("_C")))
			{
				TemplateClassName.LeftChopInline(2);
			}

			FString RelativeFilePath = FPaths::Combine(
				TEXT("Config/TSTemplates"), TemplateClassName + TEXT(".ts")
			);

			FString FullFilePath = FPaths::Combine(FPaths::ProjectConfigDir(), RelativeFilePath);
			if (!FPaths::FileExists(FullFilePath))
			{
				FullFilePath = FPaths::Combine(BaseDir, RelativeFilePath);
			}

			if (FPaths::FileExists(FullFilePath))
			{
				if (FFileHelper::LoadFileToString(Content, *FullFilePath))
				{
					Content = Content.Replace(TEXT("{BPName}"), *BPName)
									 .Replace(TEXT("{MixinName}"), *MixinName)
									 .Replace(TEXT("{PackageName}"), *PackageName)
									 .Replace(TEXT("{MixinImportPath}"), *MixinImportPath)
									 .Replace(TEXT("{AssetPath}"), *ClassPath)
									 .Replace(TEXT("{TsTypePath}"), *TsTypePath);

					bTemplateFound = true;
					break;
				}
			}
		}

		if (!bTemplateFound)
		{
			FString DefaultTemplatePath = FPaths::Combine(BaseDir, TEXT("Config/TSTemplates/Object.ts"));
			if (FPaths::FileExists(DefaultTemplatePath))
			{
				if (FFileHelper::LoadFileToString(Content, *DefaultTemplatePath))
				{
					Content = Content.Replace(TEXT("{BPName}"), *BPName)
									 .Replace(TEXT("{MixinName}"), *MixinName)
									 .Replace(TEXT("{PackageName}"), *PackageName)
									 .Replace(TEXT("{MixinImportPath}"), *MixinImportPath)
									 .Replace(TEXT("{AssetPath}"), *ClassPath)
									 .Replace(TEXT("{TsTypePath}"), *TsTypePath);
					bTemplateFound = true;
				}
			}
		}

		if (!bTemplateFound)
		{
			Content = FString::Printf(
				TEXT(
					"import * as UE from \"ue\";\n"
					"import mixin from \"%s\";\n\n"
					"const AssetPath = \"%s\";\n\n"
					"@mixin(AssetPath)\n"
					"export class %s implements %s {\n"
					"}\n"
				),
				*MixinImportPath,
				*ClassPath,
				*MixinName,
				*TsTypePath
			);
		}

		FFileHelper::SaveStringToFile(Content, *AbsFilePath);

		// 自动注册到 MixinRegistry.ts
		FString RegistryFileName = Settings->MixinRegistryFileName;
		if (RegistryFileName.IsEmpty())
		{
			RegistryFileName = TEXT("MixinRegistry.ts");
		}

		FString RegistryFilePath = FPaths::Combine(FPaths::ProjectDir(), TEXT("TypeScript"), RegistryFileName);
		FPaths::MakeStandardFilename(RegistryFilePath);

		FString RegistryContent;

		// 如果文件不存在，创建并添加注释头
		if (!PlatformFile.FileExists(*RegistryFilePath))
		{
			RegistryContent = TEXT("// Mixin Registry - 自动生成，请勿手动编辑\r\n// Auto-generated Mixin imports\r\n\r\n");
		}
		else
		{
			FFileHelper::LoadFileToString(RegistryContent, *RegistryFilePath);
		}

		FString ImportPath = TEXT("./") + RelativePath;
		ImportPath.ReplaceInline(TEXT("\\"), TEXT("/"));

		if (!RegistryContent.Contains(ImportPath))
		{
			FString ImportStmt = FString::Printf(TEXT("import '%s';"), *ImportPath);

			// 解析文件：分离注释头和 import 语句
			TArray<FString> Lines;
			RegistryContent.ParseIntoArrayLines(Lines);

			TArray<FString> HeaderLines;
			TArray<FString> ImportLines;

			for (const FString& Line : Lines)
			{
				FString TrimmedLine = Line.TrimStartAndEnd();
				if (TrimmedLine.StartsWith(TEXT("import ")))
				{
					ImportLines.Add(TrimmedLine);
				}
				else if (TrimmedLine.StartsWith(TEXT("//")) || TrimmedLine.IsEmpty())
				{
					if (ImportLines.Num() == 0)
					{
						HeaderLines.Add(Line);
					}
				}
			}

			ImportLines.Add(ImportStmt);
			ImportLines.Sort();

			FString NewContent;
			for (const FString& HeaderLine : HeaderLines)
			{
				NewContent += HeaderLine + TEXT("\r\n");
			}
			if (HeaderLines.Num() > 0 && !HeaderLines.Last().IsEmpty())
			{
				NewContent += TEXT("\r\n");
			}
			for (const FString& ImportLine : ImportLines)
			{
				NewContent += ImportLine + TEXT("\r\n");
			}

			FFileHelper::SaveStringToFile(NewContent, *RegistryFilePath);
		}
	}

	// 启动编辑器
	const FString EditorCommand = Settings->GetEditorCommand();
	const EPuertsMixinEditorType EditorType = Settings->EditorType;

	FString ProcExecutable;
	FString ProcArgs;

	if (EditorType == EPuertsMixinEditorType::VSCode)
	{
		const FString CmdArgs = FString::Printf(TEXT("-r -g \"%s:%d\""), *AbsFilePath, 1);

		if (EditorCommand.EndsWith(TEXT(".cmd")) || EditorCommand.EndsWith(TEXT(".bat")))
		{
			ProcExecutable = TEXT("cmd.exe");
			ProcArgs = FString::Printf(TEXT("/c %s %s"), *EditorCommand, *CmdArgs);
		}
		else
		{
			ProcExecutable = EditorCommand;
			ProcArgs = CmdArgs;
		}
	}
	else
	{
		FString CmdArgs = FString::Printf(TEXT("\"%s\""), *AbsFilePath);

		if (EditorCommand.EndsWith(TEXT(".cmd")) || EditorCommand.EndsWith(TEXT(".bat")))
		{
			ProcExecutable = TEXT("cmd.exe");
			ProcArgs = FString::Printf(TEXT("/c %s %s"), *EditorCommand, *CmdArgs);
		}
		else
		{
			ProcExecutable = EditorCommand;
			ProcArgs = CmdArgs;
		}
	}

	FProcHandle Handle = FPlatformProcess::CreateProc(
		*ProcExecutable,
		*ProcArgs,
		true,
		false,
		false,
		nullptr,
		0,
		nullptr,
		nullptr
	);

	if (GEditor)
	{
		GEditor->Exec(nullptr, TEXT("Puerts.Gen"), *GLog);
	}

	if (!Handle.IsValid())
	{
		FMessageDialog::Open(
			EAppMsgType::Ok, FText::Format(
				FText::FromString(TEXT("Failed to launch editor: {0}")), FText::FromString(EditorCommand)
			)
		);
	}
}

void FPuertsMixinEditorToolbar::CreateMixinsForBlueprints(const TArray<UBlueprint*>& Blueprints, const FString& TargetDirectory)
{
	if (Blueprints.Num() == 0)
	{
		return;
	}

	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
	const UPuertsMixinSettings* Settings = GetDefault<UPuertsMixinSettings>();
	static FString BaseDir = IPluginManager::Get().FindPlugin(TEXT("PuertsMixin"))->GetBaseDir();

	TArray<FString> CreatedFiles;

	for (UBlueprint* TargetBP : Blueprints)
	{
		if (!TargetBP)
		{
			continue;
		}

		// Blueprint 名称
		FString BPName = TargetBP->GetName();

		// 批量导出时，MixinName 默认使用蓝图名称
		FString MixinName = BPName;

		// Blueprint 所在 Package 路径
		FString PackageName = TargetBP->GetOutermost()->GetName();

		// 去掉 /Game/ 前缀
		FString ContentRelativePath = PackageName;
		if (ContentRelativePath.StartsWith(TEXT("/Game/")))
		{
			ContentRelativePath.RightChopInline(6);
		}

		// 构造文件路径（使用 MixinName 作为文件名）
		FString UserSelectedPath = TargetDirectory + MixinName + TEXT(".ts");

		// 构造绝对路径
		FString AbsFilePath = FPaths::Combine(FPaths::ProjectDir(), TEXT("TypeScript"), UserSelectedPath);
		FPaths::MakeStandardFilename(AbsFilePath);

		// 计算相对路径
		FString RelativePath = UserSelectedPath;
		if (RelativePath.EndsWith(TEXT(".ts")))
		{
			RelativePath.LeftChopInline(3);
		}

		// 确保目录存在
		FString FileDir = FPaths::GetPath(AbsFilePath);
		if (!PlatformFile.DirectoryExists(*FileDir))
		{
			PlatformFile.CreateDirectoryTree(*FileDir);
		}

		// 如果文件已存在则跳过
		if (PlatformFile.FileExists(*AbsFilePath))
		{
			continue;
		}

		// 计算 MixinImportPath
		TArray<FString> PathParts;
		RelativePath.ParseIntoArray(PathParts, TEXT("/"), true);

		int32 DirectoryDepth = PathParts.Num() - 1;

		FString MixinImportPath;
		if (DirectoryDepth <= 0)
		{
			MixinImportPath = TEXT("./mixin");
		}
		else
		{
			MixinImportPath = TEXT("..");
			for (int32 i = 1; i < DirectoryDepth; ++i)
			{
				MixinImportPath += TEXT("/..");
			}
			MixinImportPath += TEXT("/mixin");
		}

		// Blueprint 生成类路径
		FString ClassPath = TargetBP->GetPathName() + TEXT("_C");

		// 生成 TS 类型路径
		TArray<FString> ContentPathParts;
		ContentRelativePath.ParseIntoArray(ContentPathParts, TEXT("/"), true);

		FString TsTypePath = TEXT("UE.Game");
		if (ContentPathParts.Num() > 0)
		{
			for (int32 i = 0; i < ContentPathParts.Num() - 1; ++i)
			{
				TsTypePath += TEXT(".");
				TsTypePath += ContentPathParts[i];
			}
			const FString& BPShortName = ContentPathParts.Last();
			TsTypePath += TEXT(".");
			TsTypePath += BPShortName;
			TsTypePath += TEXT(".");
			TsTypePath += BPShortName;
			TsTypePath += TEXT("_C");
		}
		else
		{
			TsTypePath += TEXT(".");
			TsTypePath += BPName;
			TsTypePath += TEXT(".");
			TsTypePath += BPName;
			TsTypePath += TEXT("_C");
		}

		// 查找并应用模板
		UClass* Class = TargetBP->GeneratedClass;
		FString Content;
		bool bTemplateFound = false;

		for (auto TemplateClass = Class; TemplateClass; TemplateClass = TemplateClass->GetSuperClass())
		{
			FString TemplateClassName = TemplateClass->GetName();
			if (TemplateClassName.EndsWith(TEXT("_C")))
			{
				TemplateClassName.LeftChopInline(2);
			}

			FString RelativeFilePath = FPaths::Combine(
				TEXT("Config/TSTemplates"), TemplateClassName + TEXT(".ts")
			);

			FString FullFilePath = FPaths::Combine(FPaths::ProjectConfigDir(), RelativeFilePath);
			if (!FPaths::FileExists(FullFilePath))
			{
				FullFilePath = FPaths::Combine(BaseDir, RelativeFilePath);
			}

			if (FPaths::FileExists(FullFilePath))
			{
				if (FFileHelper::LoadFileToString(Content, *FullFilePath))
				{
					Content = Content.Replace(TEXT("{BPName}"), *BPName)
									 .Replace(TEXT("{MixinName}"), *MixinName)
									 .Replace(TEXT("{PackageName}"), *PackageName)
									 .Replace(TEXT("{MixinImportPath}"), *MixinImportPath)
									 .Replace(TEXT("{AssetPath}"), *ClassPath)
									 .Replace(TEXT("{TsTypePath}"), *TsTypePath);

					bTemplateFound = true;
					break;
				}
			}
		}

		if (!bTemplateFound)
		{
			FString DefaultTemplatePath = FPaths::Combine(BaseDir, TEXT("Config/TSTemplates/Object.ts"));
			if (FPaths::FileExists(DefaultTemplatePath))
			{
				if (FFileHelper::LoadFileToString(Content, *DefaultTemplatePath))
				{
					Content = Content.Replace(TEXT("{BPName}"), *BPName)
									 .Replace(TEXT("{MixinName}"), *MixinName)
									 .Replace(TEXT("{PackageName}"), *PackageName)
									 .Replace(TEXT("{MixinImportPath}"), *MixinImportPath)
									 .Replace(TEXT("{AssetPath}"), *ClassPath)
									 .Replace(TEXT("{TsTypePath}"), *TsTypePath);
					bTemplateFound = true;
				}
			}
		}

		if (!bTemplateFound)
		{
			Content = FString::Printf(
				TEXT(
					"import * as UE from \"ue\";\n"
					"import mixin from \"%s\";\n\n"
					"const AssetPath = \"%s\";\n\n"
					"@mixin(AssetPath)\n"
					"export class %s implements %s {\n"
					"}\n"
				),
				*MixinImportPath,
				*ClassPath,
				*MixinName,
				*TsTypePath
			);
		}

		FFileHelper::SaveStringToFile(Content, *AbsFilePath);
		CreatedFiles.Add(RelativePath);

		// 自动注册到 MixinRegistry.ts
		FString RegistryFileName = Settings->MixinRegistryFileName;
		if (RegistryFileName.IsEmpty())
		{
			RegistryFileName = TEXT("MixinRegistry.ts");
		}

		FString RegistryFilePath = FPaths::Combine(FPaths::ProjectDir(), TEXT("TypeScript"), RegistryFileName);
		FPaths::MakeStandardFilename(RegistryFilePath);

		FString RegistryContent;

		// 如果文件不存在，创建并添加注释头
		if (!PlatformFile.FileExists(*RegistryFilePath))
		{
			RegistryContent = TEXT("// Mixin Registry - 自动生成，请勿手动编辑\r\n// Auto-generated Mixin imports\r\n\r\n");
		}
		else
		{
			FFileHelper::LoadFileToString(RegistryContent, *RegistryFilePath);
		}

		FString ImportPath = TEXT("./") + RelativePath;
		ImportPath.ReplaceInline(TEXT("\\"), TEXT("/"));

		if (!RegistryContent.Contains(ImportPath))
		{
			FString ImportStmt = FString::Printf(TEXT("import '%s';"), *ImportPath);

			// 解析文件：分离注释头和 import 语句
			TArray<FString> Lines;
			RegistryContent.ParseIntoArrayLines(Lines);

			TArray<FString> HeaderLines;
			TArray<FString> ImportLines;

			for (const FString& Line : Lines)
			{
				FString TrimmedLine = Line.TrimStartAndEnd();
				if (TrimmedLine.StartsWith(TEXT("import ")))
				{
					ImportLines.Add(TrimmedLine);
				}
				else if (TrimmedLine.StartsWith(TEXT("//")) || TrimmedLine.IsEmpty())
				{
					if (ImportLines.Num() == 0)
					{
						HeaderLines.Add(Line);
					}
				}
			}

			ImportLines.Add(ImportStmt);
			ImportLines.Sort();

			FString NewContent;
			for (const FString& HeaderLine : HeaderLines)
			{
				NewContent += HeaderLine + TEXT("\r\n");
			}
			if (HeaderLines.Num() > 0 && !HeaderLines.Last().IsEmpty())
			{
				NewContent += TEXT("\r\n");
			}
			for (const FString& ImportLine : ImportLines)
			{
				NewContent += ImportLine + TEXT("\r\n");
			}

			FFileHelper::SaveStringToFile(NewContent, *RegistryFilePath);
		}
	}

	// 执行 Puerts.Gen
	if (GEditor && CreatedFiles.Num() > 0)
	{
		GEditor->Exec(nullptr, TEXT("Puerts.Gen"), *GLog);
	}

	// 显示结果
	if (CreatedFiles.Num() > 0)
	{
		FString Message = FString::Printf(TEXT("Created %d Mixin file(s):\n"), CreatedFiles.Num());
		for (const FString& File : CreatedFiles)
		{
			Message += TEXT("  - ") + File + TEXT(".ts\n");
		}
		FMessageDialog::Open(EAppMsgType::Ok, FText::FromString(Message));
	}
	else
	{
		FMessageDialog::Open(EAppMsgType::Ok, FText::FromString(TEXT("No new Mixin files created (files may already exist).")));
	}
}

#undef LOCTEXT_NAMESPACE
