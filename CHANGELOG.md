# 07.08.2025
# Implemented four new items:
* **Armor Shard**: Grants `10% armor`. Functionally identical to the vanilla *Armor Bonus*.
* **Medipack**: Restores `50% health`.
* **Heavy Armor**: Absorbs `80% damage`. Grants `300% armor` upon pickup.
* **Vitality Serum**: Increases max health by `50%` when used. Effect resets on `New Game` or `idclev##`.

# Bugfixes and internal improvements:
* Fixed *medkit behavior*: When player HP is low, a message now appears indicating the medkit is urgently needed. Medipack shares the same behavior.
* Reworked `P_GiveBody` in `p_inter.c`: Now uses `VitaHealth` instead of hardcoded `MAXHEALTH` (*#define MAXHEALTH 100*).
* Added new variables in d_player.h:
  * `int VitaHealth`
  * `bool Vitally`
* Visplane overflow handler updated: Now throws I_Error("R_FindPlane: MAPPER - GANDON"); in `R_Plane.c`.
* New states and actors added to `info.c` and `info.h`: Implemented as additions rather than replacements.
* Fixed Vitality Serum bug: Player can now heal normally without needing to re-pick up the stimpack, medkit, medpack.
