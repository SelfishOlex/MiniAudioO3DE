/*
 * Copyright (c) Contributors to the Open 3D Engine Project.
 * For complete copyright and license terms please see the LICENSE at the root of this distribution.
 *
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */

#define STB_VORBIS_HEADER_ONLY
#include <MiniAudio/stb_vorbis.c>    // Enables Vorbis decoding.

#define MINIAUDIO_IMPLEMENTATION
#include <MiniAudio/miniaudio.h>

// The stb_vorbis implementation must come after the implementation of miniaudio.
#undef STB_VORBIS_HEADER_ONLY
#include <MiniAudio/stb_vorbis.c>
