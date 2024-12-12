// Copyright Epic Games, Inc. All Rights Reserved.

#include "SConfirmWidget.h"
#include "Misc/Paths.h"
#include "HAL/PlatformFilemanager.h"
#include "Widgets/SBoxPanel.h"
#include "Widgets/Layout/SBorder.h"
#include "Widgets/Images/SImage.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/Input/SButton.h"
#include "GenericPlatform/GenericPlatformFile.h"
#include "ISourceControlProvider.h"
#include "ISourceControlModule.h"
#include "SourceControlHelpers.h"
#include "EditorStyleSet.h"
#include "Widgets/Layout/SWidgetSwitcher.h"
#include "Framework/Notifications/NotificationManager.h"
#include "Widgets/Notifications/SNotificationList.h"

#define LOCTEXT_NAMESPACE "SConfirmWidget"

/////////////////////////////////////////////////////
// Widget的定义和使用



TSharedRef<SWidget> SConfirmWidget::MakeRow(FName IconName, FText Message, FText ButtonMessage)
{
	FText Tooltip = LOCTEXT("PlatformSetupTooltip", "click it to add");

	TSharedRef<SHorizontalBox> Result = SNew(SHorizontalBox)
		.ToolTipText(Tooltip)

		// Status icon
		+ SHorizontalBox::Slot()
		.AutoWidth()
		.VAlign(VAlign_Center)
		[
			SNew(SImage)
				.Image(FEditorStyle::GetBrush(IconName))
		]

		// Notice
		+ SHorizontalBox::Slot()
		.FillWidth(10.0f)
		.Padding(16.0f, 0.0f)
		.VAlign(VAlign_Center)
		[
			SNew(STextBlock)
				.ColorAndOpacity(FLinearColor::White)
				.ShadowColorAndOpacity(FLinearColor::Black)
				.ShadowOffset(FVector2D::UnitVector)
				.Text(Message)
		];


	if (!ButtonMessage.IsEmpty())
	{
		Result->AddSlot()
			.AutoWidth()
			.VAlign(VAlign_Center)
			[
				SNew(SButton)
					.OnClicked(this, &SConfirmWidget::OnButtonPressed)
					.Text(ButtonMessage)
			];
	}

	return Result;
}
//需要修改
bool SConfirmWidget::login() {

	return true;
}

void SConfirmWidget::Construct(const FArguments& InArgs)
{
	TargetFilename = " ";

	FOnSetupClicked = InArgs._FOnSetupClicked;
	isLogined = false;
	isConfirmed = false;
	//未登录界面
	TSharedRef<SWidget> NoLoginWidget = MakeRow(
		"SettingsEditor.WarningIcon",
		LOCTEXT("NoLoginText", "The plugins arent not login ,press button to login"),
		LOCTEXT("MissingFilesButton", "Login Now"));

	TSharedRef<SWidget> ErrorLoginWidget = MakeRow(
		"SettingsEditor.WarningIcon",
		LOCTEXT("ErrorLoginText", "The account or password are incorrect , please check out now"),
		LOCTEXT("NeedsCheckoutButton", "ReLogin Now"));

	TSharedRef<SWidget> NoConfirmWidget = MakeRow(
		"SettingsEditor.WarningIcon",
		LOCTEXT("NoConfirmText", "Now is login but not confirm ours ELUA , please check and confirm it to continue"),
		LOCTEXT("ReadOnlyButton", "Continue now"));

	TSharedRef<SWidget> ConfirmedWidget = MakeRow(
		"SettingsEditor.GoodIcon",
		LOCTEXT("ReadyToModifyText", "All is done！"),
		FText::GetEmpty());

	ChildSlot
		[
			SNew(SBorder)
				.BorderBackgroundColor(this, &SConfirmWidget::GetBorderColor)
				.BorderImage(FEditorStyle::GetBrush("ToolPanel.LightGroupBorder"))
				.Padding(8.0f)
				/*.DesiredSizeScale(FVector2D(100.0,1.0))*/
				[
					SNew(SWidgetSwitcher)
						.WidgetIndex(this, &SConfirmWidget::GetSetupStateAsInt)

						// Locked slot
						+ SWidgetSwitcher::Slot()
						[
							NoLoginWidget
						]
						+ SWidgetSwitcher::Slot()
						[
							ErrorLoginWidget
						]
						+ SWidgetSwitcher::Slot()
						[
							NoConfirmWidget
						]
						+ SWidgetSwitcher::Slot()
						[
							ConfirmedWidget
						]
				]
		];

	UpdateCache(true);
}

void SConfirmWidget::Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime)
{
	UpdateCache(false);
}

int32 SConfirmWidget::GetSetupStateAsInt() const
{
	return (int32)CachedSetupState;
}
//先简单这么些 需要完善相关功能
SConfirmWidget::ESetupState  SConfirmWidget::GetSetupStateBasedOnFile(bool bForce) const
{
	if (!isLogined)
	{
		return NoLogin;
	}
	else
	{
		if(!isConfirmed){
			return NoConfirm;
		}
		return Confirmed;
	}
}

void SConfirmWidget::UpdateCache(bool bForceUpdate)
{
	CachedSetupState = GetSetupStateBasedOnFile(bForceUpdate);
}

FSlateColor SConfirmWidget::GetBorderColor() const
{
	switch (CachedSetupState)
	{
	case NoLogin:
		return FLinearColor(0.8f, 0, 0);
	case Confirmed:
		return FLinearColor::Green;
	case ErrorLogin:
	case NoConfirm:
	default:
		return FLinearColor::Yellow;
	}
}

//按下按钮的反馈
FReply SConfirmWidget::OnButtonPressed()
{
	switch (CachedSetupState)
	{
	case NoLogin:
		DComfirm_Login_Declare.ExecuteIfBound();
		//FOnSetupClicked.Execute();
		isLogined = true;
		UpdateCache(false);
		break;

	case ErrorLogin:
	{
// 		if (!FPlatformFileManager::Get().GetPlatformFile().SetReadOnly(*TargetFilename, false))
// 		{
// 			FText NotificationErrorText = FText::Format(LOCTEXT("FailedToMakeWritable", "Could not make {0} writable."), FText::FromString(TargetFilename));
// 
// 			FNotificationInfo Info(NotificationErrorText);
// 			Info.ExpireDuration = 3.0f;
// 
// 			FSlateNotificationManager::Get().AddNotification(Info);
// 		}
		UpdateCache(false);
	}
	break;

	case NoConfirm:
	{
		isConfirmed = true;
// 		FText ErrorMessage;
// 
// 		if (!SourceControlHelpers::CheckoutOrMarkForAdd(TargetFilename, FText::FromString(TargetFilename), NULL, ErrorMessage))
// 		{
// 			FNotificationInfo Info(ErrorMessage);
// 			Info.ExpireDuration = 3.0f;
// 			FSlateNotificationManager::Get().AddNotification(Info);
// 		}
		UpdateCache(false);
	}
	break;

	case Confirmed:
	default:
		break;
	}

	return FReply::Handled();
}

bool SConfirmWidget::IsReadyToGo() const
{
	return CachedSetupState == Confirmed;
}

TAttribute<bool> SConfirmWidget::GetReadyToGoAttribute() const
{
	return TAttribute<bool>(this, &SConfirmWidget::IsReadyToGo);
}

/////////////////////////////////////////////////////

#undef LOCTEXT_NAMESPACE
