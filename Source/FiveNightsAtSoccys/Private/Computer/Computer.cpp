// Fill out your copyright notice in the Description page of Project Settings.


#include "Computer/Computer.h"

#include "Camera/SecurityCamera.h"
#include "Engine/TextureRenderTarget2D.h"
#include "Kismet/GameplayStatics.h"
#include "Materials/MaterialInstanceDynamic.h"


// Sets default values
AComputer::AComputer()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	MonitorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MonitorMesh"));
	RootComponent = MonitorMesh;


}

// Called when the game starts or when spawned
void AComputer::BeginPlay()
{
	Super::BeginPlay();

	// Connect to security cameras
	LinkToCameras();

	// Switch to camera 0
	SwitchToCameraIndex(CurrentCameraIndex);
}


bool AComputer::LinkToCameras()
{
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASecurityCamera::StaticClass(), FoundActors);
	const int32 NumCameras = SecurityCameras.Num();
	
	for(const auto& Camera : FoundActors)
	{
		if(ASecurityCamera* SecurityCamera = Cast<ASecurityCamera>(Camera))
		{
			if(!SecurityCameras.Contains(SecurityCamera))
			{
				SecurityCamera->LinkToComputer(this);
				SecurityCameras.Add(SecurityCamera);
			}
		}
	}

	return NumCameras != SecurityCameras.Num();
}

void AComputer::LoadStreamLevelsBySoftObjectPtr()
{
	StreamLevelsStack.RemoveAt(0);
	if(StreamLevelsStack.IsEmpty()) return;
	
	FLatentActionInfo LatentInfo;
	LatentInfo.CallbackTarget = this;
	LatentInfo.ExecutionFunction = "LoadStreamLevelsBySoftObjectPtr";
	
	UGameplayStatics::LoadStreamLevelBySoftObjectPtr(GetWorld(), StreamLevelsStack[0], true, true, LatentInfo);
}

void AComputer::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	//ScreenMaterial = MonitorMesh->CreateDynamicMaterialInstance(0, ComputerScreenMaterialBase);
	ScreenMaterial = UMaterialInstanceDynamic::Create(ComputerScreenMaterialBase, this);
	MonitorMesh->SetMaterial(1, ScreenMaterial);	
}

void AComputer::SwitchToCameraIndex(int32 Index)
{
	if(!SecurityCameras.IsValidIndex(Index))
	{
		UE_LOG(LogTemp, Error, TEXT("Invalid camera index %d"), Index);
		return;
	}
	
	if(ASecurityCamera* Camera = SecurityCameras[Index])
	{
		if(ScreenMaterial)
		{
			// Change camera index
			CurrentCameraIndex = Index;
			CurrentCamera = Camera;

			// Set screen material texture to camera view
			ScreenMaterial->SetTextureParameterValue("Display Input", Camera->GetCameraOutput());

			
			OnCameraChanged.Broadcast();
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("No screen material"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Null camera index %d"), Index);
	}
}

void AComputer::SwitchToNextCamera()
{
	const int32 NumCameras = SecurityCameras.Num();
	if(NumCameras == 0)
	{
		UE_LOG(LogTemp, Error, TEXT("No cameras"));
		return;
	}

	const int32 NextCameraIndex = (CurrentCameraIndex + 1) % NumCameras;
	SwitchToCameraIndex(NextCameraIndex);
}

void AComputer::SwitchToPreviousCamera()
{
	const int32 NumCameras = SecurityCameras.Num();
	if(NumCameras == 0)
	{
		UE_LOG(LogTemp, Error, TEXT("No cameras"));
		return;
	}

	const int32 PreviousCameraIndex = (CurrentCameraIndex - 1) % NumCameras;
	SwitchToCameraIndex(PreviousCameraIndex);
}


