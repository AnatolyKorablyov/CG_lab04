#include "stdafx.h"
#include "WindowClient.h"
#include "includes/opengl-common.hpp"
#include <glm/gtc/matrix_transform.hpp>

using glm::mat4;
using glm::vec3;
using glm::vec4;

const unsigned NUMBER_MODELS_TO_GENERATE_TEXTURES = 4;

namespace
{
const vec3 CAMERA_EYE = {0, 10, 20};
const vec3 CAMERA_AT = {0, 0, 0};
const vec3 CAMERA_UP = {0, 1, 0};
const vec4 SUNLIGHT_DIRECTION = {0, -1, 0, 0};
const vec4 WHITE_RGBA = {1, 1, 1, 1};
const vec4 FADED_WHITE_RGBA = {0.3f, 0.3f, 0.3f, 1.0f};
const char SCENE_JSON[] = "res/static_scene/scene.json";
const char SKYBOX_PLIST[] = "res/static_scene/skybox-stone-and-sky.plist";

void SetupOpenGLState()
{
    // включаем механизмы трёхмерного мира.
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW);
    glCullFace(GL_BACK);
}

glm::mat4 MakeProjectionMatrix(const glm::ivec2 &size)
{
    // Матрица перспективного преобразования вычисляется функцией
    // glm::perspective, принимающей угол обзора, соотношение ширины
    // и высоты окна, расстояния до ближней и дальней плоскостей отсечения.
    const float fieldOfView = glm::radians(70.f);
    const float aspect = float(size.x) / float(size.y);
    const float zNear = 0.01f;
    const float zFar = 100.f;

    return glm::perspective(fieldOfView, aspect, zNear, zFar);
}
}

glm::vec3 GetRGBhueOnName(const std::string & colorName)
{
	glm::vec3 hueRGB;
	if (colorName == "green")
	{
		hueRGB.r = std::rand() % 100;
		hueRGB.g = std::rand() % 115 + 139;
		hueRGB.b = 0;
	}
	else if (colorName == "grey")
	{
		auto randNum = std::rand() % 130;
		hueRGB = { randNum, randNum, randNum };
	}
	else if (colorName == "red")
	{
		hueRGB.r = std::rand() % 115 + 139;
		hueRGB.g = std::rand() % 100;
		hueRGB.b = 0;
	}
	return hueRGB;
}

void FillingInPixels(SDL_Surface * pSur, Uint32 * pixels, const std::string & colorName)
{
	glm::vec3 hueRGB;
	for (int x = 0; x < pSur->w; x++)
	{
		for (int y = 0; y < pSur->h; y++)
		{
			hueRGB = GetRGBhueOnName(colorName);
			pixels[x + y*(pSur->w)] = SDL_MapRGB(pSur->format, hueRGB.r, hueRGB.g, hueRGB.b);
		}
	}
}

void CWindowClient::ProcedureGenerationTextures()
{
	std::string colorName = "random";

	for (int i = 0; i < NUMBER_MODELS_TO_GENERATE_TEXTURES; i++)
	{
		auto pTexture = m_world.getEntity(i).getComponent<CMeshComponent>().m_pModel.get()->m_materials[0].pDiffuse.get();

		SDL_Surface *pSur = SDL_CreateRGBSurface(0, 5 * 160, 5 * 160, 32, 0x000000ff, 0x0000ff00, 0x00ff0000, 0xff000000);

		Uint32* pixel = (Uint32 *)pSur->pixels;

		switch (i)
		{
		case 0:
			colorName = "green";
			break;
		case 3:
			colorName = "red";
			break;
		default:
			colorName = "grey";
		}

		FillingInPixels(pSur, pixel, colorName);

		pTexture->Bind();
		pTexture->ApplyImageData(*pSur);
		pTexture->ApplyTrilinearFilter();
		pTexture->ApplyMaxAnisotropy();
		pTexture->GenerateMipmaps();
		pTexture->Unbind();
	}
}

CWindowClient::CWindowClient(CWindow &window)
    : CAbstractWindowClient(window)
    , m_defaultVAO(CArrayObject::do_bind_tag())
    , m_mouseGrabber(window)
    , m_camera(CAMERA_EYE, CAMERA_AT, CAMERA_UP)
{
    const vec4 BLACK_RGBA = {0, 0, 0, 1};
    const float CAM_SPEED = 20;

    window.SetBackgroundColor(BLACK_RGBA);
    SetupOpenGLState();

    m_camera.SetMoveSpeed(CAM_SPEED);
    m_renderSystem.SetupLight0(SUNLIGHT_DIRECTION, WHITE_RGBA, FADED_WHITE_RGBA);

    CSceneLoader loader(m_world);
    loader.LoadScene(SCENE_JSON);
    loader.LoadSkybox(SKYBOX_PLIST);


	ProcedureGenerationTextures();


    // Добавляем систему, отвечающую за рендеринг планет.
    m_world.addSystem(m_renderSystem);

    // После активации новых сущностей или деактивации,
    //  а при добавления новых систем следует
    //  вызывать refresh() у мира.
    m_world.refresh();
}

void CWindowClient::OnUpdate(float deltaSeconds)
{
    m_camera.Update(deltaSeconds);
}

void CWindowClient::OnDraw()
{


    const glm::ivec2 windowSize = GetWindow().GetWindowSize();

    const mat4 view = m_camera.GetViewMat4();
    const mat4 proj = MakeProjectionMatrix(windowSize);


    glViewport(0, 0, windowSize.x, windowSize.y);
    m_renderSystem.Render(view, proj);

}

bool CWindowClient::OnKeyDown(const SDL_KeyboardEvent &event)
{
    return m_camera.OnKeyDown(event);
}

bool CWindowClient::OnKeyUp(const SDL_KeyboardEvent &event)
{
    return m_camera.OnKeyUp(event);
}

bool CWindowClient::OnMousePress(const SDL_MouseButtonEvent &event)
{
    return m_camera.OnMousePress(event);
}

bool CWindowClient::OnMouseMotion(const SDL_MouseMotionEvent &event)
{
    return m_mouseGrabber.OnMouseMotion(event)
            || m_camera.OnMouseMotion(event);
}

bool CWindowClient::OnMouseUp(const SDL_MouseButtonEvent &event)
{
    return m_camera.OnMouseUp(event);
}
