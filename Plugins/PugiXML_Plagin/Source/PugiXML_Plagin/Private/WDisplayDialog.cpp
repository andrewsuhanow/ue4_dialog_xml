// Fill out your copyright notice in the Description page of Project Settings.


#include "WDisplayDialog.h"


#include "Blueprint/WidgetTree.h"

#include "Components/TextBlock.h"
//#include "Components/Overlay.h"
#include "Components/Border.h"
#include "Components/SizeBox.h"
#include "Components/VerticalBox.h"
#include "Components/HorizontalBox.h"
#include "Components/ScrollBox.h"
#include "Components/Image.h"

#include "WResponseButton.h"    //#include "Components/Button.h"





void UWDisplayDialog::NativeConstruct()
{
	Super::NativeConstruct();
	
	//    TEST
	/*for (int32 i = 0; i < 20; i++)
	{
		UTextBlock* ttt = WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass());
		///UTextBlock* ttt = ConstructObject<UTextBlock>(UTextBlock::StaticClass(), this);
		ttt->SetText(FText::FromString(TEXT("Default Tex")));
		ReplicsScrollBox->AddChild(ttt);
		ReplicsText.Add(ttt);
	}*/


	//FVector2D ReplicPanelSize = ReplicBorder->GetCachedGeometry().GetLocalSize();  //  All replic zone size
	//UE_LOG(LogTemp, Warning, TEXT("sxxxxx = '%f'"), ReplicPanelSize.X);
}

/*
void UWDisplayDialog::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	
	if (ReplicDelayTime > 0)
	{
		ReplicDelayTime -= InDeltaTime;
	}
	else if ( ReplicDelayTime > -1 )
	{
		ReplicDelayTime = -1;
		DrawDialog(*ReplicToDraw, *ResponseToDraw);
	}

	//if (doOffsetReplicScroll)
	//{
		//ReplicsScrollBox->ScrollToEnd();
	//}
}*/


void UWDisplayDialog::Init(ADLG_GlobalActor* _GlobagDialogActorRef, bool _Scrolling_dialog)
{
	GlobagDialogActorRef = _GlobagDialogActorRef;
	Scrolling_dialog = _Scrolling_dialog;


	ShowReplicPanel(false);
	ShowResponsePanel(false);
}

void UWDisplayDialog::ParamsInit()
{
	ReplicPanelSize = ReplicBorder->GetCachedGeometry().GetLocalSize();  //  All replic zone size
	if (ReplicPanelSize.X != 0)
	{
		GetWorld()->GetTimerManager().ClearTimer(TimerHandle_ParamsInit);
		DrawDialog(*ReplicToDraw, *ResponseToDraw);
	}
}


void UWDisplayDialog::ShowDialogPanel()
{
	ShowReplicPanel(true); 
	ShowResponsePanel(true);
}


