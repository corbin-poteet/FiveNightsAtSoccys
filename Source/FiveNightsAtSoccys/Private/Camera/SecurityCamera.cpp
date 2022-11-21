// Fill out your copyright notice in the Description page of Project Settings.


#include "Camera/SecurityCamera.h"

#include "Components/SceneCaptureComponent2D.h"
#include "Computer/Computer.h"
#include "Engine/TextureRenderTarget2D.h"


// Sets default values
ASecurityCamera::ASecurityCamera()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SceneCaptureComponent = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("SceneCaptureComponent"));
	SceneCaptureComponent->bCaptureOnMovement = false;
}

void ASecurityCamera::SetFrameRate(float NewFrameRate)
{
	FrameRate = NewFrameRate;
	
	if (FrameRate > 0)
	{
		SceneCaptureComponent->bCaptureEveryFrame = false;
		GetWorld()->GetTimerManager().SetTimer(FrameTimerHandle, this, &ASecurityCamera::UpdateCamera, 1 / FrameRate, true);
	}
	else
	{
		SceneCaptureComponent->bCaptureEveryFrame = true;
		GetWorld()->GetTimerManager().ClearTimer(FrameTimerHandle);
	}
}

// Called when the game starts or when spawned
void ASecurityCamera::BeginPlay()
{
	Super::BeginPlay();

	SetFrameRate(FrameRate);
}

// Called every frame
void ASecurityCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool ASecurityCamera::LinkToComputer(const AComputer* Computer)
{	
	const int Width = Computer->GetScreenResolution().X;
	const int Height = Computer->GetScreenResolution().Y;

	UTextureRenderTarget2D* RenderTarget = NewObject<UTextureRenderTarget2D>(this);
	RenderTarget->InitCustomFormat(Width, Height, PF_B8G8R8A8, false);
	
	
	//UTexture2D* Texture = UTexture2D::CreateTransient(Width, Height, Computer->GetPixelFormat());
	//#if WITH_EDITORONLY_DATA
	//	Texture->MipGenSettings = TMGS_NoMipmaps;
	//#endif

	SceneCaptureComponent->TextureTarget = RenderTarget;

	return true;
}

void ASecurityCamera::UpdateCamera() const
{
	SceneCaptureComponent->CaptureScene();
}

