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
        // UI�E�B�W�F�b�g�𐶐����ĉ�ʂɒǉ�
        AutonomousWidgetInstance = CreateWidget<UUserWidget>(GetWorld(), AutonomousWidgetClass);
        if (AutonomousWidgetInstance)
        {
            AutonomousWidgetInstance->AddToViewport();

            // �E�B�W�F�b�g���̊e�v�f�ւ̎Q�Ƃ𖼑O�Ŏ擾���A�L���b�V������
            DialogueText = Cast<UTextBlock>(AutonomousWidgetInstance->GetWidgetFromName(TEXT("DialogueText")));
            OptionButton1 = Cast<UButton>(AutonomousWidgetInstance->GetWidgetFromName(TEXT("OptionButton1")));
            OptionButton2 = Cast<UButton>(AutonomousWidgetInstance->GetWidgetFromName(TEXT("OptionButton2")));

            if (!DialogueText || !OptionButton1 || !OptionButton2)
            {
                // �G���[���O: �K�v�ȃE�B�W�F�b�g��������Ȃ��ꍇ
                UE_LOG(LogTemp, Error, TEXT("AutonomousUIController: Failed to find one or more widgets in WBP_AutonomousUI. Check names."));
            }
        }
    }
}

void AAutonomousUIController::StartAutonomousTalking()
{
    // �Z���t���X�g����łȂ���΁A�����_���Ȏ��Ԍ��Talk()���Ăяo��
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
        // �����_���ɃZ���t��I��ŕ\��
        const int32 RandomIndex = FMath::RandRange(0, AutonomousDialogues.Num() - 1);
        DialogueText->SetText(FText::FromString(AutonomousDialogues[RandomIndex]));
    }

    // ���́u�b�������v���X�P�W���[������
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
        // �{�^���̃N���b�N�C�x���g�������I�Ɏ��s����
        TargetButton->OnClicked.Broadcast();
        UE_LOG(LogTemp, Log, TEXT("Option %d was force-selected by AutonomousUIController."), OptionIndex);
    }
}