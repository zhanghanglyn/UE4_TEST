#pragma once

#include "CoreMinimal.h"
#include "ProceduralMeshComponent.h"
//#include "Plugins/Runtime/ProceduralMeshComponent/Source/ProceduralMeshComponent/Public/ProceduralMeshComponent.h"
#include "CustomWall.generated.h"

UCLASS(meta = (BlueprintSpawnableComponent), ClassGroup = CustomMeshComponent)
class CUSTOMMESH_API ACustomWall : public AActor
{
	GENERATED_UCLASS_BODY()

public:
	//ACustomWall(const FObjectInitializer& ObjectInitializer);

	/* virtual */
	virtual void PostActorCreated() override;

	
public:
	void SetStartPoint( FVector InStartVec);
	void SetEndPoint(FVector InStartVec);

protected:
	void CreateWall();

protected:
	UProceduralMeshComponent* WallMesh;

private:
	//起始点和结束点
	FVector StartVec;
	FVector EndVec;
};