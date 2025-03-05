// /*
// * Polaris Engine
// *
// * Copyright (C) 2025 Michael Chervenak aka GitHub: Cherve3
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
// * 	Date: 03/05/2025
// * 	Time: 01:03:19
// */

#ifndef PE_GRAPHICS_H
#define PE_GRAPHICS_H

#include <vulkan/vulkan.hpp>

#include <SDL3/SDL.h>

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
#define VK_USE_PLATFORM_WIN32_KHR 1
#endif

inline constexpr bool DEBUG = true;

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
        sdl_init();
        vulkan_init();
        game_loop();
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
    vk::DebugUtilsMessengerEXT debug_callback = nullptr;
    
    bool logical_device_created = false;
    Uint32 device_count = 0;
    std::vector<VkPhysicalDevice> devices;
    vk::PhysicalDevice gpu = nullptr;
    
    vk::Device device = nullptr;
    vk::SurfaceKHR surface = nullptr;

    vk::Format color_format = vk::Format::eUndefined;
    vk::ColorSpaceKHR color_space = vk::ColorSpaceKHR::eSrgbNonlinear;

    vk::DeviceQueueCreateInfo* pQueueCreateInfo = nullptr;
    vk::PhysicalDeviceFeatures device_features {};

    vk::Semaphore image_available_semephore = nullptr;
    vk::Semaphore render_finished_semephore = nullptr;

    PE_Pipeline pPipe;

    //Command* graphicsCommandPool;
    //UniformBufferObject ubo;

    /**
     *	@brief Initializes SDL and creates a window to display the program.
     */
    void sdl_init();
    /**
     *	@brief Initializes everything necessary for Vulkan to operate.
     */
    void vulkan_init();
    /**
        @brief Specifies the application info.
    */
    void app_info();
    /**
        @brief Specifies the instance info.
    */
    void instance_info();
    /**
        @brief queries for validation layer properties.
    */
    void validation_init();
    /**
     *	@brief Enable validation layers.
     */
    void enable_layers();
    /**
     *	@brief get the gpu that the engine is going to use.
     */
    void gpu_setup();
    /**
     *	@brief select the gpu that will be used.
     */
    void gpu_select();
    /**
     *	@brief Initializes instance extensions.
     */
    void instance_extensions_init();
    /**
     *	@brief Initializes device extensions.
     */
    void device_extensions_init();
    /**
        @brief the main game loop.
    */
    void game_loop();
    /**
        @brief frees all the data to close the program cleanly.
    */
    void cleanup();
};

#endif
