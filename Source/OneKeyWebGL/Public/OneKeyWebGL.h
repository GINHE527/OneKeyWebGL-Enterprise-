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
	/** ����ȫ���� */
	void Copy_Zip_Upload();
	/*������*/
	void Deletetemp();
	/*ί�а�*/
	void Declare_Bind();
	TSharedPtr<FExtender>ToolBarExtender;
	TSharedPtr<const FExtensionBase>Extension;

private:

	void RegisterMenus();

private:
	TSharedRef<SDockTab> OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs);

	TSharedPtr<class FUICommandList> PluginCommands;
	/** FExtend��չ��ʽ��ں��� */
	void ExtendMenuByFExtend();
	/** ��������չ������һ���˵���ť */
	void MakeExistingMainMenuEntry(FMenuBuilder& MenuBuilder);
	/** ��������չ�����ɲ˵���ť�ĵ����¼� */
	void ExistingMainMenuEntryAction();
	/** ����һ��MenuBar�˵���ť */
	void MakeNewMenuBarEntry(FMenuBarBuilder& MenuBarBuilder);
	/** ������չ������һ���˵���ť */
	void MakeNewMainMenuEntry(FMenuBuilder& MenuBuilder);
	/** ������չ�����ɲ˵���ť�ĵ����¼� */
	void NewMainMenuEntryAction();
	
};

