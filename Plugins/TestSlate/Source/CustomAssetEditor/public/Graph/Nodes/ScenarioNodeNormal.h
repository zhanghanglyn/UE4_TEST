#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "Runtime/Engine/Classes/EdGraph/EdGraphNode.h"
#include "ScenarioNodeBase.h"
#include "Editor/GraphEditor/Public/SGraphNode.h"
#include "ScenarioNodeNormal.generated.h"

/* 存储节点数据的部分 */
UCLASS()
class UScenarioNodeNormal : public UEdGraphNode
{
	GENERATED_UCLASS_BODY()

public:

	//~ Begin UEdGraphNode Interface
	//创建一个新节点的时候调用，会在里面生成该节点的Instance


	//~ End

	/* 父类方法，继承后可以在里面添加新节点 */
	virtual void AllocateDefaultPins();


public:

	UPROPERTY(EditAnywhere, Category = DialogueGraphNode)
	FString TestData;

};

/* 继承SBorder的Node显示类 */
class SScenarioNodeNormal : public SGraphNode
{
public:
	SLATE_BEGIN_ARGS(SScenarioNodeNormal)
	{

	}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs , UEdGraphNode* InNode);

	/*更新Node已匹配Data更新*/
	virtual void UpdateGraphNode();
	
	/*创建Pin UI*/
	virtual void CreatePinWidgets();

	/* 把一个Pin添加到Node上，必须是新创建的Pin */
	virtual void AddPin(const TSharedRef<SGraphPin>& PinToAdd);

};