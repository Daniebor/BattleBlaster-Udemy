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
