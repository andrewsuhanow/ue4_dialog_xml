// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "DLG_GlobalActor.h"

#include "WDisplayDialog.generated.h"



//class UOverlay;
class UImage;
class UBorder;
class UVerticalBox;
class UHorizontalBox;
class USizeBox;
class UScrollBox;
class UTextBlock;
class UWResponseButton;



UCLASS()
class PUGIXML_PLAGIN_API UWDisplayDialog : public UUserWidget
{
	GENERATED_BODY()
	

public:

	virtual void NativeConstruct() override;

protected:

	//UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	//	UOverlay* OverlayForBar;

	//UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	//	UVerticalBox* DialogPhrase_VerticalBox;



	//   ------------ Replics -------------
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
		UScrollBox* ReplicsScrollBox;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
		UBorder* ReplicBorder;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
		USizeBox* ReplicSizeBox;
//	UPROPERTY()
//		TArray<UVerticalBox*> FullReplicsBySpeker;
	UPROPERTY()
		TArray<UHorizontalBox*> ReplicsHorizontalBoxText;
	//UPROPERTY()
	//	int32 TextStringsNum = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
		UImage* CurrentSpikerImage;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
		UTextBlock* CurrentSpekerName;
	UPROPERTY()
		TArray<UTextBlock*> AllSpekersName;
	//UPROPERTY()
	//	bool doOffsetReplicScroll = true;
	//UPROPERTY()
	//	float SctollOffset = 0;
		//bool IsNewSpekerIsOld = false;
//	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
//		TArray<UTextBlock*> ReplicsText;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "DialogSystem")
		float TextSize = 32.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "DialogSystem")
		float CurrentSpikerImageSize = 50.f;
	UPROPERTY()
		USizeBox* BorderPaddingUnder;
	UPROPERTY()
		FString CurrentSpekerImage_Path = FString("none");
	UPROPERTY()
		FString CurrentSpekerNameStr = FString("none");
	///	TArray <UBorder*> TextBorder;
	///UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Dialog (Read only)")
	///	TArray<FString> Replic;


	//   ------------ Response ------------
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
		UBorder* ResponseBorder;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
		UScrollBox* ResponseScrollBox;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<UWResponseButton> ResponseButtonClassBP;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
		TArray<UWResponseButton*> ResponseButton;
	//	TArray<UButton*> ResponseButton;
	//UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	//	TArray<UTextBlock*> ResponseText;

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Dialog (Read only)")
	//	TArray<FString> Response;


public:

	//   ------------ Use ------------

	UFUNCTION()
		void ShowDialogPanel();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Dialog (Read only)")
		bool iSDialogInProgress = false;
	UFUNCTION()
		void DrawDialog(TArray<FReplicToDraw> &_ReplicToDraw, 
						TArray<FResponseToDraw> &_ResponseToDraw);
	UFUNCTION()
		void StopDialog();

	UFUNCTION()
		void KeyMouseLeftDown();
	UFUNCTION()
		void KeySpace();
	UFUNCTION()
		void KeyEscape();

	//UPROPERTY()
		TArray<FReplicToDraw> *ReplicToDraw;
	//UPROPERTY()
		TArray<FResponseToDraw> *ResponseToDraw;

	UPROPERTY()
		FTimerHandle TimerHandle_ReplicDelay;
	UFUNCTION()
		void ReplicDelay();   // 7777777777777777777
	UPROPERTY()
		float ReplicDelayTime = -1;
	//  ---  init parrams  ---
	UFUNCTION()
		void ParamsInit();
	UPROPERTY()
		FVector2D ReplicPanelSize = FVector2D(0,0);
	UPROPERTY()
		FTimerHandle TimerHandle_ParamsInit;



	//UFUNCTION(BlueprintImplementableEvent)  
	//	void OnShowReplicPanel();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void OnShowReplicPanel(UPARAM(ref) bool& Show, UPARAM(ref) FString& s);
		void OnShowReplicPanel_Implementation(UPARAM(ref) bool& Show, UPARAM(ref) FString& s);
	UFUNCTION(BlueprintCallable)
		void ShowReplicPanel(bool Show = true);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void OnShowResponsePanel(UPARAM(ref) bool& Show, UPARAM(ref) FString& s);
		void OnShowResponsePanel_Implementation(UPARAM(ref) bool& Show, UPARAM(ref) FString& s);
	UFUNCTION(BlueprintCallable)
		void ShowResponsePanel(bool Show = true);
	
	
	//UFUNCTION()
	//	void DrawReplicPrepare();
	//UFUNCTION()
	//	void DrawResponsePrepare();


	
/*


	//UFUNCTION()
		//+++++++++++++++++++++++++++++++++++
	//	void DrawReplic(FString& XmlFileContent, FString& _LastDialog, FString& _LastSpeech,
	//										FString& _Replic, float _SoundDelay, ETransitType _TransitTypePlayingCategory);
	UFUNCTION()
		void DrawResponse(FString& _XmlFileContent, FString& _LastDialog, FString& _LastSpeech, 
											TArray<FString>& _Response, TArray<int32>& _ResponseIndex);


*/
	
public:

	//   --------  Base parameter  ---------
	UFUNCTION()
		void Init(ADLG_GlobalActor* _GlobagDialogActorRef, bool _Scrolling_dialog);
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Dialog (Read only)")
		bool Scrolling_dialog;

	//++++++++++++void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public:

	//   --------  for CallBack with DLG_GlobalActor  ---------
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Dialog (Read only)")
		ADLG_GlobalActor* GlobagDialogActorRef = nullptr;
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Dialog (Read only)")
	//	FString LastDialog; 
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Dialog (Read only)")
	//	FString LastSpeech;
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Dialog (Read only)")
	//	FString Replic; 
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Dialog (Read only)")
	//	float SoundDelay;

	//FString* XmlFileContent;


	//	bool aaa = true;
};
