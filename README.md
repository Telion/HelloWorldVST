# HelloWorldVST
A basic "Hello World" style Visual Studio 2017 project for creating a virtual instrument in VST format. The official Steinberg VST SDK is included (GPL v3 licensed).

# To build the SDK
- Install CMake (and make sure it is in your Path)
- Create a build folder next to the SDK (recommended name: build_sdk)
- From inside the build folder, run 'cmake -G"Visual Studio 15 2017 Win64" ../vst3sdk'
- Open the .sln file that now exists in your build folder. In Visual Studio 2017, build the solution.

# To create your plugin (without copying this one)
- Start with a c++ console application sln (without its own folder for the sln) in a folder next to the VST3 SDK.
- Include dllmain.cpp from public.sdk/source/main.
- Write an Entry.cpp file
- Write a Processor class
- Write a Controller class
- Add a .def file
- Add "$(MSBuildProjectDirectory)\\..\vst3sdk;$(MSBuildProjectDirectory)\\..\vst3sdk\vstgui4" to your include paths
- Add "$(MSBuildProjectDirectory)\\..\build_sdk\lib\Debug\base.lib;$(MSBuildProjectDirectory)\\..\build_sdk\lib\Debug\sdk.lib;$(MSBuildProjectDirectory)\\..\build_sdk\lib\Debug\vstgui_support.lib;$(MSBuildProjectDirectory)\\..\build_sdk\lib\Debug\vstgui_uidescription.lib;$(MSBuildProjectDirectory)\\..\build_sdk\lib\Debug\vstgui.lib" to your linker additional dependencies
- Important: In linker options -> All Options, add "/EXPORT:GetPluginFactory" to Additional Options
- Set the project configuration type to "Dynamic Library (.dll)"
- Set the target extension to ".vst3"
- Build from Visual Studio

# To run validation as a build step
- Add "$(MSBuildProjectDirectory)\build_sdk\bin\Debug\validator.exe $(MSBuildProjectDirectory)\VersatileSynth\x64\Debug\VersatileSynth.vst3" as a post-build step. (Repeat for Release if needed.)
