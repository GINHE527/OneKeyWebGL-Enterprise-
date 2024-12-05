#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UMG/Public/Components/Widget.h"
#include "OneKeyWebGLSettings.generated.h"

UCLASS(config = Game, defaultconfig)
class ONEKEYWEBGL_API UOneKeyWebGLSettings : public UObject
{
    GENERATED_BODY()

public:
    UOneKeyWebGLSettings();

    UPROPERTY(Transient, VisibleAnywhere, Category = "OneKeyWebGL Custom Settings")
    UTexture2D* PreviewImage;

    UFUNCTION(CallInEditor, Category = "OneKeyWebGL Custom Settings")
    void RegeneratePreview();
    
    UPROPERTY(config, EditAnywhere, Category = "OneKeyWebGL Custom Settings")
    FString Custom_Project_Name; // 自定义项目名称

    //账户密码
    UPROPERTY(config, EditAnywhere, Category = "login here")
    FString Account_;

    UPROPERTY(config, EditAnywhere, Category = "login here")
    FString Password_;

    UPROPERTY(config, VisibleAnywhere, Category = "Plz confirm Eula in www.example.com ")
    bool Eula_Confirm; //是否同意EULA协议
};
