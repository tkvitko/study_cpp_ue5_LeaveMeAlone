// LeaveMeAlone Game by Netologiya. All Rights Reserved.


#include "Player/LMADefaultCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/InputComponent.h"
#include "Components/LMAHealthComponent.h"
#include "Components/LMAEnduranceComponent.h"
#include "Components/LMAWeaponComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ALMADefaultCharacter::ALMADefaultCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
    
    // настройки компонента штатива
    SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
    SpringArmComponent->SetupAttachment(GetRootComponent());
    SpringArmComponent->SetUsingAbsoluteRotation(true);
    SpringArmComponent->TargetArmLength = ArmLength;
    SpringArmComponent->SetRelativeRotation(FRotator(YRotation, 0.0f, 0.0f));
    SpringArmComponent->bDoCollisionTest = false;
    SpringArmComponent->bEnableCameraLag = true;

    // настройки компонента камеры
    CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
    CameraComponent->SetupAttachment(SpringArmComponent);
    CameraComponent->SetFieldOfView(FOV);
    CameraComponent->bUsePawnControlRotation = false;
    
    // компонент здоровья
    HealthComponent = CreateDefaultSubobject<ULMAHealthComponent>("HealthComponent");
    
    // компонент выносливости
    EnduranceComponent = CreateDefaultSubobject<ULMAEnduranceComponent>("EnduranceComponent");
    
    // компонент оружия
    WeaponComponent = CreateDefaultSubobject<ULMAWeaponComponent>("Weapon");
    
    // запрет поворота персонажа в сторону камеры
    bUseControllerRotationPitch = false;
    bUseControllerRotationYaw = false;
    bUseControllerRotationRoll = false;

}

// Called when the game starts or when spawned
void ALMADefaultCharacter::BeginPlay()
{
	Super::BeginPlay();
    
    // установка курсора на уровне
    if (CursorMaterial) {
        CurrentCursor = UGameplayStatics::SpawnDecalAtLocation(GetWorld(), CursorMaterial, CursorSize, FVector(0));
    }
    
    OnHealthChanged(HealthComponent->GetHealth());
    
    // подписка на делегат о смерти персонажа
    HealthComponent->OnDeath.AddDynamic(this, &ALMADefaultCharacter::OnDeath);
//    HealthComponent->OnDeath.AddUObject(this, &ALMADefaultCharacter::OnDeath);
    
    // подписка на делегат об изменении здоровья
    HealthComponent->OnHealthChanged.AddUObject(this, &ALMADefaultCharacter::OnHealthChanged);
    
    // подписка на делегат об окончании выносливости
    EnduranceComponent->OnEmptyEndurance.AddUObject(this, &ALMADefaultCharacter::OnEmptyEndurance);
	
}

// Called every frame
void ALMADefaultCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    if (!(HealthComponent->IsDead()))
    {
        RotationPlayerOnCursor();
    }
}

// Called to bind functionality to input
void ALMADefaultCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
    
    // движение персонажа
    PlayerInputComponent->BindAxis("MoveForward", this, &ALMADefaultCharacter::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &ALMADefaultCharacter::MoveRight);
    PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &ALMADefaultCharacter::StartSprint);
    PlayerInputComponent->BindAction("Sprint", IE_Released, this, &ALMADefaultCharacter::StopSprint);
    
    // стрельба
    PlayerInputComponent->BindAction("ScrollCameraUp", IE_Pressed, this, &ALMADefaultCharacter::ScrollCameraUp);
    PlayerInputComponent->BindAction("ScrollCameraDown", IE_Pressed, this, &ALMADefaultCharacter::ScrollCameraDown);
    
    PlayerInputComponent->BindAction("Fire", IE_Pressed, WeaponComponent, &ULMAWeaponComponent::Fire);
    PlayerInputComponent->BindAction("Reload", IE_Pressed, WeaponComponent, &ULMAWeaponComponent::Reload);
}

void ALMADefaultCharacter::MoveForward(float Value)
{
    AddMovementInput(GetActorForwardVector(), Value);
}

void ALMADefaultCharacter::MoveRight(float Value)
{
    AddMovementInput(GetActorRightVector(), Value);
}

void ALMADefaultCharacter::ScrollCameraUp()
{
    if (ArmLength < ArmLengthMax) {
            ArmLength += ArmLengthChangeStep;
            SpringArmComponent->TargetArmLength = ArmLength;
        }
}

void ALMADefaultCharacter::ScrollCameraDown()
{
    if (ArmLength > ArmLenghtMin) {
            ArmLength -= ArmLengthChangeStep;
            SpringArmComponent->TargetArmLength = ArmLength;
        }
}

void ALMADefaultCharacter::StartSprint()
{
    if (!EnduranceComponent->IsEnduranceEmpty()) {
        UCharacterMovementComponent* CurrentCharacterMovement = GetCharacterMovement();
        CurrentCharacterMovement->MaxWalkSpeed = SprintSpeed;
        EnduranceComponent->EnableSpending();
    }
}

void ALMADefaultCharacter::StopSprint()
{
    UCharacterMovementComponent* CurrentCharacterMovement = GetCharacterMovement();
    CurrentCharacterMovement->MaxWalkSpeed = NormalSpeed;
    EnduranceComponent->EnableAccumulation();
}

void ALMADefaultCharacter::OnDeath()
{
    CurrentCursor->DestroyRenderState_Concurrent();
    PlayAnimMontage(DeathMontage);
    GetCharacterMovement()->DisableMovement();
    SetLifeSpan(5.0f);

    if (Controller)
    {
        Controller->ChangeState(NAME_Spectating);
    }
}

void ALMADefaultCharacter::OnEmptyEndurance() {
    StopSprint();
}

void ALMADefaultCharacter::RotationPlayerOnCursor()
{
    APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
    if (PC)
    {
        FHitResult ResultHit;
        PC->GetHitResultUnderCursor(ECC_GameTraceChannel1, true, ResultHit);
        float FindRotatorResultYaw = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), ResultHit.Location).Yaw;
        SetActorRotation(FQuat(FRotator(0.0f, FindRotatorResultYaw, 0.0f)));
        if (CurrentCursor)
        {
            CurrentCursor->SetWorldLocation(ResultHit.Location);
        }
    }
}

void ALMADefaultCharacter::OnHealthChanged(float NewHealth)
{
    GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString::Printf(TEXT("Health = %f"), NewHealth));
}
