#include "ScenarioFactories.h"
#include "ScenarioPin.h"
#include "ScenarioGraphSchema.h"
#include "ScenarioNodeNormal.h"


TSharedPtr<class SGraphNode> FScenarioNodeFactory::CreateNode(class UEdGraphNode* InNode) const
{
	if ( auto CurNode = Cast< UScenarioNodeNormal >(InNode) )
		return SNew(SScenarioNodeNormal, CurNode);

	return nullptr;
}

TSharedPtr<class SGraphPin> FScenarioPinFactory::CreatePin(class UEdGraphPin* Pin) const
{
	if (Pin->PinType.PinCategory == UScenarioGraphSchema::PC_Normal)
		return SNew(SScenarioPin, Pin);
	
	return nullptr;
}
