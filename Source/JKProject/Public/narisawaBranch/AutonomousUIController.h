// AutonomousUIController.h

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AutonomousUIController.generated.h"

class UUserWidget;
class UTextBlock;
class UButton;

UCLASS()
class JKPROJECT_API AAutonomousUIController : public AActor
{
    GENERATED_BODY()

public:
    AAutonomousUIController();

protected:
    virtual void BeginPlay() override;

public:
    /** UI�ɋ����I�ɑI������I�΂���֐��B�O������Ăяo�����Ƃ�z��B */
    UFUNCTION(BlueprintCallable, Category = "Autonomous UI")
    void ForceSelectOption(int32 OptionIndex);

private:
    /** UI�E�B�W�F�b�g�̃N���X�BBlueprint�Őݒ肷��B */
    UPROPERTY(EditAnywhere, Category = "Autonomous UI", meta = (AllowPrivateAccess = "true"))
    TSubclassOf<UUserWidget> AutonomousWidgetClass;

    /** �����I�ɘb���Z���t�̃��X�g�BBlueprint�Őݒ肷��B */
    UPROPERTY(EditAnywhere, Category = "Autonomous UI", meta = (AllowPrivateAccess = "true"))
    TArray<FString> AutonomousDialogues;

    /** �b��������Ԋu�i�b�j�B�ŏ��l�ƍő�l�B*/
    UPROPERTY(EditAnywhere, Category = "Autonomous UI", meta = (AllowPrivateAccess = "true"))
    FVector2D TalkingIntervalRange = FVector2D(5.0f, 15.0f);

    /** �������ꂽUI�E�B�W�F�b�g�ւ̃|�C���^ */
    UPROPERTY()
    TObjectPtr<UUserWidget> AutonomousWidgetInstance;

    /** UI����TextBlock�ւ̃|�C���^ */
    UPROPERTY()
    TObjectPtr<UTextBlock> DialogueText;

    /** UI����Button�ւ̃|�C���^ */
    UPROPERTY()
    TObjectPtr<UButton> OptionButton1;

    /** UI����Button�ւ̃|�C���^ */
    UPROPERTY()
    TObjectPtr<UButton> OptionButton2;

    /** �b�������鏈�����Ăяo�����߂̃^�C�}�[�n���h�� */
    FTimerHandle TalkTimerHandle;

    /** UI�����������A�Q�Ƃ��L���b�V������ */
    void InitializeUI();

    /** �����I�ɘb���������J�n���� */
    void StartAutonomousTalking();

    /** ���ۂɃZ���t��I���UI�ɕ\������ */
    void Talk();
};