// Fill out your copyright notice in the Description page of Project Settings.


#include "RayCastPlayerController.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"

void ARayCastPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	check(InputComponent);
	InputComponent->BindAction("Atirar", EInputEvent::IE_Released,
		this, &ARayCastPlayerController::AtirarRayCast);
}




void ARayCastPlayerController::AtirarRayCast()
{
	float Tamanho = 1000.f;
	/* Neste caso foi estabelecido que a origem do radio será a camera
	Logo achamos o vetor "frente" da câmera(para onde a câmera está
	apontando */
	FVector Direcao = PlayerCameraManager->GetActorForwardVector();

	/* Ponto de origem, de onde vai ser disparado o raio(Raycast)*/
	FVector Origem = PlayerCameraManager->GetCameraLocation();

	/* Será o vetor de origem somado com o vetor direção */
	FVector PontoFinal = LocalizacaoPontoDeVisaoDoPlayer + 
		(RotacaoPontoDeVisaoDoPlayer.Vector() * Tamanho);

	/* Variável struct que vai receber todos os detalhes da colisão do raio*/
	FHitResult ResultadodoHit;


	FCollisionQueryParams CollisionParams;

	bool ColidiuComAlgo = GetWorld()->LineTraceSingleByChannel(ResultadodoHit,
		Origem, PontoFinal, ECollisionChannel::ECC_Visibility, CollisionParams);
	DrawDebugLine(GetWorld(), Origem, PontoFinal, FColor::Red, false, 10.f, (uint8)0, 1.f);

	/* Se o raio colidir com algo antes de terminar, seu traço vai retornar true em
	ColdiuComAlgo*/
	if (ColidiuComAlgo)
	{
		UE_LOG(LogTemp, Error, TEXT("Ator %s"), *ResultadodoHit.Actor->GetName());
		UE_LOG(LogTemp, Error, TEXT("Local %s"), *ResultadodoHit.Location.ToString());
	}

}




void ARayCastPlayerController::Tick(float Deltatime)
{
	Super::Tick(Deltatime);

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(LocalizacaoPontoDeVisaoDoPlayer,
		RotacaoPontoDeVisaoDoPlayer);
}
