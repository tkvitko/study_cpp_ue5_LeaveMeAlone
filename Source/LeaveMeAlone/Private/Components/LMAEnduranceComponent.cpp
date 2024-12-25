// LeaveMeAlone Game by Netologiya. All Rights Reserved.


#include "Components/LMAEnduranceComponent.h"


ULMAEnduranceComponent::ULMAEnduranceComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void ULMAEnduranceComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

void ULMAEnduranceComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    if (Spending && !IsEnduranceEmpty()) {
        Endurance -= Step;
        GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Blue, FString::Printf(TEXT("Endurance = %f"), Endurance));
    } else if (!Spending && !IsEnduranceFull()) {
        Endurance += Step;
        GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Blue, FString::Printf(TEXT("Endurance = %f"), Endurance));
    }
    
    if (IsEnduranceEmpty()) {
        OnEmptyEndurance.Broadcast();
    }
    
}

bool ULMAEnduranceComponent::IsEnduranceFull() {
    return FMath::IsNearlyEqual(Endurance, MaxEndurance);
}

bool ULMAEnduranceComponent::IsEnduranceEmpty() {
    return Endurance == 0.0f;
}

bool ULMAEnduranceComponent::IsEnduranceSpending() {
    return Spending;
}

void ULMAEnduranceComponent::EnableSpending() {
    Spending = true;
}

void ULMAEnduranceComponent::EnableAccumulation() {
    Spending = false;
}
