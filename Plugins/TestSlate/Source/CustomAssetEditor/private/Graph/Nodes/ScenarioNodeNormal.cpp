#include "ScenarioNodeNormal.h"


/************************************************************************/
/*	                   SScenarioNodeNormal                               */
/************************************************************************/
void SScenarioNodeNormal::Construct(const FArguments& InArgs, UEdGraphNode* InNode)
{
	//�������Hover��ʱ�����ʾ
	SetCursor(EMouseCursor::CardinalCross);

	GraphNode = InNode;

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


}

void SScenarioNodeNormal::CreatePinWidgets()
{

}

void SScenarioNodeNormal::AddPin(const TSharedRef<SGraphPin>& PinToAdd)
{

}






/************************************************************************/
/*	                   UScenarioNodeNormal                               */
/************************************************************************/

UScenarioNodeNormal::UScenarioNodeNormal(const FObjectInitializer& ObjectInitializer) :Super(ObjectInitializer)
{

}

void UScenarioNodeNormal::AllocateDefaultPins()
{

}




