#include "EventTreeMgr.h"
#include "MyCustomAsset.h"
#include "Runtime/Engine/Classes/EdGraph/EdGraphNode.h"
#include "RootNodes.h"
#include "ScenarioGraph.h"

/*UEventTreeMgr::UEventTreeMgr(const FObjectInitializer& ObjectInitializer) :Super(ObjectInitializer) 
{
	
}*/

bool UEventTreeMgr::GetTreeAsset(FString Path)
{
	UObject* TreeAssetTemp = LoadObject<UObject>(NULL, *Path);
	if (TreeAssetTemp)
	{
		TreeAsset = Cast<UMyCustomAsset>(TreeAssetTemp);
		if(TreeAsset)
		{
			TreeGraph = Cast<UScenarioGraph>(TreeAsset->StoryGraph);
			if (TreeGraph)
			{
				RootNode = TreeGraph->RootNode;
				return true;
			}
		}		
	}	
	return false;
}

/*
	startRun的流程应该是，为该节点装配节点控制器，通过判断控制器的完成状态来进行下一节点的切换
*/
void UEventTreeMgr::StartRun()
{
	RootNode->GetAllOutNodeLinked();

	//获取节点类型，根据节点类型分配Controller

}

/* 收到本次节点已完成后，获取当前节点的接下去的节点，重复环节。
*/
void UEventTreeMgr::PlayNext()
{

}

void UEventTreeMgr::Clear()
{

}