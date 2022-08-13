/*
 * Copyright (c) Contributors to the Open 3D Engine Project.
 * For complete copyright and license terms please see the LICENSE at the root of this distribution.
 *
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */

#pragma once

#include <AzCore/Component/Component.h>
#include <AzCore/Component/TickBus.h>
#include <AzCore/std/smart_ptr/unique_ptr.h>
#include <AzCore/Asset/AssetManager.h>
#include <MiniAudio/miniaudio.h>
#include <MiniAudio/MiniAudioBus.h>

namespace MiniAudio
{
    class MiniAudioSystemComponent
        : public AZ::Component
        , public MiniAudioRequestBus::Handler
    {
    public:
        AZ_COMPONENT(MiniAudioSystemComponent, "{9F15877E-3FC6-4479-867F-A31883DFC945}");

        static void Reflect(AZ::ReflectContext* context);

        static void GetProvidedServices(AZ::ComponentDescriptor::DependencyArrayType& provided);
        static void GetIncompatibleServices(AZ::ComponentDescriptor::DependencyArrayType& incompatible);
        static void GetRequiredServices(AZ::ComponentDescriptor::DependencyArrayType& required);
        static void GetDependentServices(AZ::ComponentDescriptor::DependencyArrayType& dependent);

        MiniAudioSystemComponent();
        MiniAudioSystemComponent(const MiniAudioSystemComponent&) = delete;
        MiniAudioSystemComponent& operator=(const MiniAudioSystemComponent&) = delete;
        ~MiniAudioSystemComponent();

        // AZ::Component interface implementation
        void Init() override;
        void Activate() override;
        void Deactivate() override;

        // MiniAudioRequestBus
        ma_engine* GetSoundEngine() override;

    private:
        ma_engine m_engine;

        // Assets related data
        AZStd::vector<AZStd::unique_ptr<AZ::Data::AssetHandler>> m_assetHandlers;
    };

} // namespace MiniAudio
