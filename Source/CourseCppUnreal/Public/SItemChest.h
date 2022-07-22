// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SGameplayInterface.h"
#include "SItemChest.generated.h"

class UStaticMeshComponent;

UCLASS()
class COURSECPPUNREAL_API ASItemChest : public AActor,
                                        public ISGameplayInterface {
  GENERATED_BODY()

  void Interact_Implementation(APawn* InstigatorPawn);

public:
  UPROPERTY(EditAnywhere)
  float TargetLidPitch = 110.0f;

  UPROPERTY(VisibleAnywhere)
  UStaticMeshComponent* BaseMesh;

  UPROPERTY(VisibleAnywhere)
  UStaticMeshComponent* LidMesh;

  // Sets default values for this actor's properties
  ASItemChest();

protected:
  // Called when the game starts or when spawned
  virtual void BeginPlay() override;

public:
  // Called every frame
  virtual void Tick(float DeltaTime) override;
};
