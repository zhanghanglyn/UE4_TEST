// Fill out your copyright notice in the Description page of Project Settings.


#include "StoryPlayerPawn.h"

// Sets default values
AStoryPlayerPawn::AStoryPlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//��ʼ��һ��UI
	/*if (m_SelectUI == NULL)
	{
		if (UClass* SelevtWidgetNew = LoadClass<UUserWidget>(NULL, TEXT("/Game/StoryTest/BP_SelectWidgetNew")))
		{
			if (GetWorld() != NULL)
			{
				if (APlayerController* PC = GetWorld()->GetFirstPlayerController())
				{
					m_SelectUI = CreateWidget<USelectWidget>(PC, SelevtWidgetNew);
					check(m_SelectUI);
					m_SelectUI->AddToViewport();
					//m_SelectUI->SetVisibility(ESlateVisibility::Hidden);

					//��ѡ��ί�лص�
					m_SelectUI->m_clickOneDelegate.BindUObject(this, &AStoryPlayerPawn::SelectOneCall);
				}
			}
		}
	}*/

}

// Called when the game starts or when spawned
void AStoryPlayerPawn::BeginPlay()
{
	Super::BeginPlay();

	//��ʼ��һ��UI
	if (m_SelectUI == NULL)
	{
		UClass* TempSelectUI = LoadClass<UUserWidget>(NULL, TEXT("WidgetBlueprint'/Game/StoryTest/UI/BP_SelectWidgetNew.BP_SelectWidgetNew_C'"));
		if (TempSelectUI != nullptr)
		{
			m_SelectUI = CreateWidget<USelectWidget>(GetWorld()->GetFirstPlayerController(), TempSelectUI);
			check(m_SelectUI);
			m_SelectUI->AddToViewport();
			m_SelectUI->SetVisibility(ESlateVisibility::Hidden);
			SetInputModeGameOnly();

			//��ѡ��ί�лص�
			m_SelectUI->m_clickOneDelegate.BindUObject(this, &AStoryPlayerPawn::SelectOneCall);
		}
	}


	//���Բ��ԣ�����������10.10.11
	/*WidgetComponent = NewObject<UWidgetComponent>(RootComponent, UWidgetComponent::StaticClass());
	if (WidgetComponent != nullptr)
	{
		WidgetComponent->RegisterComponent();
		WidgetComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

		//"WidgetBlueprint'/Game/StoryTest/UI/TESTUI.TESTUI_C'"

		//UClass* Widget = LoadClass<UUserWidget>(NULL, TEXT("WidgetBlueprint'/Game/StoryTest/UI/StoryControl.StoryControl_C'"));
		UClass* Widget = LoadClass<UUserWidget>(NULL, TEXT("WidgetBlueprint'/Game/StoryTest/UI/TESTUI.TESTUI_C'"));

		if (Widget != nullptr)
		{
			WidgetComponent->SetWidgetClass(Widget);
			//UUserWidget *temp_widget = CreateWidget<UUserWidget>(GetWorld()->GetFirstPlayerController(), Widget);
			//temp_widget->AddToViewport();
		}
	}*/

	//TestFunc();
}

// Called every frame 
void AStoryPlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AStoryPlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	check(PlayerInputComponent);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AStoryPlayerPawn::Click);
	//���ӽ��ƶ�
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	//PlayerInputComponent->BindAxis("TurnRate", this, &AStoryPlayerPawn::TurnRate)
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

}

void AStoryPlayerPawn::SetInputModeGameOnly()
{
	FInputModeGameOnly Mode;
	GetWorld()->GetFirstPlayerController()->SetInputMode(Mode);
}

void AStoryPlayerPawn::SetInputModeUIOnly()
{
	FInputModeUIOnly Mode;
	GetWorld()->GetFirstPlayerController()->SetInputMode(Mode);
}

/************************************************************************/
/*                    �������				                            */
/************************************************************************/
void AStoryPlayerPawn::Click()
{
	//���ж�������ͨ�ĵ����Ļ�������ڽ����¼�
	UE_LOG(LogTemp, Warning, TEXT("i'm click!!!!"));
	m_clickDelegate.ExecuteIfBound();
}

