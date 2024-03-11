# Simulate-Drop-Without-MemoryLeak
## Description
The `do_drop` command is an ACMD (Action Command) in a game server implementation responsible for simulating item drops from a specified mob to a character. This command is commonly used for testing purposes to evaluate drop rates and item distribution in the game.

## Usage
The `do_drop` command takes two parameters:
1. `mob vnum`: The virtual number (vnum) of the mob from which drops will be simulated.
2. `count`: The number of times to execute the drop simulation.

## Functionality
The command simulates item drops from the specified mob (`mob vnum`) a certain number of times (`count`). It then records the simulated drops and provides feedback to the user.

## Implementation Details
- Parses input arguments to extract the mob vnum and count.
- Spawns the specified mob (`pkAttacker`) at a random position on the same map as the character issuing the command.
- Iterates `loopCount` times, simulating drops each time.
- Uses the `ITEM_MANAGER::CreateDropItem` function to generate item drops from the mob.
- Records the simulated drops and accumulates the count of each dropped item.
- Provides feedback to the user indicating the number of simulated drops and the name of the mob.
- Creates item instances for each simulated drop and provides color-coded feedback based on the rarity of the dropped items.
- Destroys the temporary mob character (`pkAttacker`) and item instances after simulation.

## Error Handling
- Checks for valid input arguments and displays a syntax message if arguments are missing.
- Logs an error message if an item instance in the vector is null.

## Logging
- Records simulated item drops with the character's name.

## Notes
- This command is primarily intended for testing purposes and should not be used in a production environment.
- Ensure proper testing procedures are followed to accurately assess drop rates and item distribution in the game.
