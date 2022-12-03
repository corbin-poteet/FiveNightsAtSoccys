// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/AnimatronicPose.h"
#include "DrawDebugHelpers.h"
#include "Selection.h"
#include "Components/ArrowComponent.h"


void AAnimatronicPose::GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const
{
	Super::GetOwnedGameplayTags(TagContainer);

}

// Sets default values
AAnimatronicPose::AAnimatronicPose()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//bRunConstructionScriptOnDrag = false;

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>("AnimatronicMesh");

	#if WITH_EDITORONLY_DATA
		//USelection::SelectObjectEvent.AddUObject(this, &AAnimatronicPose::OnSelectedDelegate);
		USelection::SelectObjectEvent.AddUObject(this, &ThisClass::OnSelected);
	#endif
}

void AAnimatronicPose::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	ActivateAnimatronic(false);
}

void AAnimatronicPose::ActivateAnimatronic(bool bNewActivated)
{
	bAnimatronicActivated = bNewActivated;
	SetActorHiddenInGame(!bAnimatronicActivated);
}

// Called when the game starts or when spawned
void AAnimatronicPose::BeginPlay()
{
	Super::BeginPlay();
	
}

AAnimatronicPose* AAnimatronicPose::SelectNextPose()
{
	// If there are no poses, return self
	//if(NextPoseCandidates.Num() <= 0)
	//{
	//	return this;
	//}
	
	// If we can kill the player, do so
	for (const auto& Pose : NextPoseCandidates)
	{
		if (Pose->IsKillPose())
		{
			if (!Pose->IsBlocked())
			{
				return Pose;
			}
		}
	}

	const int32 NumShuffles = NextPoseCandidates.Num() - 1;
	for(int32 i = 0 ; i < NumShuffles ; ++i)
	{
		const int32 SwapIdx = FMath::RandRange(i, NumShuffles);// NextPoseCandidates.RandRange(i, NumShuffles);
		NextPoseCandidates.Swap(i, SwapIdx);
	}

	
	for (const auto& Pose : NextPoseCandidates)
	{
		if (!Pose->IsBlocked())
		{
			return Pose;
		}
	}

	return this;
}

void AAnimatronicPose::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	if(IsSelectedInEditor())
	{
		ShowDebugLinks();
	}
}



#if WITH_EDITORONLY_DATA
// ReSharper disable once CppParameterMayBeConstPtrOrRef
// ReSharper disable once CppMemberFunctionMayBeConst
void AAnimatronicPose::OnSelected(UObject* Object)
{
	if (!GetWorld())
	{
		return;
	}
	
	if (!Object || !Object->IsA<AAnimatronicPose>())
	{
		FlushPersistentDebugLines(GetWorld());
		return;
	}

	if(Object == this)
	{
		ShowDebugLinks();
	}

	ShowDebugLinks();

}

void AAnimatronicPose::ShowDebugLinks() const
{	
	FlushPersistentDebugLines(GetWorld());
	UE_LOG(LogTemp, Warning, TEXT("Selected"));
	for (const AAnimatronicPose* Pose : GetNextPoseCandidates())
	{
		if(!Pose)
		{
			continue;
		}
		
		FVector Start = GetMesh()->GetCenterOfMass();
		FVector End = Pose->GetMesh()->GetCenterOfMass();
				
		FMaterialParameterInfo ParamInfo;
		ParamInfo.Name = "Tint";
		FLinearColor LinearColor = FLinearColor::Green;
		FColor Color = FColor::Green;
		GetMesh()->GetMaterial(0)->GetVectorParameterValue(ParamInfo, LinearColor);
		Color = LinearColor.ToFColor(false);

		DrawDebugLine(GetWorld(), Start, End, Color, true, 1.0f, 255, 2.5f);
		//DrawDebugDirectionalArrow(GetWorld(), Start, End, 250.0f, Color, true, 1.0f, 1, 5.0f);
		
	}
}
#endif



