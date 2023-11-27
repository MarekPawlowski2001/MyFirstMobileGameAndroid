// Fill out your copyright notice in the Description page of Project Settings.

#include "BasePlane.h"
#include "TheOneGameModeBase.h"


ABasePlane::ABasePlane()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	// Set the 3D mesh
	BasicMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisualRepresentation"));
	SetRootComponent(BasicMesh);
	BasicMesh->SetWorldScale3D(FVector(2, 2, 1));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("StaticMesh'/Engine/BasicShapes/Plane.Plane'"));
	BasicMesh->SetStaticMesh(MeshAsset.Object);
	// Set the basic texture
	static ConstructorHelpers::FObjectFinder<UMaterial> MaterialAsset(TEXT("Material'/Game/BasePlaneMaterial.BasePlaneMaterial'"));
	BasicMesh->SetMaterial(0, MaterialAsset.Object);
	// Create component to display numbers
	MyText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("ValueText"));
	MyText->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
	MyText->SetHorizontalAlignment(EHTA_Center);
	MyText->SetVerticalAlignment(EVRTA_TextCenter);
	MyText->SetTextRenderColor(FColor::White);
	MyText->SetWorldLocation(GetActorLocation() + FVector(0, 0, 1));
	MyText->SetWorldRotation(GetActorRotation() + FRotator(90,180,0));
	MyText->SetXScale(2.2);
	MyText->SetYScale(2.2);
	MyText->SetWorldSize(22);
}

// Called when the game starts or when spawned
void ABasePlane::BeginPlay()
{
	Super::BeginPlay();
	ATheOneGameModeBase* ActiveGameMode = static_cast<ATheOneGameModeBase*> (UGameplayStatics::GetGameMode(GetWorld()));
	// Set the number from GameMode and set the proper size of the text
	FVector Location = GetActorLocation();
	if(Location != FVector(0,0,0))
	MyText->SetText(ActiveGameMode->RandomNumbers[2-static_cast<int>(Location.X)/200][2+static_cast<int>(Location.Y)/200]);
	if (MyText->Text.ToString().Len()==6){
		MyText->SetWorldSize(18);
	}
}

// Called every frame
void ABasePlane::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Show text with the number after reset the level
void ABasePlane::ResetTextComponent(){
	MyText->SetVisibility(true);
}