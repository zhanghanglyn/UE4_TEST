#include "STreeArrow.h"

STreeArrow::STreeArrow()
{

}

void STreeArrow::Construct(const FArguments& InArgs)
{
	//Size = InArgs._Size.Get();

	InitArrowData();
}

int32 STreeArrow::OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const
{
	//TArray<FVector2D> LinePoints = { FVector2D(0, 0), FVector2D(10,50),FVector2D(50,90) };
	for (int ArrowCount = 0 ; ArrowCount < ArrowList.Num() ; ArrowCount++ )
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
	
	return SCompoundWidget::OnPaint(Args, AllottedGeometry, MyCullingRect, OutDrawElements, LayerId, InWidgetStyle, bParentEnabled);
}

FVector2D STreeArrow::ComputeDesiredSize(float LayoutScaleMultiplier) const
{
	return SCompoundWidget::ComputeDesiredSize(LayoutScaleMultiplier);
}

//打开该界面的时候，初始化线段数据
void STreeArrow::InitArrowData()
{
	TArray<FVector2D> LinePoints = { FVector2D(0, 0), FVector2D(10,50),FVector2D(50,90) };
	TArray<FVector2D> LinePoints1 = { FVector2D(210,150),FVector2D(150,390) };
	TArray<FVector2D> LinePoints2 = { FVector2D(40,50), FVector2D(140,150)};
	ArrowList.Add(LinePoints);
	ArrowList.Add(LinePoints1);
	ArrowList.Add(LinePoints2);
}

void STreeArrow::TTTT()
{
	TArray<FVector2D> LinePoints = { FVector2D(0, 0), FVector2D(10,50),FVector2D(50,90) };
	ArrowList.Empty();
	ArrowList.Add( LinePoints);
}
