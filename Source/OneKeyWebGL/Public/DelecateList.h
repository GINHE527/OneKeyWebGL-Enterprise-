#pragma once 
#include "CoreMinimal.h"

//Settings �� ���� Picker ͨ��
DECLARE_DELEGATE_OneParam(DSettingstoEImagePicker, class UOneKeyWebGLSettings*)

//Socket �� slate confirm ͨ�� 
DECLARE_DELEGATE_OneParam(DSockettoConfirmSlate, class SConfirmWidget*)