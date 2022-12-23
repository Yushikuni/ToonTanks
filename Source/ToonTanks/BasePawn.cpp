 // Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"

#include "Kismet/GameplayStatics.h"
#include "Projectile.h"

// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Making capsule component for collision
	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	
	// Capsule component is a root component
	RootComponent = CapsuleComp;

	//Adding meshes and attachet them
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(CapsuleComp);

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	TurretMesh->SetupAttachment(BaseMesh);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Base"));
	ProjectileSpawnPoint->SetupAttachment(TurretMesh);
}

void ABasePawn::HandleDestruction()
{
	//Add: Visual / sound efekt
}

void ABasePawn::RotateTurret(FVector LookAtTarget)
{
	FVector ToTarget = LookAtTarget - TurretMesh->GetComponentLocation(); //World space vector
	FRotator LookAtRotation = FRotator(0.f, ToTarget.Rotation().Yaw, 0.f); //world space rotation

	TurretMesh->SetWorldRotation(FMath::RInterpTo(TurretMesh->GetComponentRotation(),LookAtRotation,UGameplayStatics::GetWorldDeltaSeconds(this),25.f));
}

void ABasePawn::Fire()
{
	FVector Location = ProjectileSpawnPoint->GetComponentLocation();
	FRotator Rotation = ProjectileSpawnPoint->GetComponentRotation();
	auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, Location, Rotation);
	Projectile->SetOwner(this);
}