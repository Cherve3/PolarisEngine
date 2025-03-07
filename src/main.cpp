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
// * File Name: main.cpp
// * File Created:
// * 	Date: 01/31/2025
// * 	Time: 09:01:08
// * File Updated:
// * 	Date: 03/05/2025
// * 	Time: 01:03:19
// */

#include "PE_graphics.h"

#include "simple_logger.h"

int main(int argc, char* argv[])
{
    // Logger
    init_logger("Polaris.log", false);
    slog("Polaris Engine Start");

    try
    {
        PeGraphics graphics;
        graphics.run();
    }
    catch (const vk::SystemError& err)
    {
        slog("vk::SystemError: %s", err.what());
        slog_sync();
        return EXIT_FAILURE;
    }
    catch (const std::exception& e)
    {
        slog(e.what());
        slog_sync();
        return EXIT_FAILURE;
    }
    catch (...)
    {
        slog("Unknown Error");
        slog_sync();
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
