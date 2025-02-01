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
// * File Name: PE_pipeline.h
// * File Created:
// * 	Date: 01/30/2025
// * 	Time: 04:01:15
// * File Updated:
// * 	Date: 01/31/2025
// * 	Time: 08:01:15
// */

#pragma once

#include <SDL_vulkan.h>
#include <vulkan/vulkan.hpp>

#include "simple_logger.h"

class PePipeline
{
public:
    bool inUse;

private:
    VkPipeline pipeline;
    VkRenderPass renderPass;
    VkPipelineLayout pipelineLayout;
    size_t vertSize;
    char* vertShader;
    VkShaderModule vertModule;
    size_t fragSize;
    char* fragShader;
    VkShaderModule fragModule;
    VkDevice device;
    Uint32* pDescriptorCursor; /**<keeps track of which descriptors have been used per frame*/
    VkDescriptorPool* pDescriptorPool;
    VkDescriptorSetLayout descriptorSetLayout;
    VkDescriptorSet** descriptorSets;
    Uint32 descriptorPoolCount;
    Uint32 descriptorSetCount;

    void pipeline_init();
};
