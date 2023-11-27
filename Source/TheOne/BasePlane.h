// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TextRenderComponent.h"
#include "BasePlane.generated.h"

UCLASS()
class THEONE_API ABasePlane : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABasePlane();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Pointer to 3D Mesh
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* BasicMesh{};
	// Pointer to text which display number on the object
	UPROPERTY(EditAnywhere)
		UTextRenderComponent* MyText {};
	// change visibility of the text in MyText variable  
	void ResetTextComponent();
};