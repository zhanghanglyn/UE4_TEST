#include "ScenarioGraph.h"

UScenarioGraph::UScenarioGraph(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	Schema = UScenarioGraphSchema::StaticClass();
}