#pragma once
// #include "Camera.h"
// #include "Input.h"
// #include "Object.h"
// #include "Portal.h"
// #include "Player.h"
// #include "Timer.h"
// #include "Scene.h"
// #include "Sky.h"
#include <GL/glew.h>
// #include <windows.h>
#include <memory>
#include <vector>

#include <GLFW/glfw3.h>

#include "euclid/core/game_header.h"
#include "euclid/util/timer.h"
#include "euclid/core/camera.h"
#include "euclid/object/portal.h"
#include "euclid/sky.h"

class Engine
{
public:
  Engine(int *argc, char **argv);
  ~Engine() = default;

  int Run();
  // void Update();
  void Render(const Camera & /* cam */, GLuint /* curFBO */, const Portal * /* skipPortal */);
  // void LoadScene(int ix);

  // LRESULT WindowProc(HWND hCurWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

  // const Player& GetPlayer() const { return *player; }
  float NearestPortalDist() const
  {
    return 0.0;
  };

private:
  void CreateGLWindow(int *argc, char **argv);
  void InitGLObjects();
  // void DestroyGLObjects();
  // void SetupInputs();
  // void ConfineCursor();
  // void ToggleFullscreen();

  // HDC   hDC;           // device context
  // HGLRC hRC;				   // opengl context
  // HWND  hWnd;				   // window
  // HINSTANCE hInstance; // process id
  GLFWwindow *window;

  // LONG iWidth;         // window width
  // LONG iHeight;        // window height
  bool isFullscreen; // fullscreen state

  Camera main_cam;
  // Input input;
  Timer timer;

  std::vector<std::shared_ptr<Object>> vObjects;
  std::vector<std::shared_ptr<Portal>> vPortals;
  std::shared_ptr<Sky> sky;
  // std::shared_ptr<Player> player;

  GLint occlusionCullingSupported;

  // std::vector<std::shared_ptr<Scene>> vScenes;
  // std::shared_ptr<Scene> curScene;
};
