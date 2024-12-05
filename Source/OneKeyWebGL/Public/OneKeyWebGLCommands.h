// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "OneKeyWebGLStyle.h"

class FOneKeyWebGLCommands : public TCommands<FOneKeyWebGLCommands>
{
public:

	FOneKeyWebGLCommands()
		: TCommands<FOneKeyWebGLCommands>(
			TEXT("OneKeyWebGL"),
			NSLOCTEXT("Contexts", "OneKeyWebGL", "OneKeyWebGL Plugin"),
			NAME_None,
			FOneKeyWebGLStyle::GetStyleSetName())	
	{
	};

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > ToExtendMenu;
	TSharedPtr< FUICommandInfo > OpenPluginWindow;
	TSharedPtr< FUICommandInfo > ClearTemp;
	TSharedPtr< FUICommandInfo > FixPlugins;

};
