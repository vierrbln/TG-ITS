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
@file main.c
 *
@brief Include the main function and all UIR callbacks
in physical.ini
 *
@version 1.0.0.0
 *
@author Robert Renner <A HREF="mailto:4r@sw-its.net">4r@sw-its.net</A>\n

Language: ANSI-C ISO/IEC9899:1990
 *
<b>History:</b>
- <b>02.12.04 R.Renner</b>
- Initial revision
- <b>15.04.08 R.Renner</b>
- Check License -> diff trial or full version

 ******************************************************************************
 *****************************************************************************/

/* INCLUDE FILES ************************************************************/
#include <cviauto.h>
#include "main.h"
#include "resmgr.h"

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
main
 *
@brief Main function
 *
@param argc: Count of command line arguments
@param *argv: Command line arguments (Array of strings)
 *
@return Exit error codes
 *****************************************************************************/
int main(int argc, char* argv[])
{
   short sLicenseOK;
   short sErrorOccurred;
   long lErrorCode;
   char cErrorMessage[1024];
   char cSystemID[1024];
   if (InitCVIRTE(0, argv, 0) == 0)
   {
      return  - 1;
   }
   /* out of memory */

   //Check license
   /*RESMGR_Setup (0, "", "", &sErrorOccurred, &lErrorCode, cErrorMessage);
   RESMGR_Read_ROM (0, cSystemID, &sErrorOccurred, &lErrorCode, cErrorMessage);
   RESMGR_Cleanup (0, &sErrorOccurred, &lErrorCode, cErrorMessage);
   sLicenseOK = lc_CheckLicense ("SW-ITS", cSystemID);
   if (!sLicenseOK) {
   sDemoMode = 1;
   } else {
   sDemoMode = 0;
   }   */


   sLicenseOK = TRUE;
   sDemoMode = FALSE;

   CA_InitActiveXThreadStyleForCurrentThread(0, COINIT_APARTMENTTHREADED);

   if ((iMainPanelHandle = LoadPanel(0, "resources\\phy.uir", PANEL)) < 0)
   {
      return  - 1;
   }
   if ((iEditPanelHandle = LoadPanel(iMainPanelHandle, "resources\\phy.uir", EDIT)) < 0)
   {
      return  - 1;
   }
   if ((iPhysExportPanelHandle = LoadPanel(iMainPanelHandle, "resources\\phy.uir", EXPORT)) < 0)
   {
      return  - 1;
   }
   if ((gSplash = LoadPanel(0, "resources\\Splash.uir", SPLASH)) < 0)
   {
      return  - 1;
   }
   if ((iScanPanelHandle = LoadPanel(0, "resources\\phy.uir", PANEL_2)) < 0)
   {
      return  - 1;
   }
   if ((iSADPanelHandle = LoadPanel(0, "resources\\phy.uir", PANEL_3)) < 0)
   {
      return  - 1;
   }
   iMenuHandle = GetPanelMenuBar(iMainPanelHandle);
   GetProjectDir(cProjectDir);
   iShouldQuitProgramm = FALSE;
   iError = viOpenDefaultRM(&SessionDefRM);
   if (iError)
   {
      HandleError("viOpenDefaultRM", iError);
      return 0;
   }

   //GPIB settings
   GpibSAD = NO_SAD;
   GpibTimeOut = T1s;
   GpibEosEnable = TRUE;
   GpibEosSign = LINEFEED;

   SetActiveCtrl(iMainPanelHandle, PANEL_STARTSCAN);

   DisplayPanel(iMainPanelHandle);
   RunUserInterface();
   DiscardPanel(iMainPanelHandle);
   return 0;
}

/* FUNCTION *****************************************************************/
/**
PanelCallback
 *
@brief Callback function of main panel (PANEL defined in phy.h)
 *
@param panel: Specifier for a particular panel that is currently in memory
@param event: Defined as constant, located in the .uir header file
@param callbackData: Callback data of this function
@param eventData1: Contain keycode information
@param eventData2: Contain keycode information
 *
@return error code
 *****************************************************************************/
