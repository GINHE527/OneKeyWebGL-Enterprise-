// 

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleInterface.h"
#include "Modules/ModuleManager.h"
#include "Editor/PropertyEditor/Public/PropertyHandle.h"

/**
 * 当选取新图像时触发的委托。
 * @param InChosenImage 用户选取的图像的路径。
 * @param InTargetImage 此选择器所代表的目标图像的路径。
 * @return 如果图像应该被刷新则返回true
 */
DECLARE_DELEGATE_RetVal_TwoParams(bool, FOnExternalImagePicked, const FString& /** 已选图像 */, const FString& /** 目标图像 */);

/**
 * 用于获取开始选取图像的起始路径时触发的委托。
 * @return 选择器将用作起始的路径
 */
DECLARE_DELEGATE_RetVal(FString, FOnGetPickerPath);

/**
 * 用于配置外部图像选择器
 */
struct FElImagePickerConfiguration
{
public:
    FElImagePickerConfiguration()
        : MaxDisplayedImageDimensions(400.0f, 400.0f)
        , bRequiresSpecificSize(false)
    {
    }

    /** 外部图像存储在磁盘上对应的图像路径。 */
    FString TargetImagePath;

    /** 如果目标图像不存在时将使用的磁盘上的图像路径。 */
    FString DefaultImagePath;

    /** 选择器将用作起始的路径 */
    FOnGetPickerPath OnGetPickerPath;

    /** 当选取新图像时触发的委托。 */
    FOnExternalImagePicked OnExternalImagePicked;

    /** 图像显示应受限的尺寸。会保持宽高比。 */
    FVector2D MaxDisplayedImageDimensions;

    /** 实际图像需要达到的尺寸（除非设置了bRequiresSpecificSize，否则此参数会被忽略） */
    FIntPoint RequiredImageDimensions;

    /** 图像是否需要特定尺寸？ */
    bool bRequiresSpecificSize;

    /** 如果目标图像不存在时将使用的磁盘上的图像路径。 */
    TArray<FString> FileExtensions;

    /** 如果需要使用的属性句柄 */
    TSharedPtr<class IPropertyHandle> PropertyHandle;
    
};

/**
 * 闪屏编辑器模块的公共接口
 */
class IElImagePickerModule : public IModuleInterface
{
public:
    /**
     * 创建一个用于显示和编辑闪屏的部件。
     *
     * @param 传入配置参数
     * @return 图像编辑部件
     */
    virtual TSharedRef<class SWidget> MakeEditorWidget(const FElImagePickerConfiguration& InConfiguration) = 0;

    /**
     * 获取外部图像选择器模块实例的引用。
     *
     * @return 外部图像选择器模块的引用。
     */
    static IElImagePickerModule& Get()
	{
		return FModuleManager::LoadModuleChecked<IElImagePickerModule>("ElImagePicker");
    }
};