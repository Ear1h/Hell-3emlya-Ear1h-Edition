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
