#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "UObject/Object.h"
#include "Runtime/Engine/Classes/EdGraph/EdGraphSchema.h"
#include "Runtime/CoreUObject/Public/UObject/Class.h"
#include "EdGraph/EdGraphNode.h"
#include "EdGraph/EdGraphPin.h"
#include "AssetData.h"
#include "UObject/ObjectKey.h"
#include "ScenarioGraphSchema.generated.h"

UCLASS()
class UScenarioGraphSchema : public UEdGraphSchema
{
	GENERATED_UCLASS_BODY()

public:
	/*
	使用任何默认节点填充新图形
	*
	* @param图形用于添加默认节点
	* @param contextclass如果指定，图形终端将使用这个类来搜索签名的上下文(即接口函数)
	*/
	virtual void CreateDefaultNodesForGraph(UEdGraph& Graph) const;
	/*
	获取当右键点击图形时可以进行的所有操作
	GetGraphContextActions方法可以告诉蓝图在右键时哪些类能显示，即能创建的节点类型
	*/
	virtual void GetGraphContextActions(FGraphContextMenuBuilder& ContextMenuBuilder) const;
	/*
	确定是否可以在两个引脚之间创建连接。
	*
	* @param是第一个pin码。
	* @param b第二个引脚。
	*
	* @ @如果连接是合法的，返回一个空字符串，否则会出现描述连接失败原因的消息。
	*/
	virtual const FPinConnectionResponse CanCreateConnection(const UEdGraphPin* A, const UEdGraphPin* B) const;
};