// Fergus Marsden 2020.


#include "WorldWarTwo/Vehicles/FJMTrackedVehicle.h"
#include <Components/StaticMeshComponent.h>
#include <Components/SplineComponent.h>
#include <Components/AudioComponent.h>
#include <Components/HierarchicalInstancedStaticMeshComponent.h>
#include "WorldWarTwo/Library/StaticFunctions.h"
#include <TimerManager.h>
#include <Components/BoxComponent.h>
#include <Kismet/KismetMathLibrary.h>
#include <Kismet/KismetArrayLibrary.h>
#include <PhysicsEngine/PhysicsConstraintComponent.h>
#include "WorldWarTwo/Components/Vehicles/FJMVehicleSeatComponent.h"
#include "WorldWarTwo/Components/Vehicles/TankMovementComponent.h"
#include "WorldWarTwo/Components/Vehicles/FJMVehicleDismountComponent.h"

AFJMTrackedVehicle::AFJMTrackedVehicle(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	VehicleBodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VehicleBody"));
	VehicleBodyMesh->SetMobility(EComponentMobility::Movable);
	SetRootComponent(VehicleBodyMesh);

	DismountComp->SetupAttachment(VehicleBodyMesh);
	PerceptionRoot->SetupAttachment(VehicleBodyMesh);

	EngineStartAudio = CreateDefaultSubobject<UAudioComponent>(TEXT("EngineStartAudio"));
	EngineStartAudio->SetupAttachment(VehicleBodyMesh);

	EngineRunningAudio = CreateDefaultSubobject<UAudioComponent>(TEXT("EngineRunningAudio"));
	EngineRunningAudio->SetupAttachment(VehicleBodyMesh);

	EngineStopAudio = CreateDefaultSubobject<UAudioComponent>(TEXT("EngineStopAudio"));
	EngineStopAudio->SetupAttachment(VehicleBodyMesh);

	VehicleTrigger->SetupAttachment(VehicleBodyMesh);
	CameraGimbal->SetupAttachment(VehicleBodyMesh);

	DriverSeat = CreateDefaultSubobject<UFJMVehicleSeatComponent>(TEXT("DriverSeat"));
	DriverSeat->SetupAttachment(VehicleBodyMesh);
	DriverSeat->SetSeatRole(EVehiclePositions::Driver);
	DriverSeat->SetSeatIndex(2);

	TrackRight = CreateDefaultSubobject<UHierarchicalInstancedStaticMeshComponent>(TEXT("VehicleTrack_Right"));
	TrackRight->SetupAttachment(VehicleBodyMesh);
	RightTrackComps.AddUnique(TrackRight);

	SplineRight = CreateDefaultSubobject<USplineComponent>(TEXT("VehicleSpline_Right"));
	SplineRight->SetupAttachment(TrackRight);

	WheelROne = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WheelRight_1"));
	WheelROne->SetupAttachment(TrackRight);
	ApplyWheelPhysics(WheelROne);
	RightTrackComps.AddUnique(WheelROne);

	WheelRTwo = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WheelRight_2"));
	WheelRTwo->SetupAttachment(TrackRight);
	ApplyWheelPhysics(WheelRTwo);
	RightTrackComps.AddUnique(WheelRTwo);

	WheelRThree = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WheelRight_3"));
	WheelRThree->SetupAttachment(TrackRight);
	ApplyWheelPhysics(WheelRThree);
	RightTrackComps.AddUnique(WheelRThree);

	WheelRFour = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WheelRight_4"));
	WheelRFour->SetupAttachment(TrackRight);
	ApplyWheelPhysics(WheelRFour);
	RightTrackComps.AddUnique(WheelRFour);

	WheelRFive = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WheelRight_5"));
	WheelRFive->SetupAttachment(TrackRight);
	ApplyWheelPhysics(WheelRFive);
	RightTrackComps.AddUnique(WheelRFive);

	WheelRSix = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WheelRight_6"));
	WheelRSix->SetupAttachment(TrackRight);
	ApplyWheelPhysics(WheelRSix);
	RightTrackComps.AddUnique(WheelRSix);

	WheelRSeven = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WheelRight_7"));
	WheelRSeven->SetupAttachment(TrackRight);
	ApplyWheelPhysics(WheelRSeven);
	RightTrackComps.AddUnique(WheelRSeven);

	WheelREight = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WheelRight_8"));
	WheelREight->SetupAttachment(TrackRight);
	ApplyWheelPhysics(WheelREight);
	RightTrackComps.AddUnique(WheelREight);

	SuspensionROne = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SuspensionRight_1"));
	SuspensionROne->SetupAttachment(TrackRight);
	ApplySuspensionPhysics(SuspensionROne);
	RightTrackComps.AddUnique(SuspensionROne);

	SuspensionConstraintROne = CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("Suspension_R1_Constraint"));
	SuspensionConstraintROne->SetupAttachment(SuspensionROne);
	RightTrackConstraints.AddUnique(SuspensionConstraintROne);

	SuspensionRTwo = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SuspensionRight_2"));
	SuspensionRTwo->SetupAttachment(TrackRight);
	ApplySuspensionPhysics(SuspensionRTwo);
	RightTrackComps.AddUnique(SuspensionRTwo);

	SuspensionConstraintRTwo = CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("Suspension_R2_Constraint"));
	SuspensionConstraintRTwo->SetupAttachment(SuspensionRTwo);
	RightTrackConstraints.AddUnique(SuspensionConstraintRTwo);

	SuspensionRThree = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SuspensionRight_3"));
	SuspensionRThree->SetupAttachment(TrackRight);
	ApplySuspensionPhysics(SuspensionRThree);
	RightTrackComps.AddUnique(SuspensionRThree);

	SuspensionConstraintRThree = CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("Suspension_R3_Constraint"));
	SuspensionConstraintRThree->SetupAttachment(SuspensionRThree);
	RightTrackConstraints.AddUnique(SuspensionConstraintRThree);

	WheelConstraintROne = CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("Wheel_R1_Constraint"));
	WheelConstraintROne->SetupAttachment(WheelROne);
	RightTrackConstraints.AddUnique(WheelConstraintROne);

	WheelConstraintRTwo = CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("Wheel_R2_Constraint"));
	WheelConstraintRTwo->SetupAttachment(WheelRTwo);
	RightTrackConstraints.AddUnique(WheelConstraintRTwo);

	WheelConstraintRThree = CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("Wheel_R3_Constraint"));
	WheelConstraintRThree->SetupAttachment(WheelRThree);
	RightTrackConstraints.AddUnique(WheelConstraintRThree);

	WheelConstraintRFour = CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("Wheel_R4_Constraint"));
	WheelConstraintRFour->SetupAttachment(WheelRFour);
	RightTrackConstraints.AddUnique(WheelConstraintRFour);

	WheelConstraintRFive = CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("Wheel_R5_Constraint"));
	WheelConstraintRFive->SetupAttachment(WheelRFive);
	RightTrackConstraints.AddUnique(WheelConstraintRFive);

	WheelConstraintRSix = CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("Wheel_R6_Constraint"));
	WheelConstraintRSix->SetupAttachment(WheelRSix);
	RightTrackConstraints.AddUnique(WheelConstraintRSix);

	WheelConstraintRSeven = CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("Wheel_R7_Constraint"));
	WheelConstraintRSeven->SetupAttachment(WheelRSeven);
	RightTrackConstraints.AddUnique(WheelConstraintRSeven);

	WheelConstraintREight = CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("Wheel_R8_Constraint"));
	WheelConstraintREight->SetupAttachment(WheelREight);
	RightTrackConstraints.AddUnique(WheelConstraintREight);

	TrackLeft = CreateDefaultSubobject<UHierarchicalInstancedStaticMeshComponent>(TEXT("VehicleTrack_Left"));
	TrackLeft->SetupAttachment(VehicleBodyMesh);
	LeftTrackComps.AddUnique(TrackLeft);

	SplineLeft = CreateDefaultSubobject<USplineComponent>(TEXT("VehicleSpline_Left"));
	SplineLeft->SetupAttachment(TrackLeft);

	WheelLOne = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WheelLeft_1"));
	WheelLOne->SetupAttachment(TrackLeft);
	ApplyWheelPhysics(WheelLOne);
	LeftTrackComps.AddUnique(WheelLOne);

	WheelLTwo = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WheelLeft_2"));
	WheelLTwo->SetupAttachment(TrackLeft);
	ApplyWheelPhysics(WheelLTwo);
	LeftTrackComps.AddUnique(WheelLTwo);

	WheelLThree = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WheelLeft_3"));
	WheelLThree->SetupAttachment(TrackLeft);
	ApplyWheelPhysics(WheelLThree);
	LeftTrackComps.AddUnique(WheelLThree);

	WheelLFour = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WheelLeft_4"));
	WheelLFour->SetupAttachment(TrackLeft);
	ApplyWheelPhysics(WheelLFour);
	LeftTrackComps.AddUnique(WheelLFour);

	WheelLFive = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WheelLeft_5"));
	WheelLFive->SetupAttachment(TrackLeft);
	ApplyWheelPhysics(WheelLFive);
	LeftTrackComps.AddUnique(WheelLFive);

	WheelLSix = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WheelLeft_6"));
	WheelLSix->SetupAttachment(TrackLeft);
	ApplyWheelPhysics(WheelLSix);
	LeftTrackComps.AddUnique(WheelLSix);

	WheelLSeven = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WheelLeft_7"));
	WheelLSeven->SetupAttachment(TrackLeft);
	ApplyWheelPhysics(WheelLSeven);
	LeftTrackComps.AddUnique(WheelLSeven);

	WheelLEight = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WheelLeft_8"));
	WheelLEight->SetupAttachment(TrackLeft);
	ApplyWheelPhysics(WheelLEight);
	LeftTrackComps.AddUnique(WheelLEight);

	SuspensionLOne = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SuspensionLeft_1"));
	SuspensionLOne->SetupAttachment(TrackLeft);
	ApplySuspensionPhysics(SuspensionLOne);
	LeftTrackComps.AddUnique(SuspensionLOne);

	SuspensionConstraintLOne = CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("Suspension_L1_Constraint"));
	SuspensionConstraintLOne->SetupAttachment(SuspensionLOne);
	LeftTrackConstraints.AddUnique(SuspensionConstraintLOne);

	SuspensionLTwo = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SuspensionLeft_2"));
	SuspensionLTwo->SetupAttachment(TrackLeft);
	ApplySuspensionPhysics(SuspensionLTwo);
	LeftTrackComps.AddUnique(SuspensionLTwo);

	SuspensionConstraintLTwo = CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("Suspension_L2_Constraint"));
	SuspensionConstraintLTwo->SetupAttachment(SuspensionLTwo);
	LeftTrackConstraints.AddUnique(SuspensionConstraintLTwo);

	SuspensionLThree = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SuspensionLeft_3"));
	SuspensionLThree->SetupAttachment(TrackLeft);
	ApplySuspensionPhysics(SuspensionLThree);
	LeftTrackComps.AddUnique(SuspensionLThree);

	SuspensionConstraintLThree = CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("Suspension_L3_Constraint"));
	SuspensionConstraintLThree->SetupAttachment(SuspensionLThree);
	LeftTrackConstraints.AddUnique(SuspensionConstraintLThree);

	WheelConstraintLOne = CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("Wheel_L1_Constraint"));
	WheelConstraintLOne->SetupAttachment(WheelLOne);
	LeftTrackConstraints.AddUnique(WheelConstraintLOne);

	WheelConstraintLTwo = CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("Wheel_L2_Constraint"));
	WheelConstraintLTwo->SetupAttachment(WheelLTwo);
	LeftTrackConstraints.AddUnique(WheelConstraintLTwo);

	WheelConstraintLThree = CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("Wheel_L3_Constraint"));
	WheelConstraintLThree->SetupAttachment(WheelLThree);
	LeftTrackConstraints.AddUnique(WheelConstraintLThree);

	WheelConstraintLFour = CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("Wheel_L4_Constraint"));
	WheelConstraintLFour->SetupAttachment(WheelLFour);
	LeftTrackConstraints.AddUnique(WheelConstraintLFour);

	WheelConstraintLFive = CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("Wheel_L5_Constraint"));
	WheelConstraintLFive->SetupAttachment(WheelLFive);
	LeftTrackConstraints.AddUnique(WheelConstraintLFive);

	WheelConstraintLSix = CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("Wheel_L6_Constraint"));
	WheelConstraintLSix->SetupAttachment(WheelLSix);
	LeftTrackConstraints.AddUnique(WheelConstraintLSix);

	WheelConstraintLSeven = CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("Wheel_L7_Constraint"));
	WheelConstraintLSeven->SetupAttachment(WheelLSeven);
	LeftTrackConstraints.AddUnique(WheelConstraintLSeven);

	WheelConstraintLEight = CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("Wheel_L8_Constraint"));
	WheelConstraintLEight->SetupAttachment(WheelLEight);
	LeftTrackConstraints.AddUnique(WheelConstraintLEight);

	MGGimbal->SetupAttachment(VehicleBodyMesh);

	SetActorTickEnabled(true);

	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.SetTickFunctionEnable(true);
	PrimaryActorTick.bStartWithTickEnabled = true;

	WheelsLeft.Add(WheelLOne);
	WheelsLeft.Add(WheelLTwo);
	WheelsLeft.Add(WheelLThree);
	WheelsLeft.Add(WheelLFour);
	WheelsLeft.Add(WheelLFive);
	WheelsLeft.Add(WheelLSix);
	WheelsLeft.Add(WheelLSeven);
	WheelsLeft.Add(WheelLEight);

	WheelsRight.Add(WheelROne);
	WheelsRight.Add(WheelRTwo);
	WheelsRight.Add(WheelRThree);
	WheelsRight.Add(WheelRFour);
	WheelsRight.Add(WheelRFive);
	WheelsRight.Add(WheelRSix);
	WheelsRight.Add(WheelRSeven);
	WheelsRight.Add(WheelREight);

	SuspendersRight.Add(SuspensionROne);
	SuspendersRight.Add(SuspensionRTwo);
	SuspendersRight.Add(SuspensionRThree);

	SuspendersLeft.Add(SuspensionLOne);
	SuspendersLeft.Add(SuspensionLTwo);
	SuspendersLeft.Add(SuspensionLThree);

	SetupPhysics();
}

