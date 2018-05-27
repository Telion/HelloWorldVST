#pragma once

#include "public.sdk/source/vst/vstaudioeffect.h"

#include "public.sdk/source/vst/vstaudioprocessoralgo.h"

#include "pluginterfaces/base/ibstream.h"
#include "pluginterfaces/base/ustring.h"
#include "pluginterfaces/vst/ivstevents.h"
#include "pluginterfaces/vst/ivstparameterchanges.h"
#include "pluginterfaces/vst/vstpresetkeys.h"

#include <stdio.h>
#include "base/source/fstreamer.h"


#include "Config.h"

namespace Steinberg {
namespace Vst {

class Processor : public AudioEffect
{
	int sampleNum = 0;

public:
	// The host calls this to create an instance (see Entry.cpp)
	static FUnknown* createInstance(void*)
	{
		return (IAudioProcessor*)new Processor();
	}

	Processor()
	{
		setControllerClass(ControllerUid);
	}

	virtual ~Processor() // must be virtual
	{

	}

	// Your code goes here
	tresult PLUGIN_API process(ProcessData& data) SMTG_OVERRIDE
	{
		for (int i = 0; i < data.numOutputs; ++i)
		{
			void** out = getChannelBuffersPointer(processSetup, data.outputs[i]);
			for (int j = 0; j < data.numSamples; ++j)
			{
				((Sample32*)out)[j] = 0;
			}
		}

		//if (data.numInputs == 0 || data.numOutputs == 0)
		//{
		//	// nothing to do
		//	return kResultOk;
		//}

		//// (simplification) we suppose in this example that we have the same input channel count than the output
		//int32 numChannels = data.inputs[0].numChannels;

		////---get audio buffers----------------
		//uint32 sampleFramesSize = getSampleFramesSizeInBytes(processSetup, data.numSamples);
		//void** in = getChannelBuffersPointer(processSetup, data.inputs[0]);
		//void** out = getChannelBuffersPointer(processSetup, data.outputs[0]);

		////---check if silence---------------
		//// normally we have to check each channel (simplification)
		//if (data.inputs[0].silenceFlags != 0)
		//{
		//	// mark output silence too
		//	data.outputs[0].silenceFlags = data.inputs[0].silenceFlags;

		//	// the Plug-in has to be sure that if it sets the flags silence that the output buffer are clear
		//	for (int32 i = 0; i < numChannels; i++)
		//	{
		//		// do not need to be cleared if the buffers are the same (in this case input buffer are already cleared by the host)
		//		if (in[i] != out[i])
		//		{
		//			memset(out[i], 0, sampleFramesSize);
		//		}
		//	}

		//	// nothing to do at this point
		//	return kResultOk;
		//}

		//// mark our outputs has not silent
		//data.outputs[0].silenceFlags = 0;

		//for (int i = 0; i < data.numSamples; ++i)
		//{
		//	for (int j = 0; j < data.numInputs; ++j)
		//		((Sample32**)out)[j][i] = 0;//((Sample32**)in)[j][i] / 4;
		//}

		return kResultOk;

		//// finally the process function
		//// In this example there are 4 steps:
		//// 1) Read inputs parameters coming from host (in order to adapt our model values)
		//// 2) Read inputs events coming from host (we apply a gain reduction depending of the velocity of pressed key)
		//// 3) Process the gain of the input buffer to the output buffer
		//// 4) Write the new VUmeter value to the output Parameters queue


		////---1) Read inputs parameter changes-----------
		//IParameterChanges* paramChanges = data.inputParameterChanges;
		//if (paramChanges)
		//{
		//	int32 numParamsChanged = paramChanges->getParameterCount();
		//	// for each parameter which are some changes in this audio block:
		//	for (int32 i = 0; i < numParamsChanged; i++)
		//	{
		//		IParamValueQueue* paramQueue = paramChanges->getParameterData(i);
		//		if (paramQueue)
		//		{
		//			ParamValue value;
		//			int32 sampleOffset;
		//			int32 numPoints = paramQueue->getPointCount();
		//			switch (paramQueue->getParameterId())
		//			{
		//			case kGainId:
		//				// we use in this example only the last point of the queue.
		//				// in some wanted case for specific kind of parameter it makes sense to retrieve all points
		//				// and process the whole audio block in small blocks.
		//				if (paramQueue->getPoint(numPoints - 1, sampleOffset, value) == kResultTrue)
		//				{
		//					fGain = (float)value;
		//				}
		//				break;

		//			case kBypassId:
		//				if (paramQueue->getPoint(numPoints - 1, sampleOffset, value) == kResultTrue)
		//				{
		//					bBypass = (value > 0.5f);
		//				}
		//				break;
		//			}
		//		}
		//	}
		//}

		////---2) Read input events-------------
		//IEventList* eventList = data.inputEvents;
		//if (eventList)
		//{
		//	int32 numEvent = eventList->getEventCount();
		//	for (int32 i = 0; i < numEvent; i++)
		//	{
		//		Event event;
		//		if (eventList->getEvent(i, event) == kResultOk)
		//		{
		//			switch (event.type)
		//			{
		//				//----------------------
		//			case Event::kNoteOnEvent:
		//				// use the velocity as gain modifier
		//				fGainReduction = event.noteOn.velocity;
		//				break;

		//				//----------------------
		//			case Event::kNoteOffEvent:
		//				// noteOff reset the reduction
		//				fGainReduction = 0.f;
		//				break;
		//			}
		//		}
		//	}
		//}

		////-------------------------------------
		////---3) Process Audio---------------------
		////-------------------------------------
		//if (data.numInputs == 0 || data.numOutputs == 0)
		//{
		//	// nothing to do
		//	return kResultOk;
		//}

		//// (simplification) we suppose in this example that we have the same input channel count than the output
		//int32 numChannels = data.inputs[0].numChannels;

		////---get audio buffers----------------
		//uint32 sampleFramesSize = getSampleFramesSizeInBytes(processSetup, data.numSamples);
		//void** in = getChannelBuffersPointer(processSetup, data.inputs[0]);
		//void** out = getChannelBuffersPointer(processSetup, data.outputs[0]);

		////---check if silence---------------
		//// normally we have to check each channel (simplification)
		//if (data.inputs[0].silenceFlags != 0)
		//{
		//	// mark output silence too
		//	data.outputs[0].silenceFlags = data.inputs[0].silenceFlags;

		//	// the Plug-in has to be sure that if it sets the flags silence that the output buffer are clear
		//	for (int32 i = 0; i < numChannels; i++)
		//	{
		//		// do not need to be cleared if the buffers are the same (in this case input buffer are already cleared by the host)
		//		if (in[i] != out[i])
		//		{
		//			memset(out[i], 0, sampleFramesSize);
		//		}
		//	}

		//	// nothing to do at this point
		//	return kResultOk;
		//}

		//// mark our outputs has not silent
		//data.outputs[0].silenceFlags = 0;

		////---in bypass mode outputs should be like inputs-----
		//if (bBypass)
		//{
		//	for (int32 i = 0; i < numChannels; i++)
		//	{
		//		// do not need to be copied if the buffers are the same
		//		if (in[i] != out[i])
		//		{
		//			memcpy(out[i], in[i], sampleFramesSize);
		//		}
		//	}
		//	// in this example we do not update the VuMeter in Bypass
		//}
		//else
		//{
		//	float fVuPPM = 0.f;

		//	//---apply gain factor----------
		//	float gain = (fGain - fGainReduction);
		//	if (bHalfGain)
		//	{
		//		gain = gain * 0.5f;
		//	}

		//	// if the applied gain is nearly zero, we could say that the outputs are zeroed and we set the silence flags. 
		//	if (gain < 0.0000001)
		//	{
		//		for (int32 i = 0; i < numChannels; i++)
		//		{
		//			memset(out[i], 0, sampleFramesSize);
		//		}
		//		data.outputs[0].silenceFlags = (1 << numChannels) - 1;  // this will set to 1 all channels
		//	}
		//	else
		//	{
		//		if (data.symbolicSampleSize == kSample32)
		//			fVuPPM = processAudio<Sample32>((Sample32**)in, (Sample32**)out, numChannels,
		//				data.numSamples, gain);
		//		else
		//			fVuPPM = processAudio<Sample64>((Sample64**)in, (Sample64**)out, numChannels,
		//				data.numSamples, gain);
		//	}

		//	//---3) Write outputs parameter changes-----------
		//	IParameterChanges* outParamChanges = data.outputParameterChanges;
		//	// a new value of VuMeter will be send to the host 
		//	// (the host will send it back in sync to our controller for updating our editor)
		//	if (outParamChanges && fVuPPMOld != fVuPPM)
		//	{
		//		int32 index = 0;
		//		IParamValueQueue* paramQueue = outParamChanges->addParameterData(kVuPPMId, index);
		//		if (paramQueue)
		//		{
		//			int32 index2 = 0;
		//			paramQueue->addPoint(0, fVuPPM, index2);
		//		}
		//	}
		//	fVuPPMOld = fVuPPM;
		//}

		//return kResultOk;
	}

