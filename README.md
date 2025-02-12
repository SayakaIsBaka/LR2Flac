# LR2Flac

A LR2 mod adding FLAC files as keysound fallback for LR2, should work with any LR2 version (tested on LR2HD and LR2SD).
This is required for some BMSes which use FLAC files for keysounds but defines them as WAV files in the BMS, making them unable to work with LR2 out of the box. As LR2 actually supports FLAC out of the box, this mod just adds flac files as another fallback extension in addition to ogg and wav when loading a BMS.

The old xdelta patch is also provided for people who prefer patching their installation of LR2 (not recommended, may cause instabilities).

## Usage

LR2Flac is provided as a DLL to inject into LR2. [lr2_chainload](https://github.com/SayakaIsBaka/lr2_chainload) is recommended as it allows to automatically load LR2Flac during startup without using any extra binaries.
To use LR2Flac with lr2_chainload, follow the steps below:
- Download the latest release of lr2_chainload [here](https://github.com/SayakaIsBaka/lr2_chainload/releases)
- Extract the contents of the archive in LR2's folder
- Download the latest release of LR2Flac [here](https://github.com/SayakaIsBaka/LR2Flac/releases)
- Put the DLL file somewhere on your system (it doesn't have to be in LR2's folder)
- Edit `chainload.txt` in LR2's folder and add a line with the path to LR2Flac's DLL. For example, if placing the `LR2Flac.dll` file into LR2's folder, the `chainload.txt` file would be similar to the following:
```
#
# lr2_chainload
# https://github.com/SayakaIsBaka/lr2_chainload
#
# This file is read during startup to automatically load additional libraries.
# Each line should contain either a relative or full path to a library file.
LR2Flac.dll
```
- Run the game. BMS files using FLAC should now play properly.

You may also use LR2Flac by injecting the DLL into LR2's process with your favorite DLL injector.

## Usage (xdelta patch)

- Download LR2Flac.xdelta
- Patch LR2body.exe / LRHbody.exe using [Delta Patcher](https://github.com/marco-calautti/DeltaPatcher) / [xdelta](https://github.com/jmacd/xdelta) / [Hack64 Web Patcher](https://hack64.net/tools/patcher.php) or any xdelta-compatible patcher out there
- Profit!
