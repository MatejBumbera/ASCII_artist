# ASCII_artist
Inspired by: https://github.com/desrtfx/SkillGradedProjects

# Description:
This program transforms pictures into ASCII art.

# How to use:
```
python .\main.py path_to_picture

for properly displayed picture, download it with ctrl + s
```

path_to_picture - relative or absolute path to picture

# Dependencies:
cv2 - pip install opencv-python

# How to run C++ version
1. Install opencv extension on your computer. (https://opencv.org/releases/)
2. Install cmake. (https://cmake.org/download/)
2. Add <your_path>/opencv/build/x64/vc16/bin to your system's PATH environment variable.
3. Set CMakeLists.txt file according to instructions in the file. 
4. Go into folder  cpp_version/ASCII_artist_build.
5. Run: cmake ../
        cmake --build .
        cd ./Debug 
6. run the executable: .\ASCII_artist.exe path_to_picture
