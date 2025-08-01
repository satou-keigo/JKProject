#include "MyFPSGameMode.h"
#include "MyPlayerController.h" // ���̌�ō쐬����PlayerController�̃w�b�_
#include "UObject/ConstructorHelpers.h"

AMyFPSGameMode::AMyFPSGameMode()
{
    // ���̃Q�[�����[�h�Ŏg����PlayerController���A��ō쐬����J�X�^���N���X�Ɏw��
    PlayerControllerClass = AMyPlayerController::StaticClass();

    // DefaultPawnClass��nullptr�ɐݒ肷�邱�ƂŁA�Q�[���J�n���Ɏ����ŃL�����N�^�[���X�|�[������̂�h��
    DefaultPawnClass = nullptr;
}

void AMyFPSGameMode::StartGameplay()
{
    // PlayerController���炱�̊֐����Ă΂��ƁA�f�t�H���g��Pawn�i�v���C���[�L�����N�^�[�j���X�|�[��
    RestartPlayer(GetWorld()->GetFirstPlayerController());
}