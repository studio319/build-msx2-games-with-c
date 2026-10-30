# Build MSX2 Games with C — Example Source Code

**Retro Game Programming with MSXgl**

**Original Korean title: C언어로 만드는 MSX2 게임**  
**Studio 319**

[한국어](README.md) | **English** | [日本語](README.ja.md)

This repository provides the **hands-on example source code and prebuilt MSX2 ROM files** for the book *Build MSX2 Games with C* (original Korean title: 《C언어로 만드는 MSX2 게임》). The examples are listed in the order they appear in the book. You can modify and build the source code yourself or run the provided ROM files in an MSX2 emulator.

## Quick Start

1. Click **Code → Download ZIP** at the top of the repository, then extract the archive. You do not need a GitHub account to download a public repository.
2. Find the relevant section number in the **Example List** below, then open the corresponding project folder.
3. To run an example immediately, open the `.rom` file in its `out` directory with an MSX2 emulator such as openMSX.
4. To build an example yourself, first set up **MSXgl, SDCC, and the other development tools** as described in Chapter 2 of the book. On Windows, run `build.bat` from the example's directory.

### Files in a Typical Project

```text
ch03/5/draw_point/
├── template.c        # C source code
├── project_config.js # Build configuration
├── msxgl_config.h    # MSXgl configuration
├── build.bat         # Windows build script
├── build.sh          # Shell build script
├── out/
│   └── template.rom  # Built ROM file
└── emul/
    └── rom/
        └── template.rom  # Emulator ROM copy
```

> File layouts vary depending on the stage of development. In Chapters 4 and 5, some projects split functionality into files such as `block_data.c`, `board.c`, `player.c`, and `enemy.c`. Most ROMs built in Chapter 5 are named `vertical_shooter.rom`.

## Example List

**The tables follow the learning sequence in the book, not GitHub's alphabetical folder order.** When a section contains multiple examples, follow the step numbers in order. Each link opens the corresponding project folder or ROM file.

### Chapter 3 · MSX2 Programming Fundamentals

| Book Section | Step | Example Folder | ROM |
|---|:---:|---|---|
| 3-5 Drawing in SCREEN 5 | 1 | [`draw_point`](ch03/5/draw_point/) — Drawing a point | [ROM](ch03/5/draw_point/out/template.rom) |
| ↳ Same section | 2 | [`draw_line`](ch03/5/draw_line/) — Drawing a line | [ROM](ch03/5/draw_line/out/template.rom) |
| ↳ Same section | 3 | [`draw_box`](ch03/5/draw_box/) — Drawing a rectangle | [ROM](ch03/5/draw_box/out/template.rom) |
| ↳ Same section | 4 | [`draw_fillbox`](ch03/5/draw_fillbox/) — Drawing a filled rectangle | [ROM](ch03/5/draw_fillbox/out/template.rom) |
| ↳ Same section | 5 | [`draw_circle`](ch03/5/draw_circle/) — Drawing a circle | [ROM](ch03/5/draw_circle/out/template.rom) |
| ↳ Same section | 6 | [`draw_example`](ch03/5/draw_example/) — Combining basic shapes | [ROM](ch03/5/draw_example/out/template.rom) |
| 3-6 Keyboard and Joystick Input | 1 | [`keyboard_input`](ch03/6/keyboard_input/) — Reading keyboard input | [ROM](ch03/6/keyboard_input/out/template.rom) |
| 3-7 Game Loops and Moving Objects | 1 | [`move_box`](ch03/7/move_box/) — Moving a rectangle | [ROM](ch03/7/move_box/out/template.rom) |
| ↳ Same section | 2 | [`move_box2`](ch03/7/move_box2/) — Erasing the trail of a moving rectangle | [ROM](ch03/7/move_box2/out/template.rom) |
| ↳ Same section | 3 | [`move_box3`](ch03/7/move_box3/) — Keeping movement within screen boundaries | [ROM](ch03/7/move_box3/out/template.rom) |
| 3-8 Sprites | 1 | [`sprite`](ch03/8/sprite/) — Displaying a sprite | [ROM](ch03/8/sprite/out/template.rom) |
| ↳ Same section | 2 | [`move_sprite`](ch03/8/move_sprite/) — Moving a sprite | [ROM](ch03/8/move_sprite/out/template.rom) |
| ↳ Same section | 3 | [`move_sprite2`](ch03/8/move_sprite2/) — Moving a sprite over a background | [ROM](ch03/8/move_sprite2/out/template.rom) |
| 3-9 Producing Sound with the PSG | 1 | [`psg`](ch03/9/psg/) — Playing PSG tones | [ROM](ch03/9/psg/out/template.rom) |
| ↳ Same section | 2 | [`noise`](ch03/9/noise/) — Playing PSG noise | [ROM](ch03/9/noise/out/template.rom) |
| ↳ Same section | 3 | [`music`](ch03/9/music/) — Playing a melody | [ROM](ch03/9/music/out/template.rom) |
| 3-10 Managing Data with Arrays | 1 | [`music_array`](ch03/10/music_array/) — Managing a melody with an array | [ROM](ch03/10/music_array/out/template.rom) |
| ↳ Same section | 2 | [`music_array2`](ch03/10/music_array2/) — Managing a melody with a two-dimensional array | [ROM](ch03/10/music_array2/out/template.rom) |
| 3-11 Grouping Data with Structures | 1 | [`move_sprite3`](ch03/11/move_sprite3/) — Moving a sprite using a structure | [ROM](ch03/11/move_sprite3/out/template.rom) |

