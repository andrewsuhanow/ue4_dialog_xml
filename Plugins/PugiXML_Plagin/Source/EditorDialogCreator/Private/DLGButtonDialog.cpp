// Fill out your copyright notice in the Description page of Project Settings.




#include "DLGButtonDialog.h"
#include "SlateOptMacros.h"

#include "Widgets/Input/SButton.h"

//#include "widgets/SCanvas.h"
//#include "Widgets/Layout/SBorder.h"
//#include "Widgets/Overlay.h"
//#include "Widgets/SBoxPanel.h"   //  VerticalBox, HorisontalBox
//#include "Widgets/Images/SImage.h"


//#include "Kismet/GameplayStatics.h"

//#include "SMyWidget222.h"

#include "Rendering/DrawElements.h"   //+++++++++++++++++++++++++++





//#include "Engine/World.h"
#include "Blueprint/WidgetLayoutLibrary.h"


BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SDLGButtonDialog::Construct(const FArguments& InArgs)
{


	Delegate_OnDLGButtonDialogClicked = InArgs._OnDLGButtonDialogClicked;
	Param_ButtonDialogType = InArgs._ButtonDialogType.Get();
	Param_DialodIndex = InArgs._DialodIndex.Get();	
	Param_SpeechIndex = InArgs._SpeechIndex.Get(); //Param_SpeechIndex = (InArgs._SpeechIndex.Get() != -1) ? InArgs._SpeechIndex.Get() : -1;
	Param_ReplicOrResponseIndex = InArgs._ReplicOrResponseIndex.Get(); 
	Param_RepOrConditionIndex = InArgs._RepOrConditionIndex.Get();
	Param_ConditionIndex = InArgs._ConditionIndex.Get();


	Param_Visibility = InArgs._SetVisibility.Get() ? 1.f : 0.f;

	//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Green, FString::SanitizeFloat(ViewportSize.X));

	float a = 1.f;

	ChildSlot
	[
		SNew(SButton)
		.ContentPadding(0)
		//.ContentPadding(0)
		.ButtonColorAndOpacity(FLinearColor(1.f, 1.f, 1.f, Param_Visibility))
		.Visibility(this, &SDLGButtonDialog::GetButtonHited)
		.OnClicked(this, &SDLGButtonDialog::SendData)
	];
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION



    
FReply SDLGButtonDialog::SendData()
{

	//ButtonHitted = EVisibility::Hidden;

	//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Green, FString::SanitizeFloat(111222333));
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Green, "Propperty button is Used");

	Delegate_OnDLGButtonDialogClicked.Execute(Param_ButtonDialogType, Param_DialodIndex, Param_SpeechIndex, 
														Param_ReplicOrResponseIndex, Param_RepOrConditionIndex, Param_ConditionIndex);
	//Delegate_OnDLGButtonClicked.ExecuteIfBound(Param_ButtonType, Param_DialodTag);
	//Delegate_OnDLGButtonClicked.Brodcast(Param_ButtonType, Param_DialodTag);


	return FReply::Handled();
}








//void SDLGButtonDialog::Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime)
//{
//}




/*
int32 SSlBaseWidget::OnPaint(const FPaintArgs& Args,
							const FGeometry& AllottedGeometry,
							const FSlateRect& MyCullingRect,
							FSlateWindowElementList& OutDrawElements,
							int32 LayerId,
							const FWidgetStyle& InWidgetStyle,
							bool bParentEnabled) const
{

	LayerId = SCompoundWidget::OnPaint(Args, AllottedGeometry, MyCullingRect, OutDrawElements, LayerId, InWidgetStyle, bParentEnabled);

	
	

	//LayerId++;

	FVector2D LineStart(10, 10);
	TArray<FVector2D> LinePoints;
	TArray<FLinearColor> LineColors;
	//LinePoints.Add(LineStart);
	//LineColors.Add(FLinearColor::Red);
	//LinePoints.Add(LineStart + FVector2D(100.0f, 150.0f));
	//LinePoints.Add(LineStart + FVector2D(200.0f, 110.0f));
	//LinePoints.Add(LineStart + FVector2D(300.0f, 250.0f));
	//LinePoints.Add(LineStart + FVector2D(400.0f, 110.0f));


	LinePoints.Add(FVector2D(mousePos.X, mousePos.Y));
	LinePoints.Add(FVector2D(mousePos.X+1, mousePos.Y+1));


	FSlateDrawElement::MakeLines(
		OutDrawElements,
		LayerId,
		AllottedGeometry.ToPaintGeometry(),
		LinePoints,
		ESlateDrawEffect::None,
		FColor::Cyan,
		true,
		5.0f
	);






	//LinePoints.Empty();
	//LinePoints.Add(FVector2D(ViewportSize.X - GameInstance->MiniMapSize.X.X, 50));
	//LinePoints.Add(FVector2D(1 + ViewportSize.X - GameInstance->MiniMapSize.X.X, 50));

	//FSlateDrawElement::MakeLines(
	//	OutDrawElements,
	//	LayerId,
	//	AllottedGeometry.ToPaintGeometry(), //ToOffsetPaintGeometry(FVector2D(0, 10)),
	//	LinePoints,
	//	ESlateDrawEffect::None,
	//	FColor::Red,
	//	true,
	//	5.0f
	//);
	


return LayerId;
}
*/






