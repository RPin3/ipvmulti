// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/AAmmoPickup.h"

#include "Components/SphereComponent.h"
#include "Ipvmulti/IpvmultiCharacter.h"

// Sets default values
AAAmmoPickup::AAAmmoPickup()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;

	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	RootComponent = Collision;

	Collision->SetSphereRadius(100.f);
	Collision->OnComponentBeginOverlap.AddDynamic(this, &AAAmmoPickup::OnOverlapBegin);
}

void AAAmmoPickup::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (HasAuthority())
	{
		AIpvmultiCharacter* Character = Cast<AIpvmultiCharacter>(OtherActor);
		if (Character)
		{
			Character->RefillAmmo();
			Destroy(); 
		}
	}
}

