#pragma once
#include "CoreMinimal.h"
#include "EventComponentBase.h"
#include "ShowUIComponentBase.generated.h"

/* 事件Component的基类 */
UCLASS(ClassGroup = (EventTreeComponent) , meta = (BlueprintSpawnableComponent))
class UShowUIComponentBase : public UEventComponentBase
{
	GENERATED_BODY()

public:
	UShowUIComponentBase() : Super() {};

	virtual void StartAction() override;

public:
};
