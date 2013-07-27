turmite-simulator
=================

Simulates turmites on a torus. See [https://en.wikipedia.org/wiki/Turmite](https://en.wikipedia.org/wiki/Turmite).

Uses the [SFML](http://sfml-dev.org/) library.

Features
--------
- executable accepts command-line parameters:
  1. name of the turmite ruleset (currently supporting the turmites listed [below](#included-turmites))
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
