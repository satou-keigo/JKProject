#include "MyPlayerController.h"
#include "MyFPSGameMode.h"             
#include "narisawaBranch/AutonomousUIController.h"    
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"

void AMyPlayerController::BeginPlay()
{
    Super::BeginPlay();

    // �u���[�v�����g��UI��AI Controller�̃N���X���ݒ肳��Ă��邩�m�F
    if (PreGameWidgetClass && AutonomousUIControllerClass)
    {
        // UI�E�B�W�F�b�g��AI�R���g���[���[�����[���h�ɐ���
        MainWidgetInstance = CreateWidget<UUserWidget>(this, PreGameWidgetClass);
        UIControllerInstance = GetWorld()->SpawnActor<AAutonomousUIController>(AutonomousUIControllerClass);

        // ��������AI�R���g���[���[�ɁA����Ώۂ�UI��������
        if (UIControllerInstance)
        {
            UIControllerInstance->SetTargetWidget(MainWidgetInstance);
        }

        // UI�E�B�W�F�b�g���̃{�^����T���o���A�N���b�N�C�x���g�Ɋ֐���ڑ��i�o�C���h�j
        if (auto* OptionButton = Cast<UButton>(MainWidgetInstance->GetWidgetFromName(TEXT("PreGameOptionButton1"))))
        {
            OptionButton->OnClicked.AddDynamic(this, &AMyPlayerController::OnPreGameOptionClicked);
        }
        // ���̃{�^�����K�v�ł���Γ��l�ɐڑ����܂��B

        // UI����ʂɕ\�����A�}�E�X�J�[�\����\������UI�𑀍�ł��郂�[�h�ɐݒ�
        MainWidgetInstance->AddToViewport();
        SetInputMode(FInputModeUIOnly()); // ���͂�UI�݂̂Ɍ���
        bShowMouseCursor = true;          // �}�E�X�J�[�\����\��
    }
}

void AMyPlayerController::OnPreGameOptionClicked()
{
    // �I�����{�^�����N���b�N���ꂽ��A���������s
    UE_LOG(LogTemp, Log, TEXT("Pre-game option selected. Starting gameplay..."));

    // UI��WidgetSwitcher��T���A�\����Ƃ茾���[�h�iIndex 1�j�ɐ؂�ւ���
    if (auto* Switcher = Cast<UWidgetSwitcher>(MainWidgetInstance->GetWidgetFromName(TEXT("MainSwitcher"))))
    {
        Switcher->SetActiveWidgetIndex(1);
    }

    // AI�R���g���[���[�ɓƂ茾�̊J�n�𖽗�
    if (UIControllerInstance)
    {
        UIControllerInstance->StartMonologue();
    }

    // GameMode���擾���A�Q�[���{�҂̊J�n��ʒm
    if (auto* GameMode = GetWorld()->GetAuthGameMode<AMyFPSGameMode>())
    {
        GameMode->StartGameplay();
    }

    // ���̓��[�h���Q�[���v���C�p�ɕύX���A�}�E�X�J�[�\�����\���ɂ���
    SetInputMode(FInputModeGameOnly()); // ���͂��Q�[���݂̂Ɍ���
    bShowMouseCursor = false;
}