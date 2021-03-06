/* MIT License
#
# Copyright (c) 2020 Ferhat Geçdoğan All Rights Reserved.
# Distributed under the terms of the MIT License.
#
# */

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <sys/utsname.h>
#include <chrono>
#include <stdint.h>

// Libraries 
#include <Colorized.hpp>
#include <FileSystemPlusPlus.h>
#include <Colors.h>
#include <Logos.h>

#define FETCHEYA_VERSION "0.3"
#define FETCHEYA_STATUS "beta-2"

#ifndef __FreeBSD__
	#include <sys/sysinfo.h>
#endif

std::string ftime(__TIME__); // Convert
std::string Ws("				     ");

class systemInfo {
public:
	std::string EraseAllSubString(std::string & mainString, const std::string & erase) {
   	 size_t pos = std::string::npos;
   	 while((pos = mainString.find(erase)) != std::string::npos) {
   	     	mainString.erase(pos, erase.length());
   	 }
   		return mainString;
    	}

	void getOS() {
		fsplusplus::ReadFilePath("/etc/os-release"); 
	}
	
	void getCPU() {
		fsplusplus::ReadCPU();
	}

	void Test8bitColors_Top() {
		colorized::PrintWith(colorized::Colorize(BOLD, DARK_GRAY).c_str(), "███");
		colorized::PrintWith(colorized::Colorize(BOLD, LIGHT_RED).c_str(), "███");
		colorized::PrintWith(colorized::Colorize(BOLD, LIGHT_GREEN).c_str(), "███");
		colorized::PrintWith(colorized::Colorize(BOLD, LIGHT_YELLOW).c_str(), "███");
		colorized::PrintWith(colorized::Colorize(BOLD, LIGHT_BLUE).c_str(), "███");
		colorized::PrintWith(colorized::Colorize(BOLD, LIGHT_MAGENTA).c_str(), "███");
		colorized::PrintWith(colorized::Colorize(BOLD, LIGHT_CYAN).c_str(), "███");
		colorized::PrintWith(colorized::Colorize(BOLD, WHITE).c_str(), "███");	
	}
	
	void Test8bitColors_Bottom() {
		colorized::PrintWith(colorized::Colorize(BOLD, BLACK).c_str(), "███");
		colorized::PrintWith(colorized::Colorize(BOLD, RED).c_str(), "███");
		colorized::PrintWith(colorized::Colorize(BOLD, GREEN).c_str(), "███");
		colorized::PrintWith(colorized::Colorize(BOLD, YELLOW).c_str(), "███");
		colorized::PrintWith(colorized::Colorize(BOLD, BLUE).c_str(), "███");
		colorized::PrintWith(colorized::Colorize(BOLD, MAGENTA).c_str(), "███");
		colorized::PrintWith(colorized::Colorize(BOLD, CYAN).c_str(), "███");
		colorized::PrintWith(colorized::Colorize(BOLD, LIGHT_GRAY).c_str(), "███\n");	
	}

	std::string getSystem() {
		struct utsname buf;
		if(!uname(&buf)) { //Get name and information about current kernel.
			//printf("%s\n",buf.sysname);//Display the system name.
			return buf.sysname;
		} else {
			perror("uname");
			return "?";
		}
	}
	
	std::string getHostname() {
		struct utsname sysinfo;
		uname(&sysinfo);
		hostname = sysinfo.nodename;
		if(hostname.length() == 0) {
			return "fegeya";
		}
		return hostname;
	}
	std::string getUsername() {
		username = getenv("USER");
		return username;
	}
	int getUserHostLength() {
		hostnameLength = getHostname().length();
		usernameLength = getUsername().length();
		UserHostLength = usernameLength + hostnameLength;
		return UserHostLength;
	}
	std::string getDevice() {
		std::ifstream device;
		filename = "/sys/devices/virtual/dmi/id/product_family";
		device.open(filename);
		if(device.good()){
			getline(device, deviceName);
		}
		device.close();
		return deviceName;
	}

