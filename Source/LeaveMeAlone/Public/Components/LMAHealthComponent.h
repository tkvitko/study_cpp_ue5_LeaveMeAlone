// LeaveMeAlone Game by Netologiya. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LMAHealthComponent.generated.h"

// декларация делегата о смерте персонажа
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeath);
//DECLARE_MULTICAST_DELEGATE(FOnDeath);

// декларация делегата об изменении здоровья
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHealthChanged, float);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LEAVEMEALONE_API ULMAHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	ULMAHealthComponent();
    
    // получить текущее здоровье персонажа
    UFUNCTION(BlueprintCallable)
    float GetHealth() const { return Health; }
    
    // проверить, не умер ли персонаж
    UFUNCTION(BlueprintCallable)
    bool IsDead() const;
    
    bool AddHealth(float NewHealth);
    bool IsHealthFull() const;
    
    // объявление задекларированных выше делегатов (о смерти и об изменнии здоровья)
    UPROPERTY(BlueprintAssignable)
    FOnDeath OnDeath;
    
    FOnHealthChanged OnHealthChanged;

protected:
    // максимальное значение здоровья
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    float MaxHealth = 100.0f;
    
	virtual void BeginPlay() override;

private:
    
    // текущее здоровье персонажа
    float Health = 0.0f;
    
    // реакция на получение урона
    UFUNCTION()
    void OnTakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);
};
