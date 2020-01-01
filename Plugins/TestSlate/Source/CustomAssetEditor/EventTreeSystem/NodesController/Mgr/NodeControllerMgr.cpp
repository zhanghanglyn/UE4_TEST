#include "NodeControllerMgr.h"
#include "CustomAssetEditor/EventTreeSystem/NodesController/ActionNodeController.h"

UNodeControllerBase* FNodeControllerMgr::CreateController(UScenarioNodeNormal* Node)
{
	//如果是个Action节点
	if (Node->NodeCategory == FScenarioNodeUtil::NodeCategoryAction)
	{
		//test 先创建Base的controller
		UActionNodeController* NodeController = NewObject< UActionNodeController>();
		//NodeController->CurNode = Node;
		NodeController->InitController(Node);

		return NodeController;
	}
	else
	{

		UE_LOG(LogTemp, Warning, TEXT("None Control can be Create"));
	}

	return nullptr;
}