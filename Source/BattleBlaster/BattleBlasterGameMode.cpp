// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleBlasterGameMode.h"

#include "Kismet/GameplayStatics.h"
#include "Tower.h"

void ABattleBlasterGameMode::BeginPlay()
{
	Super::BeginPlay();
	
	TArray<AActor*> Towers;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATower::StaticClass(), Towers);
	TowerCount = Towers.Num();
	UE_LOG(LogTemp, Warning, TEXT("TowerCount: %d"), TowerCount);
	
	if (APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0))
	{
		Tank = Cast<ATank>(PlayerPawn);
		if (!Tank)
		{
			UE_LOG(LogTemp, Warning, TEXT("GameMode: Failed to find the tank actor!"));
		}
		else
		{
			int32 LoopIndex = 0;
			while (LoopIndex < TowerCount)
			{
				if (ATower* Tower = Cast<ATower>(Towers[LoopIndex]))
				{
					Tower->Tank = Tank;
				}
				LoopIndex++;
			}
		}
	}
	
	
}

void ABattleBlasterGameMode::ActorDied(AActor* DeadActor)
{
	if (DeadActor == Tank)
	{
		Tank->HandleDestruction();
	}
	else
	{
		ATower* DeadTower = Cast<ATower>(DeadActor);
		DeadTower->Destroy();
		if (DeadTower)
		{
			TowerCount--;
			DeadTower->HandleDestruction();
			if (TowerCount == 0)
			{
				UE_LOG(LogTemp, Display, TEXT("All Towers destroy, Victory"));
			}
			else
			{
				UE_LOG(LogTemp, Display, TEXT("Tower destroyed, remaining towers: %d"), TowerCount);
			}
		}
	}
}
