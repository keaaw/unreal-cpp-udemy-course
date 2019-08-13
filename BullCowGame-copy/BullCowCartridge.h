// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Console/Cartridge.h"
#include "BullCowCartridge.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BULLCOWGAME_API UBullCowCartridge : public UCartridge
{
	GENERATED_BODY()

	public:
	virtual void BeginPlay() override;
	virtual void OnInput(const FString& Input) override;

	// Your declarations go below!
	private:
		enum Mode
		{
			Playing,
			AskPlayAgain,
			GameOver
		};

		FString hiddenWord_;
		int tries_;
		Mode mode_;
		int bulls_;
		int cows_;

		void startTheGame();
		void promptUserForGuess();
		void handleYesNoInput(const FString& input);
		void handlePlayInput(const FString& input);
		void askPlayAgain();
	
};
