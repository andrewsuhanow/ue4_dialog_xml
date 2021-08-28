// Copyright Epic Games, Inc. All Rights Reserved.

#include "XMLGameMode.h"
#include "XMLCharacter.h"



#include "UObject/ConstructorHelpers.h"


//#include "DLG_GlobalComponent.h"   //  DLG   77777777777777




AXMLGameMode::AXMLGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}


	//DLG_GlobalComponent = CreateDefaultSubobject<UDLG_GlobalComponent>("DLG_GlobalComponent");


}


void AXMLGameMode::BeginPlay()
{
	Super::BeginPlay();

	
}



