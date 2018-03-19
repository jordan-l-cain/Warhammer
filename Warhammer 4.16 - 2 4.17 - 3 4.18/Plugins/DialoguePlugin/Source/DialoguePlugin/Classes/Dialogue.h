#pragma once
#include "Runtime/Engine/Classes/Engine/DataAsset.h"
#include "WarhammerGameModeBase.h"
#include "Dialogue.generated.h"

//add any fields you want here, for example:
// item - to grant/remove item
// actor class - to spawn an actor
// int32 money/experience - to grant money/experience
USTRUCT(Blueprintable)
struct FDialogueEvents
{
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue Event")
	class UAnimMontage* AnimationMontage = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Global Variables")
	//TMap of all world conditions that will cause events. Here is the dialogue version which will set the corresponding TMap in the WarhammerGameModeBase
	TMap< FName, bool > WorldConditions;


	GENERATED_USTRUCT_BODY()
};

// add any fields you want here, for example:
// int32 level - to check for minimum level
// item - to check for inventory item
USTRUCT(Blueprintable)
struct FDialogueConditions 
{
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue Condition")
	int32 Money = 0;

	GENERATED_USTRUCT_BODY()
};

USTRUCT(Blueprintable)
struct FDialogueNode
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue Node")
	int32 id;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue Node")
	bool isPlayer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue Node")
	FText Text;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue Node")
	TArray<int32> Links;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue Node")
	FVector2D Coordinates;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue Node")
	bool bHasEvents = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue Node")
	bool bHasConditions = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue Node", meta = (EditCondition = "bHasEvents"))
	FDialogueEvents Events;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue Node", meta = (EditCondition = "bHasConditions"))
	FDialogueConditions Conditions;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue Node")
	class USoundBase* Sound = NULL;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue Node")
	class UDialogueWave* DialogueWave = NULL;
};

UCLASS(Blueprintable, BlueprintType)
class DIALOGUEPLUGIN_API UDialogue : public UDataAsset
{
	GENERATED_BODY()

public:

	UDialogue(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, Category = Dialogue)
	FDialogueNode GetFirstNode();

	UFUNCTION(BlueprintCallable, Category = Dialogue)
	TArray<FDialogueNode> GetNextNodes(FDialogueNode Node);

	UFUNCTION(BlueprintCallable, Category = Dialogue)
	static void CallFunctionByName(UObject* Object, FString FunctionName);
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Dialogue)
	bool DisplayIdleSplines = true;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Dialogue)
	FText Name;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Dialogue)
	TArray<FDialogueNode> Data;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Dialogue) //don't remove uproperty here
	int32 NextNodeId;

	FDialogueNode GetNodeById(int32 id, int32 &index);
	FDialogueNode GetNodeById(int32 id);

	int32 CurrentNodeId;
	bool isLinking;
	FVector2D LinkingCoords;
	int32 LinkingFromIndex;
	//FSlateImageBrush* bgStyle;
};
