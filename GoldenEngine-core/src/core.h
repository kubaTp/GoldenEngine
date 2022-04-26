#pragma once

#include "utils/projectutils.h"           // needs to be attached first to avoid errrors with windows.h
#include "utils/timer.h" 
#include "utils/fileutils.h"
#include "utils/serializationservice.h"

#include "utils/resourceloader.h"
#include "utils/assert.h"
#include "usage/chief.h"

#include "maths/maths.h"
#include <glm/glm.hpp>

#include "graphics/window.h"
#include "graphics/shader.h"
#include "graphics/buffers/bufferpack.h"
#include "graphics/renderers/simple2Drenderer.h"
#include "graphics/renderers/batchrenderer2D.h"
#include "graphics/renderables/staticsprite.h"
#include "graphics/renderables/sprite.h"
#include "graphics/texture.h"
#include "graphics/layers/tilelayer.h"
#include "graphics/layers/group.h"
#include "graphics/scenes/scene.h"
#include "graphics/UI/label.h"
#include "graphics/UI/fontmanager.h"

#include "sound/soundmanager.h"

#include "graphics/camera.h"

#ifdef PREDEFINED_MACROS

using rs = golden::ResourceLoader; // it's not a reference to RobertRS7
using lg = golden::Logger;
#define endl '\n'

#endif