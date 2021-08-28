// Fill out your copyright notice in the Description page of Project Settings.


#include "DLGObjectCustomizationDetails.h"

#if WITH_EDITOR

#include "DetailCategoryBuilder.h"
#include "DetailLayoutBuilder.h"
#include "DetailWidgetRow.h"

#include "Kismet2/KismetEditorUtilities.h"
#include "Widgets/SNullWidget.h"

#include "Widgets/Text/STextBlock.h"
#include "Widgets/Input/SButton.h"
#include "Editor/UnrealEd/Public/Kismet2/BlueprintEditorUtils.h"
#include "Components/BoxComponent.h"
#include "Engine.h"
#include "Editor/UnrealEd/Classes/Editor/EditorEngine.h"
#include "Editor/UnrealEd/Public/Editor.h"

#include "Editor/Kismet/Public/SSCSEditor.h"

#include "DesktopPlatformModule.h"					 // Dialog Window
#include "IDesktopPlatform.h"						 // Dialog Window
#include "PugiXML_Plagin/Include/pugixml.hpp"        //  PUGI

#define LOCTEXT_NAMESPACE "FDLGObjectCustomizationDetails"


TSharedRef<IDetailCustomization> FDLGObjectCustomizationDetails::MakeInstance()
{
	return MakeShareable(new FDLGObjectCustomizationDetails);
}



//  -------------    Button in all object's propety "Dialog settings"   -------------
void FDLGObjectCustomizationDetails::CustomizeDetails(IDetailLayoutBuilder& DetailBuilder)
{
	//IDetailCategoryBuilder& EngineCategory = DetailBuilder.EditCategory("Dialog settings");
	IDetailCategoryBuilder& EngineCategory = DetailBuilder.EditCategory("DialogSystem");


	BaseClass = DetailBuilder.GetBaseClass();
	SelectedObjectList = DetailBuilder.GetSelectedObjects();

	const FText CreateWorldBtn = LOCTEXT("Button", "Set dialog File(.xml)");
	EngineCategory.AddCustomRow(CreateWorldBtn, false)
		.NameContent()
		[
			SNullWidget::NullWidget
		]
	.ValueContent()
		.VAlign(VAlign_Center)
		.MaxDesiredWidth(300)
		[
			SNew(SButton)
			.VAlign(VAlign_Center)
			.ToolTipText(LOCTEXT("Set dialog File(.xml)", "Set dialog File(.xml)"))
			.OnClicked(this, &FDLGObjectCustomizationDetails::ClickBtnPopulate)
			.Content()
			[
				SNew(STextBlock)
				.Text(CreateWorldBtn)
			]
		];

}

