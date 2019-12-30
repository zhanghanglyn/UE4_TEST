#pragma once
#include "CoreMinimal.h"
#include "MyCustomAsset.generated.h"

UCLASS(BlueprintType)
class UMyCustomAsset : public UObject
{
	GENERATED_BODY()

public:
	UMyCustomAsset() {};
	
	/** Graph for Behavior Tree */
	UPROPERTY()
	class UEdGraph* StoryGraph;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = MyCustomAsset)
	FString Description;


	/** Info about the graphs we last edited */
	//UPROPERTY()
	//TArray<FEditedDocumentInfo> LastEditedDocuments;

};