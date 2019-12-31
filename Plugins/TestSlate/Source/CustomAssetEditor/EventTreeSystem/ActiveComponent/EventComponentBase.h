#pragma once
#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "EventComponentBase.generated.h"

/* 事件Component的基类 */
UCLASS(ClassGroup = (EventTreeComponent) , meta = (BlueprintSpawnableComponent))
class UEventComponentBase : public USceneComponent
{
	GENERATED_BODY()

public:
	UEventComponentBase() {};

	/* 基类函数，回调自身等 */
	//自身播放完毕后回调结束
	virtual void FinishCallBack() {};
	//把自身清除
	virtual void Clear() {};
	
	/* 基类函数，回调自身等 */

	//暂时写作Action，后续接入其余模块就只改动Action：该Component进行的操作等  
	void Action() {};


};