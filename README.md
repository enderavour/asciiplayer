# asciivid - simple ASCII video displayer built using OpenCV

## Descripion:
- The project was rewritten and resructured.
- Currently it is still binded to Windows, but will be ported to other systems.
- Extracts audio via ffmpeg, converts frames into videos and renders them in terminal. 

### Requirements:
- OpenCV (2)
- ffmpeg 
- miniaudio 

### Build and Usage:
1. Clone the Github repository of the project:
```cmd
git clone https://github.com/enderavour/asciiplayer.git && cd asciiplayer
```
2. Navigade into ```include``` and download the ```miniaudio.h``` header:
```cmd
curl -o miniaudio.h https://raw.githubusercontent.com/mackron/miniaudio/master/miniaudio.h
```
3. Download and extract OpenCV into the root of the project.
4. Run ```build_win.bat``` or type in manually:
```cmd
cmake -DCMAKE_PREFIX_PATH=.\opencv\build ..
```
5. Navigate to ```build``` and run
```
cmake --build .
```
6. Navigate into Debug directory and run the program:
```
asciiplayer video.mp4
```
## Notes
- If there are DLL errors while trying to start the application, just move the required DLL's into ```Debug``` folder, place them near the executable
- Contributors and improvement ideas are welcome. 