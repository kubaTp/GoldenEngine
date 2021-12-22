#pragma once

#include "utils/timer.h" // needs to be attached first to avoid errrors with windows.h
#include "utils/fileutils.h"
#include "utils/serializationservice.h"

#include "utils/resourceloader.h"
#include "usage/chief.h"

#include "maths/maths.h"

#include "graphics/window.h"
#include "graphics/shader.h"
#include "graphics/buffers/bufferpack.h"
#include "graphics/simple2Drenderer.h"
#include "graphics/batchrenderer2D.h"
#include "graphics/staticsprite.h"
#include "graphics/sprite.h"
#include "graphics/texture.h"
#include "graphics/layers/tilelayer.h"
#include "graphics/layers/group.h"
#include "graphics/label.h"
#include "graphics/fontmanager.h"

#include "sound/soundmanager.h"

#include "components/components_pack.h"

#ifdef PREDEFINED_MACROS

using rs = golden::ResourceLoader; // it's not a reference to RobertRS7
using lg = golden::Logger;
#define endl '\n'

#endif