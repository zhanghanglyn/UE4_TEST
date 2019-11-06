
#include "TreeNode.h"

STreeNode::STreeNode()
	: BgImageBrush(FCoreStyle::Get().GetBrush("Border"))
{

}

void STreeNode::Construct(const FArguments& InArgs, SCanvasTree* Tree)
{
	BgImageBrush = InArgs._ABgImageBrush;

	bFlipForRightToLeftFlowDirection = InArgs._AbFlipForRightToLeftFlowDirection.Get();

	BorderBackgroundColor = InArgs._ABorderBackgroundColor;

	bIsFocusable = InArgs._bIsFocusable.Get();

	ClickNodeCallDelegate = InArgs._ClickNodeCallBack;

	UpNodeCallDelegate = InArgs._UpNodeCallBack;

	//设置Tree的指针
	CanvasTree = Tree;
	ChildNode = nullptr;
	ParentNode = nullptr;

	//19.11.04 先暂时定死设计尺寸
	DesiredSizeScale = FVector2D(100, 60);

	//设置连线点为控件中心
	CenterPosition = FVector2D(DesiredSizeScale.Get().X / 2, DesiredSizeScale.Get().Y / 2);

	this->ChildSlot
	//.HAlign(InArgs._HAlign)
	//.VAlign(InArgs._VAlign)
	//.Padding(InArgs._Padding)
	[
		InArgs._Content.Widget
	];
}

int32 STreeNode::OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const
{

 	const FSlateBrush* BrushResource = BgImageBrush.Get();
	const bool bEnabled = ShouldBeEnabled(bParentEnabled);

	if (BrushResource && BrushResource->DrawAs != ESlateBrushDrawType::NoDrawType)
	{
		const bool bShowDisabledEffect = true;  //就默认设置显示消失特效
		const ESlateDrawEffect DrawEffects = (bShowDisabledEffect && !bEnabled) ? ESlateDrawEffect::DisabledEffect : ESlateDrawEffect::None;


		//在绘制列表中添加一个背景
		if (bFlipForRightToLeftFlowDirection && GSlateFlowDirection == EFlowDirection::RightToLeft)
		{
			const FGeometry FlippedGeometry = AllottedGeometry.MakeChild(FSlateRenderTransform(FScale2D(-1, 1)));
			FSlateDrawElement::MakeBox(
				OutDrawElements,
				LayerId,
				FlippedGeometry.ToPaintGeometry(),
				BrushResource,
				DrawEffects,
				BrushResource->GetTint(InWidgetStyle) * InWidgetStyle.GetColorAndOpacityTint() * BorderBackgroundColor.Get().GetColor(InWidgetStyle)
			);
		}
		else
		{
			FSlateDrawElement::MakeBox(
				OutDrawElements,
				LayerId,
				AllottedGeometry.ToPaintGeometry(),
				BrushResource,
				DrawEffects,
				BrushResource->GetTint(InWidgetStyle) * InWidgetStyle.GetColorAndOpacityTint() * BorderBackgroundColor.Get().GetColor(InWidgetStyle)
			);
		}
	}
	
	return SCompoundWidget::OnPaint(Args, AllottedGeometry, MyCullingRect, OutDrawElements, LayerId, InWidgetStyle, bEnabled);

}

#pragma  optimize("", off)
FVector2D STreeNode::ComputeDesiredSize(float LayoutScaleMultiplier) const
{

	//return DesiredSizeScale.Get() * SCompoundWidget::ComputeDesiredSize(LayoutScaleMultiplier);
	return DesiredSizeScale.Get();
}
#pragma  optimize("", on)

void STreeNode::SetContent(TSharedRef< SWidget > InContent)
{
	ChildSlot
	[
		InContent
	];
}

const TSharedRef< SWidget >& STreeNode::GetContent() const
{
	return ChildSlot.GetWidget();
}

void STreeNode::ClearContent()
{
	ChildSlot.DetachWidget();
}

void STreeNode::SetBgImage(const TAttribute<const FSlateBrush*>& InBorderImage)
{
	if (!BgImageBrush.IdenticalTo(InBorderImage))
	{
		BgImageBrush = InBorderImage;
		Invalidate(EInvalidateWidget::LayoutAndVolatility);
	}
}

