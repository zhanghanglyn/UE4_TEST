#include "NodeControllerMgr.h"
#include "ActionNodeController.h"

UNodeControllerBase* FNodeControllerMgr::CreateController(UScenarioNodeNormal* Node)
{
	//如果是个Action节点
	if (GraphNode->NodeCategory == FScenarioNodeUtil::NodeCategoryAction)
	{
		//test 先创建Base的controller
		UNodeControllerBase* NodeController = NewObject< UNodeControllerBase>();
		NodeController->CurNode = Node;

		return NodeController;
	}
	else
	{

		UE_LOG(LogTemp, Warning, TEXT("None Control can be Create"));
	}

	return nullptr;
}