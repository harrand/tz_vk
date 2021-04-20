#ifndef TOPAZ_GL_VK_RENDER_PASS_HPP
#define TOPAZ_GL_VK_RENDER_PASS_HPP
#if TZ_VULKAN
#include "gl/vk/attachment.hpp"
#include "gl/vk/impl/setup/logical_device.hpp"
#include <vector>
#include <cstdint>
#include <optional>
#include <span>

namespace tz::gl::vk
{

    class RenderSubpass;

    class RenderPassBuilder
    {
    public:
        using AttachmentID = std::size_t;
        using SubpassID = std::size_t;

        RenderPassBuilder();
        template<typename... Args>
        RenderPassBuilder& with(Args&&... args);

        std::span<const Attachment* const> get_attachments() const;
        std::span<const RenderSubpass> get_subpasses() const;

        friend class RenderSubpass;
    private:
        std::vector<const Attachment*> subpass_attachments;
        std::vector<RenderSubpass> subpasses;
    };

    using Attachments = std::initializer_list<Attachment>;

    class RenderSubpass
    {
    public:

        struct Description
        {
            Description() = default;
            Description(const Description& copy);
            Description(Description&& move);
            std::vector<VkAttachmentReference> referenced_input_attachments;
            std::vector<VkAttachmentReference> referenced_colour_attachments;
            std::optional<VkAttachmentReference> referenced_depth_stencil_attachments;
            std::vector<std::uint32_t> referenced_preserved_attachments;
            VkSubpassDescription vk = {};

            void update_description();
        };

        RenderSubpass(RenderPassBuilder& parent, Attachments attachments);
        Description describe() const;
    private:
        std::size_t get_attachment_id(const Attachment& attachment) const;

        RenderPassBuilder* parent;
        std::vector<Attachment> attachments;
        std::size_t attachments_offset;
    };

    class RenderPass
    {
    public:
        RenderPass(const LogicalDevice& device, RenderPassBuilder builder);
        RenderPass(const RenderPass& copy) = delete;
        RenderPass(RenderPass&& move);
        ~RenderPass();

        RenderPass& operator=(const RenderPass& rhs) = delete;
        RenderPass& operator=(RenderPass&& rhs);
    private:
        VkRenderPass render_pass;
        const LogicalDevice* device;
    };
}

#include "gl/vk/render_pass.inl"
#endif // TZ_VULKAN
#endif // TOPAZ_GL_VK_RENDER_PASS_HPP