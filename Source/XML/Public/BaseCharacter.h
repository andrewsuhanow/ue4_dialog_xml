// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

//#include "DLG_DialogItem.h"      		//  7777777777777777777

#include "BaseCharacter.generated.h"

UCLASS()
class XML_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:



	//UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "DLG")
	//	UDLG_DialogItem* DialogItemComponent;

public:
	// Sets default values for this character's properties
	ABaseCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
