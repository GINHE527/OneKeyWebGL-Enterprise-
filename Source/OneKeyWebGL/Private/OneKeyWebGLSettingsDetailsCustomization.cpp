#include "OneKeyWebGLSettingsDetailsCustomization.h"
#include "DetailLayoutBuilder.h"
#include "DetailCategoryBuilder.h"
#include "DetailWidgetRow.h"  // 
#include "Widgets/SWidget.h"   // 
#include "OneKeyWebGLSettings.h"  // 
#include "HerfSlate.h"


TSharedRef<IDetailCustomization> FOnekeyWebGLSettingsDetailsCustomization::MakeInstance() {
	return MakeShareable(new FOnekeyWebGLSettingsDetailsCustomization);
}

void FOnekeyWebGLSettingsDetailsCustomization::CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) {
	IDetailCategoryBuilder& WebCate = DetailBuilder.EditCategory("Confirm state");
	WebCate.AddCustomRow(FText::FromString("To website"))
		.ValueContent()
		[
			SNew(SHerfSlate)
		];
	IDetailCategoryBuilder& CateConfirm = DetailBuilder.EditCategory("Confirm state");
	CateConfirm.AddCustomRow(FText::FromString("Confirm state"))
		.ValueContent()
		[
			SNew(SConfirmWidget)
		];

	IDetailCategoryBuilder& Category = DetailBuilder.EditCategory("OneKeyWebGL Custom Settings");

	Category.AddCustomRow(FText::FromString("Image Preview (1920x1080)"))
		.ValueContent()  // 使用ValueContent来加载小部件
		[
			UOneKeyWebGLSettings::CreateImageWidget(GetMutableDefault<UOneKeyWebGLSettings>())
		];

	IDetailCategoryBuilder& newCate = DetailBuilder.EditCategory("OneKeyProject Icon Set");

	newCate.AddCustomRow(FText::FromString("Icon Preview (64x64)"))
		.ValueContent()  // 使用ValueContent来加载小部件
		[
			UOneKeyWebGLSettings::CreateIcoImageWidget(GetMutableDefault<UOneKeyWebGLSettings>())
		];
}