//////////////////////
//Gen Setup//////////
////////////////////

void AFJMTrackedVehicle::InitTracks()
{
	SetupWheels();
	SetupTracks();

	if (!bEditTracks)
	{
		SetupSuspensions();
		SetupPhysics();
	}

	//
}

void AFJMTrackedVehicle::SetupPhysics()
{
	VehicleBodyMesh->SetMobility(EComponentMobility::Movable);
	VehicleBodyMesh->BodyInstance.bOverrideMass = true;
	VehicleBodyMesh->BodyInstance.SetMassOverride(1000.f);
	VehicleBodyMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	VehicleBodyMesh->SetCollisionObjectType(ECollisionChannel::ECC_Vehicle);
	VehicleBodyMesh->SetGenerateOverlapEvents(false);

	for (UStaticMeshComponent* Mesh : WheelsRight)
	{
		ApplyWheelPhysics(Mesh);
	}

	for (UStaticMeshComponent* Mesh : WheelsLeft)
	{
		ApplyWheelPhysics(Mesh);
	}

	for (UStaticMeshComponent* Mesh : SuspendersRight)
	{
		ApplySuspensionPhysics(Mesh);
	}

	for (UStaticMeshComponent* Mesh : SuspendersLeft)
	{
		ApplySuspensionPhysics(Mesh);
	}

	VehicleBodyMesh->SetSimulatePhysics(true);
	CreatePhysicsConstraints();
}

