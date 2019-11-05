#include "SLayoutTree.h"

#define  LOCTEXT_NAMESPACE "SCanvasTree"

SCanvasTree::SCanvasTree() : Children(this), ArrowChildren(this), BorderImg(FCoreStyle::Get().GetBrush("Border"))
{
	SetCanTick(false);
	bCanSupportFocus = false;
	
}

void SCanvasTree::Construct(const FArguments& InArgs, FVector2D Position ,FVector2D Size)
{

	M_Position = Position;
	M_SIZE = Size;
	BorderImg = InArgs._BorderBrush;

	//加个背景（边框在底下用来标示）
	SCanvasTree::FSlot& NewSlot = *new SCanvasTree::FSlot();
	NewSlot
	[
		SNew(SImage).Image(FTestSlateStyle::Get().GetBrush("UI.TreeBg"))
	];
	ArrowChildren.Add(&NewSlot);

	//TSharedPtr< STreeArrow> mTreeArrowPanel;
	//添加一个箭头处理层，在背景层之上
	SCanvasTree::FSlot& ArrowSlot = *new SCanvasTree::FSlot();
	ArrowSlot
	[
		SAssignNew(mTreeArrowPanel , STreeArrow)
		//SNew(STreeArrow)
	];
	ArrowChildren.Add(&ArrowSlot);

	const int32 NumSlots = InArgs.Slots.Num();
	for (int32 SlotIndex = 0; SlotIndex < NumSlots; ++SlotIndex)
	{
		Children.Add(InArgs.Slots[SlotIndex]);
	}
}

int32 SCanvasTree::RemoveSlot(const TSharedRef<SWidget>& SlotWidget)
{
	for (int32 count = 0; count < Children.Num(); count++)
	{
		if (SlotWidget == Children.GetChildAt(count))
		{
			Children.RemoveAt(count);
			return count;
		}
	}

	return -1;
}

void SCanvasTree::ClearChildren()
{
	Children.Empty();
}

void SCanvasTree::OnArrangeChildren(const FGeometry& AllottedGeometry, FArrangedChildren& ArrangedChildren) const
{
	if (Children.Num() > 0)
	{
		for (int32 ChildIndex = 0; ChildIndex < Children.Num(); ++ChildIndex)
		{
			const SCanvasTree::FSlot& CurChild = Children[ChildIndex];
			//const FVector2D Size = CurChild.SizeAttr.Get();
			//19.11.04 使用TreeNode自身的size
			const FVector2D Size = CurChild.GetWidget()->GetDesiredSize();

			//Handle HAlignment
			FVector2D Offset(0.0f, 0.0f);

			switch (CurChild.HAlignment)
			{
			case HAlign_Center:
				Offset.X = -Size.X / 2.0f;
				break;
			case HAlign_Right:
				Offset.X = -Size.X;
				break;
			case HAlign_Fill:
			case HAlign_Left:
				break;
			}

			//handle VAlignment
			switch (CurChild.VAlignment)
			{
			case VAlign_Bottom:
				Offset.Y = -Size.Y;
				break;
			case VAlign_Center:
				Offset.Y = -Size.Y / 2.0f;
				break;
			case VAlign_Top:
			case VAlign_Fill:
				break;
			}

			// Add the information about this child to the output list (ArrangedChildren)
			ArrangedChildren.AddWidget(AllottedGeometry.MakeChild(
				// The child widget being arranged
				CurChild.GetWidget(),
				// Child's local position (i.e. position within parent)
				CurChild.PositionAttr.Get() + Offset,
				// Child's size
				Size
			));
		}
	}
}

void SCanvasTree::ArrangeArrow(const FGeometry& AllottedGeometry, FArrangedChildren& ArrangedChildren) const
{
	if (ArrowChildren.Num() > 1)
	{
		//先绘制一个背景

		const SCanvasTree::FSlot& BgChild = ArrowChildren[0];
		const FVector2D BgSize = M_SIZE;
		ArrangedChildren.AddWidget(AllottedGeometry.MakeChild(
			// The child widget being arranged
			BgChild.GetWidget(),
			// Child's local position (i.e. position within parent)
			BgChild.PositionAttr.Get(),
			// Child's size
			BgSize
		));
		//再绘制一个箭头层
		const SCanvasTree::FSlot& ArrowChild = ArrowChildren[1];
		ArrangedChildren.AddWidget(AllottedGeometry.MakeChild(
			// The child widget being arranged
			ArrowChild.GetWidget(),
			// Child's local position (i.e. position within parent)
			ArrowChild.PositionAttr.Get(),
			// Child's size
			BgSize
		));
	}
}


