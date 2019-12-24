#include "ScenarioPin.h"

void SScenarioPin::Construct(const FArguments& InArgs, UEdGraphPin* InPin)
{
	this->SetCursor(EMouseCursor::Default);

	GraphPinObj = InPin;
	check(GraphPinObj != NULL);

	//判断下是否有Schema 其实也不需要
	const UEdGraphSchema* Schema = GraphPinObj->GetSchema();
	check(Schema);

	//设置两个style
	CachedImg_Pin_Background = FEditorStyle::GetBrush(TEXT("Graph.StateNode.Pin.Background"));
	CachedImg_Pin_BackgroundHovered = FEditorStyle::GetBrush(TEXT("Graph.StateNode.Pin.BackgroundHovered"));

	SBorder::Construct(SBorder::FArguments()
		.BorderImage(this, &SScenarioPin::GetPinBorder )  //会根据是否被HOVER返回上面设置的两个STYLE
		.BorderBackgroundColor(this , &SScenarioPin::GetPinColor)
		.OnMouseButtonDown( this , &SScenarioPin::OnPinMouseDown)	//
		.Cursor(this, &SScenarioPin::GetPinCursor)
	);
	//设置OWENER
	TSharedRef<UEdGraphNode> TempNode = MakeShareable(InPin->GetOwningNode());

	//InPin->GetOuter()
	//SetOwner();

}

TSharedRef<SWidget> SScenarioPin::GetDefaultValueWidget()
{
	return SNew(STextBlock);
}