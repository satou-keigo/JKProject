// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterInterface.h"
#include "Kismet/KismetSystemLibrary.h"

//‰¼ŠÖ”
void ICharacterInterface::shot()
{
    if (GEngine && GEngine->GetWorld())
    {
        UKismetSystemLibrary::PrintString(GEngine->GetWorld(), "shot", true, true, FLinearColor(0.0f, 0.66f, 1.0f, 1.0f), 2.0f);
    }
}

// Add default functionality here for any ICharacterInterface functions that are not pure virtual.
