#include "ScenarioFactories.h"
#include "ScenarioPin.h"


TSharedPtr<class SGraphPin> FScenarioPinFactory::CreatePin(class UEdGraphPin* Pin) const
{
	return SNew(SScenarioPin, Pin);
}