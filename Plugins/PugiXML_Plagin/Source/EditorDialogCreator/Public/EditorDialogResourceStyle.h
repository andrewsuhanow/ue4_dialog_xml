// Fill out your copyright notice in the Description page of Project Settings.
///////////////// StyleSlate01Style
#pragma once

#include "CoreMinimal.h"
#include "Styling/SlateWidgetStyle.h"
#include "Styling/SlateWidgetStyleContainerBase.h"

#include "EditorDialogResourceStyle.generated.h"

/**
 * 
 */
USTRUCT()
struct FEditorDialogResourceStyle : public FSlateWidgetStyle  // SLATE1_API   // PUGIXML_PLAGIN_API
{
	GENERATED_USTRUCT_BODY()

	FEditorDialogResourceStyle();
	virtual ~FEditorDialogResourceStyle();

	// FSlateWidgetStyle
	virtual void GetResources(TArray<const FSlateBrush*>& OutBrushes) const override;
	static const FName TypeName;
	virtual const FName GetTypeName() const override { return TypeName; };
	static const FEditorDialogResourceStyle& GetDefault();


	//UPROPERTY(EditAnywhere, Category = "Current Patameter")
	//	FSlateBrush Image_01;
	//UPROPERTY(EditAnywhere, Category = "Current Patameter")
	//	FSlateBrush Image_02;
	UPROPERTY(EditAnywhere, Category = "Current Patameter")
		FSlateBrush ImageLayerActivate;
	UPROPERTY(EditAnywhere, Category = "Current Patameter")
		FSlateBrush ImageLayerDefault;
	UPROPERTY(EditAnywhere, Category = "Current Patameter")
		FSlateBrush TitleDialog;
	UPROPERTY(EditAnywhere, Category = "Current Patameter")
		FSlateBrush TitleDialogStart;
	UPROPERTY(EditAnywhere, Category = "Current Patameter")
		FSlateBrush TitleDialogEnd;
	UPROPERTY(EditAnywhere, Category = "Current Patameter")
		FSlateBrush ImageButtonSectionRollUp;
	UPROPERTY(EditAnywhere, Category = "Current Patameter")
		FSlateBrush ImageButtonSectionExpand;
	UPROPERTY(EditAnywhere, Category = "Current Patameter")
		FSlateBrush PropertyDialog;
	UPROPERTY(EditAnywhere, Category = "Current Patameter")
		FSlateBrush PropertyDialogStart;
	UPROPERTY(EditAnywhere, Category = "Current Patameter")
		FSlateBrush PropertyDialogEnd;
	UPROPERTY(EditAnywhere, Category = "Current Patameter")
		FSlateBrush Condition;
	UPROPERTY(EditAnywhere, Category = "Current Patameter")
		FSlateBrush ConditionStart;
	UPROPERTY(EditAnywhere, Category = "Current Patameter")
		FSlateBrush ConditionEnd;
	UPROPERTY(EditAnywhere, Category = "Current Patameter")
		FSlateBrush ImageValueZone;
	UPROPERTY(EditAnywhere, Category = "Current Patameter")
		FSlateBrush ImageAddElement;
	//UPROPERTY(EditAnywhere, Category = "Current Patameter")
	//	FSlateBrush ImageRemoveElement;
	UPROPERTY(EditAnywhere, Category = "Current Patameter")
		FSlateBrush ImageMoveElement;
	UPROPERTY(EditAnywhere, Category = "Current Patameter")
		FSlateBrush SpekersImageDefault;
	UPROPERTY(EditAnywhere, Category = "Current Patameter")
		FSlateBrush ImageDeleteElement;
	UPROPERTY(EditAnywhere, Category = "Current Patameter")
		FSlateBrush ImageAddSoundElement;
	UPROPERTY(EditAnywhere, Category = "Current Patameter")
		FSlateBrush ImageConditionButtonOn;
	UPROPERTY(EditAnywhere, Category = "Current Patameter")
		FSlateBrush ImageConditionButtonOFF;
	UPROPERTY(EditAnywhere, Category = "Current Patameter")
		FSlateBrush TitleReplic;
	UPROPERTY(EditAnywhere, Category = "Current Patameter")
		FSlateBrush TitleReplicStart;
	UPROPERTY(EditAnywhere, Category = "Current Patameter")
		FSlateBrush TitleReplicEnd;
	UPROPERTY(EditAnywhere, Category = "Current Patameter")
		FSlateBrush TitleResponse;
	UPROPERTY(EditAnywhere, Category = "Current Patameter")
		FSlateBrush TitleResponseStart;
	UPROPERTY(EditAnywhere, Category = "Current Patameter")
		FSlateBrush TitleResponseEnd;
	UPROPERTY(EditAnywhere, Category = "Current Patameter")
		FSlateBrush PropertyReplic;
	UPROPERTY(EditAnywhere, Category = "Current Patameter")
		FSlateBrush PropertyReplicStart;
	UPROPERTY(EditAnywhere, Category = "Current Patameter")
		FSlateBrush PropertyReplicEnd;
	UPROPERTY(EditAnywhere, Category = "Current Patameter")
		FSlateBrush PropertyResponse;
	UPROPERTY(EditAnywhere, Category = "Current Patameter")
		FSlateBrush PropertyResponseStart;
	UPROPERTY(EditAnywhere, Category = "Current Patameter")
		FSlateBrush PropertyResponseEnd;
	UPROPERTY(EditAnywhere, Category = "Current Patameter")
		FSlateBrush ImageVariableButtonOn;
	UPROPERTY(EditAnywhere, Category = "Current Patameter")
		FSlateBrush ImageVariableButtonOff;
	UPROPERTY(EditAnywhere, Category = "Current Patameter")
		FSlateBrush PlaySound;

};

/**
 */
UCLASS(hidecategories=Object, MinimalAPI)
class UStyleEditorDialogResourceStyle : public USlateWidgetStyleContainerBase
{
	GENERATED_BODY()

public:
	/** The actual data describing the widget appearance. */
	UPROPERTY(Category=Appearance, EditAnywhere, meta=(ShowOnlyInnerProperties))
	FEditorDialogResourceStyle WidgetStyle;

	virtual const struct FSlateWidgetStyle* const GetStyle() const override
	{
		return static_cast< const struct FSlateWidgetStyle* >( &WidgetStyle );
	}
};
