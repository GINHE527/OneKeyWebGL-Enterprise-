//���ڳ���Elua����֤
#pragma once
#include "CoreMinimal.h"
#include "Misc/Attribute.h"
#include "Input/Reply.h"
//�����޸�slate��ɫ��ͷ�ļ�
#include "Styling/SlateColor.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "Widgets/SWidget.h"
#include "Widgets/SCompoundWidget.h"

DECLARE_DELEGATE(DComfirm_Login)

class SConfirmWidget :public SCompoundWidget {
	// ��ͬ״̬������
	enum ESetupState
	{
		// 		��ʾȱ���ļ���״̬
		// 				MissingFiles,
		// 				// ��ʾ��Ҫ��������ܴӰ汾����ϵͳ�Ȼ�ȡ���°汾����״̬
		// 				NeedsCheckout,
		// 				// ��ʾ�ļ�Ϊֻ��״̬
		// 				ReadOnlyFiles,
		// 				// ��ʾ��׼���ÿ����޸ĵ�״̬
		// 				ReadyToModify
		//δ��¼��δ��֤��״̬
		NoLogin,
		//��¼����
		ErrorLogin,
		//δ��֤״̬(ǰ���Ѿ���¼)
		NoConfirm,
		//����֤״̬
		Confirmed
	};

	SLATE_BEGIN_ARGS(SConfirmWidget)
		{}

		// ����һ������������ΪFText�������ı���ʾ��֧�ֱ��ػ��ȹ��ܣ�������ƽ̨������
		//SLATE_ARGUMENT(FText, PlatformName)

		// ����һ���¼���ί�����ͣ��������ð�ť�����ʱ�ᴥ�����¼�����Ӧ��ί������ΪFSimpleDelegate
		SLATE_EVENT(FSimpleDelegate, FOnSetupClicked)

	SLATE_END_ARGS()

public:
	//slate ���캯����
	void Construct(const FArguments& InArgs);

	//��ȡһ����ʾ�Ƿ�׼���ü��������������Ƿ�����ƽ̨����Ҫ���������Ĳ����������ԣ�TAttribute����ʾ�ɰ󶨵��������Ի���Ӧ�仯�ȣ����ú���Ϊ����Ա�����������޸Ķ����ڲ�״̬
	TAttribute <bool> GetReadyToGoAttribute() const;

	// ����SWidget�ӿ�Ҫ��ʵ�ֵĺ���������ʵ�ֲ����Ķ�ʱ�����߼����������ʱ��仯���½�����ʾ�������
	// �����������������ò����ļ��β�����Ϣ��AllottedGeometry������ǰʱ�䣨InCurrentTime���Լ�ʱ������InDeltaTime��
	virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;

	DComfirm_Login DComfirm_Login_Declare;
private:
	//��ȡ��ǰ״̬
	int32 GetSetupStateAsInt() const;

	// �ж��Ƿ�׼���ü��������������Ƿ�����ƽ̨����Ҫ�����������ú���Ϊ����Ա�����������޸Ķ����ڲ�״̬
	bool IsReadyToGo() const;

	// ��ȡ���ڲ����߿����ɫ��FSlateColor����������Slate UI����б�ʾ��ɫ�����ú���Ϊ����Ա�����������޸Ķ����ڲ�״̬
	FSlateColor GetBorderColor() const;

	// ����������һ���������õĲ�����SWidget�������ڹ���һ����ʾ���ݣ������������ͼ�����ƣ�FName���ͣ�ͨ�����ڱ�ʶ��Դ�ȣ���Ҫ��ʾ����Ϣ�ı���FText���ͣ��Լ���ť��ص���Ϣ�ı���FText���ͣ�
	TSharedRef<SWidget> MakeRow(FName IconName, FText Message, FText ButtonMessage);

	// ����ť������ʱ���õĺ��������ڴ���ť���µ���ز���������һ��FReply���ͣ���ʾ�԰�ť���²�������Ӧ�������Ƿ����˸��¼����Ƿ�����˵����������
	FReply OnButtonPressed();

	// ����ָ���ļ�����������״̬������ESetupStateö�����ͱ�ʾ��״̬��������һ������ֵ�������ھ����Ƿ�ǿ�Ƹ���״̬��ѯ���ú���Ϊ����Ա�����������޸Ķ����ڲ�״̬
	ESetupState GetSetupStateBasedOnFile(bool bForceUpdate) const;

	// ������ΪCachedSetupState�Ļ��棨�������ڻ�������״̬�����Ϣ�������ظ���ѯ�������������һ������ֵ�������ھ����Ƿ�ǿ�Ƹ��»��棬
	void UpdateCache(bool bForceUpdate);

	// ���ڱ���Ŀ���ļ������ַ�����������������ƽ̨������ص�ĳ���ļ�������
	FString TargetFilename;

	// ���ڻ�������״̬�ı���������ΪESetupStateö�����ͣ�����֮ǰ��ѯ�����õ�������״̬��Ϣ�������ظ�����
	ESetupState CachedSetupState;

	// һ����ί�����͵ı��������ڰ󶨵����ð�ť�����ʱҪִ�еĺ������������ϵ������
	FSimpleDelegate FOnSetupClicked;
public:
	// ��ʾ��¼״̬
	bool isLogined;
	// ��ʾ��֤״̬
	bool isConfirmed;
	// check is login?
	bool login();
};