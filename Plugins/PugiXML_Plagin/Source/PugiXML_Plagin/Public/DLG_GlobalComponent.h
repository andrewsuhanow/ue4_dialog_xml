// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "DLG_GlobalComponent.generated.h"

/**
 * 
 */
UCLASS()
class PUGIXML_PLAGIN_API UDLG_GlobalComponent : public UObject
{
	GENERATED_BODY()


public:



	UDLG_GlobalComponent();

	UFUNCTION()
		void DLG_PlayDialog();
	
};
