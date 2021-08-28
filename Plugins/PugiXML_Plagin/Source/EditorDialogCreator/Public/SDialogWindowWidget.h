// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

//#include "DLG_GlobalActor.h"
//#include "../../PugiXML_Plagin/Public/DLG_GlobalActor.h"

#include "DLGButtonDialog.h"
#include "DLGButtonCondition.h"
#include "DLGButtonResponse.h"

#include "Widgets/Input/SSpinBox.h"

#include "Widgets/SCompoundWidget.h"
  


struct FVariables
{
	FName VariableName = FName("none");
	//TSharedPtr<class STextBlock> ConditionVariable_Name_Statick;
	TSharedPtr<class SEditableTextBox> ChangeVariable_Name_Editable;
	TSharedPtr<class UButton> ChangeVariable_Name_Button;
	bool IsProperty_VariableName_EditNow = false;

	FName VariableValue = FName("none");
	//TSharedPtr<class STextBlock> ConditionVariable_Value_Statick;
	TSharedPtr<class SEditableTextBox> ChangeVariable_Value_Editable;
	TSharedPtr<class UButton> Change_VariableValue_Button;
	bool IsProperty_VariableValue_EditNow = false;

	bool isVariableGlobal = true;
};

struct FCondition
{

	FName ConditionType = FName("and");
	//TSharedPtr<class STextBlock> Condition_Type_Statick;                 //   DELETE OTHER, THE SAME, STATICK-BLOCK in OTHER SECTIONSS
	TSharedPtr<class SEditableTextBox> Condition_Type_Editable;
	TSharedPtr<class UButton> ChangeCondition_Type_Button;
	bool IsProperty_Type_EditNow = false;

	FName VariableName = FName("none");
	//TSharedPtr<class STextBlock> ConditionVariable_Name_Statick;
	TSharedPtr<class SEditableTextBox> ConditionVariable_Name_Editable;
	TSharedPtr<class UButton> ChangeConditionVariable_Name_Button;
	bool IsProperty_VariableName_EditNow = false;

	FName VariableValue = FName("none");
	//TSharedPtr<class STextBlock> ConditionVariable_Value_Statick;
	TSharedPtr<class SEditableTextBox> ConditionVariable_Value_Editable;
	TSharedPtr<class UButton> ChangeCondition_ariableValue_Button;
	bool IsProperty_VariableValue_EditNow = false;

	bool isVariableGlobal = true;
};


struct FRepSection
{

	 
	FName Time = FName("0");
	//TSharedPtr<class SSpinBox<float>> SB_Delay;

	FName Delay = FName("0");
	//TSharedPtr<class SSpinBox<float>> SB_AfterDelay;

	FName Speker = FName("none");
	//TSharedPtr<SComboBox<TSharedPtr<FString>>> CB_Spiker;
	//TSharedPtr<FString>	CurrentSpiker = MakeShareable(new FString(TEXT("none")));
	//bool isSpikerComboBoxEditNow = false;

	FName Sound = FName("none");
	//TSharedPtr<SComboBox<TSharedPtr<FString>>> CB_Sound;
	//TSharedPtr<FString>	CurrentSound = MakeShareable(new FString(TEXT("none")));
	//bool isSoundComboBoxEditNow = false;

	TSharedPtr<class SDLGButtonDialog> ReplicTitleCollapsedContent_Button;

	TSharedPtr<class STextBlock> ReplicSectionRepeat_Statick;
	TSharedPtr<class SEditableTextBox> ReplicSectionRepeat_Editable;
	TSharedPtr<class SDLGButtonDialog> ChangeReplicSectionRepeat_Button;

	FString ComentText = FString("none");

	TArray<FCondition> RepCondition;	
	TSharedPtr<class SVerticalBox> RepConditionBlock;
	bool IsConditionOpen = false;

	//bool IsSectionOpen = true;
	bool IsSectionEditNow = false;

};
  
struct FResponseSection 
{

	//FName RepeatProperty = FName("none");   //  once,   always

	TSharedPtr<class SDLGButtonDialog> ResponseTitleCollapsedContent_Button;

	TSharedPtr<SComboBox<TSharedPtr<FString>>> CB_ResponseRepeat;
	TSharedPtr<FString>	ResponseRepeatPropperty = MakeShareable(new FString(TEXT("once")));

