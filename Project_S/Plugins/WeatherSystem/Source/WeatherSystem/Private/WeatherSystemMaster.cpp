#include "WeatherSystemMaster.h"
#include "Math/UnrealMathUtility.h"
#include "Net/UnrealNetwork.h"
#include "TimerManager.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

AWeatherSystemMaster::AWeatherSystemMaster()
{
	PrimaryActorTick.bCanEverTick = true;
	SetupDefaults();
	bReplicates = true;
	bAlwaysRelevant = true;
}

void AWeatherSystemMaster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bSnowIsComing || bRainIsComing) {
		GetPlayerLocation();
	}
}

void AWeatherSystemMaster::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AWeatherSystemMaster, bSnowIsComing);
	DOREPLIFETIME(AWeatherSystemMaster, bRainIsComing);
	DOREPLIFETIME(AWeatherSystemMaster, bIsNight);
}

void AWeatherSystemMaster::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority()) {
		GetWorldTimerManager().SetTimer(RandomWeatherTimerHandle, this, &AWeatherSystemMaster::WeatherRandomFunc, WeatherRandomTime, WeatherRandomTimeLoop, 1.0f);
		GetWorldTimerManager().SetTimer(ThunderTimerHandle, this, &AWeatherSystemMaster::ThunderAudioPlay, ThunderWaitingTime, true, 1.0f);
	}

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AWaterBase::StaticClass(), WaterArray);

	SunTimeLine->Play();

	UpdateSunFloat.BindDynamic(this, &AWeatherSystemMaster::UpdateSunTimeLine);
	if (SunAngleCurve) {
		SunTimeLine->AddInterpFloat(SunAngleCurve, UpdateSunFloat);
	}

	UpdateIsNightFloat.BindDynamic(this, &AWeatherSystemMaster::UpdateIsNightTimeLine);
	if (IsNightCurve) {
		IsNightTimeLine->AddInterpFloat(IsNightCurve, UpdateIsNightFloat);
	}

	UpdateSnowOrRainFallingFloat.BindDynamic(this, &AWeatherSystemMaster::UpdateSnowOrRainFallingTimeLine);
	if (SnowOrRainFallingCurve) {
		SnowOrRainFallingTimeLine->AddInterpFloat(SnowOrRainFallingCurve, UpdateSnowOrRainFallingFloat);
	}

	UpdateRainFallingFloat.BindDynamic(this, &AWeatherSystemMaster::UpdateRainFallingTimeLine);
	if (RainFallingCurve) {
		RainFallingTimeLine->AddInterpFloat(RainFallingCurve, UpdateRainFallingFloat);
	}

	UpdateSnowFallingFloat.BindDynamic(this, &AWeatherSystemMaster::UpdateSnowFallingTimeLine);
	if (SnowFallingCurve) {
		SnowFallingTimeLine->AddInterpFloat(SnowFallingCurve, UpdateSnowFallingFloat);
	}

	UpdateGetWetFloat.BindDynamic(this, &AWeatherSystemMaster::UpdateGetWetTimeLine);
	if (GetWetCurve) {
		GetWetTimeLine->AddInterpFloat(GetWetCurve, UpdateGetWetFloat);
	}

	UpdateFrozenFloat.BindDynamic(this, &AWeatherSystemMaster::UpdateFrozenTimeLine);
	if (FrozenCurve) {
		FrozenTimeLine->AddInterpFloat(FrozenCurve, UpdateFrozenFloat);
	}
}

