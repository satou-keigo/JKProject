#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MyFPSGameMode.generated.h"

UCLASS()
class YOURPROJECT_API AMyFPSGameMode : public AGameModeBase
{
    GENERATED_BODY()

public:
    AMyFPSGameMode();

    /** �O������̌Ăяo���ɉ����āA�v���C���[�L�����N�^�[���X�|�[�������Q�[���v���C���J�n */
    void StartGameplay();
};