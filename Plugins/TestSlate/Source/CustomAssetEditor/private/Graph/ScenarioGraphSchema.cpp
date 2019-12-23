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

UScenarioGraphSchema::UScenarioGraphSchema(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UScenarioGraphSchema::CreateDefaultNodesForGraph(UEdGraph& Graph) const
{
	FGraphNodeCreator<UScenarioNodeBase> NodeCreater(Graph);
	UScenarioNodeBase* Nodebase = NodeCreater.CreateNode();
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

}

/* 链接两个引脚 */
bool UScenarioGraphSchema::TryCreateConnection(UEdGraphPin* A, UEdGraphPin* B) const
{
	const bool bModified = UEdGraphSchema::TryCreateConnection(A, B);

	return bModified;
}


#undef LOCTEXT_NAMESPACE