//////////////////////
//Begin Play/////////
////////////////////

void AFJMTrackedVehicle::BeginPlay()
{
	Super::BeginPlay();


	bIsTurnBraking = false;
	bIsBrakingL = false;
	bIsBrakingR = false;

	SetupWheels();
	SetupTracks();
	SetupSuspensions();
	SetupPhysics();

	for (UPhysicsConstraintComponent* Constraint : PhysConstraints)
	{
		Constraint->SetLinearPositionTarget(FVector(0.f, 0.f, SuspensionLinnearPositionTargetZ));
		Constraint->SetLinearDriveParams(SuspensionLinnearPositionStrength, SuspensionLinnearVelocityStrength, 0.f);
	}

	GetWorld()->GetTimerManager().SetTimer(TrackRefreshTimer, this, &AFJMTrackedVehicle::RefreshTracks, TrackRefreshRate, true);
}

void AFJMTrackedVehicle::OnBeginUse(AFJMBaseHumanCharacter * UsingCharacter, UFJMVehicleSeatComponent * SeatUsed)
{
	if (!bEngineRunning)
	{
		EngineStartAudio->Activate(true);
		EngineStartAudio->Play();
		EngineStartAudio->FadeOut(EngineStartTime + 1, 0.f);

		FTimerHandle UnusedHandle;
		GetWorld()->GetTimerManager().SetTimer(UnusedHandle, this, &AFJMTrackedVehicle::StartEngine, EngineStartTime, false);
	}
}

void AFJMTrackedVehicle::OnEndUse()
{
	EngineRunningAudio->Deactivate();

	EngineStopAudio->Activate(true);
	EngineStopAudio->Play();

	bEngineRunning = false;
}

void AFJMTrackedVehicle::StartEngine()
{
	bEngineRunning = true;
	EngineStartAudio->Deactivate();

	EngineRunningAudio->Activate(true);
	EngineRunningAudio->Play();
}

/////////////////
//Setup Tracks//
///////////////

void AFJMTrackedVehicle::SetupTracks()
{
	TrackRight->ClearInstances();
	TrackLeft->ClearInstances();
	//First we clear the left hand spline, we will mirror the right hand ssplie onto it so that we only need to edit one.
	SplineLeft->ClearSplinePoints();

	for (uint8 i = 0; i <= SplineRight->GetNumberOfSplinePoints(); i++)
	{
		SplineRight->SetSplinePointType(i, ESplinePointType::CurveClamped, true);

		FVector SplinePointRightLoc = SplineRight->GetLocationAtSplinePoint(i, ESplineCoordinateSpace::Local);
		FVector SplinePointLeftLoc = FVector(SplinePointRightLoc.X, SplineLeft->GetRelativeLocation().Y, SplinePointRightLoc.Z);

		FVector ArriveTangeant = SplineRight->GetArriveTangentAtSplinePoint(i, ESplineCoordinateSpace::Local);
		FVector LeaveTangeant = SplineRight->GetLeaveTangentAtSplinePoint(i, ESplineCoordinateSpace::Local);
		FVector UpVector = SplineRight->GetUpVectorAtSplinePoint(i, ESplineCoordinateSpace::Local);

		SplineLeft->AddSplinePointAtIndex(SplinePointLeftLoc, i, ESplineCoordinateSpace::Local, true);
		SplineLeft->SetTangentsAtSplinePoint(i, ArriveTangeant, LeaveTangeant, ESplineCoordinateSpace::Local, true);
		SplineLeft->SetUpVectorAtSplinePoint(i, UpVector, ESplineCoordinateSpace::Local, true);
		SplineLeft->SetSplinePointType(i, ESplinePointType::CurveClamped, true);
	}

	CreateInstancedTrackMeshForSpline(SplineRight, TrackRight, true);
	CreateInstancedTrackMeshForSpline(SplineLeft, TrackLeft, false);

	TrackRight->SetStaticMesh(TrackMesh);
	TrackLeft->SetStaticMesh(TrackMesh);
}

