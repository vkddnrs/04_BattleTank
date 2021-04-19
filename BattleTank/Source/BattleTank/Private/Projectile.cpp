// Fill out your copyright notice in the Description page of Project Settings.

#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Projectile.h"




// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovement");
	ProjectileMovement->bAutoActivate = false;


	CollisionMesh = CreateDefaultSubobject<UStaticMeshComponent>("CollisionMesh");
	SetRootComponent(CollisionMesh);
	CollisionMesh->SetNotifyRigidBodyCollision(true);
	CollisionMesh->SetVisibility(false);
	
	LaunchBlast = CreateDefaultSubobject<UParticleSystemComponent>("LaunchBlast");
    LaunchBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	LaunchBlast->SetAutoActivate(true);
	
	ImpactBlast = CreateDefaultSubobject<UParticleSystemComponent>("ImpactBlast");
	ImpactBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	ImpactBlast->SetAutoActivate(false);

	ExplosionForce = CreateDefaultSubobject<URadialForceComponent>("ExplosionForce");
	ExplosionForce->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	//ExplosionForce->SetAutoActivate(false);

}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	CollisionMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::LaunchProjectile(float Speed)
{
	ProjectileMovement->SetVelocityInLocalSpace(FVector::ForwardVector * Speed);
	ProjectileMovement->Activate();
}

void AProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent,
	FVector NormalImpuls, const FHitResult& Hit)
{
	LaunchBlast->Deactivate();
	ImpactBlast->Activate(true);
	ExplosionForce->FireImpulse();
	///************
	//SetRootComponent(LaunchBlast); начальный вариант
	//CollisionMesh->DestroyComponent();
	///**************

	UGameplayStatics::ApplyRadialDamage(
		this,
		ProjectileDamage,
		GetActorLocation(),
		ExplosionForce->Radius,
		UDamageType::StaticClass(),
		TArray<AActor*>() // damage all actors (not ignor)
		);
	
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AProjectile::TimerProjectileDestroy, DestroyDelay);
}

void AProjectile::TimerProjectileDestroy()
{
	UE_LOG(LogTemp, Warning, TEXT("%s is destroy"), *GetName());
	Destroy();
}

