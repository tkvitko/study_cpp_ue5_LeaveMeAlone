// LeaveMeAlone Game by Netologiya. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LMABaseWeapon.generated.h"

class USkeletalMeshComponent;

USTRUCT(BlueprintType)
struct FAmmoWeapon
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Weapon")
    int32 Bullets;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Weapon")
    int32 Clips;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Weapon")
    bool Infinite;
};

UCLASS()
class LEAVEMEALONE_API ALMABaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:
	ALMABaseWeapon();
    void Fire();
    void ChangeClip();

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Weapon")
    USkeletalMeshComponent* WeaponComponent;
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Weapon")
    float TraceDistance = 800.0f;
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Weapon")
    FAmmoWeapon AmmoWeapon {30, 0, true};
    
    // выстрел
    void Shoot();
    void DecrementBullets();
    bool IsCurrentClipEmpty() const;
    
	virtual void BeginPlay() override;
    
private:
    FAmmoWeapon CurrentAmmoWeapon;

public:
	virtual void Tick(float DeltaTime) override;
    FAmmoWeapon GetCurrentAmmoWeapon() const { return CurrentAmmoWeapon; }

};
