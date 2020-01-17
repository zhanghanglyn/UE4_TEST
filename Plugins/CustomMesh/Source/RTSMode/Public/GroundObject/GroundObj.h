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
	AGroundObj(const FObjectInitializer& ObjectInitializer);

	/* virtual */
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;


	/* 开始被点击 */
	virtual void StartTouch(FVector TouchLocation) override;
	virtual void TouchHold(FVector TouchLocation) override;
	virtual void TouchEnd(FVector TouchLocation) override;
public:


protected:
	UPROPERTY(VisibleAnywhere , meta = (Category = "Ground Mesh"))
	class UStaticMeshComponent* GroundMeshComponent;
	//模型路径 暂时这么标
	UPROPERTY(EditAnywhere, meta = (Category = "Ground Mesh"))
	FString GroundMeshPath = "/Game/StarterContent/Shapes/Shape_Plane";

	UPROPERTY(EditAnywhere, meta = (Category = "Ground Config"))
	FVector2D GroundWidthHeight = FVector2D(100,100);

	//UPROPERTY(EditAnywhere, meta = (Category = "Ground Config"))
	//float GroundHeight;

};