	TSharedPtr<SComboBox<TSharedPtr<FString>>> CB_ResponseReturnType;
	TSharedPtr<FString>	ResponseReturnTypePropperty = MakeShareable(new FString(TEXT("click_link_once"))); 

	FName DialogLink = FName("DEFAULT");
	FName SpeechLink = FName("DEFAULT");
	//TSharedPtr<class STextBlock> ResponseSectionRepeat_Statick;
	//TSharedPtr<class SEditableTextBox> ResponseSectionRepeat_Editable;
	//TSharedPtr<class SDLGButtonDialog> ChangeResponseSectionRepeat_Button;

	FString ComentText = FString("none");

	TSharedPtr<class SVerticalBox> ResponseBlock;
	//TArray<FSpeechSection> SpeechSection;

	TArray<FCondition> ResponseCondition;
	TSharedPtr<class SVerticalBox> ResponseConditionBlock;
	bool IsConditionOpen = false;
	 

	TArray<FVariables> VariableSection;
	TSharedPtr<class SVerticalBox> VariableBlock;
	bool IsVariableOpen = false;
	 
	//bool IsSectionOpen = true;
	bool IsSectionEditNow = false;

};
 
struct FReplicSection
{
	//FName RepeatProperty = FName("none");   //  once,   after_once,   return_breack,  always

	TSharedPtr<class SDLGButtonDialog> ReplicTitleCollapsedContent_Button;


	TSharedPtr<SComboBox<TSharedPtr<FString>>> CB_ReplicRepeat;
	TSharedPtr<FString>	ReplicRepeatPropperty = MakeShareable(new FString(TEXT("once")));

	//TSharedPtr<class STextBlock> ReplicSectionRepeat_Statick;
	//TSharedPtr<class SEditableTextBox> ReplicSectionRepeat_Editable;
	//TSharedPtr<class SDLGButtonDialog> ChangeReplicSectionRepeat_Button;

	FString ComentText = FString("none");
	//TSharedPtr<class SMultiLineEditableTextBox> ReplicComent_EditableMultiline;

	TSharedPtr<class SVerticalBox> RepBlock;
	TArray<FRepSection> RepSection; 

	TArray<FCondition> ReplicCondition;
	TSharedPtr<class SVerticalBox> ReplicConditionBlock;
	bool IsConditionOpen = false;

	bool IsSectionOpen = false;
	bool IsSectionEditNow = false;

};
     
struct FSpeechSection
{
	FName Name = FName("DEFAULT");   //  a lot of "DEFAULT" or lot of "What_user_set"

	TSharedPtr<class SDLGButtonDialog> SpeechTitleCollapsedContent_Button;

	TSharedPtr<class STextBlock> SpeechSectionName_Statick;
	TSharedPtr<class SEditableTextBox> SpeechSectionName_Editable;
	TSharedPtr<class SDLGButtonDialog> ChangeSpeechSectionName_Button;
	 
	

	TSharedPtr<class SVerticalBox> ReplicAndResponseBlock;
	TArray<FReplicSection> ReplicSection;
	TArray<FResponseSection> ResponseSection;

	//TSharedPtr<class SVerticalBox> SpeechConditionBlock;
	//TArray<FReplicSection> SpeechConditionSection;
	TArray<FCondition> SpeechCondition;
	TSharedPtr<class SVerticalBox> SpeechConditionBlock;
	bool IsConditionOpen = false;

	 
	bool IsSectionOpen = false;
	bool IsSectionEditNow = false;

};


//USTRUCT(BlueprintType, Blueprintable)   
struct FDialogSection
{
//	GENERATED_BODY()


	//UPROPERTY()
	FName Name = FName("DEFAULT");   //  1 - "DEFAULT" and other "What_user_set"

	//TSharedPtr<class STextBlock> DialogSectionName_Statick;
	TSharedPtr<class SEditableTextBox> DialogSectionName_Editable;
	TSharedPtr<class SDLGButtonDialog> DialogTitleCollapsedContent_Button;
	TSharedPtr<class SDLGButtonDialog> ChangeDialodSectionName_Button;
	

	TSharedPtr<class SVerticalBox> SpeechBlock;
	TArray<FSpeechSection> SpeechSection;


	bool IsSectionOpen = false;
	bool IsSectionEditNow = false;

};


struct FSound
{
	FName name = FName("none");

	FString SoundAssetPath;
	FString SoundComment;


