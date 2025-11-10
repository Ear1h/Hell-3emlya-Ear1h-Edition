# **NOTICE!**

Since this is purely an experimental port, I was mainly testing some exclusive features here.
In the future, everything will be brought in line with the common standards of Boom, MBF, MBF21, and so on.

# MAPPING

## Action Specials

| ID | Action Special | Type | Description |
|----|----------------|------|-------------|
| 256| Scrool Left (Fast)| After Start Map| The wall scrolls to the left at triple speed|
| 257| Scrool Right| After Start Map| The wall scrolls to the right|
| 258| Scrool Right (Fast)| After Start Map| The wall scrolls to the right at triple speed|
| 259| Scrool Down| After Start Map| The wall scrolls to the down|
| 260| Scrool Down (Fast)| After Start Map| The wall scrolls to the down at triple speed|
| 261| Scrool Up| After Start Map| The wall scrolls to the up|
| 262| Scrool Up (Fast)| After Start Map| The wall scrolls to the up at triple speed|
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
| 310 | Transfer Sky | After Start Map | A sector with the specified tag changes the sky texture, taken from **uppertexture** (like in _MBF_).|
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


