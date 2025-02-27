#pragma once

#include <cocos2d.h>
#include <functional>
#include <string>
#include <imgui.h>

class ImGuiCocos {
public:
	enum class InputMode {
		// This is the default behavior, which will let clicks go through to gd,
		// and keyboard inputs too as long as imgui isn't using it.
		Default,
		// This mode blocks any input from going through as long as imgui is toggled on.
		Blocking,
	};
private:
	cocos2d::CCTexture2D* m_fontTexture = nullptr;
	bool m_initialized = false;
	bool m_visible = true;
	bool m_reloading = false;
	bool m_forceLegacy = false;
	std::function<void()> m_setupCall, m_drawCall;
	InputMode m_inputMode = InputMode::Default;
	ImGuiMouseCursor m_lastCursor = ImGuiMouseCursor_COUNT;

	float uiScale = 1.0f;

	ImGuiCocos();

	void newFrame();
	void renderFrame() const;
	void legacyRenderFrame() const; // uses OpenGL 2.0 for rendering, for compatibility with older devices
public:
	ImGuiCocos(const ImGuiCocos&) = delete;
	ImGuiCocos(ImGuiCocos&&) = delete;

	static ImGuiCocos& get();

	// called on mod unloaded
	void destroy();
	// called on swapBuffers
	void drawFrame();

	ImGuiCocos& setup(std::function<void()> fun);
	ImGuiCocos& setup();

	ImGuiCocos& draw(std::function<void()> fun);

	// used to reinitialize imgui context
	void reload();

	void toggle();
	[[nodiscard]] bool isVisible() const;
	void setVisible(bool v);

	void setInputMode(InputMode mode);
	InputMode getInputMode();

	void setForceLegacy(bool force);
	[[nodiscard]] bool getForceLegacy() const;

	[[nodiscard]] bool isInitialized() const;
	
	float getUIScale();
	void setUIScale(float v);

	static ImVec2 cocosToFrame(const cocos2d::CCPoint& pos);
	static cocos2d::CCPoint frameToCocos(const ImVec2& pos);
};
