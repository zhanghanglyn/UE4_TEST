#include "STreeArrow.h"

STreeArrow::STreeArrow()
{

}

void STreeArrow::Construct(const FArguments& InArgs)
{
	Size = InArgs._Size.Get();

	InitArrowData();
}


FVector2D STreeArrow::ComputeDesiredSize(float LayoutScaleMultiplier) const
{
	return Size.Get() * SCompoundWidget::ComputeDesiredSize(LayoutScaleMultiplier);
}

int32 STreeArrow::OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const
{
	//TArray<FVector2D> LinePoints = { FVector2D(0, 0), FVector2D(10,50),FVector2D(50,90) };
	if (ArrowList.Num() > 0)
	{
		for (int ArrowCount = 0; ArrowCount < ArrowList.Num(); ArrowCount++)
		{
			const FGeometry FlippedLineGeometry = AllottedGeometry.MakeChild(FSlateRenderTransform(FScale2D(1, 1)));
			FSlateDrawElement::MakeLines(
				OutDrawElements,
				LayerId,
				AllottedGeometry.ToPaintGeometry(),
				ArrowList[ArrowCount],
				ESlateDrawEffect::None,
				FLinearColor::White,
				true,
				5
			);
		}
	}
	//再绘制当前正在进行的绘制
	if(CurArrow.Num() > 0)
	{
		const FGeometry FlippedLineGeometry = AllottedGeometry.MakeChild(FSlateRenderTransform(FScale2D(1, 1)));
		FSlateDrawElement::MakeLines(
			OutDrawElements,
			LayerId,
			AllottedGeometry.ToPaintGeometry(),
			CurArrow,
			ESlateDrawEffect::None,
			FLinearColor::White,
			true,
			5
		);
	}
	
	return SCompoundWidget::OnPaint(Args, AllottedGeometry, MyCullingRect, OutDrawElements, LayerId, InWidgetStyle, bParentEnabled);
}

//鼠标事件暂时只向上冒泡！
FReply STreeArrow::OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	FReply Reply = FReply::Unhandled();

	return Reply;
}

FReply STreeArrow::OnMouseMove(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	return FReply::Unhandled();
}

FReply STreeArrow::OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	return FReply::Unhandled();
}


//打开该界面的时候，初始化线段数据
void STreeArrow::InitArrowData()
{
	/*TArray<FVector2D> LinePoints = { FVector2D(0, 0), FVector2D(10,50),FVector2D(50,90) };
	TArray<FVector2D> LinePoints1 = { FVector2D(210,150),FVector2D(150,390) };
	TArray<FVector2D> LinePoints2 = { FVector2D(40,50), FVector2D(140,150)};
	ArrowList.Add(LinePoints);
	ArrowList.Add(LinePoints1);
	ArrowList.Add(LinePoints2);*/
}

void STreeArrow::StartDrawArrow(FVector2D startPos)
{
	CurArrow.Empty();

	FVector2D StartPos = startPos;
	CurArrow.Add(StartPos);
}

void STreeArrow::MoveDrawArrow(FVector2D endPos)
{
	if (CurArrow.Num() > 0 && CurArrow.Num() < 2)
		CurArrow.Add(endPos);
	else
		CurArrow[1] = endPos;
}

void STreeArrow::EndDrawArrow(FVector2D endPos)
{
	if (CurArrow.Num() > 0 && CurArrow.Num() < 2)
		CurArrow.Add(endPos);
	else
		CurArrow[1] = endPos;

	ArrowList.Add(CurArrow);
	CurArrow.Empty();
}

















void STreeArrow::TTTT()
{
	TArray<FVector2D> LinePoints = { FVector2D(0, 0), FVector2D(10,50),FVector2D(50,90) };
	ArrowList.Empty();
	ArrowList.Add( LinePoints);
}
