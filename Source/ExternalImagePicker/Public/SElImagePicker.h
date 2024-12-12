// ��Ȩ���� Epic Games, Inc. ��������Ȩ����

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
 * ������ʾ�ͱ༭�ⲿͼ�����õ�С���������磬������Ļ��ƽ̨ͼ��ȣ�
 */
class SElImagePicker : public SCompoundWidget
{
public:

	SLATE_BEGIN_ARGS(SElImagePicker) {}

		/** ���ǽ�Ҫ�༭��ͼ���·�� */
		SLATE_ARGUMENT(FString, TargetImagePath)

		/** Ҫ��ʾ��Ĭ��ͼ���·�� */
		SLATE_ARGUMENT(FString, DefaultImagePath)

		/** ��ѡ��ͼ��ʱ������ί�� */
		SLATE_ARGUMENT(FOnExternalImagePicked, OnExternalImagePicked)

		/** ��ȡ��ʼѡ��·��ʱ������ί�� */
		SLATE_ARGUMENT(FOnGetPickerPath, OnGetPickerPath)

		/** ͼ����ʾӦ�ñ����Ƶĳߴ硣�����ݺ�ȡ� */
		SLATE_ARGUMENT(FVector2D, MaxDisplayedImageDimensions)

		/** ʵ��ͼ����Ҫ�Ĵ�С������������bRequiresSpecificSize��������ԣ� */
		SLATE_ARGUMENT(FIntPoint, RequiredImageDimensions)

		/** ͼ���Ƿ���Ҫ�ض��ߴ磿 */
		SLATE_ARGUMENT(bool, RequiresSpecificSize)

		/** ͼ���������չ�� */
		SLATE_ARGUMENT(TArray<FString>, Extensions)

// 		��ǰ��ָ��settings����ȷ������ȷ�޸ģ�
// 		SLATE_ARGUMENT(UOneKeyWebGLSettings*, Sett);

	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);



private:
	/** �����и�����չ����Ŀ��ͼ��Ӧ�õ�Ԥ���У������ȱ��Ŀ����Ӧ��Ĭ��ͼ�� */
	void ApplyImageWithExtenstion(const FString& Extension);

	/** Ӧ�õ�һ��ƥ��֧����չ������Чͼ�� */
	void ApplyFirstValidImage();

	/** ��Ŀ��ͼ��Ӧ�õ�Ԥ���У������ȱ��Ŀ����Ӧ��Ĭ��ͼ�� */
	void ApplyImage();

	/** ��ͼ��Ӧ�õ�Ԥ���� */
	void ApplyImage(const FString& ImagePath);

	/** Ӧ������ָʾ����ͼ�񡱵�ռλ��ͼ�� */
	void ApplyPlaceholderImage();

	/** ������ѡ���ļ�����ťʱ���õ�ί�� */
	FReply OnPickFile();

	/** ί�����ڼ���Ҫ��ʾ��ͼ�� */
	const FSlateBrush* GetImage() const;

	/** ����ѡ��ͼ��Ĺ�����ʾ����ʾ�ߴ� */
	FText GetImageTooltip() const;

	/** �������������ڵ���ͼ���С�Ա����ݺ�� */
	FVector2D GetConstrainedImageSize() const;

	/** ί�У�����������ʾͼ��Ŀ�� */
	FOptionalSize GetImageWidth() const;

	/** ί�У�����������ʾͼ��ĸ߶� */
	FOptionalSize GetImageHeight() const;

	/** �Ӵ��̼���ͼ������һ��Slate��ˢ */
	TSharedPtr< FSlateDynamicImageBrush > LoadImageAsBrush(const FString& ImagePath);

	/** ��������ͼ��Ĭ��״̬��ί�д������ */
	void HandleResetToDefault();

	/** ��ȡ��������ΪĬ��״̬���ı���ί�д������ */
	FText GetResetToDefaultText() const;

	/** ����Ƿ���Ĭ��ֵ�в�֮ͬ�� */
	bool DiffersFromDefault() const;

private:
	/** �������ڻ�����������ı�ˢ */
	TSharedPtr<FSlateDynamicImageBrush> ImageBrush;

	/** ����ͼ��Ԥ���Ŀ� */
	TSharedPtr<SHorizontalBox> ImageBox;

	/** Ҫ��ʾ��Ĭ��ͼ���·�� */
	FString DefaultImagePath;

	/** ���ǽ�Ҫ�༭��ͼ���·�� */
	FString TargetImagePath;

	/** ����Ҫʹ�õ��ļ����͵���չ�� */
	TArray<FString> Extensions;

	/** ��ѡ��ͼ��ʱ������ί�� */
	FOnExternalImagePicked OnExternalImagePicked;

	/** ѡ������ʹ�õ���ʼ·�� */
	FOnGetPickerPath OnGetPickerPath;

	/** ����ʹ���������͵�ͼ�� */
	enum EFileLocation
	{
		UsingDummyPlaceholderImage,
		UsingDefaultImage,
		UsingTargetImage,
	};

	/** ��������ʹ���ĸ��ļ��� */
	EFileLocation TypeOfImage;

	/** ͼ����ʾӦ�ñ����Ƶĳߴ� */
	FVector2D MaxDisplayedImageDimensions;

	/** ͼ��Ӧ��ӵ�еĳߴ磨���������bRequiresSpecificSize�� */
	FIntPoint RequiredImageDimensions;

	/** ͼ���Ƿ���Ҫ�ض��ߴ磿 */
	bool bRequiresSpecificSize;

	/** ������ʾ����ߴ�Ĵ�����ʾС���� */
	TSharedPtr<class SErrorText> ErrorHintWidget;

	
};
