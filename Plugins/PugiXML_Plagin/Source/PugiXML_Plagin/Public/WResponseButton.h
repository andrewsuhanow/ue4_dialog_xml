// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// #include "WResponseButton.h"

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "DLG_GlobalActor.h"

#include "WResponseButton.generated.h"

class UButton;
class UTextBlock;


UCLASS()
class PUGIXML_PLAGIN_API UWResponseButton : public UUserWidget
{
	GENERATED_BODY()

//public:
//	DECLARE_DELEGATE_TwoParam(FActionButtonDelegate, int32, int32);    //   Только одного подписать
//	FActionButtonDelegate ActionButtonClicked;


//public:

	//UWResponseButton(const FObjectInitializer& ObjectInitializer);

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PROJ_MAIN_Parrameter")
		FButtonStyle ButtonStyle;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PROJ_MAIN_Parrameter")
		FLinearColor ButtobColor_Normal = FLinearColor(0.25f, 0.25f, 0.15f);
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PROJ_MAIN_Parrameter")
		FLinearColor ButtobColor_Hovered = FLinearColor(0.35f, 0.35f, 0.0f);    // FLinearColor(0.3f, 0.3f, 0.1f);
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PROJ_MAIN_Parrameter")
		FLinearColor ButtobColor_Pressed = FLinearColor(0.8f, 0.8f, 0.0f);
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PROJ_MAIN_Parrameter")
		FLinearColor ButtobColor_Disabled = FLinearColor(0.35f, 0.3f, 0.32f);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PROJ_MAIN_Parrameter")
		FLinearColor ButtobColor_ActivatedHold = FLinearColor(0.9f, 1.0f, 0.1f);
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PROJ_MAIN_Parrameter")
		FLinearColor ButtobColor_ActivatedHold_Hovered = FLinearColor(0.4f, 0.4f, 0.03f);
	//UFUNCTION()
	//	void SatAsActivateHold(bool State);


public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		UButton* ResponseButton;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		UTextBlock* ResponseText;
	
	
	virtual void NativeConstruct() override;

	UPROPERTY()
		ADLG_GlobalActor* GlobagDialogActorRef = nullptr;

	FResponseToDraw *CurrentResponse;

	UFUNCTION()
		void init(class ADLG_GlobalActor*& _GlobagDialogActorRef, FResponseToDraw &_CurrentResponse);
	UFUNCTION()
		void OnClick();

};
