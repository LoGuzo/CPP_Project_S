// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FirstCharacter.h"
#include "Project_S/S_StructureAll.h"
#include "UserCharacter.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_S_API AUserCharacter : public AFirstCharacter
{
	GENERATED_BODY()
	
	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

public:
	AUserCharacter();
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	virtual void PostInitializeComponents() override;

	void SaveCharacterData(FString _RowName, struct FMyCharacterData _NewData);
	void LoadCharacterData();
	
	void SetNowLevelData(int32 _Level);
	void SetNowEquipData(const TArray<struct FS_Slot>&_MyEquip);
	void SetNowInvenData(const TArray<struct FS_Slot>&_MyInven);
protected:

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	class AWeaponActor* MyWeapon = nullptr;

	FMyCharacterData NowCharData;

	// UI
	TSubclassOf<class US_CharacterWidget> CharacterUI;

	class US_CharacterWidget* HUDWidget;

	int32 IWeapon;

	bool bIsFlipFlopInventoryActive;

	bool bIsFlipFlopEquipmentActive;

	void PickUpItem();

	class AA_Item* Curitem;

	class UC_InventoryComponent* Inventory;

	class UC_EqiupComponent* Equip;
public:
	void SetMyWeapon(TSubclassOf<class AA_Item>_MyWeapon);

	void RemoveMyWeapon();

	void Attack();

	UC_InventoryComponent* GetInventoryCom() { return Inventory; }

	void OnInventoryKeyPressed();

	void OnEquipmentKeyPressed();

	AA_Item* GetCurItem() { return Curitem; }
	void SetCurItem(AA_Item* _Curitem);

	void UpdateInventory();
};