	TSharedPtr<class STextBlock> SoundrName_Statick;
	//TSharedPtr<class SEditableTextBox> SoundrName_Editable;

};

//USTRUCT(BlueprintType, Blueprintable)   
struct FSpekers
{
//	GENERATED_BODY()


	FName name = FName("none");

	TSharedPtr<class STextBlock> SpekerName_Statick;
	TSharedPtr<class SEditableTextBox> SpekerName_Editable;

	TSharedPtr<class SScrollBox> SounsScroll;


	//UPROPERTY()
	FString SpekersAssetPath;
	FSlateBrush SpekersImageBrush;


	TArray<FSound> Sound;

	bool IsSectionEditNow = false;

	// sounsAsset Path ++++++++++++++++++++++++++
};



UENUM()  //BlueprintType, Blueprintable
enum class EProppertyToChange : uint8
{
	none,

	DialogName,
	SpeechName,
	repeatReplic,   ////////////////---------------------  NOT String
	repeatResponse,   ////////////////---------------------  NOT String	
	DialogLink,
	SpeechLink,
	Delay,
	AfrerDelay,
	 
	Speech_condition_type,
	Speech_condition_varType,
	Speech_condition_varName,
	Speech_condition_varValue,
	Replic_condition_type,
	Replic_condition_varType,
	Replic_condition_varName,
	Replic_condition_varValue,
	rep_condition_type,
	rep_condition_varType,
	rep_condition_varName,
	rep_condition_varValue,
	Response_condition_type,		// and/or
	Response_condition_varType,   // Global/LOcal
	Response_condition_varName,
	Response_condition_varValue,

	//Response_variable_type,
	Response_variable_varType,
	Response_variable_varName,
	Response_variable_varValue,
	//VariableName_Property,
	//VariableValue_Property,
	//dialogLink,
	//gotoMarker,
	//gotoType,

	replicComent,
	repComent,
	responseComent,


	speker,
	sound,
	time,
	delay,

	SpekerinSpekerBlock,


	AddDialog,
	AddSpeech,
	AddReplick,
	AddResponse,
	ButtonAddRep,
	ButtonAddSpeech_Condition,
	ButtonAddReplic_Condition,
	ButtonAddResponse_Condition,
	ButtonAddResponse_Variable,
	ButtonAddRep_Condition,

	MoveDialog,
	MoveSpeech,
	MoveSpeech_Condition,
	MoveReplic,
	MoveReplic_Condition,
	MoveRep,
	MoveRep_Condition,
	MoveResponse,
	MoveResponse_Condition,
	MoveResponse_Variable,

	RemoveDialog,
	RemoveSpeech,
	RemoveSpeech_Condition,
	RemoveReplic,
	RemoveReplic_Condition,
	RemoveRep,
	RemoveRep_Condition,
	RemoveResponse,
	RemoveResponse_Condition,
	RemoveResponse_Variable,

	
	 


	CollapsedDialogSection,
	CollapsedSpeechSection,
	CollapsedSpeech_Condition,
	CollapsedReplicSection,
	CollapsedReplic_Condition,
	CollapsedRep_Condition,
	CollapsedResponseSection,
	CollapsedResponse_Condition,
	CollapsedResponse_Variables,

	ButtonAdd_Variable,
	Variable_varName,
	Variable_varValue
};


UENUM()  //BlueprintType, Blueprintable
enum class EShouldUpdate : uint8
{
	none,
	inDialog,
	inSpeech,
	inReplic,
	inRep,
	inResponse
};


struct FPropertyIndex
{
	//EProppertyToChange ProppertyToChange;
	int32 iDialog = -1;
	int32 iSpeech = -1;
	int32 iReplicOrResponse = -1;
	int32 iRepOrResponsCondition = -1;
	int32 iRepCondition = -1;

	int32 iSpeechCondition = -1;
	int32 iReplicCondition = -1;
	int32 iResponseCondition = -1;
	int32 iResponseVariable = -1;

	int32 iVariable = -1;

	int32 SpekerIndex = -1;
};

  
 
