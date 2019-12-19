#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "UObject/Object.h"
#include "Runtime/Engine/Classes/EdGraph/EdGraphSchema.h"
#include "Runtime/CoreUObject/Public/UObject/Class.h"
#include "EdGraph/EdGraphNode.h"
#include "EdGraph/EdGraphPin.h"
#include "AssetData.h"
#include "UObject/ObjectKey.h"
#include "ScenarioGraphSchema.generated.h"

UCLASS()
class UScenarioGraphSchema : public UEdGraphSchema
{
	GENERATED_UCLASS_BODY()

public:
	/*
	ʹ���κ�Ĭ�Ͻڵ������ͼ��
	*
	* @paramͼ���������Ĭ�Ͻڵ�
	* @param contextclass���ָ����ͼ���ն˽�ʹ�������������ǩ����������(���ӿں���)
	*/
	virtual void CreateDefaultNodesForGraph(UEdGraph& Graph) const;
	/*
	��ȡ���Ҽ����ͼ��ʱ���Խ��е����в���
	GetGraphContextActions�������Ը�����ͼ���Ҽ�ʱ��Щ������ʾ�����ܴ����Ľڵ�����
	*/
	virtual void GetGraphContextActions(FGraphContextMenuBuilder& ContextMenuBuilder) const;
	/*
	ȷ���Ƿ��������������֮�䴴�����ӡ�
	*
	* @param�ǵ�һ��pin�롣
	* @param b�ڶ������š�
	*
	* @ @��������ǺϷ��ģ�����һ�����ַ���������������������ʧ��ԭ�����Ϣ��
	*/
	virtual const FPinConnectionResponse CanCreateConnection(const UEdGraphPin* A, const UEdGraphPin* B) const;
};