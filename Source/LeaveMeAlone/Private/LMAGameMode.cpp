// LeaveMeAlone Game by Netologiya. All Rights Reserved.


#include "LMAGameMode.h"
#include "Player/LMADefaultCharacter.h"
#include "Player/LMAPlayerController.h"

ALMAGameMode::ALMAGameMode() {
    DefaultPawnClass = ALMADefaultCharacter::StaticClass();
    PlayerControllerClass = ALMAPlayerController::StaticClass();
}
