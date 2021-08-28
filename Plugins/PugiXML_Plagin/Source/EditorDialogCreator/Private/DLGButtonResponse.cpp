// Fill out your copyright notice in the Description page of Project Settings.




#include "DLGButtonResponse.h"
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
void SDLGButtonResponse::Construct(const FArguments& InArgs)
{


	Delegate_OnDLGButtonResponseClicked = InArgs._OnDLGButtonResponseClicked;
	Param_ButtonResponseType = InArgs._ButtonResponseType.Get();
	Param_DialodTag = InArgs._DialodTag.Get();

	//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Green, FString::SanitizeFloat(ViewportSize.X));

	ChildSlot
	[
		SNew(SButton)
		.OnClicked(this, &SDLGButtonResponse::SendData)
	];
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION




FReply SDLGButtonResponse::SendData()
{
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Green, FString::SanitizeFloat(111222333));

	Delegate_OnDLGButtonResponseClicked.Execute(Param_ButtonResponseType, Param_DialodTag);
	//Delegate_OnDLGButtonClicked.ExecuteIfBound(Param_ButtonType, Param_DialodTag);
	//Delegate_OnDLGButtonClicked.Brodcast(Param_ButtonType, Param_DialodTag);


	return FReply::Handled();
}








//void SDLGButtonResponse::Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime)
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






