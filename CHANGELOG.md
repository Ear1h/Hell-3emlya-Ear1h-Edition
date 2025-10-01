# 07.08.2025
# Implemented four new items:
* **Armor Shard**: Grants `10% armor`. Functionally identical to the vanilla *Armor Bonus*.
* **Medipack**: Restores `50% health`.
* **Heavy Armor**: Absorbs `80% damage`. Grants `300% armor` upon pickup.
* **Vitality Serum**: Increases `max health` by `50%` when used. Effect resets on `New Game` or `idclev##`.

# Bugfixes and internal improvements:
* Fixed *medkit behavior*: When player HP is low, a message now appears indicating the medkit is urgently needed. Medipack shares the same behavior.
* Reworked `P_GiveBody` in `p_inter.c`: Now uses `VitaHealth` instead of hardcoded `MAXHEALTH` (*#define MAXHEALTH 100*).
* Added new variables in `d_player.h`:
  * `int VitaHealth`
  * `bool Vitally`
* Visplane overflow handler updated: Now throws I_Error("R_FindPlane: MAPPER - GANDON"); in `R_Plane.c`.
* New states and actors added to `info.c` and `info.h`: Implemented as additions rather than replacements.
* Fixed Vitality Serum bug: Player can now heal normally without needing to re-pick up the stimpack, medkit, medpack.

# 08.08.2025

* Implemented new powerup: `REGENERATION`. Upon pickup, the player gains `4 HP per second` for the duration of the effect. The effect lasts exactly `25 seconds`.
* New sector special types added:
  * `Kill player` (type 18)
  * `Kill player and Exit Level` (type 19)
  * `Kill player and Secret Exit Level` (type 20)
* Added `MF_COUNTITEM` flag to `Armor Shard` and `Vitality Serum`.

# 10.08.2025
* Added new `gameversion 2.0` to maintain demo compatibility with previous versions:
  * New items now function only in this version; otherwise, nothing happens.
  * New special actions do not work in older versions.
  * New Dehacked parameters are only available in version `2.0` (details below).

* `Dehacked` improvements:
  * Added **string mnemonics** for `pickup messages` of new items.
  * You can now edit the following properties:
    * `Stimpack Health` – Amount of `health` restored by a *Stimpack* (default: `10`).
    * `Medikit Health` – Amount of `health` restored by a *Medikit* (default: `25`).
    * `Medipack Health` – Amount of `health` restored by a *Medipack* (default: `50`).
    * `Health Bonus Count` – Amount of `health` restored by a *Health Bonus* (default: `1`).
    * `Armor Bonus Count` – Amount of `armor` granted by an *Armor Bonus* (default: `1`).
    * `Armor Shard Count` – Amount of `armor` granted by an *Armor Shard* (default: `10`).
    * `Heavy Armor Class` – `Armor class` value granted by *Heavy Armor* (default: `3`).
    * `Regeneration Health` – Amount of `health` restored per second during *Regeneration* (default: `5`).
    * `Vitality Health` – Maximum player `health` after picking up *Vitality Serum* (default: `150`).

* Bugfix:
  * Fixed an issue where regeneration could heal a dead player. Regeneration now works only if the player’s `HP` is above `0%`.

# 11.08.2025
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

# 15.08.2025
# New THINGS Flag
* Added a new difficulty filter: `Nightmare` (`MTF_NIGHTMARE = 32`). You can now configure monsters to be excluded from **Nightmare** mode, or to appear only in it.

# New LINEDEFS Flag
* New Linedef flags include both `MBF21` features and new mechanics such as hitscan blocking, projectile blocking, and monster sight blocking.
* All flags can be combined to create an impassable line that blocks everything (except sound — for that, you’ll still need additional lines).

| Flag | Description           | Value
|-------|-----------------------|------
|ML_BLOCKPLAYERS | Block players (MBF21 flag). | 512
|ML_BLOCKLANDMONSTERS | Block Land Monsters (without MT_FLOAT, like cacos, pain elemental). (from MBF21). | 0x400
|ML_BLOCKSCAN | Block hitscan and BFG9000 tracers (from ZDoom). | 0x800
|ML_BLOCKPROJECTILE | Block projectiles (from ZDoom). | 0x1000
|ML_BLOCKSIGHT | Block thing sight	 (from ZDoom). | 0x2000

# Sector Special changes

* Introduced Boom sector specials along with new flags.
* Both features were presumably reserved by *Team TNT* for future development but never made it into a release. `MBF2y` will implement this feature in the near future.

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

* Bugfixes:
  * **Vitality Serum** now works correctly (previously non-functional due to `gameversion > exe_doom_2_0`).
  * Fixed an issue where picking up **Vitality Serum** with more than `150 HP` would reset health to the default value (150).

# 16.08.25

* Added new actors:
  * **Nightmare Imp**: Spawns only in Nightmare mode. Functions like the regular Imp in Nightmare, but with reduced pain chance and higher health.
  * **Nightmare Demon**: Spawns only in Nightmare mode. Functions like the regular Demon in Nightmare.
  * **Nightmare Projectile**: Moves at the same speed as the Imp’s projectile in Nightmare mode.

* Bug fixes:
  * Fixed a logic error preventing the player from gaining health from `medkits`.
  * Fixed an issue where the player could exceed `100` health without picking up `Vitality Serum`.
  * Fixed an issue where an object with the `AMBUSH` flag would spawn on the map in Nightmare mode (without the `Nightmare` flag).

# 20.08.25

* Added new actors:
  * **Dark Imp**: An enhanced version of the `Doom Imp`. Throws a slow projectile, but with a chance to home in on the player. The projectile accelerates in Nightmare skill.
  * **Dark Imp Ball**: Dark Imp projectile.
  * **Dark Imp Ball Smoke**: Smoke is now transparent.
  * **Kamikaze**: Its sole purpose is to get close to the player and explode.

* Added new codepointers:
  * `A_KamikazeSee`: Play `dskami` sound
  * `A_DarkImpAttack`: Shoot Dark Imp Ball

* Added new linedef special:
  * New wall scrollers added in multiple directions (up, down, left, right), with both normal and 3× speed variants. (256-262). Affects the limit (64 in vanilla).

# 22.08.25

* Added new linedef special:

| Value | Description          
|-------|--------------
| 263 | W1 Clear Sector Special
| 264 | W1 Clear Linedef Special

* When entering a secret area, a corresponding message and a new sound are played.
* Fixed a bug where `T_FireFlicker` would stop working after loading a save.

# 08.09.25

### New Features  
- **ALTFIRE mechanic** added: every available weapon now supports an alternate fire (currently only for the pistol).  
- **DeHackEd modding support**: you can now edit `altfire` and `altfireflash`.  

⚠️ Works only with **version 2.0**.  

# Bug fixes
- Removed the `dssecret` sound.
- Fixed a bug where `A_ReFire` behaved incorrectly when both `BT_ATTACK` and `BT_ALTFIRE` were held down simultaneously.
- Fixed an issue where some `A_FireShotgun` states failed to display the `flashstate` on-screen.

# 15.09.25

### New Sector Flag

| Value | Description          
|-------|--------------
| 8192 | If this flag is enabled, any actor (except the Voodoo Doll) will take damage (if damage flags are set).|

### New actor flag

| Flag | Description           | Value
|-------|-----------------------|------
|MF2_FLOORPROTECTOR | Protects the actor from damage floors.| 512

### Quality of Life

* This port now displays statistics (**KILLS, ITEMS, SECRETS**) in the HUD.
* When the player enters a secret, a separate message is displayed in the center of the screen indicating the secret has been found.

### Fixes

* `Clear Sector Special` now removes the secret from the level.
* Fixed an issue where the player couldn't fire after switching weapons.

# 18.09.25

### Technical
- Implemented **BEX_ptr** support for adding new codepointers directly from **BOOM**.

### New Actions
- Added `A_PlaySound2(sfx_id)`: actor plays an existing sound.  
- Added `A_LineEffect2(spec, tag)`: actor remotely activates a special action.  
- Added `A_RadiusDamage(damage, dist)`: configurable explosion radius and damage.  

### Removed
- Removed `A_KamikazeSee` in favor of `A_PlaySound2`.

### Bugfixes

- Fixed a bug where pressing weapon slots could trigger a shot from the alternate weapon.  
- Fixed a crash when the `D_E4M#` lump was missing.  

# 21.09.25

### Enhancements
- Increased number of states to **4000** (DehExtra).  
- Added new codepointers:  

#### `A_ReFireTo(state states, bool CheckAmmo)` (from MBF21)  
- Switches to the next state when the player holds the fire (or alt-fire) button.  
- If `CheckAmmo` is true and there isn’t enough ammo, the weapon switches to another state.  

#### `A_CheckAmmo(state states, uint ammo)` (adapted from MBF21)  
- Checks the amount of ammo.  
- If there isn’t enough, the weapon switches to another state.  

#### `A_CustomWeaponBulletAttack(fixed hspread, fixed vspread, int bullets, int damage, int damage_mod, int sound, int ammo)`  
- Similar to the MBF21 codepointer.  
- `hspread` and `vspread` control bullet spread.  
- `bullets` = number of projectiles fired.  
- `damage` = base damage.  
- `damage_mod` = random damage modifier.  
- `sound` = firing sound.  
- `ammo` = amount of ammo consumed per shot.

#### `A_WeaponCustomMissileAttack(int type, int ammo)`  
- A simplified version of `A_WeaponProjectile`.  
- Spawns the specified projectile and consumes the given amount of ammo.  

#### `A_CustomMeleeAttack(int damage, int damage_mod, fixed zerkfactor, fixed range)`  
- Player performs a melee attack based on damage and range.  
- `zerkfactor` controls the berserk damage multiplier (editable).  

#### `A_JumpIfCounterEqual(uint CounterType, byte CounterCount, state id)`  
- Switches to another state if the selected counter matches the value specified in the arguments.  

#### `A_DecreaseCounter(uint CounterType, byte CounterCount)`  
- Decreases the specified counter by the given amount.  

#### `A_IncreaseCounter(uint CounterType, byte CounterCount)`  
- Increases the specified counter by the given amount.  

---

### New Actor Properties  
- **Counter1–4**  

The counter system is a simplified version of `A_JumpIfInventory` from DECORATE or `if (i > 0)` from ZScript.  
It allows an actor to switch to a desired state without wasting extra frames idling.  

# 01.10.25

### New Lump: `SPECDEFS`

This lump allows defining **macros** for linedefs so that a single line can trigger multiple actions at once.  
The lump uses **JSON** syntax.

#### Example Syntax

```json
"macro": [
  {
    "id": 1,
    "specials": [
      { "action": 101, "tag": 19 },
      { "action": 306, "tag": 1 },
      { "action": 268, "tag": 2 }
    ]
  }
]
```
* action → specifies the linedef special (only S1/SR are supported; W1/WR and G1/GR do not work).
* tag → parameter required for the action (can represent sector tag, text ID, etc.).
* The number of macros is unlimited.

#### Message Definitions

SPECDEFS also allows defining messages that can be displayed in chat when a given linedef is triggered.

```json
"message": [
  {
    "id": 1,
    "text": "Exit opened on train's right side."
  }
]
```
* id → linedef tag.
* text[80] → message string (max length = 80).
* If text length exceeds 80, the game will intentionally crash during initialization.

### Added New Codepointers

- **A_Jump(random, state1, state2, state3, state4)**  
  Jumps to a random state.  
  - If `state2–4` are set to `0`, they are treated as `state1`.

- **A_ResetHealth()**  
  Resets actor health to the default value defined in `info->health`.

- **A_SetSelfHealth(int health)**  
  Increases actor’s health by the given `health` amount.

- **A_JumpIfSetFlags(int flags, int flags2, int genericflags, state)**  
  Jumps to the specified state if one or more of the given flags are set.

- **A_Die()**  
  Instantly kills the actor.

- **A_SetSpeed(int speed)**  
  Sets the actor’s movement speed.

- **A_NoiseAlert()**  
  Alerts all nearby monsters and directs them to the actor’s target.

- **A_JumpIfSkill(skill skill, int state, bool IsHigher)**  
  Jumps to the specified state depending on current game skill.  
  - If `IsHigher = false`: checks for **exact skill match**.  
  - If `IsHigher = true`: condition passes if current skill is **greater or equal** than the given skill.
 
 ### New Map Flags

- **GENERIC1 – GENERIC4**  
  Utility flags that allow customizing monsters and actors **without creating duplicate “trash actors”**.  
  Can be used to enable conditional behavior or script-like effects.

 ### New ACtor Flags
- **MF4_GENERIC1 – MF4_GENERIC4**  
  Actor-side equivalents of the above `GENERIC` flags.  

- **MF2_NORANDOM**  
  Projectiles with this flag deal **non-randomized damage** (fixed value, no Doom RNG spread).  

- **MF2_STAY**  
  Actors with this flag:  
  - Remain in place (immobile).  
  - Do not trigger secondary effects such as chasing or wandering.  

### New Actor: **Ceiling Turret**

- Always spawns **attached to the ceiling**.  
- No collision box (actors can pass through), but **still vulnerable to damage**.  
- Weapon behavior:  
  - Fires **two-round bursts** in sequence.  