void UWDisplayDialog::DrawDialog(TArray<FReplicToDraw>& _ReplicToDraw,
								TArray<FResponseToDraw>& _ResponseToDraw)
{

	ReplicToDraw = &_ReplicToDraw;
	ResponseToDraw = &_ResponseToDraw;



	
	if (ReplicPanelSize.X == 0) 
	{
		GetWorld()->GetTimerManager().SetTimer(TimerHandle_ParamsInit, this, &UWDisplayDialog::ParamsInit, 0.2, true);
		return;
	}


	// Clear Response Panel
	while (ResponseButton.Num() > 0)
	{
			ResponseButton[0]->RemoveFromParent();
			ResponseButton.RemoveAt(0);
	}
	
	// Clear Replic Panel           //   if SCLOLLING == true
	//while (ReplicsText.Num() > 0)
	//{
	//	ReplicsText[0]->RemoveFromParent();
	//	ReplicsText.RemoveAt(0);
	//}





	

	if ((*ReplicToDraw).Num() > 0)
	{

		//  --------  Spacer under Current Text   ------------
		if (BorderPaddingUnder) BorderPaddingUnder->RemoveFromParent();




		//  --------  New Speker's name and image  --------
		if (CurrentSpekerNameStr != (*ReplicToDraw)[0].SpekerName &&
			CurrentSpekerImage_Path != (*ReplicToDraw)[0].SpekerImagePath)
		{
			//IsNewSpekerIsOld = true;
			CurrentSpekerNameStr = (*ReplicToDraw)[0].SpekerName;
			CurrentSpekerName->SetText(FText::FromString((*ReplicToDraw)[0].SpekerName));
			CurrentSpekerName->SetFont(FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Regular.ttf"), TextSize * 1.5f));

			//---  Draw Empty stting     ///////////// ???????????????? NEED  ADD  Padding insted   ??????????????????????????????
			if (ReplicsScrollBox->GetChildrenCount() != 0)
			{
				UHorizontalBox* ReplicsHorizontalBoxTextTMP_ = WidgetTree->ConstructWidget<UHorizontalBox>(UHorizontalBox::StaticClass());
				ReplicsHorizontalBoxText.Add(ReplicsHorizontalBoxTextTMP_);
				UTextBlock* ReplicTextTMP_ = WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass());
				ReplicTextTMP_->SetText(FText::FromString(FString(" ")));
				ReplicsHorizontalBoxText.Last()->AddChildToHorizontalBox(ReplicTextTMP_);
				ReplicsScrollBox->AddChild(ReplicsHorizontalBoxText.Last());
			}
			//---  Draw Name
			UHorizontalBox* ReplicsHorizontalBoxTextTMP = WidgetTree->ConstructWidget<UHorizontalBox>(UHorizontalBox::StaticClass());
			ReplicsHorizontalBoxText.Add(ReplicsHorizontalBoxTextTMP);
			UTextBlock* SpekerNameinReplic = WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass());
			SpekerNameinReplic->SetFont(FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Regular.ttf"), TextSize * 1.3f));
			SpekerNameinReplic->SetText(FText::FromString(CurrentSpekerNameStr));
			ReplicsHorizontalBoxText.Last()->AddChildToHorizontalBox(SpekerNameinReplic);
			ReplicsScrollBox->AddChild(ReplicsHorizontalBoxText.Last());

			//--- image
			CurrentSpekerImage_Path = (*ReplicToDraw)[0].SpekerImagePath;
			UTexture2D* SpekerTexture = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), 
														NULL, *((*ReplicToDraw)[0].SpekerImagePath)));
			CurrentSpikerImage->SetBrushFromTexture(SpekerTexture, false);
		}
		//  ------------ 
		
			
		
		


		//  ================  My ParseToArray() (with additional "space" and "\n") =================
		// (*ReplicToDraw)[0].ReplicTextStr.ParseIntoArray(TextStringArray, TEXT(" "), true); // Breack text
		TArray<FString> TextStringArray;
		int32 Space_Symbol = (*ReplicToDraw)[0].ReplicTextStr.Find(" ",
						ESearchCase::Type::IgnoreCase, ESearchDir::Type::FromStart, 0);
		int32 startMid = 0;
		while (Space_Symbol != -1)
		{		
			int32 CoundMid = Space_Symbol - startMid;
			TextStringArray.Add((*ReplicToDraw)[0].ReplicTextStr.Mid(startMid, CoundMid));
			//--- check if last Added element has "\n"	
				{int32 n_Symbol = TextStringArray.Last().Find("\n",
									ESearchCase::Type::IgnoreCase, ESearchDir::Type::FromStart, 0);
				while (n_Symbol != -1)
				{
					FString StrTMP = TextStringArray.Last();
					if (StrTMP == FString("\n")) break;
					TextStringArray.Last() = StrTMP.Mid(0, n_Symbol);
					TextStringArray.Add(FString("\n"));
					if (StrTMP.Len() > n_Symbol + 1)
					{
						TextStringArray.Add(StrTMP.Mid(n_Symbol + 1, StrTMP.Len() - n_Symbol + 1));
					}
					n_Symbol = TextStringArray.Last().Find("\n",
								ESearchCase::Type::IgnoreCase, ESearchDir::Type::FromStart, 0);
				}}
			//--- check If more then one "space" forward
			int32 TMP = Space_Symbol;
			startMid = Space_Symbol;
			Space_Symbol = (*ReplicToDraw)[0].ReplicTextStr.Find(" ",
				ESearchCase::Type::IgnoreCase, ESearchDir::Type::FromStart, ++Space_Symbol);
			
			while (Space_Symbol != -1 && Space_Symbol - TMP == 1)
			{
				TMP = Space_Symbol;
				Space_Symbol = (*ReplicToDraw)[0].ReplicTextStr.Find(" ",
						ESearchCase::Type::IgnoreCase, ESearchDir::Type::FromStart, ++Space_Symbol);
			}
		}
		//--- Add last element (if exist)
		int32 Lenght = (*ReplicToDraw)[0].ReplicTextStr.Len();
		int32 CoundMid = Lenght - startMid;
		if (CoundMid > 0)
		{
			TextStringArray.Add((*ReplicToDraw)[0].ReplicTextStr.Mid(startMid, CoundMid));
		}
		//---    DELETE   "\n"-String
		for (int32 nSumbol = 0; nSumbol < TextStringArray.Num(); nSumbol++)
		{
			if (TextStringArray[nSumbol] == FString("\n"))
			{
				TextStringArray.RemoveAt(nSumbol);
				nSumbol--;
			}
		}
		//-----------------------------------



		//  ================= Form Vertical and Horisontal BoxStringsArray from FStringArray  =================
		float CurrentReplicSizeY = 0;  // diallog Text UnderOffset
		bool isNeedNewRow = true;
		FString AllNewString = FString("");
		for (int32 i = 0; i < TextStringArray.Num(); i++)
		{
			//---  New  UTextBlock
			UTextBlock* ReplicTextTMP = WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass());
			ReplicTextTMP->SetFont(FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Regular.ttf"), TextSize));

			FString StringTMP = TextStringArray[i];
			
			if (StringTMP == FString("\n") || isNeedNewRow )
			{
				//--- add previous HorizontalBox to VertialBox  
				if (ReplicsHorizontalBoxText.Num() > 0 && ReplicsHorizontalBoxText.Last()->GetChildrenCount() > 0 && i != 0)
				{
					ReplicsScrollBox->AddChild(ReplicsHorizontalBoxText.Last());
				}
				//--- create new HorizontalBox ~~ NewStringLine
				UHorizontalBox* ReplicsHorizontalBoxTextTMP = WidgetTree->ConstructWidget<UHorizontalBox>(UHorizontalBox::StaticClass());
				ReplicsHorizontalBoxText.Add(ReplicsHorizontalBoxTextTMP);
				AllNewString = FString("");
				isNeedNewRow = false;

				//---  Get Text Height for forming BottomPadding in ReplicScrollBox
				TSharedRef<FSlateFontMeasure> WFontSize_TMP = (FSlateApplication::Get().GetRenderer()->GetFontMeasureService());
				FVector2D FontSizeTMP = WFontSize_TMP->Measure(AllNewString, ReplicTextTMP->Font);
				CurrentReplicSizeY += FontSizeTMP.Y;
			}
			AllNewString += StringTMP;   //  "AllNewString" -- need for check text Horizontal size in one line

			//---  Get Text size
			TSharedRef<FSlateFontMeasure> PaddingUnder = (FSlateApplication::Get().GetRenderer()->GetFontMeasureService());
			FVector2D TextSizeTMP = PaddingUnder->Measure(AllNewString, ReplicTextTMP->Font);

			//--  if string with next word fit in cutrrent string =>> add it
			if (TextSizeTMP.X < ReplicPanelSize.X - TextSize/5)
			{
				if (StringTMP != FString("\n")) {
					ReplicTextTMP->SetText(FText::FromString(StringTMP));
					ReplicsHorizontalBoxText.Last()->AddChildToHorizontalBox(ReplicTextTMP);
				}
			}
			//--- else create new string
			else
			{
				isNeedNewRow = true;
				i--;                // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!       ERROR when Wery long WORD
			}				       //    !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!  !!!!!!!!!!!!!!!!!	
		}
		ReplicsScrollBox->AddChild(ReplicsHorizontalBoxText.Last());

		
			
	
		if (ReplicPanelSize.Y > CurrentReplicSizeY)
		{
			//---  Bottom offset in ReplicScrollBox  ------------
			float newScrollOffset = ReplicPanelSize.Y - CurrentReplicSizeY;
			BorderPaddingUnder = WidgetTree->ConstructWidget<USizeBox>(USizeBox::StaticClass());;
			BorderPaddingUnder->SetHeightOverride(newScrollOffset - TextSize / 2.3f);
			ReplicsScrollBox->AddChild(BorderPaddingUnder);
			ReplicsScrollBox->ScrollToEnd();
		}
		else
		{
			//ReplicsScrollBox->ScrollToEnd();
			//float FullOffset = ReplicsScrollBox->GetScrollOffset();
			//float lastOffset = CurrentReplicSizeY - ReplicPanelSize.Y;
			////SctollOffset = FullOffset - lastOffset;
			//--ReplicsScrollBox->ScrollToStart();
			//--ReplicsScrollBox->SetScrollOffset(-50);
		}
		//----------------------------------------------
	  

		//===   Set time Delay
		float time = FCString::Atof(*(*ReplicToDraw)[0].Time);
		ReplicDelayTime = time + (*ReplicToDraw)[0].Delay;
		GetWorld()->GetTimerManager().SetTimer(TimerHandle_ReplicDelay, this, &UWDisplayDialog::ReplicDelay, time, false);


		//UTextBlock* ReplicTextTMP = WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass());
		//ReplicTextTMP->SetAutoWrapText(true);  //   7777777777777777
		////--Cast<TSharedPtr<STextBlock>>(sTextBlock)->SetWrappingPolicy(ETextWrappingPolicy::AllowPerCharacterWrapping);
		////--ReplicTextTMP->SetWrappingPolicy(ETextWrappingPolicy::AllowPerCharacterWrapping);  //
		//ReplicTextTMP->SetText(FText::FromString((*ReplicToDraw)[0].ReplicTextStr));

		////++TSharedPtr<SWidget> sTextBlock = ReplicTextTMP->TakeWidget();
		//
		////  ----   Calculate Size Under  ----
		//FVector2D ReplicPanelSize = ReplicBorder->GetCachedGeometry().GetLocalSize();
		////FVector2D ReplicPanelSize = ReplicBorder->GetCachedGeometry().LocalToAbsolute(ReplicBorder->GetCachedGeometry().GetLocalSize());
		////FVector2D ReplicPanelSize = ReplicSizeBox->HeightOverride;
		//
	
		//UE_LOG(LogTemp, Warning, TEXT("Rep-panet = '%f'"), ReplicPanelSize.Y);
		//UE_LOG(LogTemp, Warning, TEXT("Text = '%f'"), TextSizeTMP.Y);
		//UE_LOG(LogTemp, Warning, TEXT("Text = '%f'"), BorderPaddingUnder_Size);
		///UE_LOG(LogTemp, Warning, TEXT("size = '%f'   '%f'"), Size2D.X, Size2D.Y);




		(*ReplicToDraw).RemoveAt(0);

		ReplicsScrollBox->ScrollToEnd();
		return;
	}
	 



	//  Draw Response Panel
	if ((*ResponseToDraw).Num() > 0)
	{
		for (int32 i = 0; i < (*ResponseToDraw).Num(); i++)
		{
			if (ResponseButtonClassBP && GlobagDialogActorRef)  
			{
				//  ------------    Check if has Response with ReturnParrameter "Pass"   --------------
				if ((*ResponseToDraw)[i].ResponseReturn == EResponseReturn::pass_link_once ||
					(*ResponseToDraw)[i].ResponseReturn == EResponseReturn::pass_link_back ||
					(*ResponseToDraw)[i].ResponseReturn == EResponseReturn::pass_link_noreplic ||
					(*ResponseToDraw)[i].ResponseReturn == EResponseReturn::pass_default_once ||
					(*ResponseToDraw)[i].ResponseReturn == EResponseReturn::pass_default_back ||
					(*ResponseToDraw)[i].ResponseReturn == EResponseReturn::pass_default_noreplic )
				{
					GlobagDialogActorRef->ChangeVariables((*ResponseToDraw)[i]);

					//  ------------    if just one Response    --------------  ==>  AutoTransfer
					if ((*ResponseToDraw).Num() == 1)
					{
						GlobagDialogActorRef->GenerateDialog((*ResponseToDraw)[i].ResponseReturn,
							(*ResponseToDraw)[i].LinkDialog.ToString(),
							(*ResponseToDraw)[i].LinkSpeech.ToString());
							return;
					}
					else   //==> Spend this Response
					{
						continue;
					}

				}

				 
				// ====================     Draw Response     =====================
				UWResponseButton* ResponseBtnTMP = CreateWidget<UWResponseButton>(this, ResponseButtonClassBP);
				///UWResponseButton* ResponseBtnTMP = WidgetTree->ConstructWidget<UWResponseButton>(UWResponseButton::StaticClass());
				ResponseBtnTMP->init(GlobagDialogActorRef, (*ResponseToDraw)[i]);
				ResponseButton.Add(ResponseBtnTMP);   

				//++              777777777777777777777777777777              MABE DON'T ADD TO SCROLL
				ResponseScrollBox->AddChild(ResponseBtnTMP);   
			}
		}
	}
	else
	{
		//   -------   EXIT Dialog  ----------
		StopDialog();
	}
}

