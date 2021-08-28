// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


//#include "DLG_GlobalActor.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "DialogParameter.h"



#include "DLG_GlobalActor.generated.h"



/*
UENUM()   // BlueprintType, Blueprintable
enum class ETransitType : uint8
{
	//  condition 'DLG_PlayDialog' repeat
	StartDialog,
	//ContinueReplic,
	//BreakAfterResponse,
	//BackAfterResponse,

	//  check current playingMode
	//none,
	Once,
	AfterOnce,
	Back,
	Breack
}; 
*/
USTRUCT(BlueprintType, Blueprintable)
struct FReplicToDraw
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
		FString SpekerName = FString("None");
	UPROPERTY()
		FString ReplicTextStr = FString("...");
	UPROPERTY()
		FString SpekerImagePath = FString("none"); 
	UPROPERTY()
		FString SoundPath = FString("none");
	UPROPERTY()
		FString Time = FString("none");
	UPROPERTY()
		float Delay = 0;   //  Time waiting after
};
 
USTRUCT(BlueprintType, Blueprintable)
struct FResponseToDraw
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
		FString str = FString("...");
	UPROPERTY()
		FName LinkDialog = FName("DEFAULT");
	UPROPERTY()
		FName LinkSpeech = FName("DEFAULT");
	UPROPERTY()
		EResponseReturn ResponseReturn = EResponseReturn::none;

	UPROPERTY()
		TArray<FString> VariableToChange_LocalOrGlobal;
	UPROPERTY()
		TArray<FString> VariableToChange_Name;
	UPROPERTY()
		TArray<FString> VariableToChange_Value;
};


UCLASS()
class PUGIXML_PLAGIN_API ADLG_GlobalActor : public AActor
{
	GENERATED_BODY()
	





		//UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Dialog settings")
		//UTexture2D* TTTTTTTTTTT;



public:	
	// Sets default values for this actor's properties
	ADLG_GlobalActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:

	//   
	//UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Dialog settings")
	//	TMap<FName, FString> Avatar;

	UFUNCTION()
		void DLG_InitLocalVariables();
	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "DialogSystem")
		TArray<FName> LocalVariables;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "DialogSystem")
		TMap<FName, FName> GlobalVariable;
	UFUNCTION(BlueprintCallable, Category="DialogSystem")
		void SetGlobalVariablesMapRef(UPARAM(ref) TMap<FName, FName>& _GlobalVariable);
	UFUNCTION(BlueprintCallable, Category = "DialogSystem")
		void AddGlobalVar(FName _key, FName _value);
	UFUNCTION(BlueprintCallable, Category = "DialogSystem")
		FName GetGlobalVar(FName _key);
	//UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	//	void OnVariableSet(FName& key, FName& value);
		//void OnVariableSet(UPARAM(ref) FName& key, UPARAM(ref) FName& value);
		//void OnVariableSet_Implementation(UPARAM(ref) bool& Show, UPARAM(ref) FString& s);

	UPROPERTY()
		class UWDisplayDialog* DisplayDialog;
	UFUNCTION()
		void DLG_InitDialodWidget();
	//UFUNCTION()
	//	void DLG_GenerateDialog(FString &_LastDialog, FString &_LastSpeech, TArray<FString> &_Replic, 
	//							TArray<FString> &_Response, TArray<int32> &_ResponseIndex, bool isNew = false);

public:

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "DialogSystem")
		TSubclassOf<class UWDisplayDialog> DisplayDialog_BPClass;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "DialogSystem")
		bool Scrolling_dialog = true;
	

	//   =============  Dialog draw  ================
	UPROPERTY()
		AActor* ActorSpeker;
	//UPROPERTY()
		FString* XmlFilePath;
	//UPROPERTY()
		FDialogParameter* DialogParameter;
	
	UPROPERTY()
		TArray<FReplicToDraw> ReplicsToDraw;
	UPROPERTY()
		TArray<FResponseToDraw> ResponsesToDraw;

	UFUNCTION()
		void ChangeVariables(FResponseToDraw& _CurrentResponse);
	UFUNCTION()
		void DLG_StopDialog();
	UFUNCTION()
		void DLG_PlayDialog(AActor* _ActorSpeker, 
							FString& _XmlFilePath,
							FDialogParameter& _DialogParameter);

	UFUNCTION()
		void GenerateDialog(EResponseReturn ResponseReturn = EResponseReturn::none,
								FString _NextDialogNode = FString("DEFAULT"),
								FString _NextSpeechNode = FString("DEFAULT"));

	
	UFUNCTION()
		void OnResponseButtonClicked(FString& _XmlFileContent, FString _LastDialogNode, FString _LastSpeechNode, int32 _ResponseIndex);
	UFUNCTION()
		void ExitDialog();



	UPROPERTY(BlueprintReadWrite, Category = "DialogSystem")
		UAudioComponent* AudioComponent;
	UPROPERTY()
		class UInputComponent* DialogInputComponent;
	UPROPERTY()
		class UInputComponent* StoredInputComponent;
	UFUNCTION()
		void KeyMouseLeftDown();
	UFUNCTION()
		void KeySpace();
	UFUNCTION()
		void KeyEscape();



	//UPROPERTY()
	//	FString LastDialogNode_Global = FString("none");
	//UPROPERTY()
	//	FString LastSpeechNode_Global = FString("none");
//public:	
	// Called every frame
	//virtual void Tick(float DeltaTime) override;

};
