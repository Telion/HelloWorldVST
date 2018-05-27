#pragma once

#include "pluginterfaces/base/funknown.h"

namespace Steinberg {
namespace Vst {

// Our version number
#define VERSION "0.0.1"

// Which kind of plugin is this
#define PluginType "Fx"

// List of all class identifiers plus forward declarations.
static const FUID ControllerUid = FUID(0xFEDCBA98, 0xEDCBA987, 0xDCBA9876, 0xCBA98765);
class Controller;

static const FUID ProcessorUid = FUID(0x12345678, 0x23456789, 0x3456789A, 0x456789AB);
class Processor;

}
}