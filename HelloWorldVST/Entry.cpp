#include "Controller.h"
#include "Processor.h"
#include "Config.h"

#include "public.sdk/source/main/pluginfactoryvst3.h"

#define stringPluginName "Hello World VST3"

// Called after dll load
bool InitModule()
{
	return true;
}

// Called before dll unload
bool DeinitModule()
{
	return true;
}

using namespace Steinberg::Vst;

// Factory definition
// Describes which classes comprise this plugin
BEGIN_FACTORY_DEF("CompanyGoesHere", "WebsiteGoesHere", "EmailGoesHere")

	DEF_CLASS2(INLINE_UID_FROM_FUID(ProcessorUid),
		PClassInfo::kManyInstances,
		kVstAudioEffectClass,
		stringPluginName " Processor",
		Vst::kDistributable,
		PluginType,
		VERSION,
		kVstVersionString,
		::Processor::createInstance)

	DEF_CLASS2(INLINE_UID_FROM_FUID(ControllerUid),
		PClassInfo::kManyInstances,
		kVstComponentControllerClass,
		stringPluginName " Controller",
		0, // Component flags (not relevant here)
		"", // Plugin type (not relevant here)
		VERSION,
		kVstVersionString,
		::Controller::createInstance)

END_FACTORY
