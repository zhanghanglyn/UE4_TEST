#pragma once
#include "CoreMinimal.h"
#include "NodeControllerBase.h"
#include "ActionNodeController.generated.h"

UCLASS()
class UActionNodeController : public UNodeControllerBase
{
	GENERATED_BODY()

public:

	UActionNodeController(const FObjectInitializer& ObjectInitializer) : UNodeControllerBase(ObjectInitializer) {};

	virtual void Init() override;

	virtual void Clear() override;
protected:


};