class SDialogWindowWidget : public SCompoundWidget  //  PUGIXML_PLAGIN_API
{
public:
	SLATE_BEGIN_ARGS(SDialogWindowWidget)
	{}
		//SLATE_ARGUMENT()
		SLATE_ATTRIBUTE(FString*, PathToFile)
//		SLATE_ATTRIBUTE(FSlateColor, myLinearImageColor_TEST)
//		SLATE_ATTRIBUTE(FVector2D, ViewportSizeParam)
//		SLATE_ATTRIBUTE(class AWorldBoundActor*, BoundWorldActor)
//		SLATE_ATTRIBUTE(class UGlobalGameInstance*, GameInstance)
		//SLATE_EVENT()
		SLATE_END_ARGS()

	

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

	virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;

	
	int32 OnPaint
	(
		const FPaintArgs& Args,
		const FGeometry& AllottedGeometry,
		const FSlateRect& MyCullingRect,
		FSlateWindowElementList& OutDrawElements,
		int32 LayerId,
		const FWidgetStyle& InWidgetStyle,
		bool bParentEnabled
	) const override;


public:


	//+++++++++++++++++++++++++++++++++++++++++++++++


	TSharedPtr<class SButton> ContentPanelShowButton;
	TSharedPtr<class SButton> VariablesPanelShowButton;
	TSharedPtr<class SButton> SpekerPanelShowButton;
	FReply OnButtonSelectLayer(FName MainPanelType);

	EVisibility DialogContentVisibility = EVisibility::Visible;   //  // Collapsed  Visible
	EVisibility DialogVariablesVisibility = EVisibility::Collapsed;
	EVisibility DialogSpikersVisibility = EVisibility::Collapsed;


	TSharedPtr<class SVerticalBox> LeftIndicator_1;
	TSharedPtr<class SVerticalBox> LeftIndicator_2;
	TSharedPtr<class SVerticalBox> RightIndicator;
	TSharedPtr<class SScrollBox> MainContentPanelBlock;           //   Main content, where will add new content.   ScrollBox
	TSharedPtr<class SScrollBox> MainSpikersPanelBlock;       //    Spikers
	TSharedPtr<class SScrollBox> MainSpikersEditablePanelBlock;       //    Spikers sEditable


	const FSlateBrush* PlaySound;
	const FSlateBrush* ImageLayerActivate;
	const FSlateBrush* ImageLayerDefault;
	const FSlateBrush* TitleDialog;
	const FSlateBrush* TitleDialogStart;
	const FSlateBrush* TitleDialogEnd;
	const FSlateBrush* TitleReplic;
	const FSlateBrush* TitleReplicStart;
	const FSlateBrush* TitleReplicEnd;
	const FSlateBrush* TitleResponse;
	const FSlateBrush* TitleResponseStart;
	const FSlateBrush* TitleResponseEnd;

	const FSlateBrush* ImageAddElement;
	//const FSlateBrush* ImageRemoveElement;
	const FSlateBrush* ImageMoveElement;
	const FSlateBrush* ImageDeleteElement;
	const FSlateBrush* ImageAddSoundElement;
	const FSlateBrush* ImageConditionButtonOn;
	const FSlateBrush* ImageConditionButtonOFF;
	const FSlateBrush* ImageVariableButtonOn;
	const FSlateBrush* ImageVariableButtonOff;
	const FSlateBrush* GetImageConditionButton(EProppertyToChange _ProppertyToChange, FPropertyIndex PropertyIndex)  const;
	const FSlateBrush* PropertyDialog;
	const FSlateBrush* PropertyDialogStart;
	const FSlateBrush* PropertyDialogEnd;
	const FSlateBrush* PropertyReplic;
	const FSlateBrush* PropertyReplicStart;
	const FSlateBrush* PropertyReplicEnd;
	const FSlateBrush* PropertyResponse;
	const FSlateBrush* PropertyResponseStart;
	const FSlateBrush* PropertyResponseEnd;

	const FSlateBrush* ImageValueZone;
	const FSlateBrush* Condition;
	const FSlateBrush* ConditionStart;
	const FSlateBrush* ConditionEnd;
	const FSlateBrush* ImageButtonSectionRollUp;
	const FSlateBrush* ImageButtonSectionExpand;
	const FSlateBrush* GetImageButtonSectionCollapsed(EProppertyToChange _ProppertyToChange, FPropertyIndex PropertyIndex)  const;
	EVisibility IsSectionCollapsed(EProppertyToChange _ProppertyToChange, FPropertyIndex PropertyIndex) const;
	


