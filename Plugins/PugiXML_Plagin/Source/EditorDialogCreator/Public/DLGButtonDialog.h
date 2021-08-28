// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
 

#include "Widgets/SCompoundWidget.h"




UENUM()  //BlueprintType, Blueprintable
enum class EButtonDialogType : uint8
{
	AddNewDialog,
	AddNewSpeech,
	AddNewReplick,
	AddNewRep,
	AddNewResponse,
	DialogName,
	SpeechName,
	ReplicRepeat,
	RepName,
	ResponseRepeat,
	SpeechConditionName,
	ReplicConditionName,
	RepConditionName,
	ResponseConditionName,

	CollapsedDialogSection,
	CollapsedSpeechSection,
	CollapsedSpeechCondition,
	CollapsedReplicSection,
	CollapsedReplicCondition,
	CollapsedResponseSection,
	CollapsedResponseCondition,


};



DECLARE_DELEGATE_SixParams(FDLGButtonDialogClicked, EButtonDialogType, int32, int32, int32, int32, int32);


class SDLGButtonDialog : public SCompoundWidget  //SLATE1_API  // PUGIXML_PLAGIN_API
{
public:
	SLATE_BEGIN_ARGS(SDLGButtonDialog)
	{}
		//SLATE_ARGUMENT()
		SLATE_EVENT(FDLGButtonDialogClicked, OnDLGButtonDialogClicked)
		SLATE_ATTRIBUTE(EButtonDialogType, ButtonDialogType)
		SLATE_ATTRIBUTE(int32, DialodIndex)
		SLATE_ATTRIBUTE(int32, SpeechIndex)
		SLATE_ATTRIBUTE(int32, ReplicOrResponseIndex)
		SLATE_ATTRIBUTE(int32, RepOrConditionIndex)
		SLATE_ATTRIBUTE(int32, ConditionIndex)
		SLATE_ATTRIBUTE(bool, SetVisibility)
		//SLATE_EVENT()
	SLATE_END_ARGS()

	

	
	void Construct(const FArguments& InArgs);

	//virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;
	


	//   Stored function whith this DLG_Button exequte
	FDLGButtonDialogClicked Delegate_OnDLGButtonDialogClicked;

	EButtonDialogType Param_ButtonDialogType;
	int32 Param_DialodIndex = -1;
	int32 Param_SpeechIndex = -1;
	int32 Param_ReplicOrResponseIndex = -1;    // depend of  "Param_ButtonDialogType"
	int32 Param_RepOrConditionIndex = -1;    // depend of  "Param_ButtonDialogType"
	int32 Param_ConditionIndex = -1;   

	
	int32 Param_RepOrLinkOrConditionIndex = -1;       // depend of  "Param_ButtonDialogType"
	float Param_Visibility = 1.f;

	EVisibility ButtonHitted = EVisibility::Visible;   //Hidden   Visible
	EVisibility GetButtonHited() const {	return ButtonHitted; }

	FReply SendData();


	


/*
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
*/

};