void AFJMTrackedVehicle::RefreshTracks()
{
	if (Speed > 5.f)
	{
		TrackRight->ClearInstances();
		TrackLeft->ClearInstances();

		CreateInstancedTrackMeshForSpline(SplineRight, TrackRight, true);
		CreateInstancedTrackMeshForSpline(SplineLeft, TrackLeft, false);
	}
}

/////////////////
//Setup Wheels//
///////////////

void AFJMTrackedVehicle::SetupWheels()
{
	SuspensionLOne->SetStaticMesh(SuspensionMesh);
	SuspensionLTwo->SetStaticMesh(SuspensionMesh);
	SuspensionLThree->SetStaticMesh(SuspensionMesh);

	SuspensionROne->SetStaticMesh(SuspensionMesh);
	SuspensionRTwo->SetStaticMesh(SuspensionMesh);
	SuspensionRThree->SetStaticMesh(SuspensionMesh);

	for (UStaticMeshComponent* Wheel : WheelsRight)
	{
		if (Wheel == WheelROne && WheelFrontMesh)
		{
			WheelROne->SetStaticMesh(WheelFrontMesh);
		}
		else if (Wheel == WheelREight && WheelBackMesh)
		{
			WheelREight->SetStaticMesh(WheelBackMesh);
		}
		else
		{
			Wheel->SetStaticMesh(WheelMesh);
		}

		FVector WheelPos = Wheel->GetRelativeLocation();
		FVector NewRelLoc = FVector(WheelPos.X, WheelsHalfWidth, WheelPos.Z);
	}

	for (UStaticMeshComponent* Wheel : WheelsLeft)
	{
		Wheel->SetPhysMaterialOverride(WheelPhyscialMaterial);

		if (Wheel == WheelLOne && WheelFrontMesh)
		{
			WheelLOne->SetStaticMesh(WheelFrontMesh);
		}
		else if (Wheel == WheelLEight && WheelBackMesh)
		{
			WheelLEight->SetStaticMesh(WheelBackMesh);
		}
		else
		{
			Wheel->SetStaticMesh(WheelMesh);
		}

		FVector WheelPos = Wheel->GetRelativeLocation();
		FVector NewRelLoc = FVector(WheelPos.X, WheelsHalfWidth, WheelPos.Z);
	}

}

void AFJMTrackedVehicle::ApplyWheelPhysics(UStaticMeshComponent* Wheel)
{
	//TODO if physics is sloppy look at position solver iteration count - see BP for details.
	Wheel->SetMobility(EComponentMobility::Movable);
	Wheel->BodyInstance.bOverrideMass = bShouldOverrideMass;
	Wheel->BodyInstance.SetMassOverride(WheelMassKG);
	Wheel->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Wheel->SetCollisionObjectType(ECollisionChannel::ECC_PhysicsBody);
	Wheel->SetGenerateOverlapEvents(false);
	Wheel->SetSimulatePhysics(true);
}

void AFJMTrackedVehicle::SetupWheelConstraints(UPhysicsConstraintComponent* Constraint)
{
	Constraint->ConstraintInstance.ProfileInstance.bDisableCollision = true;
	Constraint->ConstraintInstance.ProfileInstance.bEnableProjection = true;
	Constraint->ConstraintInstance.ProfileInstance.ProjectionAngularTolerance = 1.f;
	Constraint->ConstraintInstance.ProfileInstance.ProjectionLinearTolerance = 1.f;

	Constraint->SetAngularSwing1Limit(EAngularConstraintMotion::ACM_Locked, 45.f);
	Constraint->SetAngularSwing2Limit(EAngularConstraintMotion::ACM_Free, 45.f);
	Constraint->SetAngularTwistLimit(EAngularConstraintMotion::ACM_Locked, 45.f);

	Constraint->SetAngularDriveMode(EAngularDriveMode::TwistAndSwing);
}

bool AFJMTrackedVehicle::WheelIsGrounded(UStaticMeshComponent* Wheel)
{
	FVector GroundLocation;
	UStaticFunctions::GetGroundLocationAtVector(GetWorld(), Wheel->GetComponentLocation(), GroundLocation);

	float DistanceToGround = (GroundLocation - Wheel->GetComponentLocation()).Size();
	float ZOffsetAbsolute = UKismetMathLibrary::Abs(TrackHeightOffset);

	if (DistanceToGround <= ZOffsetAbsolute)
	{
		return true;
	}
	else
	{
		return false;
	}
}

/////////////////
//Setup Susp////
///////////////

bool AFJMTrackedVehicle::SetupSuspensions()
{
	uint8 CountRight = 0;
	for (UStaticMeshComponent* WheelR : WheelsRight)
	{
		AdjustSplinePointForWheel(WheelR, SplineRight, CountRight, true);
		RotateWheels(WheelR, true);
		CountRight++;
	}

	uint8 CountLeft = 0;
	for (UStaticMeshComponent* WheelL : WheelsLeft)
	{
		AdjustSplinePointForWheel(WheelL, SplineLeft, CountLeft, false);
		RotateWheels(WheelL, false);
		CountLeft++;
	}

	return true;
}

void AFJMTrackedVehicle::ApplySuspensionPhysics(UStaticMeshComponent* Suspension)
{
	Suspension->SetMobility(EComponentMobility::Movable);
	Suspension->BodyInstance.bOverrideMass = bShouldOverrideMass;
	Suspension->BodyInstance.SetMassOverride(SuspensionMassKG);
	Suspension->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Suspension->SetCollisionObjectType(ECollisionChannel::ECC_Vehicle);
	Suspension->SetGenerateOverlapEvents(false);
	Suspension->SetSimulatePhysics(true);
}

