#ifndef __PE_EXTENSIONS_H__
#define __PE_EXTENSIONS_H__

#include <vulkan/vulkan.hpp>

class PeExtension
{
public:

	uint32_t							enabled_extension_count;
	std::vector<const char*>			enabled_extension_names;

	uint32_t							available_extension_count;
	std::vector <VkExtensionProperties>	available_extensions;

private:
	

};


#endif
