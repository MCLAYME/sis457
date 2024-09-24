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
/*
		FVector posicionInicial = FVector(0.50f, -2400.0f, 1000.0f);
		FRotator rotacionInicial = FRotator(0.0f, 0.0f, 10.0f);
		FTransform SpawnLocationCP;
		float anchoComponentePlataforma = 300.0f;
		float incrementoAltoComponentePlataforma = -105.0f;
		float incrementoAltoEntrePisos = 1200.0f;
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
	}*/

	// PISO HACIA LA DERECHA

	FVector posicionInicial = FVector(1300.0f, 500.0f, 300.f);		
	FRotator rotacionInicial = FRotator(0.0f, 0.0f, 15);
	FTransform SpawnLocationCP;

	for (int npp = 0; npp < 5; npp++)                        //NUMERO DE PISOS
	{
		rotacionInicial.Roll = rotacionInicial.Roll * -1;
		posicionInicial.Z += 450.0f;

		SpawnLocationCP.SetRotation(FQuat(rotacionInicial));
		for (int ncp = 0; ncp < 5; ncp++) {                               //NUMERO DE PLATAFORMAS

			SpawnLocationCP.SetLocation(FVector(posicionInicial.X, posicionInicial.Y, posicionInicial.Z));
			componentesPlataforma.Add(GetWorld()->SpawnActor<AcomponentePlataforma>(AcomponentePlataforma::StaticClass(), SpawnLocationCP));
			posicionInicial.Y += 600.0f;
			posicionInicial.Z += 140.0f;
			rotacionInicial.Roll = rotacionInicial.Roll * -1;

		}
		posicionInicial.Y -= 1530.0f;
		posicionInicial.Z += 800.0f;
	}

	//PISO HACIA LA IZQUIERDA

	FVector posicionInicialI = FVector(1180.0f, 50.0f, 1000.f);
	FRotator rotacionInicialI = FRotator(0.0f, 0.0f, -15);

	for (int nppI = 0; nppI < 5; nppI++)                        //NUMERO DE PISOS
	{
		rotacionInicialI.Roll = rotacionInicialI.Roll * -1;
		posicionInicialI.Z += 1500.0f;

		SpawnLocationCP.SetRotation(FQuat(rotacionInicialI));
		for (int ncpI = 0; ncpI < 5; ncpI++) {                               //NUMERO DE PLATAFORMAS

			SpawnLocationCP.SetLocation(FVector(posicionInicialI.X, posicionInicialI.Y, posicionInicialI.Z));
			componentesPlataforma.Add(GetWorld()->SpawnActor<AcomponentePlataforma>(AcomponentePlataforma::StaticClass(), SpawnLocationCP));
			posicionInicialI.Y += 700.0f;
			posicionInicialI.Z -= 140.0f;
			rotacionInicialI.Roll = rotacionInicialI.Roll * -1;

		}

		posicionInicialI.Y -= 100.0f;
		posicionInicialI.Z += 1000.0f;
	}






	FTransform SpawnLocationMuroBomba;
	SpawnLocationMuroBomba.SetLocation(FVector(1180.0f, -1100.0f, 400.0f));
	SpawnLocationMuroBomba.SetRotation(FQuat(FRotator(0.0f, 0.0f, 0.0f)));
	 GetWorld()->SpawnActor<AMuroBomba>(AMuroBomba::StaticClass(), SpawnLocationMuroBomba);
	//muroBomba1->SetActorScale3D(FVector(1.0f, 1.0f, 1.0f));
	// Definir la posición en la que queremos crear el cono disparador
	 FVector PosicionCono = FVector(1180.0f, -460.0f, 1260.0f);
	 FRotator RotacionCono = FRotator::ZeroRotator; // Rotación inicial sin rotación

	 // Comprobar si la clase del ConoDisparador está asignada
	 if (ClaseCono)
	 {
		 // Crear el ConoDisparador en la posición deseada
		 ACono* Cono = GetWorld()->SpawnActor<ACono>(ClaseCono, PosicionCono, RotacionCono);

		 if (Cono)
		 {
			 UE_LOG(LogTemp, Warning, TEXT("Cono disparador creado en la posición (370, -460, 1260)"));
		 }
	 }
}

/*void ADonkeyKong_L02GameMode::SpawnBarril()
{
	//if (barriles.Num() >= numeroMaximoBarriles) {
	if (contadorBarriles < numeroMaximoBarriles) {
		//Spawn de un objeto barril en la escena sobre la primera plataforma
		FTransform SpawnLocationBarril;
		SpawnLocationBarril.SetLocation(FVector(1160.0f, 900.0f, 860.0f));
		SpawnLocationBarril.SetRotation(FQuat(FRotator(90.0f, 0.0f, 0.0f)));
		//ABarril* barril01 = GetWorld()->SpawnActor<ABarril>(ABarril::StaticClass(), SpawnLocationBarril);
		barriles.Add(GetWorld()->SpawnActor<ABarril>(ABarril::StaticClass(), SpawnLocationBarril));
		contadorBarriles++;

		if (contadorBarriles >= numeroMaximoBarriles) {
			GetWorld()->GetTimerManager().ClearTimer(SpawnBarrilTimerHandle);
		}
	}
}*/