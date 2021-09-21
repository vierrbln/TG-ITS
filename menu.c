/****************************************************************************/
/**

Copyright 2007-2021 Robert Renner

This file is part of SW-ITS.

SW-ITS is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

SW-ITS is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with SW-ITS.  If not, see <http://www.gnu.org/licenses/>.

Diese Datei ist Teil von SW-ITS.

SW-ITS ist Freie Software: Sie können es unter den Bedingungen
der GNU General Public License, wie von der Free Software Foundation,
Version 3 der Lizenz oder (nach Ihrer Wahl) jeder neueren
veröffentlichten Version, weiter verteilen und/oder modifizieren.

SW-ITS wird in der Hoffnung, dass es nützlich sein wird, aber
OHNE JEDE GEWÄHRLEISTUNG, bereitgestellt; sogar ohne die implizite
Gewährleistung der MARKTFÄHIGKEIT oder EIGNUNG FÜR EINEN BESTIMMTEN ZWECK.
Siehe die GNU General Public License für weitere Details.

Sie sollten eine Kopie der GNU General Public License zusammen mit diesem
Programm erhalten haben. Wenn nicht, siehe <https://www.gnu.org/licenses/>.

/****************************************************************************/
/**
@file menu.c
 *
@brief Include menu bar callbacks
 *
@version 1.0.0.0
 *
@author Robert Renner <A HREF="mailto:4r@sw-its.net">4r@sw-its.net</A>\n

Language: ANSI-C ISO/IEC9899:1990
 *
<b>History:</b>
- <b>03.12.04 R.Renner</b>
- Enable HTML help menu item
- <b>02.12.04 R.Renner</b>
- Initial revision

 ******************************************************************************
 *****************************************************************************/

/* INCLUDE FILES ************************************************************/
#include "main.h"
#include <userint.h>
#include "phy.h"

/* GLOBAL CONSTANT DEFINITIONS **********************************************/

/* GLOBAL VARIABLE DEFINITIONS **********************************************/

/* LOCAL TYPE DEFINITIONS ***************************************************/

/* LOCAL CONSTANT DEFINITIONS ***********************************************/

/* LOCAL VARIABLE DEFINITIONS ***********************************************/

/* LOCAL MACRO DEFINITIONS **************************************************/

/* LOCAL FUNCTION DECLARATIONS **********************************************/

/* LOCAL FUNCTION DEFINITIONS ***********************************************/

/* GLOBAL FUNCTION DECLARATIONS *********************************************/

/* GLOABL FUNCTION DEFINITIONS **********************************************/

/* FUNCTION *****************************************************************/
/**
OpenPhysicalIni
 *
@brief Callback function of MENU_FILE_OPENPHYSICAL (defined in phy.h). This
function should open a phsyical.ini for
@todo  The function currently not implemented
 *
@param menuBar: Specifier for a menu bar that is currently in memory
@param menuItem: Defined as constant, located in the .uir header file
@param callbackData: Callback data of this function
@param panel: Specifier for a particular panel that is currently in memory
 *
@return void
 *****************************************************************************/
void CVICALLBACK OpenPhysicalIni(int menuBar, int menuItem, void* callbackData, int panel)
{
   MessagePopup("TG-ITS", "Sorry, this function is not yet implemented!");
}

/* FUNCTION *****************************************************************/
/**
SavePhysicalIni
 *
@brief Callback function of MENU_FILE_SAVEPHYS (defined in phy.h) This function
save current settings into R&S compatible physical.ini
 *
@param menuBar: Specifier for a menu bar that is currently in memory
@param menuItem: Defined as constant, located in the .uir header file
@param callbackData: Callback data of this function
@param panel: Specifier for a particular panel that is currently in memory
 *
@return void
 *****************************************************************************/
void CVICALLBACK SavePhysicalIni(int menuBar, int menuItem, void* callbackData, int panel)
{
   StartExportPhysicalIni();
}

/* FUNCTION *****************************************************************/
/**
QuitProgramm
 *
@brief Callback function of MENU_FILE_QUIT (defined in phy.h) This function
close the application.
 *
@param menuBar: Specifier for a menu bar that is currently in memory
@param menuItem: Defined as constant, located in the .uir header file
@param callbackData: Callback data of this function
@param panel: Specifier for a particular panel that is currently in memory
 *
@return void
 *****************************************************************************/
