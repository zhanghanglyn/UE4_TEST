#include "ActiveComponentMgr.h"
#include "CustomAssetEditor/EventTreeSystem/ActiveComponent/ShowUIComponentBase.h"
#include "CustomAssetEditor/EventTreeSystem/ActiveComponent/Data/NodeDataShowUI.h"

#pragma optimize("",off)
bool FActiveComponentMgr::RunAction(UEventComponentBase* RunComponent)
{
	check(RunComponent);

	if (UShowUIComponentBase* CastShowUIComponent = Cast<UShowUIComponentBase>(RunComponent))
	{
		CastShowUIComponent->StartAction();
		return true;
	}

	return false;
}
#pragma optimize("",on)

/*根据传入组件获取他的类型*/
FName FActiveComponentMgr::GetEventComponentCategory(UEventComponentBase* RunComponent)
{
	//如果是ShowUI组件
	if (RunComponent->StaticClass() == UShowUIComponentBase::StaticClass() || RunComponent->GetFName() == UShowUIComponentBase::StaticClass()->GetFName())
	{
		return FEventComponentCategoryUtil::ComponentShowUI;
	}
	else
	{
		return FEventComponentCategoryUtil::ComponentBase;
	}

	return FEventComponentCategoryUtil::ComponentBase;
}
FName FActiveComponentMgr::GetEventComponentCategory(TSubclassOf< UEventComponentBase> RunComponent)
{
	//如果是ShowUI组件
	if (RunComponent->StaticClass() == UShowUIComponentBase::StaticClass() || RunComponent->GetFName() == UShowUIComponentBase::StaticClass()->GetFName())
	{
		return FEventComponentCategoryUtil::ComponentShowUI;
	}
	else
	{
		return FEventComponentCategoryUtil::ComponentBase;
	}

	return FEventComponentCategoryUtil::ComponentBase;
}

/**/
UComponentNodeDataBase* FActiveComponentMgr::CreateComponentNodeData(TSubclassOf <UEventComponentBase> RunComponent)
{
	if (GetEventComponentCategory(RunComponent) == FEventComponentCategoryUtil::ComponentShowUI)
	{
		return NewObject<UNodeDataShowUI>();
	}

	return nullptr;
}
UComponentNodeDataBase* FActiveComponentMgr::CreateComponentNodeData(UEventComponentBase* RunComponent)
{
	if (GetEventComponentCategory(RunComponent) == FEventComponentCategoryUtil::ComponentShowUI)
	{
		return NewObject<UNodeDataShowUI>();
	}

	return nullptr;
}