void AStoryPlayerPawn::TurnRate(float Rate)
{
	//���ж�������ͨ�ĵ����Ļ�������ڽ����¼�
	//UE_LOG(LogTemp, Warning, TEXT("Trun rate!!!! %d"), Rate);
	//AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

///////////////////////////////////////////////

void AStoryPlayerPawn::SetScenarioByPathName(FString PathName)
{
	FString path = FPaths::ProjectContentDir();

	//����յ�ǰ�籾
	int32 Count = m_curData.Num();
	if (Count > int32(0))
		m_curData.Empty();

	//���ַ�����ȡ����
	FString csvFilePath = ScenarioPath + PathName;
	//if (FPaths::FileExists((path + csvFilePath)))
	/*UDataTable *pDataTable = LoadObject<UDataTable>(NULL, *csvFilePath);
	if (pDataTable != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("yeah"));

	}*/

	//ȡһ��scenarioConfig
	FString scenarioConfigPath = ScenarioPath + ScenarioConfigName;
	FStreamableManager& AssetLoader = UAssetManager::GetStreamableManager();
	UDataTable *scenarioConfig = AssetLoader.LoadSynchronous<UDataTable>(FSoftObjectPath(scenarioConfigPath));
	if (scenarioConfig != nullptr)
	{
		FScenarioScenarioConfig* tmpPtr = nullptr;
		for (auto it : scenarioConfig->GetRowMap())
		{
			tmpPtr = (FScenarioScenarioConfig*)(it.Value);
			//�������Ҫ���ŵľ籾
			if (tmpPtr->scenarioId.Equals(PathName))
			{
				m_sequencePath = tmpPtr->se_path;
				break;
			}
		}
	}


	//���ַ�����ȡ����
	//FStreamableManager& AssetLoader = UAssetManager::GetStreamableManager();
	UDataTable *TestData2 = AssetLoader.LoadSynchronous<UDataTable>(FSoftObjectPath(csvFilePath));
	if (TestData2 != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("yeah22"));
		FScenarioDataBase* tmpPtr = nullptr;
		for (auto it : TestData2->GetRowMap())
		{
			tmpPtr = (FScenarioDataBase*)(it.Value);
			//UE_LOG(LogTemp, Warning, TEXT("--- row:%s, key:%d, name:%d"), *it.Key.ToString(), tmpPtr->mId, tmpPtr->nextPage);
			m_curData.Add(tmpPtr->mId, *tmpPtr);
		}
	}

}

void AStoryPlayerPawn::InitializePage()
{
	bSequencerOver = false;
	bEventOver = false;
	bSelectOver = false;

	if (m_SelectUI != nullptr)
		m_SelectUI->SetVisibility(ESlateVisibility::Hidden);
	SetInputModeGameOnly();
}

//��ʽ��ʼ�ܾ���
void AStoryPlayerPawn::StartRun()
{
	int32 Count = m_curData.Num();
	if (Count <= int32(0))
	{
		UE_LOG(LogTemp, Warning, TEXT("ScenarioData is null!!!!"));
		return;
	}

	//��һЩ��ʼ���Ĺ���
	m_curPage = 1;

	GetScenarioSequencer(m_sequencePath);

	//PlayNext();
}

void AStoryPlayerPawn::PlayNext()
{
	//����������ҳ������Ϊ-1������������
	if (m_curPage > m_curData.Num() || m_curPage == -1)
		return ;

	FScenarioDataBase *cur_page = m_curData.Find(m_curPage);
	InitializePage();

	//���ž���
	PlaySequence(*cur_page);

	//�����¼�
	PlayEvent(cur_page->eventId);

	//����ѡ��
	PlaySelection(*cur_page);

	//return *cur_page;
}

