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

	// Obtemos a localiza��o deste ator
	FVector LocalizacaoDoAtor = GetActorLocation();
	/* Indicamos que queremos que o final da esfera de raycasting seja
	Localiza��o do ator + 100 em x, y e z */
	FVector FinalDaEsferaDebug = LocalizacaoDoAtor + FVector(100, 100, 100);

	/* Criamos um componente de colis�o e setamos que ele ser� 
	uma esfera atrav�s da fun��o MakeSphere. Raio ser� 200 */
	FCollisionShape ColisaoEsferica = FCollisionShape::MakeSphere(200.f);

	/* Desenha uma esfera para analisarmos como ser� fisicamente a esfera
	que ser� criada em SweepMultiByChannel
	Ou seja, quem detecta a colis�o � SweepMultiByChannel
	DrawDebug � apenas para conseguir enxergar o raycasting em a��o*/
	DrawDebugSphere(GetWorld(), LocalizacaoDoAtor, ColisaoEsferica.GetSphereRadius(),
		200, FColor::Red, true, -1.f, (uint8)0, 0.5f);

	/* Aqui chamamos a fun��o e enviamos seus par�metros */
	bool OcorreuColisao = GetWorld()->SweepMultiByChannel
	(ResultadosColisao, LocalizacaoDoAtor, FinalDaEsferaDebug, FQuat::Identity,
		ECollisionChannel::ECC_WorldStatic, ColisaoEsferica);
	/* No nosso caso indica que o trace channel � WordStatic e determina
	que tipo de Canal de Colis�o a esfera deve analisar*/

	if (OcorreuColisao)
	{
		/* Auto � utilizado para que em tempo de compila��o
		o tipo de Colisoes seja estabelecido automaticamente
		dependendo do tipo de ResultadoColisao 
		
		J� que ResultadosColisao � um array, o for vai varrer esse array
		e a cada passada vai colocando o elemento na vari�vel auto& Colisoes
		Ent�o coloca na tela o nome do ator*/
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

