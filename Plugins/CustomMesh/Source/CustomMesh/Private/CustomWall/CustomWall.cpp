#include "CustomWall.h"

ACustomWall::ACustomWall(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	WallMesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("CustomWall"));
	RootComponent = WallMesh;
	//WallMesh->bUseAsyncCooking = false;
}

// This is called when actor is spawned (at runtime or when you drop it into the world in editor)
void ACustomWall::PostActorCreated()
{
	Super::PostActorCreated();
	CreateWall();
}

void ACustomWall::CreateWall()
{
	TArray<FVector> vertices;
	vertices.Add(FVector(0, 0, 0));
	vertices.Add(FVector(0, 100, 0));
	vertices.Add(FVector(0, 0, 100));

	TArray<int32> Indices;
	Indices.Add(0);
	Indices.Add(1);
	Indices.Add(2);

	TArray<FVector> normals;
	normals.Add(FVector(1, 0, 0));
	normals.Add(FVector(1, 0, 0));
	normals.Add(FVector(1, 0, 0));

	TArray<FVector2D> UV0;
	UV0.Add(FVector2D(0, 0));
	UV0.Add(FVector2D(10, 0));
	UV0.Add(FVector2D(0, 10));

	//切线朝着X方向
	TArray<FProcMeshTangent> Tangents;
	Tangents.Add(FProcMeshTangent(0, 1, 0));
	Tangents.Add(FProcMeshTangent(0, 1, 0));
	Tangents.Add(FProcMeshTangent(0, 1, 0));

	TArray<FLinearColor> vertexColors;
	vertexColors.Add(FLinearColor(0.75, 0.75, 0.75, 1.0));
	vertexColors.Add(FLinearColor(0.75, 0.75, 0.75, 1.0));
	vertexColors.Add(FLinearColor(0.75, 0.75, 0.75, 1.0));

	WallMesh->CreateMeshSection_LinearColor(0, vertices, Indices, normals, UV0, vertexColors, Tangents, true);

	//检查有没有冲突数据，不处理了
	WallMesh->ContainsPhysicsTriMeshData(true);
}

void ACustomWall::SetStartPoint(FVector InStartVec)
{

}

void ACustomWall::SetEndPoint(FVector InStartVec)
{

}