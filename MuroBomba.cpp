// Fill out your copyright notice in the Description page of Project Settings.


#include "MuroBomba.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Engine/Engine.h"

AMuroBomba::AMuroBomba()
{
	PrimaryActorTick.bCanEverTick = true;

	// Crear el componente de malla estática
	MuroBombaMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MuroBombaMesh"));
	RootComponent = MuroBombaMesh;

	// Asignar la malla
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MuroBombaMeshAsset(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube'"));
	if (MuroBombaMeshAsset.Succeeded())
	{
		MuroBombaMesh->SetStaticMesh(MuroBombaMeshAsset.Object);
		FVector NewScale(2.0f, 0.25f, 3.0f);
		MuroBombaMesh->SetWorldScale3D(NewScale);
	}

	// Asignar el material congelado
	static ConstructorHelpers::FObjectFinder<UMaterial> FrozenMaterialAsset(TEXT("Material'/Game/StarterContent/Materials/M_Tech_Panel.M_Tech_Panel'"));
	if (FrozenMaterialAsset.Succeeded())
	{
		FrozenMaterial = FrozenMaterialAsset.Object;
	}
}

void AMuroBomba::Chocar()
{
	// Llama a los efectos definidos en AMuro

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, TEXT("Chocaste con un muro congelado."));
}

void AMuroBomba::BeginPlay()
{
	Super::BeginPlay();

	if (FrozenMaterial)
	{
		MaterialInstance = UMaterialInstanceDynamic::Create(FrozenMaterial, this);
		if (MaterialInstance && MuroBombaMesh)
		{
			MuroBombaMesh->SetMaterial(0, MaterialInstance);
		}
	}
}

void AMuroBomba::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}