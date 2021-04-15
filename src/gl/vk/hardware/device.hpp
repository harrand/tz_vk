#ifndef TOPAZ_GL_VK_HARDWARE_DEVICE_HPP
#define TOPAZ_GL_VK_HARDWARE_DEVICE_HPP
#if TZ_VULKAN
#include "gl/vk/common/basic_list.hpp"
#include "vulkan/vulkan.h"

namespace tz::gl::vk::hardware
{
    using DeviceProperties = VkPhysicalDeviceProperties;
    class Device
    {
    public:
        using List = tz::gl::vk::common::BasicList<Device>;
        static Device null();
        bool is_null() const;
        DeviceProperties get_properties() const;

        friend List get_all_devices(VkInstance instance);
    private:
        Device();
        Device(VkPhysicalDevice phys_dev);

        VkPhysicalDevice dev;
    };

    Device::List get_all_devices(VkInstance instance);
}

#endif // TZ_VULKAN
#endif // TOPAZ_GL_VK_HARDWARE_DEVICE_HPP