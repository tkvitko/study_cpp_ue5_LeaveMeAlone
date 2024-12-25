// LeaveMeAlone Game by Netologiya. All Rights Reserved.


#include "LevelActors/Pickup/LMAHealthPickup.h"
#include "Components/LMAHealthComponent.h"
#include "Components/SphereComponent.h"
#include "Player/LMADefaultCharacter.h"

// Sets default values
ALMAHealthPickup::ALMAHealthPickup()
{
	PrimaryActorTick.bCanEverTick = true;
    
    SphereComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
    SphereComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    SphereComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
    SetRootComponent(SphereComponent);

}

void ALMAHealthPickup::BeginPlay()
{
	Super::BeginPlay();
	
}

void ALMAHealthPickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALMAHealthPickup::NotifyActorBeginOverlap(AActor* OtherActor)
// функция, которая сработает при пересечении персонажем капсулы пикапа
{
    Super::NotifyActorBeginOverlap(OtherActor);
    const auto Charcter = Cast<ALMADefaultCharacter>(OtherActor);
    if (GivePickup(Charcter))
    {
        PickupWasTaken();
    }
}

bool ALMAHealthPickup::GivePickup(ALMADefaultCharacter* Character)
// взятие пикапа персонажем
{
    const auto HealthComponent = Character->GetHealthComponent();
    if (!HealthComponent) return false;

    return HealthComponent->AddHealth(HealthFromPickup);
}

void ALMAHealthPickup::PickupWasTaken()
// активности после взятие пикапа - скрытие пикапа на время респауна
{
    SphereComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
    GetRootComponent()->SetVisibility(false,true);

    FTimerHandle RespawnTimerHandle;
    GetWorldTimerManager().SetTimer(RespawnTimerHandle, this, &ALMAHealthPickup::RespawnPickup, RespawnTime);
}

void ALMAHealthPickup::RespawnPickup()
// возврат пикапа на уровень после истечения таймера
{
    SphereComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
    GetRootComponent()->SetVisibility(true,true);
}
