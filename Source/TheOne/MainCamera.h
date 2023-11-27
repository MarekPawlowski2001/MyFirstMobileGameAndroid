// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraActor.h"
#include "Camera/CameraComponent.h"
#include "MainCamera.generated.h"

/**
 * 
 */
UCLASS()
class THEONE_API AMainCamera : public ACameraActor
{
	GENERATED_BODY()
		public:
		// not used in the project
		FVector2D ViewportRes{};

		virtual void BeginPlay() override;
};
