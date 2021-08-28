// Copyright Epic Games, Inc. All Rights Reserved.

#include "EditorDialogCreatorCommands.h"

#define LOCTEXT_NAMESPACE "FEditorDialogCreatorModule"

void FEditorDialogCreatorCommands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "Dialog", "Create new dialog", EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE
