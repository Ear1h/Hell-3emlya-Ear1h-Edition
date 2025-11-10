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
| 259| Scrool Down| After map starting| The wall scrolls to the down|
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

# New Thing Flags 
* Add `Ear1h27 Bits = X` in the Thing definition.
* The format is the same as the existing Bits field.
* Example: `Ear1h27 Bits = NODAMAGE+ANTITELEFRAG`.
* The value can also be given as a number (sum of the individual flag values below).

| Flag | Description           | Value
|-------|-----------------------|------
|MF2_NORESPAWN | Enemies do not respawn on `Nightmare` difficulty or with the `-respawn` parameter (from ID24). | 1
|MF2_FULLVOLSOUNDS | Full volume see / death sound & splash immunity (from MBF21). | 2
|MF2_NORADIUSDMG | Doesn't take splash damage (cyberdemon, mastermind) (from MBF21). | 4
|MF2_ACTIVATOR | Thing can activate most player-activated linedefs as though it were a voodoo doll. (from MBF2y). | 8
|MF2_NODAMAGE | Thing does not lose health when taking damage.	 (from MBF2y). | 16
|MF2_NOCRUSH | If Thing is a `CORPSE`, it does not turn into gibs when crushed. If Thing is `DROPPED`, it does not disappear when crushed. (Thing will still take damage from crushers.) (from MBF2y). | 32
|MF2_MONSTERPASS | Thing passes through monster-blocking lines, without being a friend, projectile or a player. (from Eternity). | 64
|MF2_SPAWNONLYNIGHTMARE | Enemies spawn only on Nightmare difficulty. | 128
|MF2_ANTITELEFRAG | Things that would telefrag this thing are telefragged instead. (from MBF2y). | 256
|MF2_FLOORDAMAGE| With this flag, all actors take damage from damaging sectors.| 512
|MF2_NORANDOM| Random damage from projectiles is disabled | 0x400
|MF2_STAY| The actor always stays in its position | 0x800
|MF2_DONTFALL| The actor does not fall after death | 0x1000
|MF2_RIP| Projectiles pass through the actor | 0x2000
|MF2_NIGHTMAREMOBJ| The actor is now a Nightmare monster and will respawn | 0x4000
|MF2_FLOORHUGGER| Projectiles do not die upon contact with the floor | 0x8000
|MF2_DMGIGNORED| Actors that take damage from another actor ignore it, as with the Arch-Vile | 0x10000

## GENERIC FLAGS
* Add `Generic = X` in the Thing definition.
* The format is the same as the existing Bits field.
* Example: `Generic = MF4_GENERIC1+MF4_GENERIC3`.
* The value can also be given as a number (sum of the individual flag values below).

| Flag | Description           | Value
|-------|-----------------------|------
| MF4_GENERIC1  | Sets Generic Flag 1 on the actor so it fulfills a specific condition from Doom Builder.| 1| 
| MF4_GENERIC2  | Sets Generic Flag 2 on the actor so it fulfills a specific condition from Doom Builder.| 2| 
| MF4_GENERIC3  | Sets Generic Flag 3 on the actor so it fulfills a specific condition from Doom Builder.| 4| 
| MF4_GENERIC4  | Sets Generic Flag 4 on the actor so it fulfills a specific condition from Doom Builder.| 8| 

### Counters
Things now have instanced global counters that can be manipulated and checked via codepointers. The following mobj properties have been added to facilitate this:

| Property Name | Description                                                              | Default Value                         | Minimum Value | Maximum Value                   |
|---------------|--------------------------------------------------------------------------|---------------------------------------|---------------|---------------------------------
| `counter1`    | The current value of the Thing's first internal counter.                 | 0 / Thing's `Counter 1 initial` value | 0             | 255 |
| `counter2`    | The current value of the Thing's second internal counter.                | 0 / Thing's `Counter 2 initial` value | 0             | 255 |
| `counter3`    | The current value of the Thing's third internal counter.                 | 0 / Thing's `Counter 3 initial` value | 0             | 255 |
| `counter4`    | The current value of the Thing's fourth internal counter.                | 0 / Thing's `Counter 4 initial` value | 0             | 255 |

#### Fast speed
- Sets the thing speed for skill 5 / -fast.
- Add `Fast speed = X` in the Thing definition.
- `X` has the same units as the normal `Speed` field.

#### Dropped Item
- The thing ID to spawn on death.
- Add `droppeditem = X` in the Thing definition.

#### Nightmare Reaction
- Configurable reaction level in Nightmare mode (default: 0).
- Add `NightmareReaction = X` in the Thing definition.

#### New "Args" fields for DEHACKED states (from MBF21)
- Defines 8 new integer fields in the state table for use as codepointer arguments
- Args are defined in dehacked by adding `Args1 = X`, `Args2 = X`... up to `Args8 = X` in the State definition.
- Default value for each arg is determined by the frame's codepointer. For ease of implementation, DEHACKED tools may wish to simply pass through any args that are explicitly set by the user (i.e. assume the default value is undefined).

##### Actor pointers

- **A_LineEffect2(special, tag)**
  - Performs the action of the args[0] linedef type, on tag args[1].
  - Args:
    - `special (short)`: Linedef type
    - `tag (short)`: Sector Tag

- **A_PlaySound2(sound)**
  - Plays sound index args[0]
  - Args:
    - `sound (soundid)`: Sound id in sfx_id

- **A_PlaySound2(sound)**
  - Plays sound index args[0]
  - Args:
    - `sound (soundid)`: Sound id in sfx_id

- **A_RadiusDamage(damage, radius)**
  - Generic explosion.
  - Args:
    - `damage (uint)`: Max explosion damge
    - `radius (uint)`: Explosion radius, in map units

- **A_NoiseAlert**
  - Alerts monsters within sound-travel distance of the calling actor's target.
  - No Args.

- **A_JumpIfSetFlags(state, flags, flags2, genericflag)**
  - Jumps to a state if caller has the specified thing flags set.
  - Args:
    - `state (uint)`: State to jump to.
    - `flags (int)`: Standard actor flag(s) to check
    - `flags2 (int)`: ID27 actor flag(s) to check
    - `flags2 (int)`: Generic actor flag(s) to check
  - Notes:
    - If multiple flags are specified in a field, jump will only occur if all the flags are set (e.g. AND comparison, not OR)
   
- **A_AddFlags(flags, flags2)**
  - Adds the specified thing flags to the caller.
  - Args:
    - `flags (int)`: Standard actor flag(s) to add
    - `flags2 (int)`: ID27 actor flag(s) to add

- **A_RemoveFlags(flags, flags2)**
  - Removes the specified thing flags from the caller.
  - Args:
    - `flags (int)`: Standard actor flag(s) to remove
    - `flags2 (int)`: ID27 actor flag(s) to remove
   
- **A_Spawn2(type, z_ofs)**
  - Actor spawn function.
  - Args:
    - `type (uint)`: Type (dehnum) of actor to spawn
    - `z_ofs (fixed)`: Z (up/down) spawn position offset

- **A_JumpIfSkill(skill, state, isHigher, fast)**
  - Jumps to another state depending on the current skill level.
  - Args:
    - `skill (int)`: Skill level to compare (0–4)
    - `state (int)`: State to jump to if condition is met
    - `isHigher (bool)`: Jump if current skill is higher
    - `fast (bool)`: Jump only when -fast mode is active

- **A_JumpIfCounterEqual(type, counter, state)**
  - Changes the actor’s state when the internal counter reaches the specified value.
  - Args:
    - `type (int)`: Counter Type (1–4)
    - `counter (short)`: Counter value to check
    - `state (short)`: Jump if counter reaches the specified value.

- **A_DecreaseCounter(type, counter)**
  - Decreases the actor’s internal counter by the specified amount.
  - Args:
    - `type (int)`: Counter Type (1–4)
    - `counter (short)`: Decreases Counter value by amount
   
- **A_IncreaseCounter(type, counter)**
  - Increases the actor’s internal counter by the specified amount.
  - Args:
    - `type (int)`: Counter Type (1–4)
    - `counter (short)`: Increases Counter value by amount

- **A_ResetHealth**
  - Reset Health actor to default
  - No Args.

- **A_SetSelfHealth(health)**
  - Increases the actor’s health by the specified amount.
  - Args:
    - `health (int)`: Increase actor health

- **A_Die**
  - Kill the actor
  - No Args.
 
- **A_MonsterMeleeAttack(damagebase, damagedice, sound, range)**
  - Generic monster melee attack.
  - Args:
    - `damagebase (uint)`: Base damage of attack; if not set, defaults to 3
    - `damagedice (uint)`: Attack damage random multiplier; if not set, defaults to 8
    - `sound (uint)`: Sound to play if attack hits
    - `range (fixed)`: Attack range; if not set, defaults to calling actor's melee range property
  - Notes:
    - Damage formula is: `damage = (damagebase * random(1, damagedice))`
   
- **A_MonsterBulletAttack(hspread, vspread, numbullets, damagebase, damagedice)**
  - Generic monster bullet attack.
  - Args:
    - `hspread (fixed)`: Horizontal spread (degrees, in fixed point)
    - `vspread (fixed)`: Vertical spread (degrees, in fixed point)
    - `numbullets (uint)`: Number of bullets to fire; if not set, defaults to 1
    - `damagebase (uint)`: Base damage of attack; if not set, defaults to 3
    - `damagedice (uint)`: Attack damage random multiplier; if not set, defaults to 5
  - Notes:
    - Damage formula is: `damage = (damagebase * random(1, damagedice))`
   
 **A_MonsterProjectile2(type, angle)**
  - Generic monster projectile attack.
  - Args:
    - `type (uint)`: Type (dehnum) of actor to spawn
    - `angle (fixed)`: Angle (degrees), relative to calling actor's angle
   
# WEAPONS

## Weapon AltFire

* Add `AltShooting frame = X` in the Weapon definition.
* Weapons now support alternate fire.  
* `X` represents a frame number.

## Weapon AltFlash

* Add `AltFiring frame = X` in the Weapon definition.
* Weapons now support alternate flash for altfire.  
* `X` represents a frame number.

## Weapon Flags
- Add `Weapon Flags = X` in the Weapon definition.
- The format is the same as the existing thing `Bits` field.
- Example: `MBF21 Bits = SILENT+NOTHRUST`.
- The value can also be given as a number (sum of the individual flag values below).

| Name           | Value | Description                                      |
|----------------|-------|--------------------------------------------------|
| NOTHRUST       | 0x001 | Doesn't thrust things                            |
| SILENT         | 0x002 | Weapon is silent                                 |

##### Weapon pointers
- **A_RefireTo(state, noammocheck)**
  - Jumps to `state` if the fire button is currently being pressed and the weapon has enough ammo to fire.
  - Args:
    - `state (uint)`: State index to jump to.
    - `noammocheck (int)`: If nonzero, skip the ammo check.
   
- **A_WeaponCustomMissileAttack(type, ammodecrease)**
  - Generic weapon projectile attack.
  - Args:
    - `type (uint)`: Type (dehnum) of actor to spawn
    - `ammodecrease (uint)`: Consume ammo per shot
   
- **A_CustomMeleeAttack(damagebase, damagedice, zerkfactor, range)**
  - Generic weapon melee attack.
  - Args:
    - `damagebase (uint)`: Base damage of attack; if not set, defaults to 2
    - `damagedice (uint)`: Attack damage random multiplier; if not set, defaults to 10
    - `zerkfactor (fixed)`: Berserk damage multiplier; if not set, defaults to 1.0
    - `range (fixed)`: Attack range; if not set, defaults to player mobj's melee range property
   
- **A_CheckAmmo(state, amount)**
  - Jumps to `state` if ammo is below `amount`.
  - Args:
    - `state (uint)`: State index to jump to.
    - `amount (uint)`: Amount of ammo to check. If zero, will default to the current weapon's `ammopershot` value.

- **A_CustomWeaponBulletAttack(hspread, vspread, numbullets, damagebase, damagedice, sound, ammodecrease)**
  - Generic weapon bullet attack.
  - Args:
    - `hspread (fixed)`: Horizontal spread (degrees, in fixed point)
    - `vspread (fixed)`: Vertical spread (degrees, in fixed point)
    - `numbullets (uint)`: Number of bullets to fire; if not set, defaults to 1
    - `damagebase (uint)`: Base damage of attack; if not set, defaults to 5
    - `damagedice (uint)`: Attack damage random multiplier; if not set, defaults to 3
    - `sound (uint)`: Play weapon sound
    - `ammodecrease (uint)`: Consume ammo per shot
