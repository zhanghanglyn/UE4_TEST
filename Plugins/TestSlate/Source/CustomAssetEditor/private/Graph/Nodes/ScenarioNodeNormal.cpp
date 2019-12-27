#include "ScenarioNodeNormal.h"
#include "Runtime/SlateCore/Public/Widgets/SBoxPanel.h"
#include "ScenarioGraph.h"
#include "ScenarioPin.h"
#include "ScenarioGraph.h"
#include "ScenarioEditor.h"
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
	OwnerGraphNode = Cast<UScenarioNodeNormal>(InNode);

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
						.Padding(FMargin(20.0f, 0.0f, 20.0f, 0.0f))
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
	
	UEdGraphPin* CurPin = OwnerGraphNode->GetOutPutPin();
	TSharedPtr< SScenarioPin> NewPin = SNew(SScenarioPin, CurPin);
	check(NewPin.IsValid());

	this->AddPin(NewPin.ToSharedRef());

}

/* 因为整圈都是我的RightNode~所以 Input和OutPut就都放在OutPut啦 */
void SScenarioNodeNormal::AddPin(const TSharedRef<SGraphPin>& PinToAdd)
{
	PinToAdd->SetOwner(SharedThis(this));

	RightNodeBox->AddSlot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		.FillHeight(1.0f)
		[
			PinToAdd
		];

	OutputPins.Add(PinToAdd);   //放入所有OutPutPins列表中
}

//外部方法相关
void SScenarioNodeNormal::UpdateNodeNmae(FString NodeName)
{
	InlineEditableText->SetText(NodeName);
}

FReply SScenarioNodeNormal::OnMouseButtonDoubleClick(const FGeometry& InMyGeometry, const FPointerEvent& InMouseEvent)
{
	//会调用自身UNode的双击方法！
	OwnerGraphNode->DoubleClickNodeCall();

	if (InMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton))
	{
		OnDoubleClick.ExecuteIfBound(GraphNode);
		return FReply::Handled();
	}
	return FReply::Unhandled();
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

void UScenarioNodeNormal::AllocateDefaultPins()
{
	CreatePin(EEdGraphPinDirection::EGPD_Input, TEXT("Normal"), TEXT("In"));
	CreatePin(EEdGraphPinDirection::EGPD_Output, TEXT("Root"), TEXT("Out"));
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
	SAssignNew(SNodeWidgetShared, SScenarioNodeNormal, this);

	return SNodeWidgetShared;//SAssignNew(SNodeWidgetShared,SScenarioNodeNormal,this);
}

//双击节点的调用函数
void UScenarioNodeNormal::DoubleClickNodeCall()
{

	//(SNodeWidgetShared.Get())->UpdateNodeNmae("I HAVE BEEN DOUBLE");

	//双击打开一个Tab
	if (bOpenGraph)
	{
		if (UScenarioGraph* Graph = Cast<UScenarioGraph>(GetGraph()))
		{
			if (Graph->ScenarioEditor)
				Graph->ScenarioEditor->OpenInsideNodeGraphTab(this);
		}
	}
	
		

}

//当Detail属性变化时更新 可能之后的很多操作都在这儿了
void UScenarioNodeNormal::OnDetailUpdate()
{
	(SNodeWidgetShared.Get())->UpdateNodeNmae(NodeName);
}

/*删除节点的众多操作*/
void UScenarioNodeNormal::DestroyNode()
{

	UEdGraphNode::DestroyNode();
}