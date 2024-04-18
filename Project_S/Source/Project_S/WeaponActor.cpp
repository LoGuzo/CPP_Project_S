#include "WeaponActor.h"
#include "C_ItemComponent.h"

// Sets default values
AWeaponActor::AWeaponActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	ItemCom = CreateDefaultSubobject<UC_ItemComponent>(TEXT("ITEMCOM"));

}
