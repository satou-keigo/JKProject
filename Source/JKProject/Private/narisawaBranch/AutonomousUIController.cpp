// AutonomousUIController.cpp

#include "narisawaBranch/AutonomousUIController.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "TimerManager.h"

AAutonomousUIController::AAutonomousUIController()
{
    PrimaryActorTick.bCanEverTick = false;
}

void AAutonomousUIController::BeginPlay()
{
    Super::BeginPlay();

    InitializeUI();
    StartAutonomousTalking();
}

void AAutonomousUIController::InitializeUI()
{
    if (AutonomousWidgetClass)
    {
        // UIウィジェットを生成して画面に追加
        AutonomousWidgetInstance = CreateWidget<UUserWidget>(GetWorld(), AutonomousWidgetClass);
        if (AutonomousWidgetInstance)
        {
            AutonomousWidgetInstance->AddToViewport();

            // ウィジェット内の各要素への参照を名前で取得し、キャッシュする
            DialogueText = Cast<UTextBlock>(AutonomousWidgetInstance->GetWidgetFromName(TEXT("DialogueText")));
            OptionButton1 = Cast<UButton>(AutonomousWidgetInstance->GetWidgetFromName(TEXT("OptionButton1")));
            OptionButton2 = Cast<UButton>(AutonomousWidgetInstance->GetWidgetFromName(TEXT("OptionButton2")));

            if (!DialogueText || !OptionButton1 || !OptionButton2)
            {
                // エラーログ: 必要なウィジェットが見つからない場合
                UE_LOG(LogTemp, Error, TEXT("AutonomousUIController: Failed to find one or more widgets in WBP_AutonomousUI. Check names."));
            }
        }
    }
}

void AAutonomousUIController::StartAutonomousTalking()
{
    // セリフリストが空でなければ、ランダムな時間後にTalk()を呼び出す
    if (AutonomousDialogues.Num() > 0)
    {
        const float Interval = FMath::RandRange(TalkingIntervalRange.X, TalkingIntervalRange.Y);
        GetWorld()->GetTimerManager().SetTimer(TalkTimerHandle, this, &AAutonomousUIController::Talk, Interval, false);
    }
}

void AAutonomousUIController::Talk()
{
    if (DialogueText && AutonomousDialogues.Num() > 0)
    {
        // ランダムにセリフを選んで表示
        const int32 RandomIndex = FMath::RandRange(0, AutonomousDialogues.Num() - 1);
        DialogueText->SetText(FText::FromString(AutonomousDialogues[RandomIndex]));
    }

    // 次の「話しかけ」をスケジュールする
    StartAutonomousTalking();
}

void AAutonomousUIController::ForceSelectOption(int32 OptionIndex)
{
    UButton* TargetButton = nullptr;

    switch (OptionIndex)
    {
    case 1:
        TargetButton = OptionButton1;
        break;
    case 2:
        TargetButton = OptionButton2;
        break;
    default:
        break;
    }

    if (TargetButton && TargetButton->OnClicked.IsBound())
    {
        // ボタンのクリックイベントを強制的に実行する
        TargetButton->OnClicked.Broadcast();
        UE_LOG(LogTemp, Log, TEXT("Option %d was force-selected by AutonomousUIController."), OptionIndex);
    }
}