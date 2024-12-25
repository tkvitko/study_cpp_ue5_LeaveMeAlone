// LeaveMeAlone Game by Netologiya. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LMAEnduranceComponent.generated.h"

// декларация делегата об окончании выносливоси
DECLARE_MULTICAST_DELEGATE(FOnEmptyEndurance)


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LEAVEMEALONE_API ULMAEnduranceComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ULMAEnduranceComponent();
    
    bool IsEnduranceFull();
    bool IsEnduranceEmpty();
    bool IsEnduranceSpending();
    
    void EnableSpending();
    void EnableAccumulation();
    
    // объявление задекларированных выше делегатов
    FOnEmptyEndurance OnEmptyEndurance;

protected:
	virtual void BeginPlay() override;
    
    // максимальная выносливоть
    float MaxEndurance = 100.0f;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
    // текущая выносливость
    float Endurance = 100.0f;
    bool Spending = false;
    float Step = 1;
};
