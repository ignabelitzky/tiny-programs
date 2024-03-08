# Simple Audio Player

This is a simple audio player written in C++ using the miniaudio library and nCurses. It loads an audio file and plays it back through the default audio output device.

## Features
- Supports playback of various audio file formats (WAV, FLAC, MP3, etc.)
- Minimalistic command-line interface
- Works on Linux

## Prerequisites
- **g++ compiler**
- miniaudio library (included in the `include` directory)
- ncurses library
- Audio file(s) to play

## Building
To build the program, follow these steps:

1. Clone this repository or download the source code files.
```Bash
git clone git@github.com:ignabelitzky/tiny-programs
```
2. Navigate to the directory containing the source code.
```Bash
cd tiny-programs/audio-player
```
3. Compile the source code using make:
```Bash
make
```

## Usage
Run the program from the command line with the path to the audio file you want to play as the argument. For example:
```Bash
./main
```
A menu will show up, and you only need to select one option of the three to play the audio.

## Troubleshooting
- If you encounter any issues with audio playback, ensure that your audio output device is correctly configured and functional.
