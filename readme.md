# Arkanoid

Minimal arcade game based on the classic Arkanoid, made in OpenGL.

Developed as final project of the *Graphics Programming* course for the Master in Computer Game Development.


## Gameplay

You should already know the game:
- `Left`/`Right` to move the paddle
- `Space` to launch the ball (careful, it's fast)
- Don't miss the ball
- Destroy all bricks
- Press `ESC` or `Q` to rage quit

There's just one demo level in the game,
so if you manage to beat that that's all, the game restarts.

The game restarts when you miss the ball anyway since you have a single life,
so there's really no point in beating the game at all :)


## Build

I provide pre-built binaries on [itch.io](https://alberto-lazari.itch.io/arkanoid) for macOS and Windows,
as well as a WebGL version playable directly from the browser!

Of course you can compile the game yourself, too. \
The project uses CMake as its main cross-platform build system.
You can easily use the `cmake` command for building the executable if you feel comfortable with it,
or you can use other methods that wrap its functionalities.

You will need to clone the repo first.
Remember that GLFW is included as a submodule, so clone this with
```bash
git clone --recurse-submodules https://github.com/alberto-lazari/arkanoid
```

### POSIX

I provide a `Makefile` for POSIX environments
(tested on macOS, but it should work fine on Linux).

It just wraps the CMake commands into a more intuitive interface.

#### Usage

- `make Arkanoid` compiles the game executable
- `make run` compiles the game and runs it
- `make clean` cleans the build

### Windows

If you just want an IDE to do the work, you can count on VS support for CMake
(and others, I suppose, like Rider).


Here's the [official guide](https://learn.microsoft.com/en-us/cpp/build/cmake-projects-in-visual-studio?view=msvc-170),
but you should be able to simply open it as a directory and VS should automatically do its magic.


## Technical Notes

Upon starting the development of this project,
I thought I could simply write some very direct and low-level code and get away with it.
Little did I know that I would have started writing pieces of a simple game engine.

The current state of the codebase is quite messy and is lacking a proper logical design.
It would require a major refactor,
but I feel like writing an actual engine would deviate outside the scope of the course,
and I sadly have not much time to spend on this.

If I was to rewrite this from scratch I would definitely dedicate more effort to designing a proper high-level interface for game objects and geometric models.
