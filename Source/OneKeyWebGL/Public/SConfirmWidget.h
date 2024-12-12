//用于承载Elua的验证
#pragma once
#include "CoreMinimal.h"
#include "Misc/Attribute.h"
#include "Input/Reply.h"
//用于修改slate颜色的头文件
#include "Styling/SlateColor.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "Widgets/SWidget.h"
#include "Widgets/SCompoundWidget.h"

DECLARE_DELEGATE(DComfirm_Login)

class SConfirmWidget :public SCompoundWidget {
	// 不同状态的类型
	enum ESetupState
	{
		// 		表示缺少文件的状态
		// 				MissingFiles,
		// 				// 表示需要检出（可能从版本控制系统等获取最新版本）的状态
		// 				NeedsCheckout,
		// 				// 表示文件为只读状态
		// 				ReadOnlyFiles,
		// 				// 表示已准备好可以修改的状态
		// 				ReadyToModify
		//未登录且未认证的状态
		NoLogin,
		//登录错误
		ErrorLogin,
		//未认证状态(前提已经登录)
		NoConfirm,
		//已认证状态
		Confirmed
	};

	SLATE_BEGIN_ARGS(SConfirmWidget)
		{}

		// 定义一个参数，类型为FText（用于文本表示，支持本地化等功能），代表平台的名称
		//SLATE_ARGUMENT(FText, PlatformName)

		// 定义一个事件（委托类型），当设置按钮被点击时会触发该事件，对应的委托类型为FSimpleDelegate
		SLATE_EVENT(FSimpleDelegate, FOnSetupClicked)

	SLATE_END_ARGS()

public:
	//slate 构造函数，
	void Construct(const FArguments& InArgs);

	//获取一个表示是否准备好继续操作（比如是否满足平台配置要求等情况）的布尔类型属性（TAttribute，表示可绑定到其他属性或响应变化等），该函数为常成员函数，不会修改对象内部状态
	TAttribute <bool> GetReadyToGoAttribute() const;

	// 这是SWidget接口要求实现的函数，用于实现部件的定时更新逻辑（比如根据时间变化更新界面显示等情况）
	// 传入参数包括分配给该部件的几何布局信息（AllottedGeometry）、当前时间（InCurrentTime）以及时间间隔（InDeltaTime）
	virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;

	DComfirm_Login DComfirm_Login_Declare;
private:
	//获取当前状态
	int32 GetSetupStateAsInt() const;

	// 判断是否准备好继续操作（比如是否满足平台配置要求等情况），该函数为常成员函数，不会修改对象内部状态
	bool IsReadyToGo() const;

	// 获取用于部件边框的颜色（FSlateColor类型用于在Slate UI框架中表示颜色），该函数为常成员函数，不会修改对象内部状态
	FSlateColor GetBorderColor() const;

	// 创建并返回一个共享引用的部件（SWidget），用于构建一行显示内容，传入参数包括图标名称（FName类型，通常用于标识资源等）、要显示的消息文本（FText类型）以及按钮相关的消息文本（FText类型）
	TSharedRef<SWidget> MakeRow(FName IconName, FText Message, FText ButtonMessage);

	// 当按钮被按下时调用的函数，用于处理按钮按下的相关操作，返回一个FReply类型，表示对按钮按下操作的响应（例如是否处理了该事件、是否进行了导航等情况）
	FReply OnButtonPressed();

	// 根据指定文件返回其设置状态（返回ESetupState枚举类型表示的状态），传入一个布尔值参数用于决定是否强制更新状态查询，该函数为常成员函数，不会修改对象内部状态
	ESetupState GetSetupStateBasedOnFile(bool bForceUpdate) const;

	// 更新名为CachedSetupState的缓存（可能用于缓存设置状态相关信息，避免重复查询等情况），传入一个布尔值参数用于决定是否强制更新缓存，
	void UpdateCache(bool bForceUpdate);

	// 用于保存目标文件名的字符串变量，可能是与平台配置相关的某个文件的名称
	FString TargetFilename;

	// 用于缓存设置状态的变量，类型为ESetupState枚举类型，保存之前查询或计算得到的设置状态信息，避免重复操作
	ESetupState CachedSetupState;

	// 一个简单委托类型的变量，用于绑定当设置按钮被点击时要执行的函数（或函数集合等情况）
	FSimpleDelegate FOnSetupClicked;
public:
	// 表示登录状态
	bool isLogined;
	// 表示认证状态
	bool isConfirmed;
	// check is login?
	bool login();
};