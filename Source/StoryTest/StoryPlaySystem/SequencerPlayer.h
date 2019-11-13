// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StoryPlaySystem/StoryPlayerBase.h"
#include "SequencerPlayer.generated.h"

/**
 * 
 */
UCLASS()
class USequencerPlayer : public UStoryPlayerBase
{
	GENERATED_BODY()
	
public:
	USequencerPlayer(const FObjectInitializer& ObjectInitializer);

	/* 播放器播放时注册的调用事件委托 , 参数为当前播放状态*/
	virtual void PlayStateCall(STORY_PLAYSATAE _CurState) override;
	
};
