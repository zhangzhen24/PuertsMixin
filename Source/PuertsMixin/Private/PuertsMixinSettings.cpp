
#include "PuertsMixinSettings.h"

UPuertsMixinSettings::UPuertsMixinSettings()
	: EditorType(EPuertsMixinEditorType::VSCode)
	  , CustomEditorExecutable(TEXT("code.cmd"))
	  , MainEntryFileName(TEXT("Main.ts"))
	  , MixinRegistryFileName(TEXT("MixinRegistry.ts"))
{}

FString UPuertsMixinSettings::GetEditorCommand() const
{
	switch (EditorType)
	{
		case EPuertsMixinEditorType::VSCode:
			return TEXT("code.cmd");

		case EPuertsMixinEditorType::Custom:
			return CustomEditorExecutable.IsEmpty() ? TEXT("code.cmd") : CustomEditorExecutable;

		default:
			return TEXT("code.cmd");
	}
}
