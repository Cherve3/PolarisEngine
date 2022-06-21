#ifndef __PE__VALIDATION_H__
#define __PE__VALIDATION_H__

#include <vulkan/vulkan.hpp>

class PeValidation
{
public:
	uint32_t layer_count;
	std::vector<VkLayerProperties> available_layers;
	std::vector<const char*> layer_names;

private:
	
	
	
};


#endif
