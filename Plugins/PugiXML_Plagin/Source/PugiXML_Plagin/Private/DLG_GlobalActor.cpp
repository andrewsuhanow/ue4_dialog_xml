// Fill out your copyright notice in the Description page of Project Settings.


#include "DLG_GlobalActor.h"

#include "WDisplayDialog.h"

#include "PugiXML_Plagin/Include/pugixml.hpp"           //  PUGI
#include <sstream>   //  777777


#include "Interfaces/IPluginManager.h"

#include "GameFramework/PlayerController.h"  //  InputMode

#include "InputCoreTypes.h"          //InputComponent->BindKey(EKeys::

#include "Components/InputComponent.h"
#include "Components/AudioComponent.h"


// Sets default values
ADLG_GlobalActor::ADLG_GlobalActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	DialogInputComponent = CreateDefaultSubobject<UInputComponent>(TEXT("DialogInputComponent"));
	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
	//AudioComponent->AttachParent = RootComponent;
	AudioComponent->bAutoActivate = true;
}


void ADLG_GlobalActor::BeginPlay()
{
	Super::BeginPlay();
	

	DialogInputComponent->BindKey(EKeys::LeftMouseButton, EInputEvent::IE_Pressed, this, &ADLG_GlobalActor::KeyMouseLeftDown);
	DialogInputComponent->BindKey(EKeys::SpaceBar, EInputEvent::IE_Pressed, this, &ADLG_GlobalActor::KeySpace);
	DialogInputComponent->BindKey(EKeys::Escape, EInputEvent::IE_Pressed, this, &ADLG_GlobalActor::KeyEscape);


	DLG_InitDialodWidget();
	DLG_InitLocalVariables();

}



void ADLG_GlobalActor::DLG_InitDialodWidget()
{
	if (DisplayDialog_BPClass && GetWorld())
	{
		DisplayDialog = CreateWidget<UWDisplayDialog>(GetWorld(), DisplayDialog_BPClass, TEXT("DisplayDialog"));

		if (DisplayDialog)
		{
			DisplayDialog->Init(this, Scrolling_dialog);
			DisplayDialog->AddToViewport();
		}
	}

}


void ADLG_GlobalActor::DLG_InitLocalVariables()
{
	//   ============   Get LocalVariables from .xml   ====================
	pugi::xml_document xmlVariables;

	FString LVariableXmlPath = FPaths::ProjectContentDir() + FString("Dialog/") + FString("LVariables.xml");
	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
	if (!PlatformFile.FileExists(*LVariableXmlPath)) return;

	pugi::xml_parse_result parse_VariablesRes = xmlVariables.load_file(StringCast<ANSICHAR>(*LVariableXmlPath).Get());
	if (!parse_VariablesRes) return;

	//  Get Root Node
	pugi::xml_node VariableRootNode = xmlVariables.child("local_variables");
	VariableRootNode = xmlVariables.child("local_variables");

	LocalVariables.Empty();
	pugi::xpath_node_set DLG_Var = VariableRootNode.select_nodes("variable");
	for (int32 i_Variables = 0; i_Variables < DLG_Var.size(); i_Variables++)
	{
		std::string STD_VarValueStr(DLG_Var[i_Variables].node().attribute("value").as_string());	//   get attribute("value")
		std::wstring STD_W_VarValueStr = pugi::as_wide(STD_VarValueStr.c_str());
		FString VarValueStr(STD_W_VarValueStr.c_str());
		LocalVariables.Add(FName(*VarValueStr));
	}
	
}

   
void ADLG_GlobalActor::KeyMouseLeftDown()
{
	DisplayDialog->KeyMouseLeftDown();
	UE_LOG(LogTemp, Warning, TEXT("DialogSystem: KeyMouseLeftDown()"));
}
void ADLG_GlobalActor::KeySpace()
{
	DisplayDialog->KeySpace();
	UE_LOG(LogTemp, Warning, TEXT("DialogSystem: KeySpace()"));
}
void ADLG_GlobalActor::KeyEscape()
{
	DisplayDialog->KeyEscape();
	UE_LOG(LogTemp, Warning, TEXT("DialogSystem: KeyEscape()"));
}


void ADLG_GlobalActor::DLG_PlayDialog(AActor* _ActorSpeker,
									FString& _XmlFilePath,
									FDialogParameter& _DialogParameter)
{
	ActorSpeker = _ActorSpeker;
	XmlFilePath = &_XmlFilePath;
	DialogParameter = &_DialogParameter;


	//  ----------  GameMode   Dialog  -----------------
	APlayerController* PC = Cast<APlayerController>(GEngine->GetFirstLocalPlayerController(GetWorld()));
	//PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);    //  #include "Kismet/GameplayStatics.h"
	if (!PC) return;	
	StoredInputComponent = PC->InputComponent;
	if(DialogInputComponent) PC->InputComponent = DialogInputComponent;
	//PC->InputComponent = StoredInputComponent;
	//PC->SetupInputComponent();
	

	

	PC->SetInputMode(FInputModeGameAndUI());   //  FInputModeGameAndUI(),   FInputModeUIOnly(),  FInputModeGameOnly()
	PC->bShowMouseCursor = true;
	//UWidgetBlueprintLibrary::SetInputMode_GameAndUI();
	//UWidgetBlueprintLibrary::SetInputMode_GameOnly();
	//UWidgetBlueprintLibrary::SetInputMode_UIOnly();


	DisplayDialog->ShowDialogPanel();

	GenerateDialog();

}



