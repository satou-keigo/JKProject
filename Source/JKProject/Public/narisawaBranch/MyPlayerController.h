#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"


class UUserWidget;
class AAutonomousUIController;

UCLASS()
class JKPROJECT_API AMyPlayerController : public APlayerController
{
    GENERATED_BODY()

protected:
    virtual void BeginPlay() override;

private:
    UPROPERTY(EditAnywhere, Category = "UI", meta = (AllowPrivateAccess = "true"))
    TSubclassOf<UUserWidget> PreGameWidgetClass;

    UPROPERTY(EditAnywhere, Category = "UI", meta = (AllowPrivateAccess = "true"))
    TSubclassOf<AAutonomousUIController> AutonomousUIControllerClass;

    /** ��������UI�E�B�W�F�b�g�̃C���X�^���X��ێ�����|�C���^ */
    UPROPERTY()
    TObjectPtr<UUserWidget> MainWidgetInstance;

    /** ��������AI�R���g���[���[�̃C���X�^���X��ێ�����|�C���^ */
    UPROPERTY()
    TObjectPtr<AAutonomousUIController> UIControllerInstance;

    /** �v���C�O�̑I�����{�^�����N���b�N���ꂽ���Ƀo�C���h�i�ڑ��j�����֐� */
    UFUNCTION()
    void OnPreGameOptionClicked();
};