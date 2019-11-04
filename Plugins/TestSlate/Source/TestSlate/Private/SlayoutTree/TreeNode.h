/**
@ 类描述
@Author ZHANGH
@Email  @
@Date   2019-11-03 22:13:03

@实现一个树节点，该节点响应鼠标点击事件，并且有一个链表结构来表明自己的父节点和子节点，
@添加一个背景图片
@添加一个中间文字

*/


#pragma once
#include "TestSlate.h"

class  STreeNode : public SCompoundWidget
{
	DECLARE_DELEGATE_OneParam( ClickNodeCall , FVector2D)

public:
	SLATE_BEGIN_ARGS(STreeNode)
		:_ABgImageBrush(FCoreStyle::Get().GetBrush("Border"))
		, _ABorderBackgroundColor(FLinearColor::White)
		, _AbFlipForRightToLeftFlowDirection(false)
		, _bIsFocusable(true)
	{}
	SLATE_DEFAULT_SLOT(FArguments, Content)  //相当于绑定一个插槽叫做SLATE？

	SLATE_ATTRIBUTE( const FSlateBrush* , ABgImageBrush )
	SLATE_ATTRIBUTE(FSlateColor, ABorderBackgroundColor)
	SLATE_ATTRIBUTE(bool , AbFlipForRightToLeftFlowDirection)
	SLATE_ATTRIBUTE(bool, bIsFocusable)

	//绑定事件
	SLATE_EVENT(ClickNodeCall , ClickNodeCallBack)

	SLATE_END_ARGS()

	STreeNode();

	void Construct(const FArguments& InArgs);

	virtual void SetContent(TSharedRef< SWidget > InContent);
	//获取内容
	const TSharedRef< SWidget >& GetContent() const;
	//清除内容
	void ClearContent();
	//设置背景样式
	void SetBgImage(const TAttribute<const FSlateBrush*>& InBorderImage);
	/** Sets the color and opacity of the background image of this border. */
	void SetBorderBackgroundColor(const TAttribute<FSlateColor>& InColorAndOpacity);
	//设置大小 默认写死了 不设置算了
	//void SetDesiredSizeScale(const TAttribute<FVector2D>& InDesiredSizeScale);

public:
	// SWidget overrides
	virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;
	virtual bool SupportsKeyboardFocus() const override;
	virtual void OnFocusLost(const FFocusEvent& InFocusEvent) override;
	//virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;
	//virtual FReply OnKeyUp(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;
	virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;
	//virtual FReply OnMouseButtonDoubleClick(const FGeometry& InMyGeometry, const FPointerEvent& InMouseEvent) override;
	/*virtual FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;
	virtual FReply OnMouseMove(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;
	virtual void OnMouseEnter(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;
	virtual void OnMouseLeave(const FPointerEvent& MouseEvent) override;
	virtual void OnMouseCaptureLost(const FCaptureLostEvent& CaptureLostEvent) override;*/
	virtual bool IsInteractable() const override;
	//virtual bool ComputeVolatility() const override;

protected:
	// Begin SWidget overrides.
	//计算设计大小
	virtual FVector2D ComputeDesiredSize(float) const override;
	// End SWidget overrides.

protected:

	TAttribute<const FSlateBrush*> BgImageBrush;
	//是否可以成为焦点
	bool bIsFocusable;

	TAttribute<FSlateColor> BorderBackgroundColor;
	/** Flips the image if the localization's flow direction is RightToLeft */
	bool bFlipForRightToLeftFlowDirection;
	//设计尺寸大小
	TAttribute<FVector2D> DesiredSizeScale;

	//记录一个开始点击的位置
	FVector2D PressedScreenSpacePosition;

//事件委托
protected:
	ClickNodeCall ClickNodeCallDelegate;

//点击处理函数
protected:
	void PressFunction();

};