void STreeNode::SetBorderBackgroundColor(const TAttribute<FSlateColor>& InColorAndOpacity)
{
	if (!BorderBackgroundColor.IdenticalTo(InColorAndOpacity))
	{
		BorderBackgroundColor = InColorAndOpacity;
		Invalidate(EInvalidateWidget::PaintAndVolatility);
	}
}

/************************************************************************/
/*                     鼠标点击事件相关                            */
/************************************************************************/
bool STreeNode::SupportsKeyboardFocus() const
{
	// Buttons are focusable by default
	return bIsFocusable;
}

void STreeNode::OnFocusLost(const FFocusEvent& InFocusEvent)
{
	SCompoundWidget::OnFocusLost(InFocusEvent);

	//Release();
}

bool STreeNode::IsInteractable() const
{
	return true;
}

//鼠标点击时，记录一个生成状态，并且向上层发送，开始创建箭头
#pragma  optimize("", off)
FReply STreeNode::OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	FReply Reply = FReply::Unhandled();

	//判断下控件可见，并且是鼠标按下或者是点击事件时，处理函数
	if (IsEnabled() && MouseEvent.GetEffectingButton() == EKeys::LeftMouseButton || MouseEvent.IsTouchEvent())
	{
		PressedScreenSpacePosition = MouseEvent.GetScreenSpacePosition();
		FVector2D absolutePos = MyGeometry.GetAbsolutePosition();
		FVector2D ClickSizeInTree = PressedScreenSpacePosition - absolutePos;

		SetAbsoluteCenterLinePos(absolutePos);

		PressFunction(ClickSizeInTree);

		//向上冒泡！才能获取正确的点击位置
		Reply = FReply::Unhandled();
	}
	else if (IsEnabled() && MouseEvent.GetEffectingButton() == EKeys::RightMouseButton || MouseEvent.IsTouchEvent())
	{

	}
	Invalidate(EInvalidateWidget::Layout);

	return Reply;
}
#pragma  optimize("", on)

void STreeNode::PressFunction(FVector2D AbsolutePos)
{
	//传出回调
	ClickNodeCallDelegate.ExecuteIfBound(AbsolutePos,this);
}

FReply STreeNode::OnMouseMove(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	FReply Reply = FReply::Unhandled();

	return Reply;
}

/* 鼠标抬起时时判断是否当前Tree有选中节点，如果有：
	判断当前NODE是否为Tree的选中节点，如果是，不处理；如果不是：
	设置自己的父节点为Tree的当前选中节点,设置当前选中节点的子节点为自身
*/
FReply STreeNode::OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	FReply Reply = FReply::Unhandled();

	//判断下控件可见，并且是鼠标按下或者是点击事件时，处理函数
	if (IsEnabled() && MouseEvent.GetEffectingButton() == EKeys::LeftMouseButton || MouseEvent.IsTouchEvent())
	{
		PressedScreenSpacePosition = MouseEvent.GetScreenSpacePosition();
		FVector2D absolutePos = MyGeometry.GetAbsolutePosition();
		FVector2D ClickSizeInNode = PressedScreenSpacePosition - absolutePos;

		SetAbsoluteCenterLinePos(absolutePos);

		UpNodeCallDelegate.ExecuteIfBound(ClickSizeInNode, this);
	}

	return Reply;
}

void STreeNode::OnMouseEnter(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	
}

void STreeNode::OnMouseLeave(const FPointerEvent& MouseEvent)
{

}

/************************************************************************/
/*						         END							        */
/************************************************************************/
void STreeNode::SetAbsoluteCenterLinePos(FVector2D NodeStartPos)
{
	LinePos =(NodeStartPos + CenterPosition);
	UE_LOG(LogTemp, Warning, TEXT("Pos!!! : %f + %f"), LinePos.X, LinePos.Y);
}
FVector2D STreeNode::GetAbsoluteCenterLinePos()
{
	return LinePos;
}

void STreeNode::SetChildNode(STreeNode* _ChildNode)
{
	ChildNode = _ChildNode;
}

void STreeNode::SetParentNode(STreeNode* _ParentNode)
{
	ParentNode = _ParentNode;
}

STreeNode* STreeNode::GetChildNode()
{
	return ChildNode;
}

STreeNode* STreeNode::GetParentNode()
{
	return ParentNode;
}

/*********************
	数据相关	
*/
