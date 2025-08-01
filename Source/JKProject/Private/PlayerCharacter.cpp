// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(RootComponent);

	// Input Mapping Context�uIMC_Player�v��ǂݍ���
	DefaultMappingContext = LoadObject<UInputMappingContext>(nullptr, TEXT("/Game/satoBranch/Inputs/IMC_Player"));

	// Input Action�uIA_Move�v��ǂݍ���
	ControlAction = LoadObject<UInputAction>(nullptr, TEXT("/Game/satoBranch/Inputs/IA_Move"));

	CameraControl = LoadObject<UInputAction>(nullptr, TEXT("/Game/satoBranch/Inputs/IA_Look"));

}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	ICharacterInterface::shot();
	//Add Input Mapping Context
	if (const APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {
		// ControlBall��IA_Control��Triggered��Bind����
		EnhancedInputComponent->BindAction(ControlAction, ETriggerEvent::Triggered, this, &APlayerCharacter::ControlCharacter);
		EnhancedInputComponent->BindAction(CameraControl, ETriggerEvent::Triggered, this, &APlayerCharacter::CameraMove);
	}
}

void APlayerCharacter::ControlCharacter(const FInputActionValue& Value)
{
	// input��Value��Vector2D�ɕϊ��ł���
	const FVector2D V = Value.Get<FVector2D>();
	AddMovementInput(FVector(0, 1, 0), V.X);
	AddMovementInput(FVector(1, 0, 0), V.Y);
}

void APlayerCharacter::CameraMove(const FInputActionValue& Value)
{
	// input��Value��Vector2D�ɕϊ��ł���
	FVector2D v = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(v.X);
		AddControllerPitchInput(v.Y);

		// Pawn�������Ă���Control�̊p�x���擾����
		FRotator controlRotate = GetControlRotation();

		// PlayerController�̊p�x��ݒ肷��
		UGameplayStatics::GetPlayerController(this, 0)->SetControlRotation(FRotator(controlRotate.Pitch, controlRotate.Yaw, 0.0f));
	}
}