void CVICALLBACK QuitProgramm(int menuBar, int menuItem, void* callbackData, int panel)
{
   if (iMadeChanges)
   {
      if (ConfirmPopup("TG-ITS", "Do you want quit this program, WITHOUT SAVING changes?\nAll informations obtained from the scanning process,\nwill be gone!"))
      {
         QuitUserInterface(0);
      }
      else
      {
         iShouldQuitProgramm = TRUE;
         StartExportPhysicalIni();
      }
   }
   else
   {
      if (ConfirmPopup("TG-ITS", "Are you sure you want to quit?"))
      {
         QuitUserInterface(0);
      }
   }
}

/* FUNCTION *****************************************************************/
/**
NewScan
 *
@brief Callback function of MENU_EDIT_NEWSCAN (defined in phy.h) This function
start a new scan overall tsvp resources
 *
@param menuBar: Specifier for a menu bar that is currently in memory
@param menuItem: Defined as constant, located in the .uir header file
@param callbackData: Callback data of this function
@param panel: Specifier for a particular panel that is currently in memory
 *
@return void
 *****************************************************************************/
void CVICALLBACK NewScan(int menuBar, int menuItem, void* callbackData, int panel)
{
   SearchForDevices();
}

/* FUNCTION *****************************************************************/
/**
OpenHelp
 *
@brief Callback function of MENU_HELP_HELP (defined in phy.h) This function
open the CHM file.
 *
@param menuBar: Specifier for a menu bar that is currently in memory
@param menuItem: Defined as constant, located in the .uir header file
@param callbackData: Callback data of this function
@param panel: Specifier for a particular panel that is currently in memory
 *
@return void
 *****************************************************************************/
void CVICALLBACK OpenHelp(int menuBar, int menuItem, void* callbackData, int panel)
{
   char cPath[300];
   int iError;
   sprintf(cPath, "%s\\resources\\TG-ITS.chm", cProjectDir);
   iError = ShowHtmlHelp(cPath, HH_DISPLAY_TOPIC, 0);
   if (iError)
   {
      MessagePopup("TG-ITS", "Cannot open help file of this tool. Check install folder!");
   }
}

/* FUNCTION *****************************************************************/
/**
OpenSplash
 *
@brief Callback function of MENU_HELP_ABOUT (defined in phy.h) This function
open the version splash popup.
 *
@param menuBar: Specifier for a menu bar that is currently in memory
@param menuItem: Defined as constant, located in the .uir header file
@param callbackData: Callback data of this function
@param panel: Specifier for a particular panel that is currently in memory
 *
@return void
 *****************************************************************************/
void CVICALLBACK OpenSplash(int menuBar, int menuItem, void* callbackData, int panel)
{
   char cTextMessage[1024];
   sprintf(cTextMessage, "TG-ITS TemplateGenerator - Version %s ", VERSION);
   SetCtrlVal(gSplash, SPLASH_SELECTEDSEQ, cTextMessage);

   SetCtrlAttribute(gSplash, SPLASH_SELECTEDSEQ, ATTR_TEXT_BGCOLOR, VAL_TRANSPARENT);
   SetCtrlAttribute(gSplash, SPLASH_LABEL, ATTR_TEXT_BGCOLOR, VAL_TRANSPARENT);
   SetCtrlAttribute(gSplash, SPLASH_PRODUCT, ATTR_TEXT_BGCOLOR, VAL_TRANSPARENT);


   DisplayPanel(gSplash);
}

/* FUNCTION *****************************************************************/
/**
EditRessource
 *
@brief Callback function of MENU_EDIT_EDIT (defined in phy.h). Menu item are
created during the run time.
 *
@param menuBar: Specifier for a menu bar that is currently in memory
@param menuItem: Defined as constant, located in the .uir header file
@param callbackData: Callback data of this function
@param panel: Specifier for a particular panel that is currently in memory
 *
@return void
 *****************************************************************************/
void CVICALLBACK EditRessource(int menuBar, int menuItem, void* callbackData, int panel)
{
   ressource* ptr;
   if (iDevicesFound)
   {
      ptr = pFirstRessource;
      while (ptr->menuID != menuItem)
      {
         ptr = ptr->next;
      }
      pEditRessource = ptr;
      SetValue(pEditRessource);
      InstallPopup(iEditPanelHandle);
      SetActiveCtrl(iEditPanelHandle, EDIT_ECS);
   }
}

/* FUNCTION *****************************************************************/
/**
ChangeSecAdress
 *
@brief Callback function of MENU_OPTIONS_GIBPSAD (defined in phy.h).
 *
@param menuBar: Specifier for a menu bar that is currently in memory
@param menuItem: Defined as constant, located in the .uir header file
@param callbackData: Callback data of this function
@param panel: Specifier for a particular panel that is currently in memory
 *
@return void
 *****************************************************************************/
