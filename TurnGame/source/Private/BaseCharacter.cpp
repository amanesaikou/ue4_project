// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "Components/InputComponent.h"
#include "MyGameInstance.h"
#include "GameFramework/SpringArmComponent.h"

ABaseCharacter::ABaseCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)

	abilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	abilitySystemComponent->SetIsReplicated(true);
}

void ABaseCharacter::AcquireAbility() {
	if (abilitySystemComponent) {
		for (auto& ability : AbilityToAquire)
			abilitySystemComponent->GiveAbility(FGameplayAbilitySpec(ability, 1, 0));
		abilitySystemComponent->InitAbilityActorInfo(this, this);
	}
}

void ABaseCharacter::SetAttributes(FMyAttributeSet attributes) {
	SetHealth(attributes.GetHealth());
	SetMaxHealth(attributes.GetMaxHealth());
	SetMana(attributes.GetMana());
	SetMaxMana(attributes.GetMaxMana());
	SetAttack(attributes.GetAttack());
	SetDefense(attributes.GetDefense());
	SetCriticalStrike(attributes.GetCriticalStrike());
}

float ABaseCharacter::GetHealth() const {
	return attributeSet.GetHealth();
}

float ABaseCharacter::GetMaxHealth() const {
	return attributeSet.GetMaxHealth();
}

float ABaseCharacter::GetMana() const {
	return attributeSet.GetMana();
}

float ABaseCharacter::GetMaxMana() const {
	return attributeSet.GetMaxMana();
}

float ABaseCharacter::GetAttack() const {
	return attributeSet.GetAttack();
}

float ABaseCharacter::GetDefense() const {
	return attributeSet.GetDefense();
}

float ABaseCharacter::GetCriticalStrike() const {
	return attributeSet.GetCriticalStrike();
}

void ABaseCharacter::SetHealth(float value) {
	attributeSet.SetHealth(value);
}

void ABaseCharacter::SetMaxHealth(float value) {
	attributeSet.SetMaxHealth(value);
}

void ABaseCharacter::SetMana(float value) {
	attributeSet.SetMana(value);
}

void ABaseCharacter::SetMaxMana(float value) {
	attributeSet.SetMaxMana(value);
}

void ABaseCharacter::SetAttack(float value) {
	attributeSet.SetAttack(value);
}

void ABaseCharacter::SetDefense(float value) {
	attributeSet.SetDefense(value);
}

void ABaseCharacter::SetCriticalStrike(float value) {
	attributeSet.SetCriticalStrike(value);
}

void ABaseCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
	Jump();
}

void ABaseCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
	StopJumping();
}

void ABaseCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ABaseCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void ABaseCharacter::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void ABaseCharacter::MoveRight(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

void ABaseCharacter::AddEquipmentAttribute() {
	UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(GetGameInstance());
	FMyAttributeSet temp = MyGameInstance->GetAttributeSet();
	attributeSet = attributeSet + temp;
}

UAbilitySystemComponent* ABaseCharacter::GetAbilitySystemComponent() const {
	return abilitySystemComponent;
}

void ABaseCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &ABaseCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ABaseCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &ABaseCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ABaseCharacter::LookUpAtRate);

	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &ABaseCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &ABaseCharacter::TouchStopped);

	// VR headset functionality
	//PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &ABaseCharacter::OnResetVR);
}

FMyAttributeSet::FMyAttributeSet() {
	health = 0;
	maxHealth = 0;
	mana = 0;
	maxMana = 0;
	attack = 0;
	defense = 0;
	criticalStrike = 0;
}

FMyAttributeSet FMyAttributeSet::operator+(FMyAttributeSet& A) {
	FMyAttributeSet temp;
	temp.health = health + A.health;
	temp.maxHealth = maxHealth + A.maxHealth;
	temp.mana = mana + A.mana;
	temp.maxMana = maxMana + A.maxMana;
	temp.attack = attack + A.attack;
	temp.defense = defense + A.defense;
	temp.criticalStrike = criticalStrike + A.criticalStrike;
	return temp;
}

float FMyAttributeSet::GetHealth() const {
	return health;
}

float FMyAttributeSet::GetMaxHealth() const {
	return maxHealth;
}

float FMyAttributeSet::GetMana() const {
	return mana;
}

float FMyAttributeSet::GetMaxMana() const {
	return maxMana;
}

float FMyAttributeSet::GetAttack() const {
	return attack;
}

float FMyAttributeSet::GetDefense() const {
	return defense;
}

float FMyAttributeSet::GetCriticalStrike() const {
	return criticalStrike;
}

void FMyAttributeSet::SetHealth(float value) {
	health = value;
}

void FMyAttributeSet::SetMaxHealth(float value) {
	maxHealth = value;
}

void FMyAttributeSet::SetMana(float value) {
	mana = value;
}

void FMyAttributeSet::SetMaxMana(float value) {
	maxMana = value;
}

void FMyAttributeSet::SetAttack(float value) {
	attack = value;
}

void FMyAttributeSet::SetDefense(float value) {
	defense = value;
}

void FMyAttributeSet::SetCriticalStrike(float value) {
	criticalStrike = value;
}