### Chapter 4 · Building a Falling-Block Puzzle Game

| Book Section | Step | Example Folder | ROM |
|---|:---:|---|---|
| 4-2 Creating a 10×20 Game Board | 1 | [`gameboard`](ch04/2/gameboard/) — Creating a 10×20 game board | [ROM](ch04/2/gameboard/out/template.rom) |
| 4-3 Representing Block Shapes as Data | 1 | [`draw_block`](ch04/3/draw_block/) — Defining and drawing block shapes | [ROM](ch04/3/draw_block/out/template.rom) |
| 4-4 Moving Blocks Left and Right | 1 | [`move_block`](ch04/4/move_block/) — Moving a block left and right | [ROM](ch04/4/move_block/out/template.rom) |
| 4-5 Making Blocks Fall Automatically | 1 | [`fall_block`](ch04/5/fall_block/) — Making a block fall automatically | [ROM](ch04/5/fall_block/out/template.rom) |
| 4-6 Locking Blocks and Spawning the Next One | 1 | [`stack_blocks`](ch04/6/stack_blocks/) — Locking blocks and spawning new ones | [ROM](ch04/6/stack_blocks/out/template.rom) |
| 4-7 Creating Different Block Shapes | 1 | [`multiple_shapes`](ch04/7/multiple_shapes/) — Using multiple block shapes | [ROM](ch04/7/multiple_shapes/out/template.rom) |
| ↳ Same section | 2 | [`random_shapes`](ch04/7/random_shapes/) — Selecting random block shapes | [ROM](ch04/7/random_shapes/out/template.rom) |
| 4-8 Rotating Blocks | 1 | [`rotate_shapes`](ch04/8/rotate_shapes/) — Rotating blocks | [ROM](ch04/8/rotate_shapes/out/template.rom) |
| 4-9 Clearing Completed Lines | 1 | [`clear_lines`](ch04/9/clear_lines/) — Clearing completed lines | [ROM](ch04/9/clear_lines/out/template.rom) |
| 4-10 Handling Game Over | 1 | [`gameover`](ch04/10/gameover/) — Handling game over | [ROM](ch04/10/gameover/out/template.rom) |
| 4-11 Moving Blocks Down with the Down Arrow Key | 1 | [`keyboard_drop`](ch04/11/keyboard_drop/) — Handling the Down Arrow key | [ROM](ch04/11/keyboard_drop/out/template.rom) |
| 4-12 Adding Difficulty Levels | 1 | [`level_up`](ch04/12/level_up/) — Implementing levels and fall speed | [ROM](ch04/12/level_up/out/template.rom) |
| 4-13 Adding a Simple UI | 1 | [`ui`](ch04/13/ui/) — Displaying score, level, and other UI elements | [ROM](ch04/13/ui/out/template.rom) |
| 4-14 Refactoring the Source Code | 1 | [`code_refactoring`](ch04/14/code_refactoring/) — Separating and organizing source files | [ROM](ch04/14/code_refactoring/out/template.rom) |
| 4-15 Adding Sound Effects | 1 | [`sfx`](ch04/15/sfx/) — Adding sound effects | [ROM](ch04/15/sfx/out/template.rom) |
| 4-16 Polishing and Completing the Game | 1 | [`falling_blocks`](ch04/16/falling_blocks/) — Completed falling-block puzzle game | [ROM](ch04/16/falling_blocks/out/template.rom) |

### Chapter 5 · Building a Vertical-Scrolling Shooter

