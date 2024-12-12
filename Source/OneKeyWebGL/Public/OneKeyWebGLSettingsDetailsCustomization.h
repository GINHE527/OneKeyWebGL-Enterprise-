// OneKeyWebGLSettingsDetailsCustomization.h

#pragma once

#include "CoreMinimal.h"
#include "IDetailCustomization.h"
#include "OneKeyWebGLSettings.h"
#include "SConfirmWidget.h"

class FOnekeyWebGLSettingsDetailsCustomization : public IDetailCustomization {
public :
	static TSharedRef<IDetailCustomization>MakeInstance();
	virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;
};



