#include "Rendering/PresentationObjects.h"

namespace Firefly {
namespace Rendering {
namespace Presentation {

void CreateImage(VkImage& target) {
}

void CreateImageView(VkDevice device, VkImage source, VkFormat format,
                     VkImageAspectFlagBits aspect_mask, VkImageView& target) {
    VkImageViewCreateInfo create_info       = {VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO};
    create_info.image                       = source;
    create_info.viewType                    = VK_IMAGE_VIEW_TYPE_2D;
    create_info.format                      = format;
    create_info.subresourceRange.aspectMask = aspect_mask;
    create_info.subresourceRange.baseArrayLayer = 0;
    create_info.subresourceRange.levelCount     = 1;
    create_info.subresourceRange.layerCount     = 1;

    VK_ASSERT(vkCreateImageView(device, &create_info, nullptr, &target),
              "Failed to create Image View.");
}

void CreateAttachment(VkDevice device, VkImage* source, VkFormat format,
                      VkImageUsageFlagBits usage_flag, FramebufferAttachment& target) {
    VkImageAspectFlagBits aspect_mask = VK_IMAGE_ASPECT_FLAG_BITS_MAX_ENUM;
    VkImageLayout         img_layout;

    target.Format = format;
    if (usage_flag & VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT) {
        aspect_mask = VK_IMAGE_ASPECT_COLOR_BIT;
        img_layout  = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
    }
    if (usage_flag & VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT) {
        aspect_mask = VK_IMAGE_ASPECT_DEPTH_BIT;
        img_layout  = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
    }

    FFLY_ASSERT((aspect_mask < VK_IMAGE_ASPECT_FLAG_BITS_MAX_ENUM),
                "Attachment usage not supported");

    /* Use swapchain image */
    if (source != nullptr) {
        target.Image = *source;
    }
    /* Use custom image */
    else {
        CreateImage(target.Image);
    }

    CreateImageView(device, *source, format, aspect_mask, target.View);
}

void CreateFramebuffer(VkDevice device, VkRenderPass renderpass, VkExtent2D extent,
                       FramebufferAttachment color_attachment,
                       FramebufferAttachment depth_attachment, Framebuffer& target) {
    target.Color      = color_attachment;
    target.Depth      = depth_attachment;
    target.Width      = extent.width;
    target.Height     = extent.height;
    target.RenderPass = renderpass;

    std::array<VkImageView, 1> attachments = {target.Color.View}; //,target.Depth.View};

    VkFramebufferCreateInfo create_info = {VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO};
    create_info.renderPass              = target.RenderPass;
    create_info.attachmentCount         = static_cast<uint32>(attachments.size());
    create_info.pAttachments            = attachments.data();
    create_info.width                   = target.Width;
    create_info.height                  = target.Height;
    create_info.layers                  = 1;

    VK_ASSERT(vkCreateFramebuffer(device, &create_info, nullptr, &target.Framebuffer),
              "Failed to create Framebuffer.");
}

} // namespace Presentation
} // namespace Rendering
} // namespace Firefly