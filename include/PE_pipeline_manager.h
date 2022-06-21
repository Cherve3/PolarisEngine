#ifndef __PE_PIPELINE_MANAGER_H__
#define __PE_PIPELINE_MANAGER_H__

#include <SDL_vulkan.h>
#include <vulkan/vulkan.hpp>

#include "PE_pipeline.h"

class PePipelineManager
{
public:
    
private:
    std::vector<PePipeline> pipelineList;
    Uint32                  maxPipelines;
    Uint32                  chainLength;

    /*
     *  @brief creates the initial list of pipelines.
     *  max_pipelines - the max number of pipelines that can exist
     */
    void pipeline_manager_init(Uint32 max_pipelines);
    /*
     *  @brief creates a new pipeline
     */
    PePipeline* pipeline_new();
    /*
     *  @brief increases the max amount of pipelines available.
     */
    void max_pipeline_increase();
};

#endif