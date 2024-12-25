// LeaveMeAlone Game by Netologiya. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "LMADefaultCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class ULMAHealthComponent;
class ULMAWeaponComponent;
class UAnimMontage;

UCLASS()
class LEAVEMEALONE_API ALMADefaultCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ALMADefaultCharacter();
    
    UFUNCTION()
    ULMAHealthComponent* GetHealthComponent() const { return HealthComponent; }
    
    UFUNCTION()
    ULMAEnduranceComponent* GetEnduranceComponent() const { return EnduranceComponent; }

protected:
    // компонент штатива
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    USpringArmComponent* SpringArmComponent;

    // компонент камеры
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UCameraComponent* CameraComponent;
    
    // компонент здоровья
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components|Health")
    ULMAHealthComponent* HealthComponent;
    
    // компонент выносливости
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components|Endurance")
    ULMAEnduranceComponent* EnduranceComponent;
    
    // компонент оружия
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    ULMAWeaponComponent* WeaponComponent;
    
    // курсор и его материал
    UPROPERTY()
    UDecalComponent* CurrentCursor = nullptr;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cursor")
    UMaterialInterface* CursorMaterial = nullptr;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cursor")
    FVector CursorSize = FVector(20.0f, 40.0f, 40.0f);
    
    // длина штатива камеры
    UPROPERTY(EditAnywhere, meta = (ClampMin = "700.0", ClampMax = "4000.0", UIMin = "700.0", UIMax = "4000.0"))
    float ArmLength = 1200.0f;
    
    // переменная, которая хранит указательно на анимацию смерти персонажа
    UPROPERTY(EditDefaultsOnly, Category="Animation")
    UAnimMontage* DeathMontage;
    
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
    
private:
    // параметры камеры персонажа
    float YRotation = -65.0f;
    float FOV = 65.0f;
    int ArmLenghtMin = 700;
    int ArmLengthMax = 2000;
    int ArmLengthChangeStep = 300;
    
    // скорость персонажа
    int NormalSpeed = 300;
    int SprintSpeed = 600;
    
    // обработка событий с клавиатуры и мыши
    void MoveForward(float Value);
    void MoveRight(float Value);
    void ScrollCameraUp();
    void ScrollCameraDown();
    void StartSprint();
    void StopSprint();
    
    // функция для обработки получения делегата о смерти персонажа
    void OnDeath();
    
    // функция для обработки получения делегата об изменении здоровья
    void OnHealthChanged(float NewHealth);
    
    // реакция на окончание выносливости
    void OnEmptyEndurance();
    
    // для отключение вращения персонажа после смерти
    void RotationPlayerOnCursor();
};
