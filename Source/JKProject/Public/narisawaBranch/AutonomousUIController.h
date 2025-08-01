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
    /** UIに強制的に選択肢を選ばせる関数。外部から呼び出すことを想定。 */
    UFUNCTION(BlueprintCallable, Category = "Autonomous UI")
    void ForceSelectOption(int32 OptionIndex);

private:
    /** UIウィジェットのクラス。Blueprintで設定する。 */
    UPROPERTY(EditAnywhere, Category = "Autonomous UI", meta = (AllowPrivateAccess = "true"))
    TSubclassOf<UUserWidget> AutonomousWidgetClass;

    /** 自律的に話すセリフのリスト。Blueprintで設定する。 */
    UPROPERTY(EditAnywhere, Category = "Autonomous UI", meta = (AllowPrivateAccess = "true"))
    TArray<FString> AutonomousDialogues;

    /** 話しかける間隔（秒）。最小値と最大値。*/
    UPROPERTY(EditAnywhere, Category = "Autonomous UI", meta = (AllowPrivateAccess = "true"))
    FVector2D TalkingIntervalRange = FVector2D(5.0f, 15.0f);

    /** 生成されたUIウィジェットへのポインタ */
    UPROPERTY()
    TObjectPtr<UUserWidget> AutonomousWidgetInstance;

    /** UI内のTextBlockへのポインタ */
    UPROPERTY()
    TObjectPtr<UTextBlock> DialogueText;

    /** UI内のButtonへのポインタ */
    UPROPERTY()
    TObjectPtr<UButton> OptionButton1;

    /** UI内のButtonへのポインタ */
    UPROPERTY()
    TObjectPtr<UButton> OptionButton2;

    /** 話しかける処理を呼び出すためのタイマーハンドル */
    FTimerHandle TalkTimerHandle;

    /** UIを初期化し、参照をキャッシュする */
    void InitializeUI();

    /** 自律的に話す処理を開始する */
    void StartAutonomousTalking();

    /** 実際にセリフを選んでUIに表示する */
    void Talk();
};