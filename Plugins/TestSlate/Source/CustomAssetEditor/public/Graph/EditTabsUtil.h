#pragma once

#include "CoreMinimal.h"

struct FScenarioEditorTabsUtil
{
	// Details的通用ID
	static const FName GraphDetailsID;
	static const FName SearchID;

	// Editor的通用ID
	static const FName GraphEditorID;
};

//所有节点以及Pin使用的名称定义
struct FScenarioNodeUtil
{
	static const FName NodeCategoryNormal;
	static const FName NodeCategoryRoot;
	static const FName NodeCategoryEnd;
};

struct FScenarioPinUtil
{
	static const FName SubPinCategoryNormal;	//普通节点的SubPin，暂时只用这一个，用来进行PinFactory的创建
	static const FName SubPinCategoryRoot;		//Root和End是特殊不能单独连接的
	static const FName SubPinCategoryEnd;		//Root和End是特殊不能单独连接的

	static const FName PinCategoryNotAllow;	//不允许任何连接
	static const FName PinCategoryNormal;	//普通Pin，只允许一个链接
	static const FName PinCategoryMulti;	//允许链接多个Pin
};