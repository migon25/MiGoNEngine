#include "Layers.h"
#include <iostream>
#include <string>

#if defined(_WIN32)
#include <windows.h>
#elif defined(__APPLE__)
#include <cstdlib>
#elif defined(__linux__)
#include <cstdlib>
#endif

static void MenuFile();
void OpenWebsite(const std::string& url);

Layers::Layers(GLFWwindow* _window, RizzEngine& _engine, Camera& _camera, FBO* _frameBuffer, std::vector<GameObject*>& _model) : window(_window), engine(_engine), camera(_camera),  fbo(_frameBuffer), model(_model)
{
	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
 
	// Setup Dear ImGui style
	//ImGui::StyleColorsDark();
	//ImGui::StyleColorsLight();
    //ImGui::StyleColorsClassic();
    ImGui::StyleColorsCustom(); // My custom colored GUI

	ImGuiStyle& style = ImGui::GetStyle();
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		style.WindowRounding = 0.0f;
		style.Colors[ImGuiCol_WindowBg].w = 0.0f;
        style.FrameRounding = 3.0f;
	}

	// Setup Platform/Renderer backends
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 130");

    //create the panels
    CreatePanels();
    m_PropertyPanel.get()->SwitchActive();
}

void Layers::CreatePanels()
{
    PropertyPanel panel1(model);
    Layers::m_PropertyPanel = std::make_unique<PropertyPanel>(panel1);
    Layers::panels.push_back(m_PropertyPanel.get());
}

void Layers::BeginLayer()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

    // Create the docking environment
    ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus |  ImGuiWindowFlags_NoBackground;

    ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->Pos);
    ImGui::SetNextWindowSize(viewport->Size);
    ImGui::SetNextWindowViewport(viewport->ID);

    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGui::Begin("InvisibleWindow", nullptr, windowFlags);
    ImGui::PopStyleVar(3);

    ImGuiID dockSpaceId = ImGui::GetID("InvisibleWindowDockSpace");

    ImGui::DockSpace(dockSpaceId, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_PassthruCentralNode);
    ImGui::End();
}

void Layers::Render()
{
    //ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());

    AppMainMenuBar();
	ImGui::ShowDemoWindow();
    ImGui::Begin("Viewport");
    {
        ImGui::Checkbox("WireFrame Mode", &engine.wireframeMode);
        ImGui::BeginChild("GameRender");
        float width = ImGui::GetContentRegionAvail().x;
        float height = ImGui::GetContentRegionAvail().y;
        if (ImGui::IsMouseHoveringRect(ImGui::GetWindowPos(),ImVec2(ImGui::GetWindowWidth(), ImGui::GetWindowHeight())))
        {
            camera.Imputs(window);
        }
        ImGui::Image((ImTextureID)fbo->getFrameTexture(), ImGui::GetContentRegionAvail(),ImVec2(0, 1),ImVec2(1, 0));
    }
    ImGui::EndChild();
    ImGui::End();

    for (auto &panel : panels)
    {
        if (panel->active)
            panel->Render();
    }
}

void Layers::EndLayer()
{
	// Rendering
	ImGui::Render();
	glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        GLFWwindow* backup_current_context = glfwGetCurrentContext();
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        glfwMakeContextCurrent(backup_current_context);
    }
}

void Layers::AppMainMenuBar()
{
    const std::string GitHubRepo = "https://github.com/migon25/RiZzEngine";
    const std::string ricky = "https://www.youtube.com/watch?v=xvFZjo5PgG0";
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            MenuFile();
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Info"))
        {
            if (ImGui::MenuItem("About")) {}
            if (ImGui::MenuItem("Github")) 
            {
                OpenWebsite(GitHubRepo);
            }
            ImGui::Separator();
            if (ImGui::MenuItem(":D"))
            {
                OpenWebsite(ricky);
            }
            ImGui::EndMenu();
           
        }
        ImGui::EndMainMenuBar();
    }
}

