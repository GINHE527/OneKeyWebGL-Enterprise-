// Copyright Epic Games, Inc. All Rights Reserved.

#include "OneKeyWebGL.h"
#include "OneKeyWebGLStyle.h"
#include "OneKeyWebGLCommands.h"
#include "Misc/MessageDialog.h"
#include "ToolMenus.h"
#include <EditorWorldExtension.h>

#include "FileZipperGinhe.h"
#include <cstdlib>
#include "LevelEditor.h"
#define FExtendMenuBase FOneKeyWebGLModule

static const FName OneKeyWebGLTabName("OneKeyWebGL");
static bool isRuned = false;
int copylist = 0;
short COPYlist = 0;
Zipper_ginhe* ZipPtr = new Zipper_ginhe();

#define LOCTEXT_NAMESPACE "FOneKeyWebGLModule"

void FOneKeyWebGLModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FOneKeyWebGLStyle::Initialize();

	FOneKeyWebGLStyle::ReloadTextures();

	FOneKeyWebGLCommands::Register();

	ExtendMenuByFExtend();

	PluginCommands = MakeShareable(new FUICommandList);



	//绑定事件
	PluginCommands->MapAction(
		FOneKeyWebGLCommands::Get().ToExtendMenu,
		FExecuteAction::CreateRaw(this, &FOneKeyWebGLModule::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FOneKeyWebGLModule::RegisterMenus));
}


void FOneKeyWebGLModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		SettingsModule->UnregisterSettings("Project", "Plugins", "UOneKeyWebGLSettings");
	}

	FOneKeyWebGLStyle::Shutdown();

	FOneKeyWebGLCommands::Unregister();
}

void FExtendMenuBase::ExtendMenuByFExtend()
{
	TSharedPtr<FExtender> MainMenuExtender = MakeShareable(new FExtender);

	MainMenuExtender->AddMenuExtension(
		"EpicGamesHelp",
		EExtensionHook::After,
		nullptr,
		FMenuExtensionDelegate::CreateRaw(this, &FExtendMenuBase::MakeExistingMainMenuEntry)
	);

	// 起始于此处
	MainMenuExtender->AddMenuBarExtension(
		"Help",
		EExtensionHook::After,
		nullptr,
		FMenuBarExtensionDelegate::CreateRaw(this, &FExtendMenuBase::MakeNewMenuBarEntry)
	);

	FLevelEditorModule& LevelEditorModule =
		FModuleManager::Get().LoadModuleChecked<FLevelEditorModule>("LevelEditor");

	TSharedPtr<FExtensibilityManager> MenuExtensibilityManager =
		LevelEditorModule.GetMenuExtensibilityManager();

	MenuExtensibilityManager->AddExtender(MainMenuExtender);
}

void FExtendMenuBase::MakeExistingMainMenuEntry(FMenuBuilder& MenuBuilder)
{
	MenuBuilder.AddMenuEntry(
		FText::FromString("Existing Hook Button"),	        // 按钮名称
		FText::FromString("This is a existing hook extend"),	// 按钮提示
		FSlateIcon(),	            // 我们可以为按钮添加图标，这里暂时缺省
		FUIAction(FExecuteAction::CreateRaw(
			this, &FExtendMenuBase::ExistingMainMenuEntryAction))// 绑定执行按钮的代理函数
	);
}

void FExtendMenuBase::ExistingMainMenuEntryAction()
{
	UE_LOG(LogTemp, Warning, TEXT("ExistingMainMenuEntryAction is called."))
}

void FExtendMenuBase::MakeNewMenuBarEntry(FMenuBarBuilder& MenuBarBuilder)
{
	MenuBarBuilder.AddPullDownMenu(						// 添加下拉菜单按钮
		FText::FromString("OneKeyWebGL"),					// 该按钮名称
		FText::FromString("Click it to open the menu"),
		FNewMenuDelegate::CreateRaw(this, &FExtendMenuBase::MakeNewMainMenuEntry),
		"OneKeyWebGL HOOK"					                // 该按钮的ExtensionHook
	);
}

