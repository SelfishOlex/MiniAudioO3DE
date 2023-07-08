# MiniAudioO3DE
This is a very early integration of https://miniaud.io/ into Open 3D Engine as a Gem. It has the most fundamental features working already: sound playback, sound positioning, and listener positioning. One can test the sounds in the Editor viewport without entering game mode.

# Supported Sound Formats
- Wav (in main branch)
- Mp3, Flac and Ogg support is available in development branch (to be tested and merged to main when appropriate)

# Components
- MiniAudio Playback Component

![image](https://user-images.githubusercontent.com/5432499/184503877-e9d1d3ec-4520-48eb-9bc2-bff25ab47709.png)

- MiniAudio Listener Component

![image](https://user-images.githubusercontent.com/5432499/184503840-0ac54dd6-66e8-400b-bc68-8ac16f839c1f.png)

# How-To Guide in C++

1. Declare a dependency in your cmake target on `Gem::MiniAudio.API`:
    ```
    BUILD_DEPENDENCIES
        PUBLIC
            ...
            Gem::MiniAudio.API
    ```
2. Include the header file, for example
    ```cpp
    #include <MiniAudio/MiniAudioPlaybackBus.h>
    ```
3. Invoke MiniAudioPlaybackRequestBus interface
    ```cpp
    MiniAudio::MiniAudioPlaybackRequestBus::Event(GetEntityId(), &MiniAudio::MiniAudioPlaybackRequestBus::Events::Play);
    ```
4. Or get a direct pointer to the interface:
    ```cpp    
    if (auto bus = MiniAudio::MiniAudioPlaybackRequestBus::FindFirstHandler(GetEntityId()))
    {
        bus->Play();
    }
    ```
5. You can also declare a dependency of a component on a particular component of MiniAudio, such as:
    ```cpp
    static void GetRequiredServices(AZ::ComponentDescriptor::DependencyArrayType& required)
    {
        required.push_back(AZ_CRC_CE("MiniAudioPlaybackComponent"));
    }
    ```
    
# How-To in Scripting 

The following nodes are exposed to scripting.

![image](https://user-images.githubusercontent.com/5432499/197317433-18b16407-2bd8-4deb-abf1-53dd67f1d831.png)

For the playback component:
![image](https://user-images.githubusercontent.com/5432499/197317353-60f694af-4a30-46d8-bb85-89519f9e87de.png)

For the listener component:
![image](https://user-images.githubusercontent.com/5432499/197317439-5cf7eaad-b5ab-4fb1-86ac-c6d2fb75a4cd.png)



# License

Same license as Open 3D Engine, see https://github.com/o3de/o3de

