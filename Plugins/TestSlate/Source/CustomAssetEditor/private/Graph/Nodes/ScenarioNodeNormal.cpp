#include "ScenarioNodeNormal.h"


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




