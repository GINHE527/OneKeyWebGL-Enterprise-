// Copyright Epic Games, Inc. All Rights Reserved.

#include "OneKeyWebGLCommands.h"


#define LOCTEXT_NAMESPACE "FOneKeyWebGLModule"

void FOneKeyWebGLCommands::RegisterCommands()
{
	//Ðü¸¡ÎÄ×ÖÏÔÊ¾
	UI_COMMAND(ToExtendMenu, "OneKeyWebGL", "Click it to open menus", EUserInterfaceActionType::Button, FInputGesture());
	UI_COMMAND(OpenPluginWindow, "OneKeyWebGL", "Open tHE MENU", EUserInterfaceActionType::Button, FInputGesture())
}




#undef LOCTEXT_NAMESPACE
