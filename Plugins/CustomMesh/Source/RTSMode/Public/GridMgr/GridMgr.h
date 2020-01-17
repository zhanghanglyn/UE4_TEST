#pragma once

#include "CoreMinimal.h"
#include "GridMgr.generated.h"

/* 格子中包含的数据 */
USTRUCT()
struct FGridData
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY()
	bool BeOccupy = false; //是否被占用

	UPROPERTY()
	int32 GridRow = 0;	//格子的横向Index

	UPROPERTY()
	int32 GridColumn = 0;	//格子的纵向Index

	UPROPERTY()
	FString StartGridId;	//如果该字段不为空，则说明是多格子组成的部件的其余部分,如果为空，则自身就是StartGrid

	/* 必须在创建时调用！ */
	bool SetGridId();
	FString GetGridId() {
		return GridId;
	};

protected:
	UPROPERTY()
	FString GridId = "";

public:
	static int32 GridCount;// = 0;
	static FString GridName;// = "Grid_";
	
};