	void AddDialogSection(FPropertyIndex PropertyIndex);
	void AddSpeechSection(FPropertyIndex PropertyIndex);
	void AddReplicSection(FPropertyIndex PropertyIndex);
	void AddResponseSection(FPropertyIndex PropertyIndex);
	void AddRepSection(FPropertyIndex PropertyIndex);
	void AddSpeechCondition(FPropertyIndex PropertyIndex);
	void AddRepCondition(FPropertyIndex PropertyIndex);
	void AddReplicCondition(FPropertyIndex PropertyIndex);
	void AddResponseCondition(FPropertyIndex PropertyIndex);
	void AddResponseVariable(FPropertyIndex PropertyIndex);

	FReply SaveAll();
	FReply LoadAll();
	  
	//void UpdateContentPanel();
	void UpdateDialogBlock();
	void DrawConditionElement(TSharedPtr<SVerticalBox>& RepConditionBlock,
								FPropertyIndex& CurrentPropertyIndex,
								EProppertyToChange AddButtonPropperty,
								EProppertyToChange MoveButtonPropperty,
								EProppertyToChange RemoveButtonPropperty,

								TSharedPtr<class SEditableTextBox> &TextBoxCondition_Type,
								FName& Type_Text,
								EProppertyToChange ConditionTypePropperty,
								TSharedPtr<class SEditableTextBox> &TextBoxVariable_Name,
								FName& VariableName_Text,
								EProppertyToChange VarNamePropperty,
								TSharedPtr<class SEditableTextBox> &TextBoxVariable_Value,
								FName& VariableValue_Text,
								EProppertyToChange VarValuePropperty,

								EProppertyToChange VarTypePropperty);

	//bool Update = true;
	EShouldUpdate ShouldUpdate = EShouldUpdate::none;

	//void ChangeSectionProperty(EProppertyToChange ProppertyToChange, int32 _CurrentDialogSectionIndex = -1, int32 _CurrentSpeechSectionIndex = -1, int32 _ReplicOrResponseIndex = -1);
	void EditProperty(EProppertyToChange _ProppertyToChange, FPropertyIndex PropertyIndex);  //XXXXXXXXXXXX++++++++++++++++++++++++
	//void SwitchCollapsedSection(EButtonDialogType _ButtonDialogType, int32 _DialogIndex = -1, int32 _SpeechIndex = -1, int32 _ReplicOrResponseIndex = -1);
	void SwitchCollapsedSection(EProppertyToChange _ProppertyToChange, FPropertyIndex PropertyIndex);

	TArray<FDialogSection> DialogSection;


	

	/*
	.OptionsSource(&SpikersList)
	.OnComboBoxOpening( this, &SDialogWindowWidget::OnSpekerComboBoxOpening, CurrentPropertyIndex)
	.OnGenerateWidget(this, &SDialogWindowWidget::HandleComboBoxGenerateWidget)
	.OnSelectionChanged(this, &SDialogWindowWidget::GetSpekerComboList, CurrentPropertyIndex)
	//.InitiallySelectedItem(DialogSection[i_Dlg].SpeechSection[i_Speech].ReplicSection[i_Replic].RepSection[i_Rep].CurrentSpiker)
	[

		SNew(STextBlock)
		.Text(this, &SDialogWindowWidget::GetCurrentItemLabelXXXXXXXXXXXXXXXXXXXXXXXXX, CurrentPropertyIndex)
		*/

	///////////////////////////////////////////////////////////////////////////////////////////////////////////  EditProperty




	FReply OnButtonClick(EProppertyToChange ProppertyToChange, FPropertyIndex PropertyIndex);
	FReply OnButtonRemoveClick(EProppertyToChange ProppertyToChange, FPropertyIndex PropertyIndex);
/*	void OnDLGButtonClick(EButtonDialogType _ButtonDialogType,       //  77777777777777777777777777777777777777777777
							int32 _Param_DialodIndex = -1,
							int32 _Param_SpeechIndex = -1,
							int32 _Param_ReplicOrResponseIndex = -1,
							int32 _Param_RepOrConditionIndex = -1,						int32 _Param_ConditionIndex = -1

							//int32 Param_Replic = -1,
							////int32 Param_Replic_condition = -1,
							//
							//int32 Param_Rep = -1,
							//int32 Param_condition = -1
						);
	*/
	///////////////////////////////int32 changingDialod_Index = -1;
	//////////////////////////////int32 changingSpeech_Index = -1;
	/////////////////////////////////int32 changingReplicOrResponse_Index = -1;
	//int32 changingRepOrCondition_Index = -1;
	////////////////////////////////EProppertyToChange  changingPropperty = EProppertyToChange::none;
	