#pragma  optimize("", off)
int32 SCanvasTree::OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const
{
	/************************************************************************/
	/*							绘制箭头等相关！		 				 */
	/************************************************************************/
	//获取一次笔刷设置一个边框 ，若没有背景图的绘制，就无法响应点击
	{
		/*const FSlateBrush* BorderBrush = BorderImg.Get();

		if (BorderBrush && BorderBrush->DrawAs != ESlateBrushDrawType::NoDrawType)
		{
			const ESlateDrawEffect DrawEffects = ESlateDrawEffect::DisabledEffect;
			//判断下是否反向，但是现阶段不考虑
			if (GSlateFlowDirection == EFlowDirection::RightToLeft)
			{
				const FGeometry FlippedGeometry = AllottedGeometry.MakeChild(FSlateRenderTransform(FScale2D(-1, 1)));
				FSlateDrawElement::MakeBox(
					OutDrawElements,
					LayerId,
					FlippedGeometry.ToPaintGeometry(),
					BorderBrush,
					DrawEffects,
					BorderBrush->GetTint(InWidgetStyle) * InWidgetStyle.GetColorAndOpacityTint() * FLinearColor::White
				);
			}
			else
			{
				FSlateDrawElement::MakeBox(
					OutDrawElements,
					LayerId,
					AllottedGeometry.ToPaintGeometry(),
					BorderBrush,
					DrawEffects,
					BorderBrush->GetTint(InWidgetStyle) * InWidgetStyle.GetColorAndOpacityTint() * FLinearColor::White//BorderBackgroundColor.Get().GetColor(InWidgetStyle)
				);
			}
			//尝试画一条线
			TArray<FVector2D> LinePoints = { FVector2D( 0, 0 ), FVector2D( 10,50),FVector2D( 50,90) };
			const FGeometry FlippedLineGeometry = AllottedGeometry.MakeChild(FSlateRenderTransform(FScale2D(1, 1)));
			FSlateDrawElement::MakeLines(
				OutDrawElements,
				LayerId,
				AllottedGeometry.ToPaintGeometry(),
				LinePoints,
				ESlateDrawEffect::None,
				FLinearColor::White,
				true,
				5
			);
		}*/

		int32 ArrowLayerId = LayerId;

		FArrangedChildren ArrangedArrowChildren(EVisibility::Visible);
		this->ArrangeArrow(AllottedGeometry, ArrangedArrowChildren);

		const bool bForwardedEnabled = ShouldBeEnabled(bParentEnabled);

		const FPaintArgs NewArgs = Args.WithNewParent(this);

		for (int32 ChildIndex = 0; ChildIndex < ArrangedArrowChildren.Num(); ++ChildIndex)
		{
			FArrangedWidget& CurWidget = ArrangedArrowChildren[ChildIndex];

			if (!IsChildWidgetCulled(MyCullingRect, CurWidget))
			{
				const int32 CurWidgetsMaxLayerId = CurWidget.Widget->Paint(NewArgs, CurWidget.Geometry, MyCullingRect, OutDrawElements, ArrowLayerId + 1, InWidgetStyle, bForwardedEnabled);

				ArrowLayerId = FMath::Max(ArrowLayerId, CurWidgetsMaxLayerId);
			}
		}

		LayerId = ArrowLayerId;
	}

	/************************************************************************/
	/*							绘制箭头等相关！		 				 */
	/************************************************************************/

	FArrangedChildren ArrangedChildren(EVisibility::Visible);
	this->ArrangeChildren(AllottedGeometry, ArrangedChildren);

	// Because we paint multiple children, we must track the maximum layer id that they produced in case one of our parents
	// wants to an overlay for all of its contents.
	int32 MaxLayerId = LayerId;

	const bool bForwardedEnabled = ShouldBeEnabled(bParentEnabled);

	const FPaintArgs NewArgs = Args.WithNewParent(this);

	for (int32 ChildIndex = 0; ChildIndex < ArrangedChildren.Num(); ++ChildIndex)
	{
		FArrangedWidget& CurWidget = ArrangedChildren[ChildIndex];

		if (!IsChildWidgetCulled(MyCullingRect, CurWidget))
		{
			const int32 CurWidgetsMaxLayerId = CurWidget.Widget->Paint(NewArgs, CurWidget.Geometry, MyCullingRect, OutDrawElements, MaxLayerId + 1, InWidgetStyle, bForwardedEnabled);

			MaxLayerId = FMath::Max(MaxLayerId, CurWidgetsMaxLayerId);
		}
	}

	return MaxLayerId;
}
#pragma  optimize("", on)