void ADLG_GlobalActor::GenerateDialog(EResponseReturn _ResponseReturn,
										FString _NextDialogNode,
										FString _NextSpeechNode)
{
/*	//  ============================== Draw all Parameter ============================  ((( TEST )))

GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Yellow, FString::Printf(TEXT("%s"), *XmlFilePath));
UE_LOG(LogTemp, Warning, TEXT("replic-------: = '%s'"), *XmlFilePath);
for (int32 i = 0; i < DialogParameter.DialogNode.Num(); i++)
{
	UE_LOG(LogTemp, Warning, TEXT("DIALOG '%s'"), *DialogParameter.DialogNode[i].Name.ToString());
	for (int32 i1 = 0; i1 < DialogParameter.DialogNode[i].SpeechNode.Num(); i1++)
	{
		UE_LOG(LogTemp, Warning, TEXT("     SPEECH '%s'"), *DialogParameter.DialogNode[i].SpeechNode[i1].Name.ToString());
		for (int32 i1_1 = 0; i1_1 < DialogParameter.DialogNode[i].SpeechNode[i1].DLGVariable_Checking.Num(); i1_1++)
		{
			UE_LOG(LogTemp, Warning, TEXT("     SPEECH_CONDITION   '%s',   '%i',    '%s'"), *DialogParameter.DialogNode[i].SpeechNode[i1].DLGVariable_Checking[i1_1].NameGlobalVar.ToString(),
																	DialogParameter.DialogNode[i].SpeechNode[i1].DLGVariable_Checking[i1_1].IndexLocalVar,
																	*DialogParameter.DialogNode[i].SpeechNode[i1].DLGVariable_Checking[i1_1].Value.ToString());
		}
		for (int32 i1_2 = 0; i1_2 < DialogParameter.DialogNode[i].SpeechNode[i1].ReplicNode.Num(); i1_2++)
		{
			for (int32 i1_2_1 = 0; i1_2_1 < DialogParameter.DialogNode[i].SpeechNode[i1].ReplicNode[i1_2].DLGVariable_Checking.Num(); i1_2_1++)
			{
				UE_LOG(LogTemp, Warning, TEXT("     REOLIC_CONDITION   '%s',   '%i',    '%s'"), *DialogParameter.DialogNode[i].SpeechNode[i1].ReplicNode[i1_2].DLGVariable_Checking[i1_2_1].NameGlobalVar.ToString(),
																								DialogParameter.DialogNode[i].SpeechNode[i1].ReplicNode[i1_2].DLGVariable_Checking[i1_2_1].IndexLocalVar,
																								*DialogParameter.DialogNode[i].SpeechNode[i1].ReplicNode[i1_2].DLGVariable_Checking[i1_2_1].Value.ToString());	
			}
		}
	}
}
*/


	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
//  ================================  Get xmlDialog Content ====================
	pugi::xml_document xmlDoc;

	//IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
	if (!PlatformFile.FileExists(**XmlFilePath)) return;

	pugi::xml_parse_result parse_Res = xmlDoc.load_file(StringCast<ANSICHAR>(**XmlFilePath).Get());
	if (!parse_Res) return;

	//  Get Root Node
	pugi::xml_node DialogRootNode = xmlDoc.child("name");
	
	//std::string RootNodeStr(RootNode.attribute("name").as_string());
//   ================================   Get LocalVariables from .xml   ====================
	pugi::xml_document xmlVariables;

	FString LVariableXmlPath = FPaths::ProjectContentDir() + FString("Dialog/") + FString("LVariables.xml");
	//IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
	if (!PlatformFile.FileExists(*LVariableXmlPath)) return;

	pugi::xml_parse_result parse_VariablesRes = xmlVariables.load_file(StringCast<ANSICHAR>(*LVariableXmlPath).Get());
	if (!parse_VariablesRes) return;
	//  Get Root Node
	pugi::xml_node VariableRootNode = xmlVariables.child("local_variables");
	





	if (_ResponseReturn == EResponseReturn::click_default_once ||
		_ResponseReturn == EResponseReturn::click_default_back ||
		_ResponseReturn == EResponseReturn::click_default_noreplic ||
		_ResponseReturn == EResponseReturn::pass_default_once ||
		_ResponseReturn == EResponseReturn::pass_default_back ||
		_ResponseReturn == EResponseReturn::pass_default_noreplic)
	{
		_NextDialogNode = FString("DEFAULT");
		_NextSpeechNode = FString("DEFAULT");
	}


	 
	//  =========================  Check Node Condition AtAll  =======================
	auto CheckCondition = [&](pugi::xml_node _DlgBranchRootNode,      //  XXXXXXXXXXXXXXXXXXXXXXXXXXXXX   COPY OR REF
							pugi::char_t* NodeNameStr,
							TArray<FName>& _LocalVariables,
							pugi::xml_node _VariableRootNode,      //  XXXXXXXXXXXXXXXXXXXXXXXXXXXXX   COPY OR REF
							//TArray<int32>& _Checking_LocalVariable,
							TMap<FName, FName>& _GlobalVariable)
	{

		// ==========================    CONDITION  ============================

		

		bool isCurrentNodeTest = true;
		TArray<std::string> Or_ToCheck;
		TArray<std::string> Or_ToIgnor;
		//std::wstring STD_W_NodeNameStr = pugi::as_wide(STD_NodeNameStr.c_str());
		pugi::xpath_node_set DLG_ConditionNode = _DlgBranchRootNode.select_nodes(NodeNameStr);
		for (int32 i_Condition = 0; i_Condition < DLG_ConditionNode.size(); i_Condition++)
		{
			// ======== Get Condition Type  (And/Or) =========
			std::string STD_TypeOrAnd_Str(DLG_ConditionNode[i_Condition].node().attribute("type").as_string()); // Attribute(Or/And)
			// ======== Get variable Type  (Local/Global) =========
			std::string STD_TypeLocalGlobal_Str(DLG_ConditionNode[i_Condition].node().attribute("var_type").as_string());  //   get attribute("Local/Global")
			// ======== Get variable Value =========
			std::string STD_VarValue_Str(DLG_ConditionNode[i_Condition].node().text().as_string());   //   get variable "Value"
			FString VarValue_Str(STD_VarValue_Str.c_str());
			// ======== Get variable Name =========
			std::string STD_VarName_Str(DLG_ConditionNode[i_Condition].node().attribute("var_name").as_string()); // Attribute(var_name)
			FString VarName_Str(STD_VarName_Str.c_str());

			// ======== Check if need ignore variable, becose "Or-type" and alredy "true" ========
			if (Or_ToIgnor.Contains(STD_TypeOrAnd_Str)) continue;

			bool isCurrentConditionTest = true;

			// ==============   "global"   ===================
			if (STD_TypeLocalGlobal_Str == "global")
			{
				// ========  Compare with 'GlobalVariable_value'  =========
				// ------- Find "Variable" in global by "Name" -------
				FName* GlobalValueRef = _GlobalVariable.Find(FName(*VarName_Str));
				if (GlobalValueRef) 
				{
					FName realGlobalVariable_value = *GlobalValueRef;
					if (FName(*VarValue_Str) != realGlobalVariable_value) isCurrentConditionTest = false;
				}
				else isCurrentConditionTest = false;
			}

			// ==============   "Local"   ===================
			else  
			{ 
				bool VariableIsAbsent = true;
				pugi::xpath_node_set XML_Var = VariableRootNode.select_nodes("variable");
				for (int32 i_Variables = 0; i_Variables < XML_Var.size(); i_Variables++)
				{
					//  name of local variable in LVariable_XmlFile
					std::string STD_XmlVarNameStr(XML_Var[i_Variables].node().attribute("name").as_string());	//   get attribute("name")

					if (STD_VarName_Str == STD_XmlVarNameStr)
					{
						VariableIsAbsent = false;

						//std::string STD_XmlVarValueStr(XML_Var[i_Variables].node().attribute("value").as_string());	//   get attribute("value")				
						if (VarValue_Str != _LocalVariables[i_Variables].ToString()) isCurrentConditionTest = false;
						//if (STD_VarValue_Str != STD_XmlVarValueStr) isCurrentConditionTest = false;
						break;
					}
				}
				if(VariableIsAbsent) isCurrentConditionTest = false;  // Variable is absent in LVariable_XmlFile
						
				/*if ((_Checking_LocalVariable.Num()-1) < i_Condition ||
					_Checking_LocalVariable[i_Condition] == -1 ||			 //  Has condition-Variable but absent LVariable in File
					(_LocalVariables.Num()-1) < _Checking_LocalVariable[i_Condition])
				{
					isCurrentConditionTest = false;
				}		
				else if(FName(*VarValue_Str) != _LocalVariables[_Checking_LocalVariable[i_Condition]]) 
					isCurrentConditionTest = false;
				else if (_Checking_LocalVariable.Num() == 0) //  if NoOne local Condition  =>>  chech next cindition
					isCurrentConditionTest = true;
				*/ 					 
			}

			//   And / Or   (result alredy have)
			if (!isCurrentConditionTest)
			{
				//  Result NOT correct
				if (STD_TypeOrAnd_Str == "and") isCurrentNodeTest = false;
				else if (!Or_ToCheck.Contains(STD_TypeOrAnd_Str)) Or_ToCheck.Add(STD_TypeOrAnd_Str);
			}
			else
			{
				//  Result correct
				if (STD_TypeOrAnd_Str == "and") continue;
				else if (Or_ToCheck.Contains(STD_TypeOrAnd_Str)) Or_ToCheck.Remove(STD_TypeOrAnd_Str);
				Or_ToIgnor.Add(STD_TypeOrAnd_Str);
			}

			if (!isCurrentNodeTest) break;
		}
		if (Or_ToCheck.Num() > 0) isCurrentNodeTest = false;

		return isCurrentNodeTest;
	};

	 

	auto GetAppropriateREP = [&](pugi::xml_node _DlgBranchRootNode, // REPLIC.node()  // XXXXXXXXXXXXXXXXXXXXXXXXXXXXX   COPY OR REF
									pugi::char_t* NodeNameStr, 
									TArray<FName>& _LocalVariables,
									FReplicNode& ReplicNodeParam,
									TMap<FName, FName>& _GlobalVariable,
									FReplicToDraw& ReplicsToDrawTMP_Ref)
	{
		// ==========================    REP   ============================
		/*TArray<int32> CorrectReps;
		pugi::xpath_node_set DLG_Rep = DLG_Replic[i_Replic].node().select_nodes("rep");
		for (int32 i_Rep = 0; i_Rep < DLG_Rep.size(); i_Rep++)
		{
			//  XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX  if TMap.iSEmpty()   XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXx
			//  XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX  if TMap.iSEmpty()   XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXx
			//  XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX  if TMap.iSEmpty()   XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXx
			//  XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX  if TMap.iSEmpty()   XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXx
			//  XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX  if TMap.iSEmpty()   XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXx
			bool isCurrentRepTest = CheckCondition(DLG_Rep[i_Rep].node(),
				"rep_condition",
				LocalVariables,
				_DialogParameter.DialogNode[i_Dlg].SpeechNode[i_Speech].ReplicNode[i_Replic].RepNode[i_Rep].DLGVariable_Checking,
				GlobalVariable);

			// -----------  if this "Rep" satisfy of condition =>> save it for further (random) Geting  ----------
			if (isCurrentRepTest) CorrectReps.Add(i_Rep);
		}

		int32 IndexOfChosedRep = 0;
		if (CorrectReps.Num() == 0) continue;  // if NOone "Reps" is alloud =>> spend "Replic"
		else
		{
			IndexOfChosedRep = RandRange(0, CorrectReps.Num() - 1);

			FReplicToDraw ReplicsToDrawTMP;

			ReplicsToDrawTMP.ReplicTextStr = FString("..........................");
			ReplicsToDrawTMP.SpekerImagePath = FString("..........................");
			ReplicsToDrawTMP.SoundPath = FString("..........................");
			ReplicsToDrawTMP.Time = 2;
			ReplicsToDrawTMP.Delay = 1;

		}*/

		TArray<int32> CorrectReps;
		pugi::xpath_node_set DLG_Rep = _DlgBranchRootNode.select_nodes(NodeNameStr);
		for (int32 i_Rep = 0; i_Rep < DLG_Rep.size(); i_Rep++)
		{
			bool isCurrentRepTest = CheckCondition(DLG_Rep[i_Rep].node(),
												"rep_condition",
												_LocalVariables,
												VariableRootNode,
												//ReplicNodeParam.RepNode[i_Rep].IndexLocalVar,
												_GlobalVariable);

			// -----------  if this "Rep" satisfy of condition =>> save it for further (random) Geting  ----------
			if (isCurrentRepTest) CorrectReps.Add(i_Rep);
		}

		int32 IndexOfChosedRep = 0;
		if (CorrectReps.Num() == 0) return false;  // if NOone "Reps" is alloud =>> spend "Replic"
		else
		{
			//  ---------    Get random Rep from alloud Rep   ----------
			IndexOfChosedRep = FMath::RandRange(0, CorrectReps.Num() - 1);
	
				
				std::string STD_ReturnTextStr(DLG_Rep[IndexOfChosedRep].node().text().as_string());   //  Get "Text" Value
				std::wstring STD_W_ReturnTextStr = pugi::as_wide(STD_ReturnTextStr.c_str());
				FString ReturnTextStr(STD_W_ReturnTextStr.c_str());
				ReturnTextStr.TrimStartAndEndInline();               //  remove \t \n
			ReplicsToDrawTMP_Ref.ReplicTextStr = ReturnTextStr;   //   Return Value "phrase Text"


				std::string STD_ReturnTimeStr(DLG_Rep[IndexOfChosedRep].node().attribute("time").as_string()); // Attribute(time)
				FString ReturnTimeStr(STD_ReturnTimeStr.c_str());
			ReplicsToDrawTMP_Ref.Time = ReturnTimeStr;           //   Return Value "time"

				std::string STD_ReturnDelayStr(DLG_Rep[IndexOfChosedRep].node().attribute("delay").as_string()); // Attribute(delay)
				FString ReturnDelayStr(STD_ReturnDelayStr.c_str());
			ReplicsToDrawTMP_Ref.Delay = FCString::Atof(*ReturnDelayStr);   //   Return Value "delay"
				

			//  -----------------  Get data from Speker.xml  -----------------
			std::string STD_RequiredSpekerNameStr(DLG_Rep[IndexOfChosedRep].node().attribute("speker").as_string()); // Attribute(speker)
			std::string STD_RequireSpekerSoundStr(DLG_Rep[IndexOfChosedRep].node().attribute("sound").as_string()); // Attribute(sound)

			pugi::xml_document xmlSpeker;
			FString SpekerXmlPath = FPaths::ProjectContentDir() + FString("Dialog/") + FString("Spekers.xml");
			IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();//----------
			if (!PlatformFile.FileExists(*SpekerXmlPath)) return false;//-------+++++
			pugi::xml_parse_result parse_SpekerRes = xmlSpeker.load_file(StringCast<ANSICHAR>(*SpekerXmlPath).Get());
			if (!parse_SpekerRes) return false;
			pugi::xml_node SpekerRootNode = xmlSpeker.child("game_spekers"); //  Get Root Node

			//  ----------  Found Required Speker  ----------
			pugi::xpath_node_set SpekerNode = SpekerRootNode.select_nodes("speker");
			for (int32 i_Speker = 0; i_Speker < SpekerNode.size(); i_Speker++)
			{

				std::string STD_CurrentSpekerName(SpekerNode[i_Speker].node().attribute("name").as_string());
				if (STD_CurrentSpekerName == STD_RequiredSpekerNameStr)
				{
					FString ReturnSpekerName(STD_CurrentSpekerName.c_str());
					ReplicsToDrawTMP_Ref.SpekerName = ReturnSpekerName;

					std::string STD_ReturnImagePath(SpekerNode[i_Speker].node().text().as_string());
					FString ReturnImagePath(STD_ReturnImagePath.c_str());
					ReturnImagePath.TrimStartAndEndInline();               //  remove \t \n
					ReplicsToDrawTMP_Ref.SpekerImagePath = ReturnImagePath;   //   Return Value "Image Path"


					//  ----------  Found Required Sound  ----------
					pugi::xpath_node_set SoundNode = SpekerNode[i_Speker].node().select_nodes("sound");
					for (int32 i_Sound = 0; i_Sound < SpekerNode.size(); i_Sound++)
					{
						std::string STD_CurrentSpekerSound(SoundNode[i_Sound].node().attribute("name").as_string());
						if (STD_CurrentSpekerSound == STD_RequireSpekerSoundStr)
						{
							std::string STD_ReturnSoundPath(SoundNode[i_Sound].node().text().as_string());
							FString ReturnSoundPath(STD_ReturnSoundPath.c_str());
							ReturnSoundPath.TrimStartAndEndInline();               //  remove \t \n
							ReplicsToDrawTMP_Ref.SoundPath = ReturnSoundPath;   //   Return Value "Sound Path"
						}
					}
				}

				//--
			}
		}
		return true;
	};




	ReplicsToDraw.Empty();

	// ==========================    DIALOG  ============================
	bool ExtremalExit = false;
	pugi::xpath_node_set DLG_Dialog = DialogRootNode.select_nodes("dialog");
	for (int32 i_Dlg = 0; i_Dlg < DLG_Dialog.size(); ++i_Dlg)
	{
	std::string STD_DlgStr(DLG_Dialog[i_Dlg].node().attribute("dialog_name").as_string());  //   get attribute("dialog_name")
	FString DlgStr(STD_DlgStr.c_str());
	if (DlgStr == _NextDialogNode)
	{
		// ==========================    SPEECH  ============================
		bool IsSpeechNodeGenerate_ok = false;
		pugi::xpath_node_set DLG_Speech = DLG_Dialog[i_Dlg].node().select_nodes("speech");
		for (int32 i_Speech = 0; i_Speech < DLG_Speech.size(); ++i_Speech)
		{
		std::string STD_SpeechStr(DLG_Speech[i_Speech].node().attribute("speech_name").as_string());  //   get attribute("speech_name")
		FString SpeechStr(STD_SpeechStr.c_str());
		if (SpeechStr == _NextSpeechNode)
		{			
			//  ========================   Check "Speech" CONDITION  ===========================
			bool isCurrentSpeechTest = CheckCondition(DLG_Speech[i_Speech].node(),
											"speech_condition",
											LocalVariables,
											VariableRootNode,
											//(*DialogParameter).DialogNode[i_Dlg].SpeechNode[i_Speech].IndexLocalVar,
											GlobalVariable);

			//  ------  if desired "Speech" node don't pass requide test  ---------   
			//   =>>  go throught  "Speech(default -> default -> default...)" node or start from "DEFAULD"   ---  
			if (!isCurrentSpeechTest)
			{
				if (_NextSpeechNode != FString("DEFAULT"))
				{
					_NextSpeechNode = FString("DEFAULT");
					_ResponseReturn = EResponseReturn::click_link_back;
					i_Speech = -1;  // loop to begin (0)
				}					
				continue;
			}


			//  ============================  If  PROPERTY "NO-REPLIC" =>> PASS "Replik" zone  =========================
			if (_ResponseReturn != EResponseReturn::click_link_noreplic &&
				_ResponseReturn != EResponseReturn::click_default_noreplic &&
				_ResponseReturn != EResponseReturn::pass_link_noreplic &&
				_ResponseReturn != EResponseReturn::pass_default_noreplic)
			{

				//  ======================  Check Replick Repeat mode  =========================

					std::string RequireReplicRepeat = "always";
					//EReplicRepeat RequireReplicRepeat = EReplicRepeat::always;

					if (_ResponseReturn == EResponseReturn::click_link_back ||
						_ResponseReturn == EResponseReturn::click_default_back ||
						_ResponseReturn == EResponseReturn::pass_link_back ||
						_ResponseReturn == EResponseReturn::pass_default_back)
					{
						RequireReplicRepeat = "back";
						//RequireReplicRepeat = EReplicRepeat::back;
					}
					else if (_ResponseReturn == EResponseReturn::click_link_once ||
							 _ResponseReturn == EResponseReturn::click_default_once ||
							 _ResponseReturn == EResponseReturn::pass_default_once ||
							 _ResponseReturn == EResponseReturn::none ||
							 _ResponseReturn == EResponseReturn::pass_link_once)
					{
						if (!(*DialogParameter).DialogNode[i_Dlg].SpeechNode[i_Speech].IsRepeatOnce_Done)
							//RequireReplicRepeat = EReplicRepeat::once;
								RequireReplicRepeat = "once";
						else
							//RequireReplicRepeat = EReplicRepeat::after_once;
							RequireReplicRepeat = "after_once";
					}


				// ==========================    REPLIC   ============================

				pugi::xpath_node_set DLG_Replic = DLG_Speech[i_Speech].node().select_nodes("replic");
				for (int32 i_Replic = 0; i_Replic < DLG_Replic.size(); i_Replic++)
				{

					std::string STD_ReplicRepeatStr(DLG_Replic[i_Replic].node().attribute("repeat").as_string());  //   get attribute("repeat")
					//FString ReplicRepeatStr(STD_ReplicRepeatStr.c_str());

					// ===============  Check repet property:  (once/after_once/comeback), (always)  =================
					if(RequireReplicRepeat != STD_ReplicRepeatStr && STD_ReplicRepeatStr != "always") continue;
				
					//  ========================   CHECK "Replic" CONDITION  ===========================
					bool isCurrentReplicTest = CheckCondition(DLG_Replic[i_Replic].node(),
																"replic_condition",
																LocalVariables,
																VariableRootNode,
																//(*DialogParameter).DialogNode[i_Dlg].SpeechNode[i_Speech]
																//			.ReplicNode[i_Replic].IndexLocalVar,
																GlobalVariable);

					if (!isCurrentReplicTest) continue;
					else
					{
						FReplicToDraw ReplicsToDrawTMP;
						bool IsAlloudRepExist = GetAppropriateREP(DLG_Replic[i_Replic].node(),
												"rep",
												LocalVariables,
												(*DialogParameter).DialogNode[i_Dlg].SpeechNode[i_Speech]
																				.ReplicNode[i_Replic],
												GlobalVariable,
												ReplicsToDrawTMP);

						if (IsAlloudRepExist) ReplicsToDraw.Add(ReplicsToDrawTMP);
					}
				}

				 
				//  -----  if No-One "Replic" has satisfied conditions  -----  
				//   =>> goto next "Speech=(default -> default -> default...)" node or start from "DEFAULD"   ---
				if (ReplicsToDraw.Num() == 0)
				{
					if (_NextSpeechNode != FString("DEFAULT"))
					{
						_NextSpeechNode = FString("DEFAULT");
						_ResponseReturn = EResponseReturn::click_link_back;
						i_Speech = -1;   // loop to begin (0)
					}
					continue;
				}

				IsSpeechNodeGenerate_ok = true;

				//  -------   mark this "Replic" as using "after_once" next time   -------
				(*DialogParameter).DialogNode[i_Dlg].SpeechNode[i_Speech].IsRepeatOnce_Done = true;
			}



			// ==========================    RESPONSE   ============================

			ResponsesToDraw.Empty();

			pugi::xpath_node_set DLG_Response = DLG_Speech[i_Speech].node().select_nodes("response");
			for (int32 i_Response = 0; i_Response < DLG_Response.size(); i_Response++)
			{

				std::string STD_ResponseRepeatStr(DLG_Response[i_Response].node().attribute("repeat").as_string());  //   get attribute("repeat")
				//FString ResponseRepeatStr(STD_ResponseRepeatStr.c_str());

				// ===============  Check repet property:  (once / always)  =================
				if (STD_ResponseRepeatStr != "once")
				{
					if ((*DialogParameter).DialogNode[i_Dlg].SpeechNode[i_Speech].ResponseNode[i_Response].IsRepeatOnce_Done)	continue;
					else (*DialogParameter).DialogNode[i_Dlg].SpeechNode[i_Speech].ResponseNode[i_Response].IsRepeatOnce_Done = true;
				}

				//  ========================   CHECK "Response" CONDITION  ===========================
				bool isCurrentResponseTest = CheckCondition(DLG_Response[i_Response].node(),
															"response_condition",
															LocalVariables,
															VariableRootNode,
															GlobalVariable);

				if (!isCurrentResponseTest) continue;
				else
				{
					FResponseToDraw ResponseToDrawTMP;

						std::string STD_ResponseTextStr(DLG_Response[i_Response].node().text().as_string());
						std::wstring STD_W_ResponseTextStr = pugi::as_wide(STD_ResponseTextStr.c_str());
						FString ResponseTextStr(STD_W_ResponseTextStr.c_str());
						ResponseTextStr.TrimStartAndEndInline();               //  remove \t \n
					ResponseToDrawTMP.str = ResponseTextStr;

						std::string STD_ResponseDialogLinkStr(DLG_Response[i_Response].node().attribute("dialog_link").as_string());  //   get attribute("dialog_link")
						FString ResponseDialogLinkStr(STD_ResponseDialogLinkStr.c_str());
					ResponseToDrawTMP.LinkDialog = FName(*ResponseDialogLinkStr);
					
						std::string STD_ResponseSpeechLinkStr(DLG_Response[i_Response].node().attribute("speech_link").as_string());  //   get attribute("speech_link")
						FString ResponseSpeechLinkStr(STD_ResponseSpeechLinkStr.c_str());
					ResponseToDrawTMP.LinkSpeech = FName(*ResponseSpeechLinkStr);

						const std::string STD_ResponseReturnTypeStr(DLG_Response[i_Response].node().attribute("return_type").as_string());  //   get attribute("return_type")
					if(STD_ResponseReturnTypeStr == "CLO (click_link_once)")
						ResponseToDrawTMP.ResponseReturn = EResponseReturn::click_link_once;
					else if(STD_ResponseReturnTypeStr == "CLR (click_link_return)")
						ResponseToDrawTMP.ResponseReturn = EResponseReturn::click_link_back;
					else if(STD_ResponseReturnTypeStr == "CLN (click_link_noreplic)")
						ResponseToDrawTMP.ResponseReturn = EResponseReturn::click_link_noreplic;
					else if(STD_ResponseReturnTypeStr == "CDO (click_default_once)")
						ResponseToDrawTMP.ResponseReturn = EResponseReturn::click_default_once;
					else if(STD_ResponseReturnTypeStr == "CDR (click_default_return)")
						ResponseToDrawTMP.ResponseReturn = EResponseReturn::click_default_back;
					else if(STD_ResponseReturnTypeStr == "CDN (click_default_noreplic)")
						ResponseToDrawTMP.ResponseReturn = EResponseReturn::click_default_noreplic;
					else if(STD_ResponseReturnTypeStr == "PLO (pass_link_once)")
						ResponseToDrawTMP.ResponseReturn = EResponseReturn::pass_link_once;
					else if(STD_ResponseReturnTypeStr == "PLR (pass_link_return)")
						ResponseToDrawTMP.ResponseReturn = EResponseReturn::pass_link_back;
					else if(STD_ResponseReturnTypeStr == "PLN (pass_link_noreplic)")
						ResponseToDrawTMP.ResponseReturn = EResponseReturn::pass_link_noreplic;
					else if(STD_ResponseReturnTypeStr == "PDO (pass_default_once)")
						ResponseToDrawTMP.ResponseReturn = EResponseReturn::pass_default_once;
					else if(STD_ResponseReturnTypeStr == "PDR (pass_default_return)")
						ResponseToDrawTMP.ResponseReturn = EResponseReturn::pass_default_back;
					else if(STD_ResponseReturnTypeStr == "PDN (pass_default_noreplic)")
						ResponseToDrawTMP.ResponseReturn = EResponseReturn::pass_default_noreplic;
					else //std::string("EXT (exit)")
						ResponseToDrawTMP.ResponseReturn = EResponseReturn::exit;
					


					// ==========================     RESPONSE    Variable_To_Change    ============================

					pugi::xpath_node_set DLG_ResponseCondition = DLG_Response[i_Response].node().select_nodes("change_variable");
					for (int32 i_ResponseCondition = 0; i_ResponseCondition < DLG_ResponseCondition.size(); i_ResponseCondition++)
					{

							std::string STD_ResponseVarTypeStr(DLG_ResponseCondition[i_ResponseCondition].node().attribute("var_type").as_string());  //   get attribute("var_type")
							FString ResponseVarTypeStr(STD_ResponseVarTypeStr.c_str());
						ResponseToDrawTMP.VariableToChange_LocalOrGlobal.Add(ResponseVarTypeStr);

							std::string STD_ResponseVarNameStr(DLG_ResponseCondition[i_ResponseCondition].node().attribute("var_name").as_string());  //   get attribute("var_name")

						if (ResponseVarTypeStr == FString("global"))
						{
							FString ResponseVarNameStr(STD_ResponseVarNameStr.c_str());
							ResponseToDrawTMP.VariableToChange_Name.Add(ResponseVarNameStr);
						}
						else  //  =========  "Local"  =========
						{
							bool VariableIsAbsent = true;
							pugi::xpath_node_set DLG_Var = VariableRootNode.select_nodes("variable");
							for (int32 i_Variables = 0; i_Variables < DLG_Var.size(); i_Variables++)
							{
								//  name of local variable in LVariable_XmlFile
								std::string STD_VarNameStr(DLG_Var[i_Variables].node().attribute("name").as_string());	//   get attribute("name")

								if (STD_VarNameStr == STD_ResponseVarNameStr)
								{
									ResponseToDrawTMP.VariableToChange_Name.Add(FString::FromInt(i_Variables));
									VariableIsAbsent = false;
									break;
								}
							}
							if(VariableIsAbsent) ResponseToDrawTMP.VariableToChange_Name.Add(FString::FromInt(-1));
						}
						
							std::string STD_ResponseVarValueStr(DLG_ResponseCondition[i_ResponseCondition].node().text().as_string());  //   Get var "Value"
							FString ResponseVarValueStr(STD_ResponseVarValueStr.c_str());
						ResponseToDrawTMP.VariableToChange_Value.Add(ResponseVarValueStr);
					}

					ResponsesToDraw.Add(ResponseToDrawTMP);
				}
			} // response loop END

			//  ----    if Responses No-One Exist    -----   =>>  goto next "Speech=default" node or 
			//  -----  go thought "Speech (default -> default -> default...)" node or start from "DEFAULD"   ---
			if (ResponsesToDraw.Num() == 0)
			{
				ReplicsToDraw.Empty();
				IsSpeechNodeGenerate_ok = false;

				if (_NextSpeechNode != FString("DEFAULT"))
				{
					_NextSpeechNode = FString("DEFAULT");
					_ResponseReturn = EResponseReturn::click_link_back;
					i_Speech = 0;
				}
				continue;  
			}
			
			break;  ///  don't Check other "Speech"
		}
		}  // Speech loop END

		//  ------  if desired "Dialog" don't have any "replics" or "responses"  ---------    
		//   =>>  go throught "DEFAULT" Dialog and Speech nodes  ---------
		if(IsSpeechNodeGenerate_ok)	break;  //  don't Check other "Dialog"
		else
		{
			i_Dlg = -1;  // loop to begin (0)
			ReplicsToDraw.Empty();
			ResponsesToDraw.Empty();
			_NextDialogNode = FString("DEFAULT");
			_NextSpeechNode = FString("DEFAULT"); 
			_ResponseReturn = EResponseReturn::click_link_back;
			if (!ExtremalExit)
			{
				ExtremalExit = true;
				continue;
			}
			else
			{
				DLG_StopDialog();
				return;
			}

			   
		}
	}
	  
	}


	 

	DisplayDialog->DrawDialog(ReplicsToDraw, ResponsesToDraw);
	



	  
	

	USoundBase* MySoundWave = LoadObject<USoundBase>(this, TEXT("/Game/VoiceSound/Dialog_Test.Dialog_Test"));

	AudioComponent->SetSound(MySoundWave);
	AudioComponent->Play();
	//++++if(AudioComponent->IsPlaying())	AudioComponent->Stop();

/*	AudioComponent = UGameplayStatics::SpawnSoundAttached(
		MySoundWave, MeshComp, NAME_None,
		FVector(ForceInit), EAttachLocation::KeepRelativeOffset,
		true
	);*/

	//++float length = MySoundWave->Duration;
	//UGameplayStatics::PlaySoundAtLocation(this, MySoundWave, ActorSpeker->GetActorLocation());
	//UGameplayStatics::PlaySound2D(this, MySoundWave);

















	//  ------ generate and Draw DialogPanel  ------ 
	//DLG_GenerateDialog(CurrentDlgName, CurrentSpeechMarker, Replic, Response, ResponseIndex, true);



/*
	std::ostringstream ss;
	xmlDoc.save(ss);
	std::string s = ss.str();

*/

	///FString FSs(s.c_str());
	///UE_LOG(LogTemp, Warning, TEXT("unit->data->py = '%s'"), *FSs);

	///std::wstring ws = pugi::as_wide(ss.str());
	///FString FSss(ws.c_str());
	///UE_LOG(LogTemp, Warning, TEXT("unit->data->py = '%s'"), *FSss);


}


