﻿#include "ActionNodes.h"


const FName UActionNodes::ComponentPropertyName = "ActiveComponent";

UActionNodes::UActionNodes()
{
	NodeName = "Action";
	bOpenGraph = false;
	NodeCategory = FScenarioNodeUtil::NodeCategoryAction;

	//if (DataBase == nullptr)
	//	DataBase = NewObject<UComponentNodeDataBase>();
	if (ActiveComponent)
		CurComponentName = FActiveComponentMgr::GetEventComponentCategory(ActiveComponent);
}

TSharedPtr<SGraphNode> UActionNodes::CreateVisualWidget()
{
	SAssignNew(SNodeWidgetShared, SScenarioNodeNormal, this).NodeBgColor(FLinearColor::FromSRGBColor(FColor(78, 151, 131)))
		.CategoryTEXT(FText::FromString(L"互动节点"));

	return SNodeWidgetShared;
}

/*
	如果更新的是选择的组件，则会重新生成DataBase数据,确保类型对应！
*/
void UActionNodes::OnDetailUpdate(const FPropertyChangedEvent& PropertyChangedEvent)
{
	FName ChangeEventComponentName = FActiveComponentMgr::GetEventComponentCategory(ActiveComponent);
	if (PropertyChangedEvent.GetPropertyName() == UActionNodes::ComponentPropertyName && !ChangeEventComponentName.IsEqual(CurComponentName))
	{
		//如果是ShowUI类型，则对应生成  
		if (FActiveComponentMgr::GetEventComponentCategory(ActiveComponent) == FEventComponentCategoryUtil::ComponentShowUI)
		{
			DataBase = nullptr;
			DataBase = FActiveComponentMgr::CreateComponentNodeData(ActiveComponent , this);
		}
	}

	CurComponentName = ChangeEventComponentName;

	(SNodeWidgetShared.Get())->UpdateNodeNmae(NodeName);
}