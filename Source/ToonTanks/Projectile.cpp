// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"

#include "Components/CapsuleComponent.h"

#include "Kismet/GameplayStatics.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false; //Not need to tick

	// Projectile Components:
	//Capsule:
	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	RootComponent = CapsuleComp;

	//Adding meshes and attachet them
	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	ProjectileMesh->SetupAttachment(RootComponent);

	ProjectileMovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement Component"));

	//Add smoke trail
	SmokeTrail = CreateDefaultSubobject< UParticleSystemComponent>(TEXT("Smoke Trail"));
	SmokeTrail->SetupAttachment(RootComponent);

	ProjectileMovementComp->MaxSpeed = 1500.f;
	ProjectileMovementComp->InitialSpeed = 1500.f;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	//CapsuleComp->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
	CapsuleComp->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::OnOverlapBegin);
	CapsuleComp->OnComponentEndOverlap.AddDynamic(this, &AProjectile::OnOverlapEnd);

	//ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);

	if (LaunchSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, LaunchSound, GetActorLocation());
	}
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AProjectile::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("START Overlap"));
	/*AActor* MyOwner = GetOwner();
	/*if (MyOwner == nullptr)//<- chyba
	{
		Destroy();
		return;
	}
	
	AController* MyOwnerInstigator = MyOwner->GetInstigatorController();
	UClass* DamageClassType = UDamageType::StaticClass();
	
	if (OtherActor && OtherActor != this && OtherActor != MyOwner)
	{
		//UGameplayStatics::ApplyDamage(OtherActor, Damage, MyOwnerInstigator, this, DamageClassType);//<- chyba
		
		
		if (HitParticles)
		{
			UGameplayStatics::SpawnEmitterAtLocation(this, HitParticles, GetActorLocation(), GetActorRotation());
		}

		/*if (HitSound)//<- chyba
		{
			UGameplayStatics::PlaySoundAtLocation(this, HitSound, GetActorLocation());
		}
		if (HitCameraShakeClass)
		{
			GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(HitCameraShakeClass);
		}
	}
	//Destroy();//<- chyba
	*/
}
void AProjectile::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogTemp, Warning, TEXT("END overlap"));
	/*if (OtherActor && (OtherActor != this) && OtherComp)
	{
		
	}*/
}
