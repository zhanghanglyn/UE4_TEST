﻿#include "GroundObj.h"
#include "CustomMesh/Private/CustomWall/CustomWall.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"

AGroundObj::AGroundObj(FString InActorName) : Super(InActorName)
{
	UE_LOG(LogTemp, Warning, TEXT("Is This Worked?"));
}

AGroundObj::AGroundObj(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	// 创建一个初始地面
	GroundMeshComponent = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("GroundDefaultMesh"));
	//GroundMeshComponent = NewObject<UStaticMeshComponent>(this, TEXT("GroundDefaultMesh"));
	//GroundMeshComponent->RegisterComponent();
	//GroundMeshComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	
	if (!GroundMeshPath.IsEmpty())
	{
		UStaticMesh* GroundMesh = Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, *GroundMeshPath));
		if (GroundMesh)
		{
			GroundMeshComponent->SetStaticMesh(GroundMesh);
			FBoxSphereBounds MeshBounds = GroundMesh->GetBounds();
			FBox MeshBox = MeshBounds.GetBox();
			FVector Scale = FVector(GroundWidthHeight.X / MeshBox.GetSize().X , GroundWidthHeight.Y / MeshBox.GetSize().Y , 1);
			GroundMeshComponent->SetWorldScale3D(Scale);
		}
			
	}
}

void AGroundObj::StartTouch(FVector TouchLocation)
{
	//开始创建一个墙
	UWorld* World = this->GetWorld();
	if (World)
	{
		FVector CreatePos = FVector(TouchLocation.X, TouchLocation.Y, TouchLocation.Z + 50);
		ACustomWall* testWall = World->SpawnActor<ACustomWall>(ACustomWall::StaticClass(), CreatePos, FRotator(0, 0, 0));
		//测试计算一个立方体
		testWall->CreateWall(FVector(50, 50, 50));
	}
		

}

void AGroundObj::TouchHold(FVector TouchLocation)
{

}

void AGroundObj::TouchEnd(FVector TouchLocation)
{

}

#pragma optimize("",off)
void AGroundObj::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	//UE_LOG(LogTemp, Warning, TEXT("Property changed!!!!!!!!"));
	if (PropertyChangedEvent.MemberProperty == nullptr)
		return;

	if (PropertyChangedEvent.MemberProperty->GetName() == "GroundMeshPath")
	{
		if (!GroundMeshPath.IsEmpty())
		{
			UStaticMesh* GroundMesh = Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, *GroundMeshPath));
			if (GroundMesh)
			{
				GroundMeshComponent->SetStaticMesh(GroundMesh);
				FBoxSphereBounds MeshBounds = GroundMesh->GetBounds();
				FBox MeshBox = MeshBounds.GetBox();
				FVector Scale = FVector(GroundWidthHeight.X / MeshBox.GetSize().X, GroundWidthHeight.Y / MeshBox.GetSize().Y, 1);
				GroundMeshComponent->SetWorldScale3D(Scale);
			}
		}
	}
	else if(PropertyChangedEvent.MemberProperty->GetName() == "GroundWidthHeight")
	{
		if (GroundMeshComponent)
		{
			if (UStaticMesh* TempStaticMesh = GroundMeshComponent->GetStaticMesh())
			{
				FBoxSphereBounds MeshBounds = TempStaticMesh->GetBounds();
				FBox MeshBox = MeshBounds.GetBox();
				FVector Scale = FVector(GroundWidthHeight.X / MeshBox.GetSize().X, GroundWidthHeight.Y / MeshBox.GetSize().Y, 1);
				GroundMeshComponent->SetWorldScale3D(Scale);
			}
		}
	}
}
#pragma optimize("",on)