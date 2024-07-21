// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FirstCharacter.h"
#include "Components/TimelineComponent.h"
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

	void SaveCharacterData();
	void LoadCharacterData();
	void DelayedLoadCharacterData();
	void SetClass(E_CharClass _ClassType);

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_PickUpItem();
	UFUNCTION(NetMulticast, Reliable)
	void Multi_PickUpItem();
	void PickUpItem();
	void SetUserWidget();

	void SetMyParty(class UPartySystem* _MyParty);

	virtual void ShotAttackCheck() override;

	void UpdateQuest(const TArray<FQuestNode*>& Slots);
protected:
	void SetMesh(E_CharClass _ClassType);

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

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	virtual void ResetStat() override;

	float CalculateHitDirectionAngle(const FVector& AttackerLocation);

	void UserDied();

	virtual void Multi_UseSkill(const FString& _SkillName) override;

	virtual void Multi_UseSkill_Implementation(const FString& SkillName) override;

	UPROPERTY(ReplicatedUsing = OnRep_MeshPath)
	USkeletalMesh* MeshPath;

	UFUNCTION()
	void OnRep_MeshPath();

private:
	class UPartySystem* MyParty;

	UPROPERTY(Replicated)
	E_CharClass ClassType;

	UPROPERTY(ReplicatedUsing = OnRep_MyWeapon)
	class AWeaponActor* MyWeapon;

	TWeakPtr<FCharacterClass> ClassData;

	TWeakPtr<FSkillTable> NowSkill;

	// UI
	TSubclassOf<class US_CharacterWidget> CharacterUI;

	class US_CharacterWidget* HUDWidget;

	int32 IWeapon;

	bool bIsFlipFlopInventoryActive;

	bool bIsFlipFlopEquipmentActive;

	bool bIsFlipFlopSkillWidgetActive;

	class AA_Item* Curitem;

	UPROPERTY(Replicated)
	class UC_InventoryComponent* Inventory;

	class UC_EqiupComponent* Equip;

	UPROPERTY(Replicated)
	class UC_QuickSlotComponent* QuickSlot;

	class UUserAnimInstance* AnimInstance;

	bool IsAttacking;

	int32 AttackIndex = 0;

	void Dash();

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_Dash();

	UFUNCTION(NetMulticast, Reliable)
	void Multi_Dash();

	void StopDashing();

	void ResetDash();

	UPROPERTY()
	FTimerHandle UnusedHandle;

	UPROPERTY()
	FTimerHandle HitHandle;

	FTimeline CurveTimeLine;

	UFUNCTION()
	void TimelineProgress(float _Value);

	FRotator BeforeRot;

	TWeakPtr<FMyCharacterData> LoadData;

	void UseItem(const int32 QuickIndex);

	void UsePotion(const int32 StackSize, const FString& ItemName);

	void SetHitFalse();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
public:
	void UseQuickSlot();
	
	void AttackCheck();

	void SetMyWeapon(TSubclassOf<class AA_Item> _MyWeapon);

	UFUNCTION()
	void OnRep_MyWeapon();

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_SetMyWeapon(TSubclassOf<class AA_Item> _MyWeapon);

	UFUNCTION(NetMulticast, Reliable)
	void Multi_SetMyWeapon(TSubclassOf<class AA_Item> _MyWeapon);

	void RemoveMyWeapon();

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_RemoveMyWeapon();

	UFUNCTION(NetMulticast, Reliable)
	void Multi_RemoveMyWeapon();

	void Attack();
	
	void AttackMontage();

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_AttackMontage();

	UFUNCTION(NetMulticast, Reliable)
	void Multi_AttackMontage();
	
	UFUNCTION()
	void OnAttackMontageEnd(UAnimMontage* Montage, bool bInterrupted);

	UC_InventoryComponent* GetInventoryCom() const { return Inventory; }

	UC_EqiupComponent* GetEquipCom() const { return Equip; }

	void OnInventoryKeyPressed();

	void OnEquipmentKeyPressed();

	void OnSkillWidgetKeyPressed();

	AA_Item* GetCurItem() const { return Curitem; }
	void SetCurItem(AA_Item *_Curitem);

	void AnyMove(UCurveBase* _SkillCurve);

	UPROPERTY(EditAnyWhere, Category = Camera)
	TSubclassOf<class UCameraShakeBase> TCameraShake;

	UFUNCTION(BlueprintCallable, Category = "Camera")
	void PlayCameraShake(TSubclassOf<UCameraShakeBase> ShakeClass);

	void UserReset();

	void SetWidget();

	void RemoveWidget();
};
