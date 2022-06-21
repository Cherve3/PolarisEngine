
#include <string.h>
#include <stdio.h>

#include "PE_graphics.h"


void PeGraphics::sdlInit() {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		slog("Could not initialize SDL.");
	}
	else {
		slog("SDL initialized");
	}

	pMainWindow = SDL_CreateWindow(
		"Polaris Engine",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		1280,
		720,
		SDL_WINDOW_VULKAN);

	if (pMainWindow == nullptr) {
		slog("Could not create SDL window.");
	}
	else {
		slog("SDL window created");
	}
}


void PeGraphics::vulkanInit() {

	appInfo();
	instanceExtensionsInit();
	validationInit();
	enableLayers();
	instanceInfo();
	
	
	try {
		vk_instance = vk::createInstance(vk_instance_info);
	}
	catch (const std::exception& e) {
		slog("Could not create a Vulkan instance : %s", e.what());
	}

	if (!SDL_Vulkan_CreateSurface(pMainWindow, static_cast<VkInstance>(vk_instance), &surface)) {
		slog("Could not create a Vulkan surface.");
	}
	gpuSetup();
	deviceExtensionsInit();
}

void PeGraphics::gameLoop() {
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

void PeGraphics::cleanup() {
	slog("Cleaning up...");
	vk_instance.destroySurfaceKHR(surface);
	SDL_DestroyWindow(pMainWindow);
	SDL_Quit();
	vk_instance.destroy();

	slog("Polaris Closed");
}
// TODO: deallocate vectors at close or error.

void PeGraphics::appInfo()
{
	vk_app_info = vk::ApplicationInfo()
		.setPApplicationName("Polaris Engine")
		.setApplicationVersion(VK_MAKE_API_VERSION(0, 1, 0, 0))
		.setPEngineName("Polaris Engine")
		.setEngineVersion(VK_MAKE_API_VERSION(0, 1, 0, 0))
		.setApiVersion(VK_API_VERSION_1_3);
}

void PeGraphics::instanceExtensionsInit()
{
	vkEnumerateInstanceExtensionProperties(
		nullptr,
		&instance_extensions.available_extension_count,
		nullptr);
	slog("Total available instance extensions: %i", instance_extensions.available_extension_count);
	if (!instance_extensions.available_extension_count)
	{
		slog("Error: available extensions is 0");
		return;
	}
	instance_extensions.available_extensions.resize(instance_extensions.available_extension_count);
	vkEnumerateInstanceExtensionProperties(
		nullptr,
		&instance_extensions.available_extension_count,
		instance_extensions.available_extensions.data());

	slog("Available instance extensions: ");
	for (const auto& i : instance_extensions.available_extensions)
	{
		instance_extensions.enabled_extension_names.push_back(i.extensionName);
		slog("%s", i.extensionName);
	}
}

void PeGraphics::deviceExtensionsInit()
{
	vkEnumerateDeviceExtensionProperties(
		gpu,
		nullptr,
		&device_extensions.available_extension_count,
		nullptr);
	slog("Total available device extensions: %i", device_extensions.available_extension_count);
	if (!device_extensions.available_extension_count) return;

	device_extensions.available_extensions.resize(device_extensions.available_extension_count);
	if (!device_extensions.available_extensions.data()) return;

	vkEnumerateDeviceExtensionProperties(
		gpu,
		nullptr,
		&device_extensions.available_extension_count,
		device_extensions.available_extensions.data());

	//device_extensions.enabled_extension_names.resize(device_extensions.available_extension_count);
	for (const auto& i : device_extensions.available_extensions)
	{
		device_extensions.enabled_extension_names.push_back(i.extensionName);
		slog("%s", i.extensionName);
	}
}

void PeGraphics::instanceInfo()
{
	vk_instance_info = vk::InstanceCreateInfo()
		.setFlags(vk::InstanceCreateFlags())
		.setPApplicationInfo(&vk_app_info)
		.setEnabledExtensionCount(instance_extensions.available_extension_count)
		.setPpEnabledExtensionNames(instance_extensions.enabled_extension_names.data())
		.setEnabledLayerCount(validate.layer_count)
		.setPpEnabledLayerNames(validate.layer_names.data());
}

void PeGraphics::validationInit()
{
	vkEnumerateInstanceLayerProperties(&validate.layer_count, NULL);
	slog("discovered %i validation layers", validate.layer_count);

	if (!validate.layer_count) return;

	validate.available_layers.resize(validate.layer_count);
	validate.layer_names.resize(validate.layer_count);
	vkEnumerateInstanceLayerProperties(&validate.layer_count, validate.available_layers.data());

	slog("available validation layers:");
	for (int i = 0; i < validate.layer_count; ++i)
	{
		validate.layer_names[i] = validate.available_layers[i].layerName;
		slog("%s", validate.layer_names[i]);
	}
}

void PeGraphics::enableLayers()
{
	if (_DEBUG)
	{
		validate.layer_count++;
		validate.layer_names.push_back("VK_LAYER_KHRONOS_validation");
		slog("added %s to layers", validate.layer_names[validate.layer_count - 1]);
	}
}

void PeGraphics::gpuSetup()
{
	vkEnumeratePhysicalDevices(
		vk_instance,
		&device_count,
		nullptr);
	slog("There are %i device(s) available.",device_count);
	if (!device_count)
	{
		slog("Failed to create a vulkan instance: cannot find gpu with Vulkan support.");
		//TODO: Close
		return;
	}
	devices.resize(device_count);
	vkEnumeratePhysicalDevices(vk_instance, &device_count, devices.data());
	
	for (auto& device : devices)
		slog("%s", device);
		
	gpuSelect();
}

void PeGraphics::gpuSelect()
{
	gpu = devices[0];
}
void graphics_setup_debug();
void graphics_semephore_create();

