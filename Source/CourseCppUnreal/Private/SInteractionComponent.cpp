// Fill out your copyright notice in the Description page of Project Settings.

#include "SInteractionComponent.h"
#include "DrawDebugHelpers.h"
#include "SGameplayInterface.h"

USInteractionComponent::USInteractionComponent() {

  PrimaryComponentTick.bCanEverTick = true;
}

void USInteractionComponent::PrimaryInteract() {
  FCollisionObjectQueryParams objectQueryParams;
  objectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);

  AActor* myOwner = GetOwner();
  FVector end;

  FVector eyeLocation;
  FRotator eyeRotation;

  myOwner->GetActorEyesViewPoint(eyeLocation, eyeRotation);
  end = eyeLocation + (eyeRotation.Vector() * 1000);

  TArray<FHitResult> hits;

  FCollisionShape shape;
  float radius = 30.0f;
  shape.SetSphere(radius);

  bool bBlockingHit = GetWorld()->SweepMultiByObjectType(
      hits,
      eyeLocation,
      end,
      FQuat::Identity,
      objectQueryParams,
      shape);
  FColor lineColor = bBlockingHit ? FColor::Blue : FColor::Red;

  for (FHitResult hit : hits) {
    DrawDebugSphere(
        GetWorld(),
        hit.ImpactPoint,
        radius,
        32,
        lineColor,
        false,
        2.0f);

    AActor* hitActor = hit.GetActor();
    if (hitActor) {
      if (hitActor->Implements<USGameplayInterface>()) {
        APawn* myPawn = Cast<APawn>(myOwner);
        ISGameplayInterface::Execute_Interact(hitActor, myPawn);
        break;
      }
    }
  }
  DrawDebugLine(GetWorld(), eyeLocation, end, lineColor, false, 2.0f, 0, 2.0f);
}

void USInteractionComponent::BeginPlay() { Super::BeginPlay(); }

void USInteractionComponent::TickComponent(
    float DeltaTime,
    ELevelTick TickType,
    FActorComponentTickFunction* ThisTickFunction) {
  Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}
