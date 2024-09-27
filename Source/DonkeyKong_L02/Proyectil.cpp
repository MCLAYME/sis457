#include "Proyectil.h"

AProyectil::AProyectil()
{
    PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> ProyectilMeshAsset(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Torus.Shape_Torus'"));
	if (ProyectilMeshAsset.Succeeded())
	{
		ProyectilMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProyectilMesh"));
		ProyectilMesh->SetStaticMesh(ProyectilMeshAsset.Object);
		RootComponent = ProyectilMesh;
	}


    Velocidad = 1000.0f;

}

void AProyectil::BeginPlay()
{
    Super::BeginPlay();
}

void AProyectil::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
	// Actualizar la posición del proyectil basado en la dirección de movimiento
	FVector NuevaPosicion = GetActorLocation() + (DireccionMovimiento * Velocidad * DeltaTime);
	SetActorLocation(NuevaPosicion);
}

void AProyectil::DispararEnDireccion(const FVector& Direccion)
{

    DireccionMovimiento = Direccion.GetSafeNormal(); // Asegurarse de que la dirección esté normalizada

}