//ÿһҳ��ÿһ���������֮�󶼻�ͳһ����һ�θûص������������ҳ������ִ���ֱ꣬�ӽ�����һҳ
void AStoryPlayerPawn::CallBackByEveryPageAction( int32 _page)
{
	UE_LOG(LogTemp, Warning, TEXT("page click call : CallBackByEveryPageAction"));

	if (bSequencerOver == true && bEventOver == true)
	{
		//19.09.24 ����Ӧ����һ������ǰҳ����Լ���ǰҳ���ݵȵĺ���������page ֮����playNext
		if (_page != -1)
			m_curPage = _page;
		else
		{
			//����������ҳ������Ϊ-1������������ ��ʱ����������
			if (m_curPage > m_curData.Num() || m_curPage == -1)
					return;
			else
				m_curPage = m_curData.Find(m_curPage)->nextPage;
		}
			
		PlayNext();
	}	
	else
		UE_LOG(LogTemp, Warning ,TEXT("this page is not over!!") );
}


/************************************************************************/
/*                        ����sequence���                              */
/************************************************************************/

void AStoryPlayerPawn::GetScenarioSequencer(FString FullPath)
{
	FStreamableManager& AssetLoader = UAssetManager::GetStreamableManager();
	IntroMovieSequence = AssetLoader.LoadSynchronous<ULevelSequence>(FSoftObjectPath(FullPath)); //<ULevelSequence>(FSoftObjectPath(FullPath));

	m_MovieActor = GetWorld()->SpawnActor<ALevelSequenceActor>();

	m_MovieActor->SetSequence(IntroMovieSequence);
	m_sequencePlayer = m_MovieActor->GetSequencePlayer();//SequencePlayer->Play();

	//MovieActor->GetSequence();
}

//���Ŷ���
void AStoryPlayerPawn::PlaySequence(FScenarioDataBase cur_page)
{
	//���ж��������Ҫ����SE,���ò�����ɱ�ʶ����ֹͣ����
	if (cur_page.second_temp == -1)
	{
		if (m_sequencePlayer != NULL)
		{
			if (m_sequencePlayer->IsPlaying() == true)
				m_sequencePlayer->Stop();
		}
		bSequencerOver = true;
	}
	else
	{
		if (m_sequencePlayer != NULL)
		{
			if (m_sequencePlayer->IsPlaying() == true)
				m_sequencePlayer->Stop();

			m_sequencePlayer->Play();
			bSequencerOver = false;
		}
	}
	//���õ������Ϊ��ͨ���
	m_clickDelegate.Unbind();
	m_clickDelegate.BindUObject(this, &AStoryPlayerPawn::SequencerClick);

	if (finishDelegate.IsBound() == false)
	{
		finishDelegate.BindUFunction(this, "SequencePlayOverCallBack");
		m_sequencePlayer->OnFinished.AddUnique(finishDelegate);
	}
	
	//���ò�ʹ�������������
	SetBeControlCamera(cur_page.bOutCameraControl);
}

void AStoryPlayerPawn::SequencerClick()
{
	CallBackByEveryPageAction();
}

//Sequencer������ϻص�
void AStoryPlayerPawn::SequencePlayOverCallBack()
{
	bSequencerOver = true;
	UE_LOG(LogTemp, Warning, TEXT("now !!!!!!!!!!!!SequencePlayOverCallBack!!!!!!!!!!!"));
}

void AStoryPlayerPawn::SetBeControlCamera(bool _bControl)
{
	if (m_sequencePlayer != NULL)
		m_sequencePlayer->SetDisableCameraCuts(_bControl);
}



/************************************************************************/
/*                       �����¼�										*/
/************************************************************************/                

//����IDȥ�����¼� //��ʱ��д��һ���¼�����ʽ
void AStoryPlayerPawn::PlayEvent(FString _eventId)
{
	//
	if (_eventId.IsEmpty())
		bEventOver = true;
	else   //Ϊ��ͬ�ĺ�������ͬ�İ��Լ��趨����
	{
		//������¼�����ί�У����û��
		if (_eventId == "EVENT_PICK")
		{
			m_clickDelegate.Unbind();
			m_clickDelegate.BindUObject(this, &AStoryPlayerPawn::PickEventClick);
		}
	}
}