	//......   
	//......
	//......
	//......
	//......
	//......
	EVisibility GetVisibility_LocalVarIndicator(EProppertyToChange _ProppertyToChange, FPropertyIndex PropertyIndex) const;
	EVisibility GetVisibility_GlobalVarIndicator(EProppertyToChange _ProppertyToChange, FPropertyIndex PropertyIndex) const;
	EVisibility GetVisibilityOfSectionPropperty_Static(EProppertyToChange _ProppertyToChange, FPropertyIndex PropertyIndex) const;  
	EVisibility GetVisibilityOfSectionPropperty_Editable(EProppertyToChange _ProppertyToChange, FPropertyIndex PropertyIndex) const;  
	FText GetProppertyText(EProppertyToChange _ProppertyToChange, FPropertyIndex PropertyIndex) const;   
 
	void ConfirmEditableTextBox(const FText& Text, ETextCommit::Type TextType, EProppertyToChange ProppertyToChange, FPropertyIndex PropertyIndex);


	//   ConfirmCurrentSelection  //  HIDDEN-BUTTON BECOME UNHITTED, Breack this
	void ConfirmCurrentSelection(EProppertyToChange _ProppertyToChange, FPropertyIndex changingPropperty);
	void OnEditableTextChange(const FText& _Text);





	//  ================================           Combo-Box         ==============================================
	void InitComboBox_StaticList();   
	TSharedRef<SWidget> HandleComboBoxGenerateWidget(TSharedPtr<FString> InItem);
	TArray<TSharedPtr<FString>> ReplicRepeatComboList;
	TArray<TSharedPtr<FString>> ResponseRepeatComboList;
	TArray<TSharedPtr<FString>> ResponseReturnTypeComboList;
	
	void GetReplicRepeatComboList(TSharedPtr<FString> NewSelection, ESelectInfo::Type SelectInfo, FPropertyIndex PropertyIndex);   //XXXXXXXXXXX   ++++++++++++++
	void GetResponseRepeatComboList(TSharedPtr<FString> NewSelection, ESelectInfo::Type SelectInfo, FPropertyIndex PropertyIndex);   //XXXXXXXXXXX   ++++++++++++++
	void GetResponseReturnTypeComboList(TSharedPtr<FString> NewSelection, ESelectInfo::Type SelectInfo, FPropertyIndex PropertyIndex);   //XXXXXXXXXXX   ++++++++++++++
	//void OnReplicRepeatComboBoxOpening(FPropertyIndex PropertyIndex);
	FText GetCurrentReplicRepeatLabel(FPropertyIndex PropertyIndex) const;
	FText GetCurrentResponseRepeatLabel(FPropertyIndex PropertyIndex) const;
	FText GetCurrentResponseReturnTypeLabel(FPropertyIndex PropertyIndex) const;

	UPROPERTY()
		FString EditableChangedText;


	// ================================        SMenuAnchor   "HelperMeny"     ==============================================

	//FGeometry CachedGeometry;
	float HelperMenu_Height = 30.f;
	FOptionalSize GetHelperMenu_Height() const;
	bool CalculateHelperMenuPosition = false;
	bool isHelperMenuOpen = false;
	EVisibility GetHelperPanelVisibility() const;
	FMargin HelperPanelPosition = FMargin(0,0,0,0);
	FMargin  GetHelperPanelPosition() const;
	FReply CancelHelperPanel();
	FReply OnHelperPanelClick(EProppertyToChange ProppertyToChange, FPropertyIndex PropertyIndex);  
	FReply OnHelperPanelElementClick(EProppertyToChange ProppertyToChange, FPropertyIndex PropertyIndex, int32 index);
	TSharedPtr<class SScrollBox> HelperMenulList;
	TSharedPtr<class SEditableTextBox> HelperMenulEditableText;
	TArray<FString> ListElementTmp;   //  HelperPanel temporare list
	//TSharedPtr<SMenuAnchor> StacklessAnchorPanel;
	//FReply OnClickStacklessAnchor(TSharedPtr<SMenuAnchor> ClickedAnchor);
	//TSharedRef<SWidget> MakeAnchorMenuContent(FString ContentLabel) const;
	//TSharedRef<SWidget> MakeAnchorMenuContent(EProppertyToChange ProppertyToChange, FPropertyIndex PropertyIndex) const;
	  
/*
	TArray<TSharedPtr<FString>> SpikersList;
	TArray<TSharedPtr<FString>> SoundList;
	//  -- Speker ComboBox  ---
	void GetSpekerComboList(TSharedPtr<FString> NewSelection, ESelectInfo::Type SelectInfo, FPropertyIndex PropertyIndex);   //XXXXXXXXXXX   ++++++++++++++
	void OnSpekerComboBoxOpening(FPropertyIndex PropertyIndex);   
	FText GetCurrentSpikerLabel(FPropertyIndex PropertyIndex) const;
	//  -- Sound ComboBox  ---
	void GetSoundComboList(TSharedPtr<FString> NewSelection, ESelectInfo::Type SelectInfo, FPropertyIndex PropertyIndex);
	void OnSoundComboBoxOpening(FPropertyIndex PropertyIndex);
	FText GetCurrentSoundLabel(FPropertyIndex PropertyIndex) const;
*/
	
