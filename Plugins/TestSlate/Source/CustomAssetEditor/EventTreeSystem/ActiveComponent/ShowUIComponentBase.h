#pragma once
#include "CoreMinimal.h"
#include "EventComponentBase.h"
#include "CustomAssetEditor/EventTreeSystem/ActiveComponent/Data/NodeDataShowUI.h"
#include "ShowUIComponentBase.generated.h"

/* 事件Component的基类 */
UCLASS(ClassGroup = (EventTreeComponent) , meta = (BlueprintSpawnableComponent))
class UShowUIComponentBase : public UEventComponentBase
{
	GENERATED_BODY()

public:
	UShowUIComponentBase() : Super() {};

	virtual void StartAction() override;

	virtual void SetData(UComponentNodeDataBase* Data) override;

	virtual void Clear();

	UFUNCTION()
	void TimerOver();
public:
	UPROPERTY(EditAnywhere, Category = "测试测试")
	FString ShowName = "Test!!!!";

protected:
	UPROPERTY()
	UUserWidget* m_SelectUI;

	//计时器timer
	FTimerHandle UITimer;
};
