// Copyright Epic Games, Inc. All Rights Reserved.

using System.IO;
using UnrealBuildTool;

public class OneKeyWebGL : ModuleRules
{
   
public OneKeyWebGL(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        bEnableUndefinedIdentifierWarnings = false; // Ϊ���޸��������
        bEnableExceptions = true; // ����std��exception��û���õĻ��������ַ�����ת����ʱ�򣬷�Windowsƽ̨���б������

        string LibDir = Path.Combine(ModuleDirectory, "Zlib/lib");

        foreach (string file in Directory.GetFiles(LibDir))
        {
            PublicAdditionalLibraries.Add(file);
        }
        PublicIncludePaths.AddRange(
			new string[] {
				// ... add public include paths required here ...
				"OneKeyWebGL/Public/",
				"OneKeyWebGL/Private/",
                "OneKeyWebGL/Zlib/"
            }
			); 
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
				// ... add other private include paths required here ...
				"OneKeyWebGL/Public/",

                "OneKeyWebGL/Zlib/"
            }
			);
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"zlib"
				// ... add other public dependencies that you statically link with here ...
			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"Projects",
				"InputCore",
				"UnrealEd",
				"ToolMenus",
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
				// ... add private dependencies that you statically link with here ...	
			}
			);
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
			);
	}
}
