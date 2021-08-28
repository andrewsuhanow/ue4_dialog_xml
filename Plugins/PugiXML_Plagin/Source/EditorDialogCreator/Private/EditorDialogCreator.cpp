// Copyright Epic Games, Inc. All Rights Reserved.

#include "EditorDialogCreator.h"
#include "EditorDialogCreatorStyle.h"    
#include "EditorDialogCreatorCommands.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "ToolMenus.h"



#include "SDialogWindowWidget.h"
//#include "widgets/SCanvas.h"
//#include "Widgets/SBoxPanel.h"   //  VerticalBox, HorisontalBox
//#include "Widgets/SOverlay.h"

static const FName EditorWindowsPluginTabName("EditorDialogCreator");

#define LOCTEXT_NAMESPACE "FEditorDialogCreatorModule"

void FEditorDialogCreatorModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FEditorDialogCreatorStyle::Initialize();
	FEditorDialogCreatorStyle::ReloadTextures();

	FEditorDialogCreatorCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FEditorDialogCreatorCommands::Get().OpenPluginWindow,
		FExecuteAction::CreateRaw(this, &FEditorDialogCreatorModule::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FEditorDialogCreatorModule::RegisterMenus));
	
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(EditorWindowsPluginTabName, FOnSpawnTab::CreateRaw(this, &FEditorDialogCreatorModule::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("FEditorWindowsPluginTabTitle", "MyNewWindow_NAME"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);
}

void FEditorDialogCreatorModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FEditorDialogCreatorStyle::Shutdown();

	FEditorDialogCreatorCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(EditorWindowsPluginTabName);
}

TSharedRef<SDockTab> FEditorDialogCreatorModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{


	//  test
	UE_LOG(LogTemp, Warning, TEXT("int = '%s'"), *PathToCurrentXML);


	//FText WidgetText = FText::Format(
	//	LOCTEXT("WindowWidgetText", "Add code to {0} in {1} to override this window's contents"),
	//	FText::FromString(TEXT("FEditorDialogCreatorModule::OnSpawnPluginTab")),
	//	FText::FromString(TEXT("EditorDialogCreator.cpp"))
	//	);

	//const FDockTabStyle* GenericTabStyle = &FCoreStyle::Get().GetWidgetStyle<FDockTabStyle>("Docking.Tab");
	//TSharedPtr<SDialogWindowWidget> DialogWindow;

	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
	/*			SNew(SCanvas)
					+ SCanvas::Slot()
					//.Position(CurrentPanelPosition)
					//.Position(FVector2D(ViewportSize.X - GameInstance->MiniMapSize.X, 0.f))
					.Size(FVector2D(200, 50))
					.HAlign(HAlign_Fill)
					.VAlign(VAlign_Fill)
					[

						SNew(SVerticalBox)
							+ SVerticalBox::Slot()
							.HAlign(HAlign_Fill)
							.VAlign(VAlign_Fill)
							[
								//  ==========  TOP gorisontal Panel   ===============
								SNew(SHorizontalBox)
								.Visibility(EVisibility::Visible)

									+ SHorizontalBox::Slot()
									[
										SNew(SButton)
										//.OnClicked(this, &FEditorDialogCreatorModule::ButtonContentDialog_Presed, FName("dlg_content"))
										//[
										//	SNew(STextBlock)
										//	.Text(FText::FromString(TEXT("Content dialo")))
										//]
									]
									+ SHorizontalBox::Slot()
									[
										SNew(SButton)
										//.OnClicked(this, &FEditorDialogCreatorModule::ButtonContentDialog_Presed, FName("var"))
										.OnClicked(this, &FEditorDialogCreatorModule::ButtonContentDialog_Presed, 1)
										//.OnPressed(this, &FEditorDialogCreatorModule::ButtonContentDialog_Presed, 1)
										[
											SNew(STextBlock)
											.Text(FText::FromString(TEXT("Variables")))
										]
									]
									//+ SHorizontalBox::Slot()
									//.AutoWidth()
									//.VAlign(VAlign_Center)
									//.Padding(0, 0, 5, 0)
									////.HAlign(HAlign_Left)
									//.HAlign(HAlign_Fill)
									//.VAlign(VAlign_Fill)
									//[
									//	SNew(STextBlock)
									//	.Text(FText::FromString(TEXT("Tab_1")))
									//]

							]

							+ SVerticalBox::Slot()
							.HAlign(HAlign_Fill)
							.VAlign(VAlign_Fill)
							[
								// tab content area
								SAssignNew(ContentAreaOverlay, SOverlay)

								+ SOverlay::Slot()
									[
									//// content goes here
									//SAssignNew(ContentSlot, SBorder)
									//.BorderImage(this, &SDockingTabStack::GetContentAreaBrush)
									//.Padding(this, &SDockingTabStack::GetContentPadding)
									//.Clipping(EWidgetClipping::ClipToBounds)
									//[
										SNew(STextBlock)
										.Text(LOCTEXT("EmptyTabMessage", "Empty Tab!"))
									//]
								]
							]
					]
			];
			*/
			// Put your tab content here!
/*			SNew(SBox)
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			[
				//--------------------
				SNew(SHorizontalBox)
				.Visibility(EVisibility::Visible)
				//.ToolTip(InArgs._ToolTip)

				//// Tab Label
				+ SHorizontalBox::Slot()
				.FillWidth(1.0f)
				.Padding(0.0f, 1.0f)
				.VAlign(VAlign_Center)
				[
					//SAssignNew(LabelWidget, STextBlock)      //  TSharedPtr<STextBlock> LabelWidget;
					SNew(STextBlock)
					.TextStyle(FCoreStyle::Get(), "Docking.TabFont")
					//.Text("AAAAAAAA")
				]
		*/		//-----------------------------



			//  ======================   Dialog Window   =====================
			SNew(SDialogWindowWidget)
			//SAssignNew(DialogWindow, SDialogWindowWidget)
				.PathToFile(&PathToCurrentXML)
			//.Text(WidgetText)
		];
		
		
}





void FEditorDialogCreatorModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->TryInvokeTab(EditorWindowsPluginTabName);
}

void FEditorDialogCreatorModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FEditorDialogCreatorCommands::Get().OpenPluginWindow, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("Settings");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FEditorDialogCreatorCommands::Get().OpenPluginWindow));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}






#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FEditorDialogCreatorModule, EditorDialogCreator)


