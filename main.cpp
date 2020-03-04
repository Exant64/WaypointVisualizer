#include "pch.h"
#include "SA2ModLoader.h"

extern "C" 
{
	struct __declspec(align(4)) WaypointThing__
	{
		int x;
		int z;
	};

	struct WaypointThing_
	{
		int index;
		WaypointThing__ array[512]; //sa2 size different to sadx
	};
	DataArray(WaypointThing_, WaypointThings, 0x1A15938, 16);
	VoidFunc(sub_42D340, 0x42D340);
	int indexTest = 1;
	float ratio = 10.0f;
	float yPos = 25.0f;
	void __cdecl Renderer_Main(ObjectMaster* a1)
	{
		if (Controllers[0].release & Buttons_L)
		{
			if (indexTest > 0)
				indexTest--;
		}
		if (Controllers[0].release & Buttons_R)
		{
			if (indexTest < 15)
				indexTest++;
		}
		
	}

	void __cdecl Renderer_Display(ObjectMaster* a1)
	{
		for (int i = 0; i < WaypointThings[indexTest].index; i++)
		{
			njPushMatrix(_nj_current_matrix_ptr_);
			njTranslate(_nj_current_matrix_ptr_, (WaypointThings[indexTest].array[i].x - 16) * ratio, yPos, (WaypointThings[indexTest].array[i].z - 20) * ratio);

			sub_42D340();
			ProcessChunkModelsWithCallback((NJS_OBJECT*)0x171552C, ProcessChunkModel);

			njPopMatrix(1);
		}
		PrintDebug("%d \n", indexTest);
	}

	void CreateRenderer()
	{
		indexTest = 1;
		ObjectMaster* loaded = LoadObject(4, "AL_WaypointVisualizer", Renderer_Main, LoadObj_Data1);
		loaded->DisplaySub = Renderer_Display;
	}
	void SpawnAllChaoHook()
	{
		CreateRenderer();
		SpawnAllChaoInGarden();
	}

	__declspec(dllexport) void Init()
	{
		WriteCall((void*)0x0054C9C2, SpawnAllChaoHook); //neutgarden
		WriteCall((void*)0x0054D3B9, SpawnAllChaoHook); //herogarden
		WriteCall((void*)0x0054B8D9, SpawnAllChaoHook); //darkgarden
	}
	__declspec(dllexport) ModInfo SA2ModInfo = { ModLoaderVer };
}