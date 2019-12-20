#include "ScenarioSchemaAction.h"
#include "ScenarioNodeBase.h"

#define LOCTEXT_NAMESPACE "ScenarioSchemaAction"

/* �ڵ���Action��ֻ��ʱд���������ӹ����� */
UEdGraphNode* FScenarioSchemaAction::PerformAction(class UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2D Location, bool bSelectNewNode /* = true */)
{
	UEdGraphNode* ResultNode = nullptr;

#if WITH_EDITOR
	// If there is a template, we actually use it
	if (NodeTemplate != nullptr)
	{
		const FScopedTransaction Transaction(LOCTEXT("AddNode", "Add Node"));
		ParentGraph->Modify();
		if (FromPin)
		{
			FromPin->Modify();
		}
		//ResultNode = CreateNode(ParentGraph, FromPin, Location, NodeTemplate);
	}
#endif

	ResultNode = CreateNode(ParentGraph, FromPin, Location, NodeTemplate, bSelectNewNode);

	return ResultNode;
}

/*Ĭ������ʱ��ΪTemplateΪnull*/
UEdGraphNode* FScenarioSchemaAction::CreateNode(UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2D Location, class UEdGraphNode* InNodeTemplate , bool bSelectNewNode)
{
	UEdGraphNode* ResultNode;
	if (InNodeTemplate == nullptr)
	{
		FGraphNodeCreator<UScenarioNodeBase> NodeCreater(*ParentGraph);
		ResultNode = NodeCreater.CreateNode(bSelectNewNode);
		NodeCreater.Finalize();
	}
	else
	{
		ResultNode = DuplicateObject<UEdGraphNode>(InNodeTemplate, ParentGraph);
	}
		
	ResultNode->SetFlags(RF_Transactional);
	ResultNode->AutowireNewNode(FromPin);

	ResultNode->NodePosX = Location.X;
	ResultNode->NodePosY = Location.Y;

	return ResultNode;
}

#undef LOCTEXT_NAMESPACE