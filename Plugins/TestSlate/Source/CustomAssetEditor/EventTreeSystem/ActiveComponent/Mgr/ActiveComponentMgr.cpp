#include "ActiveComponentMgr.h"
#include "CustomAssetEditor/EventTreeSystem/ActiveComponent/ShowUIComponentBase.h"

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