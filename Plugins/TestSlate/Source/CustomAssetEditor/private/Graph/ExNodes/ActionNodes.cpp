#include "ActionNodes.h"

UActionNodes::UActionNodes()
{
	NodeName = "Action";
	bOpenGraph = false;
	NodeCategory = FScenarioNodeUtil::NodeCategoryAction;
}

TSharedPtr<SGraphNode> UActionNodes::CreateVisualWidget()
{
	SAssignNew(SNodeWidgetShared, SScenarioNodeNormal, this).NodeBgColor(FLinearColor::FromSRGBColor(FColor(78, 151, 131)))
		.CategoryTEXT(FText::FromString(L"互动节点"));

	return SNodeWidgetShared;
}