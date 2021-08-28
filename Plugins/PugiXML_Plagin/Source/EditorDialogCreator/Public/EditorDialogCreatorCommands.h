// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "EditorDialogCreatorStyle.h"

class FEditorDialogCreatorCommands : public TCommands<FEditorDialogCreatorCommands>
{
public:

	FEditorDialogCreatorCommands()
		: TCommands<FEditorDialogCreatorCommands>(TEXT("PugiXML_Plagin"), NSLOCTEXT("Contexts", "PugiXML_Plagin", "PugiXML_Plagin Plugin"), NAME_None, FEditorDialogCreatorStyle::GetStyleSetName())
		//: TCommands<FEditorDialogCreatorCommands>(TEXT("EditorWindowsPlugin"), NSLOCTEXT("Contexts", "EditorWindowsPlugin", "EditorWindowsPlugin Plugin"), NAME_None, FEditorDialogCreatorStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > OpenPluginWindow;
};