	std::string getUptime() {
		#ifdef __FreeBSD__
		return "0m";
		#else
		static struct sysinfo info;
		sysinfo(&info);
		uptime = info.uptime;		
		if(uptime/60 >= 60) {
			uptimeHour = (uptime/60)/60;
			uptimeHourWhole = uptimeHour;
			uptimeMinutes = uptimeHour - uptimeHourWhole;
			uptimeMinutesWhole = uptimeMinutes * 60;
			if(uptimeHour >= 24) {
				uptimeDay = uptimeHour/24;
				uptimeDayWhole = uptimeDay;
				uptimeHour = uptimeDay - uptimeDayWhole;
				uptimeHour = uptimeHour * 24;
				uptimeHourWhole = uptimeHour;
				uptimeStream << uptimeDayWhole << "d " << uptimeHourWhole << "h " << uptimeMinutesWhole << "m";
			}
			else {
				uptimeStream << uptimeHourWhole << "h " << uptimeMinutesWhole << "m";
			}
		}
		else {
			uptimeMinutes = uptime/60;
			uptimeMinutesWhole = uptimeMinutes;
			uptimeStream << uptimeMinutesWhole << "m";
		}
		uptimeString = uptimeStream.str();
		return uptimeString;
		#endif
	}
	std::string getShell() {
		shell = getenv("SHELL");
		shell.erase(0,5);
		return shell;
	}
	std::string getDe() {
		desktop = getenv("XDG_CURRENT_DESKTOP");
		if(desktop.length() != 0) {		
			return desktop;
		}
		return "null";
	}
	std::string getTerm() {
		terminal = getenv("TERM");
		return terminal;
	}
	std::string getKernel() {
		struct utsname sysinfo;
		uname(&sysinfo);
		kernelVersion = sysinfo.release;
		return kernelVersion;
	}
	std::string getArch() {
		struct utsname sysinfo;
		uname(&sysinfo);
		architecture = sysinfo.machine;
		return architecture;
	}
	std::string getEditor() {
		editor = getenv("EDITOR");
		return editor;
	}
	std::string getVisual() {
		visual = getenv("VISUAL");
		return visual;
	}
private:
	std::string distroLine, filename, hostname, username, deviceName,
		uptimeString, shell, terminal, kernelVersion, architecture,
		editor, visual, lineOne, desktop;
	double uptime, uptimeMinutes, uptimeHour, uptimeDay;
	int initialUptime, uptimeMinutesWhole, uptimeHourWhole, uptimeDayWhole, usernameLength,
		hostnameLength, UserHostLength;
	std::stringstream uptimeStream;
};

void Parse(int p) {
	systemInfo systemInfo;
	if(p == 2) {
		colorized::PrintWith(colorized::Colorize(BOLD, LIGHT_BLUE).c_str(), systemInfo.getUsername().c_str());
		colorized::PrintWith(colorized::Colorize(BOLD, LIGHT_CYAN).c_str(), "@");  
		colorized::PrintWith(colorized::Colorize(BOLD, BLUE).c_str(), (systemInfo.getHostname()).c_str());
		printf("\n");		
	} else if(p == 3) {	
		for(int i = 0; i != systemInfo.getUserHostLength() + 1; i++) {
			std::cout << "\033[1;36m" << "-" << "\033[1;31m";
		}
		
		printf("\n"); 
	} else if(p == 4) {
		std::cout << "\033[1;34m" << "Build: " << "\033[01;33m" << FETCHEYA_VERSION << "-" <<
		FETCHEYA_STATUS << "-" << "fetcheyav" << systemInfo.EraseAllSubString(ftime, ":") << std::endl;
	} else if(p == 5) {
		#ifdef __FreeBSD__
			std::cout << "\033[1;31m" << "OS Name:" << "\033[1;36m" << " " << "FreeBSD" << std::endl;
		#else
			std::cout << "\033[1;31m" << "OS Name:" << "\033[1;36m" << " " << fsplusplus::ReadOSName() << std::endl;
		#endif
	} else if(p == 6) {
		std::cout << "\033[1;36m" << "Architecture:" << "\033[1;33m" << " " << systemInfo.getArch() << std::endl;
	} else if(p == 7) {
		std::cout << "\033[1;32m" << "Hostname:" << "\033[1;35m" << " " << systemInfo.getHostname() << std::endl;
	} else if(p == 8) {
		std::cout << "\033[1;34m" << "Kernel Name:" << "\033[1;35m" << " " <<  systemInfo.getSystem() << std::endl;
	} else if(p == 9) {
		std::cout << "\033[01;33m" << "Kernel Release:" << "\033[1;34m" << " "  << systemInfo.getKernel() << std::endl;
	} else if(p == 10) {
		std::cout << "\033[1;35m" << "CPU:" << "\033[1;31m" << " ";
		systemInfo.getCPU();
	} else if(p == 11) {
		std::cout << "\033[1;34m" << "Uptime:" << "\033[01;33m" << " "  <<  systemInfo.getUptime() << std::endl;	
	} else if(p == 12) {
		std::cout << "\033[1;35m" << "Terminal:" << "\033[1;32m" << " "  << systemInfo.getTerm() << std::endl;
	} else if(p == 13) {
		std::cout << "\033[1;36m" << "Shell:" << "\033[1;31m" << " " << systemInfo.getShell() << std::endl;
	} else if(p == 14) {
		colorized::PrintWith(colorized::Colorize(BOLD, LIGHT_CYAN).c_str(), "Desktop Env: ");
		colorized::PrintWith(colorized::Colorize(BOLD, LIGHT_RED).c_str(), systemInfo.getDe().c_str());	
		std::cout << "\n\n";
	} else if(p == 15) {
		systemInfo.Test8bitColors_Top();
		std::cout << "\n";
	} else if(p == 16) {
		systemInfo.Test8bitColors_Bottom();
	} else { printf("\n"); }
}

int main() {
	int a = 0;
	systemInfo systemInfo;
	unsigned short int x = 0;                              
      	char** logo = OSLogo();
      	
	if(control != true) {
  		for (x = 0; x < 18; x++) {
    			std::cout << logo[x];
			Parse(x);
		}
	} else {
		for (x = 0; x < 15; x++) {
			Parse(x);
		}
	}	
	
	std::cout << Ws;
	//systemInfo.Test16bitColours();
	printf("\n\n");
	return F_OK;
}

