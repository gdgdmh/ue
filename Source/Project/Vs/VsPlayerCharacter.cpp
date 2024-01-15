// Fill out your copyright notice in the Description page of Project Settings.


#include "VsPlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

#include "InputMappingContext.h" // 追加

#include "WeaponKnife.h"

AVsPlayerCharacter::AVsPlayerCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	//CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom")); // ProjectCharacterですでに生成しているので必要なし
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	//FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera")); // ProjectCharacterですでに生成しているので必要なし
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// テスト
	// Input Mapping Contextを読込
	DefaultMappingContext = LoadObject<UInputMappingContext>(NULL, TEXT("/Game/ThirdPerson/Input/IMC_Default"), NULL, LOAD_None, NULL);

	ProjectileClass = AWeaponKnife::StaticClass();
	//Initialize fire rate
	FireRate = 0.25f;
	bIsFiringWeapon = false;
}

// To add mapping context
void AVsPlayerCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	// 発射
	UWorld* World = GetWorld();
	check(World);
	{
		ShootKnifer = World->SpawnActor<ALoopShootKnifer>();
		TObjectPtr<AVsShootParameter> ShootParameter = NewObject<AVsShootParameter>();
		FVector spawnLocation = GetActorLocation() + (GetActorRotation().Vector() * 100.0f) + (GetActorUpVector() * 50.0f);
		FRotator spawnRotation = GetActorRotation();
		FActorSpawnParameters spawnParameters;
		spawnParameters.Instigator = GetInstigator();
		spawnParameters.Owner = this;

		ShootParameter->SetLocation(spawnLocation);
		ShootParameter->SetRotation(spawnRotation);
		ShootParameter->SetSpawnParameters(spawnParameters);
		ShootKnifer->SetShootParameter(ShootParameter);
		ShootKnifer->SetShootTimerEnable(true);
		ShootKnifer->SetShootTimer(1.0f);

		ShootKnifer->GetShootBeforeDispacher().AddDynamic(this, &AVsPlayerCharacter::ShootBeforeEvent);
		ShootKnifer->StartShootTimer(World->GetTimerManager());
	}
}

/** Called for movement input */
void AVsPlayerCharacter::Move(const FInputActionValue& Value)
{	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}

}

/** Called for looking input */
void AVsPlayerCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AVsPlayerCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {

		//Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AVsPlayerCharacter::Move);

		//Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AVsPlayerCharacter::Look);

		// Handle firing projectiles
		PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AVsPlayerCharacter::StartFire);
	}

}

void AVsPlayerCharacter::StartFire()
{
    if (!bIsFiringWeapon)
    {
        bIsFiringWeapon = true;
        UWorld* World = GetWorld();
        World->GetTimerManager().SetTimer(FiringTimer, this, &AVsPlayerCharacter::StopFire, FireRate, false);
        HandleFire();
    }
}

void AVsPlayerCharacter::StopFire()
{
    //ProjectCharacterと定義かぶりしているのでいったん消す
    bIsFiringWeapon = false;
}

void AVsPlayerCharacter::HandleFire_Implementation()
{
    FVector spawnLocation = GetActorLocation() + (GetActorRotation().Vector() * 100.0f) + (GetActorUpVector() * 50.0f);
    FRotator spawnRotation = GetActorRotation();

    FActorSpawnParameters spawnParameters;
    spawnParameters.Instigator = GetInstigator();
    spawnParameters.Owner = this;

    AWeaponKnife* spawnedProjectile = GetWorld()->SpawnActor<AWeaponKnife>(spawnLocation, spawnRotation, spawnParameters);
}

void AVsPlayerCharacter::ShootBeforeEvent()
{
	UE_LOG(LogTemp, Log, TEXT("AVsPlayerCharacter::ShootBeforeEvent()"));
	TObjectPtr<AVsShootParameter> ShootParameter = NewObject<AVsShootParameter>();
	FVector spawnLocation = GetActorLocation() + (GetActorRotation().Vector() * 100.0f) + (GetActorUpVector() * 50.0f);
	FRotator spawnRotation = GetActorRotation();
	FActorSpawnParameters spawnParameters;
	spawnParameters.Instigator = GetInstigator();
	spawnParameters.Owner = this;
	ShootParameter->SetLocation(spawnLocation);
	ShootParameter->SetRotation(spawnRotation);
	ShootParameter->SetSpawnParameters(spawnParameters);
	ShootKnifer->SetShootParameter(ShootParameter);
}