static void MenuFile()
{
    ImGui::MenuItem("(demo menu)", NULL, false, false);
    if (ImGui::MenuItem("New")) {}
    if (ImGui::MenuItem("Open", "Ctrl+O")) {}
    if (ImGui::BeginMenu("Open Recent"))
    {
        ImGui::MenuItem("fish_hat.c");
        ImGui::MenuItem("fish_hat.inl");
        ImGui::MenuItem("fish_hat.h");
        if (ImGui::BeginMenu("More.."))
        {
            ImGui::MenuItem("Hello");
            ImGui::MenuItem("Sailor");
            if (ImGui::BeginMenu("Recurse.."))
            {
                MenuFile();
                ImGui::EndMenu();
            }
            ImGui::EndMenu();
        }
        ImGui::EndMenu();
    }
    if (ImGui::MenuItem("Save", "Ctrl+S")) {}
    if (ImGui::MenuItem("Save As..")) {}

    ImGui::Separator();
    if (ImGui::BeginMenu("Options"))
    {
        static bool enabled = true;
        ImGui::MenuItem("Enabled", "", &enabled);
        ImGui::BeginChild("child", ImVec2(0, 60), true);
        for (int i = 0; i < 10; i++)
            ImGui::Text("Scrolling Text %d", i);
        ImGui::EndChild();
        static float f = 0.5f;
        static int n = 0;
        ImGui::SliderFloat("Value", &f, 0.0f, 1.0f);
        ImGui::InputFloat("Input", &f, 0.1f);
        ImGui::Combo("Combo", &n, "Yes\0No\0Maybe\0\0");
        ImGui::EndMenu();
    }

    if (ImGui::BeginMenu("Colors"))
    {
        float sz = ImGui::GetTextLineHeight();
        for (int i = 0; i < ImGuiCol_COUNT; i++)
        {
            const char* name = ImGui::GetStyleColorName((ImGuiCol)i);
            ImVec2 p = ImGui::GetCursorScreenPos();
            ImGui::GetWindowDrawList()->AddRectFilled(p, ImVec2(p.x + sz, p.y + sz), ImGui::GetColorU32((ImGuiCol)i));
            ImGui::Dummy(ImVec2(sz, sz));
            ImGui::SameLine();
            ImGui::MenuItem(name);
        }
        ImGui::EndMenu();
    }

    // Here we demonstrate appending again to the "Options" menu (which we already created above)
    // Of course in this demo it is a little bit silly that this function calls BeginMenu("Options") twice.
    // In a real code-base using it would make senses to use this feature from very different code locations.
    if (ImGui::BeginMenu("Options")) // <-- Append!
    {
        static bool b = true;
        ImGui::Checkbox("SomeOption", &b);
        ImGui::EndMenu();
    }

    if (ImGui::BeginMenu("Disabled", false)) // Disabled
    {
        IM_ASSERT(0);
    }
    if (ImGui::MenuItem("Checked", NULL, true)) {}
    ImGui::Separator();

    if (ImGui::Button("Quit")) 
    {
        ImGui::OpenPopup("Close program?");
    }

    if (ImGui::BeginPopupModal("Close program?", NULL, ImGuiWindowFlags_AlwaysAutoResize))
    {
        ImGui::Text("      Do you want to close program?\n");
        ImGui::Separator();

        if (ImGui::Button("YES", ImVec2(120, 0))) { glfwSetWindowShouldClose(glfwGetCurrentContext(), true); }
        ImGui::SetItemDefaultFocus();
        ImGui::SameLine();
        if (ImGui::Button("Cancel", ImVec2(120, 0))) { ImGui::CloseCurrentPopup(); }
        ImGui::EndPopup();
    }
}

// just some code to open Websites
void OpenWebsite(const std::string& url) {
    std::cout << "Opening URL: " << url << std::endl;

#if defined(_WIN32)
    ShellExecuteA(nullptr, "open", url.c_str(), nullptr, nullptr, SW_SHOWNORMAL);
    printf("ShellExecute called.");
    if (GetLastError() != 0) {
        std::cout << "Error: " << GetLastError() << std::endl;
    }
#elif defined(__APPLE__)
    // On macOS, use the 'open' command to open a URL
    std::string command = "open " + url;
    system(command.c_str());
#elif defined(__linux__)
    // On Linux, use the 'xdg-open' command to open a URL
    std::string command = "xdg-open " + url;
    system(command.c_str());
#else
    // Unsupported platform
    printf("Opening websites is not supported on this platform.");
#endif
}