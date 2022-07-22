// Fill out your copyright notice in the Description page of Project Settings.

#include "SCharacter.h"
#include "Animation/AnimMontage.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "SInteractionComponent.h"

// Sets default values
ASCharacter::ASCharacter() {
  // Set this character to call Tick() every frame.  You can turn this off to
  // improve performance if you don't need it.
  PrimaryActorTick.bCanEverTick = true;

  SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");
  SpringArmComp->bUsePawnControlRotation = true;
  SpringArmComp->SetupAttachment(RootComponent);

  CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");
  CameraComp->SetupAttachment(SpringArmComp);

  InteractionComp =
      CreateDefaultSubobject<USInteractionComponent>(TEXT("InteractionComp"));

  GetCharacterMovement()->bOrientRotationToMovement = true;

  bUseControllerRotationYaw = false;
}

// Called when the game starts or when spawned
void ASCharacter::BeginPlay() { Super::BeginPlay(); }

// Called every frame
void ASCharacter::Tick(float DeltaTime) { Super::Tick(DeltaTime); }

// Called to bind functionality to input
void ASCharacter::SetupPlayerInputComponent(
    UInputComponent* PlayerInputComponent) {
  Super::SetupPlayerInputComponent(PlayerInputComponent);

  PlayerInputComponent->BindAxis(
      "MoveForward",
      this,
      &ASCharacter::MoveForward);
  PlayerInputComponent->BindAxis("MoveRight", this, &ASCharacter::MoveRight);

  PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
  PlayerInputComponent->BindAxis(
      "LookUp",
      this,
      &APawn::AddControllerPitchInput);

  PlayerInputComponent->BindAction(
      "PrimaryAttack",
      IE_Pressed,
      this,
      &ASCharacter::PrimaryAttack);
  PlayerInputComponent
      ->BindAction("Jump", IE_Pressed, this, &ASCharacter::Jump);
  PlayerInputComponent->BindAction(
      "PrimaryInteract",
      IE_Pressed,
      this,
      &ASCharacter::PrimaryInteract);
}

void ASCharacter::MoveForward(float value) {
  FRotator ControlRot = GetControlRotation();
  ControlRot.Pitch = 0.0f;
  ControlRot.Roll = 0.0f;
  AddMovementInput(ControlRot.Vector(), value);
}

void ASCharacter::MoveRight(float value) {
  FRotator ControlRot = GetControlRotation();
  ControlRot.Pitch = 0.0f;
  ControlRot.Roll = 0.0f;

  FVector RightVector = FRotationMatrix(ControlRot).GetScaledAxis(EAxis::Y);

  AddMovementInput(RightVector, value);
}

void ASCharacter::PrimaryAttack() {
  PlayAnimMontage(AttackAnim);

  GetWorldTimerManager().SetTimer(
      TimerHandle_PrimaryAttack,
      this,
      &ASCharacter::PrimaryAttack_TimeElapsed,
      AnimationDelay);
}

void ASCharacter::PrimaryAttack_TimeElapsed() {
  FVector HandLocation = GetMesh()->GetSocketLocation("Muzzle_01");

  FTransform SpawnTM = FTransform(GetControlRotation(), HandLocation);

  FActorSpawnParameters SpawnParams;
  SpawnParams.SpawnCollisionHandlingOverride =
      ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

  GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnTM, SpawnParams);
}

void ASCharacter::PrimaryInteract() { InteractionComp->PrimaryInteract(); }