// 版权所有 Epic Games, Inc. 保留所有权利。

#pragma once

#include "CoreMinimal.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "Input/Reply.h"
#include "Types/SlateStructs.h"
#include "Widgets/SCompoundWidget.h"
#include "IElImagePickerModule.h"
#include "Brushes/SlateDynamicImageBrush.h"
#include "Widgets/Notifications/SErrorText.h"

/**
 * 用于显示和编辑外部图像引用的小部件（例如，启动屏幕、平台图标等）
 */
class SElImagePicker : public SCompoundWidget
{
public:

	SLATE_BEGIN_ARGS(SElImagePicker) {}

		/** 我们将要编辑的图像的路径 */
		SLATE_ARGUMENT(FString, TargetImagePath)

		/** 要显示的默认图像的路径 */
		SLATE_ARGUMENT(FString, DefaultImagePath)

		/** 当选择图像时触发的委托 */
		SLATE_ARGUMENT(FOnExternalImagePicked, OnExternalImagePicked)

		/** 获取开始选择路径时触发的委托 */
		SLATE_ARGUMENT(FOnGetPickerPath, OnGetPickerPath)

		/** 图像显示应该被限制的尺寸。保持纵横比。 */
		SLATE_ARGUMENT(FVector2D, MaxDisplayedImageDimensions)

		/** 实际图像需要的大小（除非设置了bRequiresSpecificSize，否则忽略） */
		SLATE_ARGUMENT(FIntPoint, RequiredImageDimensions)

		/** 图像是否需要特定尺寸？ */
		SLATE_ARGUMENT(bool, RequiresSpecificSize)

		/** 图像允许的扩展名 */
		SLATE_ARGUMENT(TArray<FString>, Extensions)

// 		当前所指的settings对象（确保能正确修改）
// 		SLATE_ARGUMENT(UOneKeyWebGLSettings*, Sett);

	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);



private:
	/** 将具有给定扩展名的目标图像应用到预览中，或如果缺少目标则应用默认图像 */
	void ApplyImageWithExtenstion(const FString& Extension);

	/** 应用第一个匹配支持扩展名的有效图像 */
	void ApplyFirstValidImage();

	/** 将目标图像应用到预览中，或如果缺少目标则应用默认图像 */
	void ApplyImage();

	/** 将图像应用到预览中 */
	void ApplyImage(const FString& ImagePath);

	/** 应用用于指示“无图像”的占位符图像 */
	void ApplyPlaceholderImage();

	/** 单击“选择文件”按钮时调用的委托 */
	FReply OnPickFile();

	/** 委托用于检索要显示的图像 */
	const FSlateBrush* GetImage() const;

	/** 返回选定图像的工具提示，表示尺寸 */
	FText GetImageTooltip() const;

	/** 辅助函数，用于调整图像大小以保留纵横比 */
	FVector2D GetConstrainedImageSize() const;

	/** 委托，用于限制显示图像的宽度 */
	FOptionalSize GetImageWidth() const;

	/** 委托，用于限制显示图像的高度 */
	FOptionalSize GetImageHeight() const;

	/** 从磁盘加载图像并制作一个Slate笔刷 */
	TSharedPtr< FSlateDynamicImageBrush > LoadImageAsBrush(const FString& ImagePath);

	/** 用于重置图像到默认状态的委托处理程序 */
	void HandleResetToDefault();

	/** 获取用于重置为默认状态的文本的委托处理程序 */
	FText GetResetToDefaultText() const;

	/** 检查是否与默认值有不同之处 */
	bool DiffersFromDefault() const;

private:
	/** 我们用于绘制启动画面的笔刷 */
	TSharedPtr<FSlateDynamicImageBrush> ImageBrush;

	/** 包含图像预览的框 */
	TSharedPtr<SHorizontalBox> ImageBox;

	/** 要显示的默认图像的路径 */
	FString DefaultImagePath;

	/** 我们将要编辑的图像的路径 */
	FString TargetImagePath;

	/** 我们要使用的文件类型的扩展名 */
	TArray<FString> Extensions;

	/** 当选择图像时触发的委托 */
	FOnExternalImagePicked OnExternalImagePicked;

	/** 选择器将使用的起始路径 */
	FOnGetPickerPath OnGetPickerPath;

	/** 正在使用哪种类型的图像 */
	enum EFileLocation
	{
		UsingDummyPlaceholderImage,
		UsingDefaultImage,
		UsingTargetImage,
	};

	/** 我们正在使用哪个文件？ */
	EFileLocation TypeOfImage;

	/** 图像显示应该被限制的尺寸 */
	FVector2D MaxDisplayedImageDimensions;

	/** 图像应该拥有的尺寸（如果设置了bRequiresSpecificSize） */
	FIntPoint RequiredImageDimensions;

	/** 图像是否需要特定尺寸？ */
	bool bRequiresSpecificSize;

	/** 用于显示错误尺寸的错误提示小部件 */
	TSharedPtr<class SErrorText> ErrorHintWidget;

	
};
