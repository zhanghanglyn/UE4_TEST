#pragma once
#include "CoreMinimal.h"
#include "CustomAssetEditor/EventTreeSystem/ActiveComponent/EventComponentBase.h"
#include "EditTabsUtil.h"
#include "ScenarioNodeNormal.h"

//这个类不需要了！！ 
class CUSTOMASSETEDITOR_API FActiveComponentMgr
{

public:
	FActiveComponentMgr(){};

	/* 外部调用，去Run一个Componnet的Action，自动将其转化为对应的子类 */
	static bool RunAction( UEventComponentBase* RunComponent );

protected:

};