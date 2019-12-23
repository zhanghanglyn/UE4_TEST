#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "Runtime/Engine/Classes/EdGraph/EdGraphNode.h"
#include "ScenarioNodeBase.h"
#include "Editor/GraphEditor/Public/SGraphNode.h"
#include "ScenarioNodeNormal.generated.h"

/* �洢�ڵ����ݵĲ��� */
UCLASS()
class UScenarioNodeNormal : public UEdGraphNode
{
	GENERATED_UCLASS_BODY()

public:

	//~ Begin UEdGraphNode Interface
	//����һ���½ڵ��ʱ����ã������������ɸýڵ��Instance


	//~ End

	/* ���෽�����̳к��������������½ڵ� */
	virtual void AllocateDefaultPins();


public:

	UPROPERTY(EditAnywhere, Category = DialogueGraphNode)
	FString TestData;

};

/* �̳�SBorder��Node��ʾ�� */
class SScenarioNodeNormal : public SGraphNode
{
public:
	SLATE_BEGIN_ARGS(SScenarioNodeNormal)
	{

	}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs , UEdGraphNode* InNode);

	/*����Node��ƥ��Data����*/
	virtual void UpdateGraphNode();
	
	/*����Pin UI*/
	virtual void CreatePinWidgets();

	/* ��һ��Pin��ӵ�Node�ϣ��������´�����Pin */
	virtual void AddPin(const TSharedRef<SGraphPin>& PinToAdd);

};