void AFJMTrackedVehicle::SetupSuspensionConstraints(UPhysicsConstraintComponent* Constraint)
{
	PhysConstraints.Add(Constraint);

	Constraint->ConstraintInstance.ProfileInstance.bDisableCollision = true;
	Constraint->ConstraintInstance.ProfileInstance.bEnableProjection = true;
	Constraint->ConstraintInstance.ProfileInstance.ProjectionAngularTolerance = 1.f;
	Constraint->ConstraintInstance.ProfileInstance.ProjectionLinearTolerance = 1.f;

	Constraint->SetAngularSwing1Limit(EAngularConstraintMotion::ACM_Locked, 0.f);
	Constraint->SetAngularSwing2Limit(EAngularConstraintMotion::ACM_Locked, 0.f);
	Constraint->SetAngularTwistLimit(EAngularConstraintMotion::ACM_Locked, 0.f);

	Constraint->SetLinearXLimit(ELinearConstraintMotion::LCM_Locked, 0.f);
	Constraint->SetLinearYLimit(ELinearConstraintMotion::LCM_Locked, 0.f);
	Constraint->SetLinearZLimit(ELinearConstraintMotion::LCM_Limited, SuspensionLinnearPositionAllowanceZ);
	Constraint->SetLinearDriveParams(SuspensionLinnearPositionStrength, SuspensionLinnearVelocityStrength, 0.f);
	Constraint->SetLinearPositionTarget(FVector(0.f, 0.f, SuspensionLinnearPositionTargetZ));
	Constraint->SetLinearPositionDrive(false, false, true);
	Constraint->SetLinearVelocityDrive(false, false, true);
}

////////////////
//Movement/////
//////////////

void AFJMTrackedVehicle::CalculateMovementForce(float& ForceRight, float& ForceLeft)
{
	float FR = 0.f;
	float FL = 0.f;

	if (bIsBrakingR)
	{
		BrakeLevelRight = UKismetMathLibrary::FClamp((BrakeLevelRight + BrakingFactor), 0.f, 1.f);
	}
	else
	{
		BrakeLevelRight = UKismetMathLibrary::FClamp((BrakeLevelRight - BrakingFactor), 0.f, 1.f);
	}

	if (bIsBrakingL)
	{
		BrakeLevelLeft = UKismetMathLibrary::FClamp((BrakeLevelLeft + BrakingFactor), 0.f, 1.f);
	}
	else
	{
		BrakeLevelLeft = UKismetMathLibrary::FClamp((BrakeLevelLeft - BrakingFactor), 0.f, 1.f);
	}

	if (MoveForwardInput > 0.f)
	{
		FR = 1.f;
		FL = 1.f;
	}
	else if (MoveForwardInput < 0.f)
	{
		FR = -1.f;
		FL = -1.f;
	}
	else
	{
		//is equal to 0.f
		if (MoveRightInput == 0.f)
		{
			FR = 0.f;
			FL = 0.f;
		}
		else
		{
			FR = MoveRightInput * -1;
			FL = MoveRightInput * 1;
		}
	}

	ForceRight = FR;
	ForceLeft = FL;
}

void AFJMTrackedVehicle::SimulateBodyTorque()
{
	if (!bIsFlying)
	{
		if (Speed < 15.f)
		{
			FVector NewTorque = (VehicleBodyMesh->GetRightVector() * 50.f) * MoveForwardInput;
			VehicleBodyMesh->AddTorqueInDegrees(NewTorque, NAME_None, true);
		}
	}
}

void AFJMTrackedVehicle::MoveForward(float AxisValue)
{
	if (!LeftTrackDestroyed && !RightTrackDestroyed)
	{
		if (MoveRightInput < 0.3 && MoveRightInput > -0.3)
		{
			if (AxisValue < 0.1 && AxisValue > -0.1)
			{
				MoveForwardInput = 0.f;
			}
			else
			{
				MoveForwardInput = AxisValue;
			}
		}
	}
	else
	{
		MoveForwardInput = 0.f;
	}
}

void AFJMTrackedVehicle::MoveRight(float AxisValue)
{
	if (!LeftTrackDestroyed && !RightTrackDestroyed)
	{
		UE_LOG(LogTemp, Warning, TEXT("vehicle Move Right: %f"), AxisValue);
		if (AxisValue < 0.1 && AxisValue > -0.1)
		{
			MoveRightInput = 0.f;
			bIsBrakingL = false;
			bIsBrakingR = false;
		}
		else if (AxisValue < 0.3 && AxisValue > -0.3)
		{
			MoveRightInput = AxisValue;

			if (MoveForwardInput == 0.f)
			{
				bIsBrakingL = false;
				bIsBrakingR = false;
			}
			else if (!bIsTurnBraking)
			{
				if (AxisValue > 0.f)
				{
					bIsBrakingL = false;
					bIsBrakingR = true;
				}
				else if (AxisValue < 0.f)
				{
					bIsBrakingL = true;
					bIsBrakingR = false;
				}
				else
				{
					//Axis is 0
					bIsBrakingL = false;
					bIsBrakingR = false;
				}
			}
		}
		else
		{
			MoveRightInput = UKismetMathLibrary::FClamp(AxisValue * 10, -1, 1);
			MoveForwardInput = 0.f;

			bIsBrakingL = false;
			bIsBrakingR = false;
		}
	}
	else
	{
		MoveRightInput = 0.f;
		bIsBrakingL = false;
		bIsBrakingR = false;
	}
}

////////////////
//Tick/////////
//////////////

void AFJMTrackedVehicle::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	if (bIsDestroyed)
	{

	}
	else
	{
		FVector BodyVelocity = VehicleBodyMesh->GetComponentVelocity();
		Speed = BodyVelocity.Size() * 0.036;

		bool bIsRightLeftInput = UKismetMathLibrary::Abs(MoveRightInput) > 0.3;
		bool IsMoving = Speed > 12.f;

		if (bIsRightLeftInput && IsMoving)
		{
			bIsTurnBraking = true;
			bIsBrakingL = true;
			bIsBrakingR = true;
			MoveForwardInput = 0.f;
		}
		else
		{
			bIsFlying = CheckIsFlying();
			bIsTurnBraking = false;
		}

		//calculate movement force
		float ForceRight;
		float ForceLeft;
		CalculateMovementForce(ForceRight, ForceLeft);
		
		TrackRightForward = UKismetMathLibrary::FInterpTo(TrackRightForward, ForceRight, DeltaSeconds, TankHandling);
		TrackLeftForward = UKismetMathLibrary::FInterpTo(TrackLeftForward, ForceLeft, DeltaSeconds, TankHandling);
		
		SetupSuspensions();
		HandleLinearDamping();
		
		float LeftSpeed;
		float RightSpeed;
		UpdateTrackSpeed(LeftSpeed, RightSpeed);

		TrackSpeedLeft = LeftSpeed;
		TrackSpeedRight = RightSpeed;

		ModulateEngineSounds();
	}
	
}

