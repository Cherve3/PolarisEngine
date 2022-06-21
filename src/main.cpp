/*
 * Polaris Engine
 *
 * Copyright (C) 2022 Cherve3
 * 
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/*
    Polaris Engine
*/

// Enable the WSI extensions
#if defined(__ANDROID__)
#define VK_USE_PLATFORM_ANDROID_KHR
#elif defined(__linux__)
#define VK_USE_PLATFORM_XLIB_KHR
#elif defined(_WIN32)
#define VK_USE_PLATFORM_WIN32_KHR
#endif

#include "PE_graphics.h"

int main(int argc, char* argv[])
{
    // Logger
    init_logger("Polaris.log");
    slog("Polaris Start");

    PeGraphics graphics;

    try {
        graphics.run();
    }
    catch (const std::exception& e) {
        slog(e.what());
        slog_sync();
        return EXIT_FAILURE;
    }
    catch (const vk::SystemError& err)
    {
        slog("vk::SystemError: %s", err.what());
        return EXIT_FAILURE;
    }
    catch (...)
    {
        slog("Unknown Error");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