void SCanvasTree::OnFocusLost(const FFocusEvent& InFocusEvent)
{
	SPanel::OnFocusLost(InFocusEvent);

	//Release();
}

FVector2D SCanvasTree::ComputeDesiredSize(float) const
{
	// Canvas widgets have no desired size -- their size is always determined by their container
	return FVector2D::ZeroVector;
	//return FVector2D(500, 500);
}

FChildren* SCanvasTree::GetChildren()
{
	return &Children;
}

/////////////////////鼠标点击事件相关

bool SCanvasTree::SupportsKeyboardFocus() const
{
	return true;
}

bool SCanvasTree::IsInteractable() const
{
	return true;
}

//判断如果是右键，则再点击位置生成一个TreeNode
#pragma  optimize("", off)
FReply SCanvasTree::OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	FReply Reply = FReply::Unhandled();

	//暂时写的右键为添加Tree
	if (IsEnabled() && MouseEvent.GetEffectingButton() == EKeys::RightMouseButton)
	{
		//计算一下生成位置，因为有一个相对位置的问题
		FVector2D CreatePos = MouseEvent.GetScreenSpacePosition();
		FVector2D absolutePos = MyGeometry.GetAbsolutePosition();
		FVector2D ClickSizeInTree = CreatePos - absolutePos;

		this->AddSlot().Position(ClickSizeInTree)[
			SNew(STreeNode).ClickNodeCallBack(this, &SCanvasTree::ClickNodeCall)
		];

		Reply = FReply::Handled();
	}
	//左键为开始画线，此事件因为TreeNode的冒泡事件
	if (IsEnabled() && MouseEvent.GetEffectingButton() == EKeys::LeftMouseButton && BStartDraw == true)
	{
		//计算一下生成位置，因为有一个相对位置的问题
		FVector2D CreatePos = MouseEvent.GetScreenSpacePosition();
		FVector2D absolutePos = MyGeometry.GetAbsolutePosition();
		FVector2D ClickSizeInTree = CreatePos - absolutePos;

		mTreeArrowPanel->StartDrawArrow(ClickSizeInTree);

		Reply = FReply::Handled();
	}

	return Reply;
}
#pragma  optimize("", on)

//收到Tree的点击事件
void SCanvasTree::ClickNodeCall(FVector2D Pos)
{
	//mTreeArrowPanel->StartDrawArrow(Pos);
	BStartDraw = true;
}

//当点击后鼠标移动！
FReply SCanvasTree::OnMouseMove(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	if (BStartDraw == false)
		return FReply::Unhandled();

	FReply Reply = FReply::Unhandled();
	FVector2D CreatePos = MouseEvent.GetScreenSpacePosition();
	FVector2D absolutePos = MyGeometry.GetAbsolutePosition();
	FVector2D ClickSizeInTree = CreatePos - absolutePos;

	mTreeArrowPanel->MoveDrawArrow(ClickSizeInTree);

	return FReply::Handled();
}

FReply SCanvasTree::OnMouseButtonUp(const FGeometry& InMyGeometry, const FPointerEvent& InMouseEvent)
{
	//左键抬起时结束本次绘制
	if (IsEnabled() && InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton && BStartDraw == true)
	{
		BStartDraw = false;
		FVector2D CreatePos = InMouseEvent.GetScreenSpacePosition();
		FVector2D absolutePos = InMyGeometry.GetAbsolutePosition();
		FVector2D ClickSizeInTree = CreatePos - absolutePos;

		mTreeArrowPanel->EndDrawArrow(ClickSizeInTree);
	}

	return FReply::Handled();
}

#undef   LOCTEXT_NAMESPACE