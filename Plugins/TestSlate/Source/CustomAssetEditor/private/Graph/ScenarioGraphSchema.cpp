#include "ScenarioGraphSchema.h"
#include "UObject/MetaData.h"
#include "UObject/UnrealType.h"
#include "UObject/TextProperty.h"
#if WITH_EDITOR
#include "Misc/ConfigCacheIni.h"
#include "UObject/UObjectHash.h"
#include "UObject/UObjectIterator.h"
#include "Framework/MultiBox/MultiBoxBuilder.h"
#include "ScopedTransaction.h"
#include "EditorCategoryUtils.h"
#endif

#define LOCTEXT_NAMESPACE "UScenarioGraphSchema"

//定义两个Pin的类型
const FName UScenarioGraphSchema::PC_Normal(TEXT("Normal"));
const FName UScenarioGraphSchema::PC_Root(TEXT("Root"));

UScenarioGraphSchema::UScenarioGraphSchema(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UScenarioGraphSchema::CreateDefaultNodesForGraph(UEdGraph& Graph) const
{
	//FGraphNodeCreator<UScenarioNodeBase> NodeCreater(Graph);
	//UScenarioNodeBase* Nodebase = NodeCreater.CreateNode();
	//NodeCreater.Finalize();
	FGraphNodeCreator<UScenarioNodeNormal> NodeCreater(Graph);
	UScenarioNodeNormal* Nodebase = NodeCreater.CreateNode();
	NodeCreater.Finalize();
}

void UScenarioGraphSchema::GetGraphContextActions(FGraphContextMenuBuilder& ContextMenuBuilder) const
{
	
	TSharedPtr<FScenarioSchemaAction> NewSchemaAction = TSharedPtr<FScenarioSchemaAction>(
		new FScenarioSchemaAction(LOCTEXT("CustomStoryCategory", "Custom"), LOCTEXT("AutoArrange", "Auto Arrange"), FText::GetEmpty(), 0, nullptr)
		);

	ContextMenuBuilder.AddAction(NewSchemaAction);
}

/* 判断两个引脚是否可以链接 */
const FPinConnectionResponse UScenarioGraphSchema::CanCreateConnection(const UEdGraphPin* A, const UEdGraphPin* B) const
{
	if(A->GetOwningNode() == B->GetOwningNode())
		return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW, TEXT("试试中文，这是同一个节点！"));

	else
		return FPinConnectionResponse(ECanCreateConnectionResponse::CONNECT_RESPONSE_BREAK_OTHERS_AB, TEXT(""));

}

/*链接两个引脚并通过中间节点 可以在此自定义中间节点，但是不写了*/
bool UScenarioGraphSchema::CreateAutomaticConversionNodeAndConnections(UEdGraphPin* A, UEdGraphPin* B) const
{
	UE_LOG(LogTemp, Warning, TEXT(" $#### CreateAutomaticConversionNodeAndConnections"));
	return false;
}

/* 链接两个引脚 */
bool UScenarioGraphSchema::TryCreateConnection(UEdGraphPin* A, UEdGraphPin* B) const
{
	//因为其实只写了RightNodeBox，所以要判断下，响应点击的引脚应该都是OutPut
	if (A->Direction == B->Direction)
		if (UScenarioNodeNormal* Node = Cast<UScenarioNodeNormal>(B->GetOwningNode()))
		{
			if (A->Direction == EGPD_Input)
			{
				B = Node->GetOutPutPin();
			}
			else
			{
				B = Node->GetInPutPin();
			}
		}

	const bool bModified = UEdGraphSchema::TryCreateConnection(A, B);

	return bModified;
}


#undef LOCTEXT_NAMESPACE