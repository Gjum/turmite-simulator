turmite-simulator
=================

Simulates turmites on a torus. See <https://en.wikipedia.org/wiki/Turmite>.

Uses the [SFML](http://sfml-dev.org/) library.

Features
--------

- executable accepts command-line parameters:
  1. turmite ruleset or name (currently supporting [relative](https://en.wikipedia.org/wiki/Turmite#Relative_vs._absolute_turmites) and [listed below](#included-turmites) turmites)
  2. number of turmites to run simultaneously
  3. steps between renders, small numbers = slow

  Example: `$ ./turmites Turmite_Pulsing 100 1000` will simulate 100 turmites of the type `Turmite_Pulsing` and update the window every 1000 steps.
- color table automatically switches from black/white to multi-color

Included turmites
-----------------

- `Turmite_Biotope`: simulating competing species (default turmite)
- `Turmite_Pulsing`: alternating between creating and destroying every 10k steps
- `Turmite_Fibonacci`: building a fibonacci spiral
- `Turmite_Qrcode`: buiding a distinctive growing square pattern
- `Turmite_Foo`: buiding a chaotic distinctive pattern
- `Ant_RL`: Langton's ant, building a highway after ~10000 steps
- `Ant_RRLL`: building a growing symmetrical pattern
- `Ant_RRLRR`: building a growing square

Make your own Turmites
----------------------

From [TwoDimensionalTuringMachines](https://code.google.com/p/ruletablerepository/wiki/TwoDimensionalTuringMachines)

Run the executable with the first parameter set to the movement specification string, e.g.: `$ ./turmites {{{1,2,0},{0,8,0}}}`

Each machine is specified as a table of `n_states` rows by `n_colors` columns, written in (Western) reading order: the first row first, then then other rows.

Each triple is `{A,B,C}` where `A` is the new color to write: `[0,1,2,...,(n_colors-1)]`, `B` is the direction to turn/move (see below) or `0` to halt, `C` is the new state to adopt: `[0,1,2,...,(n_states-1)]`.

The direction is specified like this:
- `1` = forward
- `2` = right
- `4` = u-turn (180 degrees)
- `8` = left
- `0` = halt
This notation will allow turmites to split, e.g. `2+8` = `10` = turn left and right. This is not implemented yet, but will be included in a later version.

For example, the triple `{1,2,3}` means: change cell to `'1'`, turn right (and move forward), and adopt state `3`.

