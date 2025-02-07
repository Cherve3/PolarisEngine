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
// * File Name: PE_pipeline_manager.cpp
// * File Created:
// * 	Date: 01/30/2025
// * 	Time: 04:01:15
// * File Updated:
// * 	Date: 01/31/2025
// * 	Time: 08:01:15
// */

#include "PE_pipeline_manager.h"

#include "PE_graphics.h"

void PePipelineManager::pipeline_manager_init(Uint32 max_pipelines)
{
    if (max_pipelines == 0)
    {
        slog("cannot initialize zero pipelines");
        return;
    }
    maxPipelines = max_pipelines;

    PE_Pipeline* pipe;
    for (int i = 0; i < max_pipelines; ++i)
        pipelineList.push_back(pipe);

    chainLength = 0;
    slog("pipeline manager created with chain length %i", chainLength);
    slog("Pipeline Manager Initialized");
}

void PePipelineManager::max_pipeline_increase()
{
}

PE_Pipeline* PePipelineManager::pipeline_new()
{
    for (int i = 0; i < maxPipelines; ++i)
    {
        if (pipelineList.at(i)->inUse) continue;
        return pipelineList.at(i);
    }


    return nullptr;
}
