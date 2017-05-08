# Battleship-Project2017

Constructs a single player battleship game against a CPU on a 10x10 grid.
Each player has 1 Carrier (size 5), 1 Battleship (size 4), 1 Cruisers (size 3), 1 Submarine (size 3), and 1 Destroyers (size 2).
As each player tries to take out their opponent, the board response will tell them if they got a hit or miss, and if a ship has been sunk.
The first player to take out all of their opponent's ships is the winner.

Currently the master branch is up to date. The CPU does not bug out now, but if there is a situation where it finds multiple ships, it will go after the most recent ship until it sinks, and then forget to go after the ships it found earlier. The computer's ships are currently visible to the player, for troubleshooting purposes, but can be removed by disabling the funtion. I also removed _checkLater, to smooth out troubleshooting, and did not add it back in, so the computer will continue to pick locations at random after misses. Currently, the game does not stop when one person wins, even with the win condition in.

