//FDialogParameter

#pragma once

#include "DialogParameter.generated.h"




UENUM()  //BlueprintType, Blueprintable
enum class EReplicRepeat : uint8
{
	once,
	after_once,
	always,
	back,
};

UENUM()  //BlueprintType, Blueprintable
enum class EResponseRepeat : uint8
{
	once,
	always,
};
UENUM()  //BlueprintType, Blueprintable
enum class EResponseReturn : uint8
{
	none,       // Onse, Afer_Onse
	exit,		//  !!!!!!!!!!!!!!!
	click_link_once,
	click_link_back,									 //  Return
	click_link_noreplic,						 // Return						(replic PASS)
	click_default_once,
	click_default_back,   // Onse, Afer_Onse
	click_default_noreplic,  // Onse, Afer_Onse									(replic PASS)
	pass_link_once,
	pass_link_back,											//  Return
	pass_link_noreplic,										//  Return			(replic PASS)
	pass_default_once,    // Onse, Afer_Onse
	pass_default_back,    // Onse, Afer_Onse
	pass_default_noreplic  // Onse, Afer_Onse									(replic PASS)
};





















USTRUCT(BlueprintType, Blueprintable)
struct FRepNode
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
		TArray<int32> IndexLocalVar;

};
 
USTRUCT(BlueprintType, Blueprintable)
struct FResponseNode
{
	GENERATED_USTRUCT_BODY()

	//UPROPERTY()
	///	TArray<FName> VarIndexOrName;
		//TArray<int32> IndexLocalVar;   XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXx
	//UPROPERTY()
	//	TArray<int32> IndexLocalVar_ToChange;  XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
	//UPROPERTY()
	//	TArray<FDLGVariable> DLGVariable_ToChange;
	UPROPERTY()
		bool IsRepeatOnce_Done = false;

};

USTRUCT(BlueprintType, Blueprintable)
struct FReplicNode
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
		TArray<int32> IndexLocalVar;
	//UPROPERTY()
	//	TArray<FDLGVariable> DLGVariable_Checking;

	UPROPERTY()
		TArray<FRepNode> RepNode;
};

USTRUCT(BlueprintType, Blueprintable)
struct FSpeechNode
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
		TArray<int32> IndexLocalVar;  


	UPROPERTY()
		FName Name;
	UPROPERTY()
		TArray<FReplicNode> ReplicNode;		 
	UPROPERTY()
		TArray<FResponseNode> ResponseNode;  
	UPROPERTY()
		bool IsRepeatOnce_Done = false;

};

USTRUCT(BlueprintType, Blueprintable)
struct FDialogNode
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
		FName Name;
	UPROPERTY()
		TArray<FSpeechNode> SpeechNode;
	
};

USTRUCT(BlueprintType, Blueprintable)
struct FDialogParameter
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
		bool isAlredyLoad = false;
	UPROPERTY()
		TArray<FString> MissingVariablesStr;
	UPROPERTY()
		TArray<FDialogNode> DialogNode;
};