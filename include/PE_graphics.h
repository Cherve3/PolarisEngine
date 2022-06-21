#ifndef __PE_GRAPHICS_H__
#define __PE_GRAPHICS_H__

#include <SDL.h>
#include <SDL_vulkan.h>
#include <vulkan/vulkan.hpp>

#include "PE_pipeline.h"
#include "PE_extensions.h"
#include "PE_validation.h"

#define _DEBUG 1

class PeGraphics
{
	
public:

	/*
	 *	@brief Runs the program.
	 */
	void run() {
		sdlInit();
		vulkanInit();
		gameLoop();
		cleanup();
	}

private:

	SDL_Window*						pMainWindow;

	vk::ApplicationInfo				vk_app_info;

	vk::Instance					vk_instance;
	vk::InstanceCreateInfo			vk_instance_info;
	
	PeValidation					validate;

	PeExtension						instance_extensions;
	PeExtension						device_extensions;

	uint32_t						sdl_extension_count;
	std::vector<const char*>		sdl_extension_names;
	std::vector<const char*>		layers;
	bool							enable_validation_layers;
	VkDebugUtilsMessengerEXT		debug_callback;
	
	bool							logical_device_created;
	Uint32							device_count;
	std::vector <VkPhysicalDevice>	devices;
	VkPhysicalDevice				gpu;

	VkDevice						device;
	VkSurfaceKHR					surface;

	VkFormat						color_format;
	VkColorSpaceKHR					color_space;

	VkDeviceQueueCreateInfo*		pQueueCreateInfo;
	VkPhysicalDeviceFeatures		device_features;

	VkSemaphore						image_available_semephore;
	VkSemaphore						render_finished_semephore;

	PePipeline*						pPipe;

	//Command* graphicsCommandPool;
	//UniformBufferObject ubo;

	/**
	 *	@brief Initializes SDL and creates a window to display the program.
	 */
	void sdlInit();
	/**
	 *	@brief Initializes everything necessary for Vulkan to operate.
	 */
	void vulkanInit();
	/**
		@brief Specifies the application info.
	*/
	void appInfo();
	/**
		@brief Specifies the instance info.
	*/
	void instanceInfo();
	/**
		@brief queries for validation layer properties.
	*/
	void validationInit();
	/**
	 *	@brief Enable validation layers.
	 */
	void enableLayers();
	/**
	 *	@brief get the gpu that the engine is going to use.
	 */
	void gpuSetup();
	/**
	 *	@brief select the gpu that will be used.
	 */
	void gpuSelect();
	/**
	 *	@brief Initializes instance extensions.
	 */
	void instanceExtensionsInit();
	/**
	 *	@brief Initializes device extensions.
	 */
	void deviceExtensionsInit();
	/**
		@brief the main game loop.
	*/
	void gameLoop();
	/**
		@brief frees all the data to close the program cleanly.
	*/
	void cleanup();
	
};

#endif