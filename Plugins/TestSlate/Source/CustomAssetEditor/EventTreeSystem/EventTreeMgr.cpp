#include "EventTreeMgr.h"
#include "MyCustomAsset.h"
#include "Runtime/Engine/Classes/EdGraph/EdGraphNode.h"
#include "RootNodes.h"
#include "EndNodes.h"
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
	//NodeControllers.Empty();
	Clear();

	for (TArray<UEdGraphNode *>::TConstIterator Iter = LinkNodes.CreateConstIterator(); Iter; ++Iter)
	{
		UScenarioNodeNormal* GraphNode = Cast<UScenarioNodeNormal>(*Iter);

		UNodeControllerBase* TempController = FNodeControllerMgr::CreateController(GraphNode);
		//绑定播放完毕回调
		TempController->OverDelegate.BindUObject(this, &UEventTreeMgr::ControllerOverCallBack);
		NodeControllers.Add(TempController);
	}
}

//检测是否是End节点！暂时认为，只有一个End
bool UEventTreeMgr::CheckEndNodes(TArray<class UEdGraphNode *> LinkNodes)
{
	for (TArray<UEdGraphNode *>::TConstIterator Iter = LinkNodes.CreateConstIterator(); Iter; ++Iter)
	{
		//如果是End节点，就结束了
		if (UEndNodes* EndNode = Cast<UEndNodes>(*Iter))
		{
			return true;
		}
	}

	return false;
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
#pragma optimize("",off)
void UEventTreeMgr::PlayNext()
{
	TArray<UEdGraphNode*> LinkNodes = CurNode->GetAllOutNodeLinked();

	//判断是否是结束节点
	if (CheckEndNodes(LinkNodes))
	{
		Finish();
		return;
	}
		

	if (LinkNodes.Num() > 0)
		CreateController(LinkNodes);
}

/* 收到一个Controller返回后，检测是否所有Controller状态均为已完成，如果不是则继续等待,其实一个节点应该只有一个Controller，所以，true的时候就Break就好了
*/
void UEventTreeMgr::ControllerOverCallBack(FName ControllerCategory)
{
	bool bFinishAll = false;

	for (TArray<UNodeControllerBase*>::TConstIterator iter = NodeControllers.CreateConstIterator();iter;++iter)
	{
		if ((*iter)->BControlOver == true)
		{
			bFinishAll = true;
			CurNode = (*iter)->CurNode;
			(*iter)->Clear();
			break;
		}
	}

	if (bFinishAll == true)
	{
		PlayNext();
	}
		
}
#pragma optimize("",on)

void UEventTreeMgr::Finish()
{
	UE_LOG(LogTemp, Warning, TEXT("本次事件播放结束~"));
	Clear();
}
#pragma optimize("",off)
/*清空需要清空的数据等*/
void UEventTreeMgr::Clear()
{
	//遍历所有Component然后清除
	for (TArray<UNodeControllerBase*>::TConstIterator iter = NodeControllers.CreateConstIterator(); iter; ++iter)
	{
		(*iter)->Clear();
	}

	NodeControllers.Empty();
}
#pragma optimize("",on)