#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "Runtime/Engine/Classes/EdGraph/EdGraphNode.h"
#include "Editor/GraphEditor/Public/SGraphNode.h"

//#include "ScenarioPin.h"
//#include "Runtime/Engine/Classes/EdGraph/EdGraph.h"

#include "ScenarioNodeNormal.generated.h"

/* 存储节点数据的部分 */
UCLASS()
class UScenarioNodeNormal : public UEdGraphNode
{
	GENERATED_BODY()

public:
	UScenarioNodeNormal();

	//~ Begin UEdGraphNode Interface
	
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
	virtual bool CanUserDeleteNode() const override { return true; };
	virtual void DestroyNode() override ;

	// called when this node is being renamed after a successful name validation
	virtual void OnRenameNode(const FString& NewName) override;

	/** 在图形编辑器或图形面板中创建表示此节点的可视小部件。如果没有实现，将使用默认的节点工厂。
		但我有点懒得写节点工厂还要注册了，就重载这个吧~
	*/
	virtual TSharedPtr<SGraphNode> CreateVisualWidget() override;

	// 取名的时候用来验证是否可以取，暂时不处理
	virtual TSharedPtr<class INameValidatorInterface> MakeNameValidator() const { return NULL; }
	/**
	* 粘贴节点的时候进行的操作，暂时先拜个早年吧
	*/
	virtual void PostPasteNode() { /*UE_LOG(LogTemp, Warning, TEXT(" Happy New Year"));*/ };
	//~ End

	/* 父类方法，继承后可以在里面添加新节点 */
	virtual void AllocateDefaultPins();

	//获取OutPutPin
	UEdGraphPin* GetOutPutPin();
	//获取InPutPin
	UEdGraphPin* GetInPutPin();

public:

	UPROPERTY(EditAnywhere, Category = "ScenarioGraphNode")
	FString TestData;

	UPROPERTY(EditAnywhere, Category = "ScenarioGraphNode")
	FString NodeName = "NormalGraph";

	static const int32 INPUT_PIN_INDEX;
	static const int32 OUTPUT_PIN_INDEX;
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