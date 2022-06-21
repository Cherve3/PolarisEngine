#include "PE_pipeline_manager.h"

void PePipelineManager::pipeline_manager_init(Uint32 max_pipelines)
{
	if (max_pipelines == 0)
	{
		slog("cannot initialize zero pipelines");
		return;
	}
	maxPipelines = max_pipelines;

	PePipeline pipe;
	for (int i = 0; i < max_pipelines; ++i)
		pipelineList.push_back(pipe);

	chainLength = 0;
	slog("pipeline manager created with chain length %i", chainLength);
	slog("Pipeline System Initialized");
}

void PePipelineManager::max_pipeline_increase()
{

}

PePipeline* PePipelineManager::pipeline_new()
{
	for (int i = 0; i < maxPipelines; ++i)
	{
		if (pipelineList.at(i).inUse) continue;
		return &pipelineList.at(i);
	}

	
	return NULL;
}

