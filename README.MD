# Usage
`ViCE.exe <video> (frameskip)`

the 1st argument is the video.

The 2nd argument is the frameskip. If not set, it will be 0 (no frames skipped). If set to "auto", the frames to be skipped will be determined (slow).

If the frameskip argument starts with `*` or `\`, the automatic frames will be automatically determined and multiplied or divided with the following number.

> Notes:
> The automatic frames skip was calibrated using a 480x360 video with 6569 frames @ 30fps
> Calculation itself is intensive, and I recomment running the program with a set frameskip with the same value as the one given by the automatic calculation.
> If it is really bad, I recommend using your own (0 will be slow)

If a .mp3 file with the same name is present, it will also be played.

## Examples:
`ViCE.exe "Bad Apple.mp4"`	Plays "Bad Apple.mp4" with 0 skipped frames
`ViCE.exe "Bad Apple.mp4" auto`	Plays "Bad Apple.mp4" with automatically skipped frames
`ViCE.exe "Bad Apple.mp4" 2`	Plays "Bad Apple.mp4" with 2 skipped frames
`ViCE.exe "Bad Apple.mp4" /48`	Plays "Bad Apple.mp4" with automatically skipped frames, divided by 48
`ViCE.exe "Bad Apple.mp4" *0.1`	Plays "Bad Apple.mp4" with automatically skipped frames, multiplied by 0.1

# Build
## Windows
There are two ways to build the program on Windows

be sure to use the Windows SDK 10.0 and the Build Tools v143

### Visual Studio GUI
1. open the project file (`ViCE\ViCE.vcxproj`) in a text editor
2. replace `C:\Users\romeo\source\Libraries\opencv` with your OpenCV location
3. open the solution in Visual Studio
4. smash "Build"

### Visual Studio CLI / MSVC
`cl /I "C:\opencv\build\include" /Fo.\intermediates\ "source\ViCE.cpp" "C:\opencv\build\x64\vc16\lib\opencv_world490.lib" /o.\x64\ViCE.exe`

Replace `C:\opencv` with your OpenCV folder

### MinGW
coming soon (maybe)

## MacOS
nuh uh

## Linux
nuh uh