#pragma once
#include "CoreMinimal.h"
#include "NodeControllerBase.generated.h"

/*节点事件控制器的基类，在循环每一个Node的时候，会为Node装配一个控制器，即用即删*/
UCLASS()
class UNodeControllerBase : public UObject
{
	GENERATED_BODY()

public:
	UNodeControllerBase(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer){};

	//根据节点参数进行组件的装配

	//接受到Component的已经完成的回调

	//向Mgr发送本次节点已完成

protected:
	//当前Mgr绑定的Node
	class UEdGraphNode* CurNode;
};