# Tyger Memory

---

## Background

### What Is Tyger?

In summer 2024, [Kana (ElusiveFluffy)](https://github.com/ElusiveFluffy), a member of the Ty the Tasmanian Tiger modding community, discovered a relatively simple method to inject C++ code into any of the original trilogy Ty games through an unused DLL referenced by the game. Kana then created the [TygerFramework](https://github.com/ElusiveFluffy/TygerFramework), a plugin loader and API designed to develop and load libraries of code into Ty, with the option for ImGui implementation to create custom UI within the game process.



### Why Does This Matter?

By doing this, Ty shares the same memory space as the loaded dlls, our custom code can read and write to memory locations within Ty directly meaning any memory manipulation can be significantly faster than the alternative kernel32 method.

This opens the door to rewrites of many of the tools that have already been created as separate applications with much cleaner and faster implementations.

### So What Is TygerMemory?

Tyger Memory is a set of high level functions that hides the memory reading behind easy to read and implement functions with clear structure and names. No more random memory addresses littered throughout the code of our tools! With this API, we can directly access a lot of the most common memory structures and data from the game with no knowledge of the structures themselves on the user's part.

---

## Using TygerMemory

### Getting Started

Firstly, this API is TygerMemory1 specifically aimed at Ty the Tasmanian Tiger 1. The functions provided by the API will produce undefined behaivour on the other games. TygerMemory2 and TygerMemory3 may be created in the future. Additionally there are some safety checks on certain function calls which are expected to be handled by the user. Check the documentation or function info for more details.

If you're only looking to use plugins and someone has sent you to this page, all you need to do is download the correct (usually the latest) version of the TygerMemory.dll and add it to your 'Plugins' directory. The other files are not needed.

If you're here as a developer wanting to make a plugin, you're best starting with [setting up TygerFramework](https://github.com/ElusiveFluffy/TygerFramework). Once you have your first plugin working, it's time to implement TygerMemory. A full guide can be found on the modding wiki.

### Adding TygerMemory

The first thing you'll need to do is head over to the releases page and download the TygerMemoryAPI.zip. This file contains all of the required header files in an include folder as well as the .lib build of the API. 

Add the header files in the include directory to your project. This step will differ depending on what build system you use. For visual studio, you can simply go to the project properties and add the include directory to the project include directories.

Finally, make sure you set the linker to link TygerMemory.lib. In visual studio, adding an existing item and selecting TygerMemory.lib will add the library as source. This, along with the header files being included, is sufficient for usage.

If you're developing several plugins, you may either

- Keep a single instance of the API files somewhere and have all projects reference it. This way, you only need to update the single instance and then your projects' references to the API files when a new update is released.

- Copy the API files you your project each time so that each project is built with a specific version of the API. If, for a given project, you don't expect to need new features as they are released, this is the better option.

Make sure the header files and the library you are using are from the same build of the API. Mismatched versions often lead to linker or invalid dll entry point errors.

---

## Starting Coding

Once you're set up, you need to include the "core.h" header file in your plugin's entry point. After initializing or in the initialization method for TygerFramework, you can call

```cpp
Core::initialize((HMODULE)API::Get()->param()->TyHModule);
```

This initializes the API to allow it to read from the game's memory by providing it the .exe module handle.

From here, any of the functions across the API can be accessed and used to retrieve and modify data in the game. For full documentation, make sure you check out [the modding wiki page](). The [Ty Collectible Tracker Plugin](https://github.com/xMcacutt/Ty-Collectible-Tracker-Plugin) can be used as an example.

---

## Resources

### Need Help?

Join the [Ty the Tasmanian Tiger modding discord](https://discord.gg/2jRZZcknkM).

There's plenty of people who would be more than happy to help. We'd also love any input you can give.

### How Can I Contribute?

We'd love any additions to the project. This API will hopefully become large and comprehensive over time with any new findings in Ty's memory being added in. If you find something you need, suggest it to us in the modding discord linked above or make a pull request and it'll be merged.