void ADLG_GlobalActor::DLG_StopDialog()
{
	APlayerController* PC = Cast<APlayerController>(GEngine->GetFirstLocalPlayerController(GetWorld()));
	if (!PC) return;
	//PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);    //  #include "Kismet/GameplayStatics.h"
	//===  Set Game InputCompomemt -----
	PC->InputComponent = StoredInputComponent; 
	DisplayDialog->StopDialog();
	
	PC->bShowMouseCursor = false;
	PC->SetInputMode(FInputModeGameOnly());

}


void ADLG_GlobalActor::ChangeVariables(FResponseToDraw& CurrentResponse)
{
	for (int32 i = 0; i < CurrentResponse.VariableToChange_Name.Num(); i++)
	{
		if (CurrentResponse.VariableToChange_LocalOrGlobal[i] == FString("local"))
		{
			int32 LocalVarIndex = FCString::Atoi(*CurrentResponse.VariableToChange_Name[i]);
			if (LocalVarIndex != -1)
				LocalVariables[LocalVarIndex] =	FName(*CurrentResponse.VariableToChange_Value[i]);
		}
		else   //  ========  "Global"  =========
		{

			FName* GlobalValueRef = GlobalVariable.Find(FName(*CurrentResponse.VariableToChange_Name[i]));
			if (GlobalValueRef)
			{
				*GlobalValueRef = FName(*CurrentResponse.VariableToChange_Value[i]);
			}
		}

	}
}





