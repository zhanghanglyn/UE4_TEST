#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "ScenarioNodeNormal.h"
#include "ActionNodes.generated.h"

UCLASS()
class UActionNodes : public UScenarioNodeNormal
{
	GENERATED_BODY()

public:

	UActionNodes();

	//~ Begin UEdGraphNode Interface
	//创建一个新节点的时候调用，会在里面生成该节点的Instance
	virtual TSharedPtr<SGraphNode> CreateVisualWidget() override;
	//~ End

};