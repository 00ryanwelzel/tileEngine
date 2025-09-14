# tileEngine

## (Ryan Welzel 9/13/2025)

A lightweight tile-based rendering engine built in C++ with SDL2.
The engine is fully JSON-driven, allowing sprites, colors, transforms, and animations to be modified without recompilation.

---

Features:
Tile-Based Rendering
Render structured 2D levels defined in JSON.

JSON-Defined Sprites
Sprites are composed from layered rectangle primitives, described entirely in JSON.

Transform Chains
Color, integer, and float attributes can be animated with interpolation functions (sine, cubic, linear, etc.).

Customizable Assets
Sprites, colors, and transforms can be added or edited by changing JSON files — no code changes required.

Memory Safety
Designed with STL containers and RAII principles for resource safety and modularity.


Requirements:
- Linux OS
- GCC compiler
