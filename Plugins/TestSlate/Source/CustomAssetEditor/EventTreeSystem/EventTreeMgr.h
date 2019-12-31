#pragma once

#include "CoreMinimal.h"
#include "EventTreeMgr.generated.h"

UCLASS()
class UEventTreeMgr : public UObject
{
	GENERATED_BODY()

public:
	UEventTreeMgr(const FObjectInitializer& ObjectInitializer) :Super(ObjectInitializer) {};

	//根据路径获取Tree资源
	bool GetTreeAsset( FString Path );

	//开始循环树
	void StartRun();
	
	//开始下一个节点
	void PlayNext();

	//完成本次循环清除数据等
	void Clear();

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
};