void AWeatherSystemMaster::WeatherRandomFunc()
{
	if (!HasAuthority()) return; // 서버에서만 실행

	if (AlwaysRain && AlwaysSnow) {
		WeatherMin = 5;
		WeatherMax = 5;
		WeatherRandomTimeLoop = false;
	}
	else if (AlwaysSunny) {
		WeatherMin = 3;
		WeatherMax = 3;
		WeatherRandomTimeLoop = false;
	}
	else if (AlwaysRain) {
		WeatherMin = 10;
		WeatherMax = 10;
		WeatherRandomTimeLoop = false;
	}
	else if (AlwaysSnow) {
		WeatherMin = 0;
		WeatherMax = 0;
		WeatherRandomTimeLoop = false;
	}
	else {
		WeatherMin = 0;
		WeatherMax = 10;
		WeatherRandomTimeLoop = true;
	}

	WeatherSet = FMath::RandRange(WeatherMin, WeatherMax);
	if (WeatherSet == 5) {
		bRainIsComing = true;
		bSnowIsComing = true;
	}
	else if (WeatherSet <= 2) {
		bSnowIsComing = true;
		bRainIsComing = false;
	}
	else if (WeatherSet >= 8) {
		bSnowIsComing = false;
		bRainIsComing = true;
	}
	else {
		bSnowIsComing = false;
		bRainIsComing = false;
	}

	// 동기화된 상태를 모든 클라이언트에게 업데이트
	MulticastUpdateWeather(bSnowIsComing, bRainIsComing, bIsNight);
}

void AWeatherSystemMaster::MulticastUpdateWeather_Implementation(bool bSnow, bool bRain, bool bNight)
{
	bSnowIsComing = bSnow;
	bRainIsComing = bRain;
	bIsNight = bNight;
	UpdateWeather();
}

void AWeatherSystemMaster::ServerUpdateWeather_Implementation()
{
	WeatherRandomFunc();
}

bool AWeatherSystemMaster::ServerUpdateWeather_Validate()
{
	return true;
}

void AWeatherSystemMaster::UpdateWeather()
{
	if (bSnowIsComing && bRainIsComing) {
		SnowOrRainFallingTimeLine->Play();
		SnowFallingTimeLine->Play();
		FrozenTimeLine->Play();
		RainFallingTimeLine->Play();
		GetWetTimeLine->Play();
		DirectionalLight->SetEnableLightShaftBloom(false);
		DirectionalLight->SetEnableLightShaftOcclusion(false);
		UKismetMaterialLibrary::SetScalarParameterValue(this, MPC_Tree, FName(TEXT("Wind_Speed")), WindSpeedOfSnowOrRain);
	}
	else if (bSnowIsComing) {
		SnowOrRainFallingTimeLine->Play();
		SnowFallingTimeLine->Play();
		FrozenTimeLine->Play();
		RainFallingTimeLine->Reverse();
		GetWetTimeLine->Reverse();
		DirectionalLight->SetEnableLightShaftBloom(false);
		DirectionalLight->SetEnableLightShaftOcclusion(false);
		UKismetMaterialLibrary::SetScalarParameterValue(this, MPC_Tree, FName(TEXT("Wind_Speed")), WindSpeedOfSnowOrRain);
	}
	else if (bRainIsComing) {
		SnowOrRainFallingTimeLine->Play();
		SnowFallingTimeLine->Reverse();
		FrozenTimeLine->Reverse();
		RainFallingTimeLine->Play();
		GetWetTimeLine->Play();
		DirectionalLight->SetEnableLightShaftBloom(false);
		DirectionalLight->SetEnableLightShaftOcclusion(false);
		UKismetMaterialLibrary::SetScalarParameterValue(this, MPC_Tree, FName(TEXT("Wind_Speed")), WindSpeedOfSnowOrRain);
	}
	else {
		SnowOrRainFallingTimeLine->Reverse();
		SnowFallingTimeLine->Reverse();
		FrozenTimeLine->Reverse();
		RainFallingTimeLine->Reverse();
		GetWetTimeLine->Reverse();
		DirectionalLight->SetEnableLightShaftBloom(true);
		DirectionalLight->SetEnableLightShaftOcclusion(true);
		UKismetMaterialLibrary::SetScalarParameterValue(this, MPC_Tree, FName(TEXT("Wind_Speed")), WindSpeedOfSunny);
	}
}

