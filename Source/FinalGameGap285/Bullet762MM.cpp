// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet762MM.h"

ABullet762MM::ABullet762MM()
{

}

void ABullet762MM::BeginPlay()
{
	Super::BeginPlay();
}

void ABullet762MM::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABullet762MM::OnBulletBeginOverlap_Trigger(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& sweepResult)
{

	Super::OnBulletBeginOverlap_Trigger(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, sweepResult);
}
