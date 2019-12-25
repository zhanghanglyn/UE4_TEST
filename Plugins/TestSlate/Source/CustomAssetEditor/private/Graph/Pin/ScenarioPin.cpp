#include "ScenarioPin.h"
#include "Runtime/SlateCore/Public/Widgets/SBoxPanel.h"
#include "Runtime/Slate/Public/Widgets/Text/SInlineEditableTextBlock.h"

void SScenarioPin::Construct(const FArguments& InArgs, UEdGraphPin* InPin)
{
	this->SetCursor(EMouseCursor::Default);

	bShowLabel = true;

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

	/*SNew(SBorder)
		.BorderImage(FEditorStyle::GetBrush("Graph.StateNode.Body"))
		.Padding(0)
		.BorderBackgroundColor(FLinearColor::Green)
		[
			SNew(SVerticalBox)
			+ SVerticalBox::Slot()
			.AutoHeight()
			[
			SNew(SInlineEditableTextBlock)
			.Style(FEditorStyle::Get(), "Graph.StateNode.NodeTitleInlineEditableText")
			.Text(FText::FromString("aafdafdafdaf"))
			]
		];*/
}

TSharedRef<SWidget> SScenarioPin::GetDefaultValueWidget()
{
	return SNew(STextBlock);
}