void AWeatherSystemMaster::UpdateIsNightTimeLine(float IsNightOutput)
{
	SkyLight->SetIntensity(FMath::Lerp(SkyLightIntensityOfDay, SkyLightIntensityOfNight, IsNightOutput));
	UKismetMaterialLibrary::SetVectorParameterValue(this, MPC, FName(TEXT("SnowColor")), FMath::Lerp(SnowColorOfDay, SnowColorOfNight, IsNightOutput));
	UKismetMaterialLibrary::SetVectorParameterValue(this, MPC, FName(TEXT("RainColor")), FMath::Lerp(RainColorOfDay, RainColorOfNight, IsNightOutput));

	if (bSnowIsComing || bRainIsComing) {
		UKismetMaterialLibrary::SetScalarParameterValue(this, MPC, FName(TEXT("StarsMask")), 0.0f);
		UKismetMaterialLibrary::SetScalarParameterValue(this, MPC, FName(TEXT("CloudDisappear")), 0.5f);
		BirdsAudio->SetVolumeMultiplier(0.0f);
		CicadaAudio->SetVolumeMultiplier(0.0f);
	}
	else {
		UKismetMaterialLibrary::SetScalarParameterValue(this, MPC, FName(TEXT("StarsMask")), FMath::Lerp(0.0f, 3.0f, IsNightOutput));
		UKismetMaterialLibrary::SetScalarParameterValue(this, MPC, FName(TEXT("CloudDisappear")), FMath::Lerp(0.5f, 1.0f, IsNightOutput));
		BirdsAudio->SetVolumeMultiplier(FMath::Lerp(FMath::RandRange(0.5f, 1.0f), 0.0f, IsNightOutput));
		CicadaAudio->SetVolumeMultiplier(FMath::Lerp(FMath::RandRange(0.5f, 1.0f), 0.0f, IsNightOutput));
	}
}

void AWeatherSystemMaster::UpdateSunTimeLine(float SunOutput)
{
	if (AlwaysDayTime) {
		DirectionalLight->SetRelativeRotation(FRotator(233.0f, 0.0f, 0.0f));
		bIsNight = false;
		IsNightTimeLine->Reverse();
	}
	else if (AlwaysNight) {
		DirectionalLight->SetRelativeRotation(FRotator(100.0f, 0.0f, 0.0f));
		bIsNight = true;
		IsNightTimeLine->Play();
	}
	else {
		DirectionalLight->SetRelativeRotation(FRotator(SunOutput, 0.0f, 0.0f));
		if (SunOutput == 360.0f) {
			SunTimeLine->PlayFromStart();
		}
		else if (SunOutput >= 2.5f && SunOutput <= 167.5f) {
			bIsNight = true;
			IsNightTimeLine->Play();
		}
		else {
			bIsNight = false;
			IsNightTimeLine->Reverse();
		}
	}
}

void AWeatherSystemMaster::GetPlayerLocation()
{
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (PlayerController) {
		APawn* PlayerPawn = PlayerController->GetPawn();
		if (PlayerPawn) {
			FVector PlayerLocation = PlayerPawn->GetActorLocation() + FVector(0.0f, 0.0f, 500.0f);
			SnowFX->SetWorldLocation(PlayerLocation);
			RainFX->SetWorldLocation(PlayerLocation);
		}
	}
}

void AWeatherSystemMaster::ThunderAudioPlay()
{
	if (bRainIsComing) {
		ThunderAudio->Play();
		ThunderAudio->SetVolumeMultiplier(FMath::RandRange(ThunderMinVolume, ThunderMaxVolume));
	}
	else {
		ThunderAudio->Stop();
	}
}

