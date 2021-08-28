// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "DialogParameter.h"

#include "DLG_GlobalActor.h"

#include "DLG_DialogItem.generated.h"














UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PUGIXML_PLAGIN_API UDLG_DialogItem : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDLG_DialogItem();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

//public:	
	// Called every frame
	//virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;




public:

	UPROPERTY()
		UClass* BP_GLobalActorClass;


	
	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "DialogSystem")
		FString PathToFile = FString("Your dialog file.xml");                    //   PATH TO DIALOG.XML,   should de set in "DLGObjectCustomizationDetails.cpp"
	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "DialogSystem")
		FDialogParameter DialogParameter;
	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "DialogSystem")
		TArray<FName> LocalVariables;
	/*UPROPERTY()
		FString PathToFileRuntime = FString("none");*/

	UPROPERTY()
		FString XmlFileContent = FString("none");
	UPROPERTY()
		FString DefaultDialog = FString("DEFAULT");

	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "DialogSystem")
		class ADLG_GlobalActor* DLG_GlobalActor;
	//UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Dialog settings")
	//	TSubclassOf<class AGameMode> CurrentGameMod;

	  
	UFUNCTION(BlueprintCallable)
		void InitDialog();
	UFUNCTION(BlueprintCallable)
		void PlayDialog();









	//UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Dialog settings")
	//--	TSubclassOf< class static ADLG_GlobalActor>   fffffffff;
};
