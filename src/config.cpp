#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <locale>

#include "../inc/config.h"

bool Configuration::SetScreenWidthHeight(int width, int height, int minWidth, int minHeight)
{
	if(width < minWidth || height < minHeight){ 
		std::cerr << "Screen definitions too small.\n\tRequested Width: " << width <<"\n\tRequestedHeight: " << height << '\n';
		return false;
	}
	Width = width;
	Height = height;
	return true;
}

int Configuration::SetVolume(int volumeType, std::string volumeLevelString)
{
	
	std::stringstream vs(volumeLevelString);
	int volumeLevel;
	vs >> volumeLevel;

	/* This is going to be making sure the volume doesn't go over 100 or under 0.
	 * Curious... I wonder if I should allow volumeLevel to be -1 as well to show
	 * mute... I think I'm going to just set a bool that sets whether it's muted.
	 *
	 * Note that these are just so I can reflect the status when I use them in a
	 * program.
	 */
	int returnValue = 0; 
	if(volumeLevel < 0){
		std::cerr << "Requested volume level is less than 0. Setting to 0.\n";
		volumeLevel = 0;
		returnValue = 1;
	}
	else if(volumeLevel > 100){
		std::cerr << "Requested volume level is greater than 100. Setting to 100.\n";
		volumeLevel = 100;
		returnValue = 2;
	}

	if(volumeType == MUSIC){
		CurrentVolume.Music = volumeLevel;
	}
	if(volumeType == INTERFACE){
		CurrentVolume.Interface = volumeLevel;
	}
	if(volumeType == EFFECTS){
		CurrentVolume.Effects = volumeLevel;
	}

	return returnValue;
}

void Configuration::SetVsync(bool turnOn)
{
	VsyncOn = turnOn;
}

void Configuration::SetFullscreen(bool turnOn)
{
	FullscreenOn = turnOn;
}

void Configuration::LoadDefaults()
{
	// Some arbitrary valuse I think will work just fine. 
	SetScreenWidthHeight(400, 300, 400, 300);
	
	SetVolume(MUSIC, "45");
	SetVolume(INTERFACE, "45");
	SetVolume(EFFECTS, "60");

	SetVsync(true);
	SetFullscreen(false);
}

bool Configuration::ApplySettings(std::string configFilePath)
{
	std::cout << "Saving Settings... (Not)\n";

	std::ofstream configFile(configFilePath, std::ios::out | std::ios::trunc);
	if(configFile){
		configFile << "ScreenWidthHeight=" << Width << "x" << Height << '\n'
			<< "MusicVol=" << CurrentVolume.Music << '\n'
			<< "EffectsVol=" << CurrentVolume.Effects << '\n'
			<< "InterfaceVol=" << CurrentVolume.Interface << '\n';

		if(FullscreenOn){
			configFile << "FullscreenOn=true\n";
		}
		else{
			configFile << "FullscreenOn=false\n";
		}

		if(VsyncOn){
			configFile << "VsyncOn=true\n";
		}
		else{
			configFile << "VsyncOn=false\n";
		}
	}
	else{
		std::cout << "Could not save configuration to " << configFilePath << "!\n";
		return false;
	}


	return true;
}

Configuration::Configuration()
{
	std::cout << "Calling LoadDefaults\n";
	LoadDefaults();
}

Configuration::Configuration(std::string configFilePath)
{
	LoadDefaults(); // This will load the defaults for the software so that
			// anything not in the configuration file will be set.
	
	std::ifstream configFile(configFilePath, std::ios::in);

	/* The following if will perform the following steps
	 *
	 * 1: Check if the configuration file was opened properly.
	 * 2: Read the file line-by-line.
	 * 3: check if the contents of each line to the left of the = sign
	 *    correspond with a setting.
	 * 4: If the contents of the line left of the = sign correspond with a
	 *    setting, set the setting to whatever is after the = on that line.
	 */

	if(configFile){ // Step 1
		std::string configFileLine = "";
		while(std::getline(configFile, configFileLine)){ // Step 2
			std::istringstream configFileLineStream(configFileLine);
			std::string key = "";
			if(std::getline(configFileLineStream, key, '=')){
				/* This might be obvious, but I'm using the 
				 * following five lines to change the text to
				 * lowercase to make checking the value easier. 
				 */
				std::locale loc;
				std::string keyBuffer = "";
				for (std::string::size_type i=0; i<key.length(); ++i){
					keyBuffer += std::tolower(key[i],loc);
				}
				key = keyBuffer;

				std::string value;
				std::getline(configFileLineStream, value);

				if(key == "screenwidthheight"){
					/* because ScreenWidthHeight is in the
					 * format of 400x300, we'll be 
					 * performing an action similar to what 
					 * we're doing for the key=value part.
					 */
					std::string w;
					std::string h;
					int wInt = 0;
					int hInt = 0;

					std::istringstream widthxheight(value);

					std::getline(widthxheight, w, 'x');
					std::getline(widthxheight, h);

					std::stringstream wSS(w);
					std::stringstream hSS(h);

					wSS >> wInt;
					hSS >> hInt;

					SetScreenWidthHeight(wInt, hInt, 400, 300);
				}
				else if(key == "vsyncon"){\
					std::stringstream vs(value);
					bool isOn;
					vs >> isOn;
					SetVsync(isOn);
				}
				else if(key == "fullscreenon"){
					if(value == "true"){ 
						FullscreenOn = true;
					}
					else{
						if(value != "false"){
							std::cerr << value << " is not a valid value for " << key << '\n';
						}
						FullscreenOn = false;
					}
				}
				else if(key == "musicvol"){
					SetVolume(MUSIC, value);
				}
				else if(key == "interfacevol"){
					SetVolume(INTERFACE, value);
				}
				else if(key == "effectsvol"){
					SetVolume(EFFECTS, value);
				}
				else{
					std::cerr << key << " is not a valid setting!\n";
				}
			}
		}	
	}
	else{
		std::cerr << "Could not open configuration file \"" << configFilePath << "\" for reading!\n";
	}
}

Configuration::~Configuration()
{
}

int Configuration::GetWidth()
{
	return Width;
}

int Configuration::GetHeight()
{
	return Height;
}

int Configuration::GetVolume(int requestedVolumeType)
{
	if(requestedVolumeType == MUSIC){
		return CurrentVolume.Music;
	}
	else if(requestedVolumeType == EFFECTS){
		return CurrentVolume.Effects;
	}
	else if(requestedVolumeType == INTERFACE){
		return CurrentVolume.Interface;
	}
	else{
		return -1;
	}
}

bool Configuration::IsVsyncOn()
{
	return VsyncOn;
}

bool Configuration::IsFullscreenOn()
{
	return FullscreenOn;
}

