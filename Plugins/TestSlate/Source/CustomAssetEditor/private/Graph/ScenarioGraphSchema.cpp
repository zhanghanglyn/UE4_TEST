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

const FPinConnectionResponse UScenarioGraphSchema::CanCreateConnection(const UEdGraphPin* A, const UEdGraphPin* B) const
{
	return UEdGraphSchema::CanCreateConnection(A, B);
}

#undef LOCTEXT_NAMESPACE