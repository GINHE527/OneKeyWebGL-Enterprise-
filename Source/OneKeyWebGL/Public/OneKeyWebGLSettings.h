#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UMG/Public/Components/Widget.h"
#include "ThumbnailRendering/ThumbnailManager.h"
#include "ImageUtils.h"
#include "IElImagePickerModule.h"
#include "OneKeyWebGLSettings.generated.h"

UCLASS(config = Game, defaultconfig)
class ONEKEYWEBGL_API UOneKeyWebGLSettings : public UObject
{
    GENERATED_BODY()

public:
    UOneKeyWebGLSettings();

//     UPROPERTY(Transient, VisibleAnywhere, Category = "OneKeyWebGL Custom Settings")
//     FImage* PreviewImage;


    UFUNCTION(CallInEditor, Category = "OneKeyWebGL Custom Settings")
    void RegeneratePreview();

	UPROPERTY(config, EditAnywhere, Category = "OneKeyWebGL Custom Settings")
	FString ImagePath;

    UPROPERTY(config, EditAnywhere, Category = "OneKeyWebGL Custom Settings")
    FString Custom_Project_Name; // �Զ�����Ŀ����
    
    UPROPERTY(config, EditAnywhere, Category = "OneKeyProject Icon Set")
    FString IcoPath;
    //�˻�����
    UPROPERTY(config, EditAnywhere, Category = "login here")
    FString Account_;

    UPROPERTY(config, EditAnywhere, Category = "login here")
    FString Password_;

    UPROPERTY(config, VisibleAnywhere, Category = "Elua")
    bool Eula_Confirm; //�Ƿ�ͬ��EULAЭ��

    void UpdateImagePaths();

    static TSharedRef<SWidget>CreateImageWidget(UOneKeyWebGLSettings* Settings);

    static TSharedRef<SWidget>CreateIcoImageWidget(UOneKeyWebGLSettings* Settings);

   
};
