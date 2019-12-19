#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "EdGraph/EdGraph.h"
#include "ScenarioEditor.h"
#include "ScenarioGraphSchema.h"
#include "ScenarioGraph.generated.h"

class FScenarioEditor;

UCLASS()
class UScenarioGraph : public UEdGraph
{
	GENERATED_UCLASS_BODY()

public:
	//UScenarioGraph(const FObjectInitializer& ObjectInitializer);

	FScenarioEditor* ScenarioEditor;


};