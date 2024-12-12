// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "Editor/UnrealEd/Public/Editor.h"
#include "Editor/UnrealEd/Public/UnrealEdGlobals.h"
#include "RenderingThread.h"
#include "Developer/Settings/Public/ISettingsModule.h"
#include "OneKeyWebGLSettings.h"
#include "Modules/ModuleManager.h"
#include "OpenGL/GL/glcorearb.h"


class FToolBarBuilder;
class FMenuBuilder;

class FOneKeyWebGLModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	
	/** This function will be bound to Command. */
	void PluginButtonClicked();
	/** 复制全流程 */
	void Copy_Zip_Upload();
	/*清理缓存*/
	void Deletetemp();
	/*委托绑定*/
	void Declare_Bind();
	TSharedPtr<FExtender>ToolBarExtender;
	TSharedPtr<const FExtensionBase>Extension;

private:

	void RegisterMenus();

private:
	TSharedRef<SDockTab> OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs);

	TSharedPtr<class FUICommandList> PluginCommands;
	/** FExtend拓展方式入口函数 */
	void ExtendMenuByFExtend();
	/** 在已有拓展点生成一个菜单按钮 */
	void MakeExistingMainMenuEntry(FMenuBuilder& MenuBuilder);
	/** 在已有拓展点生成菜单按钮的调用事件 */
	void ExistingMainMenuEntryAction();
	/** 生成一个MenuBar菜单按钮 */
	void MakeNewMenuBarEntry(FMenuBarBuilder& MenuBarBuilder);
	/** 在新拓展点生成一个菜单按钮 */
	void MakeNewMainMenuEntry(FMenuBuilder& MenuBuilder);
	/** 在新拓展点生成菜单按钮的调用事件 */
	void NewMainMenuEntryAction();
	
};

