// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputAction.h"
#include "CharacterInterface.h"
#include "PlayerPawn.generated.h"

UCLASS()
class JKPROJECT_API APlayerPawn : public APawn 
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// �C���v�b�g�A�N�V����
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Input")
	const UInputAction* InputAction;
	// �o�C���h����֐�
	void IA_Move(const FInputActionInstance& InputActionInst);
	void IA_Look(const FInputActionInstance& InputActionInst);
	void IA_Interact(const FInputActionInstance& InputActionInst);

};
