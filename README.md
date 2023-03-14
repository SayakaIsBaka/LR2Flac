# LR2Flac
xdelta patch to add FLAC keysound fallback for LR2, should work with any LR2 version (tested on LR2HD and LR2SD).

This is required for some BMSes which use FLAC files for keysounds but defines them as WAV files in the BMS, making them unable to work with LR2 out of the box. As LR2 actually supports FLAC out of the box, this patch just adds flac files as another fallback extension in addition to ogg and wav when loading a BMS.

## Usage
- Download LR2Flac.xdelta
- Patch LR2body.exe / LRHbody.exe using [Delta Patcher](https://github.com/marco-calautti/DeltaPatcher) / [xdelta](https://github.com/jmacd/xdelta) / [Hack64 Web Patcher](https://hack64.net/tools/patcher.php) or any xdelta-compatible patcher out there
- Profit!
