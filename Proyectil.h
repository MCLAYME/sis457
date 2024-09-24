#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Proyectil.generated.h"

UCLASS() // Aseg�rate de que UCLASS est� aqu�
class DONKEYKONG_L02_API AProyectil : public AActor
{
    GENERATED_BODY()

public:
    // Constructor
    AProyectil();

protected:
    // Funciones protegidas
    virtual void BeginPlay() override;

public:
    // Funciones p�blicas
    virtual void Tick(float DeltaTime) override;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Componentes")
    UStaticMeshComponent* ProyectilMesh;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movimiento")
    FVector DireccionMovimiento;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movimiento")
    float Velocidad;

    // Funci�n para inicializar la direcci�n y velocidad del proyectil
    void DispararEnDireccion(const FVector& Direccion);
};