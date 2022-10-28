# SDL2 Game Template

> Preview link: https://diraneyya.github.io/sdl2-game-starter/

This is a minimal C program that can be built into _web_ and _native_ targets (currently, only Mac OS X is supported).

![](./docs/sdl2_diagram.svg)

## Instructions

1. Install the _Emscripten SDK_ using the instructions below:<br/>
https://emscripten.org/docs/getting_started/downloads.html

2. Clone this repository and _cd_ into it:<br/>
```bash
git clone git@github.com:diraneyya/sdl2-game-starter.git
cd sdl2-game-starter
```

3. Run `make web` to make the web target.
  - _Artifact_: `index.html` (at the root of the repository)
  - _How to run_: using the live-server extension in vscode or the [emrun](https://emscripten.org/docs/compiling/Running-html-files-with-emrun.html) command by typing `emrun index.html` in the shell.

4. Run `make macos` to make the Mac OS X target.
  - _Artifact_: `index.app` (at the root of the repository). 
  - _How to run_: double click in Mac OS X

## Web app

![](./docs/screenshot_web.png)

## Mac OS X native app

![](./docs/screenshot_macos.png)
