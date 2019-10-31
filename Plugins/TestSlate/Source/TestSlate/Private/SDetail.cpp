
#include "SDetail.h"

#define  LOCTEXT_NAMESPACE "SDetail"

void SDetail::Construct(const FArguments& InArgs)
{
	this->ChildSlot
	[
		SNew(SVerticalBoxEx).ContentMargin(FMargin(20,50))
		+SVerticalBoxEx::Slot()
		.MaxHeight(40)
		[
			//SNew(SImage).Image(FTestSlateStyle::Get().GetBrush("UI.IMAGEtest1") )
			SNew(STextBlock).Text(FText::FromString(TEXT("测试属性2")))
		]
		+SVerticalBoxEx::Slot()
		.MaxHeight(40)
		[
			SNew(SButton)
		]
		//SAssignNew(LayoutPtr, SVerticalBoxEx)

	];
}

#undef   LOCTEXT_NAMESPACE