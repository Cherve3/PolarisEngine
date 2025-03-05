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
// * File Name: Utils.h
// * File Created:
// * 	Date: 02/14/2025
// * 	Time: 20:02:57
// * File Updated:
// * 	Date: 03/05/2025
// * 	Time: 01:03:19
// */

#pragma once

#include <vulkan/vulkan.hpp>
#include "simple_logger.h"

namespace Utils
{
    inline void vk_assert_msg(VkResult result, const char* message)
    {
        //const VkResult result = func();
        if (result != VK_SUCCESS) {
            slog("%s VK result: %s", message, result);
            assert(false);
        }
    }
};
