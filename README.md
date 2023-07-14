# WiiUCrashLogDumper
A simple Wii U homebrew for dumping the consoles crash logs.

> :information_source: **WiiUCrashLogDumper requires the [MochaPayload](https://github.com/wiiu-env/MochaPayload)!**  
> Make sure to update to [Aroma](https://aroma.foryour.cafe) or [Tiramisu](https://tiramisu.foryour.cafe), in order to use this application.

## Screenshots
![](res/screenshot.png)

## Building
For building you need: 
- [wut](https://github.com/devkitPro/wut)
- [libmocha](https://github.com/wiiu-env/libmocha)
- [wiiu-sdl2](https://github.com/GaryOderNichts/SDL/tree/wiiu-sdl2-2.26)
- wiiu-sdl2_ttf
- wiiu-curl
- wiiu-mbedtls

You can also build WiiUIdent using docker:
```bash
# Build docker image (only needed once)
docker build . -t wiiucrashlogdump_builder

# make 
docker run -it --rm -v ${PWD}:/project wiiucrashlogdump_builder make

# make clean
docker run -it --rm -v ${PWD}:/project wiiucrashlogdump_builder make clean
```

## Format the code via docker

`docker run --rm -v ${PWD}:/src ghcr.io/wiiu-env/clang-format:13.0.0-2 -r ./source -i`


## Additional Credits
- [@GaryOderNichts](https://github.com/GaryOderNichts) for creating [WiiUIdent](https://github.com/GaryOderNichts/WiiUIdent). The GUI is based on WiiUIdent.
- [FontAwesome](https://fontawesome.com/) for the icons.
- [Terminus Font](https://terminus-font.sourceforge.net/) for the monospace font.