int CVICALLBACK PanelCallback(int panel, int event, void* callbackData, int eventData1, int eventData2)
{
   switch (event)
   {
      case EVENT_GOT_FOCUS:

         break;
      case EVENT_LOST_FOCUS:

         break;
      case EVENT_CLOSE:
         if (iMadeChanges)
         {
            if (ConfirmPopup("TG-ITS", "Do you want quit this program, whithout saving changes?\nAll informations obtained from the scanning process,\nwill be gone!"))
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
         break;
   }
   return 0;
}

/* FUNCTION *****************************************************************/
/**
HideOwnPanel
 *
@brief Callback function of EXPORT (defined in phy.h)
 *
@param panel: Specifier for a particular panel that is currently in memory
@param event: Defined as constant, located in the .uir header file
@param callbackData: Callback data of this function
@param eventData1: Contain keycode information
@param eventData2: Contain keycode information
 *
@return error code
 *****************************************************************************/
int CVICALLBACK HideOwnPanel(int panel, int event, void* callbackData, int eventData1, int eventData2)
{

   switch (event)
   {
      case EVENT_GOT_FOCUS:

         break;
      case EVENT_LOST_FOCUS:
         if (!iShouldClose)
         {
            SetActivePanel(panel);
         }
         break;
      case EVENT_CLOSE:

         break;
   }
   return 0;
}

/* FUNCTION *****************************************************************/
/**
PanelCallback
 *
@brief Callback function of PANEL_STARTSCAN (defined in phy.h)
 *
@param panel: Specifier for a particular panel that is currently in memory
@param event: Defined as constant, located in the .uir header file
@param callbackData: Callback data of this function
@param eventData1: Contain keycode information
@param eventData2: Contain keycode information
 *
@return error code
 *****************************************************************************/
int CVICALLBACK StartScan(int panel, int control, int event, void* callbackData, int eventData1, int eventData2)
{
   switch (event)
   {
      case EVENT_COMMIT:
         SearchForDevices();
         break;
   }
   return 0;
}

/* FUNCTION *****************************************************************/
/**
StartExport
 *
@brief Callback function of PANEL_STARTEXPORT (defined in phy.h)
 *
@param panel: Specifier for a particular panel that is currently in memory
@param event: Defined as constant, located in the .uir header file
@param callbackData: Callback data of this function
@param eventData1: Contain keycode information
@param eventData2: Contain keycode information
 *
@return error code
 *****************************************************************************/
int CVICALLBACK StartExport(int panel, int control, int event, void*callbackData, int eventData1, int eventData2)
{
   switch (event)
   {
      case EVENT_COMMIT:
         StartExportPhysicalIni();
         break;
   }
   return 0;
}

/* FUNCTION *****************************************************************/
/**
ChangeValues
 *
@brief Callback function of PANEL_CANDEVICES, PANEL_DAQDEVICES
PANEL_GPIBDEVICES, PANEL_ASRLDEVICES, PANEL_PXIDEVICES (defined in phy.h)
 *
@param panel: Specifier for a particular panel that is currently in memory
@param event: Defined as constant, located in the .uir header file
@param callbackData: Callback data of this function
@param eventData1: Contain keycode information
@param eventData2: Contain keycode information
 *
@return error code
 *****************************************************************************/
int CVICALLBACK ChangeValues(int panel, int control, int event, void*callbackData, int eventData1, int eventData2)
{
   int iIndex;
   int iDeviceID;
   switch (event)
   {
      case EVENT_LEFT_DOUBLE_CLICK:
         if (iDevicesFound)
         {
            GetCtrlIndex(panel, control, &iIndex);
            if (iIndex < 0)
            {
               break;
            }
            GetValueFromIndex(panel, control, iIndex, &iDeviceID);
            pEditRessource = FindID(iDeviceID);
            SetValue(pEditRessource);
            iShouldClose = 0;
            InstallPopup(iEditPanelHandle);
            SetActiveCtrl(iEditPanelHandle, EDIT_ECS);
         }
         break;
   }
   return 0;
}

/* FUNCTION *****************************************************************/
/**
QuitWithoutSaving
 *
@brief Callback function of EDIT_ECS (defined in phy.h)
 *
@param panel: Specifier for a particular panel that is currently in memory
@param event: Defined as constant, located in the .uir header file
@param callbackData: Callback data of this function
@param eventData1: Contain keycode information
@param eventData2: Contain keycode information
 *
@return error code
 *****************************************************************************/
int CVICALLBACK QuitWithoutSaving(int panel, int control, int event, void*callbackData, int eventData1, int eventData2)
{
   int Hide, Confirm;
   switch (event)
   {
      case EVENT_COMMIT:
         GetCtrlVal(iEditPanelHandle, EDIT_HIDE, &Hide);
         if (Hide)
         {
            iShouldClose = 1;
            RemovePopup(iEditPanelHandle);
         }
         else
         {
            pEditRessource = pEditRessource->next;
            if (!pEditRessource)
            {
               pEditRessource = pFirstRessource;
            }
            SetValue(pEditRessource);
            if (!pEditRessource->next)
            {
               SetCtrlAttribute(iEditPanelHandle, EDIT_ECS, ATTR_LABEL_TEXT, "Goto first device");
               SetCtrlAttribute(iEditPanelHandle, EDIT_OK, ATTR_LABEL_TEXT, "Apply & first");
            }
            else
            {
               SetCtrlAttribute(iEditPanelHandle, EDIT_ECS, ATTR_LABEL_TEXT, "Goto next device");
               SetCtrlAttribute(iEditPanelHandle, EDIT_OK, ATTR_LABEL_TEXT, "Apply & next");
            }
         }
         break;
   }
   return 0;
}


/* FUNCTION *****************************************************************/
/**
ApplyChanges
 *
@brief Callback function of EDIT_OK (defined in phy.h)
 *
@param panel: Specifier for a particular panel that is currently in memory
@param event: Defined as constant, located in the .uir header file
@param callbackData: Callback data of this function
@param eventData1: Contain keycode information
@param eventData2: Contain keycode information
 *
@return error code
 *****************************************************************************/
int CVICALLBACK ApplyChanges(int panel, int control, int event, void*callbackData, int eventData1, int eventData2)
{
   int Hide, Confirm;
   switch (event)
   {
      case EVENT_COMMIT:
         GetCtrlVal(iEditPanelHandle, EDIT_HIDE, &Hide);
         ApplyValues(pEditRessource);
         iMadeChanges = 1;
         if (Hide)
         {
            iShouldClose = 1;
            RemovePopup(iEditPanelHandle);
         }
         else
         {
            pEditRessource = pEditRessource->next;
            if (!pEditRessource)
            {
               pEditRessource = pFirstRessource;
            }
            SetValue(pEditRessource);
            if (!pEditRessource->next)
            {
               SetCtrlAttribute(iEditPanelHandle, EDIT_ECS, ATTR_LABEL_TEXT, "Goto first device");
               SetCtrlAttribute(iEditPanelHandle, EDIT_OK, ATTR_LABEL_TEXT, "Apply & first");
            }
            else
            {
               SetCtrlAttribute(iEditPanelHandle, EDIT_ECS, ATTR_LABEL_TEXT, "Goto next device");
               SetCtrlAttribute(iEditPanelHandle, EDIT_OK, ATTR_LABEL_TEXT, "Apply & next");
            }
         }
         break;
   }
   return 0;
}

/* FUNCTION *****************************************************************/
/**
ExportPhysical
 *
@brief Callback function of EXPORT_EXPORT (defined in phy.h)
 *
@param panel: Specifier for a particular panel that is currently in memory
@param event: Defined as constant, located in the .uir header file
@param callbackData: Callback data of this function
@param eventData1: Contain keycode information
@param eventData2: Contain keycode information
 *
@return error code
 *****************************************************************************/
int CVICALLBACK ExportPhysical(int panel, int control, int event, void*callbackData, int eventData1, int eventData2)
{
   int iAutoCoupling;
   int iStatus;
   char cPathName[MAX_PATHNAME_LEN];
   FILE* pFile = NULL;
   int iFile;

   /* read "cLastFilePath" from a textfile and check if path/file is valid
   sprintf(cPathName, "%s\\resources\\savepath.txt", cProjectDir);
   pFile = fopen(cPathName, "r");
   iFile = OpenFile (cPathName, VAL_READ_ONLY, VAL_OPEN_AS_IS, VAL_ASCII);
   iStatus = ReadLine (iFile, cLastFilePath, MAX_PATHNAME_LEN);
   if (iStatus < 1)
   {
   sprintf(cLastFilePath, cProjectDir);
   }
   // iFile = OpenFile (cLastFilePath, VAL_READ_ONLY, VAL_OPEN_AS_IS, VAL_ASCII);
   if (iFile == -1)
   {
   sprintf(cLastFilePath, cProjectDir);
   }
   fclose(pFile);   */


   switch (event)
   {
      case EVENT_COMMIT:

         GetCtrlVal(panel, EXPORT_AUTOCOUPLING, &iAutoCoupling);

         if (iWantPhyIni)
         {
            iError = WritePhysicalIni(iAutoCoupling);
         }

         if (iWantAppIni)
         {
            iError = WriteApplicationIni();
         }

         if (iWantTstSeq)
         {
            iError = WriteTeststandSeq();
         }

         if (iShouldQuitProgramm == TRUE)
         {
            QuitUserInterface(0);
         }
         else
         {
            iMadeChanges = 0;
            if (!iError)
            {
               if (sDemoMode)
               {
                  MessagePopup("TG-ITS", "This trial version could not save any file. To get a full version\ncontact Spectral Electronic Forschungs- und Produktions- GmbH!\nhttp://www.spectral.de");
                  LaunchExecutable("C:\\Programme\\Internet Explorer\\IEXPLORE.EXE \"http://www.spectral.de\"");

               }
               else
               {
                  // only one file exported
                  if (iWantPhyIni && !iWantAppIni && !iWantTstSeq)
                  {
                     MessagePopup("TG-ITS", "Export of physical.ini successfully completed!");
                  }

                  if (!iWantPhyIni && iWantAppIni && !iWantTstSeq)
                  {
                     MessagePopup("TG-ITS", "Export of application.ini successfully completed!");
                  }

                  if (!iWantPhyIni && !iWantAppIni && iWantTstSeq)
                  {
                     MessagePopup("TG-ITS", "Export of NI Teststand Sequence successfully completed!");
                  }

                  // two files exported
                  if (iWantPhyIni && iWantAppIni && !iWantTstSeq)
                  {
                     MessagePopup("TG-ITS", "Export of physical.ini and application.ini successfully completed!");
                  }

                  if (iWantPhyIni && !iWantAppIni && iWantTstSeq)
                  {
                     MessagePopup("TG-ITS", "Export of physical.ini and NI Teststand Sequence successfully completed!");
                  }

                  if (!iWantPhyIni && iWantAppIni && iWantTstSeq)
                  {
                     MessagePopup("TG-ITS", "Export of application.ini and NI Teststand Sequence successfully completed!");
                  }

                  // all files exported
                  if (iWantPhyIni && iWantAppIni && iWantTstSeq)
                  {
                     MessagePopup("TG-ITS", "Export of physical.ini, application.ini and NI Teststand Sequence successfully completed!");
                  }

                  // no file exported
                  if (!iWantPhyIni && !iWantAppIni && !iWantTstSeq)
                  {
                     MessagePopup("TG-ITS", "Export aborted! No file was created.");
                  }

                  // save path
                  /* sprintf(cPathName, "%s\\resources\\savepath.txt", cProjectDir);
                  iStatus = DeleteFile(cPathName);
                  pFile = fopen(cPathName, "w");		
                  fprintf(pFile, "%s", cLastFilePath);
                  iStatus = SetFileAttrs (cPathName, 0, 0, 1, 0);
                  fclose(pFile);  */
               }
            }
            iShouldClose = 1;
            RemovePopup(iPhysExportPanelHandle);
            ClearListCtrl(iPhysExportPanelHandle, EXPORT_EXPORTDEV);
            SetMenuBarAttribute(iMenuHandle, MENU_FILE_SAVEPHYS, ATTR_DIMMED, 0);
            if (iError > 0)
            // ???
            {
               sprintf(cMsgText, "%s\\GenerateApplication.exe %s", cProjectDir, cPhysicalIniPath);
               iError = LaunchExecutable(cMsgText);
               QuitUserInterface(0);
            }
         }
         break;
   }
   return 0;
}

/* FUNCTION *****************************************************************/
/**
Discard
 *
@brief Callback function of EXPORT_DISCARD (defined in phy.h)
 *
@param panel: Specifier for a particular panel that is currently in memory
@param event: Defined as constant, located in the .uir header file
@param callbackData: Callback data of this function
@param eventData1: Contain keycode information
@param eventData2: Contain keycode information
 *
@return error code
 *****************************************************************************/
int CVICALLBACK Discard(int panel, int control, int event, void* callbackData, int eventData1, int eventData2)
{
   switch (event)
   {
      case EVENT_COMMIT:
         iShouldClose = 1;
         RemovePopup(iPhysExportPanelHandle);
         ClearListCtrl(iPhysExportPanelHandle, EXPORT_EXPORTDEV);
         break;
   }
   return 0;
}

/* FUNCTION *****************************************************************/
/**
ChangeHide
 *
@brief Callback function of EDIT_HIDE (defined in phy.h)
 *
@param panel: Specifier for a particular panel that is currently in memory
@param event: Defined as constant, located in the .uir header file
@param callbackData: Callback data of this function
@param eventData1: Contain keycode information
@param eventData2: Contain keycode information
 *
@return error code
 *****************************************************************************/
int CVICALLBACK ChangeHide(int panel, int control, int event, void*callbackData, int eventData1, int eventData2)
{
   int Hide;
   switch (event)
   {
      case EVENT_VAL_CHANGED:
         GetCtrlVal(iEditPanelHandle, EDIT_HIDE, &Hide);
         if (!Hide)
         {
            SetCtrlAttribute(iEditPanelHandle, EDIT_ECS, ATTR_LABEL_TEXT, "Goto next device");
            SetCtrlAttribute(iEditPanelHandle, EDIT_OK, ATTR_LABEL_TEXT, "Apply & next");
         }
         else
         {
            SetCtrlAttribute(iEditPanelHandle, EDIT_ECS, ATTR_LABEL_TEXT, "Quit without saving");
            SetCtrlAttribute(iEditPanelHandle, EDIT_OK, ATTR_LABEL_TEXT, "Apply");
         }
         break;
   }
   return 0;
}

/* FUNCTION *****************************************************************/
/**
SelectDriver
 *
@brief Callback function of EDIT_SELECTDRIVER (defined in phy.h)
 *
@param panel: Specifier for a particular panel that is currently in memory
@param event: Defined as constant, located in the .uir header file
@param callbackData: Callback data of this function
@param eventData1: Contain keycode information
@param eventData2: Contain keycode information
 *
@return error code
 *****************************************************************************/
int CVICALLBACK SelectDriver(int panel, int control, int event, void*callbackData, int eventData1, int eventData2)
{
   char cPathName[512];
   switch (event)
   {
      case EVENT_COMMIT:
         iError = FileSelectPopup(cProjectDir, "*.dll", "", "Select Driver-Dll", VAL_SELECT_BUTTON, 0, 1, 1, 0, cPathName);
         if (iError == 1)
         {
            SetCtrlVal(iEditPanelHandle, EDIT_DRIVERDLL, cPathName);
         }
         break;
   }
   return 0;
}

/**************************************************************************
 *                                                                        *
 **************************************************************************/

int CVICALLBACK PictureCallBack(int panel, int control, int event, void* callbackData, int eventData1, int eventData2)
{
   switch (event)
   {
      case EVENT_LEFT_CLICK:
         HidePanel(gSplash);
         break;
   }
   return 0;
}

/**************************************************************************
 *                                                                        *
 **************************************************************************/


int CVICALLBACK SlpashCallBack(int panel, int event, void* callbackData, int eventData1, int eventData2)
{
   switch (event)
   {
      case EVENT_COMMIT:
         HidePanel(gSplash);
         break;
   }
   return 0;
}

/* FUNCTION *****************************************************************/
/**
CloseSAD
 *
@brief Callback function of PANEL_3_COMMANDBUTTON (defined in phy.h)
 *
@param panel: Specifier for a particular panel that is currently in memory
@param event: Defined as constant, located in the .uir header file
@param callbackData: Callback data of this function
@param eventData1: Contain keycode information
@param eventData2: Contain keycode information
 *
@return error code
 *****************************************************************************/
int CVICALLBACK CloseSAD(int panel, int control, int event, void* callbackData, int eventData1, int eventData2)
{
   switch (event)
   {
      case EVENT_COMMIT:
         GetCtrlVal(iSADPanelHandle, PANEL_3_TOGGLEBUTTON, &GpibSAD);
         if (GpibSAD)
         {
            GetCtrlVal(iSADPanelHandle, PANEL_3_NUMERICKNOB, &GpibSAD);
         }
         RemovePopup(iSADPanelHandle);
         if (GpibSAD)
         {
            SetMenuBarAttribute(iMenuHandle, MENU_OPTIONS_GIBPSAD, ATTR_CHECKED, 1);
            sprintf(cMsgText, "GPIB Secondary Adress -> %d", GpibSAD);
            SetMenuBarAttribute(iMenuHandle, MENU_OPTIONS_GIBPSAD, ATTR_ITEM_NAME, cMsgText);
         }
         else
         {
            SetMenuBarAttribute(iMenuHandle, MENU_OPTIONS_GIBPSAD, ATTR_CHECKED, 0);
            sprintf(cMsgText, "GPIB Secondary Adress");
            SetMenuBarAttribute(iMenuHandle, MENU_OPTIONS_GIBPSAD, ATTR_ITEM_NAME, cMsgText);
         }
         break;
   }
   return 0;
}

/* FUNCTION *****************************************************************/
/**
EnableSAD
 *
@brief Callback function of PANEL_3_TOGGLEBUTTON (defined in phy.h)
 *
@param panel: Specifier for a particular panel that is currently in memory
@param event: Defined as constant, located in the .uir header file
@param callbackData: Callback data of this function
@param eventData1: Contain keycode information
@param eventData2: Contain keycode information
 *
@return error code
 *****************************************************************************/
int CVICALLBACK EnableSAD(int panel, int control, int event, void* callbackData, int eventData1, int eventData2)
{
   int iCtrlValue;
   switch (event)
   {
      case EVENT_COMMIT:
         GetCtrlVal(panel, control, &iCtrlValue);
         SetCtrlAttribute(panel, PANEL_3_NUMERICKNOB, ATTR_DIMMED, !iCtrlValue);
         break;
   }
   return 0;
}

/* FUNCTION *****************************************************************/
/**
DimmSysChExp
 *
@brief Callback function, will dimm SysCh if ABus is unchecked. (defined in phy.h)
 *
@param panel: Specifier for a particular panel that is currently in memory
@param event: Defined as constant, located in the .uir header file
@param callbackData: Callback data of this function
@param eventData1: Contain keycode information
@param eventData2: Contain keycode information
 *
@return error code
 *****************************************************************************/
int CVICALLBACK DimmSysChExp(int panel, int control, int event, void* callbackData, int eventData1, int eventData2)
{
   int iCtrlValue;
   switch (event)
   {
      case EVENT_COMMIT:
         GetCtrlVal(panel, EXPORT_EXPORTABUS, &iCtrlValue);
         if (iCtrlValue)
         {
            SetCtrlAttribute(panel, EXPORT_EXPORTSYSCH, ATTR_DIMMED, 0);
         }
         else
         {
            SetCtrlAttribute(panel, EXPORT_EXPORTSYSCH, ATTR_DIMMED, 1);
            SetCtrlVal(panel, EXPORT_EXPORTSYSCH, 0);
         }
         break;
   }
   return 0;
}

/* FUNCTION *****************************************************************/
/**
WantPhyIni
 *
@brief Callback function,dimms the export button in main panel, in different
cases. (defined in phy.h)
 *
@param panel: Specifier for a particular panel that is currently in memory
@param event: Defined as constant, located in the .uir header file
@param callbackData: Callback data of this function
@param eventData1: Contain keycode information
@param eventData2: Contain keycode information
 *
@return error code
 *****************************************************************************/
int CVICALLBACK WantPhyIni(int panel, int control, int event, void* callbackData, int eventData1, int eventData2)
{
   int iCtrlValue;
   switch (event)
   {
      case EVENT_COMMIT:

         // GetCtrlVal(panel, EXPORT_EXPORTABUS, &iWantPhyIni);
         /*if (iCtrlValue)
         {
         iWantPhyIni = 1;
         }
         else
         {
         SetCtrlAttribute (panel, EXPORT_EXPORTSYSCH, ATTR_DIMMED, 1);
         SetCtrlVal (panel, EXPORT_EXPORTSYSCH, 0);
         }
          */


         GetCtrlVal(panel, PANEL_CHECKBOX_PHYINI, &iWantPhyIni);
         if (!iWantPhyIni && !iWantAppIni && !iWantTstSeq)
         {
            SetCtrlAttribute(panel, PANEL_STARTEXPORT, ATTR_DIMMED, 1);
         }
         else
         {
            SetCtrlAttribute(panel, PANEL_STARTEXPORT, ATTR_DIMMED, 0);
         }
         if (!iWantPhyIni || !iWantAppIni)
         {
            SetCtrlVal(panel, PANEL_CHECKBOX_TSTSEQ, 0);
            iWantTstSeq = 0;
            SetCtrlAttribute(panel, PANEL_CHECKBOX_TSTSEQ, ATTR_DIMMED, 1);
         }
         if (iWantPhyIni && iWantAppIni)
         {
            SetCtrlAttribute(panel, PANEL_CHECKBOX_TSTSEQ, ATTR_DIMMED, 0);
         }
         break;
   }
   return 0;
}

/* FUNCTION *****************************************************************/
/**
WantAppIni
 *
@brief Callback function, dimms the export button in main panel, in different
cases. (defined in phy.h)
 *
@param panel: Specifier for a particular panel that is currently in memory
@param event: Defined as constant, located in the .uir header file
@param callbackData: Callback data of this function
@param eventData1: Contain keycode information
@param eventData2: Contain keycode information
 *
@return error code
 *****************************************************************************/

int CVICALLBACK WantAppIni(int panel, int control, int event, void* callbackData, int eventData1, int eventData2)
{
   switch (event)
   {
      case EVENT_COMMIT:
         GetCtrlVal(panel, PANEL_CHECKBOX_APPINI, &iWantAppIni);
         if (!iWantPhyIni && !iWantAppIni && !iWantTstSeq)
         {
            SetCtrlAttribute(panel, PANEL_STARTEXPORT, ATTR_DIMMED, 1);
         }
         else
         {
            SetCtrlAttribute(panel, PANEL_STARTEXPORT, ATTR_DIMMED, 0);
         }
         if (!iWantPhyIni || !iWantAppIni)
         {
            SetCtrlVal(panel, PANEL_CHECKBOX_TSTSEQ, 0);
            iWantTstSeq = 0;
            SetCtrlAttribute(panel, PANEL_CHECKBOX_TSTSEQ, ATTR_DIMMED, 1);
         }
         if (iWantPhyIni && iWantAppIni)
         {
            SetCtrlAttribute(panel, PANEL_CHECKBOX_TSTSEQ, ATTR_DIMMED, 0);
         }
         break;
   }
   return 0;
}

/* FUNCTION *****************************************************************/
/**
WantTstSeq
 *
@brief Callback function, dimms the export button in main panel, in different
cases. (defined in phy.h)
 *
@param panel: Specifier for a particular panel that is currently in memory
@param event: Defined as constant, located in the .uir header file
@param callbackData: Callback data of this function
@param eventData1: Contain keycode information
@param eventData2: Contain keycode information
 *
@return error code
 *****************************************************************************/

int CVICALLBACK WantTstSeq(int panel, int control, int event, void* callbackData, int eventData1, int eventData2)
{
   switch (event)
   {
      case EVENT_COMMIT:
         GetCtrlVal(panel, PANEL_CHECKBOX_TSTSEQ, &iWantTstSeq);
         if (!iWantPhyIni && !iWantAppIni && !iWantTstSeq)
         {
            SetCtrlAttribute(panel, PANEL_STARTEXPORT, ATTR_DIMMED, 1);
         }
         else
         {
            SetCtrlAttribute(panel, PANEL_STARTEXPORT, ATTR_DIMMED, 0);
         }
         break;
   }
   return 0;
}

/* FUNCTION *****************************************************************/
/**
DevListBox
 *
@brief Callback function,will check if minimum one PSAM and one PMB is checked
in the list box. (defined in phy.h)
 *
@param panel: Specifier for a particular panel that is currently in memory
@param event: Defined as constant, located in the .uir header file
@param callbackData: Callback data of this function
@param eventData1: Contain keycode information
@param eventData2: Contain keycode information
 *
@return error code
 *****************************************************************************/

int CVICALLBACK DevListBox(int panel, int control, int event, void* callbackData, int eventData1, int eventData2)
{
   int iIndex, isChecked, iCurrentIndex, i;
   char cLabel[128];
   ressource* ptr;

   switch (event)
   {
      case EVENT_COMMIT:

         GetCtrlIndex(panel, control, &iCurrentIndex);

         GetLabelFromIndex(iPhysExportPanelHandle, EXPORT_EXPORTDEV, iCurrentIndex, cLabel);

         ptr = pFirstRessource;
         while (ptr)
         {
            if (strcmp(ptr->cBenchName, cLabel) == 0)
            {
               if (strcmp(ptr->cType, "PSAM") == 0)
               {
                  IsListItemChecked(iPhysExportPanelHandle, EXPORT_EXPORTDEV, iCurrentIndex, &isChecked);
                  if (!isChecked)
                  {
                     iPSAMcheckedOnList--;
                     if (!iPSAMcheckedOnList)
                     {
                        iPSAMcheckedOnList++;
                        CheckListItem(iPhysExportPanelHandle, EXPORT_EXPORTDEV, iCurrentIndex, 1);
                        if (!iPSAMCheckWarning)
                        {
                           MessagePopup("TG-ITS", "At least one DMM has to be registered");
                           iPSAMCheckWarning = 1;
                        }
                     }
                  }
                  if (isChecked)
                  {
                     iPSAMcheckedOnList++;
                  }
               }
               if (strcmp(ptr->cType, "PMB") == 0)
               {
                  IsListItemChecked(iPhysExportPanelHandle, EXPORT_EXPORTDEV, iCurrentIndex, &isChecked);
                  if (!isChecked)
                  {
                     iPMBcheckedOnList--;
                     if (!iPMBcheckedOnList)
                     {
                        iPMBcheckedOnList++;
                        CheckListItem(iPhysExportPanelHandle, EXPORT_EXPORTDEV, iCurrentIndex, 1);
                        if (!iPMBCheckWarning)
                        {
                           MessagePopup("TG-ITS", "At least one matrix module has to be registered");
                           iPMBCheckWarning = 1;
                        }
                     }
                  }
                  if (isChecked)
                  {
                     iPMBcheckedOnList++;
                  }
               }
               ptr->iMarkedForExport = 1;
               break;
            }
            else
            {
               ptr = ptr->next;
            }
         }
   }
   return 0;
}

/******************************************************************************/
// END OF FILE
