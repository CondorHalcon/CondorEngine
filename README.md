# CondorEngine

## Visual Studio Config
### `C/C++\General\Additional Include Libraries`
```
$(SolutionDir)thirdparty\;%(AdditionalIncludedDirectories)
```

### `Linker\Additional Dependencies`
```
glfw3.lib
glfw32s.lib
opengl32.lib
```

### `Linker\General\Additional Library Directories`
```
$(SolutionDir)thirdparty\glfw\lib\$(PlatformShortName);$(SolutionDir)thirdparty\glew\lib\$(PlatformShortName);%(AdditionalLibraryDirectories)
```
