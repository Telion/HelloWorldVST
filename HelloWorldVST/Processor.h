#pragma once

#include "public.sdk/source/vst/vstaudioeffect.h"
#include "public.sdk/source/vst/vstaudioprocessoralgo.h"
#include "base/source/fstreamer.h"

#include "Config.h"

using namespace Steinberg;
using namespace Steinberg::Vst;

// The processor is the back-end of the plugin.
// It does not display any UI or control any parameters.
// It reads parameter values and outputs audio.
class Processor : public AudioEffect
{
	// The number of channels for both the input and the output.
	// We could have a different number each, but then we have to think about how to map things.
	const int channelCount = 1;

	// The current rate of samples/sec.
	double sampleRate;

	// Your code goes here.
	// (Optionally) read the input channels and then write to the output channels.
	template<typename Float>
	void ProcessImpl(Float** in, Float** out, int numSamples)
	{
		// This sample implementation simply outputs a quiter version of the input.
		for (int i = 0; i < numSamples; ++i)
		{
			for (int j = 0; j < channelCount; ++j)
			{
				out[j][i] = in[j][i] / 4;
			}
		}
	}

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

	// Outputs audio.
	// Your code goes in ProcessImpl.
	tresult PLUGIN_API process(ProcessData& data) SMTG_OVERRIDE
	{
		// Argument validation
		if (!ValidateProcessData_AllowedFailures(data))
			return kResultTrue;
		if (!ValidateProcessData_DisallowedFailures(data))
			return kResultFalse;

		void** in = getChannelBuffersPointer(processSetup, data.inputs[0]);
		void** out = getChannelBuffersPointer(processSetup, data.outputs[0]);

		// If we are silent, set the correct fields and bail early.
		if (CheckSilence(data, in, out))
			return kResultTrue;

		// Run ProcessImpl using either float or double, whichever is requested.
		if (data.symbolicSampleSize == kSample32)
			ProcessImpl<Sample32>((Sample32**)in, (Sample32**)out, data.numSamples);
		else if (data.symbolicSampleSize == kSample64)
			ProcessImpl<Sample64>((Sample64**)in, (Sample64**)out, data.numSamples);

		return kResultOk;
	}

	// Runs before process for some reason
	tresult PLUGIN_API setupProcessing(ProcessSetup& newSetup) SMTG_OVERRIDE
	{
		// This does not seem to be included in Process, so we have to save it here.
		sampleRate = newSetup.sampleRate;

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

		// Create our default inputs and outputs.
		addAudioInput(STR16("Mono In"), SpeakerArr::kMono);
		addAudioOutput(STR16("Mono Out"), SpeakerArr::kMono);

		return kResultOk;
	}

	// Teardown before the destructor is called
	tresult PLUGIN_API terminate() SMTG_OVERRIDE
	{
		return AudioEffect::terminate();
	}

	// Write all of our model state into streamer.
	tresult PLUGIN_API getState(IBStream* state) SMTG_OVERRIDE
	{
		IBStreamer streamer(state, kLittleEndian);

		if (!streamer.writeDouble(sampleRate))
			return kResultFalse;

		return kResultTrue;
	}

	// Loads all of the state back into this object.
	tresult PLUGIN_API setState(IBStream* state) SMTG_OVERRIDE
	{
		IBStreamer streamer(state, kLittleEndian);

		if (!streamer.readDouble(sampleRate))
			return kResultFalse;

		return kResultTrue;
	}

	// Negotiates with the host to determine which audio streams to use.
	// The host offers a possible arrangement. Return true if you used it or false if you did not match the request.
	// In either case, you are free to modify your own arrangement.
	// This is somewhat complicated and may be unnecessary.
	tresult PLUGIN_API setBusArrangements(SpeakerArrangement* inputs, int32 numIns, SpeakerArrangement* outputs, int32 numOuts) SMTG_OVERRIDE
	{
		// Do not attempt to accommodate the wrong numbers of inputs/outputs. Keep it simple.
		if (numIns != 1 || numOuts != 1)
			return kResultFalse;
 
		// Get our current bus arrangement.
		// Even though we know that the host has requested 1 input and 1 output, we apparently still have to use their exact speaker positions
		AudioBus* bus = FCast<AudioBus>(audioInputs[0]);
		if (!bus || bus->getArrangement() != inputs[0])
		{
			// The host requested 1 input 1 output, but the arrangement they gave us is different.
			// Remove our own arrangement and use theirs instead.
			removeAudioBusses();
			addAudioInput(STR16("Mono In"), inputs[0]);
			addAudioOutput(STR16("Mono Out"), inputs[0]);
		}

		return kResultTrue;
	}

	// Declare which floating point types we support.
	tresult PLUGIN_API canProcessSampleSize(int32 symbolicSampleSize) SMTG_OVERRIDE
	{
		// Remove kSample32 or kSample64 if necessary for your plugin, but you should really support both.
		return symbolicSampleSize == kSample32 || symbolicSampleSize == kSample64 ? kResultTrue : kResultFalse;
	}

private:
	// Helper function to validate the data before running Process.
	// If this validation fails, Process should return kResultTrue.
	bool ValidateProcessData_AllowedFailures(ProcessData& data)
	{
		if (data.numInputs == 0)
			return false;

		if (data.numOutputs == 0)
			return false;

		return true;
	}

	// Helper function to validate the data before running Process.
	// If this validation fails, Process should return kResultFalse.
	bool ValidateProcessData_DisallowedFailures(ProcessData& data)
	{
		if (data.inputs[0].numChannels < channelCount)
			return false;

		if (data.outputs[0].numChannels < channelCount)
			return false;

		return true;
	}

	// Helper function for Process to check for silence and resolve it in a trivial way.
	bool CheckSilence(ProcessData& data, void** in, void** out)
	{
		unsigned bufferSize = getSampleFramesSizeInBytes(processSetup, data.numSamples);

		if (data.inputs[0].silenceFlags != 0)
		{
			// Clear the output buffers (to actually make it silent)
			for (int32 i = 0; i < channelCount; ++i)
			{
				if (in[i] != out[i])
				{
					memset(out[i], 0, bufferSize);
				}
			}

			// We have to mark the output as silent.
			// This seems pointless now, but it is nontrivial for multichannel or multi-input scenarios.
			data.outputs[0].silenceFlags = data.inputs[0].silenceFlags;
			return true;
		}

		data.outputs[0].silenceFlags = 0;
		return false;
	}
};
