# **NOTICE!**

Since this is purely an experimental port, I was mainly testing some exclusive features here.
In the future, everything will be brought in line with the common standards of Boom, MBF, MBF21, and so on.

# MAPPING

## Action Specials

| ID | Action Special | Type | Description |
|----|----------------|------|-------------|
| 256| Scrool Left (Fast)| After map starting| The wall scrolls to the left at triple speed|
| 257| Scrool Right| After map starting| The wall scrolls to the right|
| 258| Scrool Right (Fast)| After map starting| The wall scrolls to the right at triple speed|
| 259| Scrool Down| After Start Map| The wall scrolls to the down|
| 260| Scrool Down (Fast)| After map starting| The wall scrolls to the down at triple speed|
| 261| Scrool Up| After map starting| The wall scrolls to the up|
| 262| Scrool Up (Fast)| After map starting| The wall scrolls to the up at triple speed|
| 263 | Clear Sector Special| W1| Deletes all Special Action sectors, including SECRETS and flashing lights.|
| 264 | Clear Line Special| W1| Deletes all Special Action lines|
| 265 | Clear Sector Special| S1| Deletes all Special Action sectors, including SECRETS and flashing lights.|
| 266 | Clear Sector Special| SR| Deletes all Special Action sectors, including SECRETS and flashing lights.|
| 267 | Clear Line Special| S1| Deletes all Special Action lines|
| 268 | Clear Line Special| SR| Deletes all Special Action lines|
| 300 | Macro Start | W1 | Executes multiple macros simultaneously (see SPECDEFS below).|
| 301 | Macro Start | WR | Executes multiple macros simultaneously (see SPECDEFS below).|
| 302 | Print Text | W1 | Displays text on the screen (see SPECDEFS below).|
| 303 | Print Text | WR | Displays text on the screen (see SPECDEFS below).|
| 304 | Macro Start | S1 | Executes multiple macros simultaneously (see SPECDEFS below).|
| 305 | Macro Start | SR | Executes multiple macros simultaneously (see SPECDEFS below).|
| 306 | Print Text | S1 | Displays text on the screen (see SPECDEFS below).|
| 307 | Print Text | SR | Displays text on the screen (see SPECDEFS below).|
| 308 | Exit Level (Reset Inventory) | S1 | The player loses all inventory upon exiting the level (but does not die!).|
| 309 | Exit Level (Reset Inventory) | W1 | The player loses all inventory upon exiting the level (but does not die!).|
| 310 | Transfer Sky | After map starting | A sector with the specified tag changes the sky texture, taken from **uppertexture** (like in _MBF_).|
| 321 | Teleport | S1 | The player is teleported to a specific point.|
| 322 | Teleport | SR | The player is teleported to a specific point.|
| 323 | Floor_LowerToLowestTxTy | S1 | The floor lowers and changes the adjacent texture (removing effects).|
| 324 | Floor_LowerToLowestTxTy | SR | The floor lowers and changes the adjacent texture (removing effects).|
| 330 | Floor_LowerToLowest | GR | The floor lowers all the way to the lowest floor level.|

## Generalized Sector Types

| Value | Description          
|-------|--------------
| 32 | Damage Player (5 hp) (from Boom).
| 64 | Damage Player (10 hp) (from Boom).
| 96 | Damage Player (20 hp) (from Boom).
| 128  | Secret (Boom)
| 256  | Silent Monsters (Silences any sound emitted by an actor inside the sector) (Boom-Eternity)
| 512  | Silences doors, ceilings, and other level geometry movements (Boom (Reserve))
| 4096 | Kill Player (from MBF21).
| 4128 | Kill Player and go to Exit (from MBF21).
| 4160 | Kill Player and go to Secret Exit (from MBF21).
| 8192 | Deals damage to monsters that use the **_MF2_FLOORDAMAGE_** flag in _Dehacked_. The damage is based on the value specified in **Damage**.|

## Linedef flags

| Flag | Description           | Value
|-------|-----------------------|------
|ML_BLOCKPLAYERS | Block players (MBF21 flag). | 512
|ML_BLOCKLANDMONSTERS | Block Land Monsters (without MT_FLOAT, like cacos, pain elemental). (from MBF21). | 0x400
|ML_BLOCKSCAN | Block hitscan and BFG9000 tracers (from ZDoom). | 0x800
|ML_BLOCKPROJECTILE | Block projectiles (from ZDoom). | 0x1000
|ML_BLOCKSIGHT | Block thing sight	 (from ZDoom). | 0x2000

## Map Object Flags

Should be exposed to the map editor like the `AMBUSH` flags.