void UWDisplayDialog::ReplicDelay()
{
	

	DrawDialog(*ReplicToDraw, *ResponseToDraw);

	//DrawDialog(TArray<FReplicToDraw> & _ReplicToDraw,
	//	TArray<FResponseToDraw> & _ResponseToDraw)

	//if (GlobagDialogActorRef)
	//{
		//++++++++++
		//GlobagDialogActorRef->DLG_PlayDialog(*XmlFileContent, TransitType, LastDialog, LastSpeech);
	//}
}

void UWDisplayDialog::StopDialog()
{
	//doOffsetReplicScroll = false;

	// Clear Response Panel
	while (ResponseButton.Num() > 0)
	{
		ResponseButton[0]->RemoveFromParent();
		ResponseButton.RemoveAt(0);
	}

	//++++++++ Clear Replic Panel          
	/*while (ReplicsText.Num() > 0)
	{
		ReplicsText[0]->RemoveFromParent();
		ReplicsText.RemoveAt(0);
	}*/

	ShowReplicPanel(false);
	ShowResponsePanel(false);	
}



// ------  Space =>>  Next Replic  ------
void UWDisplayDialog::KeyMouseLeftDown()
{
	if (GetWorld()->GetTimerManager().IsTimerActive(TimerHandle_ReplicDelay))
	{
		GetWorld()->GetTimerManager().ClearTimer(TimerHandle_ReplicDelay);
		DrawDialog(*ReplicToDraw, *ResponseToDraw);		
	}
}
// ------  Space =>>  Next Replic  ------
void UWDisplayDialog::KeySpace()
{
	if (GetWorld()->GetTimerManager().IsTimerActive(TimerHandle_ReplicDelay))
	{
		GetWorld()->GetTimerManager().ClearTimer(TimerHandle_ReplicDelay);
		DrawDialog(*ReplicToDraw, *ResponseToDraw);		
	}
}