float AFJMTrackedVehicle::GetMoveForwardInput() const
{
	return MoveForwardInput;
}

float AFJMTrackedVehicle::GetMoveRightInput() const
{
	return MoveRightInput;
}

bool AFJMTrackedVehicle::GetLeftTrackDestroyed() const
{
	return LeftTrackDestroyed;
}

bool AFJMTrackedVehicle::GetRightTrackDestroyed() const
{
	return RightTrackDestroyed;
}

bool AFJMTrackedVehicle::CheckIsFlying()
{
	for (UStaticMeshComponent* Wheel : WheelsRight)
	{
		if (WheelIsGrounded(Wheel))
		{
			return false;
		}
	}

	for (UStaticMeshComponent* Wheel : WheelsLeft)
	{
		if (WheelIsGrounded(Wheel))
		{
			return false;
		}
	}

	return true;
}

void AFJMTrackedVehicle::HandleLinearDamping()
{
	if (bIsFlying)
	{
		VehicleBodyMesh->SetLinearDamping(0.f);
	}
	else
	{
		if (UKismetMathLibrary::Abs(MoveForwardInput) <= 0.2f)
		{
			if (Speed < 1.f)
			{
				VehicleBodyMesh->SetLinearDamping(StationaryDampingValue);
			}
		}
		else
		{
			VehicleBodyMesh->SetLinearDamping(0.f);
		}
	}
}

void AFJMTrackedVehicle::UpdateTrackSpeed(float& LeftSpeed, float& RightSpeed)
{
	float RightBaseSpeed = (TrackRightForward * 100) / TrackSpeedMultiplier;
	RightSpeed = RightBaseSpeed * BrakeLevelRight * CurrentGear;
	UpdateTrackMesh(RightSpeed, TrackInfosRight);

	float LeftBaseSpeed = (TrackLeftForward * 100) / TrackSpeedMultiplier;
	LeftSpeed = LeftBaseSpeed * BrakeLevelLeft * CurrentGear;
	UpdateTrackMesh(LeftSpeed, TrackInfosLeft);
}

bool AFJMTrackedVehicle::UpdateTrackMesh(float ThisSpeed, TArray<FTrackInfo>& TrackPoints)
{
	//TODO sort track breaks
	uint8 IteratorIndex = 0;
	for (FTrackInfo ThisTrackPoint : TrackPoints)
	{
		float ThisSplineLength = ThisTrackPoint.Spline->GetSplineLength();

		float AvgTrackPointLength = (ThisTrackPoint.CDist * ThisSplineLength) / UKismetMathLibrary::FClamp(ThisTrackPoint.CurrentSplineLength, 0.1, 10000);
		float NextSplineLength = AvgTrackPointLength + ThisSpeed;
		float SplineAverageFactor = AvgTrackPointLength - ThisSplineLength;
		float TrackLengthFactor = ThisSplineLength - AvgTrackPointLength;
		float SpeedLength = ThisSpeed + TrackLengthFactor;

		float SelectedSpeed = NextSplineLength <= 0.f ? SpeedLength : NextSplineLength;
		float SelectedLength = NextSplineLength >= ThisSplineLength ? SplineAverageFactor : SelectedSpeed;

		FVector SplineLocation = ThisTrackPoint.Spline->GetLocationAtDistanceAlongSpline(SelectedLength, ESplineCoordinateSpace::World);
		FRotator SplineRotation = ThisTrackPoint.Spline->GetRotationAtDistanceAlongSpline(SelectedLength, ESplineCoordinateSpace::World);
		FTransform NewTransForm = FTransform(SplineRotation, SplineLocation, FVector(1.f, 1.f, 1.f));

		bool bRenderDirty = IteratorIndex == (TrackPoints.Num() - 1);

		ThisTrackPoint.HISM->UpdateInstanceTransform(ThisTrackPoint.Instance, NewTransForm, true, bRenderDirty, true);

		ThisTrackPoint.CDist = SelectedLength;
		ThisTrackPoint.CurrentSplineLength = ThisTrackPoint.Spline->GetSplineLength();

		TrackPoints[IteratorIndex] = ThisTrackPoint;

		IteratorIndex++;
	}

	return true;
}

void AFJMTrackedVehicle::ModulateEngineSounds()
{
	static FName RPMParam = FName(TEXT("RPM"));
	float AbsLeft = UKismetMathLibrary::Abs(TrackLeftForward);
	float AbsRight = UKismetMathLibrary::Abs(TrackRightForward);

	float NewRpm = (AbsLeft + AbsRight) / 2;

	EngineRunningAudio->SetFloatParameter(RPMParam, NewRpm);
}

/////////////////////
//Wheel/Track Calc//
///////////////////

void AFJMTrackedVehicle::CreateInstancedTrackMeshForSpline(USplineComponent * Spline, UHierarchicalInstancedStaticMeshComponent* InstancedObject, bool bIsRightTrack)
{
	if (bIsRightTrack)
	{
		TrackInfosRight.Empty();
	}
	else
	{
		TrackInfosLeft.Empty();
	}

	uint8 LastIndex = UKismetMathLibrary::FTrunc(Spline->GetSplineLength() / TrackLength);
	
	for (uint8 i = 0; i <= LastIndex; i++)
	{
		FVector AddInstanceLoc = Spline->GetLocationAtDistanceAlongSpline((TrackLength * i), ESplineCoordinateSpace::World);
		FRotator AddInstanceRot = Spline->GetRotationAtDistanceAlongSpline((TrackLength * i), ESplineCoordinateSpace::World);
		FVector AddInstanceScale = FVector(1.f, 1.f, 1.f);
		FTransform AddInstanceTrans = FTransform(AddInstanceRot, AddInstanceLoc, AddInstanceScale);

		uint8 Instance = InstancedObject->AddInstanceWorldSpace(AddInstanceTrans);

		if (bIsRightTrack)
		{
			FTrackInfo RTrackInfo;
			RTrackInfo.Instance = Instance;
			RTrackInfo.CDist = TrackLength * i;
			RTrackInfo.HISM = InstancedObject;
			RTrackInfo.Spline = Spline;
			RTrackInfo.CurrentSplineLength = Spline->GetSplineLength();

			TrackInfosRight.Add(RTrackInfo);
		}
		else
		{
			FTrackInfo LTrackInfo;
			LTrackInfo.Instance = Instance;
			LTrackInfo.CDist = TrackLength * i;
			LTrackInfo.HISM = InstancedObject;
			LTrackInfo.Spline = Spline;
			LTrackInfo.CurrentSplineLength = Spline->GetSplineLength();

			TrackInfosLeft.Add(LTrackInfo);
		}
	}
}