void CVICALLBACK ChangeSecAdress(int menuBar, int menuItem, void* callbackData, int panel)
{
   InstallPopup(iSADPanelHandle);
}

/* FUNCTION *****************************************************************/
/**
ChangeEOS
 *
@brief Callback function of MENU_OPTIONS_GIBPEOS_CR ... (defined in phy.h).
 *
@param menuBar: Specifier for a menu bar that is currently in memory
@param menuItem: Defined as constant, located in the .uir header file
@param callbackData: Callback data of this function
@param panel: Specifier for a particular panel that is currently in memory
 *
@return void
 *****************************************************************************/
void CVICALLBACK ChangeEOS(int menuBar, int menuItem, void* callbackData, int panel)
{
   SetMenuBarAttribute(iMenuHandle, MENU_OPTIONS_GIBPEOS_CR, ATTR_CHECKED, 0);
   SetMenuBarAttribute(iMenuHandle, MENU_OPTIONS_GIBPEOS_LF, ATTR_CHECKED, 0);
   SetMenuBarAttribute(iMenuHandle, MENU_OPTIONS_GIBPEOS_NONE, ATTR_CHECKED, 0);

   SetMenuBarAttribute(iMenuHandle, menuItem, ATTR_CHECKED, 1);

   switch (menuItem)
   {
      case MENU_OPTIONS_GIBPEOS_CR:
         GpibEosSign = CARRIAGERETURN;
         GpibEosEnable = TRUE;
         break;
      case MENU_OPTIONS_GIBPEOS_LF:
         GpibEosSign = LINEFEED;
         GpibEosEnable = TRUE;
         break;
      case MENU_OPTIONS_GIBPEOS_NONE:
         GpibEosSign = 0;
         GpibEosEnable = FALSE;
         break;
   }
}

/* FUNCTION *****************************************************************/
/**
ChangeTimeOut
 *
@brief Callback function of MENU_OPTIONS_GIBPTIMEOUT_NOLIMIT ... (defined in phy.h).
 *
@param menuBar: Specifier for a menu bar that is currently in memory
@param menuItem: Defined as constant, located in the .uir header file
@param callbackData: Callback data of this function
@param panel: Specifier for a particular panel that is currently in memory
 *
@return void
 *****************************************************************************/
