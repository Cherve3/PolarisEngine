#ifndef __PE_PIPELINE_H__
#define __PE_PIPELINE_H__

#include <SDL_vulkan.h>
#include <vulkan/vulkan.hpp>

#include "simple_logger.h"

class PePipeline
{
public:
    bool                    inUse;
private:
    
    VkPipeline              pipeline;
    VkRenderPass            renderPass;
    VkPipelineLayout        pipelineLayout;
    size_t                  vertSize;
    char*                   vertShader;
    VkShaderModule          vertModule;
    size_t                  fragSize;
    char*                   fragShader;
    VkShaderModule          fragModule;
    VkDevice                device;
    Uint32*                 pDescriptorCursor;       /**<keeps track of which descriptors have been used per frame*/
    VkDescriptorPool*       pDescriptorPool;
    VkDescriptorSetLayout   descriptorSetLayout;
    VkDescriptorSet**       descriptorSets;
    Uint32                  descriptorPoolCount;
    Uint32                  descriptorSetCount;

    void pipeline_init();
};

#endif