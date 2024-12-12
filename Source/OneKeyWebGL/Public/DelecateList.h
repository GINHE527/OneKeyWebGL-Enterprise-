#pragma once 
#include "CoreMinimal.h"

//Settings 于 子类 Picker 通信
DECLARE_DELEGATE_OneParam(DSettingstoEImagePicker, class UOneKeyWebGLSettings*)

//Socket 于 slate confirm 通信 
DECLARE_DELEGATE_OneParam(DSockettoConfirmSlate, class SConfirmWidget*)