UStaticMeshComponent* AFJMTrackedVehicle::AdjustSplinePointForWheel(UStaticMeshComponent* Wheel, USplineComponent* Spline, uint8 Index, bool bIsRight)
{
	uint8 SplineEditIndexFront = FrontWheelTrackIndexArray.FindRef(Index);
	uint8 SplineEditIndexBack = BackWheelTrackIndexArray.FindRef(Index);

	if (Index > 6 || Index == 0)
	{
		return Wheel;
	}
	else
	{
		FVector SplineLocationA = Wheel->GetComponentLocation() + (VehicleBodyMesh->GetUpVector() * TrackHeightOffset) + (VehicleBodyMesh->GetForwardVector() * 15);
		Spline->SetLocationAtSplinePoint(SplineEditIndexFront, SplineLocationA, ESplineCoordinateSpace::World, true);

		FVector SplineLocationB = Wheel->GetComponentLocation() + (VehicleBodyMesh->GetUpVector() * TrackHeightOffset) + (VehicleBodyMesh->GetForwardVector() * -15);
		Spline->SetLocationAtSplinePoint(SplineEditIndexBack, SplineLocationB, ESplineCoordinateSpace::World, true);

		return Wheel;
	}
}

void AFJMTrackedVehicle::RotateWheels(UStaticMeshComponent* Wheel, bool bIsRight)
{
	float TrackSpeed = bIsRight ? TrackSpeedRight : TrackSpeedLeft;
	float BrakeAmmount = bIsRight ? BrakeLevelRight : BrakeLevelLeft;

	float MutlSpeed = TrackSpeed * BrakeAmmount;
	float WheelSpeed = MutlSpeed * WheelRotationMultiplier;
	FVector NewAngVelocity = bIsRight ? WheelSpeed * Wheel->GetRightVector() : (WheelSpeed * Wheel->GetRightVector()) * -1;

	Wheel->SetPhysicsAngularVelocityInRadians(NewAngVelocity);
}

UStaticMeshComponent * AFJMTrackedVehicle::GetVehicleBodyMesh() const
{
	return VehicleBodyMesh;
}

////////////////
//Destroy//////
//////////////

bool AFJMTrackedVehicle::DestroyVehicle()
{
	bIsDestroyed = true;
	GetWorldTimerManager().ClearTimer(TrackRefreshTimer);

	bool RetValue = Super::DestroyVehicle();

	TArray<UActorComponent*> OutPhysComponents;
	GetComponents(UPhysicsConstraintComponent::StaticClass(), OutPhysComponents);

	for (UActorComponent* OutComp : OutPhysComponents)
	{
		if (UPhysicsConstraintComponent* PhysComp = Cast<UPhysicsConstraintComponent>(OutComp))
		{
			PhysComp->BreakConstraint();
		}
	}

	OnEndUse();
	TrackRight->ClearInstances();
	TrackLeft->ClearInstances();
	return RetValue;
}

void AFJMTrackedVehicle::DestroyTrack()
{
	DestroyTrackRight();
	DestroyTrackLeft();
}

void AFJMTrackedVehicle::DestroyTrackRight()
{
	for (uint8 i = 0; i <= TrackRight->GetInstanceCount(); i++)
	{
		FTransform InstanceTransform;
		bool hasTransform = TrackRight->GetInstanceTransform(i, InstanceTransform);

		if (hasTransform)
		{
			FName name = "RTrackMeshTemp";
			FString base = name.ToString();
			base.Append(FString::FromInt(i));
			FName CompName = FName(*base);
			UStaticMeshComponent* TrackMeshTemp = NewObject<UStaticMeshComponent>(this, CompName);

			FAttachmentTransformRules TransRules = FAttachmentTransformRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, false);
			TrackMeshTemp->AttachToComponent(TrackRight, TransRules);

			TrackMeshTemp->SetStaticMesh(TrackRight->GetStaticMesh());
			TrackMeshTemp->SetRelativeTransform(InstanceTransform);
			TrackMeshTemp->SetSimulatePhysics(true);
			TrackMeshTemp->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);

			TrackRight->ClearInstances();

			RightTrackDestroyed = true;
		}
	}

	for (UPhysicsConstraintComponent* PhysComp : RightTrackConstraints)
	{
		PhysComp->BreakConstraint();
	}

	for (USceneComponent* TrackPart : RightTrackComps)
	{
		if (UPrimitiveComponent* Prim = Cast<UPrimitiveComponent>(TrackPart))
		{
			Prim->AddRadialImpulse(GetActorLocation(), 750, 100, ERadialImpulseFalloff::RIF_Linear);
		}
	}
}

void AFJMTrackedVehicle::DestroyTrackLeft()
{
	for (uint8 i = 0; i <= TrackLeft->GetInstanceCount(); i++)
	{
		FTransform InstanceTransform;
		bool hasTransform = TrackLeft->GetInstanceTransform(i, InstanceTransform);

		if (hasTransform)
		{
			FName name = "LTrackMeshTemp";
			FString base = name.ToString();
			base.Append(FString::FromInt(i));
			FName CompName = FName(*base);
			UStaticMeshComponent* TrackMeshTemp = NewObject<UStaticMeshComponent>(this, CompName);

			FAttachmentTransformRules TransRules = FAttachmentTransformRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, false);
			TrackMeshTemp->AttachToComponent(TrackLeft, TransRules);

			TrackMeshTemp->SetStaticMesh(TrackLeft->GetStaticMesh());
			TrackMeshTemp->SetRelativeTransform(InstanceTransform);
			TrackMeshTemp->SetSimulatePhysics(true);

			TrackLeft->ClearInstances();

			LeftTrackDestroyed = true;
		}
	}

	for (UPhysicsConstraintComponent* PhysComp : LeftTrackConstraints)
	{
		PhysComp->BreakConstraint();
	}

	for (USceneComponent* TrackPart : LeftTrackComps)
	{
		if (UPrimitiveComponent* Prim = Cast<UPrimitiveComponent>(TrackPart))
		{
			Prim->AddRadialImpulse(GetActorLocation(), 750, 100, ERadialImpulseFalloff::RIF_Linear);
		}
	}
}

