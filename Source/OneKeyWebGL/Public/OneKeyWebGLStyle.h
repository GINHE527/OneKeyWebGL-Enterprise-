// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Styling/SlateStyle.h"

class FOneKeyWebGLStyle
{
public:

	static void Initialize();

	static void Shutdown();

	/** reloads textures used by slate renderer */
	static void ReloadTextures();

	/** @return The Slate style set for the Shooter game */
	static const ISlateStyle& Get();

	//点击按钮
	static void ClickOpen();

	static FName GetStyleSetName();

private:
	//建立时显示
	static TSharedRef< class FSlateStyleSet > Create();
	//点击时显示
	static TSharedRef< class FSlateStyleSet > Is_Open();

private:

	static TSharedPtr< class FSlateStyleSet > StyleInstance;
};