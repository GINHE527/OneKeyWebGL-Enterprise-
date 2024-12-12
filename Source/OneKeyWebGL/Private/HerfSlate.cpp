#include "HerfSlate.h"

/*#include "WebBrowserModule.h"*/
#include "Runtime/Core/Public/Windows/WindowsPlatformProcess.h"

FString SHerfSlate::WebsiteSource = "https://txc.qq.com/products/673962/";
void SHerfSlate::Construct(const FArguments& InArgs) {
	ChildSlot
		[
			SNew(SButton)
				.Text(FText::FromString(TEXT("µã»÷Ìø×ª")))
				.OnClicked(this, &SHerfSlate::OnButtonClick)
		];
}

FReply SHerfSlate::OnButtonClick() {
	FPlatformProcess::LaunchURL(TEXT("https://txc.qq.com/products/673962/"),NULL, NULL);
	return FReply::Handled();
}