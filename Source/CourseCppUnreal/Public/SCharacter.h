// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class USInteractionComponent;
class UAnimMontage;

UCLASS()
class COURSECPPUNREAL_API ASCharacter : public ACharacter {
  GENERATED_BODY()

public:
  // Sets default values for this character's properties
  ASCharacter();

protected:
  UPROPERTY(VisibleAnywhere)
  USpringArmComponent* SpringArmComp;

  UPROPERTY()
  UCameraComponent* CameraComp;

  UPROPERTY()
  USInteractionComponent* InteractionComp;

  UPROPERTY(EditAnywhere)
  TSubclassOf<AActor> ProjectileClass;

    UPROPERTY(EditAnywhere)
  float AnimationDelay;

  UPROPERTY(EditAnywhere)
  UAnimMontage* AttackAnim;

  // Called when the game starts or when spawned
  virtual void BeginPlay() override;

  void MoveForward(float value);
  void MoveRight(float value);

  void PrimaryAttack();

  void PrimaryInteract();

  void PrimaryAttack_TimeElapsed();

  FTimerHandle TimerHandle_PrimaryAttack;

public:
  // Called every frame
  virtual void Tick(float DeltaTime) override;

  // Called to bind functionality to input
  virtual void SetupPlayerInputComponent(
      
  class UInputComponent* PlayerInputComponent) override;


};
