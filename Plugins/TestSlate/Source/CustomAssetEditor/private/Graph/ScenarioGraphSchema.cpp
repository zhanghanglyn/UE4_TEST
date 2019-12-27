#include "ScenarioGraphSchema.h"
#include "UObject/MetaData.h"
#include "UObject/UnrealType.h"
#include "UObject/TextProperty.h"
#include "Editor/GraphEditor/Public/GraphEditorActions.h"
#include "Runtime/Slate/Public/Framework/Commands/GenericCommands.h"
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
		new FScenarioSchemaAction(LOCTEXT("CustomStoryCategory", "Custom"), LOCTEXT("Nodes", "Normal Nodes"), FText::GetEmpty(), 0, nullptr)
		);

	ContextMenuBuilder.AddAction(NewSchemaAction);
}

//添加右键菜单的操作列表，意思是可以添加像：如果右点击到Pin上打开的菜单， 如果右点击到Node上打开的菜单等
void UScenarioGraphSchema::GetContextMenuActions(const UEdGraph* CurrentGraph, const UEdGraphNode* InGraphNode,
	const UEdGraphPin* InGraphPin, class FMenuBuilder* MenuBuilder, bool bIsDebugging) const
{
	check(CurrentGraph);

	//如果右键点击到节点上
	if (InGraphNode != nullptr)
	{
		MenuBuilder->BeginSection(FName("ScenarioNodeMenu"), LOCTEXT("NodeActionsMenuHeader", "Node Actions"));
		{
			MenuBuilder->AddMenuEntry(FGenericCommands::Get().Delete);
			MenuBuilder->AddMenuEntry(FGraphEditorCommands::Get().ReconstructNodes);
			MenuBuilder->AddMenuEntry(FGraphEditorCommands::Get().BreakNodeLinks);
		}
		MenuBuilder->EndSection();
	}
	Super::GetContextMenuActions(CurrentGraph, InGraphNode, InGraphPin, MenuBuilder, bIsDebugging);
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

void UScenarioGraphSchema::BreakNodeLinks(UEdGraphNode& TargetNode) const
{
	const FScopedTransaction Transaction(NSLOCTEXT("FSMAssetEditorNativeNames", "GraphEd_BreakNodeLinks", "Break Node Links"));

	Super::BreakNodeLinks(TargetNode);
}

void UScenarioGraphSchema::BreakPinLinks(UEdGraphPin& TargetPin, bool bSendsNodeNotification) const
{
	const FScopedTransaction Transaction(NSLOCTEXT("FSMAssetEditorNativeNames", "GraphEd_BreakPinLinks", "Break Pin Links"));

	Super::BreakPinLinks(TargetPin, bSendsNodeNotification);
}

void UScenarioGraphSchema::BreakSinglePinLink(UEdGraphPin* SourcePin, UEdGraphPin* TargetPin) const
{
	const FScopedTransaction Transaction(NSLOCTEXT("FSMAssetEditorNativeNames", "GraphEd_BreakSinglePinLink", "Break Pin Link"));

	Super::BreakSinglePinLink(SourcePin, TargetPin);
}

#undef LOCTEXT_NAMESPACE