/*   77777777777777777777777777777777777777777777777777777
void ADLG_GlobalActor::DLG_GenerateDialog(FString& _LastDialog, FString& _LastSpeech, TArray<FString> &_Replic, 
										TArray<FString> &_Response, TArray<int32> &_ResponseIndex,  bool isNew)  // isNew = false
{
	//if(isNew)
	//{
	//	DisplayDialog->PrepareToNewGenerate();
	//}
	//else
	//{
	//	DisplayDialog->PrepareToContinueGenerate();
	//}

	//DisplayDialog->GenerateDialogPanel(this, _LastDialog, _LastSpeech, _Replic, _Response, _ResponseIndex);
}
*/




// Called every frame
//void ADLG_GlobalActor::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//
//}




void ADLG_GlobalActor::OnResponseButtonClicked(FString& _XmlFileContent, FString _LastDialogNode, FString _LastSpeechNode, int32 _ResponseIndex)
{
	/*
	//  ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++11111111111111111111111111111111111111111111111111111111111111111
	//  ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++11111111111111111111111111111111111111111111111111111111111111111
	//  ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++11111111111111111111111111111111111111111111111111111111111111111
	//  ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++11111111111111111111111111111111111111111111111111111111111111111
	//  ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++11111111111111111111111111111111111111111111111111111111111111111
	//  ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++11111111111111111111111111111111111111111111111111111111111111111
	//  ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++11111111111111111111111111111111111111111111111111111111111111111
	//  ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++11111111111111111111111111111111111111111111111111111111111111111

	//  Get xmlFile Content
	std::string source = (TCHAR_TO_UTF8(*_XmlFileContent));
	pugi::xml_document xmlDoc;
	xmlDoc.load(source.c_str());

	//  Get Root Node
	pugi::xml_node RootNode = xmlDoc.child("name");
	std::string RootNodeStr(RootNode.attribute("name").as_string());

	//  --- where we need to go next  ---
	std::string FindingDialogNode = (TCHAR_TO_UTF8(*_LastDialogNode));
	std::string FindingSpeechNode = (TCHAR_TO_UTF8(*_LastSpeechNode));

	FString NextDialogNode = FString("DEFAULT");
	FString NextSpeechNode = FString("DEFAULT");
	FString TransitType = FString("none");


	//   1111  ================  Run over All <dialog>,   finding: DlgName="?????" 
	pugi::xpath_node_set DLG_DialogBranchNode = RootNode.select_nodes("dialog");
	for (int32 i_Dialog = 0; i_Dialog < DLG_DialogBranchNode.size(); i_Dialog++)
	{

		//   look for attribute("DlgName")  ==  "???????" 
		std::string _StrDialog(DLG_DialogBranchNode[i_Dialog].node().attribute("DlgName").as_string());

		//  ----  when finded Dialog-node we need  ----
		if (_StrDialog == FindingDialogNode)
		{
			//   2222  ================  Run over All <CurDialog->speech>,   finding: marker="?????" 
			pugi::xpath_node_set DLG_SpeechBranchNode = DLG_DialogBranchNode[i_Dialog].node().select_nodes("speech");
			for (int32 i_Speech = 0; i_Speech < DLG_SpeechBranchNode.size(); i_Speech++)
			{
				//   look for attribute("marker")  ==  "DEFAULT" or what we need
				std::string _StrSpeech(DLG_SpeechBranchNode[i_Speech].node().attribute("marker").as_string());
				//  ----  when finded Speech-node we need, Get them parameter  ----
				if (_StrSpeech == FindingSpeechNode)
				{

					      

					//   4444  ================  Get responseNode we need from current <CurDialog->speech>   =====================
					pugi::xpath_node_set DLG_ResponseBranchNode = DLG_SpeechBranchNode[i_Speech].node().select_nodes("response");
					
					//  get property "repeat" from responseNode[_ResponseIndex]
					std::string _StrResponseProp_repeat(DLG_ResponseBranchNode[_ResponseIndex].node().attribute("repeat").as_string());
					if (_StrResponseProp_repeat == "once")
					{
						DLG_ResponseBranchNode[_ResponseIndex].node().attribute("repeat").set_value("once_done");
						std::ostringstream DoChangeText;
						xmlDoc.save(DoChangeText);
						std::string DoChangeText_stdCPP = DoChangeText.str();
						std::wstring DoChangeText_stdCPPW = pugi::as_wide(DoChangeText_stdCPP.c_str());
						_XmlFileContent = FString(DoChangeText_stdCPPW.c_str());


						//UE_LOG(LogTemp, Warning, TEXT("unit->data->py = '%s'"), *_XmlFileContent);
					}

					//  get property "dialog" from responseNode[_ResponseIndex]:  Next using DialodNode
					std::string _StrResponseProp_dialogLink(DLG_ResponseBranchNode[_ResponseIndex].node().attribute("dialog").as_string());
					if (_StrResponseProp_dialogLink != "")
					{
						NextDialogNode = FString(_StrResponseProp_dialogLink.c_str());
					}
					 
					//  get property "marker" from responseNode[_ResponseIndex]:  Next using SpeechNode
					std::string _StrSpeechProp_SpeechLink(DLG_ResponseBranchNode[_ResponseIndex].node().attribute("marker").as_string());
					if (_StrSpeechProp_SpeechLink != "")
					{
						NextSpeechNode = FString(_StrSpeechProp_SpeechLink.c_str());
					}

					//  get property "type" from responseNode[_ResponseIndex]:  Type of next Transit  //BREACK,  EXIT,  BACK
					std::string _StrSpeechProp_ransitType(DLG_ResponseBranchNode[_ResponseIndex].node().attribute("type").as_string());
					if (_StrSpeechProp_ransitType != "")
					{
						TransitType = FString(_StrSpeechProp_ransitType.c_str());
					}
					
					
					// Change Variables Locale and Globale
					pugi::xpath_node_set DLG_changeValueBranchNode = DLG_ResponseBranchNode[_ResponseIndex].node().select_nodes("change");
					for (int32 i = 0; i < DLG_changeValueBranchNode.size(); i++)
					{
						//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
						//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
						//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
						//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
					}
					

					//BREACK,  EXIT,  BACK
					//dialog="dlgName"  marker="Revisor_konflict_1" type="BREACK"
				}
			}
		}

	}
	if (NextSpeechNode == FString("DEFAULT") || NextSpeechNode == FString(""))
	{
		if (TransitType == FString("BACK"))
		{
			DLG_PlayDialog(_XmlFileContent, ETransitType::Back, _LastDialogNode, _LastSpeechNode);
		}
		else if (TransitType == FString("BREACK"))
		{
			DLG_PlayDialog(_XmlFileContent, ETransitType::Breack, _LastDialogNode, _LastSpeechNode);
		}
		else if(TransitType == FString("EXIT"))
		{
			ExitDialog();
		}
		else
		{
			//   ERROR
		}
	}
	else
	{
		// ------- Next dialog block is (Default___DialogNode and GetedNew___SpeechNode) -------
		if (NextDialogNode == FString("DEFAULT") || NextDialogNode == FString(""))
		{
			DLG_PlayDialog(_XmlFileContent, ETransitType::StartDialog, _LastDialogNode, NextSpeechNode);
		}
		// ------- Next dialog block is (GetedNew___DialogNode and GetedNew___SpeechNode) -------
		else
		{
			DLG_PlayDialog(_XmlFileContent, ETransitType::StartDialog, NextDialogNode, NextSpeechNode);
		}
		
	}
	*/
}


