#pragma once
#include "CoreMinimal.h"
#include "CustomAssetEditor/EventTreeSystem/ActiveComponent/EventComponentBase.h"
#include "CustomAssetEditor/EventTreeSystem/ActiveComponent/Data/ComponentNodeDataBase.h"
#include "EditTabsUtil.h"
#include "ScenarioNodeNormal.h"

//这个类用来做公用方法库
class CUSTOMASSETEDITOR_API FActiveComponentMgr
{

public:
	FActiveComponentMgr(){};

	/* 外部调用，去Run一个Componnet的Action，自动将其转化为对应的子类 */
	static bool RunAction( UEventComponentBase* RunComponent );

	/* 外部调用，判断一个Component是什么类型的 */
	static FName GetEventComponentCategory(TSubclassOf <UEventComponentBase> RunComponent);
	static FName GetEventComponentCategory(UEventComponentBase* RunComponent);

	/* 根据传入的Component生成一个对应的Data数据 */
	static UComponentNodeDataBase* CreateComponentNodeData(TSubclassOf <UEventComponentBase> RunComponent);
	static UComponentNodeDataBase* CreateComponentNodeData(UEventComponentBase* RunComponent);

protected:

};