	// ---------------- SSpinBox -----------------------
	//float GetTimeValue(float value);
	void SetTimeValue(float value, ETextCommit::Type _Type, EProppertyToChange ProppertyToChange, FPropertyIndex PropertyIndex);
	//void SetTimeValue(double _NewValue, ECommitMethod _CommitMethod, ETextCommit::Type _Type);
	//++++static void SetDelayValue(float value/*, EProppertyToChange _ProppertyToChange, FPropertyIndex PropertyIndex*/);
	

	void SaveDialogToXML();
	void LoadDialogFromXML();
	void ChoiseLoadingXmlFile();

	FReply OnButtonExportDialog();
	FReply OnButtonImportDialog();
	FString* PathToCurrentXML = nullptr;

	//++++++++++++++++++++++++++++++++++++++++   SPEKER Block  ++++++++++++++++++++++
	  
	void SaveSpekersToXML();
	void LoadSpekersfromXML();
	void LoadSoundFromXMLSpeker(FName FoundingSpeker);  

	const FSlateBrush* SpekersImageDefault;
	void RedrawSpekersBlock();
	FReply AddSpekersElenemt();
	TArray<FSpekers> Speker;  //  Temp loaded Speker (combo bob-loaded)
	//TArray<FSound> Sound;

	int32 changingSpeker_Index = -1;

	FReply StoredSpekerIndex(EProppertyToChange _ProppertyToChange, int32 _index);
	FReply ChangeSpekerImage(int32 _index);
	//FReply AddSpekerSound(int32 _index);
	FReply RemoveSpeker(int32 _index);
	FReply ApplayImageAssetToSpeker(int32 _index);
	const FSlateBrush* GetSpekerImage(int32 _index) const;
	EVisibility GetVisibilitySpekerNameText_Static(int32 _Index) const;
	EVisibility GetVisibilitySpekerNameText_Editable(int32 _Index) const;
	FText GetSpikerNameText(int32 _Index) const;

	TArray<FString> AssetImagePath;
	TArray<FSlateBrush> AssetImageBrush;

	//  ConfirmCurrentSelection();

	//++++++++++++++++++++++++++++++++++++++++   SOUND Block  ++++++++++++++++++++++
	  
	TArray<FSound> Sound;     //  Temp loaded SpekerSound (combo bob-loaded)
	FReply AddSpekerSound(int32 iSpeker);
	void RedrawSoundsBlock(int32 iSpeker);
	FReply ChangeSpekerSoundItem(int32 iSpeker, int32 iSound);
	FReply ShowSpekerSoundItem(int32 iSpeker, int32 iSound);
	FReply ApplaySaundToSpekerSound(int32 iSpeker, int32 iSpekerSound, int32 iSound);
	FText GetSoundNameText(int32 _iSpeker, int32 _iSound) const;
	FText GetSoundCommentText(int32 _iSpeker, int32 _iSound) const;
	FText GetSoundPathText(int32 _iSpeker, int32 _iSound) const;
	void SpekerSoundNameEditableTextBox(const FText& Text, ETextCommit::Type TextType, int32 iSpeker, int32 iSpekerSound);
	void SpekerSoundCommentEditableTextBox(const FText& Text, ETextCommit::Type TextType, int32 iSpeker, int32 iSpekerSound);

	//int32 changingSpekerSound_Index = -1; 

