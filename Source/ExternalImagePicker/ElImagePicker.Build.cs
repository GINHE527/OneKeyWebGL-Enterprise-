// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ElImagePicker : ModuleRules
{
	public ElImagePicker(ReadOnlyTargetRules Target) : base(Target)
	{
        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
				"Core",
                "Slate",
				"SlateCore",
				"DesktopPlatform",
				"ImageWrapper",
				"EditorStyle",
				"InputCore",
				"PropertyEditor",	// for 'reset to default'
            }
        );
	}
}
