#pragma once

#include "CoreMinimal.h"
#include "ActorBase.h"
#include "GroundObj.generated.h"

/*
	包含格子信息的地面
*/
UCLASS(BlueprintType, Blueprintable)
class RTSMODE_API AGroundObj : public AActorBase
{
	GENERATED_BODY()
public:
	AGroundObj( FString InActorName );

	/** Constructor for AActor that takes an ObjectInitializer for backward compatibility */
	AGroundObj(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {};

	/* 开始被点击 */
	virtual void StartTouch(FVector TouchLocation) override;
	virtual void TouchHold(FVector TouchLocation) override;
	virtual void TouchEnd(FVector TouchLocation) override;
public:

};
