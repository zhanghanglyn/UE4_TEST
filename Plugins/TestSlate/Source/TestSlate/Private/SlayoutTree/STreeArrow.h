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
#include "TestSlate/Public/TestSlate.h"

class  STreeArrow : public SBorder
{
public:
	SLATE_BEGIN_ARGS(STreeArrow)
		:_Size(FVector2D::ZeroVector)
	{}
	SLATE_ATTRIBUTE(FVector2D , Size)
	SLATE_END_ARGS()

	STreeArrow();

	void Construct(const FArguments& InArgs);


public:
	virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;
	virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;
	virtual FReply OnMouseMove(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;
	virtual FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;

protected:
	// Begin SWidget overrides.
	virtual FVector2D ComputeDesiredSize(float) const override;
	// End SWidget overrides.

private:
	//与父类大小一致的尺寸
	TAttribute<FVector2D> Size;

	//线段的数据结构
	TArray<TArray< FVector2D>> ArrowList;

	//当前画线的数据,永远只有两个，一个起点，一个结束点
	TArray<FVector2D> CurArrow;

//箭头数据相关方法
public:
	//打开该界面的时候，初始化线段数据
	void InitArrowData();

	//开始画线，确定起点位置
	void StartDrawArrow( FVector2D startPos );
	//一边移动一边进行划线
	void MoveDrawArrow(FVector2D endPos);
	//鼠标抬起时结束画线
	void EndDrawArrow(FVector2D startPos, FVector2D endPos);

	//清空当前绘制线条
	void ClearCurDrawArrow();

	//测试代码
	void TTTT();
};