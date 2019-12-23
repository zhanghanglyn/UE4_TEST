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

	//~ Begin UEdGraphNode Interface
	//创建一个新节点的时候调用，会在里面生成该节点的Instance


	//~ End

	/* 父类方法，继承后可以在里面添加新节点 */
	virtual void AllocateDefaultPins();


};