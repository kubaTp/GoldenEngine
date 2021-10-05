#pragma once

#include "src/utils/timer.h" // needs to be attached first to avoid errrors with windows.h

#include "src/graphics/window.h"
#include "src/graphics/shader.h"
#include "src/maths/maths.h"
#include "src/utils/fileutils.h"

#include "src/graphics/buffers/bufferpack.h"

#include "src/graphics/simple2Drenderer.h"
#include "src/graphics/batchrenderer2D.h"

#include "src/graphics/staticsprite.h"
#include "src/graphics/sprite.h"
#include "src/graphics/texture.h"

#include "src/graphics/layers/tilelayer.h"
#include "src/graphics/layers/group.h"

#include "src/graphics/label.h"
#include "src/graphics/fontmanager.h"

#include "src/sound/soundmanager.h"

#include "src/utils/resourceloader.h"

#include "src/utils/chief.h"

#ifdef PREDEFINED_MACROS

using rs = golden::ResourceLoader;
using lg = golden::Logger; // it's not reference to RobertRS7
#define endl '\n'

#endif