void FExtendMenuBase::MakeNewMainMenuEntry(FMenuBuilder& MenuBuilder)
{
	MenuBuilder.BeginSection("Section 1", FText::FromString("OneKeyWebGL"));	// 设置Section

	MenuBuilder.AddMenuEntry(
		FText::FromString("User Info"),
		FText::FromString("Click it show User Info"),
		FSlateIcon(),
		FUIAction(FExecuteAction::CreateRaw(this, &FExtendMenuBase::NewMainMenuEntryAction))
	);

	MenuBuilder.AddMenuEntry(
		FText::FromString("Upload"),
		FText::FromString("Click it to begin uploading"),
		FSlateIcon(),
		FUIAction(FExecuteAction::CreateRaw(this, &FOneKeyWebGLModule::Copy_Zip_Upload))
	);

	MenuBuilder.AddMenuEntry(
		FText::FromString("clear temp"),
		FText::FromString("Click it to clear"),
		FSlateIcon(),
		FUIAction(FExecuteAction::CreateRaw(this, &FOneKeyWebGLModule::Deletetemp))
	);
	MenuBuilder.EndSection();	                                       // 结束Section设置
}


//请不要修改这串代码
void FOneKeyWebGLModule::Deletetemp() {

	FString Output_Text = "temp Size is ";

	uint64 Need_delete_size = 0;

	const FString Need_delete_path = ZipPtr->Project_ab_path + "OneKey";

	Need_delete_size = GetDirectorySize(Need_delete_path);

	FString Size_Str = FString::Printf(TEXT("%llu"), Need_delete_size);

	Output_Text += Size_Str;
	Output_Text += "\n\t\t";
	Output_Text += "Press 'Ok' to delete temp \n\t\t";
	Output_Text += "Press 'Cancel' or close it will not to delete";

	FText const Title = FText::FromString("OneKeyWebGL");
	FText const DialogText = FText::Format(LOCTEXT("Output", "{0}"), FText::FromString(Output_Text));
	EAppReturnType::Type const ReturnType = FMessageDialog::Open(EAppMsgType::OkCancel, DialogText, &Title);
	if (ReturnType == EAppReturnType::Type::Ok)
	{
		// When clicked Ok button
		std::string folderPath = TCHAR_TO_UTF8(*Need_delete_path);
		std::string command = "RMDIR /S /Q ";
		for (int i = 0; i < folderPath.length(); i++)
		{
			if (folderPath[i] == '/')
				folderPath[i] = '\\';
		}
		command += folderPath;

		if (std::system(command.c_str()) == 0) {
			DebugLog("Folder deleted successfully");
		}
		else {
			DebugLog("Failed to delete folder");
		}
		return;
	}
	else if (ReturnType == EAppReturnType::Type::Cancel)
	{
		// When clicked Cancel button
		return;
	}

	
}
void FExtendMenuBase::NewMainMenuEntryAction()
{
	UE_LOG(LogTemp, Warning, TEXT("NewMainMenuEntryAction is called."))
}

void FOneKeyWebGLModule::Copy_Zip_Upload() {
	//检测是否开启
	if (!ZipPtr->ItCanBeRun)
	{
		DebugLog("ERORR CODE 000001 ,not list to send !");
		return;
	}
	//用于复制上传逻辑
	else if (copylist < 3) {
		copylist++;
		Zipper_ginhe_thread* ZipRunnable = new Zipper_ginhe_thread(ZipPtr);
		FRunnableThread* Thread = FRunnableThread::Create(ZipRunnable, TEXT("Thread -> upload"), 0, TPri_Normal);
	}
}

void FOneKeyWebGLModule::PluginButtonClicked()
{
	// Put your "OnButtonClicked" stuff here
	
}

//该方法用于点击按钮后，ES 渲染的开启和关闭 //待完成
void RenderingAdjustToOpenGLES(bool OpenButton) 
{
	if (OpenButton){
		if (GEditor) {
			GEditor;
		}
	}
	else {
		GEditor;
	}
}

//菜单的具体实现
void FOneKeyWebGLModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	//位于windows下

	FToolMenuOwnerScoped OwnerScoped(this);
	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.File");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("OneWebGL");
			Section.AddMenuEntryWithCommandList(FOneKeyWebGLCommands::Get().ToExtendMenu, PluginCommands);
		}
	}
	//位于编辑器上层
	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("Settings");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FOneKeyWebGLCommands::Get().ToExtendMenu));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}

	if (ISettingsModule* SettingModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		SettingModule->RegisterSettings("Project", "Plugins", "MySetting",
			LOCTEXT("RuntimeSettingsName", "My Setting Page"),
			LOCTEXT("RuntimeSettingsDescription", "Configure my setting"),
			GetMutableDefault<UOneKeyWebGLSettings>()
		);
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FOneKeyWebGLModule, OneKeyWebGL)