| Book Section | Step | Example Folder | ROM |
|---|:---:|---|---|
| 5-2 Making the Player Move | 1 | [`player_sprite`](ch05/2/player_sprite/) — Displaying the player sprite | [ROM](ch05/2/player_sprite/out/vertical_shooter.rom) |
| ↳ Same section | 2 | [`move_player`](ch05/2/move_player/) — Moving the player | [ROM](ch05/2/move_player/out/vertical_shooter.rom) |
| ↳ Same section | 3 | [`move_player_in_range`](ch05/2/move_player_in_range/) — Restricting the player movement area | [ROM](ch05/2/move_player_in_range/out/vertical_shooter.rom) |
| 5-3 Firing Bullets | 1 | [`bullet_fire`](ch05/3/bullet_fire/) — Firing bullets | [ROM](ch05/3/bullet_fire/out/vertical_shooter.rom) |
| 5-4 Managing Multiple Bullets | 1 | [`multiple_bullets`](ch05/4/multiple_bullets/) — Managing multiple bullets | [ROM](ch05/4/multiple_bullets/out/vertical_shooter.rom) |
| 5-5 Spawning Enemies | 1 | [`spawn_enemies`](ch05/5/spawn_enemies/) — Spawning enemies | [ROM](ch05/5/spawn_enemies/out/vertical_shooter.rom) |
| 5-6 Detecting Bullet–Enemy Collisions | 1 | [`collision_enemy_bullet`](ch05/6/collision_enemy_bullet/) — Detecting collisions between player bullets and enemies | [ROM](ch05/6/collision_enemy_bullet/out/vertical_shooter.rom) |
| 5-7 Handling Player–Enemy Collisions | 1 | [`collision_enemy_player`](ch05/7/collision_enemy_player/) — Detecting collisions between the player and enemies | [ROM](ch05/7/collision_enemy_player/out/vertical_shooter.rom) |
| 5-8 Adding a Scrolling Background | 1 | [`bg_scroll_1(wrong)`](ch05/8/bg_scroll_1%28wrong%29/) — Background scrolling: problem example | [ROM](ch05/8/bg_scroll_1%28wrong%29/out/vertical_shooter.rom) |
| ↳ Same section | 2 | [`bg_scroll_2(fixed)`](ch05/8/bg_scroll_2%28fixed%29/) — Background scrolling: corrected example | [ROM](ch05/8/bg_scroll_2%28fixed%29/out/vertical_shooter.rom) |
| 5-9 Fixing Sprite Position Offsets | 1 | [`scroll_sprite`](ch05/9/scroll_sprite/) — Correcting sprite coordinates during scrolling | [ROM](ch05/9/scroll_sprite/out/vertical_shooter.rom) |
| 5-10 Optimizing Game Performance | 1 | [`profile`](ch05/10/profile/) — Measuring and optimizing game performance | [ROM](ch05/10/profile/out/vertical_shooter.rom) |
| 5-11 Creating Different Enemies | 1 | [`various_enemies`](ch05/11/various_enemies/) — Adding different enemy types | [ROM](ch05/11/various_enemies/out/vertical_shooter.rom) |
| ↳ Same section | 2 | [`enemy_bullet`](ch05/11/enemy_bullet/) — Adding enemy bullets | [ROM](ch05/11/enemy_bullet/out/vertical_shooter.rom) |
| 5-12 Creating Explosion Effects | 1 | [`vertical_shooter`](ch05/12/vertical_shooter/) — Adding explosion effects | [ROM](ch05/12/vertical_shooter/out/vertical_shooter.rom) |
| 5-13 Completing the Title Screen and Game UI | 1 | [`ui`](ch05/13/ui/) — Adding the title screen and game UI | [ROM](ch05/13/ui/out/vertical_shooter.rom) |
| 5-14 Adding Background Music | 1 | [`bgm`](ch05/14/bgm/) — Adding background music | [ROM](ch05/14/bgm/out/vertical_shooter.rom) |
| 5-15 Adding Sound Effects | 1 | [`sfx`](ch05/15/sfx/) — Adding sound effects | [ROM](ch05/15/sfx/out/vertical_shooter.rom) |

## Building and Running the Examples

### Running a ROM Directly

- Download the `.rom` file from the project's `out` directory and open it in an MSX2 emulator such as openMSX.
- Some projects also include ROM files under `emul/rom`. To avoid confusion, all ROM links in this guide point to the versions in **`out`**.

### Building from Source (Windows)

1. Set up the MSXgl development environment as described in **Chapter 2** of the book.
2. Check that the `MSXGL_PATH` environment variable points to your MSXgl installation directory.
3. Run `build.bat` in the project folder you want to build.
4. After the build completes, find the generated `.rom` file in that project's `out` directory.

```bat
build.bat
```

> **Path compatibility note:** Depending on the version of the MSXgl build tools, builds may fail when project paths contain **spaces or Korean characters**, or when MSXgl and the example project are located on **different drives**. If this occurs, try placing both directories on the same drive under paths containing only ASCII letters, numbers, and no spaces. See Chapter 2 of the book for the full setup and build procedure.

## Notes

- Chapters 1 and 2 cover concepts and development-environment setup. Standalone project examples begin in **Chapter 3**.
- Examples in Chapters 4 and 5 represent successive stages of game development. Each project corresponds to the stage covered in its section.
- ROMs in `out` are ready-to-run build outputs. After modifying the source code, you can rebuild the project to generate a new ROM.
- This repository is intended for learning. **A public repository without a separate license does not automatically grant unrestricted rights to reuse or redistribute its contents.** Permitted uses are governed by any instructions from the copyright holder or by a separately provided license.

---

**Studio 319** · Example files for *Build MSX2 Games with C*
