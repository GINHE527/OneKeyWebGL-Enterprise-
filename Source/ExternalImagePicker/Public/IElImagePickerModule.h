// 

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleInterface.h"
#include "Modules/ModuleManager.h"
#include "Editor/PropertyEditor/Public/PropertyHandle.h"

/**
 * ��ѡȡ��ͼ��ʱ������ί�С�
 * @param InChosenImage �û�ѡȡ��ͼ���·����
 * @param InTargetImage ��ѡ�����������Ŀ��ͼ���·����
 * @return ���ͼ��Ӧ�ñ�ˢ���򷵻�true
 */
DECLARE_DELEGATE_RetVal_TwoParams(bool, FOnExternalImagePicked, const FString& /** ��ѡͼ�� */, const FString& /** Ŀ��ͼ�� */);

/**
 * ���ڻ�ȡ��ʼѡȡͼ�����ʼ·��ʱ������ί�С�
 * @return ѡ������������ʼ��·��
 */
DECLARE_DELEGATE_RetVal(FString, FOnGetPickerPath);

/**
 * ���������ⲿͼ��ѡ����
 */
struct FElImagePickerConfiguration
{
public:
    FElImagePickerConfiguration()
        : MaxDisplayedImageDimensions(400.0f, 400.0f)
        , bRequiresSpecificSize(false)
    {
    }

    /** �ⲿͼ��洢�ڴ����϶�Ӧ��ͼ��·���� */
    FString TargetImagePath;

    /** ���Ŀ��ͼ�񲻴���ʱ��ʹ�õĴ����ϵ�ͼ��·���� */
    FString DefaultImagePath;

    /** ѡ������������ʼ��·�� */
    FOnGetPickerPath OnGetPickerPath;

    /** ��ѡȡ��ͼ��ʱ������ί�С� */
    FOnExternalImagePicked OnExternalImagePicked;

    /** ͼ����ʾӦ���޵ĳߴ硣�ᱣ�ֿ�߱ȡ� */
    FVector2D MaxDisplayedImageDimensions;

    /** ʵ��ͼ����Ҫ�ﵽ�ĳߴ磨����������bRequiresSpecificSize������˲����ᱻ���ԣ� */
    FIntPoint RequiredImageDimensions;

    /** ͼ���Ƿ���Ҫ�ض��ߴ磿 */
    bool bRequiresSpecificSize;

    /** ���Ŀ��ͼ�񲻴���ʱ��ʹ�õĴ����ϵ�ͼ��·���� */
    TArray<FString> FileExtensions;

    /** �����Ҫʹ�õ����Ծ�� */
    TSharedPtr<class IPropertyHandle> PropertyHandle;
    
};

/**
 * �����༭��ģ��Ĺ����ӿ�
 */
class IElImagePickerModule : public IModuleInterface
{
public:
    /**
     * ����һ��������ʾ�ͱ༭�����Ĳ�����
     *
     * @param �������ò���
     * @return ͼ��༭����
     */
    virtual TSharedRef<class SWidget> MakeEditorWidget(const FElImagePickerConfiguration& InConfiguration) = 0;

    /**
     * ��ȡ�ⲿͼ��ѡ����ģ��ʵ�������á�
     *
     * @return �ⲿͼ��ѡ����ģ������á�
     */
    static IElImagePickerModule& Get()
	{
		return FModuleManager::LoadModuleChecked<IElImagePickerModule>("ElImagePicker");
    }
};