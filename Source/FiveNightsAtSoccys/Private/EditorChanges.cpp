// Fill out your copyright notice in the Description page of Project Settings.


#include "EditorChanges.h"

#include "Enemy/AnimatronicPose.h"

void UEditorChanges::SelectActor(AActor* Actor, bool InSelected, bool bNotify, bool bSelectEvenIfHidden,
	bool bForceRefresh)
{
	UE_LOG(LogTemp, Warning, TEXT("SelectActor"));
	if (const AAnimatronicPose* AnimatronicPose = Cast<AAnimatronicPose>(Actor))
	{
		for (const AAnimatronicPose* Pose : AnimatronicPose->GetNextPoseCandidates())
		{
			FVector Start = AnimatronicPose->GetMesh()->GetCenterOfMass();
			FVector End = Pose->GetMesh()->GetCenterOfMass();
					
			FMaterialParameterInfo ParamInfo;
			ParamInfo.Name = "Tint";
			FLinearColor LinearColor = FLinearColor::Green;
			FColor Color = FColor::Green;
			AnimatronicPose->GetMesh()->GetMaterial(0)->GetVectorParameterValue(ParamInfo, LinearColor);
			Color = LinearColor.ToFColor(true);
					
			DrawDebugLine(GetWorld(), Start, End, Color, true, 1.0f, 0, 1.0f);
			//DrawDebugDirectionalArrow(GetWorld(), Start, End, 250.0f, Color, true, 1.0f, 1, 5.0f);
		}		
	}

	Super::SelectActor(Actor, InSelected, bNotify, bSelectEvenIfHidden, bForceRefresh);
	
}
