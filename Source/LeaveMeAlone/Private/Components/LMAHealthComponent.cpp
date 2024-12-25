// LeaveMeAlone Game by Netologiya. All Rights Reserved.


#include "Components/LMAHealthComponent.h"



ULMAHealthComponent::ULMAHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

bool ULMAHealthComponent::IsDead() const
{
    return Health <= 0.0f;
}


void ULMAHealthComponent::BeginPlay()
{
	Super::BeginPlay();
    Health = MaxHealth;
    
    // рассылка делегата об изменении здороья
    OnHealthChanged.Broadcast(Health);
    
    // подписка на вызов делегата:
    AActor* OwnerComponent = GetOwner();
    if (OwnerComponent)
    {
        OwnerComponent->OnTakeAnyDamage.AddDynamic(this, &ULMAHealthComponent::OnTakeAnyDamage);
    }
}

void ULMAHealthComponent::OnTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy,
    AActor* DamageCauser)
{
    if (IsDead()) return;

    Health = FMath::Clamp(Health - Damage, 0.0f, MaxHealth);
    
    // рассылка делегата об изменении здороья
    OnHealthChanged.Broadcast(Health);
    
    // если в результате получения урона персонаж погиб, рассылка подписчикам делегата
    if (IsDead())
    {
        OnDeath.Broadcast();
    }
}

bool ULMAHealthComponent::AddHealth(float NewHealth)
{
    if (IsDead() || IsHealthFull()) return false;

    Health = FMath::Clamp(Health+NewHealth, 0.0f, MaxHealth);
    OnHealthChanged.Broadcast(Health);
    return true;
}

bool ULMAHealthComponent::IsHealthFull() const
{
    return FMath::IsNearlyEqual(Health, MaxHealth);
}
