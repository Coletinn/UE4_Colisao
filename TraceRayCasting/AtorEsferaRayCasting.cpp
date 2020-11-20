// Fill out your copyright notice in the Description page of Project Settings.


#include "AtorEsferaRayCasting.h"
#include "Components/BillboardComponent.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"

// Sets default values
AAtorEsferaRayCasting::AAtorEsferaRayCasting()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	/* Cria um componente apenas para dar uma possibilidade visual
	quando usarmos no editor */
	UBillboardComponent* BillBoard = CreateDefaultSubobject<UBillboardComponent>
		(FName("Billboard"));
	RootComponent = BillBoard;

}

// Called when the game starts or when spawned
void AAtorEsferaRayCasting::BeginPlay()
{
	Super::BeginPlay();

	/* Criado um array capaz de armazenar Structs do Tipo FHitResult
	*/
	TArray<FHitResult> ResultadosColisao;

	// Obtemos a localização deste ator
	FVector LocalizacaoDoAtor = GetActorLocation();
	/* Indicamos que queremos que o final da esfera de raycasting seja
	Localização do ator + 100 em x, y e z */
	FVector FinalDaEsferaDebug = LocalizacaoDoAtor + FVector(100, 100, 100);

	/* Criamos um componente de colisão e setamos que ele será 
	uma esfera através da função MakeSphere. Raio será 200 */
	FCollisionShape ColisaoEsferica = FCollisionShape::MakeSphere(200.f);

	/* Desenha uma esfera para analisarmos como será fisicamente a esfera
	que será criada em SweepMultiByChannel
	Ou seja, quem detecta a colisão é SweepMultiByChannel
	DrawDebug é apenas para conseguir enxergar o raycasting em ação*/
	DrawDebugSphere(GetWorld(), LocalizacaoDoAtor, ColisaoEsferica.GetSphereRadius(),
		200, FColor::Red, true, -1.f, (uint8)0, 0.5f);

	/* Aqui chamamos a função e enviamos seus parâmetros */
	bool OcorreuColisao = GetWorld()->SweepMultiByChannel
	(ResultadosColisao, LocalizacaoDoAtor, FinalDaEsferaDebug, FQuat::Identity,
		ECollisionChannel::ECC_WorldStatic, ColisaoEsferica);
	/* No nosso caso indica que o trace channel é WordStatic e determina
	que tipo de Canal de Colisão a esfera deve analisar*/

	if (OcorreuColisao)
	{
		/* Auto é utilizado para que em tempo de compilação
		o tipo de Colisoes seja estabelecido automaticamente
		dependendo do tipo de ResultadoColisao 
		
		Já que ResultadosColisao é um array, o for vai varrer esse array
		e a cada passada vai colocando o elemento na variável auto& Colisoes
		Então coloca na tela o nome do ator*/
		for (auto& Colisoes : ResultadosColisao)
		{
			UE_LOG(LogTemp, Error, TEXT("Nome do ator %s"), *Colisoes.Actor->GetName());
		}
	}


}

// Called every frame
void AAtorEsferaRayCasting::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

