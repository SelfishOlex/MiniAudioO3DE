/*
 * Copyright (c) Contributors to the Open 3D Engine Project.
 * For complete copyright and license terms please see the LICENSE at the root of this distribution.
 *
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */

#include <AzCore/Memory/SystemAllocator.h>
#include <AzCore/Module/Module.h>
#include <Clients/MiniAudioListenerComponent.h>
#include <Clients/MiniAudioPlaybackComponent.h>
#include <Clients/MiniAudioSystemComponent.h>

namespace MiniAudio
{
    class MiniAudioModuleInterface
        : public AZ::Module
    {
    public:
        AZ_RTTI(MiniAudioModuleInterface, "{290D3CED-B418-46E5-88A4-69EBF7DFC32C}", AZ::Module);
        AZ_CLASS_ALLOCATOR(MiniAudioModuleInterface, AZ::SystemAllocator, 0);

        MiniAudioModuleInterface()
        {
            // Push results of [MyComponent]::CreateDescriptor() into m_descriptors here.
            // Add ALL components descriptors associated with this gem to m_descriptors.
            // This will associate the AzTypeInfo information for the components with the the SerializeContext, BehaviorContext and EditContext.
            // This happens through the [MyComponent]::Reflect() function.
            m_descriptors.insert(m_descriptors.end(), {
                MiniAudioSystemComponent::CreateDescriptor(),
                MiniAudioPlaybackComponent::CreateDescriptor(),
                MiniAudioListenerComponent::CreateDescriptor(),
                });
        }

        /**
         * Add required SystemComponents to the SystemEntity.
         */
        AZ::ComponentTypeList GetRequiredSystemComponents() const override
        {
            return AZ::ComponentTypeList{
                azrtti_typeid<MiniAudioSystemComponent>(),
            };
        }
    };
}// namespace MiniAudio
