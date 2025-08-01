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

    /** 生成したUIウィジェットのインスタンスを保持するポインタ */
    UPROPERTY()
    TObjectPtr<UUserWidget> MainWidgetInstance;

    /** 生成したAIコントローラーのインスタンスを保持するポインタ */
    UPROPERTY()
    TObjectPtr<AAutonomousUIController> UIControllerInstance;

    /** プレイ前の選択肢ボタンがクリックされた時にバインド（接続）される関数 */
    UFUNCTION()
    void OnPreGameOptionClicked();
};