	TArray<FString> AssetSoundPath;
	//TArray<FSlateBrush> AssetSoundBaseObject;

	//++++++++++++++++++++++++++++++++++++++++   VARIABLE Block  ++++++++++++++++++++++


	TArray<FVariables> Variables;   // iVariable
	TSharedPtr<class SScrollBox> MainVariablesPanelBlock;		  //   Main Panel Variables, where will add new variables.   ScrollBox
	FString DefaultDialog = FString("DEFAULT");

	void RedrawVariablesBlock();

	void AddVariable(FPropertyIndex PropertyIndex);

	void SaveVariablesToXML();
	void LoadVariablesFromXML();
	//LoadSpekersfromXML
	//
	//+++++++++++++++++++++    Element SIZE   ++++++++++++++++++++++++++ 

	float SizeKoef = 0.8f;   //    * SizeKoef
	//float buttonSizeKoef = 1.f;

	 
	float DialodButtonSmallSize = 22.f;
	float DialodButtonBigSize = 42.f;

	float SpeechButtonSmallSize = 22.f;
	float SpeechButtonBigSize = 38.f;

	float ReplicButtonRemoveSize = 24.f;
	float ReplicButtonMoveSize = 22.f;
	float ReplicButtonAddSize = 21.f;
	float ReplicButtonSmallSize = 20.f;
	float ReplicButtonBigSize = 35.f;
	float RepButtonSmallSize = 22.f;
	float RepButtonSmallInsileSSize = 20.f;
	//float RepButtonBigSize = 27.f;

	FOptionalSize GetButtonSize(float size) const;
	FMargin GetPadding(float left, float Up, float Right, float Bottom);
	//this, &SDialogWindowWidget::GetDuttonSize, ReplicButtonBigSize
	
	//++++++++++++++++++++++++++++++++++++++++++++++++

	
	  


	







	TSharedPtr<class SVerticalBox> ContentArea;
	TSharedPtr<class SVerticalBox> VariablesArea;

	FReply OnButtonContentDialog(FName str);
	EVisibility GetContentPanelState() const;
	EVisibility GetVariablesPanelState() const;
	EVisibility ContentPanelState = EVisibility::Visible;
	EVisibility VariablesPanelState = EVisibility::Collapsed;


	
	//FReply ButtonContentDialog_Presed(int32 a) ;



	TSharedPtr<class SEditableTextBox> EditableText1;
	FString str1 = FString("str1111122222233333");
	TSharedPtr<class SMultiLineEditableTextBox> MlEditableText2;
	TSharedPtr<class SEditableTextBox> EditableText3;
	//void OnButtonT(const FText& Text);
	






	//       =========================         COMBP BPX       ========================

	TSharedPtr<SComboBox<TSharedPtr<FString>>> SecondComboBox;
	TArray<TSharedPtr<FString>> SecondComboBoxOptions;
	TSharedPtr<FString>	CurrentItem;
	void HandleSelectorComboBoxSelectionChanged1(TSharedPtr<FString> NewSelection, ESelectInfo::Type SelectInfo);
	//FText GetCurrentItemLabel() const;
	//TSharedRef<SWidget> HandleComboBoxGenerateWidget(TSharedPtr<FString> InItem);

	//float Rotation = 0.f;




//	FSlateColor RuntimeChangeImage_Color() const;
//	FSlateColor RuntimeChangeImage_Color_Param(float _R, float _G) const;

	//FVector2D DrawZone;
/*
	FVector2D ViewportSize;

	FVector2D mousePos;
	FVector2D MapMoveButtonPosition;
	FVector2D CurrentPanelPosition;
	FVector2D mousePosDeltaForMapPanel;
	FVector2D mousePosDeltaForMoveButton;
	bool bMiniMapOffset = false;

	FVector2D PointPositionInMap;
	

	FLinearColor ColorTemp = FLinearColor::Red;
	//float Y_Position = 0.f;

	FReply Button_AAAAA_Presed(int32 id);

	FReply ButtonMapPanelMove();
	//FReply ClickOnMiniMap();

	void LeftMouseRelase();
	void LeftMousePresed();






	FVector2D LeftMouseClickClick_Position;

	FVector2D ChangeImagePositionTemp() const;

	*/

//	TSharedPtr< class SBorder> MiniMapSlot;  
//	TSharedPtr< class SButton> MapMoveButton;
};
