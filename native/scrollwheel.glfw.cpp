
// Header:

// By default, multiple windows will be preferred.
#define EXTERNAL_SCROLLWHEEL_MULTI_WINDOW

// Check if we need to include part of the standard library:
#ifdef EXTERNAL_SCROLLWHEEL_MULTI_WINDOW
	#include <map>
#else
	#define EXTERNAL_SCROLLWHEEL_SINGLE_WINDOW
	#define EXTERNAL_SCROLLWHEEL_SINGLE_WINDOW_SAFE
#endif

// Namespace(s):
namespace external_scrollwheel
{
	class scrollInfo : public Object
	{
		public:
			// Constructor(s):
			scrollInfo(Float x=0.0, Float y=0.0);
			scrollInfo(double x, double y);
			
			scrollInfo* construct(Float x=0.0, Float y=0.0);
			
			// Fields:
			Float xoffset, yoffset;
	};
}

// Source:

// Namespace(s):
namespace external_scrollwheel
{
	// Use the standard namespace.
	#ifdef EXTERNAL_SCROLLWHEEL_MULTI_WINDOW
		using namespace std;
	#endif
	
	// Typedefs:
	
	// Just for the sake of maximum compatibility:
	
	/*
	#if EXTERNAL_SCROLLWHEEL_SINGLE_WINDOW_SAFE && (GLFW_VERSION < 3)
		typedef void GLFWwindow;
	#endif
	*/
	
	#ifdef EXTERNAL_SCROLLWHEEL_MULTI_WINDOW
		typedef map<GLFWwindow*, scrollInfo> scrollWheelMap;
	#endif
	
	// Classes:
	scrollInfo::scrollInfo(Float x, Float y) { construct(x, y); }
	scrollInfo::scrollInfo(double x, double y) { construct((Float)x, (Float)y); } // scrollInfo((Float)x, (Float)y)
	
	scrollInfo* scrollInfo::construct(Float x, Float y)
	{
		xoffset = x;
		yoffset = y;
		
		return this;
	}
	
	// Global variable(s):
	#ifdef EXTERNAL_SCROLLWHEEL_MULTI_WINDOW
		scrollWheelMap wheelMap = scrollWheelMap();
	#else
		GLFWwindow* targetWindow = NULL; // nullptr;
		scrollInfo wheelInfo = scrollInfo();
	#endif
	
	// Functions:
	
	// This will retrieve the standard 'BBGame' instance.
	BBGlfwGame* getGame()
	{
		return BBGlfwGame::GlfwGame();
	}
	
	GLFWwindow* getWindow(BBGlfwGame* game)
	{
		return getGame()->GetGLFWwindow();
	}
	
	// This will get the standard 'GLFWwindow' object from the 'BBGame' framework.
	GLFWwindow* getGlobalWindow()
	{
		return getWindow(getGame());
	}
	
	scrollInfo* getWheelInfo(GLFWwindow* window)
	{
		return &wheelMap[window];
	}
	
	scrollInfo* getWheelInfo(BBGlfwGame* game)
	{
		return getWheelInfo(getWindow(game));
	}
	
	scrollInfo* getWheelInfo()
	{
		#ifdef EXTERNAL_SCROLLWHEEL_MULTI_WINDOW
			return getWheelInfo(getGlobalWindow());
		#else
			return &wheelInfo;
		#endif
	}
	
	// This will act as our main call-back.
	void scrollwheelCallback(GLFWwindow* window, double xoffset, double yoffset)
	{
		// Pick where we should store the information:
		#ifdef EXTERNAL_SCROLLWHEEL_MULTI_WINDOW
			wheelMap[window] =
		#else
			wheelInfo =
		#endif
		
		scrollInfo(xoffset, yoffset);
		
		return;
	}
	
	void addWindow(GLFWwindow* window)
	{
		#ifdef EXTERNAL_SCROLLWHEEL_SINGLE_WINDOW_SAFE
			if (window == targetWindow)
				return;
			
			removeWindow();
		#endif
		
		#if CFG_GLFW_VERSION >= 3
			glfwSetScrollCallback(window, &scrollwheelCallback);
		#else
			// Support for previous versions of GLFW is not currently available.
		#endif
		
		#if defined(EXTERNAL_SCROLLWHEEL_SINGLE_WINDOW) // !defined(EXTERNAL_SCROLLWHEEL_MULTI_WINDOW)
			// Since we can't properly hold the window, we need to use this hack:
			targetWindow = window;
		#endif
		
		return;
	}
	
	void removeWindow(GLFWwindow* window)
	{
		#ifdef EXTERNAL_SCROLLWHEEL_MULTI_WINDOW
			glfwSetScrollCallback(window, NULL); // nullptr;
			wheelMap.erase(window);
		#else
			if (window == targetWindow)
				removeWindow();
		#endif
		
		return;
	}
	
	void flushWindow(GLFWwindow* window)
	{
		#ifdef EXTERNAL_SCROLLWHEEL_MULTI_WINDOW
			wheelMap[window] = scrollInfo();
		#else
			if (window == targetWindow)
				flushWindow();
		#endif
		
		return;
	}
	
	void addWindow()
	{
		//addGame(getGame());
		addWindow(getGlobalWindow());
		
		return;
	}
	
	void removeWindow()
	{
		#if defined(EXTERNAL_SCROLLWHEEL_MULTI_WINDOW)
			removeWindow(getGlobalWindow());
		#else
			targetWindow = NULL; // nullptr;
		#endif
		
		return;
	}
	
	void flushWindow()
	{
		#if defined(EXTERNAL_SCROLLWHEEL_MULTI_WINDOW)
			flushWindow(getGlobalWindow());
		#else
			wheelInfo = scrollInfo();
		#endif
		
		return;
	}
	
	void addGame(BBGlfwGame* game)
	{
		addWindow(getWindow(game));
		
		return;
	}
	
	void removeGame(BBGlfwGame* game)
	{
		removeWindow(getWindow(game));
		
		return;
	}
	
	void flushGame(BBGlfwGame* game)
	{
		flushWindow(getWindow(game));
		
		return;
	}
	
	scrollInfo* initWheel(GLFWwindow* window)
	{
		addWindow(window);
		
		return getWheelInfo(window);
	}
	
	scrollInfo* initWheel(BBGlfwGame* game)
	{
		addGame(game);
		
		return getWheelInfo(game);
	}
	
	scrollInfo* initWheel()
	{
		addWindow();
		
		return getWheelInfo();
	}
}