////////////////
//Constraints//
//////////////

void AFJMTrackedVehicle::CreatePhysicsConstraints()
{
	SuspensionConstraintROne->ComponentName1.ComponentName = FName(TEXT("VehicleBody"));
	SuspensionConstraintROne->ComponentName2.ComponentName = FName(TEXT("SuspensionRight_1"));
	SetupSuspensionConstraints(SuspensionConstraintROne);

	SuspensionConstraintRTwo->ComponentName1.ComponentName = FName(TEXT("VehicleBody"));
	SuspensionConstraintRTwo->ComponentName2.ComponentName = FName(TEXT("SuspensionRight_2"));
	SetupSuspensionConstraints(SuspensionConstraintRTwo);

	SuspensionConstraintRThree->ComponentName1.ComponentName = FName(TEXT("VehicleBody"));
	SuspensionConstraintRThree->ComponentName2.ComponentName = FName(TEXT("SuspensionRight_3"));
	SetupSuspensionConstraints(SuspensionConstraintRThree);
	
	WheelConstraintROne->ComponentName1.ComponentName = FName(TEXT("WheelRight_1"));
	WheelConstraintROne->ComponentName2.ComponentName = FName(TEXT("VehicleBody"));
	SetupWheelConstraints(WheelConstraintROne);

	WheelConstraintRTwo->ComponentName1.ComponentName = FName(TEXT("WheelRight_2"));
	WheelConstraintRTwo->ComponentName2.ComponentName = FName(TEXT("SuspensionRight_1"));
	SetupWheelConstraints(WheelConstraintRTwo);

	WheelConstraintRThree->ComponentName1.ComponentName = FName(TEXT("WheelRight_3"));
	WheelConstraintRThree->ComponentName2.ComponentName = FName(TEXT("SuspensionRight_1"));
	SetupWheelConstraints(WheelConstraintRThree);

	WheelConstraintRFour->ComponentName1.ComponentName = FName(TEXT("WheelRight_4"));
	WheelConstraintRFour->ComponentName2.ComponentName = FName(TEXT("SuspensionRight_2"));
	SetupWheelConstraints(WheelConstraintRFour);

	WheelConstraintRFive->ComponentName1.ComponentName = FName(TEXT("WheelRight_5"));
	WheelConstraintRFive->ComponentName2.ComponentName = FName(TEXT("SuspensionRight_2"));
	SetupWheelConstraints(WheelConstraintRFive);

	WheelConstraintRSix->ComponentName1.ComponentName = FName(TEXT("WheelRight_6"));
	WheelConstraintRSix->ComponentName2.ComponentName = FName(TEXT("SuspensionRight_3"));
	SetupWheelConstraints(WheelConstraintRSix);

	WheelConstraintRSeven->ComponentName1.ComponentName = FName(TEXT("WheelRight_7"));
	WheelConstraintRSeven->ComponentName2.ComponentName = FName(TEXT("SuspensionRight_3"));
	SetupWheelConstraints(WheelConstraintRSeven);

	WheelConstraintREight->ComponentName1.ComponentName = FName(TEXT("WheelRight_8"));
	WheelConstraintREight->ComponentName2.ComponentName = FName(TEXT("VehicleBody"));
	SetupWheelConstraints(WheelConstraintREight);

	SuspensionConstraintLOne->ComponentName1.ComponentName = FName(TEXT("VehicleBody"));
	SuspensionConstraintLOne->ComponentName2.ComponentName = FName(TEXT("SuspensionLeft_1"));
	SetupSuspensionConstraints(SuspensionConstraintLOne);

	SuspensionConstraintLTwo->ComponentName1.ComponentName = FName(TEXT("VehicleBody"));
	SuspensionConstraintLTwo->ComponentName2.ComponentName = FName(TEXT("SuspensionLeft_2"));
	SetupSuspensionConstraints(SuspensionConstraintLTwo);

	SuspensionConstraintLThree->ComponentName1.ComponentName = FName(TEXT("VehicleBody"));
	SuspensionConstraintLThree->ComponentName2.ComponentName = FName(TEXT("SuspensionLeft_3"));
	SetupSuspensionConstraints(SuspensionConstraintLThree);
	
	WheelConstraintLOne->ComponentName1.ComponentName = FName(TEXT("WheelLeft_1"));
	WheelConstraintLOne->ComponentName2.ComponentName = FName(TEXT("VehicleBody"));
	SetupWheelConstraints(WheelConstraintLOne);

	WheelConstraintLTwo->ComponentName1.ComponentName = FName(TEXT("WheelLeft_2"));
	WheelConstraintLTwo->ComponentName2.ComponentName = FName(TEXT("SuspensionLeft_1"));
	SetupWheelConstraints(WheelConstraintLTwo);

	WheelConstraintLThree->ComponentName1.ComponentName = FName(TEXT("WheelLeft_3"));
	WheelConstraintLThree->ComponentName2.ComponentName = FName(TEXT("SuspensionLeft_1"));
	SetupWheelConstraints(WheelConstraintLThree);

	WheelConstraintLFour->ComponentName1.ComponentName = FName(TEXT("WheelLeft_4"));
	WheelConstraintLFour->ComponentName2.ComponentName = FName(TEXT("SuspensionLeft_2"));
	SetupWheelConstraints(WheelConstraintLFour);

	WheelConstraintLFive->ComponentName1.ComponentName = FName(TEXT("WheelLeft_5"));
	WheelConstraintLFive->ComponentName2.ComponentName = FName(TEXT("SuspensionLeft_2"));
	SetupWheelConstraints(WheelConstraintLFive);

	WheelConstraintLSix->ComponentName1.ComponentName = FName(TEXT("WheelLeft_6"));
	WheelConstraintLSix->ComponentName2.ComponentName = FName(TEXT("SuspensionLeft_3"));
	SetupWheelConstraints(WheelConstraintLSix);

	WheelConstraintLSeven->ComponentName1.ComponentName = FName(TEXT("WheelLeft_7"));
	WheelConstraintLSeven->ComponentName2.ComponentName = FName(TEXT("SuspensionLeft_3"));
	SetupWheelConstraints(WheelConstraintLSeven);

	WheelConstraintLEight->ComponentName1.ComponentName = FName(TEXT("WheelLeft_8"));
	WheelConstraintLEight->ComponentName2.ComponentName = FName(TEXT("VehicleBody"));
	SetupWheelConstraints(WheelConstraintLEight);
}
