#include <functional>
#include "KeyCode.h"
#include <string>

class Window
{
public:
	Window() = default;
	~Window() = default;

	Window(const Window& other) = delete;				// Copy constructor
	Window(Window&& other) = delete;					// Move constructor
	Window& operator = (const Window& other) = delete;	// Copy assignment operator
	Window& operator = (Window&& other) = delete;		// Move assignment operator

	void Create(int width, int height, const std::string& title);
	bool ProcessLoop();
	void InitializeGraphicsContext();
	void SetWindowPFD();
	void SetKeyCallback(std::function<void(KeyCode, KeyAction)> func);
	bool GetKeyDown(KeyCode key);
	bool GetKey(KeyCode key);
	bool GetKeyUp(KeyCode key);

	constexpr inline Window* QueryInstance() noexcept { return instance; }
	constexpr inline void* GetNativeHandle() noexcept { return handle; }

private:
	static Window* instance;

	
	void* handle;
	void* hardwareDeviceContext;
};