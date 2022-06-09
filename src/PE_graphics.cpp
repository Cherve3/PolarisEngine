
#include <string.h>
#include <stdio.h>

#include "PE_graphics.h"

void PE_graphics::SDL_init() {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		slog("Could not initialize SDL.");
	}
	else {
		slog("SDL initialized");
	}

	main_window = SDL_CreateWindow(
		"Polaris Engine",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		1280,
		720,
		SDL_WINDOW_VULKAN);

	if (main_window == NULL) {
		slog("Could not create SDL window.");
	}
	else {
		slog("SDL window created");
	}
}

void PE_graphics::vulkan_init() {

	unsigned extension_count;
	if (!SDL_Vulkan_GetInstanceExtensions(main_window, &extension_count, NULL)) {
		slog("Could not get the number of required instance extensions from SDL.");
	}
	else {
		slog("Found %d extensions", extension_count);
	}
	std::vector<const char*> extensions(extension_count);
	if (!SDL_Vulkan_GetInstanceExtensions(main_window, &extension_count, extensions.data())) {
		slog("Could not get the names of required instance extensions from SDL.");
	}
	else {
		slog("Extensions available:");
		for (const auto& i : extensions)
			slog("%s", i);
	}

	std::vector<const char*> layers;
#if defined(_DEBUG)
	layers.push_back("VK_LAYER_KHRONOS_validation");
#endif

	// vk::ApplicationInfo allows the programmer to specifiy some basic information about the
	// program, which can be useful for layers and tools to provide more debug information.
	vk_app_info = vk::ApplicationInfo()
		.setPApplicationName("Polaris Engine")
		.setApplicationVersion(VK_MAKE_VERSION(1, 0, 0))
		.setPEngineName("Polaris Engine")
		.setEngineVersion(VK_MAKE_VERSION(1, 0, 0))
		.setApiVersion(VK_API_VERSION_1_3);

	// vk::InstanceCreateInfo is where the programmer specifies the layers and/or extensions that
	// are needed.
	vk_instance_info = vk::InstanceCreateInfo()
		.setFlags(vk::InstanceCreateFlags())
		.setPApplicationInfo(&vk_app_info)
		.setEnabledExtensionCount(static_cast<uint32_t>(extensions.size()))
		.setPpEnabledExtensionNames(extensions.data())
		.setEnabledLayerCount(static_cast<uint32_t>(layers.size()))
		.setPpEnabledLayerNames(layers.data());

	// Create the Vulkan instance.
	try {
		vk_instance = vk::createInstance(vk_instance_info);
	}
	catch (const std::exception& e) {
		slog("Could not create a Vulkan instance : %s", e.what());
	}

	// Create a Vulkan surface for rendering
	VkSurfaceKHR c_surface;
	if (!SDL_Vulkan_CreateSurface(main_window, static_cast<VkInstance>(vk_instance), &c_surface)) {
		slog("Could not create a Vulkan surface.");
	}
	vk::SurfaceKHR surface(c_surface);
}

void PE_graphics::gameloop() {
	// Poll for user input.
	bool stillRunning = true;
	while (stillRunning) {

		SDL_Event event;
		while (SDL_PollEvent(&event)) {

			switch (event.type) {

			case SDL_QUIT:
				stillRunning = false;
				break;

			default:
				// Do nothing.
				break;
			}
		}

		SDL_Delay(10);
	}
}

void PE_graphics::cleanup() {

	vk_instance.destroySurfaceKHR(surface);
	SDL_DestroyWindow(main_window);
	SDL_Quit();
	vk_instance.destroy();

	slog("Polaris Closed");
}

void graphics_close();
void graphics_logical_device_close();
void graphics_extension_init();
void graphics_setup_debug();
void graphics_semephore_create();

