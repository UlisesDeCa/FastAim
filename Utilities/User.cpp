#include "User.h"
#include "SimpleIni.h"
#include "skCrypter.h"
#include <fstream>
#include <iostream>


User::User() {
	CSimpleIniA ini;
	SI_Error rc = ini.LoadFile(_("User.ini"));
	if (rc < 0) 
	{
		return;  
	}
	
	this->Binds.aim = ini.GetDoubleValue(_("Key Binds"), _("Aim"));
	this->Binds.toggleMenu = ini.GetDoubleValue(_("Key Binds"), _("Hide Menu"));

	this->Aimbot.strength = ini.GetDoubleValue(_("Aimbot"), _("Strength"));
	this->Aimbot.fov = ini.GetDoubleValue(_("Aimbot"), _("FOV"));
	this->Aimbot.offsetX = ini.GetDoubleValue(_("Aimbot"), _("Offset X"));
	this->Aimbot.offsetY = ini.GetDoubleValue(_("Aimbot"), _("Offset Y"));

	this->SearchSettings.color = ini.GetDoubleValue(_("Search Settings"), _("Color"));
	this->SearchSettings.colorVariation = ini.GetDoubleValue(_("Search Settings"), _("Variation"));
	this->SearchSettings.sizeSearch = ini.GetDoubleValue(_("Search Settings"), _("Size Search"));
	this->SearchSettings.minMatch = ini.GetDoubleValue(_("Search Settings"), _("Minimum Match"));
	this->SearchSettings.refX = ini.GetDoubleValue(_("Search Settings"), _("Reference X"));
	this->SearchSettings.refY = ini.GetDoubleValue(_("Search Settings"), _("Reference Y"));

	this->Data.debug = ini.GetBoolValue(_("Data"), _("Debug"));

	// Update PreferenceXY
	const int MONITOR_CENTER_X = GetSystemMetrics(SM_CXSCREEN) / 2;
	const int MONITOR_CENTER_Y = GetSystemMetrics(SM_CYSCREEN) / 2;
	this->SearchSettings.prefX = MONITOR_CENTER_X - this->Aimbot.fov / 2 + this->SearchSettings.refX;
	this->SearchSettings.prefY = MONITOR_CENTER_Y - this->Aimbot.fov / 2 + this->SearchSettings.refY;

}

User::~User() {
	CSimpleIniA ini;
	ini.SetUnicode();
	SI_Error rc = ini.LoadFile(_("User.ini"));
	if (rc < 0) 
	{ 
		std::ofstream{ _("User.ini") };
		ini.LoadFile(_("User.ini"));
	}

	ini.SetDoubleValue(_("Key Binds"), _("Aim"), this->Binds.aim);
	ini.SetDoubleValue(_("Key Binds"), _("Hide Menu"), this->Binds.toggleMenu);

	ini.SetDoubleValue(_("Aimbot"), _("Strength"), this->Aimbot.strength);
	ini.SetDoubleValue(_("Aimbot"), _("FOV"), this->Aimbot.fov);
	ini.SetDoubleValue(_("Aimbot"), _("Offset X"), this->Aimbot.offsetX);
	ini.SetDoubleValue(_("Aimbot"), _("Offset Y"), this->Aimbot.offsetY);

	ini.SetDoubleValue(_("Search Settings"), _("Color"), this->SearchSettings.color);
	ini.SetDoubleValue(_("Search Settings"), _("Variation"), this->SearchSettings.colorVariation);
	ini.SetDoubleValue(_("Search Settings"), _("Size Search"), this->SearchSettings.sizeSearch);
	ini.SetDoubleValue(_("Search Settings"), _("Minimum Match"), this->SearchSettings.minMatch);
	ini.SetDoubleValue(_("Search Settings"), _("Reference X"), this->SearchSettings.refX);
	ini.SetDoubleValue(_("Search Settings"), _("Reference Y"), this->SearchSettings.refY);

	ini.SetBoolValue(_("Data"), _("Debug"), false);

	ini.SaveFile(_("User.ini"));
}