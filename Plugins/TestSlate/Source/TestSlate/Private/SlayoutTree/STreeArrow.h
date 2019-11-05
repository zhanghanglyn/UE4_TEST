/**
@ 类描述
@Author zhangh
@Email  1
@Date   2019-11-05 15:49:31

在SCanvasTree中专门用来显示箭头的层，基本不用继承复杂功能（美好愿望）
根据传入的数据在对应位置生成箭头线
大小与父SCanvasTree一致
*/


#pragma once
#include "TestSlate.h"

class  STreeArrow : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(STreeArrow){}
	//SLATE_ATTRIBUTE(FVector2D , Size)
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

	STreeArrow();

public:
	virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;

protected:
	// Begin SWidget overrides.
	virtual FVector2D ComputeDesiredSize(float) const override;
	// End SWidget overrides.

private:
	//与父类大小一致的尺寸
	//TAttribute<FVector2D> Size;

	//线段的数据结构
	TArray<TArray< FVector2D>> ArrowList;

//箭头数据相关方法
public:
	//打开该界面的时候，初始化线段数据
	void InitArrowData();
	//添加一条Arrow
	void TTTT();
};