// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectileActor.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMeshActor.h"
#include "Engine/StaticMesh.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "Runtime/Engine/Classes/Materials/MaterialInstanceDynamic.h"
#include "ConstructorHelpers.h"
#include "Runtime/Engine/Classes/Components/SphereComponent.h"
#include "Components/SphereComponent.h"

#define print(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::Green,text)

// Sets default values
AProjectileActor::AProjectileActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BulletComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	BulletComponent->SetMobility(EComponentMobility::Movable);
	UStaticMesh* Mesh = LoadObject<UStaticMesh>(nullptr, TEXT("/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere"));

	BulletComponent->SetVisibility(true);
	BulletComponent->SetStaticMesh(Mesh);
	BulletComponent->SetSimulatePhysics(true);
	BulletComponent->SetNotifyRigidBodyCollision(true);
	BulletComponent->SetMassOverrideInKg(NAME_None, 10.f);
	BulletComponent->SetEnableGravity(true);
	//BulletComponent->BodyInstance.SetCollisionProfileName("BlockAllDynamic");
	BulletComponent->SetMobility(EComponentMobility::Movable);
	auto material = LoadObject<UMaterial>(nullptr, TEXT("/Game/StarterContent/Materials/M_Tech_Hex_Tile_Pulse"));
	BulletComponent->SetMaterial(0, material);
	BulletComponent->SetWorldScale3D(FVector(0.2, 0.2, 0.2));
	
	//FScriptDelegate Delegate;
	//Delegate.BindUFunction(this, "OnPHit");
	//OnActorHit.Add(Delegate);
	BulletComponent->OnComponentHit.AddDynamic(this, &AProjectileActor::OnActorHit);

	SetRootComponent(BulletComponent);
}

// Called when the game starts or when spawned
void AProjectileActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AProjectileActor::Tick(float DeltaTime)
{
	BulletComponent->AddImpulse(ShootDir * 3000);
	Super::Tick(DeltaTime);	
}

void AProjectileActor::OnPHit()
{
	print("HIT ME!");
}

void AProjectileActor::Initialize(FVector startLocation)
{
	StartLocation = startLocation;
	auto myLoc = GetActorLocation();
	auto diff = startLocation - myLoc;
	//print(startLocation.ToString());
	//print(myLoc.ToString());
	startLocation.Y += 2;
	startLocation.Z -= 17;
	//startLocation.X += 1;
	SetActorLocation(startLocation);
	//print("Init Projectile!");
}

void AProjectileActor::OnActorHit(UPrimitiveComponent * HitComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit)
{
	print("I hit something");
}



