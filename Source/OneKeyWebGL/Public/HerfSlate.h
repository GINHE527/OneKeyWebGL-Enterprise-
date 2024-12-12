#pragma once
#include "CoreMinimal.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "Input/Reply.h"
#include "Types/SlateStructs.h"
#include "Widgets/SCompoundWidget.h"
#include "Brushes/SlateDynamicImageBrush.h"
#include "Widgets/Notifications/SErrorText.h"
//���ڳ��� �����Ӱ�ť
class SHerfSlate : public SCompoundWidget{

	public:
		SLATE_BEGIN_ARGS(SHerfSlate)
			{}
		SLATE_END_ARGS()

		void Construct(const FArguments & InArgs);
private:
	FReply OnButtonClick();
	static FString WebsiteSource;
};