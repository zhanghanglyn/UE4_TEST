#include "GroundObj.h"
#include "CustomMesh/Private/CustomWall/CustomWall.h"

AGroundObj::AGroundObj(FString InActorName) : Super(InActorName)
{
}

void AGroundObj::StartTouch(FVector TouchLocation)
{
	//开始创建一个墙
	UWorld* World = this->GetWorld();
	if(World)
		ACustomWall* testWall = World->SpawnActor<ACustomWall>(ACustomWall::StaticClass(), TouchLocation, FRotator(0, 0, 0));

}

void AGroundObj::TouchHold(FVector TouchLocation)
{

}

void AGroundObj::TouchEnd(FVector TouchLocation)
{

}