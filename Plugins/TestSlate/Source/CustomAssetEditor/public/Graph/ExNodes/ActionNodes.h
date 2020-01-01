#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "ScenarioNodeNormal.h"
#include "CustomAssetEditor/EventTreeSystem/ActiveComponent/EventComponentBase.h"
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

public:
	//互动物品
	UPROPERTY(EditAnywhere, Category = "互动组件")
	TSoftObjectPtr <AActor> ActiveOjb;

	UPROPERTY(EditAnywhere, Category = "互动组件")
	TSubclassOf < UEventComponentBase> ActiveComponent;
};