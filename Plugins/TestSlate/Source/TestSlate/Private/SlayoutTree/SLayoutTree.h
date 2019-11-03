/**
@ 类描述
@Author zhangh
@Email  1
@Date   2019-11-01 15:26:55

可在其中生成可以拖拽的树,与SCanvas类似
FSlot中会记录每一个子树的位置
可以在其中生成箭头

*/


#pragma once
#include "TestSlate.h"
#include "CoreMinimal.h"
#include "Misc/Attribute.h"
#include "Layout/Visibility.h"
#include "SlotBase.h"
#include "Widgets/SWidget.h"
#include "Layout/Children.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "Widgets/SPanel.h"

class FArrangedChildren;
class FPaintArgs;
class FSlateWindowElementList;

class  SCanvasTree : public SPanel
{
public:
	class FSlot : public TSlotBase<FSlot>
	{
	public:
		FSlot& Position(const TAttribute<FVector2D>& InPosition)
		{
			PositionAttr = InPosition;
			return *this;
		}

		FSlot& Size(const TAttribute<FVector2D>& InSize)
		{
			SizeAttr = InSize;
			return *this;
		}

		FSlot& HAlign(EHorizontalAlignment InHAlignment)
		{
			HAlignment = InHAlignment;
			return *this;
		}

		FSlot& VAlign(EVerticalAlignment InVAlignment)
		{
			VAlignment = InVAlignment;
			return *this;
		}

		/** Position */
		TAttribute<FVector2D> PositionAttr;

		/** Size */
		TAttribute<FVector2D> SizeAttr;

		/** Horizontal Alignment
		*  Given a top aligned slot, where '+' represents the
		*  anchor point defined by PositionAttr.
		*
		*   Left				Center				Right
			+ _ _ _ _            _ _ + _ _          _ _ _ _ +
			|		  |		   | 		   |	  |		    |
			| _ _ _ _ |        | _ _ _ _ _ |	  | _ _ _ _ |
		*
		*  Note: FILL is NOT supported.
		*/
		EHorizontalAlignment HAlignment;

		/** Vertical Alignment
		*   Given a left aligned slot, where '+' represents the
		*   anchor point defined by PositionAttr.
		*
		*   Top					Center			  Bottom
		*	+_ _ _ _ _          _ _ _ _ _		 _ _ _ _ _
		*	|		  |		   | 		 |		|		  |
		*	| _ _ _ _ |        +		 |		|		  |
		*					   | _ _ _ _ |		+ _ _ _ _ |
		*
		*  Note: FILL is NOT supported.
		*/
		EVerticalAlignment VAlignment;


		/** Default values for a slot. */
		FSlot()
			: TSlotBase<FSlot>()
			, PositionAttr(FVector2D::ZeroVector)
			, SizeAttr(FVector2D(1.0f, 1.0f))
			, HAlignment(HAlign_Left)
			, VAlignment(VAlign_Top)
		{ }
	};

	SLATE_BEGIN_ARGS(SCanvasTree){
		_Visibility = EVisibility::SelfHitTestInvisible;
	}
	SLATE_SUPPORTS_SLOT(SCanvasTree::FSlot)  //会在自身注册一个Slots，所以在Construct中，可以获取Slots
	SLATE_END_ARGS()

	SCanvasTree();

	void Construct(const FArguments& InArgs);

	static FSlot& Slot()
	{
		return *(new FSlot());
	}

	FSlot& AddSlot()
	{
		SCanvasTree::FSlot& NewSlot = *(new FSlot());
		this->Children.Add(&NewSlot);
		return NewSlot;
	}

	/**
	 * Removes a particular content slot.
	 *
	 * @param SlotWidget The widget in the slot to remove.
	 */
	int32 RemoveSlot(const TSharedRef<SWidget>& SlotWidget);

	/**
	 * Removes all slots from the panel.
	 */
	void ClearChildren();

public:

	// SWidget overrides
	virtual void OnArrangeChildren(const FGeometry& AllottedGeometry, FArrangedChildren& ArrangedChildren) const override;
	virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;
	virtual FChildren* GetChildren() override;


protected:
	// Begin SWidget overrides.
	virtual FVector2D ComputeDesiredSize(float) const override;
	// End SWidget overrides.

protected:
	/*
	TPanelChildren(SWidget* InOwner)
		: FChildren(InOwner)
		, bEmptying(false)
	{
	}  可见，初始化Children需要一个owner
	*/
	TPanelChildren<FSlot> Children;

};