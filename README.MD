# Usage
`ViCE.exe <video> (frameskip)`

the 1st argument is the video.

The 2nd argument is the frameskip. If not set, it will be 0 (no frames skipped). If set to "auto", the frames to be skipped will be determined (slow).

> Notes:
> The automatic frames skip was calibrated using a 480x360 video with 6569 frames @ 30fps
> Calculation itself is intensive, and I recommend running the program with a set frameskip with the same value as the one given by the automatic calculation.
> If it is really bad, I recommend using your own (0 will be slow)

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
