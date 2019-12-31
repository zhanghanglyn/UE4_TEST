#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "ScenarioNodeNormal.h"
#include "ActionNodes.generated.h"

UCLASS()
class UActionNodes : public UScenarioNodeNormal
{
	GENERATED_BODY()

public:

	UActionNodes();

	//~ Begin UEdGraphNode Interface
	//����һ���½ڵ��ʱ����ã������������ɸýڵ��Instance
	virtual TSharedPtr<SGraphNode> CreateVisualWidget() override;
	//~ End

};