//�����¼�,֮��������ֻ����Ϊ�����Ŀɵ������
void AStoryPlayerPawn::PickEventClick()
{
	//ͨ�����߲����Ƿ�����Ҫѡ�е�����
	//�ҵ��������ʼ��������λ��
	//this->GetActorForwardVector();
	APlayerCameraManager* tempCameraManager = GetWorld()->GetFirstPlayerController()->PlayerCameraManager;
	FVector startPos = tempCameraManager->GetCameraLocation();
	FVector forward = tempCameraManager->GetActorForwardVector();
	FVector endPos = startPos + forward * 100000;

	TArray<FHitResult> temp_HitResult;
	//������߲���
	FCollisionQueryParams cqq(FName(TEXT("Combattrace")), true, NULL);
	cqq.bTraceComplex = true;
	cqq.bReturnPhysicalMaterial = false;
	cqq.AddIgnoredActor(this);

	GetWorld()->LineTraceMultiByObjectType(temp_HitResult, startPos, endPos, ECC_PhysicsBody , cqq);
	DrawDebugLine(this->GetWorld(), startPos, endPos, FColor::Red, true, 15000.0f);

	//�����ײ������
	if (temp_HitResult.Num() > 0)
	{
		for (int i = 0; i< temp_HitResult.Num() ; i++)
		{
			FString hitName = temp_HitResult[i].GetActor()->GetName();
			int32 tempPageCount = DealDataByClickName(hitName);
			if (tempPageCount != -1)
			{
				UE_LOG(LogTemp, Warning, TEXT("Now i hit %s !"), *hitName);
				CallBackByEveryPageAction(tempPageCount);
				break;
			}
		}
	}
}

int32 AStoryPlayerPawn::DealDataByClickName(FString _hitName)
{
	if (_hitName.Equals("PickOne"))
	{
		bEventOver = true;
		return 1;
	}
	else if (_hitName.Equals("PickOne2"))
	{
		bEventOver = true;
		return 3;
	}
	else if (_hitName.Equals("PickOne3"))
	{
		bEventOver = true;
		return 4;
	}

	return -1;
}

/************************************************************************/
/*                       ����ѡ��										*/
/************************************************************************/
void AStoryPlayerPawn::PlaySelection(FScenarioDataBase cur_page)
{
	if (cur_page.select.IsEmpty() == true && cur_page.selectToPage.IsEmpty() == true)
	{
		bSelectOver = true;
		return;
	}

	//��ѡ���Լ�ҳ����ֳ���
	FString select = cur_page.select;
	TArray<FString> temp_select;
	select.ParseIntoArray(temp_select, TEXT("#"), true);

	FString select_page = cur_page.selectToPage;
	TArray<FString> temp_to_page;
	select_page.ParseIntoArray(temp_to_page, TEXT("#"), true);
	TArray<int32> int_to_page;
	for (int i = 0; i < temp_to_page.Num(); i++)
	{
		int_to_page.Add(FCString::Atoi(*temp_to_page[i]));
	}

	//���֮ǰ�ĵ������
	m_clickDelegate.Unbind();

	//����ͼ�м���ѡ��UI ֮�������� ��ʾUI
	if (m_SelectUI != NULL)
	{
		SetInputModeUIOnly();
		m_SelectUI->SetVisibility(ESlateVisibility::Visible);
		m_SelectUI->SetCurPageData(temp_select, int_to_page);
	}
}

//ѡ�����������ص�
void AStoryPlayerPawn::SelectOneCall(SelectParam param)
{
	UE_LOG(LogTemp, Warning, TEXT("Now i select next page : %d !"), param.pageId);
	bSelectOver = true;
	CallBackByEveryPageAction(param.pageId);

}


/************************************************************************/
/*                        ����ѡ��over		                            */
/************************************************************************/

