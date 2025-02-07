// /*
// * Polaris Engine
// *
// * Copyright (C) 2022 Michael Chervenak aka GitHub: Cherve3
// *
// *
// * Licensed under the Apache License, Version 2.0 (the "License");
// * you may not use this file except in compliance with the License.
// * You may obtain a copy of the License at
// *
// *     http://www.apache.org/licenses/LICENSE-2.0
// *
// * Unless required by applicable law or agreed to in writing, software
// * distributed under the License is distributed on an "AS IS" BASIS,
// * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// * See the License for the specific language governing permissions and
// * limitations under the License.
// */
// 
// /*
// * Project Name: PolarisEngine
// * File Created by: Michael Chervenak
// * File Name: PE_graphics.h
// * File Created:
// * 	Date: 01/30/2025
// * 	Time: 04:01:15
// * File Updated:
// * 	Date: 01/31/2025
// * 	Time: 08:01:15
// */

#ifndef PE_GRAPHICS_H
#define PE_GRAPHICS_H

#include <SDL.h>
#include <SDL_vulkan.h>
#include <vulkan/vulkan.hpp>

//#include "simple_logger.h"

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
#define VK_USE_PLATFORM_WIN32_KHR 1
#endif

#define VK_ASSERT_MSG(func, message)                \
{                                                   \
    const VkResult result = func;                   \
    if (result != VK_SUCCESS) {                     \
        slog("%s VK result: %s", message, result);  \
        assert(false);                              \
    }                                               \
}                                                   \

#define DEBUG 1

struct PE_Extensions
{
    uint32_t enabled_extension_count = 0;
    std::vector<const char*> enabled_extension_names;
    uint32_t available_extension_count = 0;
    std::vector<VkExtensionProperties> available_extensions;
};

struct PE_Validation
{
    uint32_t layer_count = 0;
    std::vector<VkLayerProperties> available_layers;
    std::vector<const char*> layer_names;
};

struct PE_Pipeline
{
    bool inUse = false;
    VkPipeline pipeline = nullptr;
    VkRenderPass renderPass = nullptr;
    VkPipelineLayout pipelineLayout = nullptr;
    size_t vertSize = 0;
    char* vertShader = nullptr;
    VkShaderModule vertModule = nullptr;
    size_t fragSize = 0;
    char* fragShader = nullptr;
    VkShaderModule fragModule = nullptr;
    VkDevice device = nullptr;
    Uint32* pDescriptorCursor = nullptr; /**<keeps track of which descriptors have been used per frame*/
    VkDescriptorPool* pDescriptorPool = nullptr;
    VkDescriptorSetLayout descriptorSetLayout = nullptr;
    VkDescriptorSet** descriptorSets = nullptr;
    Uint32 descriptorPoolCount = 0;
    Uint32 descriptorSetCount = 0;
};

class PeGraphics
{
public:
    /*
     *	@brief Runs the program.
     */
    void run()
    {
        sdlInit();
        vulkanInit();
        gameLoop();
        cleanup();
    }

private:
    SDL_Window* pMainWindow = nullptr;

    vk::ApplicationInfo vk_app_info;

    vk::Instance vk_instance;
    vk::InstanceCreateInfo vk_instance_info;

    PE_Validation validate;

    PE_Extensions instance_extensions;
    PE_Extensions device_extensions;

    uint32_t sdl_extension_count = 0;
    std::vector<std::string> sdl_extension_names;
    std::vector<std::string> layers;
    bool enable_validation_layers = false;
    VkDebugUtilsMessengerEXT debug_callback = nullptr;

    bool logical_device_created = false;
    Uint32 device_count = 0;
    std::vector<VkPhysicalDevice> devices;
    VkPhysicalDevice gpu = nullptr;

    VkDevice device = nullptr;
    VkSurfaceKHR surface = nullptr;

    VkFormat color_format = VK_FORMAT_UNDEFINED;
    VkColorSpaceKHR color_space = VK_COLOR_SPACE_SRGB_NONLINEAR_KHR;

    VkDeviceQueueCreateInfo* pQueueCreateInfo = nullptr;
    VkPhysicalDeviceFeatures device_features {};

    VkSemaphore image_available_semephore = nullptr;
    VkSemaphore render_finished_semephore = nullptr;

    PE_Pipeline pPipe;

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
