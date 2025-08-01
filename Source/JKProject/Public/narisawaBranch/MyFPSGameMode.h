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

    /** 外部からの呼び出しに応じて、プレイヤーキャラクターをスポーンさせゲームプレイを開始 */
    void StartGameplay();
};