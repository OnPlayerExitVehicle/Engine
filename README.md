# Engine
This project is a multiplayer based game engine for my graduation thesis. Updates are coming late to GitHub because my main objective is my graduation thesis and its weekly reports. I'll be updating here when everything about reports are completed and main bugs fixed.

# Dependencies

[GLFW](https://github.com/glfw/glfw) for cross-platform window creation.

[GLAD](https://github.com/Dav1dde/glad) for cross-platform OpenGL binding.

[Bullet 3](https://github.com/bulletphysics/bullet3) for physics.

Also [OneLoneCoder](https://github.com/onelonecoder)'s networking library is used for networking. (Soon to be replaced by my own implementation)

# Features

- You can create your own components or use internal ones to determine how your objects will behave.
- You can use physics components to use physics implementations, or create yours.
- You can use networking components to create networked game systems. You can also create networking components with given interfaces.
- Multithreaded networking, no lags or data shadowing between frames.

# To Do
- Implement multithreaded rendering.
- Implement and develop various lighting, shadowing and rendering techniques.
- Implement object loading for most common formats. (Urgent!)
- Implement animation engine. (preferably [ozz-animation](https://github.com/guillaumeblanc/ozz-animation))
