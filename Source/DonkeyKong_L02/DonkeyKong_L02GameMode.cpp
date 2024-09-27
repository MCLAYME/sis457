// Copyright Epic Games, Inc. All Rights Reserved.

#include "DonkeyKong_L02GameMode.h"
#include "DonkeyKong_L02Character.h"
#include "UObject/ConstructorHelpers.h"
//#include "ObstaculoMuro.h"
#include "componentePlataforma.h"
//#include "Barril.h"
//#include "Esfera.h"
#include "MuroBomba.h"
#include "Cono.h"


ADonkeyKong_L02GameMode::ADonkeyKong_L02GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/SideScrollerCPP/Blueprints/SideScrollerCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
void ADonkeyKong_L02GameMode::BeginPlay()
{
	Super::BeginPlay();

    GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Yellow, TEXT("Creando plataforma"));

    FVector posicionInicial = FVector(1206.0f, -1050.0f, 1000.0f);
    FRotator rotacionInicial = FRotator(0.0f, 0.0f, 10.0f);
    FTransform SpawnLocationCP;
    float anchoComponentePlataforma = 300.0f;
    float incrementoAltoComponentePlataforma = 200.0f;
    float incrementoAltoEntrePisos = 800.0f;
    float incrementoInicioPiso = 100.0f;

    for (int npp = 0; npp < 5; npp++) {
        rotacionInicial.Roll = rotacionInicial.Roll * -1;
        incrementoInicioPiso = incrementoInicioPiso * -1;
        incrementoAltoComponentePlataforma = incrementoAltoComponentePlataforma * -1;
        SpawnLocationCP.SetRotation(FQuat(rotacionInicial));
        for (int ncp = 0; ncp < 10; ncp++) {
            SpawnLocationCP.SetLocation(FVector(posicionInicial.X, posicionInicial.Y + anchoComponentePlataforma * ncp, posicionInicial.Z));
            AcomponentePlataforma* cp = GetWorld()->SpawnActor<AcomponentePlataforma>(AcomponentePlataforma::StaticClass(), SpawnLocationCP);
            posicionInicial.Z -= 0.50f;

            if ((npp == 0 || npp == 2 || npp == 4) && (ncp == 1 || ncp == 3)) {
                cp->bMoverVerticalmente = true;
                cp->StartPoint = SpawnLocationCP.GetLocation();
                cp->EndPoint = cp->StartPoint + FVector(0.0f, 0.0f, 500.0f);
            }
            if ((npp == 1 || npp == 3) && (ncp == 1 || ncp == 3)) {
                cp->bMoverHorizontalmente = true;
                cp->StartPoint = SpawnLocationCP.GetLocation();
                cp->EndPoint = cp->StartPoint + FVector(0.0f, 200.0f, 0.0f);
            }
            componentesPlataforma.Add(cp);
            if (ncp < 4) {
                posicionInicial.Z = posicionInicial.Z + incrementoAltoComponentePlataforma;
            }
        }
        posicionInicial.Z = posicionInicial.Z + incrementoAltoEntrePisos;
        posicionInicial.Z = posicionInicial.Z + incrementoInicioPiso;
    }


    FTransform SpawnLocationMuroBomba;
    SpawnLocationMuroBomba.SetLocation(FVector(1180.0f, -1100.0f, 400.0f));
    SpawnLocationMuroBomba.SetRotation(FQuat(FRotator(0.0f, 0.0f, 0.0f)));
    GetWorld()->SpawnActor<AMuroBomba>(AMuroBomba::StaticClass(), SpawnLocationMuroBomba);

    // Definir la posición en la que queremos crear el cono disparador
    FVector PosicionCono = FVector(1180.0f, -460.0f, 1260.0f);
    FRotator RotacionCono = FRotator::ZeroRotator;

    // Comprobar si la clase del ConoDisparador está asignada
    if (ClaseCono)
    {
        ACono* Cono = GetWorld()->SpawnActor<ACono>(ClaseCono, PosicionCono, RotacionCono);

        if (Cono)
        {
            GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Cono Disparador creado correctamente"));
        }
        else
        {
            GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Error al crear el Cono Disparador"));
        }
    }
}
