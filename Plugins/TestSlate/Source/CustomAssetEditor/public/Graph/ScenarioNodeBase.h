#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "Runtime/Engine/Classes/EdGraph/EdGraphNode.h"
#include "ScenarioNodeBase.generated.h"

UCLASS()
class UScenarioNodeBase : public UEdGraphNode
{
	GENERATED_UCLASS_BODY()

public:
	/* ���෽�����̳к��������������½ڵ� */
	virtual void AllocateDefaultPins();
};