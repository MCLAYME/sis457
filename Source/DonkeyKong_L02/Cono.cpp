// Fill out your copyright notice in the Description page of Project Settings.


#include "Cono.h"
#include "Proyectil.h"
#include "Engine/World.h"
#include "TimerManager.h"

// Sets default values
ACono::ACono()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    
	static ConstructorHelpers::FObjectFinder<UStaticMesh> ConoMeshAsset(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Cone.Shape_Cone'"));
	if (ConoMeshAsset.Succeeded())
	{
		ConoMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ConoMesh"));
		ConoMesh->SetStaticMesh(ConoMeshAsset.Object);
		RootComponent = ConoMesh;
	}


    TiempoEntreDisparos = 2.0f; // Tiempo entre disparos en segundos
    ContadorTiempo = 0.0f;
}

void ACono::BeginPlay()
{
    Super::BeginPlay();
}

void ACono::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // Contador para disparar cada cierto tiempo
    ContadorTiempo += DeltaTime;
    if (ContadorTiempo >= TiempoEntreDisparos)
    {
        DispararProyectilAleatorio();
        ContadorTiempo = 0.0f; // Reiniciar el contador
    }
}

void ACono::DispararProyectilAleatorio()
{
    if (ClaseProyectil)
    {
        // Obtener la rotación aleatoria del cono para disparar
        FRotator RotacionAleatoria = FRotator(FMath::RandRange(-30.0f, 30.0f), FMath::RandRange(-180.0f, 180.0f), 0.0f);
        FVector DireccionDisparo = RotacionAleatoria.Vector();

        // Obtener la ubicación y rotación del cono para instanciar el proyectil
        FVector UbicacionDisparo = GetActorLocation();
        FRotator RotacionDisparo = DireccionDisparo.Rotation();

        // Crear el proyectil
        AProyectil* Proyectil = GetWorld()->SpawnActor<AProyectil>(ClaseProyectil, UbicacionDisparo, RotacionDisparo);
        if (Proyectil)
        {
            // Establecer la dirección del proyectil
            Proyectil->DispararEnDireccion(DireccionDisparo);
        }
    }
}