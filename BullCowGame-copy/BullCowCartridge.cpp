// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

#include <string>
#include <sstream>
using namespace std;

static const FString Welcome{ TEXT("Welcome to the BullCow game!") };
static const FString PromptUserGuess{ TEXT("Enter Your Guess:") };
static const FString GoodBye{ TEXT("Bye now, thanks for playing!") };

#define P(x) { stringstream ss; ss << x; PrintLine(FString(ss.str().c_str())); }

// convert a UE FString to a C string
//
#define S(fstr) (TCHAR_TO_UTF8(*(fstr)));

void UBullCowCartridge::promptUserForGuess()
{
    P("You have " << tries_ << " tries remaining");
    PrintLine(PromptUserGuess);
}

void UBullCowCartridge::startTheGame()
{
    hiddenWord_ = TEXT("snarf");
    tries_ = 5;
    mode_ = Playing;
    bulls_ = 0;
    cows_ = 0;
    promptUserForGuess();
}

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    PrintLine(Welcome);
    startTheGame();
}

void UBullCowCartridge::handleYesNoInput(const FString& input)
{
    if (input == TEXT("yes"))
        startTheGame();
    else if (input == TEXT("no"))
    {  
        mode_ = GameOver;
        PrintLine(GoodBye);
    }
    else
    {
        P("Please enter either 'yes' or 'no'");
        askPlayAgain();
    }
}

void UBullCowCartridge::askPlayAgain()
{
    PrintLine(TEXT("Would you like to play again?"));
    mode_ = AskPlayAgain;
}

void UBullCowCartridge::handlePlayInput(const FString& input)
{
    if (input.Len() == 0)
    {
        // remind the user to enter something
        P("(You didn't enter anything. Please enter a guess)");
    }
    else if (input == hiddenWord_)
    {
        PrintLine(TEXT("*******************"));
        PrintLine(TEXT("You Win!  Congratulations!"));
        askPlayAgain();
        return;
    }
    else if (--tries_ <= 0)
    {
        P("Sorry, you ran out of guesses.");
        P("The word was: " << S(hiddenWord_));
        askPlayAgain();
        return;
    }
    P("You have " << bulls_ << " bulls and " << cows_ << " cows");
    promptUserForGuess();
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    ClearScreen();
    switch (mode_)
    {
        case Playing:
            handlePlayInput(Input);
            break;
        case AskPlayAgain:
            handleYesNoInput(Input); 
            break;
        case GameOver:
            PrintLine(GoodBye);
            break;
    }
}