/**
@ 类描述
@Author zhangh
@Email  1
@Date   2019-10-31 14:31:35

1
*/


#pragma once
#include "TestSlate.h"
#include "TestSlate/Private/SVerticalBoxEx/SVerticalBoxEx.h"
#include "SAutoLayout.h"

class  SDetail : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SDetail){}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);
private:

	TSharedPtr<SVerticalBoxEx> LayoutPtr;
};