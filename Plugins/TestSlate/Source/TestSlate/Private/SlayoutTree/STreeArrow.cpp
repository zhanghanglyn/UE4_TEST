#include "STreeArrow.h"

STreeArrow::STreeArrow()
{

}

void STreeArrow::Construct(const FArguments& InArgs)
{
	Size = InArgs._Size.Get();
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
			FSlateDrawElement::MakeLines(
				OutDrawElements,
				LayerId,
				AllottedGeometry.ToPaintGeometry(),
				ArrowList[ArrowCount],
				ESlateDrawEffect::None,
				FLinearColor::White,
				true,
				4
			);
			//画小箭头相关
			FVector2D endPos = ArrowList[ArrowCount][1];
			FVector2D startPos = ArrowList[ArrowCount][0];
			FVector2D DrawPos = FVector2D(startPos.X + (endPos.X - startPos.X)/2, startPos.Y + (endPos.Y - startPos.Y)/2);
			FVector2D DrawPosTest = FVector2D(DrawPos.X - 10, DrawPos.Y - 10);

			const FSlateBrush* BrushResource = FTestSlateStyle::Get().GetBrush("UI.ArrowBg");
			const FGeometry FlippedGeometry = AllottedGeometry.MakeChild(
				FSlateRenderTransform(FScale2D(0.05f, 0.05f) , DrawPosTest),FVector2D(0,0)
			);
			FSlateDrawElement::MakeRotatedBox(
				OutDrawElements,
				LayerId,
				FlippedGeometry.ToPaintGeometry(),
				BrushResource,
				ESlateDrawEffect::None,
				//ArrowDegrees,
				CalculateArrowRadians(ArrowList[ArrowCount][0] , ArrowList[ArrowCount][1]),
				TOptional<FVector2D>(),
				FSlateDrawElement::RelativeToElement,
				FLinearColor::White
				//FLinearColor::White
			);

		}
	}
	//再绘制当前正在进行的绘制
	if(CurArrow.Num() > 0)
	{
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

void STreeArrow::EndDrawArrow(FVector2D startPos, FVector2D endPos)
{
	/*if (CurArrow.Num() > 0 && CurArrow.Num() < 2)
		CurArrow.Add(endPos);
	else
		CurArrow[1] = endPos;*/

	CurArrow = { startPos, endPos };

	ArrowList.Add(CurArrow);
	CurArrow.Empty();

}

void STreeArrow::ClearCurDrawArrow()
{
	CurArrow.Empty();
}

float STreeArrow::CalculateArrowRadians( FVector2D startPos , FVector2D endPos) const
{
	//在线上面画一个小箭头！  计算一下ATAN 就是a/b 
	float atanVal = 0;
	float ArrowDegrees = 0;
	float LineA = (endPos.X - startPos.X);
	float LineB = (endPos.Y - startPos.Y);
	float LineC = UKismetMathLibrary::Distance2D(startPos, endPos);
	//如果是需要箭头向下是ATAN(A/B)！如果是需要箭头向上！则是ATAN(B/A)
	if (endPos.Y < startPos.Y) //此时为向上指
		ArrowDegrees = -UKismetMathLibrary::Atan(LineA / LineB) + FMath::DegreesToRadians(180);
	else if (endPos.Y > startPos.Y)
		ArrowDegrees = -UKismetMathLibrary::Atan(LineA / LineB);
	else if (endPos.X > startPos.X)
		ArrowDegrees = FMath::DegreesToRadians(90);
	else
		ArrowDegrees = FMath::DegreesToRadians(-90);

	return ArrowDegrees;
}


/*
	数据相关
*/
//打开该界面的时候，初始化线段数据
void STreeArrow::InitArrowData(TArray<TArray< FVector2D>> _ArrowList)
{
	ArrowList = _ArrowList;
}