	// Runs before process for some reason
	tresult PLUGIN_API setupProcessing(ProcessSetup& newSetup) SMTG_OVERRIDE
	{
		return AudioEffect::setupProcessing(newSetup);
	}

	// Initializes the instance
	tresult PLUGIN_API initialize(FUnknown* context) SMTG_OVERRIDE
	{
		// We apparently have to initialize the parent
		tresult result = AudioEffect::initialize(context);
		if (result != kResultOk)
		{
			return result;
		}

		//---create Audio In/Out buses------
		// we want a stereo Input and a Stereo Output
		//addAudioInput(STR16("Stereo In"), SpeakerArr::kStereo);
		addAudioOutput(STR16("Mono Out"), SpeakerArr::kMono);

		//---create Event In/Out buses (1 bus with only 1 channel)------
		//addEventInput(STR16("Event In"), 1);

		return kResultOk;
	}

	// Teardown before the destructor is called
	tresult PLUGIN_API terminate() SMTG_OVERRIDE
	{
		return AudioEffect::terminate();
	}

	// Enable or disable the plugin
	tresult PLUGIN_API setActive(TBool state) SMTG_OVERRIDE
	{
		sendTextMessage(state ? "Activating now" : "Deactivating now");

		// call our parent setActive
		return AudioEffect::setActive(state);
	}