void ADLG_GlobalActor::ADLG_GlobalActor::ExitDialog()
{

}





//  ===============================================================================================
//  ===============================================================================================
//  ===========================              Global variable           ============================
//  ===============================================================================================
//  ===============================================================================================


void ADLG_GlobalActor::SetGlobalVariablesMapRef(UPARAM(ref) TMap<FName, FName>& _GlobalVariable)
{
	GlobalVariable = _GlobalVariable;
	GlobalVariable.KeySort([](FName A, FName B) { return A < B; });

	/*
	UE_LOG(LogTemp, Warning, TEXT("-----------DDDDDDDDDDDDDDD------------"));
	for (auto& Elem : GlobalVariable)
	{
		UE_LOG(LogTemp, Warning, TEXT("TMap-------: = '%s', '%s'"), *Elem.Key.ToString(), *Elem.Value.ToString());
	}
	*/
}


//TMap<FName, FName> GlobalVariable;

void ADLG_GlobalActor::AddGlobalVar(FName _key, FName _value)
{	
	GlobalVariable.Add(_key, _value);
	GlobalVariable.KeySort([](FName A, FName B)	{ return A < B; });

	/*UE_LOG(LogTemp, Warning, TEXT("-----------------------"));
	for (auto& Elem : GlobalVariable)
	{
		UE_LOG(LogTemp, Warning, TEXT("TMap-------: = '%s', '%s'"), *Elem.Key.ToString(), *Elem.Value.ToString());
	}*/
}

FName ADLG_GlobalActor::GetGlobalVar(FName _key)
{
	//FPlatformMisc::LocalPrint(*FString::Printf(TEXT("(%i, \"%i\")%i"), 10, 20, 30));

	FName val = GlobalVariable[_key];
	//UE_LOG(LogTemp, Warning, TEXT("TMap-------: = '%s', '%s'"), *_key.ToString(), *val.ToString());
	return val;
}
/*
//void ADLG_GlobalActor::OnVariableSet_Implementation(UPARAM(ref) FName& key, UPARAM(ref) FName& value)
void ADLG_GlobalActor::OnVariableSet_Implementation(FName& key, FName& value)
{

}
*/








