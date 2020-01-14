#include "RTSPlayerCameraSpectatorPawn.h"
#include "Runtime/Engine/Classes/Components/SphereComponent.h"
#include "Runtime/Engine/Public/Engine.h"

ARTSPlayerCameraSpectatorPawn::ARTSPlayerCameraSpectatorPawn(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	// enable Tick function
	PrimaryActorTick.bCanEverTick = true;

	// disable standard WASD movement
	bAddDefaultMovementBindings = false;

	// not needed Pitch Yaw Roll
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// collision
	GetCollisionComponent()->SetGenerateOverlapEvents(false);
	GetCollisionComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetCollisionComponent()->SetCollisionProfileName(TEXT("NoCollision"));
	GetCollisionComponent()->SetSimulatePhysics(false);

	// intialize the camera
	CameraComponent = ObjectInitializer.CreateDefaultSubobject<UCameraComponent>(this, TEXT("RTS Camera"));
	CameraComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	CameraComponent->bUsePawnControlRotation = false;

	/*初始化一下相机数据*/
	//CameraHeight = 1000.0f;
	//CameraAngle = 60.0f;
	//MoveSpeed = 50.0f;
	//CurDestination = FVector(0,0,0);

	BMouseLeftHold = false;

	PrimaryActorTick.bCanEverTick = true;

	//UpdateCamera();
}

void ARTSPlayerCameraSpectatorPawn::SetupPlayerInputComponent(UInputComponent* InInputComponent)
{
	check(InInputComponent);

	Super::SetupPlayerInputComponent(InInputComponent);

	InInputComponent->BindAxis("MoveForward", this, &ARTSPlayerCameraSpectatorPawn::MoveForward);
	InInputComponent->BindAxis("MoveRight", this, &ARTSPlayerCameraSpectatorPawn::MoveToRight);

	//绑定点击事件相关
	InInputComponent->BindAction("ClickMouseLeft", IE_Pressed ,this, &ARTSPlayerCameraSpectatorPawn::OnMouseClickStart);
	InInputComponent->BindAction("ClickMouseLeft", IE_Axis, this, &ARTSPlayerCameraSpectatorPawn::OnMouseClickMove);
	InInputComponent->BindAction("ClickMouseLeft", IE_Released, this, &ARTSPlayerCameraSpectatorPawn::OnMouseClickEnd);

}

void ARTSPlayerCameraSpectatorPawn::MoveForward(float diretction)
{
	CurDestination.X = (diretction * MoveSpeed);
}

void ARTSPlayerCameraSpectatorPawn::MoveToRight(float diretction)
{
	CurDestination.Y = (diretction * MoveSpeed);
}

void ARTSPlayerCameraSpectatorPawn::OnMouseClickStart()
{
	UE_LOG(LogTemp, Warning, TEXT("Start"));
	BMouseLeftHold = true;
}

void ARTSPlayerCameraSpectatorPawn::OnMouseClickMove()
{
	UE_LOG(LogTemp, Warning, TEXT("Holding"));
}

void ARTSPlayerCameraSpectatorPawn::OnMouseClickEnd()
{
	UE_LOG(LogTemp, Warning, TEXT("ClickOver"));
	BMouseLeftHold = false;
}


void ARTSPlayerCameraSpectatorPawn::Tick(float deltaSeconds)
{
	Super::Tick(deltaSeconds);

	UpdateActor();

	//判断鼠标是否在视窗中
	FVector2D mousePosition;
	FVector2D viewportSize;
	//Get mouse position and screen size
	UGameViewportClient* gameViewport = GEngine->GameViewport;
	//Make sure viewport exists
	check(gameViewport);
	gameViewport->GetViewportSize(viewportSize);
	//如果鼠标当前在视窗中
	if (gameViewport->IsFocused(gameViewport->Viewport) && gameViewport->GetMousePosition(mousePosition))
	{
		//响应长按事件
		if (BMouseLeftHold)
			OnMouseClickMove();

		//发射射线，获取对应的位置（格子）并创建一个物体

	}
	
}

#pragma optimize("",off)
void ARTSPlayerCameraSpectatorPawn::UpdateActor()
{
	//计算下Actor的位置
	FVector NewActorPos = FVector(0,0,0);
	NewActorPos.X = GetActorLocation().X + CurDestination.X;// FMath::Clamp(NewActorPos.X, GetActorLocation().X, GetActorLocation().X + CurDestination.X);
	NewActorPos.Y = GetActorLocation().Y + CurDestination.Y;//FMath::Clamp(NewActorPos.Y, GetActorLocation().Y, GetActorLocation().Y + CurDestination.Y);
	NewActorPos.Z = CameraHeight;

	//UE_LOG(LogTemp, Warning, TEXT("NewActorPos  :  X : %d  ,  Y :%d") , NewActorPos.X , NewActorPos.Y);
	//UE_LOG(LogTemp, Warning, TEXT("CurDestination  :  X : %d  ,  Y :%d"), CurDestination.X, CurDestination.Y);

	SetActorLocation(NewActorPos);

	//计算并设置镜头的角度
	FRotator NewRotation = FRotator::ZeroRotator;
	NewRotation.Pitch = CameraAngle;
	CameraComponent->SetRelativeRotation(NewRotation);

}
#pragma optimize("",on)