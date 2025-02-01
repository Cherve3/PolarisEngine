﻿// /*
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
// * File Name: main.h
// * File Created:
// * 	Date: 01/31/2025
// * 	Time: 08:01:42
// * File Updated:
// * 	Date: 01/31/2025
// * 	Time: 08:01:42
// */

#pragma once

#if defined(_WIN32)
#define VK_USE_PLATFORM_WIN32_KHR
#endif
#if defined(_WIN64)
#define VK_USE_PLATFORM_WIN64_KHR
#endif

#define VK_ASSERT_MSG(func, message)\
{                                   \
    const VkResult result = func;   \
    if (result != VK_SUCCESS) {     \
        slog(message);              \
        assert(false);              \
    }                               \
}

class main
{
};