void AWeatherSystemMaster::UpdateSnowOrRainFallingTimeLine(float SnowOrRainFallingOutput)
{
	WindAudio->SetVolumeMultiplier(FMath::Lerp(0.0f, FMath::RandRange(0.8f, 1.0f), SnowOrRainFallingOutput));
	DirectionalLight->SetIntensity(FMath::Lerp(SunIntensityOfSunny, SunIntensityOfRainOrSnow, SnowOrRainFallingOutput));
	DirectionalLight->SetTemperature(FMath::Lerp(SunTemperatureOfDaytime, SunTemperatureOfNight, SnowOrRainFallingOutput));
	ExponentialHeightFog->SetFogDensity(FMath::Lerp(FogDensityOfSunny, FogDensityOfRainOrSnow, SnowOrRainFallingOutput));
	ExponentialHeightFog->SetFogHeightFalloff(FMath::Lerp(FogHeightFalloffOfSunny, FogHeightFalloffOfRainOrSnow, SnowOrRainFallingOutput));
	SkyAtmosphere->SetSkyLuminanceFactor(FMath::Lerp(SnowColorOfDay, DarkClouds, SnowOrRainFallingOutput));
	UKismetMaterialLibrary::SetScalarParameterValue(this, MPC_Tree, FName(TEXT("Wind_Weight")), FMath::Lerp(WindWeightOfSunny, WindWeightOfSnowOrRain, SnowOrRainFallingOutput));
	UKismetMaterialLibrary::SetVectorParameterValue(this, MPC, FName(TEXT("CloudColor")), FMath::Lerp(SnowColorOfDay, DarkClouds, SnowOrRainFallingOutput));
	UKismetMaterialLibrary::SetScalarParameterValue(this, MPC, FName(TEXT("StarsMask")), 0.0f);
	if (bIsNight) {
		BirdsAudio->SetVolumeMultiplier(0.0f);
		CicadaAudio->SetVolumeMultiplier(0.0f);
	}
	else {
		BirdsAudio->SetVolumeMultiplier(FMath::Lerp(FMath::RandRange(0.5f, 1.0f), 0.0f, SnowOrRainFallingOutput));
		CicadaAudio->SetVolumeMultiplier(FMath::Lerp(FMath::RandRange(0.5f, 1.0f), 0.0f, SnowOrRainFallingOutput));
	}
}

void AWeatherSystemMaster::UpdateRainFallingTimeLine(float RainFallingOutput)
{
	RainFX->SetFloatParameter(FName(TEXT("SpawnRate")), FMath::Lerp(0.0f, MaxRainFalling, RainFallingOutput));
	RainFX->SetFloatParameter(FName(TEXT("SpawnRate_02")), FMath::Lerp(0.0f, MaxRainFalling / 100.0f, RainFallingOutput));
	RainFX->SetFloatParameter(FName(TEXT("SpawnRate_Fog")), FMath::Lerp(0.0f, MaxRainFogFalling, RainFallingOutput));
	RainAudio->SetVolumeMultiplier(FMath::Lerp(0.0f, 1.0f, RainFallingOutput));
	UKismetMaterialLibrary::SetScalarParameterValue(this, MPC, FName(TEXT("RainDropsBlend")), FMath::Lerp(0.0f, RainDropsBlendMax, RainFallingOutput));
}

void AWeatherSystemMaster::UpdateSnowFallingTimeLine(float SnowFallingOutput)
{
	SnowFX->SetFloatParameter(FName(TEXT("SnowNumber")), FMath::Lerp(0.0f, MaxSnowFalling, SnowFallingOutput));
	SnowAudio->SetVolumeMultiplier(FMath::Lerp(0.0f, 1.0f, SnowFallingOutput));
}

void AWeatherSystemMaster::UpdateGetWetTimeLine(float GetWetOutput)
{
	UKismetMaterialLibrary::SetScalarParameterValue(this, MPC, FName(TEXT("Roughness")), FMath::Lerp(1.0f, GetWetRoughness, GetWetOutput));
	UKismetMaterialLibrary::SetScalarParameterValue(this, MPC, FName(TEXT("Specular")), FMath::Lerp(1.0f, GetWetSpecular, GetWetOutput));
}

void AWeatherSystemMaster::UpdateFrozenTimeLine(float FrozenOutput)
{
	UKismetMaterialLibrary::SetScalarParameterValue(this, MPC, FName(TEXT("SnowBlend")), FMath::Lerp(3.0f, SnowBlendMax, FrozenOutput));
	UKismetMaterialLibrary::SetScalarParameterValue(this, MPC, FName(TEXT("WaterFrozen")), FMath::Lerp(0.0f, 1000.0f, FrozenOutput));
	if (FrozenOutput >= 0.1 && WaterArray.Num()) {
		for (int i = 0; i < WaterArray.Num(); i++) {
			Cast<AWaterBase>(WaterArray[i])->SetWaterBloackAll();
		}
	}
	else if (WaterArray.Num()) {
		for (int i = 0; i < WaterArray.Num(); i++) {
			Cast<AWaterBase>(WaterArray[i])->SetWaterNoCollision();
		}
	}
}

