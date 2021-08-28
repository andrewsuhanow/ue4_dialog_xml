// Fill out your copyright notice in the Description page of Project Settings.

///////////////  StyleSlate01Style
#include "EditorDialogResourceStyle.h"

FEditorDialogResourceStyle::FEditorDialogResourceStyle()
{
}

FEditorDialogResourceStyle::~FEditorDialogResourceStyle()
{
}

const FName FEditorDialogResourceStyle::TypeName(TEXT("FEditorDialogResourceStyle"));

const FEditorDialogResourceStyle& FEditorDialogResourceStyle::GetDefault()
{
	static FEditorDialogResourceStyle Default;
	return Default;
}

void FEditorDialogResourceStyle::GetResources(TArray<const FSlateBrush*>& OutBrushes) const
{
	// Add any brush resources here so that Slate can correctly atlas and reference them
}