FReply FDLGObjectCustomizationDetails::ClickBtnPopulate()
{
	
	//  --------  Dialog Window,    load  .xml   --------------
	TArray<FString> OutFileNames;
	if (GEngine )  // && GEngine->GameViewport -- In Runtime
	{

		void* ParentWindowHandle = FSlateApplication::Get().GetActiveTopLevelWindow()->GetNativeWindow()->GetOSWindowHandle(); // In Editor
		//void* ParentWindowHandle = GEngine->GameViewport->GetWindow()->GetNativeWindow()->GetOSWindowHandle();		 // In Runtime
		IDesktopPlatform* DesktopPlatform = FDesktopPlatformModule::Get();
		if (DesktopPlatform)
		{
			FString Path = FPaths::ProjectContentDir();
			// open file picker
			uint32 SelectionFlag = 0; // if one or few files has chosen
			DesktopPlatform->OpenFileDialog(ParentWindowHandle, FString("Open file (.xml)"), Path, FString(""), FString(".xml"), SelectionFlag, OutFileNames);
			///GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Orange, OutFileNames[0]);



			//  ---------  Change Property in UDLG_DialogItem -> PathToFile" ------------
			if (OutFileNames.Num() > 0)
			{
				FText DialogText;

				//  --------- Check if file Directory correct  -------------
				FString CechingPath = FPaths::ProjectContentDir() + FString("Dialog/");
				if (OutFileNames[0].Find(CechingPath, ESearchCase::Type::IgnoreCase, ESearchDir::Type::FromStart, 0) == -1)
				{
					DialogText = FText::FromString(TEXT("file should be plased in \"Content/Dialog/...\" directory"));
					FMessageDialog::Open(EAppMsgType::Ok, DialogText);
					return FReply::Handled();
				}
				//  --------- Check if file Exist  -------------
				FString XmlFileContent;
				IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
				FString FilePath = OutFileNames[0];
				if (PlatformFile.FileExists(*FilePath))
				{
					FFileHelper::LoadFileToString(XmlFileContent, *FilePath);
				}
				else
				{
					DialogText = FText::FromString(TEXT("file cann't be opened"));
					FMessageDialog::Open(EAppMsgType::Ok, DialogText);
					return FReply::Handled();
				}

				//  --------- Check if Dialog in file Build correct  -------------
				std::string source = (TCHAR_TO_UTF8(*XmlFileContent));
				pugi::xml_document xmlDoc;
				//pugi::xml_parse_result parse_Res = xmlDoc.load_file("G:\\ARCHIV\\Archive\\UE_Proj\\XML\\Dialod_Name_01.xml");
				pugi::xml_parse_result parse_Res = xmlDoc.load_buffer(source.c_str(), source.size());  //  LOAG .XML FROM  (std::string)
				pugi::xml_node RootNode = xmlDoc.child("name");
				std::string RootNodeStr(RootNode.attribute("redy").as_string());
				FString IsDialogBuild_Ok_Str(RootNodeStr.c_str());
				if (IsDialogBuild_Ok_Str == FString("ok"))
				{
					SelectedActor = Cast<UDLG_DialogItem>(SelectedObjectList[0].Get());
					Cast<UDLG_DialogItem>(SelectedActor)->PathToFile = OutFileNames[0];   // FString(" Path_to_DialogFile.xml ");
				}
				else
				{
					DialogText = FText::FromString(TEXT("Dialog is not correct and cann't be loaded"));
					FMessageDialog::Open(EAppMsgType::Ok, DialogText);
					return FReply::Handled();
				}
			}
		}
	}

	
	
	
	///FPropertyValueIterator
	//for (TFieldIterator<FProperty> PropertyIterator(UDLG_UnitDialog::StaticClass()); PropertyIterator; ++PropertyIterator)
/*	for (TFieldIterator<FProperty> PropertyIterator(SelectedActor->GetClass()); PropertyIterator; ++PropertyIterator)
	{
		FProperty* Property = *PropertyIterator;
		FName const PropertyName = Property->GetFName();
		
		//FString value = Property->GetPropertyValue_InContainer(SelectedActor) ? "true" : "false";
		
		if (PropertyName == TEXT("AAAAAA_123456"))
		{
			FStrProperty* strProperty = Cast<FStrProperty>(Property);
			if (strProperty)
			{
				strProperty->SetPropertyValue((void*)SelectedActor, FString("rrrrrrrrrrrr"));
				//strProperty->SetPropertyValue_InContainer(SelectedActor, FString("rrrrrrrrrrrr"), 0);
				break;
			}
		}
		
	}
*/






	/*UBoxComponent* Doomy = NewObject<UBoxComponent>(SelectedActor.Get());
	SelectedActor->AddInstanceComponent(Doomy);
	FRestoreSelectedInstanceComponent RestoreSelectedInstanceComponent;
	GEditor->GetSelectedComponents()->Modify();
	SelectedActor->Modify();
	// Mark components that are either native or from the SCS as modified so they will be restored
	for (UActorComponent* ActorComponent : SelectedActor->GetComponents())
	{
		if (ActorComponent && (ActorComponent->CreationMethod == EComponentCreationMethod::SimpleConstructionScript || ActorComponent->CreationMethod == EComponentCreationMethod::Native))
		{
			ActorComponent->Modify();
		}
	}
	UBlueprint* Blueprint = Cast<UBlueprint>(SelectedActor->GetClass()->ClassGeneratedBy);
	AActor* BlueprintCDO = SelectedActor->GetClass()->GetDefaultObject<AActor>();
	const EditorUtilities::ECopyOptions::Type CopyOptions = (EditorUtilities::ECopyOptions::Type)(EditorUtilities::ECopyOptions::OnlyCopyEditOrInterpProperties | EditorUtilities::ECopyOptions::PropagateChangesToArchetypeInstances);
	NumChangedProperties = EditorUtilities::CopyActorProperties(SelectedActor.Get(), BlueprintCDO, CopyOptions);
	if (SelectedActor->GetInstanceComponents().Num() > 0)
	{
		RestoreSelectedInstanceComponent.Save(SelectedActor.Get());
		FKismetEditorUtilities::AddComponentsToBlueprint(Blueprint, SelectedActor->GetInstanceComponents());
		NumChangedProperties += SelectedActor->GetInstanceComponents().Num();
		SelectedActor->ClearInstanceComponents(true);
	}
	if (NumChangedProperties > 0)
	{
		SelectedActor = nullptr; // It is unsafe to use Actor after this point as it may have been reinstanced, so set it to null to make this obvious
	}

	FBlueprintEditorUtils::MarkBlueprintAsModified(Blueprint);
	FKismetEditorUtilities::CompileBlueprint(Blueprint);
	RestoreSelectedInstanceComponent.Restore();
*/	
	return FReply::Handled();
	
}

#endif