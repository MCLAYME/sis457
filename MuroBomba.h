// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Muro.h"
#include "MuroBomba.generated.h"

/**
 * 
 */
UCLASS()
class DONKEYKONG_L02_API AMuroBomba : public AMuro
{
	GENERATED_BODY()

public: 
	AMuroBomba();
	// Sobrescribir el método Chocar
	virtual void Chocar();


protected:
	// Llamado cuando el juego comienza
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* MuroBombaMesh;

	UPROPERTY(EditAnywhere, Category = "Materials")
	UMaterial* FrozenMaterial;

public:
	virtual void Tick(float DeltaTime) override;

};
