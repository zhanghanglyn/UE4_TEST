#include "SLayoutTree.h"

#define  LOCTEXT_NAMESPACE "SCanvasTree"

SCanvasTree::SCanvasTree() : Children(this)
{
	SetCanTick(false);
	bCanSupportFocus = false;
	
}

void SCanvasTree::Construct(const FArguments& InArgs, FVector2D Position ,FVector2D Size)
{

	M_Position = Position;
	M_SIZE = Size;
	BorderImg = InArgs._BorderBrush;

	//Ҳ���ԼӸ��������߿��ڵ���������ʾ��
	SCanvasTree::FSlot& NewSlot = *new SCanvasTree::FSlot();
	NewSlot
		[
			SNew(SImage).Image(FTestSlateStyle::Get().GetBrush("UI.TreeBg"))
		];
	Children.Add(&NewSlot);

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
		//���⴦���±���ͼ
		{
			const SCanvasTree::FSlot& BgChild = Children[0];
			const FVector2D BgSize = M_SIZE;
			ArrangedChildren.AddWidget(AllottedGeometry.MakeChild(
				// The child widget being arranged
				BgChild.GetWidget(),
				// Child's local position (i.e. position within parent)
				BgChild.PositionAttr.Get(),
				// Child's size
				BgSize
			));
		}

		for (int32 ChildIndex = 1; ChildIndex < Children.Num(); ++ChildIndex)
		{
			const SCanvasTree::FSlot& CurChild = Children[ChildIndex];
			//const FVector2D Size = CurChild.SizeAttr.Get();
			//19.11.04 ʹ��TreeNode�����size
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

#pragma  optimize("", off)
int32 SCanvasTree::OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const
{
	/************************************************************************/
	/*							���Ƽ�ͷ����أ�		 				 */
	/************************************************************************/
	//��ȡһ�α�ˢ����һ���߿� ����û�б���ͼ�Ļ��ƣ����޷���Ӧ���
	const FSlateBrush* BorderBrush = BorderImg.Get();

	if (BorderBrush && BorderBrush->DrawAs != ESlateBrushDrawType::NoDrawType)
	{
		const ESlateDrawEffect DrawEffects = ESlateDrawEffect::DisabledEffect;
		//�ж����Ƿ��򣬵����ֽ׶β�����
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
	}

	//FArrangedChildren ArrangedChildren(EVisibility::Visible);
	//this->ArrangeChildren(AllottedGeometry, ArrangedChildren);
	//LayerId = 

	/************************************************************************/
	/*							���Ƽ�ͷ����أ�		 				 */
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
	//return FVector2D::ZeroVector;
	return FVector2D(500, 500);
}

FChildren* SCanvasTree::GetChildren()
{
	return &Children;
}

/////////////////////������¼����

bool SCanvasTree::SupportsKeyboardFocus() const
{
	return true;
}

bool SCanvasTree::IsInteractable() const
{
	return true;
}

//�ж�������Ҽ������ٵ��λ������һ��TreeNode
#pragma  optimize("", off)
FReply SCanvasTree::OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	FReply Reply = FReply::Unhandled();

	if (IsEnabled() && MouseEvent.GetEffectingButton() == EKeys::RightMouseButton)
	{
		//����һ������λ�ã���Ϊ��һ�����λ�õ�����
		FVector2D CreatePos = MouseEvent.GetScreenSpacePosition();
		FVector2D absolutePos = MyGeometry.GetAbsolutePosition();
		FVector2D ClickSizeInTree = CreatePos - absolutePos;

		this->AddSlot().Position(ClickSizeInTree)[
			SNew(STreeNode).ClickNodeCallBack(this, &SCanvasTree::ClickNodeCall)
		];
		Reply = FReply::Handled();
	}

	return Reply;
}
#pragma  optimize("", on)

//#pragma  optimize("", off)
void SCanvasTree::ClickNodeCall(FVector2D Pos)
{

}
//#pragma  optimize("", on)

#undef   LOCTEXT_NAMESPACE