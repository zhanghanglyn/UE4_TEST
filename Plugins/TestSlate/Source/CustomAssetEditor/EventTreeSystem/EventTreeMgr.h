#pragma once

#include "CoreMinimal.h"
#include "CustomAssetEditor/EventTreeSystem/NodesController/NodeControllerBase.h"
#include "CustomAssetEditor/EventTreeSystem/NodesController/Mgr/NodeControllerMgr.h"
#include "EventTreeMgr.generated.h"

/*
一个节点仅有一个控制器，但是一个控制器可能对应有多个组件？
*/
UCLASS()
class UEventTreeMgr : public UObject
{
	GENERATED_BODY()

public:
	//DECLARE_MULTICAST_DELEGATE_OneParam(  )

public:
	UEventTreeMgr(const FObjectInitializer& ObjectInitializer) :Super(ObjectInitializer) {};

	//根据路径获取Tree资源
	bool GetTreeAsset( FString Path );

	//开始循环树
	void StartRun();
	
	//开始下一个节点
	void PlayNext();

	void Finish();

	//完成本次循环清除数据等
	void Clear();

	//每个Controller完成时的回调
	UFUNCTION()
	void ControllerOverCallBack(FName ControllerCategory);


protected:
	//从Array中查找所有的链接节点，并且为其生成控制器，将控制器注册到本次节点事件中
	void CreateController(TArray<class UEdGraphNode*> LinkNodes);

protected:
	//Asset资源
	UPROPERTY()
	class UMyCustomAsset* TreeAsset;

	/** Graph for Tree */
	UPROPERTY()
	class UScenarioGraph* TreeGraph;

	/* 当前走到的节点 */
	UPROPERTY()
	class UEdGraphNode* CurNode;

	UPROPERTY()
	class URootNodes* RootNode;

	//本次事件节点运行中的Controller
	UPROPERTY()
	TArray<class UNodeControllerBase* > NodeControllers;

};