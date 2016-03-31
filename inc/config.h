#ifndef CONFIG_H
#define CONFIG_H
#include <string>

enum VolumeType{
	MUSIC,
	INTERFACE,
	EFFECTS
};

struct Volumes{
	int Music;
	int Interface;
	int Effects;
};

enum Status{
	IS_OFF,
	IS_ON
};

class Configuration {
	public:
		bool SetScreenWidthHeight(int width, int height, int minWidth, int minHeight);
		/* This is pretty much self-explanatory, but I'll explain it
		 * anyway. 
		 * This takes two values. The first is the width it needs to be
		 * set to, and the second is the height it needs to be set to.
		 * Obviously doesn't return anything after it's been set. 
		 */

		int SetVolume(int volumeType, std::string volumeLevelString);
		/* setVolume takes VolumeType and the value to set it to.
		 * It returns with the following:
		 * 	0: successfully set
		 * 	1: value was too low. Volume was set to 0.
		 * 	2: value was too high. Volume was set to 100.
		 */

		void SetVsync(bool turnOn);
		/* This will set the Vsync to either on or off. Duh.
		 */

		void SetFullscreen(bool turnOn);
		/* Guess what! This turns on fullscreen. I'm gonna get an
		 * aneurysm if I keep writing dumb comments like this. 
		 * TODO: Go through when it's finished and move the
		 * unnecessary comments or the stupidly simple documentation
		 * to doc/ somewhere. For now, continue making comments to
		 * help describe the program for my own purposes.
		 */

		void LoadDefaults();
		/* This loads the defaults from an as-of-yet unspecified
		 * location... For now it simply sets the defaults without
		 * reading them from anywhere.
		 */
		
		bool ApplySettings(std::string configFilePath);
		/* This will allow you to apply the settings (obviously).
		 * It writes the to the file at configFilePath.
		 */

		Configuration();
		/* This simply runs LoadDefaults() and sets some other things.
		 */

		Configuration(std::string configFilePath);
		/* This requires a configuration file to be available at
		 * configFilePath. It first runs LoadDefaults() in order to
		 * set all settings to their defaults. Once it does that, it
		 * checks to see whether a file exists at configFilePath. If
		 * it does, it will read it and set any associated settings.
		 */

		~Configuration();
		/* Not sure what this is to do yet. We'll figure something out
		 * later.
		 */


		/* The next functions might be unnecessary. I've got no clue.
		 * They're just the 'get' functions and each return the value
		 * of the appropriate setting.
		 */

		int GetWidth();
		int GetHeight();
		int GetVolume(int requestedVolumeType);
		bool IsVsyncOn();
		bool IsFullscreenOn();


	private:
		int Width;
		int Height;

		Volumes CurrentVolume; 
		bool VsyncOn;
		bool FullscreenOn;
};
#endif
