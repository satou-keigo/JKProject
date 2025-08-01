// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputAction.h"
#include "CharacterInterface.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class JKPROJECT_API APlayerCharacter : public ACharacter , public ICharacterInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// インプットアクション
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Input")
	const UInputAction* InputAction;

	// バインドする関数
	void IA_Move(const FInputActionInstance& InputActionInst);
	void IA_Look(const FInputActionInstance& InputActionInst);
	void IA_Interact(const FInputActionInstance& InputActionInst);

};
