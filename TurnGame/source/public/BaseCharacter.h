// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystemComponent.h"
#include "Abilities/GameplayAbility.h"
#include "Engine/DataTable.h"
#include "BaseCharacter.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FMyAttributeSet : public FTableRowBase {

	GENERATED_BODY()

	// コンストラクタ
	FMyAttributeSet();

	// 演算子のオーバーロード
	FMyAttributeSet operator+(FMyAttributeSet& A);

	// 属性値を取得する関数
	float GetHealth() const;
	float GetMaxHealth() const;
	float GetMana() const;
	float GetMaxMana() const;
	float GetAttack() const;
	float GetDefense() const;
	float GetCriticalStrike() const;

	// 属性値を設定する関数
	void SetHealth(float value);
	void SetMaxHealth(float value);
	void SetMana(float value);
	void SetMaxMana(float value);
	void SetAttack(float value);
	void SetDefense(float value);
	void SetCriticalStrike(float value);

	// hp
	UPROPERTY(BlueprintReadWrite)
	float health;

	// hpの最大値
	UPROPERTY(BlueprintReadWrite)
	float maxHealth;

	// マナ
	UPROPERTY(BlueprintReadWrite)
	float mana;

	// マナの最大値
	UPROPERTY(BlueprintReadWrite)
	float maxMana;

	// 攻撃力
	UPROPERTY(BlueprintReadWrite)
	float attack;

	// 防御力
	UPROPERTY(BlueprintReadWrite)
	float defense;

	// クリティカルストライク
	UPROPERTY(BlueprintReadWrite)
	float criticalStrike;

};


UCLASS()
class MAGICTURNGAME_API ABaseCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

public:
	ABaseCharacter();
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseLookUpRate;

	UFUNCTION(BlueprintCallable, Category = BaseCharacter)
	void AcquireAbility();

	UFUNCTION(BlueprintCallable)
	void SetAttributes(FMyAttributeSet attributes);

	UFUNCTION(BlueprintCallable)
	float GetHealth() const;

	UFUNCTION(BlueprintCallable)
	float GetMaxHealth() const;

	UFUNCTION(BlueprintCallable)
	float GetMana() const;

	UFUNCTION(BlueprintCallable)
	float GetMaxMana() const;

	UFUNCTION(BlueprintCallable)
	float GetAttack() const;

	UFUNCTION(BlueprintCallable)
	float GetDefense() const;

	UFUNCTION(BlueprintCallable)
	float GetCriticalStrike() const;

	UFUNCTION(BlueprintCallable)
	void SetHealth(float value);

	UFUNCTION(BlueprintCallable)
	void SetMaxHealth(float value);

	UFUNCTION(BlueprintCallable)
	void SetMana(float value);

	UFUNCTION(BlueprintCallable)
	void SetMaxMana(float value);

	UFUNCTION(BlueprintCallable)
	void SetAttack(float value);

	UFUNCTION(BlueprintCallable)
	void SetDefense(float value);

	UFUNCTION(BlueprintCallable)
	void SetCriticalStrike(float value);

	UFUNCTION(BlueprintCallable)
	void AddEquipmentAttribute();

	UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void OnDamaged();

private:
	FMyAttributeSet attributeSet;

protected:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY()
	UAbilitySystemComponent* abilitySystemComponent;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<TSubclassOf<UGameplayAbility>>AbilityToAquire;

	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/**
	 * Called via input to turn at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

};
