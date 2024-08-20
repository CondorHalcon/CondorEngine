# CondorEngine

## Visual Studio Config
### `C/C++\General\Additional Include Libraries`
```
$(SolutionDir)thirdparty\;%(AdditionalIncludedDirectories)
```

### `Linker\Input\Additional Dependencies`
```
glfw3.lib
glew32s.lib
opengl32.lib
%(AdditionalDependencies)
```

### `Linker\General\Additional Library Directories`
```
$(SolutionDir)thirdparty\glfw\lib\$(PlatformShortName);$(SolutionDir)thirdparty\glew\lib\$(PlatformShortName);%(AdditionalLibraryDirectories)
```