void AStoryPlayerPawn::TestFunc()
{
	/*UUIWidgetComponentBase *temp_WidgetComponent = NewObject<UUIWidgetComponentBase>(RootComponent, UUIWidgetComponentBase::StaticClass());
	if (temp_WidgetComponent != nullptr)
	{
		temp_WidgetComponent->RegisterComponent();
		temp_WidgetComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

		//"WidgetBlueprint'/Game/StoryTest/UI/TESTUI.TESTUI_C'"

		//UClass* Widget = LoadClass<UUserWidget>(NULL, TEXT("WidgetBlueprint'/Game/StoryTest/UI/StoryControl.StoryControl_C'"));
		UClass* Widget = LoadClass<UUserWidget>(NULL, TEXT("WidgetBlueprint'/Game/StoryTest/UI/TESTUI.TESTUI_C'"));

		if (Widget != nullptr)
		{
			temp_WidgetComponent->SetUI(Widget);
		}
	}*/

	WidgetComponent = UUIWidgetComponentBase::CreateUIWidgetBase(RootComponent, true,true);
	//WidgetComponent->SetUI("WidgetBlueprint'/Game/StoryTest/UI/TouchUITest.TouchUITest_C'");
	UClass* Widget = LoadClass<UUserWidget>(NULL, TEXT("WidgetBlueprint'/Game/StoryTest/UI/StoryControl.StoryControl_C'"));
	UUserWidget* tempaa = WidgetComponent->SetUI(Widget);
	UUserWidgetBase *tempcc = Cast < UUserWidgetBase>(tempaa);
	UTestTouchUI *tempbb = Cast < UTestTouchUI>(tempcc);
	if (tempbb != NULL)
		FString aa = tempbb->fs;

	//�÷�����Ч��
	//UTestTouchUI* touchUI = WidgetComponent->SetUI<UTestTouchUI>("WidgetBlueprint'/Game/StoryTest/UI/TouchUITest.TouchUITest_C'");
	WidgetComponent->SetUI<UUserWidget>("WidgetBlueprint'/Game/StoryTest/UI/StoryControl.StoryControl_C'");
	//if (touchUI != NULL)
		//FString aa = touchUI->fs;
	WidgetComponent->SetUIPosition( FVector(0,50,230) );
	WidgetComponent->SetUIRotation(FRotator(0,0,190));

	//�ھ�̬��Ʒ�����,�ɹ�
	TArray<AActor*> _tArray;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AStaticMeshActor::StaticClass(), _tArray);
	AStaticMeshActor* tempMesh = NULL;
	if (_tArray.Num() > 0)
	{
		for (int i=0;i < _tArray.Num() ; i++)
		{
			if (UKismetSystemLibrary::GetDisplayName(_tArray[i]) == "TestThing")
			{
				tempMesh = Cast<AStaticMeshActor>(_tArray[i]);
				break;
			}
		}
	}
	if (tempMesh != NULL)
	{
		UUIWidgetComponentBase *temp_base = UUIWidgetComponentBase::CreateUIWidgetBase(tempMesh->GetStaticMeshComponent(), true,true);
		temp_touchUI = temp_base->SetUI<UTestTouchUI>("WidgetBlueprint'/Game/StoryTest/UI/TouchUITest.TouchUITest_C'");
	}


	//ȫ��UMG����
	FString screenPath = "WidgetBlueprint'/Game/StoryTest/UI/BF_FullScreenTest.BF_FullScreenTest_C'";
	//sUFullScreenTest *test1 = Cast<UFullScreenTest>(UUMGManager::GetInstance()->CreateScreenWidget(screenPath,GetWorld(), UFullScreenTest::StaticClass(), "Test1"));
	//UFullScreenTest *test1 = UStoryGameInstance::GetInstance(GetWorld())->GetUMGManager()->CreateScreenWidget<UFullScreenTest>(screenPath, GetWorld(), UFullScreenTest::StaticClass(), "Test1" ,10);
	//if (test1 != nullptr)
		//test1->TestFunc();

	FString screenPath2 = "WidgetBlueprint'/Game/StoryTest/UI/BP_FullScreenTest2.BP_FullScreenTest2_C'";
	//UFullScreenWidgetBase *testUI2 = UStoryGameInstance::GetInstance(GetWorld())->GetUMGManager()->CreateScreenWidget<UFullScreenWidgetBase>(screenPath2, GetWorld(), UFullScreenWidgetBase::StaticClass(), "Test2");

	UStoryGameInstance* instance = UStoryGameInstance::GetInstance(GetWorld());
	/*UFullScreenWidgetBase *temp_Test1 = instance->GetUMGManager()->GetScreenWidget("Test1");
	UFullScreenTest *test2 = nullptr;
	if (temp_Test1 != nullptr)
		test2 = Cast< UFullScreenTest>(temp_Test1);
	if (test2 != nullptr)
		test2->TestFunc();
	*/
	//�����ڴ˰�UI��ӵ����ᱻ����Ĳ��֣�
	/*UE_LOG(LogTemp, Warning, TEXT("i'm create!!!!!!!!!"));
	UClass* Temp_Widget = LoadClass<UFullScreenWidgetBase>(NULL, screenPath2.GetCharArray().GetData());
	if (Temp_Widget != nullptr)
	{
		UFullScreenWidgetBase *NewWidget = CreateWidget<UFullScreenWidgetBase>(GetWorld(), Temp_Widget);
		if (NewWidget != nullptr)
		{
			//instance->GetGameViewportClient()->AddViewportWidgetContent(NewWidget->TakeWidget());
			NewWidget->AddToViewport();
		}
	}*/

	FInputModeUIOnly uiOnly;
	//UStoryGameInstance::GetInstance(GetWorld())->GetUMGManager()->SetInputMode(GetWorld(), uiOnly);
	this->SetInputModeUIOnly();

	//UFullScreenTest *test3 = UUMGManager::GetInstance()->GetScreenWidget<UFullScreenTest>("Test1");
	//if (test3 != nullptr)
	//	test3->TestFunc();
}

