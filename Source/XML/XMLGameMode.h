// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"




#include "XMLGameMode.generated.h"

UCLASS(minimalapi)
class AXMLGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AXMLGameMode();

	virtual void BeginPlay() override;


public:

	//UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Dialog settings")
	//	class UDLG_GlobalComponent* DLG_GlobalComponent;
};



