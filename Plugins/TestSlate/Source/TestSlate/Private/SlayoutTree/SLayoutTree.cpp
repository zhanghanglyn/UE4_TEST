#include "SLayoutTree.h"

#define  LOCTEXT_NAMESPACE "SCanvasTree"

SCanvasTree::SCanvasTree() : Children(this)
{
	SetCanTick(false);
	bCanSupportFocus = false;
}

void SCanvasTree::Construct(const FArguments& InArgs)
{
	//Ҳ���ԼӸ��������߿��ڵ���������ʾ��

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
			const FVector2D Size = CurChild.SizeAttr.Get();

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

int32 SCanvasTree::OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const
{
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

FVector2D SCanvasTree::ComputeDesiredSize(float) const
{
	// Canvas widgets have no desired size -- their size is always determined by their container
	return FVector2D::ZeroVector;
}

FChildren* SCanvasTree::GetChildren()
{
	return &Children;
}


#undef   LOCTEXT_NAMESPACE