// ------  Escape =>>  Exit Dialog  ------
void UWDisplayDialog::KeyEscape()
{
	StopDialog();
}






//---------------------------------------------




void UWDisplayDialog::OnShowReplicPanel_Implementation(UPARAM(ref) bool& Show, UPARAM(ref) FString& s)
{

}
void UWDisplayDialog::ShowReplicPanel(bool Show)
{

	if (Show)ReplicBorder->SetVisibility(ESlateVisibility::Visible);   //   Collapsed,  Hidden,  Visible  
	else ReplicBorder->SetVisibility(ESlateVisibility::Collapsed);
																
	//OnShowReplicPanel(Show, Replic);           //  For flexible logic
}


void UWDisplayDialog::OnShowResponsePanel_Implementation(UPARAM(ref) bool& Show, UPARAM(ref) FString& s)
{

}
void UWDisplayDialog::ShowResponsePanel(bool Show)
{
	if (Show) ResponseBorder->SetVisibility(ESlateVisibility::Visible);   //   Collapsed,  Hidden,  Visible  
	else ResponseBorder->SetVisibility(ESlateVisibility::Collapsed);

	//OnShowResponsePanel(Show, Replic);           //  For flexible logic
}
/*
////+++++++++++++++++++++++++++++++++++++++++++++
//void UWDisplayDialog::DrawReplic(FString& _XmlFileContent, FString& _LastDialog, FString& _LastSpeech,
//											FString& _Replic, float _SoundDelay, ETransitType _TransitType)
//{
//
//	if (ReplicsScrollBox)
//	{
//		Replic = _Replic;
//		LastDialog = _LastDialog;
//		LastSpeech = _LastSpeech;
//		SoundDelay = _SoundDelay;
//		XmlFileContent = &_XmlFileContent;
//		TransitType = _TransitType;
//
//
//		UTextBlock* elTxt = WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass());
//		///UTextBlock* ttt = ConstructObject<UTextBlock>(UTextBlock::StaticClass(), this);
//		elTxt->SetText(FText::FromString(_Replic));
//		ReplicsScrollBox->AddChild(elTxt);
//		ReplicsText.Add(elTxt);
//
//
//		//  For flexible logic
//		bool T = true;
//		OnShowReplicPanel(T, Replic);
//
//		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++   DON'T DELATE BUT WAIT WHILE PRESS KEY
//		if (SoundDelay < -0.5)           //   if == -1   -> Don't delay, but wait while press KEY
//		{
//			//  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//			//  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//			//  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//
//			// wait press KEY, then:
//			// ReplicDelay();
//		}
//		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++S
//		else
//		{
//			GetWorld()->GetTimerManager().SetTimer(TimerHandle_ReplicDelay, this, &UWDisplayDialog::ReplicDelay, SoundDelay, false);
//		}
//	}
//}


void UWDisplayDialog::DrawResponse(FString& _XmlFileContent, FString& _LastDialog, FString& _LastSpeech,
													TArray<FString>& _Response, TArray<int32>& _ResponseIndex)
{
	for (int32 i = 0; i < _Response.Num(); i++)
	{
		if (GlobagDialogActorRef && ResponseScrollBox && ResponseButtonClassBP)
		{
			


			UWResponseButton* elResponse = CreateWidget<UWResponseButton>(this, ResponseButtonClassBP);
			//UWResponseButton* elResponse = WidgetTree->ConstructWidget<UWResponseButton>(UWResponseButton::StaticClass());
			elResponse->init(GlobagDialogActorRef, _XmlFileContent, _LastDialog, _LastSpeech, _Response[i], _ResponseIndex[i]);
			ResponseButton.Add(elResponse);

			//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++   MABE DON'T ADD TO SCROLL

			//  =======================   Add  to  PARENT    =======================     !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			ResponseScrollBox->AddChild(elResponse);   //  7777777777777777777777777777777777
			//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


			//   TEST
			//if(aaa)	GlobagDialogActorRef->DLG_PlayDialog(*XmlFileContent);
			//aaa = false;
		}
	}
}







//  ---------  Clear replic panel  ----------
void UWDisplayDialog::DrawResponsePrepare()
{
	for (UWResponseButton* elResponse : ResponseButton) elResponse->RemoveFromParent();
	ResponseButton.Empty();
}


//  ---------  Clear replic panel  ----------   
void UWDisplayDialog::DrawReplicPrepare()
{
	if (!Scrolling_dialog)  //  if NOT SCROLLING REPLICS
	{
		for (UTextBlock* elTxt : ReplicsText)   elTxt->RemoveFromParent();
		ReplicsText.Empty();
	}
}

*/

