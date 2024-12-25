// LeaveMeAlone Game by Netologiya. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "LMAPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class LEAVEMEALONE_API ALMAPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
    ALMAPlayerController();
    
protected:
    virtual void BeginPlay() override;
    
    // для переопределения переменной дижвковой функции для верного направления камеры после смерти персонажа
    virtual void BeginSpectatingState() override;
};