void AWeatherSystemMaster::SetupDefaults()
{
	// Root Component
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	AWeatherSystemMaster::SetRootComponent(RootComponent);

	// Directional Light
	DirectionalLight = CreateDefaultSubobject<UDirectionalLightComponent>(TEXT("DirectionalLight"));
	DirectionalLight->SetupAttachment(RootComponent);
	DirectionalLight->SetMobility(EComponentMobility::Movable);
	DirectionalLight->SetRelativeRotation_Direct(FRotator(233.0f, 0.0f, 0.0f));
	DirectionalLight->bUseTemperature = true;
	DirectionalLight->Temperature = 4500.0f;
	DirectionalLight->bEnableLightShaftOcclusion = true;
	DirectionalLight->OcclusionMaskDarkness = 1.0f;
	DirectionalLight->bEnableLightShaftBloom = true;
	DirectionalLight->BloomScale = 0.5f;
	DirectionalLight->BloomMaxBrightness = 5.0f;
	DirectionalLight->bUsedAsAtmosphereSunLight = true;
	DirectionalLight->DynamicShadowDistanceMovableLight = 200000.0f;
	DirectionalLight->DynamicShadowCascades = 5.0f;
	DirectionalLight->CascadeDistributionExponent = 4.0f;
	DirectionalLight->CascadeTransitionFraction = 0.3f;

	// Sky Light
	SkyLight = CreateDefaultSubobject<USkyLightComponent>(TEXT("SkyLight"));
	SkyLight->SetupAttachment(RootComponent);
	SkyLight->SetMobility(EComponentMobility::Movable);
	SkyLight->Intensity = 1.2f;
	SkyLight->SourceType = SLS_SpecifiedCubemap;
	CubemapTemp = LoadObject<UTextureCube>(NULL, TEXT("TextureCube'/WeatherSystem/HDRI/CubeMap.CubeMap'"));
	SkyLight->Cubemap = CubemapTemp;
	SkyLight->bCloudAmbientOcclusion = true;

	// Sky Atmosphere
	SkyAtmosphere = CreateDefaultSubobject<USkyAtmosphereComponent>(TEXT("SkyAtmosphere"));
	SkyAtmosphere->SetupAttachment(RootComponent);
	SkyAtmosphere->SetMobility(EComponentMobility::Movable);
	SkyAtmosphere->SetSkyLuminanceFactor(FVector(0.5f, 0.625f, 1.0f));

	// Post Process
	PostProcessComp = CreateDefaultSubobject<UPostProcessComponent>(TEXT("PostProcess"));
	PostProcessComp->SetupAttachment(RootComponent);
	PostProcessComp->SetMobility(EComponentMobility::Movable);
	PostProcessComp->bUnbound = true;
	PostProcessComp->Settings.bOverride_BloomIntensity = true;
	PostProcessComp->Settings.BloomIntensity = 0.0f;
	PostProcessComp->Settings.bOverride_AutoExposureBias = true;
	PostProcessComp->Settings.AutoExposureBias = 0.0f;
	PostProcessComp->Settings.bOverride_VignetteIntensity = true;
	PostProcessComp->Settings.VignetteIntensity = 0.5f;
	PostProcessComp->Settings.bOverride_ColorGradingLUT = true;
	PostProcessComp->Settings.bOverride_ColorGradingIntensity = true;
	PostProcessComp->Settings.ColorGradingIntensity = 0.5f;
	LUT = LoadObject<UTexture2D>(NULL, TEXT("Texture2D'/WeatherSystem/HDRI/RGBTableAutoMap.RGBTableAutoMap'"));
	PostProcessComp->Settings.ColorGradingLUT = LUT;

	// Volumetric Cloud
	VolumetricCloud = CreateDefaultSubobject<UVolumetricCloudComponent>(TEXT("VolumetricCloud"));
	VolumetricCloud->SetupAttachment(RootComponent);
	VolumetricCloud->SetMobility(EComponentMobility::Movable);
	VolumetricCloud->LayerBottomAltitude = 20.0f;
	CloudMaterial = LoadObject<UMaterialInstance>(NULL, TEXT("MaterialInstanceConstant'/WeatherSystem/FX/Materials/M_SimpleVolumetricCloud_Inst.M_SimpleVolumetricCloud_Inst'"));
	VolumetricCloud->SetMaterial(CloudMaterial);
	VolumetricCloud->bUsePerSampleAtmosphericLightTransmittance = true;

	// Exponential Height Fog
	ExponentialHeightFog = CreateDefaultSubobject<UExponentialHeightFogComponent>(TEXT("ExponentialHeightFog"));
	ExponentialHeightFog->SetupAttachment(RootComponent);
	ExponentialHeightFog->SetMobility(EComponentMobility::Movable);
	ExponentialHeightFog->SetRelativeLocation(FVector(0.0f, 0.0f, 5000.0f));

	// Sky Sphere
	SkySphere = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SkySphere"));
	SkySphere->SetupAttachment(RootComponent);
	SkySphereMesh = LoadObject<UStaticMesh>(NULL, TEXT("StaticMesh'/WeatherSystem/Sky/SM_SkySphere.SM_SkySphere'"));
	SkySphere->SetStaticMesh(SkySphereMesh);
	SkySphere->SetRelativeScale3D(FVector(5000.0f));
	SkyMaterial = LoadObject<UMaterial>(NULL, TEXT("Material'/WeatherSystem/Sky/Materials/M_Sky.M_Sky'"));
	SkySphere->SetMaterial(0, SkyMaterial);
	SkySphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SkySphere->CastShadow = false;

	// Rain FX
	RainFX = CreateDefaultSubobject<UNiagaraComponent>(TEXT("RainFX"));
	RainFX->SetupAttachment(RootComponent);
	RainFX->SetVisibility(true);
	NS_RainFall = LoadObject<UNiagaraSystem>(NULL, TEXT("NiagaraSystem'/WeatherSystem/FX/NS_RainFall.NS_RainFall'"));
	RainFX->SetAsset(NS_RainFall);

	// Rain Audio
	RainAudio = CreateDefaultSubobject<UAudioComponent>(TEXT("RainAudio"));
	RainAudio->SetupAttachment(RootComponent);
	RainSound = LoadObject<USoundCue>(NULL, TEXT("SoundCue'/WeatherSystem/Sounds/Cue/Rain_Cue.Rain_Cue'"));
	RainAudio->SetSound(RainSound);
	RainAudio->VolumeMultiplier = 0.0f;

	// Thunder Audio
	ThunderAudio = CreateDefaultSubobject<UAudioComponent>(TEXT("ThunderAudio"));
	ThunderAudio->SetupAttachment(RootComponent);
	ThunderSound = LoadObject<USoundCue>(NULL, TEXT("SoundCue'/WeatherSystem/Sounds/Cue/Thunder_Cue.Thunder_Cue'"));
	ThunderAudio->SetSound(ThunderSound);
	ThunderAudio->VolumeMultiplier = 0.0f;

	// Snow FX
	SnowFX = CreateDefaultSubobject<UNiagaraComponent>(TEXT("SnowFX"));
	SnowFX->SetupAttachment(RootComponent);
	SnowFX->SetVisibility(true);
	NS_SnowFall = LoadObject<UNiagaraSystem>(NULL, TEXT("NiagaraSystem'/WeatherSystem/FX/NS_SnowFall.NS_SnowFall'"));
	SnowFX->SetAsset(NS_SnowFall);

	// Snow Audio
	SnowAudio = CreateDefaultSubobject<UAudioComponent>(TEXT("SnowAudio"));
	SnowAudio->SetupAttachment(RootComponent);
	SnowSound = LoadObject<USoundCue>(NULL, TEXT("SoundCue'/WeatherSystem/Sounds/Cue/Snow_Cue.Snow_Cue'"));
	SnowAudio->SetSound(SnowSound);
	SnowAudio->VolumeMultiplier = 0.0f;

	// Wind Audio
	WindAudio = CreateDefaultSubobject<UAudioComponent>(TEXT("WindAudio"));
	WindAudio->SetupAttachment(RootComponent);
	WindSound = LoadObject<USoundCue>(NULL, TEXT("SoundCue'/WeatherSystem/Sounds/Cue/Wind_Cue.Wind_Cue'"));
	WindAudio->SetSound(WindSound);
	WindAudio->VolumeMultiplier = 0.0f;

	// Birds Audio
	BirdsAudio = CreateDefaultSubobject<UAudioComponent>(TEXT("BirdsAudio"));
	BirdsAudio->SetupAttachment(RootComponent);
	BirdsSound = LoadObject<USoundCue>(NULL, TEXT("SoundCue'/WeatherSystem/Sounds/Cue/Birds_Cue.Birds_Cue'"));
	BirdsAudio->SetSound(BirdsSound);

	// Cicada Audio
	CicadaAudio = CreateDefaultSubobject<UAudioComponent>(TEXT("CicadaAudio"));
	CicadaAudio->SetupAttachment(RootComponent);
	CicadaSound = LoadObject<USoundCue>(NULL, TEXT("SoundCue'/WeatherSystem/Sounds/Cue/Cicada_Loop.Cicada_Loop'"));
	CicadaAudio->SetSound(CicadaSound);

	// Timelines
	IsNightTimeLine = CreateDefaultSubobject<UTimelineComponent>(TEXT("IsNightTimeLine"));
	IsNightCurve = LoadObject<UCurveFloat>(NULL, TEXT("CurveFloat'/WeatherSystem/Curve/IsNightLerp.IsNightLerp'"));

	SunTimeLine = CreateDefaultSubobject<UTimelineComponent>(TEXT("SunTimeLine"));
	SunAngleCurve = LoadObject<UCurveFloat>(NULL, TEXT("CurveFloat'/WeatherSystem/Curve/SunAngle.SunAngle'"));

	SnowOrRainFallingTimeLine = CreateDefaultSubobject<UTimelineComponent>(TEXT("SnowOrRainFallingTimeLine"));
	SnowOrRainFallingCurve = LoadObject<UCurveFloat>(NULL, TEXT("CurveFloat'/WeatherSystem/Curve/SnowOrRainFalling.SnowOrRainFalling'"));

	GetWetTimeLine = CreateDefaultSubobject<UTimelineComponent>(TEXT("GetWetTimeLine"));
	GetWetCurve = LoadObject<UCurveFloat>(NULL, TEXT("CurveFloat'/WeatherSystem/Curve/GetWet.GetWet'"));

	FrozenTimeLine = CreateDefaultSubobject<UTimelineComponent>(TEXT("FrozenTimeLine"));
	FrozenCurve = LoadObject<UCurveFloat>(NULL, TEXT("CurveFloat'/WeatherSystem/Curve/Frozen.Frozen'"));

	RainFallingTimeLine = CreateDefaultSubobject<UTimelineComponent>(TEXT("RainFallingTimeLine"));
	RainFallingCurve = LoadObject<UCurveFloat>(NULL, TEXT("CurveFloat'/WeatherSystem/Curve/RainFalling.RainFalling'"));

	SnowFallingTimeLine = CreateDefaultSubobject<UTimelineComponent>(TEXT("SnowFallingTimeLine"));
	SnowFallingCurve = LoadObject<UCurveFloat>(NULL, TEXT("CurveFloat'/WeatherSystem/Curve/SnowFalling.SnowFalling'"));

	// Material Parameter Collections
	MPC = LoadObject<UMaterialParameterCollection>(NULL, TEXT("MaterialParameterCollection'/WeatherSystem/MPC/MPC_Weather.MPC_Weather'"));
	MPC_Tree = LoadObject<UMaterialParameterCollection>(NULL, TEXT("MaterialParameterCollection'/WeatherSystem/MPC/MPC_Tree_Wind.MPC_Tree_Wind'"));

	// Color Defaults
	SnowColorOfDay = FLinearColor(0.5f, 0.65f, 1.0f, 1.0f);
	SnowColorOfNight = FLinearColor(0.25f, 0.325f, 0.5f, 1.0f);
	DarkClouds = FLinearColor(0.035f, 0.0395f, 0.05f, 1.0f);
	RainColorOfDay = SnowColorOfDay;
	RainColorOfNight = SnowColorOfNight;
}