void CVICALLBACK ChangeTimeOut(int menuBar, int menuItem, void* callbackData, int panel)
{
   SetMenuBarAttribute(iMenuHandle, MENU_OPTIONS_GIBPTIMEOUT_NOLIMIT, ATTR_CHECKED, 0);
   SetMenuBarAttribute(iMenuHandle, MENU_OPTIONS_GIBPTIMEOUT_IB10USEC, ATTR_CHECKED, 0);
   SetMenuBarAttribute(iMenuHandle, MENU_OPTIONS_GIBPTIMEOUT_IB30USEC, ATTR_CHECKED, 0);
   SetMenuBarAttribute(iMenuHandle, MENU_OPTIONS_GIBPTIMEOUT_IB100USEC, ATTR_CHECKED, 0);
   SetMenuBarAttribute(iMenuHandle, MENU_OPTIONS_GIBPTIMEOUT_IB300USEC, ATTR_CHECKED, 0);
   SetMenuBarAttribute(iMenuHandle, MENU_OPTIONS_GIBPTIMEOUT_IB1MSEC, ATTR_CHECKED, 0);
   SetMenuBarAttribute(iMenuHandle, MENU_OPTIONS_GIBPTIMEOUT_IB3MSEC, ATTR_CHECKED, 0);
   SetMenuBarAttribute(iMenuHandle, MENU_OPTIONS_GIBPTIMEOUT_IB10MSEC, ATTR_CHECKED, 0);
   SetMenuBarAttribute(iMenuHandle, MENU_OPTIONS_GIBPTIMEOUT_IB30MSEC, ATTR_CHECKED, 0);
   SetMenuBarAttribute(iMenuHandle, MENU_OPTIONS_GIBPTIMEOUT_IB100MSEC, ATTR_CHECKED, 0);
   SetMenuBarAttribute(iMenuHandle, MENU_OPTIONS_GIBPTIMEOUT_IB300MSEC, ATTR_CHECKED, 0);
   SetMenuBarAttribute(iMenuHandle, MENU_OPTIONS_GIBPTIMEOUT_IB1SEC, ATTR_CHECKED, 0);
   SetMenuBarAttribute(iMenuHandle, MENU_OPTIONS_GIBPTIMEOUT_IB3SEC, ATTR_CHECKED, 0);
   SetMenuBarAttribute(iMenuHandle, MENU_OPTIONS_GIBPTIMEOUT_IB10SEC, ATTR_CHECKED, 0);
   SetMenuBarAttribute(iMenuHandle, MENU_OPTIONS_GIBPTIMEOUT_IB30SEC, ATTR_CHECKED, 0);
   SetMenuBarAttribute(iMenuHandle, MENU_OPTIONS_GIBPTIMEOUT_IB100SEC, ATTR_CHECKED, 0);
   SetMenuBarAttribute(iMenuHandle, MENU_OPTIONS_GIBPTIMEOUT_IB300SEC, ATTR_CHECKED, 0);

   SetMenuBarAttribute(iMenuHandle, menuItem, ATTR_CHECKED, 1);

   switch (menuItem)
   {
      case MENU_OPTIONS_GIBPTIMEOUT_NOLIMIT:
         GpibTimeOut = TNONE;
         break;
      case MENU_OPTIONS_GIBPTIMEOUT_IB10USEC:
         GpibTimeOut = T10us;
         break;
      case MENU_OPTIONS_GIBPTIMEOUT_IB30USEC:
         GpibTimeOut = T30us;
         break;
      case MENU_OPTIONS_GIBPTIMEOUT_IB100USEC:
         GpibTimeOut = T100us;
         break;
      case MENU_OPTIONS_GIBPTIMEOUT_IB300USEC:
         GpibTimeOut = T300us;
         break;
      case MENU_OPTIONS_GIBPTIMEOUT_IB1MSEC:
         GpibTimeOut = T1ms;
         break;
      case MENU_OPTIONS_GIBPTIMEOUT_IB3MSEC:
         GpibTimeOut = T3ms;
         break;
      case MENU_OPTIONS_GIBPTIMEOUT_IB10MSEC:
         GpibTimeOut = T10ms;
         break;
      case MENU_OPTIONS_GIBPTIMEOUT_IB30MSEC:
         GpibTimeOut = T30ms;
         break;
      case MENU_OPTIONS_GIBPTIMEOUT_IB100MSEC:
         GpibTimeOut = T100ms;
         break;
      case MENU_OPTIONS_GIBPTIMEOUT_IB300MSEC:
         GpibTimeOut = T300ms;
         break;
      case MENU_OPTIONS_GIBPTIMEOUT_IB1SEC:
         GpibTimeOut = T1s;
         break;
      case MENU_OPTIONS_GIBPTIMEOUT_IB3SEC:
         GpibTimeOut = T3s;
         break;
      case MENU_OPTIONS_GIBPTIMEOUT_IB10SEC:
         GpibTimeOut = T10s;
         break;
      case MENU_OPTIONS_GIBPTIMEOUT_IB30SEC:
         GpibTimeOut = T30s;
         break;
      case MENU_OPTIONS_GIBPTIMEOUT_IB100SEC:
         GpibTimeOut = T100s;
         break;
      case MENU_OPTIONS_GIBPTIMEOUT_IB300SEC:
         GpibTimeOut = T300s;
         break;
   }
}

/* FUNCTION *****************************************************************/
/**
AddPXIDevice
 *
@brief Callback function of MENU_EDIT_ADDPXI (defined in phy.h). Menu item are
created during the run time.
 *
@param menuBar: Specifier for a menu bar that is currently in memory
@param menuItem: Defined as constant, located in the .uir header file
@param callbackData: Callback data of this function
@param panel: Specifier for a particular panel that is currently in memory
 *
@return void
 *****************************************************************************/
void CVICALLBACK AddPXIDevice(int menuBar, int menuItem, void* callbackData, int panel)
{
   AddNewDev(1);
}

/* FUNCTION *****************************************************************/
/**
AddCANDevice
 *
@brief Callback function of MENU_EDIT_ADDCAN (defined in phy.h). Menu item are
created during the run time.
 *
@param menuBar: Specifier for a menu bar that is currently in memory
@param menuItem: Defined as constant, located in the .uir header file
@param callbackData: Callback data of this function
@param panel: Specifier for a particular panel that is currently in memory
 *
@return void
 *****************************************************************************/
void CVICALLBACK AddCANDevice(int menuBar, int menuItem, void* callbackData, int panel)
{
   AddNewDev(2);
}

/* FUNCTION *****************************************************************/
/**
AddASRLDevice
 *
@brief Callback function of MENU_EDIT_ADDASRL (defined in phy.h). Menu item are
created during the run time.
 *
@param menuBar: Specifier for a menu bar that is currently in memory
@param menuItem: Defined as constant, located in the .uir header file
@param callbackData: Callback data of this function
@param panel: Specifier for a particular panel that is currently in memory
 *
@return void
 *****************************************************************************/
