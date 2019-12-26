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
	//�������Hover��ʱ�����ʾ
	SetCursor(EMouseCursor::CardinalCross);

	GraphNode = InNode;
	UScenarioNodeNormal* NodeNormal = Cast<UScenarioNodeNormal>(InNode);
	if(NodeNormal != nullptr)
		NodeNormal->SetNodeWidget(this);

	//���½ڵ�
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
				//PIN AREA,���Ұ����ɵ�SVerticalBox����RightNodeBox
				+SOverlay::Slot()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				[
					SAssignNew(RightNodeBox, SVerticalBox)  //��Ȧ�������ҵ�RightNodeBox
				]

				//��������
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
							.BackgroundColor(this, &SScenarioNodeNormal::GetErrorColor)	//�д����ʱ���ȥȡ��ɫ
							.ToolTipText(this, &SScenarioNodeNormal::GetErrorMsgToolTip)
						]
						//�������򣬿ɵ������
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

	//����¶������Widget������
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

/* ��Ϊ��Ȧ�����ҵ�RightNode~���� Input��OutPut�Ͷ�����OutPut�� */
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

	OutputPins.Add(PinToAdd);   //��������OutPutPins�б���
}

/////////////�ⲿ�������
void SScenarioNodeNormal::UpdateNodeNmae(FString NodeName)
{
	InlineEditableText->SetText(NodeName);
}

/************************************************************************/
/*	                   UScenarioNodeNormal                               */
/************************************************************************/

UScenarioNodeNormal::UScenarioNodeNormal()
{

}

//��Detail��ȡ����Ҳ���ԣ�
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
	CreatePin(EEdGraphPinDirection::EGPD_Input, TEXT("Normal"), TEXT("In"));
	CreatePin(EEdGraphPinDirection::EGPD_Output, TEXT("Root"), TEXT("Out"));
}

void UScenarioNodeNormal::OnRenameNode(const FString& NewName)
{
	NodeName = NodeName;

	//�ٸ���һ�½ڵ�,������EDGraph��Modify();
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

void UScenarioNodeNormal::SetNodeWidget(SScenarioNodeNormal* SNode)
{
	SNodeWidget = SNode;
}
 
//��Detail���Ա仯ʱ���� ����֮��ĺܶ�������������
void UScenarioNodeNormal::OnDetailUpdate()
{
	SNodeWidget->UpdateNodeNmae(NodeName);
}