#include "MyPlayerController.h"
#include "MyFPSGameMode.h"             
#include "narisawaBranch/AutonomousUIController.h"    
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"

void AMyPlayerController::BeginPlay()
{
    Super::BeginPlay();

    // ブループリントでUIとAI Controllerのクラスが設定されているか確認
    if (PreGameWidgetClass && AutonomousUIControllerClass)
    {
        // UIウィジェットとAIコントローラーをワールドに生成
        MainWidgetInstance = CreateWidget<UUserWidget>(this, PreGameWidgetClass);
        UIControllerInstance = GetWorld()->SpawnActor<AAutonomousUIController>(AutonomousUIControllerClass);

        // 生成したAIコントローラーに、制御対象のUIを教える
        if (UIControllerInstance)
        {
            UIControllerInstance->SetTargetWidget(MainWidgetInstance);
        }

        // UIウィジェット内のボタンを探し出し、クリックイベントに関数を接続（バインド）
        if (auto* OptionButton = Cast<UButton>(MainWidgetInstance->GetWidgetFromName(TEXT("PreGameOptionButton1"))))
        {
            OptionButton->OnClicked.AddDynamic(this, &AMyPlayerController::OnPreGameOptionClicked);
        }
        // 他のボタンも必要であれば同様に接続します。

        // UIを画面に表示し、マウスカーソルを表示してUIを操作できるモードに設定
        MainWidgetInstance->AddToViewport();
        SetInputMode(FInputModeUIOnly()); // 入力をUIのみに限定
        bShowMouseCursor = true;          // マウスカーソルを表示
    }
}

void AMyPlayerController::OnPreGameOptionClicked()
{
    // 選択肢ボタンがクリックされたら、ここが実行
    UE_LOG(LogTemp, Log, TEXT("Pre-game option selected. Starting gameplay..."));

    // UIのWidgetSwitcherを探し、表示を独り言モード（Index 1）に切り替える
    if (auto* Switcher = Cast<UWidgetSwitcher>(MainWidgetInstance->GetWidgetFromName(TEXT("MainSwitcher"))))
    {
        Switcher->SetActiveWidgetIndex(1);
    }

    // AIコントローラーに独り言の開始を命令
    if (UIControllerInstance)
    {
        UIControllerInstance->StartMonologue();
    }

    // GameModeを取得し、ゲーム本編の開始を通知
    if (auto* GameMode = GetWorld()->GetAuthGameMode<AMyFPSGameMode>())
    {
        GameMode->StartGameplay();
    }

    // 入力モードをゲームプレイ用に変更し、マウスカーソルを非表示にする
    SetInputMode(FInputModeGameOnly()); // 入力をゲームのみに限定
    bShowMouseCursor = false;
}