#pragma once
#include "CoreMinimal.h"
#include "MyCustomAsset.generated.h"

UCLASS(BlueprintType)
class UMyCustomAsset : public UObject
{
	GENERATED_BODY()

public:
	UMyCustomAsset() {};

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = MyCustomAsset)
	FString Description;

};