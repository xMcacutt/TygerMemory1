#pragma once
#ifdef TYGERMEM_EXPORTS
#define TYGERMEM __declspec(dllexport)
#else
#define TYGERMEM __declspec(dllimport)
#endif

typedef UINT*(*TyPlaySoundByIndex_t)(int soundIndex, int* unknownUsuallyNullPtr, float unknownUsuallyZero);

class TYGERMEM Sound
{
private:
	static TyPlaySoundByIndex_t GetTySoundFunction();
public:
	/// <summary>
	/// Calls the play sound function from the game, to play any sound index from global.sound (As long as it is loaded with the SFX ini file for the level. UI sounds are usually always loaded). If its a looping sound it'll play forever unless manually stopped.
	/// <para>https://discord.com/channels/1029229401314967562/1029384056984571934/1289675773359296574 Floralz has made a list to easily find the index</para>
	/// </summary>
	/// <param name="soundIndex:"> The index of the sound to play</param>
	/// <returns>
	///		Returns probably a pointer to the playing sound effect properties to potentially stop it (hasn't been looked into)
	/// </returns>
	static UINT* PlayTySoundByIndex(int soundIndex);
};