	// Receives a message from the controller (for communication outside of regular parameters)
	tresult receiveText(const char* text) SMTG_OVERRIDE
	{
		return kResultOk;
	}

	// Write all of our model state into streamer.
	tresult PLUGIN_API getState(IBStream* state) SMTG_OVERRIDE
	{
		IBStreamer streamer(state, kLittleEndian);

		return kResultOk;
	}

	// Loads all of the state back into this object.
	tresult PLUGIN_API setState(IBStream* state) SMTG_OVERRIDE
	{
		IBStreamer streamer(state, kLittleEndian);

		return kResultOk;
	}

	// Negotiates with the host to determine which audio streams to use.
	tresult PLUGIN_API setBusArrangements(SpeakerArrangement* inputs, int32 numIns, SpeakerArrangement* outputs, int32 numOuts) SMTG_OVERRIDE
	{
		return kResultTrue;

		//if (numIns != 1 || numOuts != 1)
		//	return kResultFalse;

		//// This plugin is mono. Get our current input and compare to 
		//AudioBus* bus = FCast<AudioBus>(audioInputs.at(0));
		//if (bus)
		//{
		//	if (bus->getArrangement() != inputs[0])
		//	{
		//		removeAudioBusses();
		//		addAudioInput(STR16("Mono In"), inputs[0]);
		//		addAudioOutput(STR16("Mono Out"), inputs[0]);
		//	}
		//	return kResultOk;
		//}

		//return kResultFalse;
	}

	// Declare which floating point types we support.
	tresult PLUGIN_API canProcessSampleSize(int32 symbolicSampleSize) SMTG_OVERRIDE
	{
		return symbolicSampleSize == kSample32/* || symbolicSampleSize == kSample64*/ ? true : false;
	}

	// Receives a message? Not sure why
	tresult PLUGIN_API notify(IMessage* message) SMTG_OVERRIDE
	{
		if (!message)
			return kInvalidArgument;

		//if (!strcmp(message->getMessageID(), "BinaryMessage"))
		//{
		//	const void* data;
		//	uint32 size;
		//	if (message->getAttributes()->getBinary("MyData", data, size) == kResultOk)
		//	{
		//		// we are in UI thread
		//		// size should be 100
		//		if (size == 100 && ((char*)data)[1] == 1) // yeah...
		//		{
		//			fprintf(stderr, "[AGain] received the binary message!\n");
		//		}
		//		return kResultOk;
		//	}
		//}

		return AudioEffect::notify(message);
	}
};

}
}