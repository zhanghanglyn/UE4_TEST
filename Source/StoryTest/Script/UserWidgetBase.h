// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Button.h"
#include "CanvasPanel.h"
#include "UMG/Public/Components/Image.h"
#include "UMG/Public/Components/ScaleBox.h"
#include "Engine/Classes/Engine/Texture2D.h"
#include "UMG/Public/Blueprint/WidgetTree.h"
#include "UserWidgetBase.generated.h"

/**
 * 
 */
UCLASS(Abstract, editinlinenew, BlueprintType, Blueprintable, meta = (DontUseGenericSpawnObject = "True", DisableNativeTick))
class STORYTEST_API UUserWidgetBase : public UUserWidget
{
	GENERATED_BODY()

public:
	UUserWidgetBase(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct();

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

//界面按钮等相关控件变量


};