void CVICALLBACK AddASRLDevice(int menuBar, int menuItem, void* callbackData, int panel)
{
   AddNewDev(3);
}

/* FUNCTION *****************************************************************/
/**
AddGPIBDevice
 *
@brief Callback function of MENU_EDIT_ADDGPIB (defined in phy.h). Menu item are
created during the run time.
 *
@param menuBar: Specifier for a menu bar that is currently in memory
@param menuItem: Defined as constant, located in the .uir header file
@param callbackData: Callback data of this function
@param panel: Specifier for a particular panel that is currently in memory
 *
@return void
 *****************************************************************************/
void CVICALLBACK AddGPIBDevice(int menuBar, int menuItem, void* callbackData, int panel)
{
   AddNewDev(4);
}

/* FUNCTION *****************************************************************/
/**
AddDAQDevice
 *
@brief Callback function of MENU_EDIT_ADDDAQ (defined in phy.h). Menu item are
created during the run time.
 *
@param menuBar: Specifier for a menu bar that is currently in memory
@param menuItem: Defined as constant, located in the .uir header file
@param callbackData: Callback data of this function
@param panel: Specifier for a particular panel that is currently in memory
 *
@return void
 *****************************************************************************/
void CVICALLBACK AddDAQdevice(int menuBar, int menuItem, void* callbackData, int panel)
{
   AddNewDev(5);
}

/* FUNCTION *****************************************************************/
/**
AddNewDev
 *
@brief
 *
@param menuBar: Specifier for a menu bar that is currently in memory
@param menuItem: Defined as constant, located in the .uir header file
@param callbackData: Callback data of this function
@param panel: Specifier for a particular panel that is currently in memory
 *
@return void
 *****************************************************************************/
void AddNewDev(int iType)
{
   char cBenchName[300];
   ressource* ptr;
   int iIndex, iNextMenuID;
   int iControlID;

   iControlID = iType + 2; // PANEL_???DEVICES defined in phy.h

   iNewDevAdded++;
   iDevicesFound++;

   sprintf(cBenchName, "NEW DEVICE - %i", iNewDevAdded);
   pFirstRessource = pAppendDevice(pFirstRessource, iType, cBenchName, "", iDevicesFound,  - 1,  - 1); // "0" for "Slot 0" shall mean "manually added"

   InsertListItem(iMainPanelHandle, iControlID,  - 1, cBenchName, iDevicesFound);

   InsertMenuItems();

   ptr = pFirstRessource;
   while ((ptr->iID != iDevicesFound) && (ptr->next != NULL))
   {
      ptr = ptr->next;
   }

   pEditRessource = ptr;
   sprintf(ptr->cRessourceDesc, "please configure manually");
   SetValue(pEditRessource);
   iShouldClose = 0;
   InstallPopup(iEditPanelHandle);
   SetActiveCtrl(iEditPanelHandle, EDIT_ECS);
}

/* FUNCTION *****************************************************************/
/**
DeleteAllManullayAddedDev
 *
@brief Callback function of MENU_EDIT_ADDDAQ (defined in phy.h). Menu item are
created during the run time.
 *
@param menuBar: Specifier for a menu bar that is currently in memory
@param menuItem: Defined as constant, located in the .uir header file
@param callbackData: Callback data of this function
@param panel: Specifier for a particular panel that is currently in memory
 *
@return void
 *****************************************************************************/
void CVICALLBACK DeleteAllManullayAddedDev(int menuBar, int menuItem, void* callbackData, int panel)
{
   ressource* pTMP;
   ressource* pTMPpost;
   int iNoOfManuallyAddedDevices = 0;
   char cMsgTxt[100];

   if (ConfirmPopup("TG-ITS", "Do you really want to remove ALL manually created devices?\nIf not exported into physical.ini, all added information will be gone."))
   {
      pTMP = pFirstRessource;
      pTMPpost = pFirstRessource;
      while (pTMP != NULL)
      {
         pTMPpost = pTMP->next;
         if (pTMP->iSlot == 0)
         {
            iNoOfManuallyAddedDevices++;
            DeleteDev(pTMP);
         }
         pTMP = pTMPpost;
      }
      if (iNoOfManuallyAddedDevices)
      {
         sprintf(cMsgTxt, "Successfully removed %i manually added devices.", iNoOfManuallyAddedDevices);
         MessagePopup("TG-ITS", cMsgTxt);
      }
      else
      {
         MessagePopup("TG-ITS", "Operation aborted. No manually added device was detected in list.");
      }
   }
}

/******************************************************************************/
// END OF FILE
