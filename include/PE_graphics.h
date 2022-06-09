#pragma once
#include <SDL.h>
#include <SDL_vulkan.h>
#include <vulkan/vulkan.hpp>

#include "simple_logger.h"

class PE_graphics
{
	
public:

	void run() {
		SDL_init();
		vulkan_init();
		gameloop();
		cleanup();
	}

private:

	SDL_Window* main_window;

	vk::ApplicationInfo vk_app_info;

	vk::Instance vk_instance;
	vk::InstanceCreateInfo vk_instance_info;
	
	Uint32 device_count;
	VkPhysicalDevice* devices;
	VkPhysicalDevice gpu;
	bool logical_device_created;

	VkDevice device;
	VkSurfaceKHR surface;

	VkFormat color_format;
	VkColorSpaceKHR color_space;

	VkDeviceQueueCreateInfo* queue_create_info;
	VkPhysicalDeviceFeatures device_features;

	VkSemaphore image_available_semephore;
	VkSemaphore render_finished_semephore;


	//Pipeline* pipe;

	//Command* graphicsCommandPool;
	//UniformBufferObject ubo;


	void SDL_init();

	void vulkan_init();

	void gameloop();

	void cleanup();
	
};