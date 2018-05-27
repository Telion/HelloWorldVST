#pragma once

#include "vstgui/plugin-bindings/vst3editor.h"
#include "public.sdk/source/vst/vsteditcontroller.h"

#include <vector>


//#include "againparamids.h"
//#include "againuimessagecontroller.h"

#include "pluginterfaces/base/ibstream.h"
#include "pluginterfaces/base/ustring.h"
#include "pluginterfaces/vst/ivstmidicontrollers.h"

#include "base/source/fstring.h"
#include "base/source/fstreamer.h"

#include "vstgui/uidescription/delegationcontroller.h"

#include <stdio.h>
#include <math.h>

namespace Steinberg {
namespace Vst {

//template <typename T>
//class AGainUIMessageController;

class Controller : public EditController//, public IMidiMapping, public VST3EditorDelegate
{
public:
	//typedef AGainUIMessageController<AGainController> UIMessageController;

	static const FUID UID;

	// The host calls this to create an instance (see Entry.cpp)
	static FUnknown* createInstance(void*)
	{
		return (IEditController*)new Controller();
	}

	// Initializes the instance
	tresult PLUGIN_API initialize(FUnknown* context) SMTG_OVERRIDE
	{
		tresult result = EditController::initialize(context);
		if (result != kResultOk)
		{
			return result;
		}

		return kResultOk;

		////--- Create Units-------------
		//UnitInfo unitInfo;
		//Unit* unit;

		//// create root only if you want to use the programListId
		///*	unitInfo.id = kRootUnitId;	// always for Root Unit
		//unitInfo.parentUnitId = kNoParentUnitId;	// always for Root Unit
		//Steinberg::UString (unitInfo.name, USTRINGSIZE (unitInfo.name)).assign (USTRING ("Root"));
		//unitInfo.programListId = kNoProgramListId;

		//unit = new Unit (unitInfo);
		//addUnitInfo (unit);*/

		//// create a unit1 for the gain
		//unitInfo.id = 1;
		//unitInfo.parentUnitId = kRootUnitId; // attached to the root unit

		//Steinberg::UString(unitInfo.name, USTRINGSIZE(unitInfo.name)).assign(USTRING("Unit1"));

		//unitInfo.programListId = kNoProgramListId;

		//unit = new Unit(unitInfo);
		//addUnit(unit);

		////---Create Parameters------------

		////---Gain parameter--
		//GainParameter* gainParam = new GainParameter(ParameterInfo::kCanAutomate, kGainId);
		//parameters.addParameter(gainParam);

		//gainParam->setUnitID(1);

		////---VuMeter parameter---
		//int32 stepCount = 0;
		//ParamValue defaultVal = 0;
		//int32 flags = ParameterInfo::kIsReadOnly;
		//int32 tag = kVuPPMId;
		//parameters.addParameter(STR16("VuPPM"), 0, stepCount, defaultVal, flags, tag);

		////---Bypass parameter---
		//stepCount = 1;
		//defaultVal = 0;
		//flags = ParameterInfo::kCanAutomate | ParameterInfo::kIsBypass;
		//tag = kBypassId;
		//parameters.addParameter(STR16("Bypass"), 0, stepCount, defaultVal, flags, tag);

		////---Custom state init------------

		//String str("Hello World!");
		//str.copyTo16(defaultMessageText, 0, 127);

		//return result;
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

		return kResultOk;
	}

	// huh?
	IPlugView* PLUGIN_API createView(const char* name) SMTG_OVERRIDE
	{
		// someone wants my editor
		if (name && strcmp(name, "editor") == 0)
		{
			VST3Editor* view = new VST3Editor(this, "view", "again.uidesc");
			return view;
		}
		return nullptr;
	}

	// Write all of our model state into streamer.
	// Important state should generally be stored in the Processor. Tread carefully.
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
		tresult result = EditController::setParamNormalized(tag, value);
		return result;
	}

	// Not sure what this is for
	tresult PLUGIN_API getParamStringByValue(ParamID tag, ParamValue valueNormalized, String128 string) SMTG_OVERRIDE
	{
		return EditController::getParamStringByValue(tag, valueNormalized, string);
	}

	// Not sure what this is for
	tresult PLUGIN_API getParamValueByString(ParamID tag, TChar* string, ParamValue& valueNormalized) SMTG_OVERRIDE
	{
		return EditController::getParamValueByString(tag, string, valueNormalized);
	}

	// Receives a message from Processor.
	tresult receiveText(const char* text) SMTG_OVERRIDE
	{
		return kResultOk;
	}

	//---from IMidiMapping-----------------
	//tresult PLUGIN_API getMidiControllerAssignment(int32 busIndex, int16 channel, CtrlNumber midiControllerNumber, ParamID& tag) SMTG_OVERRIDE
	//{
	//	// we support for the Gain parameter all MIDI Channel but only first bus (there is only one!)
	//	if (busIndex == 0 && midiControllerNumber == kCtrlVolume)
	//	{
	//		tag = kGainId;
	//		return kResultTrue;
	//	}
	//	return kResultFalse;
	//}

	//---from VST3EditorDelegate-----------
	//IController* createSubController(UTF8StringPtr name, const IUIDescription* description, VST3Editor* editor) SMTG_OVERRIDE
	//{
	//	if (UTF8StringView(name) == "MessageController")
	//	{
	//		UIMessageController* controller = new UIMessageController(this);
	//		addUIMessageController(controller);
	//		return controller;
	//	}
	//	return nullptr;
	//}

	// Huh?
	//DELEGATE_REFCOUNT(EditController) tresult PLUGIN_API queryInterface(const char* iid, void** obj) SMTG_OVERRIDE
	//{
	//	QUERY_INTERFACE(iid, obj, IMidiMapping::iid, IMidiMapping) return EditController::queryInterface(iid, obj);
	//}

	//---Internal functions-------
	//void addUIMessageController(UIMessageController* controller)
	//{
	//	uiMessageControllers.push_back(controller);
	//}

	//void removeUIMessageController(UIMessageController* controller)
	//{
	//	UIMessageControllerList::const_iterator it =
	//		std::find(uiMessageControllers.begin(), uiMessageControllers.end(), controller);
	//	if (it != uiMessageControllers.end())
	//		uiMessageControllers.erase(it);
	//}
};

}
}