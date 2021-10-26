// Fergus Marsden 2020.

#pragma once

#include <CoreMinimal.h>
#include "WorldWarTwo/Vehicles/FJMLightArmedVehicle.h"
#include "FJMTrackedVehicle.generated.h"

class UHierarchicalInstancedStaticMeshComponent;
class USplineComponent;
class UPhysicsConstraintComponent;
class UNavMovementComponent;
class UFJMVehicleSeatComponent;
class UAudioComponent;

struct FTrackInfo
{
	uint8 Instance;
	float CDist;
	FRotator UserRotation;
	UHierarchicalInstancedStaticMeshComponent* HISM;
	USplineComponent* Spline;
	float CurrentSplineLength;
};

/**
 * 
 */
UCLASS()
class WORLDWARTWO_API AFJMTrackedVehicle : public AFJMLightArmedVehicle
{
	GENERATED_BODY()

public:
	AFJMTrackedVehicle(const FObjectInitializer& ObjectInitializer);

	UStaticMeshComponent* GetVehicleBodyMesh() const;

//////////////////////
//Components/////////
////////////////////
protected:
	UPROPERTY(Category = Vehicle, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* VehicleBodyMesh = nullptr;

	UPROPERTY(Category = Vehicle, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UAudioComponent* EngineStartAudio = nullptr;

	UPROPERTY(Category = Vehicle, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UAudioComponent* EngineRunningAudio = nullptr;

	UPROPERTY(Category = Vehicle, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UAudioComponent* EngineStopAudio = nullptr;

	/**This is the root component and forms the extent of the cover zone, pawns must be overlapping this box in order to use the cover positions within it.	*/
	UPROPERTY(Category = Cannon, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UFJMVehicleSeatComponent* DriverSeat = nullptr;

	UPROPERTY(Category = Vehicle, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UHierarchicalInstancedStaticMeshComponent* TrackRight = nullptr;

	UPROPERTY(Category = Vehicle, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USplineComponent* SplineRight = nullptr;

	UPROPERTY(Category = Vehicle, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* WheelROne = nullptr;

	UPROPERTY(Category = Vehicle, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UPhysicsConstraintComponent* WheelConstraintROne = nullptr;

	UPROPERTY(Category = Vehicle, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* WheelRTwo = nullptr;

	UPROPERTY(Category = Vehicle, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UPhysicsConstraintComponent* WheelConstraintRTwo = nullptr;

	UPROPERTY(Category = Vehicle, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* WheelRThree = nullptr;

	UPROPERTY(Category = Vehicle, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UPhysicsConstraintComponent* WheelConstraintRThree = nullptr;

	UPROPERTY(Category = Vehicle, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* WheelRFour = nullptr;

	UPROPERTY(Category = Vehicle, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UPhysicsConstraintComponent* WheelConstraintRFour = nullptr;

	UPROPERTY(Category = Vehicle, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* WheelRFive = nullptr;

	UPROPERTY(Category = Vehicle, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UPhysicsConstraintComponent* WheelConstraintRFive = nullptr;

	UPROPERTY(Category = Vehicle, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* WheelRSix = nullptr;

	UPROPERTY(Category = Vehicle, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UPhysicsConstraintComponent* WheelConstraintRSix = nullptr;

	UPROPERTY(Category = Vehicle, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* WheelRSeven = nullptr;

	UPROPERTY(Category = Vehicle, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UPhysicsConstraintComponent* WheelConstraintRSeven = nullptr;

	UPROPERTY(Category = Vehicle, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* WheelREight = nullptr;

	UPROPERTY(Category = Vehicle, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UPhysicsConstraintComponent* WheelConstraintREight = nullptr;

	UPROPERTY(Category = Vehicle, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* SuspensionROne = nullptr;

	UPROPERTY(Category = Vehicle, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UPhysicsConstraintComponent* SuspensionConstraintROne = nullptr;

	UPROPERTY(Category = Vehicle, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* SuspensionRTwo = nullptr;

	UPROPERTY(Category = Vehicle, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UPhysicsConstraintComponent* SuspensionConstraintRTwo = nullptr;

	UPROPERTY(Category = Vehicle, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* SuspensionRThree = nullptr;

	UPROPERTY(Category = Vehicle, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UPhysicsConstraintComponent* SuspensionConstraintRThree = nullptr;

	UPROPERTY(Category = Vehicle, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UHierarchicalInstancedStaticMeshComponent* TrackLeft = nullptr;

	UPROPERTY(Category = Vehicle, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USplineComponent* SplineLeft = nullptr;

	UPROPERTY(Category = Vehicle, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* WheelLOne = nullptr;

	UPROPERTY(Category = Vehicle, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UPhysicsConstraintComponent* WheelConstraintLOne = nullptr;

	UPROPERTY(Category = Vehicle, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* WheelLTwo = nullptr;

	UPROPERTY(Category = Vehicle, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UPhysicsConstraintComponent* WheelConstraintLTwo = nullptr;

	UPROPERTY(Category = Vehicle, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* WheelLThree = nullptr;

	UPROPERTY(Category = Vehicle, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UPhysicsConstraintComponent* WheelConstraintLThree = nullptr;

	UPROPERTY(Category = Vehicle, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* WheelLFour = nullptr;

	UPROPERTY(Category = Vehicle, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UPhysicsConstraintComponent* WheelConstraintLFour = nullptr;

	UPROPERTY(Category = Vehicle, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* WheelLFive = nullptr;

	UPROPERTY(Category = Vehicle, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UPhysicsConstraintComponent* WheelConstraintLFive = nullptr;

	UPROPERTY(Category = Vehicle, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* WheelLSix = nullptr;

	UPROPERTY(Category = Vehicle, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UPhysicsConstraintComponent* WheelConstraintLSix = nullptr;

	UPROPERTY(Category = Vehicle, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* WheelLSeven = nullptr;

	UPROPERTY(Category = Vehicle, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UPhysicsConstraintComponent* WheelConstraintLSeven = nullptr;

	UPROPERTY(Category = Vehicle, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* WheelLEight = nullptr;

	UPROPERTY(Category = Vehicle, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UPhysicsConstraintComponent* WheelConstraintLEight = nullptr;

	UPROPERTY(Category = Vehicle, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* SuspensionLOne = nullptr;

	UPROPERTY(Category = Vehicle, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UPhysicsConstraintComponent* SuspensionConstraintLOne = nullptr;

	UPROPERTY(Category = Vehicle, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* SuspensionLTwo = nullptr;

	UPROPERTY(Category = Vehicle, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UPhysicsConstraintComponent* SuspensionConstraintLTwo = nullptr;

	UPROPERTY(Category = Vehicle, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* SuspensionLThree = nullptr;

	UPROPERTY(Category = Vehicle, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UPhysicsConstraintComponent* SuspensionConstraintLThree = nullptr;

//////////////////////
//Gen Setup//////////
////////////////////
public:
	//initialise track physics and constraints
	UFUNCTION(BlueprintCallable)
	void InitTracks();

	//set the vehicle body up as a physics component - apply contraint options to wheels and suspension.
	virtual void SetupPhysics();

//////////////////////
//Begin Play/////////
////////////////////
public:
	/*Start the timer to reset the tracks every on the track refresh rate
	* Sets all the constraints and wheels to defaults.
	*/
	virtual void BeginPlay() override;

	//Begin Engine Audio
	virtual void OnBeginUse(AFJMBaseHumanCharacter* UsingCharacter, UFJMVehicleSeatComponent* SeatUsed) override;

protected:
	//Stop Engine audio and disable engine.
	virtual void OnEndUse() override;

	void StartEngine();

private:
	UPROPERTY(Category = Engine, EditAnywhere)
	float EngineStartTime = 2.f;

	bool bEngineRunning = false;

/////////////////
//Setup Tracks//
///////////////
protected:
	/*Connect the track splines to the wheels and constraints so that they do not float.
	*Create Instanced Meshes for the tracks */
	UFUNCTION(BlueprintCallable)
	void SetupTracks();

	//Refresh the instanced track meshes
	void RefreshTracks();

	//the maximum distance the tracks can move from their constraints.
	UPROPERTY(Category = Tracks, EditAnywhere)
	float TrackHeightOffset = -25.f;

	TArray<USceneComponent*> RightTrackComps;
	TArray<USceneComponent*> LeftTrackComps;

	TArray<UPhysicsConstraintComponent*> RightTrackConstraints;
	TArray<UPhysicsConstraintComponent*> LeftTrackConstraints;

private:
	/*Set to true while editing splines, prevents wheel construction while editing splines.*/
	UPROPERTY(Category = Tracks, EditAnywhere)
	bool bEditTracks = true;

	//the mesh to use for a section of the track
	UPROPERTY(Category = Tracks, EditAnywhere)
	UStaticMesh* TrackMesh = nullptr;

	//how often we refresh the tracks - if we dont refresh the track will eventually run out!
	UPROPERTY(Category = Tracks, EditAnywhere)
	float TrackRefreshRate = 5.f;

	//the spline length of the tracks
	UPROPERTY(Category = Tracks, EditAnywhere)
	float TrackLength = 20.f;

	TArray<FTrackInfo> TrackInfosRight;
	TArray<FTrackInfo> TrackInfosLeft;

	FTimerHandle TrackRefreshTimer;

/////////////////
//Setup Wheels//
///////////////
protected:
	//Sets the meshes for the wheels and suspension
	UFUNCTION(BlueprintCallable)
	void SetupWheels();

	//Sets the wheels as Physical components and applies the physic settings.
	void ApplyWheelPhysics(UStaticMeshComponent* Wheel);

	//Sets the physics constraints on the wheels - this will ensure they do not drop away from the vehicle and is able to drive it forward.
	void SetupWheelConstraints(UPhysicsConstraintComponent* Constraint);

	//Check if the wheel passed to the function is touching the ground.
	bool WheelIsGrounded(UStaticMeshComponent* Wheel);

	//An array tracking which spline point relates to which wheel - it means we can accurately attach the spline to the wheels so they dont look detatched.
	UPROPERTY(Category = Tracks, EditAnywhere)
	TMap<uint8, uint8> FrontWheelTrackIndexArray;

	//An array tracking which spline point relates to which wheel - it means we can accurately attach the spline to the wheels so they dont look detatched.
	UPROPERTY(Category = Tracks, EditAnywhere)
	TMap<uint8, uint8> BackWheelTrackIndexArray;

	//The material used on the wheels - this needs to be high friction in order to drive a heavy vehicle forward.
	UPROPERTY(Category = Wheels, EditAnywhere)
	UPhysicalMaterial* WheelPhyscialMaterial = nullptr;

private:
	//Average Wheel Mesh
	UPROPERTY(Category = Wheels, EditAnywhere)
	UStaticMesh* WheelMesh = nullptr;

	//BAck Wheel Mesh
	UPROPERTY(Category = Wheels, EditAnywhere)
	UStaticMesh* WheelBackMesh = nullptr;

	//Front Wheel Mesh
	UPROPERTY(Category = Wheels, EditAnywhere)
	UStaticMesh* WheelFrontMesh = nullptr;

	//the width of the wheels - helps us to centre the spline points of the track on the wheels.
	UPROPERTY(Category = Wheels, EditAnywhere)
	float WheelsHalfWidth = 150.f;

	//Wheel Mass
	UPROPERTY(Category = Wheels, EditAnywhere)
	float WheelMassKG = 100.f;

	TArray<UStaticMeshComponent*> WheelsRight;
	TArray<UStaticMeshComponent*> WheelsLeft;

/////////////////
//Setup Susp////
///////////////
protected:
	//Constrains wheels to the relevant peice of suspension.
	UFUNCTION(BlueprintCallable)
	virtual bool SetupSuspensions();

	//Sets the Suspension as Physical components and applies the physic settings.
	void ApplySuspensionPhysics(UStaticMeshComponent* Suspension);

	//Sets the physics constraints on the wheels - this will ensure they do not drop away from the vehicle and is able to drive it forward.
	void SetupSuspensionConstraints(UPhysicsConstraintComponent* Constraint);

	//The stiffness of the constraint drive on the suspension
	UPROPERTY(Category = Suspension, EditAnywhere)
	float SuspensionLinnearPositionStrength = 1000.f;

	//The Damping of the constraint drive on the suspension
	UPROPERTY(Category = Suspension, EditAnywhere)
	float SuspensionLinnearVelocityStrength = 0.f;

	//Linear target for the suspension constraint.
	UPROPERTY(Category = Suspension, EditAnywhere)
	float SuspensionLinnearPositionTargetZ = 10.f;

	UPROPERTY(Category = Suspension, EditAnywhere)
	float SuspensionLinnearPositionAllowanceZ = 20.f;

private:
	//Used to set the override mass option on the suspension meshes.
	UPROPERTY(Category = Wheels, EditAnywhere)
	bool bShouldOverrideMass = true;

	//The mesh to use for the suspension
	UPROPERTY(Category = Suspension, EditAnywhere)
	UStaticMesh* SuspensionMesh = nullptr;

	//Mass of the suspension
	UPROPERTY(Category = Suspension, EditAnywhere)
	float SuspensionMassKG = 100.f;

	TArray<UStaticMeshComponent*> SuspendersRight;
	TArray<UStaticMeshComponent*> SuspendersLeft;

////////////////
//Movement/////
//////////////
protected:
	/*This function sets the drive force of the left and right track depending on the braking and forward input variables
	*it takes in two references that will be set and returned where the funciton is called.*/
	void CalculateMovementForce(float& ForceRight, float& ForceLeft);

	//sets the move forward variable based on input
	UFUNCTION(BlueprintCallable)
	void MoveForward(float AxisValue) override;

	//sets the move right variable based on input
	UFUNCTION(BlueprintCallable)
	void MoveRight(float AxisValue) override;

	//simulates the G force drag on a heavy vehicle giving the appearence of lurching under acceleration.
	void SimulateBodyTorque();

	float MoveForwardInput = 0.f;
	float MoveRightInput = 0.f;

private:
	//This stops the vehicle from sliding around while stationary, if sliding still occurs, increase value.
	UPROPERTY(Category = Tracks, EditAnywhere)
	float StationaryDampingValue = 20.f;

	float TrackSpeedRight = 0.f;
	float TrackSpeedLeft = 0.f;

	float TrackRightForward = 0.f;
	float TrackLeftForward = 0.f;

	float Speed = 0.f;
	float TrackSpeedMultiplier = 30.f;

	uint8 CurrentGear = 1;

	//this affects how quickly the vehicle can turn.
	UPROPERTY(Category = Brakes, EditAnywhere)
	float TankHandling = 0.25f;

	//this affects how quickly the vehicle can brake.
	UPROPERTY(Category = Brakes, EditAnywhere)
	float BrakingFactor = -0.25f;

	bool bIsTurnBraking = false;
	bool bIsBrakingL = false;
	bool bIsBrakingR = false;
	float BrakeLevelRight = 0.f;
	float BrakeLevelLeft = 0.f;

	bool bIsFlying = false;

////////////////
//Tick/////////
//////////////
public:
	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION(BlueprintCallable)
	float GetMoveForwardInput() const;

	UFUNCTION(BlueprintCallable)
	float GetMoveRightInput() const;

	//Check that the tank is in the air and has no contact with hte ground
	bool CheckIsFlying();

	//Uses the linear damping value to stop the tank sliding.
	void HandleLinearDamping();

	//updates the speed of the track movement - this does not affect actual movement but gives the impression the tracks are driving the vehicle.
	void UpdateTrackSpeed(float& LeftSpeed, float& RightSpeed);

	//Resets the track mesh instances to their original positions - this is to stop us running out of track!
	bool UpdateTrackMesh(float Speed, TArray<FTrackInfo>& TrackPoints);

	//Sets the variables within the engine audio component so that the engine sounds change depending on speed.
	void ModulateEngineSounds();

/////////////////////
//Wheel/Track Calc//
///////////////////
protected:
	//ensure that the track splines stay attached to the wheels as the vehicle moves.
	virtual UStaticMeshComponent* AdjustSplinePointForWheel(UStaticMeshComponent* Wheel, USplineComponent* Spline, uint8 Index, bool bIsRight);

	//Turns the wheels - this is what drives the vehicle.
	void RotateWheels(UStaticMeshComponent* Wheel, bool bIsRight);

private:
	//create the mesh instances for the track.
	void CreateInstancedTrackMeshForSpline(USplineComponent* Spline, UHierarchicalInstancedStaticMeshComponent* InstancedObject, bool bIsRightTrack);

	UPROPERTY(Category = Wheels, EditAnywhere)
	float WheelRotationMultiplier = 6.f;

////////////////
//Destroy//////
//////////////
public:
	UFUNCTION(BlueprintCallable)
	bool GetLeftTrackDestroyed() const;

	UFUNCTION(BlueprintCallable)
	bool GetRightTrackDestroyed() const;

	virtual bool DestroyVehicle() override;

protected:
	void DestroyTrack();
	void DestroyTrackRight();
	void DestroyTrackLeft();

private:
	bool LeftTrackDestroyed = false;
	bool RightTrackDestroyed = false;
////////////////
//Constraints//
//////////////
protected:
	virtual void CreatePhysicsConstraints();

private:
	TArray<UPhysicsConstraintComponent*> PhysConstraints;

	template <typename T>
	static void SetArrayElement(T item, TArray<T>& item_array, int32 index)
	{
		if (item_array.Num() - 1 < index)
			item_array.SetNum(index);

		item_array.Insert(item, index);
	}
};
