// Fill out your copyright notice in the Description page of Project Settings.


#include "StoryPlayerBase.h"

UStoryPlayerBase::UStoryPlayerBase()
{
	SelfType = STORY_PLAYERTYPE::EVENT_PLAYER;
}

void UStoryPlayerBase::RegistToSystem(UStoryPlaySystem* PlayerSystem)
{
	if (PlayerSystem == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Can't find StoryPlayer System !!!"));
		return;
	}
		
	//PlayerSystem->RegistPlayer<UStoryPlayerBase, STORY_PLAYSATAE,void>(SelfType, this, &UStoryPlayerBase::PlayStateCall);
	//PlayerSystem->RegistPlayer(SelfType, this, &UStoryPlayerBase::PlayStateCall);
	(PlayerSystem->GetDelegate(SelfType)).AddUObject(this, &UStoryPlayerBase::PlayStateCall);
	PlayerSystem->SetCallBack(this);
}

void UStoryPlayerBase::PlayStateCall(STORY_PLAYSATAE _CurState)
{
	UE_LOG(LogTemp, Warning, TEXT("Parent PlayerBase Is Worked!"));
	M_PlayOverDelegate.ExecuteIfBound(SelfType);
}