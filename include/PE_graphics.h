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

#pragma once

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
    void run()
    {
        sdlInit();
        vulkanInit();
        gameLoop();
        cleanup();
    }

private:
    SDL_Window* pMainWindow;

    vk::ApplicationInfo vk_app_info;

    vk::Instance vk_instance;
    vk::InstanceCreateInfo vk_instance_info;

    PeValidation validate;

    PeExtension instance_extensions;
    PeExtension device_extensions;

    uint32_t sdl_extension_count;
    std::vector<const char*> sdl_extension_names;
    std::vector<const char*> layers;
    bool enable_validation_layers;
    VkDebugUtilsMessengerEXT debug_callback;

    bool logical_device_created;
    Uint32 device_count;
    std::vector<VkPhysicalDevice> devices;
    VkPhysicalDevice gpu;

    VkDevice device;
    VkSurfaceKHR surface;

    VkFormat color_format;
    VkColorSpaceKHR color_space;

    VkDeviceQueueCreateInfo* pQueueCreateInfo;
    VkPhysicalDeviceFeatures device_features;

    VkSemaphore image_available_semephore;
    VkSemaphore render_finished_semephore;

    PePipeline* pPipe;

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
