#include "OneKeyWebGLSettings.h"

// 构造函数，初始化默认值
UOneKeyWebGLSettings::UOneKeyWebGLSettings()
{
    PreviewImage = nullptr;
    Custom_Project_Name = "Project-Basic-Name";
    Account_ = "";
    Password_ = "";
    Eula_Confirm = false;
    //if(Custom_Loading_pi)
}
void UOneKeyWebGLSettings::RegeneratePreview() {
    return;
}