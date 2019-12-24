#include "ScenarioNodeNormal.h"
#include "Runtime/SlateCore/Public/Widgets/SBoxPanel.h"
#include "ScenarioGraph.h"
#include "ScenarioPin.h"
#include "Runtime/Slate/Public/Widgets/Text/SInlineEditableTextBlock.h"

const int32 UScenarioNodeNormal::INPUT_PIN_INDEX = 0;
const int32 UScenarioNodeNormal::OUTPUT_PIN_INDEX = 1;

/************************************************************************/
/*	                   SScenarioNodeNormal                               */
/************************************************************************/
void SScenarioNodeNormal::Construct(const FArguments& InArgs, UEdGraphNode* InNode)
{
	//设置鼠标Hover的时候的显示
	SetCursor(EMouseCursor::CardinalCross);

	GraphNode = InNode;

	//更新节点
	UpdateGraphNode();
}

void SScenarioNodeNormal::UpdateGraphNode()
{
	InputPins.Empty();
	InputPins.Empty();

	// Reset variables that are going to be exposed, in case we are refreshing an already setup node.
	RightNodeBox.Reset();
	LeftNodeBox.Reset();

	FLinearColor TitleShadowColor( 0.6f ,0.6f , 0.6f);
	TSharedPtr<SErrorText> ErrorText;			
	TSharedPtr<SNodeTitle> NodeTitle = SNew(SNodeTitle, GraphNode);

	this->ContentScale.Bind(this, &SGraphNode::GetContentScale);
	this->GetOrAddSlot(ENodeZone::Center)
		.HAlign(HAlign_Center)
		.VAlign(VAlign_Center)
		[
			SNew(SBorder)
			.BorderImage(FEditorStyle::GetBrush("Graph.StateNode.Body"))
			.Padding(0)
			//.BorderBackgroundColor(this, &SGraphNodeAnimState::GetBorderBackgroundColor)
			.BorderBackgroundColor(FLinearColor::Gray)
			[
				SNew(SOverlay)

				//PIN AREA,并且把生成的SVerticalBox付给RightNodeBox
				+SOverlay::Slot()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				[
					SAssignNew(RightNodeBox, SVerticalBox)  //整圈！都是我的RightNodeBox
				]

				//名字区域
				+ SOverlay::Slot()
				.HAlign(HAlign_Center)
				.VAlign(VAlign_Center)
				.Padding(10.0f)
				[
					SNew(SBorder)
					.BorderImage(FEditorStyle::GetBrush("Graph.StateNode.ColorSpill"))
					.BorderBackgroundColor(TitleShadowColor)
					.HAlign(HAlign_Center)
					.VAlign(VAlign_Center)
					.Visibility(EVisibility::SelfHitTestInvisible)  //
					[
						SNew(SHorizontalBox)
						+ SHorizontalBox::Slot()
						.AutoWidth()
						[
							// POPUP ERROR MESSAGE
							SAssignNew(ErrorText, SErrorText)
							.BackgroundColor(this, &SScenarioNodeNormal::GetErrorColor)	//有错误的时候会去取颜色
							.ToolTipText(this, &SScenarioNodeNormal::GetErrorMsgToolTip)
						]
						//名字区域，可点击名字
						+SHorizontalBox::Slot()
						.Padding(FMargin(4.0f, 0.0f, 4.0f, 0.0f))
						[
							SNew(SVerticalBox)
							+ SVerticalBox::Slot()
							.AutoHeight()
							[
								SAssignNew(InlineEditableText, SInlineEditableTextBlock)
								.Style(FEditorStyle::Get(), "Graph.StateNode.NodeTitleInlineEditableText")
								.Text(NodeTitle.Get(), &SNodeTitle::GetHeadTitle)
								.OnVerifyTextChanged(this, &SScenarioNodeNormal::OnVerifyNameTextChanged)
								.OnTextCommitted(this, &SScenarioNodeNormal::OnNameTextCommited)
								.IsReadOnly(this, &SScenarioNodeNormal::IsNameReadOnly)
								.IsSelected(this, &SScenarioNodeNormal::IsSelectedExclusively)
							]
							+ SVerticalBox::Slot()
							.AutoHeight()
							[
								NodeTitle.ToSharedRef()
							]
						]
					]
				]

			]
		];

	//将暴露出来的Widget存起来
	ErrorReporting = ErrorText;
	ErrorReporting->SetError(ErrorMsg);

	CreatePinWidgets();
}

/*  */
void SScenarioNodeNormal::CreatePinWidgets()
{
	UScenarioNodeNormal* CurNode = CastChecked<UScenarioNodeNormal>(GraphNode);
	
	UEdGraphPin* CurPin = CurNode->GetOutPutPin();
	TSharedPtr< SScenarioPin> NewPin = SNew(SScenarioPin, CurPin);
	check(NewPin.IsValid());

	this->AddPin(NewPin.ToSharedRef());

}

/* 因为整圈都是我的RightNode~所以 Input和OutPut就都放在OutPut啦 */
void SScenarioNodeNormal::AddPin(const TSharedRef<SGraphPin>& PinToAdd)
{
	RightNodeBox->AddSlot()
		.AutoHeight()
		.HAlign(HAlign_Right)
		.VAlign(VAlign_Center)
		.FillHeight(1.0f)
		[
			PinToAdd
		];
	OutputPins.Add(PinToAdd);   //放入所有OutPutPins列表中
}

/************************************************************************/
/*	                   UScenarioNodeNormal                               */
/************************************************************************/

UScenarioNodeNormal::UScenarioNodeNormal()
{

}

//从Detail中取名字也可以！
FText UScenarioNodeNormal::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	return FText::FromString(NodeName);
}

void UScenarioNodeNormal::DestroyNode()
{
	/*UEdGraph* ParentGraph = GetGraph();
	check(ParentGraph);

	// Remove the node - this will break all links. Will be GC'd after this.
	ParentGraph->RemoveNode(this);*/
	UEdGraphNode::DestroyNode();
}

void UScenarioNodeNormal::AllocateDefaultPins()
{
	CreatePin(EEdGraphPinDirection::EGPD_Input, FName("TestPinIN"), TEXT("IN"));
	CreatePin(EEdGraphPinDirection::EGPD_Output, FName("TestPinOut"), TEXT("OUT"));
}

void UScenarioNodeNormal::OnRenameNode(const FString& NewName)
{
	NodeName = NodeName;

	//再更新一下节点,调用下EDGraph的Modify();
	UScenarioGraph* CurGraph = Cast< UScenarioGraph >(GetGraph());
	if (CurGraph != nullptr)
	{
		CurGraph->Modify();
	}
}

UEdGraphPin* UScenarioNodeNormal::GetOutPutPin()
{
	return Pins[OUTPUT_PIN_INDEX];
}

UEdGraphPin* UScenarioNodeNormal::GetInPutPin()
{
	return Pins[INPUT_PIN_INDEX];
}

TSharedPtr<SGraphNode> UScenarioNodeNormal::CreateVisualWidget()
{
	return SNew(SScenarioNodeNormal,this);
}