void AStoryPlayerPawn::TestFuncTwo()
{

	//this->SetInputModeUIOnly();
	//if (WidgetComponent != NULL)
	//{
		//UTestTouchUI* touchUI = WidgetComponent->SetUI<UTestTouchUI>("WidgetBlueprint'/Game/StoryTest/UI/TouchUITest.TouchUITest_C'");
		//if (touchUI!=NULL)
		//{
		///	touchUI
		//}
	//}

	//if (temp_touchUI != nullptr)
	//{
		//temp_touchUI->SetPlay();
	//}


	UStoryGameInstance* instance = UStoryGameInstance::GetInstance(GetWorld());
	//instance->GetUMGManager()->ClearAll();

	//UStoryGameInstance::GetInstance(GetWorld())->ChangeLevel( GetWorld(), FName("/Game/StoryTest/Level/StoryTestLevel"));
	
	//UStoryGameInstance::GetInstance(GetWorld())->GetUMGManager()->DeleteInsUMGByName("Test1");
	//UStoryGameInstance::GetInstance(GetWorld())->GetUMGManager()->ClearInsUMG();
	

	FString screenPath = "WidgetBlueprint'/Game/StoryTest/UI/BF_FullScreenTest.BF_FullScreenTest_C'";
	UFullScreenWidgetBase *NewWidget = instance->GetUMGManager()->CreateInstanceWidget(screenPath, GetWorld(), "Test2");
	if (NewWidget != nullptr)
		NewWidget->SetZorder<UCanvasPanelSlot>(1);
}

void AStoryPlayerPawn::TestFuncThree()
{
	UStoryGameInstance* instance2 = UStoryGameInstance::GetInstance();

	FString screenPath2 = "WidgetBlueprint'/Game/StoryTest/UI/BP_FullScreenTest2.BP_FullScreenTest2_C'";
	UStoryGameInstance* instance = UStoryGameInstance::GetInstance(GetWorld());


	UE_LOG(LogTemp, Warning, TEXT("i'm create!!!!!!!!!"));
	UFullScreenWidgetBase *NewWidget = instance->GetUMGManager()->CreateInstanceWidget(screenPath2,GetWorld(),"Test1");


	//�����ж���������Ƿ���ĳ������
	NewWidget->SetPosition<	UCanvasPanelSlot>(FVector2D(100, 200));
	if (NewWidget != nullptr)
	{
		NewWidget->SetZorder<UCanvasPanelSlot>(2);
		//NewWidget->SetAnchors<UCanvasPanelSlot>(FAnchors(1, 1, 1, 1));
	}
		
	
}

