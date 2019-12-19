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

UScenarioGraphSchema::UScenarioGraphSchema(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UScenarioGraphSchema::CreateDefaultNodesForGraph(UEdGraph& Graph) const
{

}

void UScenarioGraphSchema::GetGraphContextActions(FGraphContextMenuBuilder& ContextMenuBuilder) const
{
	UEdGraphSchema::GetGraphContextActions(ContextMenuBuilder);
#if WITH_EDITOR
	// Run thru all nodes and add any menu items they want to add
	for (TObjectIterator<UClass> ClassIt; ClassIt; ++ClassIt)
	{
		UClass* Class = *ClassIt;
		if (Class->IsChildOf(UEdGraphNode::StaticClass())) // && !Class->HasAnyClassFlags(CLASS_Abstract | CLASS_Deprecated))
		{
			const UEdGraphNode* ClassCDO = Class->GetDefaultObject<UEdGraphNode>();

			if (ClassCDO->CanCreateUnderSpecifiedSchema(this))
			{
				ClassCDO->GetMenuEntries(ContextMenuBuilder);
			}
		}
	}
#endif
}

const FPinConnectionResponse UScenarioGraphSchema::CanCreateConnection(const UEdGraphPin* A, const UEdGraphPin* B) const
{
	return UEdGraphSchema::CanCreateConnection(A, B);
}