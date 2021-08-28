// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
 

#include "Widgets/SCompoundWidget.h"




UENUM()  //BlueprintType, Blueprintable
enum class EButtonConditionType : uint8
{
	AddNewDialogUp,
	AddNewDialogDown,
	DiallogName
};



DECLARE_DELEGATE_TwoParams(FDLGButtonConditionClicked, EButtonConditionType, int32);


class SDLGButtonCondition : public SCompoundWidget  //SLATE1_API  // PUGIXML_PLAGIN_API
{
public:
	SLATE_BEGIN_ARGS(SDLGButtonCondition)
	{}
		//SLATE_ARGUMENT()
		SLATE_EVENT(FDLGButtonConditionClicked, OnDLGButtonConditionClicked)
		SLATE_ATTRIBUTE(EButtonConditionType, ButtonConditionType)
		SLATE_ATTRIBUTE(int32, DialodTag)
		//SLATE_EVENT()
	SLATE_END_ARGS()

	

	
	void Construct(const FArguments& InArgs);

	//virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;
	


	//   Stored function whith this DLG_Button exequte
	FDLGButtonConditionClicked Delegate_OnDLGButtonConditionClicked;

	EButtonConditionType Param_ButtonConditionType;
	int32 Param_DialodTag = -1;

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
