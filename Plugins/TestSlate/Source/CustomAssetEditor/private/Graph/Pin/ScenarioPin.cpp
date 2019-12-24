#include "ScenarioPin.h"

void SScenarioPin::Construct(const FArguments& InArgs, UEdGraphPin* InPin)
{
	this->SetCursor(EMouseCursor::Default);

	GraphPinObj = InPin;
	check(GraphPinObj != NULL);

	//�ж����Ƿ���Schema ��ʵҲ����Ҫ
	const UEdGraphSchema* Schema = GraphPinObj->GetSchema();
	check(Schema);

	//��������style
	CachedImg_Pin_Background = FEditorStyle::GetBrush(TEXT("Graph.StateNode.Pin.Background"));
	CachedImg_Pin_BackgroundHovered = FEditorStyle::GetBrush(TEXT("Graph.StateNode.Pin.BackgroundHovered"));

	SBorder::Construct(SBorder::FArguments()
		.BorderImage(this, &SScenarioPin::GetPinBorder )  //������Ƿ�HOVER�����������õ�����STYLE
		.BorderBackgroundColor(this , &SScenarioPin::GetPinColor)
		.OnMouseButtonDown( this , &SScenarioPin::OnPinMouseDown)	//
		.Cursor(this, &SScenarioPin::GetPinCursor)
	);
	//����OWENER
	TSharedRef<UEdGraphNode> TempNode = MakeShareable(InPin->GetOwningNode());

	//InPin->GetOuter()
	//SetOwner();

}

TSharedRef<SWidget> SScenarioPin::GetDefaultValueWidget()
{
	return SNew(STextBlock);
}