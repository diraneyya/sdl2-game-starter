# SDL2 Game Template

This is a minimal C program that can be built into web native targets (currently, the only native target is a Mac OS X app but I intent to include Windows and Linux targets as well).

![](./docs/sdl2_diagram.svg)

## Instructions

1. Install Emscripten:<br/>
https://emscripten.org/docs/getting_started/downloads.html

2. Clone the repository:<br/>
```bash
git clone git@github.com:diraneyya/sdl2-game-starter.git
cd sdl2-game-starter
```

3. Run `make web` to make the web app (`index.html`) or `make macos` to make the native Mac OS app (`index.app`). 

4. Chrome doesn't support file XHR requests so you need to open `index.html` from a web server (e.g. live server in vscode). You can use Emscripten for that too:
```bash
emrun index.html
```

## Web app

![](./docs/screenshot_web.png)

## Mac OS X native app

![](./docs/screenshot_macos.png)