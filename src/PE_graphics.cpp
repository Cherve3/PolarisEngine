
#include <SDL.h>
#include <SDL_vulkan.h>
#include <vulkan/vulkan.hpp>

#include <string.h>
#include <stdio.h>

typedef struct
{
	SDL_Window* main_window;

	VkApplicationInfo vk_app_info;

	VkInstance vk_instance;
	VkInstanceCreateInfo vk_instance_info;

	Uint32 device_count;
	VkPhysicalDevice* devices;
	VkPhysicalDevice gpu;
	bool logicalDeviceCreated;

	VkDevice device;
	VkSurfaceKHR surface;

	VkFormat color_format;
	VkColorSpaceKHR color_space;

	VkDeviceQueueCreateInfo* queueCreateInfo;
	VkPhysicalDeviceFeatures deviceFeatures;

	VkSemaphore imageAvailableSemephore;
	VkSemaphore renderFinishedSemephore;

	
	//Pipeline* pipe;
	
	//Command* graphicsCommandPool;
	//UniformBufferObject ubo;
}Graphics;


static Graphics graphics = { 0 };

void graphics_close();
void graphics_logical_device_close();
void graphics_extension_init();
void graphics_setup_debug();
void graphics_semephore_create();

