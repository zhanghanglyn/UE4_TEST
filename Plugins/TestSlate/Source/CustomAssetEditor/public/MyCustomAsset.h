#pragma once
#include "CoreMinimal.h"
#include "MyCustomAsset.generated.h"

UCLASS(BlueprintType)
class UMyCustomAsset : public UObject
{
	GENERATED_BODY()

public:
	UMyCustomAsset() {};
	
	/** Graph for Tree */
	UPROPERTY()
	class UEdGraph* StoryGraph;

	UPROPERTY(EditAnywhere, Category = "TreeAsset")
	FString Description;

	UPROPERTY(EditAnywhere, Category = "Condition")
	TMap<FString, int32> StringCondition;

	UPROPERTY(EditAnywhere, Category = "Condition")
	TMap<FString, FString> IntCondition;

	/** Info about the graphs we last edited */
	//UPROPERTY()
	//TArray<FEditedDocumentInfo> LastEditedDocuments;

};