| Bit | Value  | Flags | Description |
|---------|--------|-------------| -------------|
| 6   | 0x0040 | `NIGHTMARE`  | Configures the **NIGHTMARE** skill. Note: For this flag to work, set **NightmareFilter = 1** in _DEHACKED [MISC]_. This was implemented for compatibility with both IWADs and custom WADs.
| 8-11  | 0x100 - 0x800  | `GENERIC FLAG 1-4`| Sets Generic Flags on the actor so it fulfills a specific condition (see DEHACKED).|
| 12   | 0x1000  | `No COUNTKILL`| Removes COUNTKILL from the actor. | 

# MODDING

During development, several internal actors were removed. Most of them were moved to **DEHEXTRA**. To see the list of removed enemies in the port, check CALAM1TY.
The new actors are linked to new items and ways to modify them. You can now edit the health values of medkits or berserks.

Full DehExtra support has been implemented. This Dehacked format allows adding new actors (up to 100), states (around 3,000), and sounds. See DehExtra on Doom Wiki!

| Index          | DoomEdNum | Name                               | Description                                                                                                                                                                                                                                                                                             |
|----------------|-----------|------------------------------------|-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| 137 | 4000     | `MT_MEDIPACK` - "Medipack" | `Width = 20`<br>`Height = 16`<br>`Mass = 100`<br><br>An enhanced version of the medkit that restores **50 HP** by default. |
| 138 | 4001     | `MT_HEAVYARMOR` - "Heavy Armor" | `Width = 20`<br>`Height = 16`<br>`Mass = 100`<br><br>An enhanced version of the blue armor. Provides **80%** damage protection. |
| 139 | 4002     | `MT_VITALLYSERUM` - "Vitality Serum" | `Width = 20`<br>`Height = 16`<br>`Mass = 100`<br><br>Increases the player’s maximum health, allowing medkits to restore up to that value. Default: 150. |
| 140 | 4003     | `MT_ARMORSHARD` - "Armor Shard" | `Width = 20`<br>`Height = 16`<br>`Mass = 100`<br><br>Grants 10% armor. Functionally identical to the vanilla Armor Bonus. |
| 141 | 4004     | `MT_REGENERATION` - "Regeneration" | `Width = 20`<br>`Height = 16`<br>`Mass = 100`<br><br>Upon pickup, the player gains 5 HP per second for the duration of the effect. The effect lasts exactly 20 seconds. |

The `[MISC]` block of `DEHACKED` lumps has been extended with the following keys. Fields not provided within the block will not be changed.

## Stimpack Health
* Add `Stimpack Health = A` in the `[MISC]` block.
* `A` is a nonnegative integer.
* Amount of `health` restored by a *Stimpack*
* Defaults: 10.

## Medikit Health
* Add `Medikit Health = A` in the `[MISC]` block.
* `A` is a nonnegative integer.
* Amount of `health` restored by a *Medikit*
* Defaults: 25.

## Medipack Health
* Add `Medipack Health = A` in the `[MISC]` block.
* `A` is a nonnegative integer.
* Amount of `health` restored by a *Medipack*
* Defaults: 50.

## Health Bonus Count
* Add `Health Bonus Count = A` in the `[MISC]` block.
* `A` is a nonnegative integer.
* Amount of `health` restored by a *Health Bonus*
* Defaults: 1.

## Armor Bonus Count
* Add `Armor Bonus Count = A` in the `[MISC]` block.
* `A` is a nonnegative integer.
* Amount of `armor` granted by an *Armor Bonus*
* Defaults: 1.

## Regeneration Health
* Add `Regeneration Health = A` in the `[MISC]` block.
* `A` is a nonnegative integer.
* Amount of `health` restored per second during *Regeneration*
* Defaults: 4.

## Vitality Health
* Add `Vitality Health = A` in the `[MISC]` block.
* `A` is a nonnegative integer.
* Maximum player `health` after picking up *Vitality Serum*
* Defaults: 150.

## Heavy Armor Class
* Add `Heavy Armor Class = A` in the `[MISC]` block.
* `A` is a nonnegative integer.
*  `Armor class` value granted by *Heavy Armor*
* Defaults: 3.

## Armor Shard Count
* Add `Armor Shard Count = A` in the `[MISC]` block.
* `A` is a nonnegative integer.
* Amount of `armor` granted by an *Armor Shard*
* Defaults: 10.

## Nightmare Filter
* Add `Nightmare Filter = A` in the `[MISC]` block.
* `A` is a nonnegative integer.
* Includes `Nightmare` skill filtering for compatibility.  
* Defaults: 0.

