#pragma once

#include "vstgui/plugin-bindings/vst3editor.h"
#include "base/source/fstreamer.h"

using namespace Steinberg;
using namespace Steinberg::Vst;

// The controller is the UI portion of the plugin.
// It can set parameters, but it does not directly process any audio.
class Controller : public EditController
{
public:
	// The host calls this to create an instance (see Entry.cpp)
	static FUnknown* createInstance(void*)
	{
		return (IEditController*)new Controller();
	}

	// Initializes the instance
	tresult PLUGIN_API initialize(FUnknown* context) SMTG_OVERRIDE
	{
		tresult result = EditController::initialize(context);
		if (result != kResultTrue)
		{
			return result;
		}

		return kResultTrue;
	}

	// Teardown before the destructor is called
	tresult PLUGIN_API terminate()
	{
		return EditController::terminate();
	}

	// Sets our GUI state to match the current Processor state
	tresult PLUGIN_API setComponentState(IBStream* state) SMTG_OVERRIDE
	{
		if (!state)
			return kResultFalse;

		IBStreamer streamer(state, kLittleEndian);

		return kResultTrue;
	}

	// Creates our GUI
	IPlugView* PLUGIN_API createView(const char* name) SMTG_OVERRIDE
	{
		if (name == std::string("editor"))
		{
			// You will get a black screen if pathToXml is not valid.
			VST3Editor* view = new VST3Editor(this, "view", "pathToXml");
			return view;
		}
		return nullptr;
	}

	// Write all of our model state into streamer.
	tresult PLUGIN_API getState(IBStream* state) SMTG_OVERRIDE
	{
		IBStreamer streamer(state, kLittleEndian);

		return kResultTrue;
	}

	// Loads all of the state back into this object.
	tresult PLUGIN_API setState(IBStream* state) SMTG_OVERRIDE
	{
		IBStreamer streamer(state, kLittleEndian);

		return kResultTrue;
	}

	// Sets the value of a parameter.
	tresult PLUGIN_API setParamNormalized(ParamID tag, ParamValue value) SMTG_OVERRIDE
	{
		return EditController::setParamNormalized(tag, value);
	}
};
