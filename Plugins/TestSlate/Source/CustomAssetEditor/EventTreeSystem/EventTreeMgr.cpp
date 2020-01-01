#include "EventTreeMgr.h"
#include "MyCustomAsset.h"
#include "Runtime/Engine/Classes/EdGraph/EdGraphNode.h"
#include "RootNodes.h"
#include "ScenarioGraph.h"

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

//从Array中查找所有的链接节点，并且为其生成控制器，将控制器注册到本次节点事件中
void UEventTreeMgr::CreateController(TArray<UEdGraphNode *> LinkNodes)
{
	NodeControllers.Empty();

	for (TArray<UEdGraphNode *>::TConstIterator Iter = LinkNodes.CreateConstIterator(); Iter; ++Iter)
	{
		UScenarioNodeNormal* GraphNode = Cast<UScenarioNodeNormal>(*Iter);

		UNodeControllerBase* TempController = FNodeControllerMgr::CreateController(GraphNode);
		//绑定播放完毕回调
		TempController->OverDelegate.BindUObject(this, &UEventTreeMgr::ControllerOverCallBack);
		NodeControllers.Add(TempController);
	}
}

/*
	startRun的流程应该是，为该节点装配节点控制器，通过判断控制器的完成状态来进行下一节点的切换
*/
void UEventTreeMgr::StartRun()
{
	TArray<UEdGraphNode*> LinkNodes = RootNode->GetAllOutNodeLinked();

	//获取节点类型，根据节点类型分配Controller
	if (LinkNodes.Num() > 0)
		CreateController(LinkNodes);

}

/* 收到本次节点已完成后，获取当前节点的接下去的节点，重复环节。
*/
void UEventTreeMgr::PlayNext()
{
	//test
	Finish();
}

/* 收到一个Controller返回后，检测是否所有Controller状态均为已完成，如果不是则继续等待
*/
void UEventTreeMgr::ControllerOverCallBack(FName ControllerCategory)
{
	bool bFinishAll = true;
	for (TArray<UNodeControllerBase*>::TConstIterator iter = NodeControllers.CreateConstIterator();iter;++iter)
	{
		if ((*iter)->BControlOver == false)
		{
			bFinishAll = false;
			break;
		}
	}

	if (bFinishAll == true)
		PlayNext();
}

void UEventTreeMgr::Finish()
{
	UE_LOG(LogTemp, Warning, TEXT("本次事件播放结束~"));
	Clear();
}

/*清空需要清空的数据等*/
void UEventTreeMgr::Clear()
{
	NodeControllers.Empty();
}