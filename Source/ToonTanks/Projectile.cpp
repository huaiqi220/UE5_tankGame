// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"

#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>("Capsule Comp");
	

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("Projectile");
	RootComponent = BaseMesh;

	Upromc = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement Component"));
	Upromc->MaxSpeed = 1300.f;
	Upromc->InitialSpeed = 1300.f;

}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	BaseMesh->OnComponentHit.AddDynamic(this,&AProjectile::OnHit);
	
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

void AProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	auto MyOwner = GetOwner();
	if(MyOwner == nullptr) return;
	AController* MyOwnerInstigator = MyOwner->GetInstigatorController();

	auto DamageTypeClass = UDamageType::StaticClass();

	if(OtherActor && OtherActor != this && OtherActor != MyOwner)
	{
		UGameplayStatics::ApplyDamage(OtherActor,Damage,MyOwnerInstigator,this,DamageTypeClass);
		Destroy();
	}
	
	

	
}

