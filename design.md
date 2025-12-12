## Goals
- [x] Land on theme
- [x] Plan our mechanics
- [ ] Get core setup code in place + git repo

# Concepts: Cat Invaders

## Technical
- multi-threading for game state | renderer
- basic collision detection
- a base level of animation for models
  - disable AA for textures globally
- dynamic creation / deletion of entities
- game menus / settings menus / ...
- utilize vWin from SDL
- create web build => WebGL (deploy to website)
- save to disc

## Theme
- 16/32 bit graphics
- setting
  - right-side & top border tree for cats to fall from
  - grass / ground texture below
    - parallax style hills in the distance
  - skybox using procedural stars / rain / ...
- visual / graphical theme
  - cats: 3-5 cat models - color variants (main body / spots: perlin noise spots), flip, rotate, animate
  - player controls a cardboard box: idle / movement animations, responsive "catch", align for dropping "into" the box
  - negative catch: limb? bug?
- color palette
  - game entities: bright / vibrant
  - environment: darker / low saturation

## Game Loop
- catch cats
  - gain points when catching a cat
- "lives" system
  - lose a life when catching <negative_catch>
  - lose a life when failing to catch a cat
- increase fall speed / spawn rate based on time
  - tweak bad : good spawn rates

## Gameplay Mechanics
- top-down
- 2d plane for movement
- auto-run / move forward
- single player game
- shoot weapon in line, hit / no hit on enemy
