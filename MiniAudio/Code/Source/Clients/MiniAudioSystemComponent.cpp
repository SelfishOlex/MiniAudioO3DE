/*
 * Copyright (c) Contributors to the Open 3D Engine Project.
 * For complete copyright and license terms please see the LICENSE at the root of this distribution.
 *
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */

#include "MiniAudioSystemComponent.h"

#include <AzCore/Serialization/EditContext.h>
#include <MiniAudio/SoundAsset.h>

#include "SoundAssetHandler.h"

namespace MiniAudio
{
    void MiniAudioSystemComponent::Reflect(AZ::ReflectContext* context)
    {
        SoundAsset::Reflect(context);

        if (AZ::SerializeContext* serialize = azrtti_cast<AZ::SerializeContext*>(context))
        {
            serialize->Class<MiniAudioSystemComponent, AZ::Component>()
                ->Version(0)
                ;

            if (AZ::EditContext* ec = serialize->GetEditContext())
            {
                ec->Class<MiniAudioSystemComponent>("MiniAudio", "[Description of functionality provided by this System Component]")
                    ->ClassElement(AZ::Edit::ClassElements::EditorData, "")
                        ->Attribute(AZ::Edit::Attributes::AppearsInAddComponentMenu, AZ_CRC("System"))
                        ->Attribute(AZ::Edit::Attributes::AutoExpand, true)
                    ;
            }
        }
    }

    void MiniAudioSystemComponent::GetProvidedServices(AZ::ComponentDescriptor::DependencyArrayType& provided)
    {
        provided.push_back(AZ_CRC_CE("MiniAudioService"));
    }

    void MiniAudioSystemComponent::GetIncompatibleServices(AZ::ComponentDescriptor::DependencyArrayType& incompatible)
    {
        incompatible.push_back(AZ_CRC_CE("MiniAudioService"));
    }

    void MiniAudioSystemComponent::GetRequiredServices([[maybe_unused]] AZ::ComponentDescriptor::DependencyArrayType& required)
    {
    }

    void MiniAudioSystemComponent::GetDependentServices([[maybe_unused]] AZ::ComponentDescriptor::DependencyArrayType& dependent)
    {
    }

    MiniAudioSystemComponent::MiniAudioSystemComponent()
    {
        if (MiniAudioInterface::Get() == nullptr)
        {
            MiniAudioInterface::Register(this);
        }
    }

    MiniAudioSystemComponent::~MiniAudioSystemComponent()
    {
        if (MiniAudioInterface::Get() == this)
        {
            MiniAudioInterface::Unregister(this);
        }
    }

    void MiniAudioSystemComponent::Init()
    {
    }

    void MiniAudioSystemComponent::Activate()
    {
        const ma_result result = ma_engine_init(nullptr, &m_engine);
        if (result != MA_SUCCESS)
        {
            AZ_Error("MiniAudio", false, "Failed to initialize audio engine, error %d", result);
        }

        MiniAudioRequestBus::Handler::BusConnect();

        {
            SoundAssetHandler* handler = aznew SoundAssetHandler();
            AZ::Data::AssetCatalogRequestBus::Broadcast(&AZ::Data::AssetCatalogRequests::EnableCatalogForAsset, AZ::AzTypeInfo<SoundAsset>::Uuid());
            AZ::Data::AssetCatalogRequestBus::Broadcast(&AZ::Data::AssetCatalogRequests::AddExtension, SoundAsset::FileExtension);
            m_assetHandlers.emplace_back(handler);
        }
    }

    void MiniAudioSystemComponent::Deactivate()
    {
        m_assetHandlers.clear();
        ma_engine_uninit(&m_engine);

        MiniAudioRequestBus::Handler::BusDisconnect();
    }

    ma_engine* MiniAudioSystemComponent::GetSoundEngine()
    {
        return &m_engine;
    }

    void MiniAudioSystemComponent::SetGlobalVolume(float scale)
    {
        m_globalVolume = scale;
        ma_engine_set_volume(&m_engine, m_globalVolume);
    }

    float MiniAudioSystemComponent::GetGlobalVolume() const
    {
        return m_globalVolume;
    }

    void MiniAudioSystemComponent::SetGlobalVolumeInDecibels(float decibels)
    {
        m_globalVolume = ma_volume_db_to_linear(decibels);
        SetGlobalVolume(m_globalVolume);
    }
} // namespace MiniAudio
