// Copyright Epic Games, Inc. All Rights Reserved.

#include "PugiXML_Plagin.h"
#if WITH_EDITOR
	#include "DLGObjectCustomizationDetails.h"
#endif
#include "DLG_DialogItem.h"		

#define LOCTEXT_NAMESPACE "FPugiXML_PlaginModule"

void FPugiXML_PlaginModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
#if WITH_EDITOR
	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	PropertyModule.RegisterCustomClassLayout(UDLG_DialogItem::StaticClass()->GetFName()
		, FOnGetDetailCustomizationInstance::CreateStatic(&FDLGObjectCustomizationDetails::MakeInstance));
#endif
}

void FPugiXML_PlaginModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FPugiXML_PlaginModule, PugiXML_Plagin)