#include "MyFPSGameMode.h"
#include "MyPlayerController.h" // この後で作成するPlayerControllerのヘッダ
#include "UObject/ConstructorHelpers.h"

AMyFPSGameMode::AMyFPSGameMode()
{
    // このゲームモードで使われるPlayerControllerを、後で作成するカスタムクラスに指定
    PlayerControllerClass = AMyPlayerController::StaticClass();

    // DefaultPawnClassをnullptrに設定することで、ゲーム開始時に自動でキャラクターがスポーンするのを防ぐ
    DefaultPawnClass = nullptr;
}

void AMyFPSGameMode::StartGameplay()
{
    // PlayerControllerからこの関数が呼ばれると、デフォルトのPawn（プレイヤーキャラクター）をスポーン
    RestartPlayer(GetWorld()->GetFirstPlayerController());
}