// Fill out your copyright notice in the Description page of Project Settings.


#include "SequencerPlayer.h"

USequencerPlayer::USequencerPlayer(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	SelfType = STORY_PLAYERTYPE::SEQ_PLAYER;
}

void USequencerPlayer::PlayStateCall(STORY_PLAYSATAE _CurState)
{
	UE_LOG(LogTemp, Warning, TEXT("USequencerPlayer Is Worked!"));
	M_PlayOverDelegate.ExecuteIfBound(SelfType);
}