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
@file write.c
 *
@brief Include all file export operations
 *
@version 1.0.0.0
 *
@author Robert Renner <A HREF="mailto:4r@sw-its.net">4r@sw-its.net</A>\n

Language: ANSI-C ISO/IEC9899:1990
 *
<b>History:</b>
- <b>06.12.04 R.Renner</b>
- Self test extensions implemented
- <b>02.12.04 R.Renner</b>
- Initial revision
- <b>15.10.07 - 07.12.07 A.Killer</b>
- System-Channels added to physical ini
- Building of Application.Ini implemented
- Automated creation of Teststand.Seq implemented
- Several Export-Features added
- <b>05.11.08 R.Renner</b>
- Debugging of some functions
- <b>20.05.09 R.Renner</b>
- Delete errors in PSU system channels
- Insert option for set "Bench name"
- <b>09.09.09 R.Renner</b>
- Delete errors in PSU system channels

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
StartExportPhysicalIni
 *
@brief This function prepares the ExportPanel for user interaction
\n[code extended by Albert Killer]
 *
@param void
 *
@return void
 *****************************************************************************/
void StartExportPhysicalIni(void)
{
   ressource* ptr;
   int iIndex, i;
   char cLabel[128];

   if (!TypeQuantity.PSAMquantity && !TypeQuantity.PMBquantity)
   {
      MessagePopup("TG-ITS", "Neither DMM-devices nor matrix-modules were detected.\nInstall PSAM- as well as PMB-module and rescan!");
      return ;
   }
   if (!TypeQuantity.PSAMquantity)
   {
      MessagePopup("TG-ITS", "No DMM-device was detected.\nInstall PSAM-module and rescan!");
      return ;
   }
   if (!TypeQuantity.PMBquantity)
   {
      MessagePopup("TG-ITS", "No matrix-module was detected.\nInstall PMB-module and rescan!");
      return ;
   }

   if (iDevicesFound)
   {
      if (CheckBenchNames())
      {
         return ;
      }
      ptr = pFirstRessource;
      while (ptr)
      {
         InsertListItem(iPhysExportPanelHandle, EXPORT_EXPORTDEV,  - 1, ptr->cBenchName, ptr->iID);
         ptr = ptr->next;
      }
      GetNumListItems(iPhysExportPanelHandle, EXPORT_EXPORTDEV, &iIndex);
      if (iIndex)
      {
         for (i = 0; i < iIndex; i++)
         {
            GetLabelFromIndex(iPhysExportPanelHandle, EXPORT_EXPORTDEV, i, cLabel);
            ptr = pFirstRessource;
            while (ptr)
            {
               if (strcmp(ptr->cBenchName, cLabel) == 0)
               {
                  if (strcmp(ptr->cType, "PAM") == 0)
                  {
                     CheckListItem(iPhysExportPanelHandle, EXPORT_EXPORTDEV, i, 1);
                  }
                  else if (strcmp(ptr->cType, "PDFT") == 0)
                  {
                     CheckListItem(iPhysExportPanelHandle, EXPORT_EXPORTDEV, i, 1);
                  }
                  else if (strcmp(ptr->cType, "PFG") == 0)
                  {
                     CheckListItem(iPhysExportPanelHandle, EXPORT_EXPORTDEV, i, 1);
                  }
                  else if (strcmp(ptr->cType, "PHDT") == 0)
                  {
                     CheckListItem(iPhysExportPanelHandle, EXPORT_EXPORTDEV, i, 1);
                  }
                  else if (strcmp(ptr->cType, "PICT") == 0)
                  {
                     CheckListItem(iPhysExportPanelHandle, EXPORT_EXPORTDEV, i, 1);
                  }
                  else if (strcmp(ptr->cType, "PMB") == 0)
                  {
                     CheckListItem(iPhysExportPanelHandle, EXPORT_EXPORTDEV, i, 1);
                     iPMBcheckedOnList = TypeQuantity.PMBquantity; // for function DevListBox
                     iPMBCheckWarning = 0;
                  }
                  else if (strcmp(ptr->cType, "PSAM") == 0)
                  {
                     CheckListItem(iPhysExportPanelHandle, EXPORT_EXPORTDEV, i, 1);
                     iPSAMcheckedOnList = TypeQuantity.PSAMquantity; // for function DevListBox
                     iPSAMCheckWarning = 0;
                  }
                  else if (strcmp(ptr->cType, "PSM1") == 0)
                  {
                     CheckListItem(iPhysExportPanelHandle, EXPORT_EXPORTDEV, i, 1);
                  }
                  else if (strcmp(ptr->cType, "PSM2") == 0)
                  {
                     CheckListItem(iPhysExportPanelHandle, EXPORT_EXPORTDEV, i, 1);
                  }
                  else if (strcmp(ptr->cType, "PSU") == 0)
                  {
                     CheckListItem(iPhysExportPanelHandle, EXPORT_EXPORTDEV, i, 1);
                  }
                  else if (strcmp(ptr->cType, "PSYS1") == 0)
                  {
                     CheckListItem(iPhysExportPanelHandle, EXPORT_EXPORTDEV, i, 1);
                  }
                  else
                  {
                     CheckListItem(iPhysExportPanelHandle, EXPORT_EXPORTDEV, i, 0);
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
      }
      iShouldClose = 0;
      InstallPopup(iPhysExportPanelHandle);
      if (iWantAppIni)
      {
         SetCtrlAttribute(iPhysExportPanelHandle, EXPORT_BENCHNAME, ATTR_DIMMED, 0);
         SetCtrlAttribute(iPhysExportPanelHandle, EXPORT_EXPORTALLCH, ATTR_DIMMED, 0);
      }
      SetActiveCtrl(iPhysExportPanelHandle, EXPORT_EXPORT);
   }
   sprintf(cLastFilePath, "%s", cProjectDir);
}


/* FUNCTION *****************************************************************/
/**
WritePhysicalIni
 *
@brief This function writes all informations into a physical.ini file.
Furthemore it starts a function to add the system channels, if asked for.
\n[code extended by Albert Killer]
 *
@param iAutoCoupling: contains status of Auto-Coupling (not yet used)
 *
@return Error code
 *****************************************************************************/
int WritePhysicalIni(int iAutoCoupling)
{

   int iStatus, iConfirm;
   char cPathName[300];
   char cDrive[10];
   char cPath[300];
   char cName[300];
   char* cGetDate;
   char cPrintDate[15];
   char cPhysicalIniPath[1024];
   char cPhysicalIniFile[1024];
   int i, iIndex, isChecked;
   int iIOChannels, iABUS, iSYSCH, iFileExists, iFileSize;
   char cLabel[128];
   FILE* pFile = NULL;

   iWantPhyIni = 0; // for the export-completed-popup
   if (sDemoMode)
   {
      return 0;
   }


   //Check for valid paths
   sprintf(cPhysicalIniPath, "C:\\Rohde-Schwarz\\GTSL\\Configuration\\");
   sprintf(cPhysicalIniFile, "%sphysical.ini", cPhysicalIniPath);
   iFileExists = FileExists(cPhysicalIniFile, &iFileSize);
   if (!iFileExists)
   {
      sprintf(cPhysicalIniPath, "C:\\Rohde-Schwarz\\GTSL\\Configuration\\");
      sprintf(cPhysicalIniFile, "%sphysical.ini", cPhysicalIniPath);
      iFileExists = FileExists(cPhysicalIniFile, &iFileSize);
   }
   if (!iFileExists)
   {
      sprintf(cPhysicalIniPath, "%s", cLastFilePath);
   }
   if (!pFile)
   {
      /*iStatus = FileSelectPopup (cPhysicalIniPath, "physical.ini", "",
      "Specify path and filename of physical.ini", VAL_SAVE_BUTTON, 0,
      1, 1, 1, cPathName);*/
      iStatus = FileSelectPopupEx(cPhysicalIniPath, "physical.ini", "", "Specify path and filename of physical.ini", VAL_SAVE_BUTTON, 0, 1, cPathName);
      sprintf(cLastFilePath, "%s", cPathName);
      switch (iStatus)
      {
         case 1:
            iStatus = DeleteFile(cPathName);
            break;
         case 2:
            iStatus = 0;
            break;
         default:
            return 0;
      }
      if (iStatus)
      {
         switch (iStatus)
         {
            case  - 6: iConfirm = ConfirmPopup("TG-ITS", "Access denied. Overwrite the file?");
            if (iConfirm)
            {
               iStatus = SetFileAttrs(cPathName, 0, 0, 0, 0);
               if (iStatus)
               {
                  MessagePopup("TG-ITS", "Could not delete file. Please check attributes");
                  return 0;
               }
            }
            break;
            default:
               MessagePopup("TG-ITS", "An unknown error has occured");
               return 0;
         }
      }
      sprintf(cPhysicalIniPath, "%s", cPathName);
      pFile = fopen(cPathName, "w");
   }

   //Format strings for print out
   SplitPath(cPathName, cDrive, cPath, cName);
   cGetDate = DateStr();
   cPrintDate[0] = cGetDate[3];
   cPrintDate[1] = cGetDate[4];
   cPrintDate[2] = '.';
   cPrintDate[3] = cGetDate[0];
   cPrintDate[4] = cGetDate[1];
   cPrintDate[5] = '.';
   cPrintDate[6] = cGetDate[6];
   cPrintDate[7] = cGetDate[7];
   cPrintDate[8] = cGetDate[8];
   cPrintDate[9] = cGetDate[9];
   cPrintDate[10] = '\0';
   sprintf(cPathName, ";\n;   %s created by TG-ITS TemplateGenerator (Version %s) %s %s\n;\n", cName, VERSION, cPrintDate, TimeStr());
   fprintf(pFile, cPathName);
   sprintf(cPathName, "%s\\resources\\template1.txt", cProjectDir);
   pFile = MergeTextFile(pFile, cPathName);
   if (pFile == 0)
   {
      MessagePopup("TG-ITS", "Could not open %s\nCheck resource folder!");
      return 0;
   }
   GetNumListItems(iPhysExportPanelHandle, EXPORT_EXPORTDEV, &iIndex);
   if (iIndex)
   {
      for (i = 0; i < iIndex; i++)
      {
         IsListItemChecked(iPhysExportPanelHandle, EXPORT_EXPORTDEV, i, &isChecked);
         if (isChecked)
         {
            GetLabelFromIndex(iPhysExportPanelHandle, EXPORT_EXPORTDEV, i, cLabel);
            pFile = WriteBench(pFile, cLabel, iAutoCoupling);
            WriteSystemChannels(cLabel, i); // writes the sys-channel infos of the checked devices into "templateSYSCH.txt"
            if (!pFile)
            {
               return  - 1;
            }
         }
      }

      GetCtrlVal(iPhysExportPanelHandle, EXPORT_EXPORTSYSCH, &iSYSCH);
      if (iSYSCH)
      {
         sprintf(cPathName, "%s\\resources\\templateSYSCH.txt", cProjectDir);
         pFile = MergeTextFile(pFile, cPathName); //  appends content of temporary file to physical.ini
         if (pFile == 0)
         {
            MessagePopup("TG-ITS", "Could not open %s\nCheck resource folder!");
            return 0;
         }
      }

      sprintf(cPathName, "%s\\resources\\templateSYSCH.txt", cProjectDir);
      DeleteFile(cPathName);

      GetCtrlVal(iPhysExportPanelHandle, EXPORT_EXPORTABUS, &iABUS);

      if (iABUS && !iSYSCH)
      // header for ABUS, if there are no system-channels requested
      {
         fprintf(pFile, "; System I/O Channels\n[io_channel->system]\n\n");
      }

      if (iABUS)
      {
         sprintf(cPathName, "%s\\resources\\template2.txt", cProjectDir);
         pFile = MergeTextFile(pFile, cPathName); // appends ABUS infos to physical.ini
         if (pFile == 0)
         {
            MessagePopup("TG-ITS", "Could not open %s\nCheck resource folder!");
            return 0;
         }
      }

      fprintf(pFile, ";");
      iWantPhyIni = 1; // for the export-completed-popup
      fclose(pFile);
   }
   return 0;
}

/* FUNCTION *****************************************************************/
/**
WriteBench
 *
@brief This function write a bench into a physcial.ini file
 *
@param pFile: File pointer to a physical.ini file
@param cLabel: Label of device which is to export
@param iAutoCoupling: contains status of Auto-Coupling (not yet used)
 *
@return File pointer to a physical.ini file
 *****************************************************************************/
FILE* WriteBench(FILE* pFile, char* cLabel, int iAutoCoupling)
{
   int PSAMSelfTest = FALSE;
   ressource* ptr;

   ptr = pFirstRessource;
   while (ptr)
   {
      if (strcmp(ptr->cBenchName, cLabel) == 0)
      {
         fprintf(pFile, "[Device->%s]\n", ptr->cBenchName);
         if (strlen(ptr->cDescription))
         {
            if (ptr->iSlot > 0)
            {
               fprintf(pFile, "Description\t\t= \"%s, Slot number %d\"\n", ptr->cDescription, ptr->iSlot);
            }
            else
            {
               fprintf(pFile, "Description\t\t= \"%s\"\n", ptr->cDescription);
            }

         }
         if (strlen(ptr->cType))
         {
            fprintf(pFile, "Type\t\t\t= %s\n", ptr->cType);
         }
         if (strlen(ptr->cRessourceDesc))
         {
            fprintf(pFile, "ResourceDesc\t\t= %s\n", ptr->cRessourceDesc);
         }
         if (ptr->iSlot >= 0)
         {
            fprintf(pFile, "Slot\t\t\t= %i\n", ptr->iSlot);
         }
         if (ptr->iFrame >= 0)
         {
            fprintf(pFile, "Frame\t\t\t= %i\n", ptr->iFrame);
         }
         if (strlen(ptr->cDriverDLL))
         {
            fprintf(pFile, "DriverDLL\t\t= %s\n", ptr->cDriverDLL);
            if (!strcmp(ptr->cDriverDLL, "rspsam.dll"))
            {
               PSAMSelfTest = TRUE;
            }
         }
         if (strlen(ptr->cDriverPrefix))
         {
            fprintf(pFile, "DriverPrefix\t\t= %s\n", ptr->cDriverPrefix);
         }
         if (strlen(ptr->cDriverOption))
         {
            if (!strcmp(ptr->cDriverDLL, "rspmb.dll") && iAutoCoupling)
            {
               fprintf(pFile, "DriverOption\t\t= \"%s,DriverSetup=crAuto:1\"\n", ptr->cDriverOption);
            }
            else
            {
               fprintf(pFile, "DriverOption\t\t= \"%s\"\n", ptr->cDriverOption);
            }
         }
         if (PSAMSelfTest && ((strlen(ptr->cSFTDll) || strlen(ptr->cSFTPrefix))))
         {
            fprintf(pFile, "; Note: The self test DLL and prefix keywords must be removed for the\n");
            fprintf(pFile, ";       first TS-PSAM module, because it is already tested in the\n");
            fprintf(pFile, ";       basic self test.\n");
         }
         if (strlen(ptr->cSFTDll))
         {
            if (PSAMSelfTest)
            {
               fprintf(pFile, ";");
            }
            fprintf(pFile, "SFTDll\t\t\t= %s\n", ptr->cSFTDll);
         }
         if (strlen(ptr->cSFTPrefix))
         {
            if (PSAMSelfTest)
            {
               fprintf(pFile, ";");
            }
            fprintf(pFile, "SFTPrefix\t\t= \"%s\"\n", ptr->cSFTPrefix);
         }
         if (ptr->iInternalType == ASRL)
         {
            fprintf(pFile, "Baudrate\t\t= %i\n", ptr->iBaudrate);
         }
         if (ptr->iInternalType == ASRL)
         {
            fprintf(pFile, "Parity\t\t\t= %s\n", ptr->cParity);
         }
         if (ptr->iInternalType == ASRL)
         {
            fprintf(pFile, "Handshake\t\t= %s\n", ptr->cHandshake);
         }
         if (ptr->iInternalType == ASRL)
         {
            fprintf(pFile, "Databits\t\t= %i\n", ptr->iDataBits);
         }
         if (ptr->iInternalType == ASRL)
         {
            fprintf(pFile, "Stopbits\t\t= %i\n", ptr->iStopBits);
         }
         fprintf(pFile, "\n");
         ptr->iMarkedForExport = 1;
         break;
      }
      else
      {
         ptr = ptr->next;
      }
   }
   return pFile;
}


/* FUNCTION *****************************************************************/
/**
WriteSystemChannels
 *
@brief This function writes infos about the system-I/O-channels to a temporary
text file, which is appended to the physical.ini file, if asked for.
\n[code by Albert Killer]
 *
@param cLabel: Label of device, from which the system channels have to
be exported
@param i: checks if the function runs for the first time, to write a header
 *
@return void
 *****************************************************************************/
void WriteSystemChannels(char cLabel[], int i)
{
   char cDeviceType[150]; // Array for label without slot
   char cPathName[300];
   FILE* pTempFile = NULL;

   ressource* ptr;

   sprintf(cPathName, "%s\\resources\\templateSYSCH.txt", cProjectDir); // path of temporary file
   pTempFile = fopen(cPathName, "a+"); // creates temporary file
   if (pTempFile == NULL)
   {
      MessagePopup("TG-ITS", "Could not write system channels,\nbecause wasn't able to create temporary file.");
      MessagePopup("TG-ITS", "Could not create physical layer.");
   }

   SetFileAttrs(cPathName,  - 1,  - 1, 1,  - 1); // hides temporary file

   if (!i)
   // checks if the function runs for the first time, to write a header										
   {
      fprintf(pTempFile, "; System I/O Channels\n[io_channel->system]\n\n");
   }



   ptr = pFirstRessource;
   while (ptr)
   {
      if (strcmp(ptr->cBenchName, cLabel) == 0)
      {
         sprintf(cDeviceType, ptr->cType);
      }
      ptr = ptr->next;
   }

   if (strcmp(cDeviceType, "PAM") == 0)
   // starts to compare actual device with possible devices
   {
      // to write the respective system-channels into "templateSYSCH.txt"
      fprintf(pTempFile, "; Device->%s\n", cLabel);

      fprintf(pTempFile, "%s_CHA1_HI = %s!CHA1_HI\n", cLabel, cLabel);
      fprintf(pTempFile, "%s_CHA1_HI1 = %s!CHA1_HI1\n", cLabel, cLabel);
      fprintf(pTempFile, "%s_CHA1_HI2 = %s!CHA1_HI2\n", cLabel, cLabel);
      fprintf(pTempFile, "%s_CHA1_HI3 = %s!CHA1_HI3\n", cLabel, cLabel);
      fprintf(pTempFile, "%s_UREFA1 = %s!UREFA1\n", cLabel, cLabel);

      fprintf(pTempFile, "%s_CHA2_HI = %s!CHA2_HI\n", cLabel, cLabel);
      fprintf(pTempFile, "%s_CHA2_HI1 = %s!CHA2_HI1\n", cLabel, cLabel);
      fprintf(pTempFile, "%s_CHA2_HI2 = %s!CHA2_HI2\n", cLabel, cLabel);
      fprintf(pTempFile, "%s_CHA2_HI3 = %s!CHA2_HI3\n", cLabel, cLabel);
      fprintf(pTempFile, "%s_UREFA2 = %s!UREFA2\n", cLabel, cLabel);

      fprintf(pTempFile, "%s_CHA3_HI = %s!CHA3_HI\n", cLabel, cLabel);
      fprintf(pTempFile, "%s_CHA3_HI1 = %s!CHA3_HI1\n", cLabel, cLabel);
      fprintf(pTempFile, "%s_CHA3_HI2 = %s!CHA3_HI2\n", cLabel, cLabel);
      fprintf(pTempFile, "%s_CHA3_HI3 = %s!CHA3_HI3\n", cLabel, cLabel);
      fprintf(pTempFile, "%s_UREFA3 = %s!UREFA3\n", cLabel, cLabel);

      fprintf(pTempFile, "%s_CHA4_HI = %s!CHA4_HI\n", cLabel, cLabel);
      fprintf(pTempFile, "%s_CHA4_HI1 = %s!CHA4_HI1\n", cLabel, cLabel);
      fprintf(pTempFile, "%s_CHA4_HI2 = %s!CHA4_HI2\n", cLabel, cLabel);
      fprintf(pTempFile, "%s_CHA4_HI3 = %s!CHA4_HI3\n", cLabel, cLabel);
      fprintf(pTempFile, "%s_UREFA4 = %s!UREFA4\n", cLabel, cLabel);

      fprintf(pTempFile, "%s_CHA_LO = %s!CHA_LO\n", cLabel, cLabel);
      fprintf(pTempFile, "%s_CHA_LO1 = %s!CHA_LO1\n", cLabel, cLabel);

      fprintf(pTempFile, "%s_CHB1_HI = %s!CHB1_HI\n", cLabel, cLabel);
      fprintf(pTempFile, "%s_CHB1_HI1 = %s!CHB1_HI1\n", cLabel, cLabel);
      fprintf(pTempFile, "%s_CHB1_HI2 = %s!CHB1_HI2\n", cLabel, cLabel);
      fprintf(pTempFile, "%s_CHB1_HI3 = %s!CHB1_HI3\n", cLabel, cLabel);
      fprintf(pTempFile, "%s_UREFB1 = %s!UREFB1\n", cLabel, cLabel);

      fprintf(pTempFile, "%s_CHB2_HI = %s!CHB2_HI\n", cLabel, cLabel);
      fprintf(pTempFile, "%s_CHB2_HI1 = %s!CHB2_HI1\n", cLabel, cLabel);
      fprintf(pTempFile, "%s_CHB2_HI2 = %s!CHB2_HI2\n", cLabel, cLabel);
      fprintf(pTempFile, "%s_CHB2_HI3 = %s!CHB2_HI3\n", cLabel, cLabel);
      fprintf(pTempFile, "%s_UREFB2 = %s!UREFB2\n", cLabel, cLabel);

      fprintf(pTempFile, "%s_CHB3_HI = %s!CHB3_HI\n", cLabel, cLabel);
      fprintf(pTempFile, "%s_CHB3_HI1 = %s!CHB3_HI1\n", cLabel, cLabel);
      fprintf(pTempFile, "%s_CHB3_HI2 = %s!CHB3_HI2\n", cLabel, cLabel);
      fprintf(pTempFile, "%s_CHB3_HI3 = %s!CHB3_HI3\n", cLabel, cLabel);
      fprintf(pTempFile, "%s_UREFB3 = %s!UREFB3\n", cLabel, cLabel);

      fprintf(pTempFile, "%s_CHB4_HI = %s!CHB4_HI\n", cLabel, cLabel);
      fprintf(pTempFile, "%s_CHB4_HI1 = %s!CHB4_HI1\n", cLabel, cLabel);
      fprintf(pTempFile, "%s_CHB4_HI2 = %s!CHB4_HI2\n", cLabel, cLabel);
      fprintf(pTempFile, "%s_CHB4_HI3 = %s!CHB4_HI3\n", cLabel, cLabel);
      fprintf(pTempFile, "%s_UREFB4 = %s!UREFB4\n", cLabel, cLabel);

      fprintf(pTempFile, "%s_CHB_LO = %s!CHB_LO\n", cLabel, cLabel);
      fprintf(pTempFile, "%s_CHB_LO1 = %s!CHB_LO1\n", cLabel, cLabel);

      fprintf(pTempFile, "\n");
   }


   if (strcmp(cDeviceType, "PDFT") == 0)
   {
      fprintf(pTempFile, "; Device->%s\n", cLabel);

      fprintf(pTempFile, "%s_AUX1com = %s!AUX1com\n", cLabel, cLabel);
      fprintf(pTempFile, "%s_AUX2com = %s!AUX2com\n", cLabel, cLabel);
      fprintf(pTempFile, "%s_AUX3com = %s!AUX3com\n", cLabel, cLabel);
      fprintf(pTempFile, "%s_AUX4com = %s!AUX4com\n", cLabel, cLabel);

      fprintf(pTempFile, "%s_AUX1no = %s!AUX1no\n", cLabel, cLabel);
      fprintf(pTempFile, "%s_AUX2no = %s!AUX2no\n", cLabel, cLabel);
      fprintf(pTempFile, "%s_AUX3no = %s!AUX3no\n", cLabel, cLabel);
      fprintf(pTempFile, "%s_AUX4no = %s!AUX4no\n", cLabel, cLabel);

      fprintf(pTempFile, "%s_GND = %s!GND\n", cLabel, cLabel);
      fprintf(pTempFile, "%s_GNDno = %s!GNDno\n", cLabel, cLabel);

      fprintf(pTempFile, "\n");
   }


   if (strcmp(cDeviceType, "PFG") == 0)
   {
      fprintf(pTempFile, "; Device->%s\n", cLabel);

      fprintf(pTempFile, "%s_CH1_Hi = %s!CH1_Hi\n", cLabel, cLabel);
      fprintf(pTempFile, "%s_CH1_Lo = %s!CH1_Lo\n", cLabel, cLabel);

      fprintf(pTempFile, "%s_CH2_Hi = %s!CH2_Hi\n", cLabel, cLabel);
      fprintf(pTempFile, "%s_CH2_Lo = %s!CH2_Lo\n", cLabel, cLabel);

      fprintf(pTempFile, "\n");
   }


   if (strcmp(cDeviceType, "PIO2") == 0)
   {
      fprintf(pTempFile, "; Device->%s\n", cLabel);

      fprintf(pTempFile, "%s_CH1_IN = %s!CH1_IN\n", cLabel, cLabel);
      fprintf(pTempFile, "%s_CH1_1 = %s!CH1_1\n", cLabel, cLabel);
      fprintf(pTempFile, "%s_CH1_2 = %s!CH1_2\n", cLabel, cLabel);

      fprintf(pTempFile, "%s_CH2_IN = %s!CH2_IN\n", cLabel, cLabel);
      fprintf(pTempFile, "%s_CH2_1 = %s!CH2_1\n", cLabel, cLabel);
      fprintf(pTempFile, "%s_CH2_2 = %s!CH2_2\n", cLabel, cLabel);

      fprintf(pTempFile, "%s_CH3_IN = %s!CH3_IN\n", cLabel, cLabel);
      fprintf(pTempFile, "%s_CH3_1 = %s!CH3_1\n", cLabel, cLabel);
      fprintf(pTempFile, "%s_CH3_2 = %s!CH3_2\n", cLabel, cLabel);

      fprintf(pTempFile, "%s_CH4_IN = %s!CH4_IN\n", cLabel, cLabel);
      fprintf(pTempFile, "%s_CH4_1 = %s!CH4_1\n", cLabel, cLabel);
      fprintf(pTempFile, "%s_CH4_2 = %s!CH4_2\n", cLabel, cLabel);

      fprintf(pTempFile, "%s_CH5_IN = %s!CH5_IN\n", cLabel, cLabel);
      fprintf(pTempFile, "%s_CH5_1 = %s!CH5_1\n", cLabel, cLabel);
      fprintf(pTempFile, "%s_CH5_2 = %s!CH5_2\n", cLabel, cLabel);

      fprintf(pTempFile, "%s_CH6_IN = %s!CH6_IN\n", cLabel, cLabel);
      fprintf(pTempFile, "%s_CH6_1 = %s!CH6_1\n", cLabel, cLabel);
      fprintf(pTempFile, "%s_CH6_2 = %s!CH6_2\n", cLabel, cLabel);

      fprintf(pTempFile, "%s_CH7_IN = %s!CH7_IN\n", cLabel, cLabel);
      fprintf(pTempFile, "%s_CH7_1 = %s!CH7_1\n", cLabel, cLabel);
      fprintf(pTempFile, "%s_CH7_2 = %s!CH7_2\n", cLabel, cLabel);

      fprintf(pTempFile, "%s_CH8_IN = %s!CH8_IN\n", cLabel, cLabel);
      fprintf(pTempFile, "%s_CH8_1 = %s!CH8_1\n", cLabel, cLabel);
      fprintf(pTempFile, "%s_CH8_2 = %s!CH8_2\n", cLabel, cLabel);

      fprintf(pTempFile, "%s_CH9_IN = %s!CH9_IN\n", cLabel, cLabel);
      fprintf(pTempFile, "%s_CH9_1 = %s!CH9_1\n", cLabel, cLabel);
      fprintf(pTempFile, "%s_CH9_2 = %s!CH9_2\n", cLabel, cLabel);

      fprintf(pTempFile, "%s_CH10_IN = %s!CH10_IN\n", cLabel, cLabel);
      fprintf(pTempFile, "%s_CH10_1 = %s!CH10_1\n", cLabel, cLabel);
      fprintf(pTempFile, "%s_CH10_2 = %s!CH10_2\n", cLabel, cLabel);

      fprintf(pTempFile, "%s_CH11_IN = %s!CH11_IN\n", cLabel, cLabel);
      fprintf(pTempFile, "%s_CH11_1 = %s!CH11_1\n", cLabel, cLabel);
      fprintf(pTempFile, "%s_CH11_2 = %s!CH11_2\n", cLabel, cLabel);

      fprintf(pTempFile, "%s_CH12_IN = %s!CH12_IN\n", cLabel, cLabel);
      fprintf(pTempFile, "%s_CH12_1 = %s!CH12_1\n", cLabel, cLabel);
      fprintf(pTempFile, "%s_CH12_2 = %s!CH12_2\n", cLabel, cLabel);

      fprintf(pTempFile, "%s_CH13_IN = %s!CH13_IN\n", cLabel, cLabel);
      fprintf(pTempFile, "%s_CH13_1 = %s!CH13_1\n", cLabel, cLabel);
      fprintf(pTempFile, "%s_CH13_2 = %s!CH13_2\n", cLabel, cLabel);

      fprintf(pTempFile, "%s_CH14_IN = %s!CH14_IN\n", cLabel, cLabel);
      fprintf(pTempFile, "%s_CH14_1 = %s!CH14_1\n", cLabel, cLabel);
      fprintf(pTempFile, "%s_CH14_2 = %s!CH14_2\n", cLabel, cLabel);

      fprintf(pTempFile, "%s_CH15_IN = %s!CH15_IN\n", cLabel, cLabel);
      fprintf(pTempFile, "%s_CH15_1 = %s!CH15_1\n", cLabel, cLabel);
      fprintf(pTempFile, "%s_CH15_2 = %s!CH15_2\n", cLabel, cLabel);

      fprintf(pTempFile, "%s_CH16_IN = %s!CH16_IN\n", cLabel, cLabel);
      fprintf(pTempFile, "%s_CH16_1 = %s!CH16_1\n", cLabel, cLabel);
      fprintf(pTempFile, "%s_CH16_2 = %s!CH16_2\n", cLabel, cLabel);

      fprintf(pTempFile, "%s_LO = %s!LO\n", cLabel, cLabel);
      fprintf(pTempFile, "%s_AGND = %s!AGND\n", cLabel, cLabel);

      fprintf(pTempFile, "\n");
   }


   if (strcmp(cDeviceType, "PSAM") == 0)
   {
      fprintf(pTempFile, "; Device->%s\n", cLabel);

      fprintf(pTempFile, "%s_DMM_HI = %s!DMM_HI\n", cLabel, cLabel);
      fprintf(pTempFile, "%s_DMM_LO = %s!DMM_LO\n", cLabel, cLabel);

      fprintf(pTempFile, "%s_DMM_SHI = %s!DMM_SHI\n", cLabel, cLabel);
      fprintf(pTempFile, "%s_DMM_SLO = %s!DMM_SLO\n", cLabel, cLabel);

      fprintf(pTempFile, "%s_DCH_HI = %s!DCH_HI\n", cLabel, cLabel);

      fprintf(pTempFile, "%s_RACOM = %s!RACOM\n", cLabel, cLabel);
      fprintf(pTempFile, "%s_RACH1 = %s!RACH1\n", cLabel, cLabel);
      fprintf(pTempFile, "%s_RACH2 = %s!RACH2\n", cLabel, cLabel);
      fprintf(pTempFile, "%s_RACH3 = %s!RACH3\n", cLabel, cLabel);
      fprintf(pTempFile, "%s_RACH4 = %s!RACH4\n", cLabel, cLabel);

      fprintf(pTempFile, "%s_RBCOM = %s!RBCOM\n", cLabel, cLabel);
      fprintf(pTempFile, "%s_RBCH1 = %s!RBCH1\n", cLabel, cLabel);
      fprintf(pTempFile, "%s_RBCH2 = %s!RBCH2\n", cLabel, cLabel);
      fprintf(pTempFile, "%s_RBCH3 = %s!RBCH3\n", cLabel, cLabel);
      fprintf(pTempFile, "%s_RBCH4 = %s!RBCH4\n", cLabel, cLabel);

      fprintf(pTempFile, "\n");
   }


   if (strcmp(cDeviceType, "PSU") == 0)
   {
      fprintf(pTempFile, "; Device->%s\n", cLabel);

      fprintf(pTempFile, "%s_CH1 = %s!CH1\n", cLabel, cLabel);
      fprintf(pTempFile, "%s_CH2 = %s!CH2\n", cLabel, cLabel);

      fprintf(pTempFile, "%s_CH1_HI = %s!CH1_HI\n", cLabel, cLabel);
      fprintf(pTempFile, "%s_CH1_LO = %s!CH1_LO\n", cLabel, cLabel);
      fprintf(pTempFile, "%s_CH1_SHI = %s!CH1_SHI\n", cLabel, cLabel);
      fprintf(pTempFile, "%s_CH1_SLO = %s!CH1_SLO\n", cLabel, cLabel);

      fprintf(pTempFile, "%s_CH2_HI = %s!CH2_HI\n", cLabel, cLabel);
      fprintf(pTempFile, "%s_CH2_LO = %s!CH2_LO\n", cLabel, cLabel);
      fprintf(pTempFile, "%s_CH2_SHI = %s!CH2_SHI\n", cLabel, cLabel);
      fprintf(pTempFile, "%s_CH2_SLO = %s!CH2_SLO\n", cLabel, cLabel);

      fprintf(pTempFile, "%s_CH1_S = %s!CH1_S\n", cLabel, cLabel);
      fprintf(pTempFile, "%s_CH2_S = %s!CH2_S\n", cLabel, cLabel);

      fprintf(pTempFile, "%s_CH1_1 = %s!CH1_1\n", cLabel, cLabel);
      fprintf(pTempFile, "%s_CH1_2 = %s!CH1_2\n", cLabel, cLabel);
      fprintf(pTempFile, "%s_CH1_3 = %s!CH1_3\n", cLabel, cLabel);
      fprintf(pTempFile, "%s_CH1_4 = %s!CH1_4\n", cLabel, cLabel);

      fprintf(pTempFile, "%s_CH1_S1 = %s!CH1_S1\n", cLabel, cLabel);
      fprintf(pTempFile, "%s_CH1_S2 = %s!CH1_S2\n", cLabel, cLabel);
      fprintf(pTempFile, "%s_CH1_S3 = %s!CH1_S3\n", cLabel, cLabel);
      fprintf(pTempFile, "%s_CH1_S4 = %s!CH1_S4\n", cLabel, cLabel);

      fprintf(pTempFile, "%s_CH2_1 = %s!CH2_1\n", cLabel, cLabel);
      fprintf(pTempFile, "%s_CH2_2 = %s!CH2_2\n", cLabel, cLabel);
      fprintf(pTempFile, "%s_CH2_3 = %s!CH2_3\n", cLabel, cLabel);
      fprintf(pTempFile, "%s_CH2_4 = %s!CH2_4\n", cLabel, cLabel);

      fprintf(pTempFile, "%s_CH2_S1 = %s!CH2_S1\n", cLabel, cLabel);
      fprintf(pTempFile, "%s_CH2_S2 = %s!CH2_S2\n", cLabel, cLabel);
      fprintf(pTempFile, "%s_CH2_S3 = %s!CH2_S3\n", cLabel, cLabel);
      fprintf(pTempFile, "%s_CH2_S4 = %s!CH2_S4\n", cLabel, cLabel);

      fprintf(pTempFile, "\n");
   }


   if (strcmp(cDeviceType, "PSYS1") == 0)
   {
      fprintf(pTempFile, "; Device->%s\n", cLabel);

      fprintf(pTempFile, "%s_Trig0No = %s!Trig0No\n", cLabel, cLabel);
      fprintf(pTempFile, "%s_Trig0Com = %s!Trig0Com\n", cLabel, cLabel);
      fprintf(pTempFile, "%s_Trig1No = %s!Trig1No\n", cLabel, cLabel);
      fprintf(pTempFile, "%s_Trig1Com = %s!Trig1Com\n", cLabel, cLabel);
      fprintf(pTempFile, "%s_Trig2No = %s!Trig2No\n", cLabel, cLabel);
      fprintf(pTempFile, "%s_Trig2Com = %s!Trig2Com\n", cLabel, cLabel);
      fprintf(pTempFile, "%s_Trig3No = %s!Trig3No\n", cLabel, cLabel);
      fprintf(pTempFile, "%s_Trig3Com = %s!Trig3Com\n", cLabel, cLabel);
      fprintf(pTempFile, "%s_Trig4No = %s!Trig4No\n", cLabel, cLabel);
      fprintf(pTempFile, "%s_Trig4Com = %s!Trig4Com\n", cLabel, cLabel);
      fprintf(pTempFile, "%s_Trig5No = %s!Trig5No\n", cLabel, cLabel);
      fprintf(pTempFile, "%s_Trig5Com = %s!Trig5Com\n", cLabel, cLabel);
      fprintf(pTempFile, "%s_Trig6No = %s!Trig6No\n", cLabel, cLabel);
      fprintf(pTempFile, "%s_Trig6Com = %s!Trig6Com\n", cLabel, cLabel);
      fprintf(pTempFile, "%s_Trig7No = %s!Trig7No\n", cLabel, cLabel);
      fprintf(pTempFile, "%s_Trig7Com = %s!Trig7Com\n", cLabel, cLabel);

      fprintf(pTempFile, "%s_Out0No = %s!Out0No\n", cLabel, cLabel);
      fprintf(pTempFile, "%s_Out0Com = %s!Out0Com\n", cLabel, cLabel);
      fprintf(pTempFile, "%s_Out1No = %s!Out1No\n", cLabel, cLabel);
      fprintf(pTempFile, "%s_Out1Com = %s!Out1Com\n", cLabel, cLabel);

      fprintf(pTempFile, "%s_4_5VNo = %s!11_5VNo\n", cLabel, cLabel);
      fprintf(pTempFile, "%s_4_5VCom = %s!11_5VCom\n", cLabel, cLabel);
      fprintf(pTempFile, "%s_11_5VNo = %s!11_5VNo\n", cLabel, cLabel);
      fprintf(pTempFile, "%s_11_5VCom = %s!11_5VCom\n", cLabel, cLabel);

      fprintf(pTempFile, "\n");
   }
   fclose(pTempFile);
}


/* FUNCTION *****************************************************************/
/**
WriteApplicationIni
 *
@brief This function writes a sample application.ini file
\n[code by Albert Killer]
 *
@param void
 *
@return Error code
 *****************************************************************************/
int WriteApplicationIni(void)
{

   int iStatus, iConfirm;
   char cPathName[300];
   char cDrive[10];
   char cPath[300];
   char cName[300];
   char* cGetDate;
   char cPrintDate[15];
   int i, k, m, n, ipfg, ipam, ipsam, p1, p2, p3, t1, t2, t3, iIndex, isChecked, CHsampleNeeded, CHdcsupplieNeeded, CHdioNeeded, ICTavailable; // counters with several tasks
   int iIOChannels, iABUS, iSYSCH;
   char cLabel[128];
   char cBenchName[1024];
   FILE* pFile = NULL;
   ressource* ptr;
   int iExportAllChannels;

   iWantAppIni = 0; // for the export-completed-popup
   GetCtrlVal(iPhysExportPanelHandle, EXPORT_EXPORTALLCH, &iExportAllChannels); // check if all channels shall be exported or only some samples
   GetCtrlVal(iPhysExportPanelHandle, EXPORT_BENCHNAME, cBenchName);
   if (!strlen(cBenchName))
   {
      sprintf(cBenchName, "SampleBench");
   }
   if (sDemoMode)
   {
      return 0;
   }


   if (!pFile)
   {
      iStatus = FileSelectPopup(cProjectDir, "application.ini", "", "Specify path and file name of application.ini", VAL_SAVE_BUTTON, 0, 1, 1, 1, cPathName);
      sprintf(cLastFilePath, "%s", cPathName);
      switch (iStatus)
      {
         case 1:
            iStatus = DeleteFile(cPathName);
            break;
         case 2:
            iStatus = 0;
            break;
         default:
            return 0;
      }
      if (iStatus)
      {
         switch (iStatus)
         {
            case  - 6: iConfirm = ConfirmPopup("TG-ITS", "Access denied. Overwrite the file?");
            if (iConfirm)
            {
               iStatus = SetFileAttrs(cPathName, 0, 0, 0, 0);
               if (iStatus)
               {
                  MessagePopup("TG-ITS", "Could not delete file. Please check attributes");
                  return 0;
               }
            }
            break;
            default:
               MessagePopup("TG-ITS", "An unknown error has occured");
               return 0;
         }
      }
      sprintf(cApplicationIniPath, "%s", cPathName);
      pFile = fopen(cPathName, "w");
   }

   //Format strings for print out
   SplitPath(cPathName, cDrive, cPath, cName);
   cGetDate = DateStr();
   cPrintDate[0] = cGetDate[3];
   cPrintDate[1] = cGetDate[4];
   cPrintDate[2] = '.';
   cPrintDate[3] = cGetDate[0];
   cPrintDate[4] = cGetDate[1];
   cPrintDate[5] = '.';
   cPrintDate[6] = cGetDate[6];
   cPrintDate[7] = cGetDate[7];
   cPrintDate[8] = cGetDate[8];
   cPrintDate[9] = cGetDate[9];
   cPrintDate[10] = '\0';
   sprintf(cPathName, ";\n;   %s created by TG-ITS TemplateGenerator (Version %s) %s %s\n;\n", cName, VERSION, cPrintDate, TimeStr());
   fprintf(pFile, cPathName);
   fprintf(pFile, ";----------------------------------------------------------------------------------\n");
   /* sprintf(cPathName, "%s\\resources\\???.txt", cProjectDir);		// maybe description temp??
   / pFile = MergeTextFile(pFile, cPathName);   // better use encoded template!
   if (pFile == 0)
   {
   MessagePopup("CreateApplicationLayer",
   "Could not open %s\nCheck resource folder!");
   return 0;
   }
    */

   // ressource manager
   fprintf(pFile, "\n[ResourceManager]\n");
   fprintf(pFile, "; general trace settings (normally off)\n");
   fprintf(pFile, "Trace = 0\n");
   fprintf(pFile, "TraceFile = C:\\Trace.log\n");
   fprintf(pFile, "TraceToScreen = 0\n");
   fprintf(pFile, "TraceTimeStamp = 1\n");
   fprintf(pFile, "TraceThreadID = 0\n");

   // logical names
   fprintf(pFile, "\n[LogicalNames]\n");
   fprintf(pFile, "%s = bench->%s\n", cBenchName, cBenchName);

   if ((TypeQuantity.PAMquantity > 1) || (TypeQuantity.PSAMquantity > 1) || (TypeQuantity.PFGquantity > 1))
   // checking for multiple pam, psam or pfg
   {
      if (TypeQuantity.PSAMquantity >= TypeQuantity.PAMquantity)
      // detecting the biggest value
      {
         if (TypeQuantity.PSAMquantity >= TypeQuantity.PFGquantity)
         {
            n = TypeQuantity.PSAMquantity;
         }
         else
         {
            n = TypeQuantity.PFGquantity;
         }
      }
      else
      {
         if (TypeQuantity.PAMquantity >= TypeQuantity.PFGquantity)
         {
            n = TypeQuantity.PAMquantity;
         }
         else
         {
            n = TypeQuantity.PFGquantity;
         }
      }
      for (i = 2; i <= n; i++)
      {
         fprintf(pFile, "%s%i = bench->%s%i\n", cBenchName, i, cBenchName, i);
      }
   }


   // bench sample
   fprintf(pFile, "\n[bench->%s]\n", cBenchName);
   fprintf(pFile, "Description = \"Type here description\"\n");
   fprintf(pFile, "Simulation = 0\n");
   fprintf(pFile, "Trace	= 0\n");
   fprintf(pFile, "ChannelTableCaseSensitive = 0\n");

   // UIR settings
   fprintf(pFile, "\n; CP-ITS settings\n");
   fprintf(pFile, "TitlebarText = Type here company name.\n");
   fprintf(pFile, "ProductName = type here product name.\n");
   fprintf(pFile, "PanelType = SINGLE\n");
   fprintf(pFile, "DebugPanelPosition = TOPLEFT\n");
   fprintf(pFile, "SerialIsMandatory = 1\n");

   // bench sample / defined devices
   fprintf(pFile, "\n; Defined devices\n");

   GetNumListItems(iPhysExportPanelHandle, EXPORT_EXPORTDEV, &iIndex);

   if (!iIndex)
   // in case of no device being marked
   {
      fprintf(pFile, "; no device was marked during export");
      fclose(pFile);
      return 0;
   }

   // bench sample / defined devices / special
   k = 1;
   n = 1;
   ipsam = 0;
   ipam = 0;
   ipfg = 0;
   ICTavailable = 0;
   for (i = 0; i < iIndex; i++)
   {
      IsListItemChecked(iPhysExportPanelHandle, EXPORT_EXPORTDEV, i, &isChecked);
      if (isChecked)
      {
         GetLabelFromIndex(iPhysExportPanelHandle, EXPORT_EXPORTDEV, i, cLabel);
         ptr = pFirstRessource;
         while (ptr)
         {
            if (strcmp(ptr->cBenchName, cLabel) == 0)
            {
               if (strcmp(ptr->cType, "PSAM") == 0)
               {
                  if (ipsam == 0)
                  {
                     fprintf(pFile, "Digitalmultimeter = device->%s\n", ptr->cBenchName);
                  }
                  ipsam++;
               }
               if (strcmp(ptr->cType, "PAM") == 0)
               {
                  if (ipam == 0)
                  {
                     fprintf(pFile, "SignalAnalyzer = device->%s\n", ptr->cBenchName);
                  }
                  ipam++;
               }
               if (strcmp(ptr->cType, "PFG") == 0)
               {
                  if (ipfg == 0)
                  {
                     fprintf(pFile, "FunctionGenerator = device->%s\n", ptr->cBenchName);
                  }
                  ipfg++;
               }
               if (strcmp(ptr->cType, "PSU") == 0)
               {
                  fprintf(pFile, "DCPwrSupply%i = device->%s\n", k, ptr->cBenchName);
                  k++;
               }
               if (strcmp(ptr->cType, "PDFT") == 0)
               {
                  fprintf(pFile, "DIODevice%i = device->%s\n", n, ptr->cBenchName);
                  n++;
               }
               if (strcmp(ptr->cType, "PICT") == 0)
               {
                  ICTavailable = 1; // used to check if PICT is available for ICTdevice1 and 2
               }
               ptr->iMarkedForExport = 1;
               break;
            }
            else
            {
               ptr = ptr->next;
            }
         }
         if (!pFile)
         {
            return  - 1;
         }
      }
   }

   // bench sample / defined devices / ICT-devices
   for (i = 0; i < iIndex; i++)
   {
      IsListItemChecked(iPhysExportPanelHandle, EXPORT_EXPORTDEV, i, &isChecked);
      if (isChecked)
      {
         GetLabelFromIndex(iPhysExportPanelHandle, EXPORT_EXPORTDEV, i, cLabel);
         ptr = pFirstRessource;
         while (ptr)
         {
            if (strcmp(ptr->cBenchName, cLabel) == 0)
            {
               if (strcmp(ptr->cType, "PICT") == 0)
               {
                  fprintf(pFile, "ICTDevice2 = device->%s\n", ptr->cBenchName);
               }
               if ((strcmp(ptr->cType, "PSAM") == 0) && (ICTavailable))
               {
                  fprintf(pFile, "ICTDevice1 = device->%s\n", ptr->cBenchName);
               }
               if ((strcmp(ptr->cType, "PSU") == 0) && (ICTavailable))
               {
                  fprintf(pFile, "ICTDevice3 = device->%s\n", ptr->cBenchName);
               }
               ptr->iMarkedForExport = 1;
               break;
            }
            else
            {
               ptr = ptr->next;
            }
         }
         if (!pFile)
         {
            return  - 1;
         }
      }
   }

   // bench sample / defined devices / switch
   CHsampleNeeded = 0;
   CHdcsupplieNeeded = 0;
   CHdioNeeded = 0;
   k = 1;
   for (i = 0; i < iIndex; i++)
   {
      IsListItemChecked(iPhysExportPanelHandle, EXPORT_EXPORTDEV, i, &isChecked);
      if (isChecked)
      {
         GetLabelFromIndex(iPhysExportPanelHandle, EXPORT_EXPORTDEV, i, cLabel);
         ptr = pFirstRessource;
         while (ptr)
         {
            if (strcmp(ptr->cBenchName, cLabel) == 0)
            {
               if (strcmp(ptr->cType, "PAM") == 0)
               {
                  fprintf(pFile, "SwitchDevice%i = device->%s\n", k, ptr->cBenchName);
                  k++;
               }
               if (strcmp(ptr->cType, "PDFT") == 0)
               {
                  fprintf(pFile, "SwitchDevice%i = device->%s\n", k, ptr->cBenchName);
                  CHdioNeeded = 1;
                  k++;
               }
               if (strcmp(ptr->cType, "PFG") == 0)
               {
                  fprintf(pFile, "SwitchDevice%i = device->%s\n", k, ptr->cBenchName);
                  k++;
               }

               if (strcmp(ptr->cType, "PIO2") == 0)
               {
                  fprintf(pFile, "SwitchDevice%i = device->%s\n", k, ptr->cBenchName);
                  k++;
               }
               if (strcmp(ptr->cType, "PMB") == 0)
               {
                  fprintf(pFile, "SwitchDevice%i = device->%s\n", k, ptr->cBenchName);
                  CHsampleNeeded = 1;
                  k++;
               }
               if (strcmp(ptr->cType, "PSAM") == 0)
               {
                  fprintf(pFile, "SwitchDevice%i = device->%s\n", k, ptr->cBenchName);
                  k++;
               }
               if (strcmp(ptr->cType, "PSM1") == 0)
               {
                  fprintf(pFile, "SwitchDevice%i = device->%s\n", k, ptr->cBenchName);
                  CHsampleNeeded = 1;
                  k++;
               }
               if (strcmp(ptr->cType, "PSM2") == 0)
               {
                  fprintf(pFile, "SwitchDevice%i = device->%s\n", k, ptr->cBenchName);
                  CHsampleNeeded = 1;
                  k++;
               }
               if (strcmp(ptr->cType, "PSU") == 0)
               {
                  fprintf(pFile, "SwitchDevice%i = device->%s\n", k, ptr->cBenchName);
                  CHdcsupplieNeeded = 1;
                  k++;
               }
               if (strcmp(ptr->cType, "PSYS1") == 0)
               {
                  fprintf(pFile, "SwitchDevice%i = device->%s\n", k, ptr->cBenchName);
                  k++;
               }
               ptr->iMarkedForExport = 1;
               break;
            }
            else
            {
               ptr = ptr->next;
            }
         }
         if (!pFile)
         {
            return  - 1;
         }
      }


   }
   // bench sample / defined devices / analog bus
   GetCtrlVal(iPhysExportPanelHandle, EXPORT_EXPORTABUS, &iABUS);
   if (iABUS)
   {
      fprintf(pFile, "AnalogBus = device->ABUS\n");
   }

   fprintf(pFile, "AppChannelTable	= io_channel->%s_analog\n", cBenchName);


   // bench sample / defined devices / channeltables & others
   k = 0;
   n = 0;
   p1 = 0;
   p2 = 0;
   p3 = 0;
   for (i = 0; i < iIndex; i++)
   {
      IsListItemChecked(iPhysExportPanelHandle, EXPORT_EXPORTDEV, i, &isChecked);
      if (isChecked)
      {
         GetLabelFromIndex(iPhysExportPanelHandle, EXPORT_EXPORTDEV, i, cLabel);
         ptr = pFirstRessource;
         while (ptr)
         {
            if (strcmp(ptr->cBenchName, cLabel) == 0)
            {
               if ((strcmp(ptr->cType, "PDFT") == 0) && (n == 0))
               {
                  fprintf(pFile, "DIOTriggerLine = 1\n");
                  fprintf(pFile, "DIOChannelTable = io_channel->%s_digital\n", cBenchName);
                  n++;
               }
               if ((strcmp(ptr->cType, "PSU") == 0) && (k == 0))
               {
                  fprintf(pFile, "DCPwrChannelTable = io_channel->dcsupplies\n");
                  k++;
               }
               ptr->iMarkedForExport = 1;
               break;
            }
            else
            {
               ptr = ptr->next;
            }
         }
         if (!pFile)
         {
            return  - 1;
         }
      }
   }


   // i/o channels dcsupplies
   GetCtrlVal(iPhysExportPanelHandle, EXPORT_EXPORTSYSCH, &iSYSCH);
   if (iSYSCH)
   {
      if (CHdcsupplieNeeded)
      {
         fprintf(pFile, "\n[io_channel->dcsupplies]\n");
      }
      k = 1;
      for (i = 0; i < iIndex; i++)
      {
         IsListItemChecked(iPhysExportPanelHandle, EXPORT_EXPORTDEV, i, &isChecked);
         if (isChecked)
         {
            GetLabelFromIndex(iPhysExportPanelHandle, EXPORT_EXPORTDEV, i, cLabel);
            ptr = pFirstRessource;
            while (ptr)
            {
               if (strcmp(ptr->cBenchName, cLabel) == 0)
               {
                  if (strcmp(ptr->cType, "PSU") == 0)
                  {
                     fprintf(pFile, "%s_CH1 = %s!CH1\n", ptr->cBenchName, ptr->cBenchName);
                     k++;
                     fprintf(pFile, "%s_CH2 = %s!CH2\n", ptr->cBenchName, ptr->cBenchName);
                     k++;
                  }
                  ptr->iMarkedForExport = 1;
                  break;
               }
               else
               {
                  ptr = ptr->next;
               }
            }
            if (!pFile)
            {
               return  - 1;
            }
         }
      }
   }

   // i/o channels sample
   GetCtrlVal(iPhysExportPanelHandle, EXPORT_EXPORTSYSCH, &iSYSCH);
   if (iSYSCH)
   {
      if (CHsampleNeeded)
      {
         fprintf(pFile, "\n[io_channel->%s_analog]\n", cBenchName);
      }
      k = 1;
      for (i = 0; i < iIndex; i++)
      {
         IsListItemChecked(iPhysExportPanelHandle, EXPORT_EXPORTDEV, i, &isChecked);
         if (isChecked)
         {
            GetLabelFromIndex(iPhysExportPanelHandle, EXPORT_EXPORTDEV, i, cLabel);
            ptr = pFirstRessource;
            while (ptr)
            {
               if (strcmp(ptr->cBenchName, cLabel) == 0)
               {
                  if (strcmp(ptr->cType, "PMB") == 0)
                  {
                     if (!iExportAllChannels)
                     {
                        fprintf(pFile, "LogicalPinName%i = %s!P1\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!P2\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!P3\n", k, ptr->cBenchName);
                        k++;
                     }
                     else
                     {
                        fprintf(pFile, "LogicalPinName%i = %s!P1\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!P2\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!P3\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!P4\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!P5\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!P6\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!P7\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!P8\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!P9\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!P10\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!P11\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!P12\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!P13\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!P14\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!P15\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!P16\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!P17\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!P18\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!P19\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!P20\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!P21\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!P22\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!P23\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!P24\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!P25\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!P26\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!P27\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!P28\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!P29\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!P30\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!P31\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!P32\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!P33\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!P34\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!P35\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!P36\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!P37\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!P38\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!P39\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!P40\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!P41\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!P42\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!P43\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!P44\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!P45\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!P46\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!P47\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!P48\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!P49\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!P50\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!P51\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!P52\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!P53\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!P54\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!P55\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!P56\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!P57\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!P58\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!P59\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!P60\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!P61\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!P62\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!P63\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!P64\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!P65\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!P66\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!P67\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!P68\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!P69\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!P70\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!P71\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!P72\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!P73\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!P74\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!P75\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!P76\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!P77\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!P78\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!P79\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!P80\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!P81\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!P82\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!P83\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!P84\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!P85\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!P86\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!P87\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!P88\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!P89\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!P90\n\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!IL1\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!IL2\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!IL3\n\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!GND\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!GNDNO\n\n", k, ptr->cBenchName);
                        k++;
                     }

                  }
                  if (strcmp(ptr->cType, "PSM1") == 0)
                  {
                     if (!iExportAllChannels)
                     {
                        fprintf(pFile, "LogicalPinName%i = %s!CH1no\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!CH1com\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!CH2no\n", k, ptr->cBenchName);
                        k++;
                     }
                     else
                     {
                        fprintf(pFile, "LogicalPinName%i = %s!CH1no\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!CH2no\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!CH3no\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!CH4no\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!CH5no\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!CH6no\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!CH7no\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!CH8no\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!CH9no\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!CH10no\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!CH11no\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!CH12no\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!CH13no\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!CH14no\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!CH15no\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!CH16no\n\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!CH1com\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!CH2com\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!CH3com\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!CH4com\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!CH5com\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!CH6com\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!CH7com\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!CH8com\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!CH9com\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!CH10com\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!CH11com\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!CH12com\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!CH13com\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!CH14com\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!CH15com\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!CH16com\n\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!LPBA\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!LPBB\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!LPBC\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!LPBD\n\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!IL1no\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!IL2no\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!IL1com\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!IL2com\n\n", k, ptr->cBenchName);
                        k++;
                     }
                  }
                  if (strcmp(ptr->cType, "PSM2") == 0)
                  {
                     if (!iExportAllChannels)
                     {
                        fprintf(pFile, "LogicalPinName%i = %s!CH1\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!CH1_HI\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!CH1_LO\n", k, ptr->cBenchName);
                        k++;
                     }
                     else
                     {
                        fprintf(pFile, "LogicalPinName%i = %s!CH1\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!CH1_HI\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!CH1_LO\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!CH1_1\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!CH1_2\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!CH1_3\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!CH1_4\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!CH1_HI1\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!CH1_LO1\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!CH1_HI2\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!CH1_LO2\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!CH1_HI3\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!CH1_LO3\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!CH1_HI4\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!CH1_LO4\n\n", k, ptr->cBenchName);
                        k++;

                        fprintf(pFile, "LogicalPinName%i = %s!CH2\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!CH2_HI\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!CH2_LO\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!CH2_1\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!CH2_2\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!CH2_3\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!CH2_4\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!CH2_HI1\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!CH2_LO1\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!CH2_HI2\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!CH2_LO2\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!CH2_HI3\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!CH2_LO3\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!CH2_HI4\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!CH2_LO4\n\n", k, ptr->cBenchName);
                        k++;

                        fprintf(pFile, "LogicalPinName%i = %s!CH3\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!CH3_HI\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!CH3_LO\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!CH3_1\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!CH3_2\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!CH3_3\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!CH3_4\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!CH3_HI1\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!CH3_LO1\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!CH3_HI2\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!CH3_LO2\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!CH3_HI3\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!CH3_LO3\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!CH3_HI4\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!CH3_LO4\n\n", k, ptr->cBenchName);
                        k++;

                        fprintf(pFile, "LogicalPinName%i = %s!CH4\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!CH4_HI\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!CH4_LO\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!CH4_1\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!CH4_2\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!CH4_3\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!CH4_4\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!CH4_HI1\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!CH4_LO1\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!CH4_HI2\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!CH4_LO2\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!CH4_HI3\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!CH4_LO3\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!CH4_HI4\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!CH4_LO4\n\n", k, ptr->cBenchName);
                        k++;

                        fprintf(pFile, "LogicalPinName%i = %s!CH5\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!CH5_HI\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!CH5_LO\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!CH5_1\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!CH5_2\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!CH5_3\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!CH5_4\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!CH5_HI1\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!CH5_LO1\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!CH5_HI2\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!CH5_LO2\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!CH5_HI3\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!CH5_LO3\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!CH5_HI4\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!CH5_LO4\n\n", k, ptr->cBenchName);
                        k++;

                        fprintf(pFile, "LogicalPinName%i = %s!CH6\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!CH6_HI\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!CH6_LO\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!CH6_1\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!CH6_2\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!CH6_3\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!CH6_4\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!CH6_HI1\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!CH6_LO1\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!CH6_HI2\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!CH6_LO2\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!CH6_HI3\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!CH6_LO3\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!CH6_HI4\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!CH6_LO4\n\n", k, ptr->cBenchName);
                        k++;

                        fprintf(pFile, "LogicalPinName%i = %s!CH7\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!CH7_HI\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!CH7_LO\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!CH7_1\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!CH7_2\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!CH7_3\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!CH7_4\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!CH7_HI1\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!CH7_LO1\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!CH7_HI2\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!CH7_LO2\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!CH7_HI3\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!CH7_LO3\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!CH7_HI4\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!CH7_LO4\n\n", k, ptr->cBenchName);
                        k++;

                        fprintf(pFile, "LogicalPinName%i = %s!CH8\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!CH8_HI\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!CH8_LO\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!CH8_1\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!CH8_2\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!CH8_3\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!CH8_4\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!CH8_HI1\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!CH8_LO1\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!CH8_HI2\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!CH8_LO2\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!CH8_HI3\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!CH8_LO3\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!CH8_HI4\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!CH8_LO4\n\n", k, ptr->cBenchName);
                        k++;

                        fprintf(pFile, "LogicalPinName%i = %s!LPBA\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalPinName%i = %s!LPBB\n\n", k, ptr->cBenchName);
                        k++;

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
            if (!pFile)
            {
               return  - 1;
            }
         }
      }
   }

   // i/o channels dio
   GetCtrlVal(iPhysExportPanelHandle, EXPORT_EXPORTSYSCH, &iSYSCH);
   if (iSYSCH)
   {
      if (CHdioNeeded)
      {
         fprintf(pFile, "\n[io_channel->%s_digital]\n", cBenchName);
      }
      k = 1;
      for (i = 0; i < iIndex; i++)
      {
         IsListItemChecked(iPhysExportPanelHandle, EXPORT_EXPORTDEV, i, &isChecked);
         if (isChecked)
         {
            GetLabelFromIndex(iPhysExportPanelHandle, EXPORT_EXPORTDEV, i, cLabel);
            ptr = pFirstRessource;
            while (ptr)
            {
               if (strcmp(ptr->cBenchName, cLabel) == 0)
               {
                  if (strcmp(ptr->cType, "PDFT") == 0)
                  {
                     if (!iExportAllChannels)
                     {
                        fprintf(pFile, "LogicalDIOName%i = %s!OUT1\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalDIOName%i = %s!IN1\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalDIOName%i = %s!OUT2\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalDIOName%i = %s!IN2\n", k, ptr->cBenchName);
                        k++;
                     }
                     else
                     {
                        fprintf(pFile, "LogicalDIOName%i = %s!OUT1\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalDIOName%i = %s!IN1\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalDIOName%i = %s!OUT2\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalDIOName%i = %s!IN2\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalDIOName%i = %s!OUT3\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalDIOName%i = %s!IN3\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalDIOName%i = %s!OUT4\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalDIOName%i = %s!IN4\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalDIOName%i = %s!OUT5\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalDIOName%i = %s!IN5\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalDIOName%i = %s!OUT6\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalDIOName%i = %s!IN6\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalDIOName%i = %s!OUT7\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalDIOName%i = %s!IN7\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalDIOName%i = %s!OUT8\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalDIOName%i = %s!IN8\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalDIOName%i = %s!OUT9\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalDIOName%i = %s!IN9\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalDIOName%i = %s!OUT10\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalDIOName%i = %s!IN10\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalDIOName%i = %s!OUT11\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalDIOName%i = %s!IN11\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalDIOName%i = %s!OUT12\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalDIOName%i = %s!IN12\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalDIOName%i = %s!OUT13\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalDIOName%i = %s!IN13\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalDIOName%i = %s!OUT14\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalDIOName%i = %s!IN14\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalDIOName%i = %s!OUT15\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalDIOName%i = %s!IN15\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalDIOName%i = %s!OUT16\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalDIOName%i = %s!IN16\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalDIOName%i = %s!OUT17\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalDIOName%i = %s!IN17\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalDIOName%i = %s!OUT18\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalDIOName%i = %s!IN18\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalDIOName%i = %s!OUT19\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalDIOName%i = %s!IN19\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalDIOName%i = %s!OUT20\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalDIOName%i = %s!IN20\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalDIOName%i = %s!OUT21\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalDIOName%i = %s!IN21\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalDIOName%i = %s!OUT22\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalDIOName%i = %s!IN22\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalDIOName%i = %s!OUT23\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalDIOName%i = %s!IN23\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalDIOName%i = %s!OUT24\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalDIOName%i = %s!IN24\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalDIOName%i = %s!OUT25\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalDIOName%i = %s!IN25\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalDIOName%i = %s!OUT26\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalDIOName%i = %s!IN26\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalDIOName%i = %s!OUT27\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalDIOName%i = %s!IN27\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalDIOName%i = %s!OUT28\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalDIOName%i = %s!IN28\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalDIOName%i = %s!OUT29\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalDIOName%i = %s!IN29\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalDIOName%i = %s!OUT30\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalDIOName%i = %s!IN30\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalDIOName%i = %s!OUT31\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalDIOName%i = %s!IN31\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalDIOName%i = %s!OUT32\n", k, ptr->cBenchName);
                        k++;
                        fprintf(pFile, "LogicalDIOName%i = %s!IN32\n", k, ptr->cBenchName);
                        k++;
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
            if (!pFile)
            {
               return  - 1;
            }
         }
      }
   }

   // additional bench 		

   if ((ipsam > 1) || (ipam > 1) || (ipfg > 1))
   {

      if (ipsam >= ipam)
      // detection of the biggest value
      {
         if (ipsam >= ipfg)
         {
            n = ipsam;
         }
         else
         {
            n = ipfg;
         }
      }
      else
      {
         if (ipam >= ipfg)
         {
            n = ipam;
         }
         else
         {
            n = ipfg;
         }
      }



      for (k = 2; k <= n; k++)
      {
         t1 = 0;
         t2 = 0;
         t3 = 0;

         fprintf(pFile, "\n[bench->%s%i]\n", cBenchName, k);

         for (i = 0; i < iIndex; i++)
         {
            IsListItemChecked(iPhysExportPanelHandle, EXPORT_EXPORTDEV, i, &isChecked);
            if (isChecked)
            {
               GetLabelFromIndex(iPhysExportPanelHandle, EXPORT_EXPORTDEV, i, cLabel);
               ptr = pFirstRessource;
               while (ptr)
               {
                  if (strcmp(ptr->cBenchName, cLabel) == 0)
                  {
                     if ((strcmp(ptr->cType, "PSAM") == 0) && (ipsam > 1))
                     {
                        p1++;
                        if (p1 > 1 && !t1)
                        {
                           fprintf(pFile, "Digitalmultimeter = device->%s\n", ptr->cBenchName);
                           ipsam--;
                           t1 = 1; // only one device of the same type in one bench
                        }

                     }
                     if ((strcmp(ptr->cType, "PAM") == 0) && (ipam > 1))
                     {
                        p2++;
                        if (p2 > 1 && !t2)
                        {
                           fprintf(pFile, "SignalAnalyzer = device->%s\n", ptr->cBenchName);
                           ipam--;
                           t2 = 1;
                        }
                     }
                     if ((strcmp(ptr->cType, "PFG") == 0) && (ipfg > 1))
                     {
                        p3++;
                        if (p3 > 1 && !t3)
                        {
                           fprintf(pFile, "FunctionGenerator = device->%s\n", ptr->cBenchName);
                           ipfg--;
                           t3 = 1;
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
               if (!pFile)
               {
                  return  - 1;
               }
            }
         }
      }
   }

   // end
   fprintf(pFile, "\n;\n; EOF\n;");
   fclose(pFile);
   iWantAppIni = 1; // for the export-completed-popup
   return 0;
}


/* FUNCTION *****************************************************************/
/**
WriteTeststandSeq
 *
@brief This function writes a teststand-seq-file depending on infos received
from scanning process, like type and quantity of devices
\n[code by Albert Killer]
 *
@return Error code
 *****************************************************************************/
int WriteTeststandSeq(void)
{
   int iStatus, iConfirm;
   char cPathName[1024];
   char cPathNameWithDoubleSlash[1024];
   char cDrive[10];
   char cPath[300];
   char cName[300];
   int i, k, n, iIndex, isChecked;
   int iIOChannels, iABUS, iSYSCH;
   char cLabel[128];
   FILE* pFile = NULL;
   ressource* ptr;

   int iPAMchecked = 0;
   int iPDFTchecked = 0;
   int iPFGchecked = 0;
   int iPHDTchecked = 0;
   int iPICTchecked = 0;
   int iPIO2checked = 0;
   int iPSAMchecked = 0;
   int iPSUchecked = 0;

   int iSteps = 0; // counts all steps in seq 5 and 6
   int iBenches = 1; // counts number of benches to be created
   int iSpecDev = 0; // counts devices which have to be initialized by a seperatly step
   int iCharWritten = 0; // counts number of characters in a string array
   int iStepIndex = 0; // number of present step
   int iDevCountBuffer[10] =
   {
      0
   }; // to buffer the number of counted devices

   char cFullName[30];
   char cAKA[30];
   char cSetupName[30];

   iWantTstSeq = 0; // for the export-completed-popup

   if (sDemoMode)
   {
      return 0;
   }

   if (!pFile)
   {
      iStatus = FileSelectPopup(cLastFilePath, "sample.seq", "", "Specify name of Teststand Sequence", VAL_SAVE_BUTTON, 0, 1, 1, 1, cPathName);
      sprintf(cLastFilePath, "%s", cPathName);
      switch (iStatus)
      {
         case 1:
            iStatus = DeleteFile(cPathName);
            break;
         case 2:
            iStatus = 0;
            break;
         default:
            return 0;
      }
      if (iStatus)
      {
         switch (iStatus)
         {
            case  - 6: iConfirm = ConfirmPopup("TG-ITS", "Access denied. Overwrite the file?");
            if (iConfirm)
            {
               iStatus = SetFileAttrs(cPathName, 0, 0, 0, 0);
               if (iStatus)
               {
                  MessagePopup("TG-ITS", "Could not delete file. Please check attributes");
                  return 0;
               }
            }
            break;
            default:
               MessagePopup("TG-ITS", "An unknown error has occured");
               return 0;
         }
      }
      sprintf(cTeststandSeqPath, "%s", cPathName);
      pFile = fopen(cPathName, "w");
   }

   // Format strings for print out
   SplitPath(cPathName, cDrive, cPath, cName);

   // Which of the found devices are checked??

   GetNumListItems(iPhysExportPanelHandle, EXPORT_EXPORTDEV, &iIndex);

   for (i = 0; i < iIndex; i++)
   {
      IsListItemChecked(iPhysExportPanelHandle, EXPORT_EXPORTDEV, i, &isChecked);
      if (isChecked)
      {
         GetLabelFromIndex(iPhysExportPanelHandle, EXPORT_EXPORTDEV, i, cLabel);
         ptr = pFirstRessource;
         while (ptr)
         {
            if (strcmp(ptr->cBenchName, cLabel) == 0)
            {
               if (strcmp(ptr->cType, "PSAM") == 0)
               // because of bench number
               {
                  iPSAMchecked++;
                  iDevCountBuffer[0] = iPSAMchecked;
               }
               if (strcmp(ptr->cType, "PAM") == 0)
               {
                  iPAMchecked++;
                  iDevCountBuffer[1] = iPAMchecked;
               }
               if (strcmp(ptr->cType, "PDFT") == 0)
               {
                  iPDFTchecked = 1; // because there is only one intialization also for multiple dev
                  iDevCountBuffer[3] = iPDFTchecked;
               }
               if (strcmp(ptr->cType, "PFG") == 0)
               {
                  iPFGchecked++;
                  iDevCountBuffer[2] = iPFGchecked;
               }
               if (strcmp(ptr->cType, "PHDT") == 0)
               {
                  iPHDTchecked++;
                  iDevCountBuffer[4] = iPHDTchecked;
               }
               if (strcmp(ptr->cType, "PICT") == 0)
               {
                  iPICTchecked = 1; // see above
                  iDevCountBuffer[5] = iPICTchecked;
               }
               if (strcmp(ptr->cType, "PIO2") == 0)
               {
                  iPIO2checked++;
                  iDevCountBuffer[6] = iPIO2checked;
               }
               if (strcmp(ptr->cType, "PSU") == 0)
               {
                  iPSUchecked = 1; // see above
                  iDevCountBuffer[7] = iPSUchecked;
               }
               ptr->iMarkedForExport = 1;
               break;
            }
            else
            {
               ptr = ptr->next;
            }
         }
         if (!pFile)
         {
            return  - 1;
         }
      }
   }

   // number of benches to be created

   if ((iPSAMchecked > 1) || (iPAMchecked > 1) || (iPFGchecked > 1))
   {

      if (iPSAMchecked >= iPAMchecked)
      // detection of biggest value
      {
         if (iPSAMchecked >= iPFGchecked)
         {
            iBenches = iPSAMchecked;
         }
         else
         {
            iBenches = iPFGchecked;
         }
      }
      else
      {
         if (iPAMchecked >= iPFGchecked)
         {
            iBenches = iPAMchecked;
         }
         else
         {
            iBenches = iPFGchecked;
         }
      }
   }

   // number of special devices and number of steps

   iSpecDev = iPSAMchecked + iPAMchecked + iPDFTchecked + iPFGchecked + iPICTchecked + iPSUchecked + iPHDTchecked + iPIO2checked;
   iSteps = 12+iBenches + (2* iSpecDev) - 1; // -1 because zero-based, 12 because of stationglob.init + 2 time stationglob. var set & ph.ini & app.ini & minimum 1 bench & text output & resmgr & text output & swmgr & 2 extended userinterface



   // H E A D E R

   fprintf(pFile, "[__Header__]\n");
   fprintf(pFile, "ProductName = \"TestStand\"\n");
   fprintf(pFile, "ProductVersion = 2.0.1.121\n");
   fprintf(pFile, "Version = 143\n");
   fprintf(pFile, "Type = \"SequenceFile\"\n");

   DoubleBackslash(cPathName, cPathNameWithDoubleSlash); // double backslash for pathname
   iCharWritten = sprintf(cPath, cPathNameWithDoubleSlash);
   if (iCharWritten < 134)
   // checks if path fits into the line
   {
      fprintf(pFile, "Path = \"%s\"\n", cPath);
   }
   if (iCharWritten >= 134)
   // writes 1st and 2nd line	
   {

      for (i = 0; i < 125; i++)
      {
         cPathNameWithDoubleSlash[i] = cPath[i];
      }
      cPathNameWithDoubleSlash[i] = '\0';
      fprintf(pFile, "Path Line0001= \"%s\"\n", cPathNameWithDoubleSlash);
      for (k = 0; k < 125; k++, i++)
      {
         cPathNameWithDoubleSlash[k] = cPath[i];
      }
      cPathNameWithDoubleSlash[k] = '\0';
      fprintf(pFile, "Path Line0002= \"%s", cPathNameWithDoubleSlash);

      if (iCharWritten > 252)
      // writes 3rd line	
      {
         for (k = 0; k < 49; k++, i++)
         {
            cPathNameWithDoubleSlash[k] = cPath[i];
         }
         cPathNameWithDoubleSlash[k] = '\0';
         fprintf(pFile, "\"\nPath Line0003= \"%s\"\n", cPathNameWithDoubleSlash);
      }
      else
      {
         fprintf(pFile, "\"\n");
      }
   }
   fprintf(pFile, "ProductVersionString = \"2.0.1f1\"\n");
   fprintf(pFile, "CharEncoding = \"SBCS\"\n");

   // D E F I N I T I O N S   +   S E Q U E N C E 0-4

   fprintf(pFile, "\n[DEF, %%OBJECTS]\n");
   fprintf(pFile, "SF = SequenceFileData\n");
   fprintf(pFile, "Path = PathValue\n");
   fprintf(pFile, "Action = StepType\n");
   fprintf(pFile, "StepTypeSubstepsArray = Objs\n");
   fprintf(pFile, "StepTypeDescFmt = Str\n");
   fprintf(pFile, "StepTypeDefNameFmt = Str\n");
   fprintf(pFile, "StepTypeMenu = Obj\n");
   fprintf(pFile, "TEInf = Obj\n");
   fprintf(pFile, "Error = Obj\n");
   fprintf(pFile, "CommonResults = Obj\n");
   fprintf(pFile, "FlexCStepAdditions = Obj\n");
   fprintf(pFile, "FCParameter = FCParameter\n");
   fprintf(pFile, "UUT = Obj\n");
   fprintf(pFile, "NI_CriticalFailureStackEntry = Obj\n");
   fprintf(pFile, "EditSubstep = StepType\n");
   fprintf(pFile, "NoneStepAdditions = Obj\n");
   fprintf(pFile, "Statement = StepType\n");
   fprintf(pFile, "Label = StepType\n");
   fprintf(pFile, "Goto = StepType\n");

   fprintf(pFile, "NI_Wait = StepType\n");
   fprintf(pFile, "PostSubstep = StepType\n");
   fprintf(pFile, "StepTypeDescFmt = Str\n");
   fprintf(pFile, "StepTypeDefNameFmt = Str\n");
   fprintf(pFile, "UUT = Obj\n");
   fprintf(pFile, "NI_CriticalFailureStackEntry = Obj\n");

   if (iPHDTchecked || iPIO2checked)
   // if phdt or pio2 is avialable
   {
      fprintf(pFile, "SeqCallStepAdditions = Obj\n");
      fprintf(pFile, "SequenceArgument = Argument\n");
   }
   // Rest of Def & Seq0-4
   fprintf(pFile, "\n");
   sprintf(cPathName, "%s\\resources\\template4.txt", cProjectDir); // Insert template with definitions and static sequences 0,1,2,3,4
   pFile = MergeEncodedTextFile(pFile, cPathName);
   if (pFile == 0)
   {
      MessagePopup("TG-ITS", "Could not open %s\nCheck resource folder!");
      return 0;
   }
   fprintf(pFile, "\n");

   // SEQ 5 ===== S E Q E N C E F I L E L O A D

   // DEF, SF.Seq[5]
   fprintf(pFile, "\n[DEF, SF.Seq[5]]\n");
   fprintf(pFile, "Parameters = Obj\n");
   fprintf(pFile, "Locals = Obj\n");
   fprintf(pFile, "Main = Objs\n");
   fprintf(pFile, "Setup = Objs\n");
   fprintf(pFile, "Cleanup = Objs\n");
   fprintf(pFile, "GotoCleanupOnFail = Bool\n");
   fprintf(pFile, "StoreResults = Bool\n");
   fprintf(pFile, "RecordResults = Bool\n");
   fprintf(pFile, "RTS = Obj\n");
   fprintf(pFile, "Requirements = Obj\n");
   fprintf(pFile, "%%NAME = \"SequenceFileLoad\"\n");
   // SF.Seq[5].
   fprintf(pFile, "\n[SF.Seq[5]]\n");
   fprintf(pFile, "%%FLG: Parameters = 262144\n");
   fprintf(pFile, "%%LO: Main = [0]\n");
   fprintf(pFile, "%%HI: Main = [%i]\n", iSteps); // define no. of steps
   fprintf(pFile, "%%LO: Cleanup = [0]\n");
   fprintf(pFile, "%%HI: Cleanup = [1]\n");
   fprintf(pFile, "%%FLG: GotoCleanupOnFail = 8\n");
   fprintf(pFile, "StoreResults = True\n");
   fprintf(pFile, "RecordResults = True\n");
   fprintf(pFile, "%%FLG: RecordResults = 8\n");
   fprintf(pFile, "%%FLG: RTS = 262152\n");
   fprintf(pFile, "%%FLG: Requirements = 4456456\n");
   // ResultList
   fprintf(pFile, "\n[DEF, SF.Seq[5].Locals]\n");
   fprintf(pFile, "ResultList = Objs\n");
   // EPTYPE
   fprintf(pFile, "\n[DEF, SF.Seq[5].Locals.ResultList]\n");
   fprintf(pFile, "%%EPTYPE = TEResult\n");
   // Main Def
   fprintf(pFile, "\n[DEF, SF.Seq[5].Main]\n");
   k = iSteps - 2 *(iPHDTchecked + iPIO2checked) + 1; // step-no. of first phdt or pio2 dev
   for (i = 0; i <= iSteps; i++)
   {
      if ((0 < i) && (i < (4+iBenches)))
      // phy.ini, app.ini, benches
      {
         fprintf(pFile, "%%[%i] = NoneStep\n", i);
         fprintf(pFile, "%%TYPE: %%[%i] = \"Statement\"\n", i);
      }
      else if (i == k)
      // if step-no. reached no. of first phdt or pio2 (if there are none of them "i" is never equal to "k")
      {
         fprintf(pFile, "%%[%i] = FlexCStep\n", i);
         fprintf(pFile, "%%TYPE: %%[%i] = \"Action\"\n", i);
         i++;
         k++;
         fprintf(pFile, "%%[%i] = SequenceCall\n", i);
         fprintf(pFile, "%%TYPE: %%[%i] = \"Action\"\n", i);
         k++;
      }
      else if (i == iSteps)
      // the last step has to set the StationGlobal SequenceFileLoadComplete to True
      {
         fprintf(pFile, "%%[%i] = NoneStep\n", i);
         fprintf(pFile, "%%TYPE: %%[%i] = \"Statement\"\n", i);
      }
      else
      // FlexCStep Actions
      {
         fprintf(pFile, "%%[%i] = FlexCStep\n", i);
         fprintf(pFile, "%%TYPE: %%[%i] = \"Action\"\n", i);
      }
   }

   // SEQ 5 == [-0-] == CREATE STATIONGLOBALS

   // Adapter
   fprintf(pFile, "\n[SF.Seq[5].Main[0].TS]\n");
   fprintf(pFile, "Adapter = \"DLL Flexible Prototype Adapter\"\n");
   // SData
   fprintf(pFile, "\n[DEF, SF.Seq[5].Main[0].TS]\n");
   fprintf(pFile, "SData = \"TYPE, FlexCStepAdditions\"\n");
   fprintf(pFile, "%%FLG: SData = 2097152\n");
   // Lib & Param Def
   fprintf(pFile, "\n[SF.Seq[5].Main[0].TS.SData.Call]\n");
   fprintf(pFile, "LibPath = \"ts_support_32.dll\"\n");
   fprintf(pFile, "Func = \"tss_CreateStationGlobals\"\n");
   fprintf(pFile, "%%LO: Parms = [0]\n");
   fprintf(pFile, "%%HI: Parms = [15]\n");
   // FCParameter
   fprintf(pFile, "\n[DEF, SF.Seq[5].Main[0].TS.SData.Call.Parms]\n");
   for (i = 0; i <= 15; i++)
   {
      fprintf(pFile, "%%[%i] = \"TYPE, FCParameter\"\n", i);
   }
   // Return Value
   fprintf(pFile, "\n[SF.Seq[5].Main[0].TS.SData.Call.Parms[0]]\n");
   fprintf(pFile, "Name = \"Return Value\"\n");
   fprintf(pFile, "Type = 3\n");
   // sequenceContext
   fprintf(pFile, "\n[SF.Seq[5].Main[0].TS.SData.Call.Parms[1]]\n");
   fprintf(pFile, "Name = \"sequenceContext\"\n");
   fprintf(pFile, "Type = 4\n");
   fprintf(pFile, "ObjType = 1\n");
   fprintf(pFile, "ArgVal = \"ThisContext\"\n");
   // nameOfPhyIni
   fprintf(pFile, "\n[SF.Seq[5].Main[0].TS.SData.Call.Parms[2]]\n");
   fprintf(pFile, "Name = \"nameOfPhyIni\"\n");
   fprintf(pFile, "Type = 2\n");
   fprintf(pFile, "StrPass = 2\n");
   SplitPath(cPhysicalIniPath, cDrive, cPath, cName); // overwrites cDrive, cPath, cName
   DoubleBackslash(cPath, cPathNameWithDoubleSlash); // double backslash for pathname
   iCharWritten = sprintf(cPath, "%s%s%s", cDrive, cPathNameWithDoubleSlash, cName);
   if (iCharWritten < 128)
   // checks if path fits into the line
   {
      fprintf(pFile, "ArgVal = \"\\\"%s\\\"\"\n", cPath);
   }
   if (iCharWritten >= 128)
   // writes 1st and 2nd line	
   {

      for (i = 0; i < 120; i++)
      {
         cPathNameWithDoubleSlash[i] = cPath[i];
      }
      cPathNameWithDoubleSlash[i] = '\0';
      fprintf(pFile, "ArgVal Line0001 = \"\\\"%s\"\n", cPathNameWithDoubleSlash);
      for (k = 0; k < 122; k++, i++)
      {
         cPathNameWithDoubleSlash[k] = cPath[i];
      }
      cPathNameWithDoubleSlash[k] = '\0';
      fprintf(pFile, "ArgVal Line0002 = \"%s", cPathNameWithDoubleSlash);

      if (iCharWritten > 242)
      // writes 3rd line	
      {
         for (k = 0; k < 58; k++, i++)
         {
            cPathNameWithDoubleSlash[k] = cPath[i];
         }
         cPathNameWithDoubleSlash[k] = '\0';
         fprintf(pFile, "\"\nArgVal Line0003 = \"%s\\\"\"\n", cPathNameWithDoubleSlash);
      }
      else
      {
         fprintf(pFile, "\\\"\"\n");
      }
   }
   // nameOfAppIni
   fprintf(pFile, "\n[SF.Seq[5].Main[0].TS.SData.Call.Parms[3]]\n");
   fprintf(pFile, "Name = \"nameOfAppIni\"\n");
   fprintf(pFile, "Type = 2\n");
   fprintf(pFile, "StrPass = 2\n");
   SplitPath(cApplicationIniPath, cDrive, cPath, cName); // overwrites cDrive, cPath, cName
   DoubleBackslash(cPath, cPathNameWithDoubleSlash); // double backslash for pathname
   iCharWritten = sprintf(cPath, "%s%s%s", cDrive, cPathNameWithDoubleSlash, cName);
   if (iCharWritten < 128)
   // checks if path fits into the line
   {
      fprintf(pFile, "ArgVal = \"\\\"%s\\\"\"\n", cPath);
   }
   if (iCharWritten >= 128)
   // writes 1st and 2nd line	
   {

      for (i = 0; i < 120; i++)
      {
         cPathNameWithDoubleSlash[i] = cPath[i];
      }
      cPathNameWithDoubleSlash[i] = '\0';
      fprintf(pFile, "ArgVal Line0001 = \"\\\"%s\"\n", cPathNameWithDoubleSlash);
      for (k = 0; k < 122; k++, i++)
      {
         cPathNameWithDoubleSlash[k] = cPath[i];
      }
      cPathNameWithDoubleSlash[k] = '\0';
      fprintf(pFile, "ArgVal Line0002 = \"%s", cPathNameWithDoubleSlash);

      if (iCharWritten > 242)
      // writes 3rd line	
      {
         for (k = 0; k < 58; k++, i++)
         {
            cPathNameWithDoubleSlash[k] = cPath[i];
         }
         cPathNameWithDoubleSlash[k] = '\0';
         fprintf(pFile, "\"\nArgVal Line0003 = \"%s\\\"\"\n", cPathNameWithDoubleSlash);
      }
      else
      {
         fprintf(pFile, "\\\"\"\n");
      }
   }
   // Def Benches
   fprintf(pFile, "\n[SF.Seq[5].Main[0].TS.SData.Call.Parms[4]]\n");
   fprintf(pFile, "Name = \"benchName\"\n");
   fprintf(pFile, "Type = 2\n");
   fprintf(pFile, "StrPass = 2\n");
   fprintf(pFile, "ArgVal = \"\\\"Sample1");
   if (iBenches > 1)
   {
      for (i = 2; i <= iBenches; i++)
      {
         fprintf(pFile, "|%i", i); // expands in case of multiple benches
      }
   }
   fprintf(pFile, "\\\"\"\n");
   // countOfPSAM
   fprintf(pFile, "\n[SF.Seq[5].Main[0].TS.SData.Call.Parms[5]]\n");
   fprintf(pFile, "Name = \"countOfPSAM\"\n");
   fprintf(pFile, "ArgVal = \"%i\"\n", iPSAMchecked);
   // countOfPICT
   fprintf(pFile, "\n[SF.Seq[5].Main[0].TS.SData.Call.Parms[6]]\n");
   fprintf(pFile, "Name = \"countOfPICT\"\n");
   fprintf(pFile, "ArgVal = \"%i\"\n", iPICTchecked);
   // countOfPFG
   fprintf(pFile, "\n[SF.Seq[5].Main[0].TS.SData.Call.Parms[7]]\n");
   fprintf(pFile, "Name = \"countOfPFG\"\n");
   fprintf(pFile, "ArgVal = \"%i\"\n", iPFGchecked);
   // countOfPDFT
   fprintf(pFile, "\n[SF.Seq[5].Main[0].TS.SData.Call.Parms[8]]\n");
   fprintf(pFile, "Name = \"countOfPDFT\"\n");
   fprintf(pFile, "ArgVal = \"%i\"\n", iPDFTchecked);
   // countOfPAM
   fprintf(pFile, "\n[SF.Seq[5].Main[0].TS.SData.Call.Parms[9]]\n");
   fprintf(pFile, "Name = \"countOfPAM\"\n");
   fprintf(pFile, "ArgVal = \"%i\"\n", iPAMchecked);
   // countOfPHDT
   fprintf(pFile, "\n[SF.Seq[5].Main[0].TS.SData.Call.Parms[10]]\n");
   fprintf(pFile, "Name = \"countOfPHDT\"\n");
   fprintf(pFile, "ArgVal = \"%i\"\n", iPHDTchecked);
   // countOfPSU
   fprintf(pFile, "\n[SF.Seq[5].Main[0].TS.SData.Call.Parms[11]]\n");
   fprintf(pFile, "Name = \"countOfPSU\"\n");
   fprintf(pFile, "ArgVal = \"%i\"\n", iPSUchecked);
   // countOfPIO2
   fprintf(pFile, "\n[SF.Seq[5].Main[0].TS.SData.Call.Parms[12]]\n");
   fprintf(pFile, "Name = \"countOfPIO2\"\n");
   fprintf(pFile, "ArgVal = \"%i\"\n", iPIO2checked);
   // errorOccured
   fprintf(pFile, "\n[SF.Seq[5].Main[0].TS.SData.Call.Parms[13]]\n");
   fprintf(pFile, "Name = \"errorOccurred\"\n");
   fprintf(pFile, "NumType = 2\n");
   fprintf(pFile, "NumPass = 1\n");
   fprintf(pFile, "ArgVal = \"Step.Result.Error.Occurred\"\n");
   // errorCode
   fprintf(pFile, "\n[SF.Seq[5].Main[0].TS.SData.Call.Parms[14]]\n");
   fprintf(pFile, "Name = \"errorCode\"\n");
   fprintf(pFile, "NumPass = 1\n");
   fprintf(pFile, "ArgVal = \"Step.Result.Error.Code\"\n");
   // errorMessage
   fprintf(pFile, "\n[SF.Seq[5].Main[0].TS.SData.Call.Parms[15]]\n");
   fprintf(pFile, "Name = \"errorMessage\"\n");
   fprintf(pFile, "Type = 2\n");
   fprintf(pFile, "StrPass = 2\n");
   fprintf(pFile, "ArgVal = \"Step.Result.Error.Msg\"\n");
   // Step-Name
   fprintf(pFile, "\n[DEF, SF.Seq[5].Main[0]]\n");
   fprintf(pFile, "%%NAME = \"StationGlobals erzeugen\"\n");



   // SEQ == [-1-] == SET SEQUENCEFILELOADCOMPLETE

   fprintf(pFile, "\n[SF.Seq[5].Main[1].TS]\n");
   fprintf(pFile, "Adapter = \"None Adapter\"\n");
   fprintf(pFile, "PostExpr = \"StationGlobals.TSVP.SequenceFileLoadComplete = False\"\n");

   fprintf(pFile, "\n[DEF, SF.Seq[5].Main[1].TS]\n");
   fprintf(pFile, "SData = \"TYPE, NoneStepAdditions\"\n");
   fprintf(pFile, "%%FLG: SData = 2097152\n");

   fprintf(pFile, "\n[DEF, SF.Seq[5].Main[1]]\n");
   fprintf(pFile, "%%NAME = \"StationGlobal setzen\"\n");



   // SEQ 5 == [-2-] == LOCATE PHYSICAL.INI

   // Path
   fprintf(pFile, "\n[SF.Seq[5].Main[2].TS]\n");
   fprintf(pFile, "Adapter = \"None Adapter\"\n");
   SplitPath(cPhysicalIniPath, cDrive, cPath, cName); // overwrites cDrive, cPath, cName
   DoubleBackslash(cPath, cPathNameWithDoubleSlash); // double backslash for pathname
   iCharWritten = sprintf(cPath, "%s%s%s", cDrive, cPathNameWithDoubleSlash, cName);
   if (iCharWritten < 88)
   // checks if path fits into the line
   {
      fprintf(pFile, "PostExpr = \"StationGlobals.TSVP.PhysicalIniFile = \\\"%s\\\"\"\n", cPath);
   }
   if (iCharWritten >= 88)
   // writes 1st and 2nd line	
   {

      for (i = 0; i < 80; i++)
      {
         cPathNameWithDoubleSlash[i] = cPath[i];
      }
      cPathNameWithDoubleSlash[i] = '\0';
      fprintf(pFile, "PostExpr Line0001 = \"StationGlobals.TSVP.PhysicalIniFile = \\\"%s\"\n", cPathNameWithDoubleSlash);
      for (k = 0; k < 120; k++, i++)
      {
         cPathNameWithDoubleSlash[k] = cPath[i];
      }
      cPathNameWithDoubleSlash[k] = '\0';
      fprintf(pFile, "PostExpr Line0002 = \"%s", cPathNameWithDoubleSlash);

      if (iCharWritten > 199)
      // writes 3rd line	
      {
         for (k = 0; k < 100; k++, i++)
         {
            cPathNameWithDoubleSlash[k] = cPath[i];
         }
         cPathNameWithDoubleSlash[k] = '\0';
         fprintf(pFile, "\"\nPostExpr Line0003 = \"%s\\\"\"\n", cPathNameWithDoubleSlash);
      }
      else
      {
         fprintf(pFile, "\\\"\"\n");
      }
   }
   // SData
   fprintf(pFile, "\n[DEF, SF.Seq[5].Main[2].TS]\n");
   fprintf(pFile, "SData = \"TYPE, NoneStepAdditions\"\n");
   fprintf(pFile, "%%FLG: SData = 2097152\n");
   // Step-Name
   fprintf(pFile, "\n[DEF, SF.Seq[5].Main[2]]\n");
   fprintf(pFile, "%%NAME = \"Physical-INI-Datei  festlegen\"\n");

   // SEQ 5 == [-3-] == LOCATE APPLICATION.INI

   // Path
   fprintf(pFile, "\n[SF.Seq[5].Main[3].TS]\n");
   fprintf(pFile, "Adapter = \"None Adapter\"\n");
   SplitPath(cApplicationIniPath, cDrive, cPath, cName); // overwrites cDrive, cPath, cName
   DoubleBackslash(cPath, cPathNameWithDoubleSlash); // double backslash for pathname
   iCharWritten = sprintf(cPath, "%s%s%s", cDrive, cPathNameWithDoubleSlash, cName);
   if (iCharWritten < 85)
   // checks if path fits into the line
   {
      fprintf(pFile, "PostExpr = \"StationGlobals.TSVP.ApplicationIniFile = \\\"%s\\\"\"\n", cPath);
   }
   if (iCharWritten >= 85)
   // writes 1st and 2nd line	
   {

      for (i = 0; i < 77; i++)
      {
         cPathNameWithDoubleSlash[i] = cPath[i];
      }
      cPathNameWithDoubleSlash[i] = '\0';
      fprintf(pFile, "PostExpr Line0001 = \"StationGlobals.TSVP.ApplicationIniFile = \\\"%s\"\n", cPathNameWithDoubleSlash);
      for (k = 0; k < 120; k++, i++)
      {
         cPathNameWithDoubleSlash[k] = cPath[i];
      }
      cPathNameWithDoubleSlash[k] = '\0';
      fprintf(pFile, "PostExpr Line0002 = \"%s", cPathNameWithDoubleSlash);

      if (iCharWritten > 199)
      // writes 3rd line	
      {
         for (k = 0; k < 103; k++, i++)
         {
            cPathNameWithDoubleSlash[k] = cPath[i];
         }
         cPathNameWithDoubleSlash[k] = '\0';
         fprintf(pFile, "\"\nPostExpr Line0003 = \"%s\\\"\"\n", cPathNameWithDoubleSlash);
      }
      else
      {
         fprintf(pFile, "\\\"\"\n");
      }
   }
   // SData
   fprintf(pFile, "\n[DEF, SF.Seq[5].Main[3].TS]\n");
   fprintf(pFile, "SData = \"TYPE, NoneStepAdditions\"\n");
   fprintf(pFile, "%%FLG: SData = 2097152\n");
   // Step-Name
   fprintf(pFile, "\n[DEF, SF.Seq[5].Main[3]]\n");
   fprintf(pFile, "%%NAME = \"Application-INI-Datei  festlegen\"\n");

   // SEQ 5 == [-4-] == SET BENCHES

   for (i = 4, k = 1; k <= iBenches; i++, k++)
   // sets every bench seperately
   {
      // Bench Names
      fprintf(pFile, "\n[SF.Seq[5].Main[%i].TS]\n", i);
      fprintf(pFile, "Adapter = \"None Adapter\"\n");
      fprintf(pFile, "PostExpr = \"StationGlobals.TSVP.BenchName%i = \\\"Sample%i\\\"\"\n", k, k);
      // SData
      fprintf(pFile, "\n[DEF, SF.Seq[5].Main[%i].TS]\n", i);
      fprintf(pFile, "SData = \"TYPE, NoneStepAdditions\"\n");
      fprintf(pFile, "%%FLG: SData = 2097152\n");
      // Step-Name
      fprintf(pFile, "\n[DEF, SF.Seq[5].Main[%i]]\n", i);
      if (iBenches > 1)
      {
         fprintf(pFile, "%%NAME = \"%i.Bench festlegen\"\n", k);
      }
      else
      {
         fprintf(pFile, "%%NAME = \"Bench festlegen\"\n");
      }
   }
   // next step!
   iStepIndex = i;

   // SEQ 5 == [-5-] == DISPLAY INIT PANEL

   // Adapter
   fprintf(pFile, "\n[SF.Seq[5].Main[%i].TS]\n", iStepIndex);
   fprintf(pFile, "Adapter = \"DLL Flexible Prototype Adapter\"\n");
   // SData
   fprintf(pFile, "\n[DEF, SF.Seq[5].Main[%i].TS]\n", iStepIndex);
   fprintf(pFile, "SData = \"TYPE, FlexCStepAdditions\"\n");
   fprintf(pFile, "%%FLG: SData = 2097152\n");
   // LibPath & Param Def
   fprintf(pFile, "\n[SF.Seq[5].Main[%i].TS.SData.Call]\n", iStepIndex);
   fprintf(pFile, "LibPath = \"ts_support_32.dll\"\n");
   fprintf(pFile, "Func = \"tss_ShowInitPanel\"\n");
   fprintf(pFile, "%%LO: Parms = [0]\n");
   fprintf(pFile, "%%HI: Parms = [5]\n");
   // FCParameters
   fprintf(pFile, "\n[DEF, SF.Seq[5].Main[%i].TS.SData.Call.Parms]\n", iStepIndex);
   fprintf(pFile, "%%[0] = \"TYPE, FCParameter\"\n");
   fprintf(pFile, "%%[1] = \"TYPE, FCParameter\"\n");
   fprintf(pFile, "%%[2] = \"TYPE, FCParameter\"\n");
   fprintf(pFile, "%%[3] = \"TYPE, FCParameter\"\n");
   fprintf(pFile, "%%[4] = \"TYPE, FCParameter\"\n");
   fprintf(pFile, "%%[5] = \"TYPE, FCParameter\"\n");
   // Return Value
   fprintf(pFile, "\n[SF.Seq[5].Main[%i].TS.SData.Call.Parms[0]]\n", iStepIndex);
   fprintf(pFile, "Name = \"Return Value\"\n");
   fprintf(pFile, "Type = 3\n");
   // sequenceContext
   fprintf(pFile, "\n[SF.Seq[5].Main[%i].TS.SData.Call.Parms[1]]\n", iStepIndex);
   fprintf(pFile, "Name = \"sequenceContext\"\n");
   fprintf(pFile, "Type = 4\n");
   fprintf(pFile, "ObjType = 1\n");
   fprintf(pFile, "ArgVal = \"ThisContext\"\n");
   // always Ontop
   fprintf(pFile, "\n[SF.Seq[5].Main[%i].TS.SData.Call.Parms[2]]\n", iStepIndex);
   fprintf(pFile, "Name = \"alwaysOntop\"\n");
   fprintf(pFile, "ArgVal = \"True\"\n");
   // errorOccurred
   fprintf(pFile, "\n[SF.Seq[5].Main[%i].TS.SData.Call.Parms[3]]\n", iStepIndex);
   fprintf(pFile, "Name = \"errorOccurred\"\n");
   fprintf(pFile, "NumType = 2\n");
   fprintf(pFile, "NumPass = 1\n");
   fprintf(pFile, "ArgVal = \"Step.Result.Error.Occurred\"\n");
   // errorCode
   fprintf(pFile, "\n[SF.Seq[5].Main[%i].TS.SData.Call.Parms[4]]\n", iStepIndex);
   fprintf(pFile, "Name = \"errorCode\"\n");
   fprintf(pFile, "NumPass = 1\n");
   fprintf(pFile, "ArgVal = \"Step.Result.Error.Code\"\n");
   // errorMessage
   fprintf(pFile, "\n[SF.Seq[5].Main[%i].TS.SData.Call.Parms[5]]\n", iStepIndex);
   fprintf(pFile, "Name = \"errorMessage\"\n");
   fprintf(pFile, "Type = 2\n");
   fprintf(pFile, "StrPass = 2\n");
   fprintf(pFile, "ArgVal = \"Step.Result.Error.Msg\"\n");
   // Step-Name
   fprintf(pFile, "\n[DEF, SF.Seq[5].Main[%i]]\n", iStepIndex);
   fprintf(pFile, "%%NAME = \"Init Panel anzeigen\"\n");
   // next step!
   iStepIndex++;

   // SEQ 5 == [-6-] == SET TEXT FOR INIT PANEL

   // Adapter
   fprintf(pFile, "\n[SF.Seq[5].Main[%i].TS]\n", iStepIndex);
   fprintf(pFile, "Adapter = \"DLL Flexible Prototype Adapter\"\n");
   // SData
   fprintf(pFile, "\n[DEF, SF.Seq[5].Main[%i].TS]\n", iStepIndex);
   fprintf(pFile, "SData = \"TYPE, FlexCStepAdditions\"\n");
   fprintf(pFile, "%%FLG: SData = 2097152\n");
   // Lib Path & Def Param
   fprintf(pFile, "\n[SF.Seq[5].Main[%i].TS.SData.Call]\n", iStepIndex);
   fprintf(pFile, "LibPath = \"ts_support_32.dll\"\n");
   fprintf(pFile, "Func = \"tss_SetTextforInitPanel\"\n");
   fprintf(pFile, "%%LO: Parms = [0]\n");
   fprintf(pFile, "%%HI: Parms = [6]\n");
   // FCParameter
   fprintf(pFile, "\n[DEF, SF.Seq[5].Main[%i].TS.SData.Call.Parms]\n", iStepIndex);
   fprintf(pFile, "%%[0] = \"TYPE, FCParameter\"\n");
   fprintf(pFile, "%%[1] = \"TYPE, FCParameter\"\n");
   fprintf(pFile, "%%[2] = \"TYPE, FCParameter\"\n");
   fprintf(pFile, "%%[3] = \"TYPE, FCParameter\"\n");
   fprintf(pFile, "%%[4] = \"TYPE, FCParameter\"\n");
   fprintf(pFile, "%%[5] = \"TYPE, FCParameter\"\n");
   fprintf(pFile, "%%[6] = \"TYPE, FCParameter\"\n");
   // Return Value
   fprintf(pFile, "\n[SF.Seq[5].Main[%i].TS.SData.Call.Parms[0]]\n", iStepIndex);
   fprintf(pFile, "Name = \"Return Value\"\n");
   fprintf(pFile, "Type = 3\n");
   // sequenceContext
   fprintf(pFile, "\n[SF.Seq[5].Main[%i].TS.SData.Call.Parms[1]]\n", iStepIndex);
   fprintf(pFile, "Name = \"sequenceContext\"\n");
   fprintf(pFile, "Type = 4\n");
   fprintf(pFile, "ObjType = 1\n");
   fprintf(pFile, "ArgVal = \"ThisContext\"\n");
   // Text
   fprintf(pFile, "\n[SF.Seq[5].Main[%i].TS.SData.Call.Parms[2]]\n", iStepIndex);
   fprintf(pFile, "Name = \"text\"\n");
   fprintf(pFile, "Type = 2\n");
   fprintf(pFile, "StrPass = 2\n");
   fprintf(pFile, "ArgVal = \"\\\"Resource-Manager\\\"\"\n");
   // alwaysOntop
   fprintf(pFile, "\n[SF.Seq[5].Main[%i].TS.SData.Call.Parms[3]]\n", iStepIndex);
   fprintf(pFile, "Name = \"alwaysOntop\"\n");
   fprintf(pFile, "ArgVal = \"True\"\n");
   // errorOccurred
   fprintf(pFile, "\n[SF.Seq[5].Main[%i].TS.SData.Call.Parms[4]]\n", iStepIndex);
   fprintf(pFile, "Name = \"errorOccurred\"\n");
   fprintf(pFile, "NumType = 2\n");
   fprintf(pFile, "NumPass = 1\n");
   fprintf(pFile, "ArgVal = \"Step.Result.Error.Occurred\"\n");
   // errorCode
   fprintf(pFile, "\n[SF.Seq[5].Main[%i].TS.SData.Call.Parms[5]]\n", iStepIndex);
   fprintf(pFile, "Name = \"errorCode\"\n");
   fprintf(pFile, "NumPass = 1\n");
   fprintf(pFile, "ArgVal = \"Step.Result.Error.Code\"\n");
   // errorMessage
   fprintf(pFile, "\n[SF.Seq[5].Main[%i].TS.SData.Call.Parms[6]]\n", iStepIndex);
   fprintf(pFile, "Name = \"errorMessage\"\n");
   fprintf(pFile, "Type = 2\n");
   fprintf(pFile, "StrPass = 2\n");
   fprintf(pFile, "ArgVal = \"Step.Result.Error.Msg\"\n");
   // Step-Name
   fprintf(pFile, "\n[DEF, SF.Seq[5].Main[%i]]\n", iStepIndex);
   fprintf(pFile, "%%NAME = \"Text aktualisieren\"\n");
   // next step!
   iStepIndex++;

   // SEQ 5 == [-7-] == LOAD RESOURCE MANAGER

   // Adapter
   fprintf(pFile, "\n[SF.Seq[5].Main[%i].TS]\n", iStepIndex);
   fprintf(pFile, "Adapter = \"DLL Flexible Prototype Adapter\"\n");
   // SData
   fprintf(pFile, "\n[DEF, SF.Seq[5].Main[%i].TS]\n", iStepIndex);
   fprintf(pFile, "SData = \"TYPE, FlexCStepAdditions\"\n");
   fprintf(pFile, "%%FLG: SData = 2097152\n");
   // Lib Path & Def Param
   fprintf(pFile, "\n[SF.Seq[5].Main[%i].TS.SData.Call]\n", iStepIndex);
   fprintf(pFile, "LibPath = \"resmgr.dll\"\n");
   fprintf(pFile, "Func = \"RESMGR_Setup\"\n");
   fprintf(pFile, "%%LO: Parms = [0]\n");
   fprintf(pFile, "%%HI: Parms = [6]\n");
   // FCParameter
   fprintf(pFile, "\n[DEF, SF.Seq[5].Main[%i].TS.SData.Call.Parms]\n", iStepIndex);
   fprintf(pFile, "%%[0] = \"TYPE, FCParameter\"\n");
   fprintf(pFile, "%%[1] = \"TYPE, FCParameter\"\n");
   fprintf(pFile, "%%[2] = \"TYPE, FCParameter\"\n");
   fprintf(pFile, "%%[3] = \"TYPE, FCParameter\"\n");
   fprintf(pFile, "%%[4] = \"TYPE, FCParameter\"\n");
   fprintf(pFile, "%%[5] = \"TYPE, FCParameter\"\n");
   fprintf(pFile, "%%[6] = \"TYPE, FCParameter\"\n");
   // Return Values
   fprintf(pFile, "\n[SF.Seq[5].Main[%i].TS.SData.Call.Parms[0]]\n", iStepIndex);
   fprintf(pFile, "Name = \"Return Value\"\n");
   fprintf(pFile, "Type = 3\n");
   // sequenceContext
   fprintf(pFile, "\n[SF.Seq[5].Main[%i].TS.SData.Call.Parms[1]]\n", iStepIndex);
   fprintf(pFile, "Name = \"sequenceContext\"\n");
   fprintf(pFile, "Type = 4\n");
   fprintf(pFile, "ObjType = 1\n");
   fprintf(pFile, "ArgVal = \"ThisContext\"\n");
   // PhyIni Name
   fprintf(pFile, "\n[SF.Seq[5].Main[%i].TS.SData.Call.Parms[2]]\n", iStepIndex);
   fprintf(pFile, "Name = \"physicalIniFileName\"\n");
   fprintf(pFile, "Type = 2\n");
   fprintf(pFile, "ArgVal = \"StationGlobals.TSVP.PhysicalIniFile\"\n");
   // AppIni Name
   fprintf(pFile, "\n[SF.Seq[5].Main[%i].TS.SData.Call.Parms[3]]\n", iStepIndex);
   fprintf(pFile, "Name = \"applicationIniFileName\"\n");
   fprintf(pFile, "Type = 2\n");
   fprintf(pFile, "ArgVal = \"StationGlobals.TSVP.ApplicationIniFile\"\n");
   // errorOccurred
   fprintf(pFile, "\n[SF.Seq[5].Main[%i].TS.SData.Call.Parms[4]]\n", iStepIndex);
   fprintf(pFile, "Name = \"errorOccurred\"\n");
   fprintf(pFile, "NumType = 2\n");
   fprintf(pFile, "NumPass = 1\n");
   fprintf(pFile, "ArgVal = \"Step.Result.Error.Occurred\"\n");
   // errorCode
   fprintf(pFile, "\n[SF.Seq[5].Main[%i].TS.SData.Call.Parms[5]]\n", iStepIndex);
   fprintf(pFile, "Name = \"errorCode\"\n");
   fprintf(pFile, "NumPass = 1\n");
   fprintf(pFile, "ArgVal = \"Step.Result.Error.Code\"\n");
   // errorMessage
   fprintf(pFile, "\n[SF.Seq[5].Main[%i].TS.SData.Call.Parms[6]]\n", iStepIndex);
   fprintf(pFile, "Name = \"errorMessage\"\n");
   fprintf(pFile, "Type = 2\n");
   fprintf(pFile, "StrPass = 2\n");
   fprintf(pFile, "ArgVal = \"Step.Result.Error.Msg\"\n");
   // Step-Name
   fprintf(pFile, "\n[DEF, SF.Seq[5].Main[%i]]\n", iStepIndex);
   fprintf(pFile, "%%NAME = \"Resource-Manager laden\"\n");
   // next step!
   iStepIndex++;

   // I N T I T I A L I Z A T I O N   O F   D E V I C E S
   for (i = 0; i <= (iSpecDev - iPHDTchecked - iPIO2checked); i++)
   // without phdt & pio2, because they need extra init.
   {
      // SELECT DEVICE
      if (!i)
      {
         sprintf(cFullName, "Switch-Manager");
         sprintf(cAKA, "swmgr");
         sprintf(cSetupName, "SWMGR");
         // SELECT BENCH
         k = 1; // in bench 1
         n = 0; // there is only one switch mgr
      }
      else if (iPSAMchecked > 0)
      {
         sprintf(cFullName, "Digitalmultimeter");
         sprintf(cAKA, "dmm");
         sprintf(cSetupName, "DMM");
         // SELECT BENCH
         k = iDevCountBuffer[0] + 1-iPSAMchecked;
         /******************************************************/
         /*** iDevCountBuffer is no. of all dev of this type ***/
         /*** iXXXchecked is the no. of the current dev      ***/
         /*** k is the no. of the current bench			  ***/
         /*** i.e.: if iXXXchecked == 4 then k = 1			  ***/
         /***       if iXXXchecked == 3 then k = 2		      ***/
         /***       if iXXXchecked == 2 then k = 3			  ***/
         /***       if iXXXchecked == 1 then k = 4			  ***/
         /******************************************************/
         if (iDevCountBuffer[0] > 1)
         // only if there are more dev of same type
         {
            n = k; // no. of current dev for displayed text
         }
         else
         {
            n = 0;
         }
         iPSAMchecked--;
      }
      else if (iPAMchecked > 0)
      {
         sprintf(cFullName, "Signalanalysator");
         sprintf(cAKA, "siganl");
         sprintf(cSetupName, "SIGANL");
         // SELECT BENCH (explanation see above)
         k = iDevCountBuffer[1] + 1-iPAMchecked;
         if (iDevCountBuffer[1] > 1)
         // only if there are more dev of same type
         {
            n = k; // no. of current dev for displayed text
         }
         else
         {
            n = 0;
         }
         iPAMchecked--;
      }
      else if (iPFGchecked > 0)
      {
         sprintf(cFullName, "Funktionsgenerator");
         sprintf(cAKA, "funcgen");
         sprintf(cSetupName, "FUNCGEN");
         // SELECT BENCH (explanation see above)
         k = iDevCountBuffer[2] + 1-iPFGchecked;
         if (iDevCountBuffer[2] > 1)
         // only if there are more dev of same type
         {
            n = k; // no. of current dev for displayed text
         }
         else
         {
            n = 0;
         }
         iPFGchecked--;
      }
      else if (iPDFTchecked > 0)
      {
         sprintf(cFullName, "Digital-IO-Manager");
         sprintf(cAKA, "diomgr");
         sprintf(cSetupName, "DIOMGR");
         // SELECT BENCH
         k = 1; // every dev of this type in first bench
         n = 0; // initialize only one time, even for multiple dev
         iPDFTchecked = 0;
      }
      else if (iPICTchecked > 0)
      {
         sprintf(cFullName, "ICT Erweiterungsmodul");
         sprintf(cAKA, "ict");
         sprintf(cSetupName, "ICT");
         // SELECT BENCH
         k = 1; // multiple dev dont make sense
         n = 0; // initialize only one time
         iPICTchecked = 0;
      }
      else if (iPSUchecked > 0)
      {
         sprintf(cFullName, "DC-Stromversorgungs-Module");
         sprintf(cAKA, "dcpwr");
         sprintf(cSetupName, "DCPWR");
         // SELECT BENCH (explanation see above)
         k = 1; // every dev of this type in first bench
         n = 0; // initialize only one time, even for multiple dev
         iPSUchecked = 0;
      }


      // WRITE INTITIALIZATION

      // SEQ 5 == [-8-] == SET TEXT FOR INIT PANEL

      // Adapter
      fprintf(pFile, "\n[SF.Seq[5].Main[%i].TS]\n", iStepIndex);
      fprintf(pFile, "Adapter = \"DLL Flexible Prototype Adapter\"\n");
      // SData
      fprintf(pFile, "\n[DEF, SF.Seq[5].Main[%i].TS]\n", iStepIndex);
      fprintf(pFile, "SData = \"TYPE, FlexCStepAdditions\"\n");
      fprintf(pFile, "%%FLG: SData = 2097152\n");
      // LibPath & Params Def
      fprintf(pFile, "\n[SF.Seq[5].Main[%i].TS.SData.Call]\n", iStepIndex);
      fprintf(pFile, "LibPath = \"ts_support_32.dll\"\n");
      fprintf(pFile, "Func = \"tss_SetTextforInitPanel\"\n");
      fprintf(pFile, "%%LO: Parms = [0]\n");
      fprintf(pFile, "%%HI: Parms = [6]\n");
      // FCParameters
      fprintf(pFile, "\n[DEF, SF.Seq[5].Main[%i].TS.SData.Call.Parms]\n", iStepIndex);
      fprintf(pFile, "%%[0] = \"TYPE, FCParameter\"\n");
      fprintf(pFile, "%%[1] = \"TYPE, FCParameter\"\n");
      fprintf(pFile, "%%[2] = \"TYPE, FCParameter\"\n");
      fprintf(pFile, "%%[3] = \"TYPE, FCParameter\"\n");
      fprintf(pFile, "%%[4] = \"TYPE, FCParameter\"\n");
      fprintf(pFile, "%%[5] = \"TYPE, FCParameter\"\n");
      fprintf(pFile, "%%[6] = \"TYPE, FCParameter\"\n");
      //Return Value
      fprintf(pFile, "\n[SF.Seq[5].Main[%i].TS.SData.Call.Parms[0]]\n", iStepIndex);
      fprintf(pFile, "Name = \"Return Value\"\n");
      fprintf(pFile, "Type = 3\n");
      // sequenceContext
      fprintf(pFile, "\n[SF.Seq[5].Main[%i].TS.SData.Call.Parms[1]]\n", iStepIndex);
      fprintf(pFile, "Name = \"sequenceContext\"\n");
      fprintf(pFile, "Type = 4\n");
      fprintf(pFile, "ObjType = 1\n");
      fprintf(pFile, "ArgVal = \"ThisContext\"\n");
      // Text
      fprintf(pFile, "\n[SF.Seq[5].Main[%i].TS.SData.Call.Parms[2]]\n", iStepIndex);
      fprintf(pFile, "Name = \"text\"\n");
      fprintf(pFile, "Type = 2\n");
      fprintf(pFile, "StrPass = 2\n");
      if (n > 0)
      {
         fprintf(pFile, "ArgVal = \"\\\"%s %i\\\"\"\n", cFullName, n); // Full name with no.  i.e. "Digitalmulitmeter 3"
      }
      else
      {
         fprintf(pFile, "ArgVal = \"\\\"%s\\\"\"\n", cFullName); // Full name of the device without number
      }
      // alwaysOntop
      fprintf(pFile, "\n[SF.Seq[5].Main[%i].TS.SData.Call.Parms[3]]\n", iStepIndex);
      fprintf(pFile, "Name = \"alwaysOntop\"\n");
      fprintf(pFile, "ArgVal = \"True\"\n");
      // errorOccured
      fprintf(pFile, "\n[SF.Seq[5].Main[%i].TS.SData.Call.Parms[4]]\n", iStepIndex);
      fprintf(pFile, "Name = \"errorOccurred\"\n");
      fprintf(pFile, "NumType = 2\n");
      fprintf(pFile, "NumPass = 1\n");
      fprintf(pFile, "ArgVal = \"Step.Result.Error.Occurred\"\n");
      // errorCode
      fprintf(pFile, "\n[SF.Seq[5].Main[%i].TS.SData.Call.Parms[5]]\n", iStepIndex);
      fprintf(pFile, "Name = \"errorCode\"\n");
      fprintf(pFile, "NumPass = 1\n");
      fprintf(pFile, "ArgVal = \"Step.Result.Error.Code\"\n");
      // errorMessage
      fprintf(pFile, "\n[SF.Seq[5].Main[%i].TS.SData.Call.Parms[6]]\n", iStepIndex);
      fprintf(pFile, "Name = \"errorMessage\"\n");
      fprintf(pFile, "Type = 2\n");
      fprintf(pFile, "StrPass = 2\n");
      fprintf(pFile, "ArgVal = \"Step.Result.Error.Msg\"\n");
      // Step-Name
      fprintf(pFile, "\n[DEF, SF.Seq[5].Main[%i]]\n", iStepIndex);
      fprintf(pFile, "%%NAME = \"Text aktualisieren\"\n");
      // next step!
      iStepIndex++;

      // SEQ 5 == [-9-] == INITIALIZE DEVICES

      // Adapter
      fprintf(pFile, "\n[SF.Seq[5].Main[%i].TS]\n", iStepIndex);
      fprintf(pFile, "Adapter = \"DLL Flexible Prototype Adapter\"\n");
      // SData 			
      fprintf(pFile, "\n[DEF, SF.Seq[5].Main[%i].TS]\n", iStepIndex);
      fprintf(pFile, "SData = \"TYPE, FlexCStepAdditions\"\n");
      fprintf(pFile, "%%FLG: SData = 2097152\n");
      // LibPath & Params Def
      fprintf(pFile, "\n[SF.Seq[5].Main[%i].TS.SData.Call]\n", iStepIndex);
      fprintf(pFile, "LibPath = \"%s.dll\"\n", cAKA); // Dll name i.e. "dmm.dll"
      fprintf(pFile, "Func = \"%s_Setup\"\n", cSetupName); // Setup name i.e. "DMM_Setup"
      fprintf(pFile, "%%LO: Parms = [0]\n");
      fprintf(pFile, "%%HI: Parms = [6]\n");
      // FCParameters			
      fprintf(pFile, "\n[DEF, SF.Seq[5].Main[%i].TS.SData.Call.Parms]\n", iStepIndex);
      fprintf(pFile, "%%[0] = \"TYPE, FCParameter\"\n");
      fprintf(pFile, "%%[1] = \"TYPE, FCParameter\"\n");
      fprintf(pFile, "%%[2] = \"TYPE, FCParameter\"\n");
      fprintf(pFile, "%%[3] = \"TYPE, FCParameter\"\n");
      fprintf(pFile, "%%[4] = \"TYPE, FCParameter\"\n");
      fprintf(pFile, "%%[5] = \"TYPE, FCParameter\"\n");
      fprintf(pFile, "%%[6] = \"TYPE, FCParameter\"\n");
      // Return Value
      fprintf(pFile, "\n[SF.Seq[5].Main[%i].TS.SData.Call.Parms[0]]\n", iStepIndex);
      fprintf(pFile, "Name = \"Return Value\"\n");
      fprintf(pFile, "Type = 3\n");
      // sequenceContext				
      fprintf(pFile, "\n[SF.Seq[5].Main[%i].TS.SData.Call.Parms[1]]\n", iStepIndex);
      fprintf(pFile, "Name = \"sequenceContext\"\n");
      fprintf(pFile, "Type = 4\n");
      fprintf(pFile, "ObjType = 1\n");
      fprintf(pFile, "ArgVal = \"ThisContext\"\n");
      // Bench Name
      fprintf(pFile, "\n[SF.Seq[5].Main[%i].TS.SData.Call.Parms[2]]\n", iStepIndex);
      fprintf(pFile, "Name = \"benchName\"\n");
      fprintf(pFile, "Type = 2\n");
      fprintf(pFile, "ArgVal = \"StationGlobals.TSVP.BenchName%i\"\n", k); // Bench Var + No.		
      // resourceID
      fprintf(pFile, "\n[SF.Seq[5].Main[%i].TS.SData.Call.Parms[3]]\n", iStepIndex);
      fprintf(pFile, "Name = \"resourceID\"\n");
      fprintf(pFile, "NumPass = 1\n");
      if (n > 0)
      // device ID for Station Globals
      {
         fprintf(pFile, "ArgVal = \"StationGlobals.TSVP.%s_%i_ID\"\n", cAKA, n);
      }
      else
      {
         fprintf(pFile, "ArgVal = \"StationGlobals.TSVP.%s_ID\"\n", cAKA);
      }
      // errorOccurred
      fprintf(pFile, "\n[SF.Seq[5].Main[%i].TS.SData.Call.Parms[4]]\n", iStepIndex);
      fprintf(pFile, "Name = \"errorOccurred\"\n");
      fprintf(pFile, "NumType = 2\n");
      fprintf(pFile, "NumPass = 1\n");
      fprintf(pFile, "ArgVal = \"Step.Result.Error.Occurred\"\n");
      // errorCode
      fprintf(pFile, "\n[SF.Seq[5].Main[%i].TS.SData.Call.Parms[5]]\n", iStepIndex);
      fprintf(pFile, "Name = \"errorCode\"\n");
      fprintf(pFile, "NumPass = 1\n");
      fprintf(pFile, "ArgVal = \"Step.Result.Error.Code\"\n");
      // errorMessage
      fprintf(pFile, "\n[SF.Seq[5].Main[%i].TS.SData.Call.Parms[6]]\n", iStepIndex);
      fprintf(pFile, "Name = \"errorMessage\"\n");
      fprintf(pFile, "Type = 2\n");
      fprintf(pFile, "StrPass = 2\n");
      fprintf(pFile, "ArgVal = \"Step.Result.Error.Msg\"\n");
      // fprintf(pFile, "[SF.Seq[5].Main[0]] %%COMMENT = \"Here one could add a comment which would be displayed in teststand next to each step\"
      // Step-Name
      fprintf(pFile, "\n[DEF, SF.Seq[5].Main[%i]]\n", iStepIndex);
      if (n > 0)
      {
         fprintf(pFile, "%%NAME = \"%s %i initialisieren\"\n", cFullName, n); // Full name with no.  i.e. "Digitalmulitmeter 3"
      }
      else
      {
         fprintf(pFile, "%%NAME = \"%s initialisieren\"\n", cFullName); // Full name of the device without number
      }
      // next step!
      iStepIndex++;
   }

   // restore the original device quantity.
   iPSAMchecked = iDevCountBuffer[0];
   iPAMchecked = iDevCountBuffer[1];
   iPFGchecked = iDevCountBuffer[2];
   iPDFTchecked = iDevCountBuffer[3];
   iPICTchecked = iDevCountBuffer[5];
   iPSUchecked = iDevCountBuffer[7];


   // INITIALIZE PHDT & PIO2 DEVICES

   if (iPHDTchecked || iPIO2checked)
   {
      // SELECT DEVICE
      for (i = 0; i <= (iPHDTchecked + iPIO2checked); i++)
      {

         if (iPHDTchecked > 0)
         {
            sprintf(cFullName, "High-Speed Digitaltest-Modul");
            sprintf(cAKA, "phdt");
            sprintf(cSetupName, "PHDT");
            // SELECT BENCH (explanation see above)
            k = iDevCountBuffer[4] + 1-iPHDTchecked;
            if (iDevCountBuffer[4] > 1)
            // only if there are more dev of same type
            {
               n = k; // no. of current dev for displayed text
            }
            else
            {
               n = 0;
            }
            iPHDTchecked--;
         }
         else if (iPIO2checked > 0)
         {
            sprintf(cFullName, "Analog/Digital-IO-Modul");
            sprintf(cAKA, "pio2");
            sprintf(cSetupName, "PIO2");
            // SELECT BENCH (explanation see above)
            k = iDevCountBuffer[6] + 1-iPIO2checked;
            if (iDevCountBuffer[6] > 1)
            // only if there are more dev of same type
            {
               n = k; // no. of current dev for displayed text
            }
            else
            {
               n = 0;
            }
            iPIO2checked--;
         }

         // WRITE INTITIALIZATION

         // SEQ 5 == [-10-] == SET TEXT FOR INIT PANEL

         // Adapter
         fprintf(pFile, "\n[SF.Seq[5].Main[%i].TS]\n", iStepIndex);
         fprintf(pFile, "Adapter = \"DLL Flexible Prototype Adapter\"\n");
         // SData
         fprintf(pFile, "\n[DEF, SF.Seq[5].Main[%i].TS]\n", iStepIndex);
         fprintf(pFile, "SData = \"TYPE, FlexCStepAdditions\"\n");
         fprintf(pFile, "%%FLG: SData = 2097152\n");
         // LibPath & Params Def
         fprintf(pFile, "\n[SF.Seq[5].Main[%i].TS.SData.Call]\n", iStepIndex);
         fprintf(pFile, "LibPath = \"ts_support_32.dll\"\n");
         fprintf(pFile, "Func = \"tss_SetTextforInitPanel\"\n");
         fprintf(pFile, "%%LO: Parms = [0]\n");
         fprintf(pFile, "%%HI: Parms = [6]\n");
         // FCParameters
         fprintf(pFile, "\n[DEF, SF.Seq[5].Main[%i].TS.SData.Call.Parms]\n", iStepIndex);
         fprintf(pFile, "%%[0] = \"TYPE, FCParameter\"\n");
         fprintf(pFile, "%%[1] = \"TYPE, FCParameter\"\n");
         fprintf(pFile, "%%[2] = \"TYPE, FCParameter\"\n");
         fprintf(pFile, "%%[3] = \"TYPE, FCParameter\"\n");
         fprintf(pFile, "%%[4] = \"TYPE, FCParameter\"\n");
         fprintf(pFile, "%%[5] = \"TYPE, FCParameter\"\n");
         fprintf(pFile, "%%[6] = \"TYPE, FCParameter\"\n");
         //Return Value
         fprintf(pFile, "\n[SF.Seq[5].Main[%i].TS.SData.Call.Parms[0]]\n", iStepIndex);
         fprintf(pFile, "Name = \"Return Value\"\n");
         fprintf(pFile, "Type = 3\n");
         // sequenceContext
         fprintf(pFile, "\n[SF.Seq[5].Main[%i].TS.SData.Call.Parms[1]]\n", iStepIndex);
         fprintf(pFile, "Name = \"sequenceContext\"\n");
         fprintf(pFile, "Type = 4\n");
         fprintf(pFile, "ObjType = 1\n");
         fprintf(pFile, "ArgVal = \"ThisContext\"\n");
         // Text
         fprintf(pFile, "\n[SF.Seq[5].Main[%i].TS.SData.Call.Parms[2]]\n", iStepIndex);
         fprintf(pFile, "Name = \"text\"\n");
         fprintf(pFile, "Type = 2\n");
         fprintf(pFile, "StrPass = 2\n");
         if (n > 0)
         {
            fprintf(pFile, "ArgVal = \"\\\"%s %i\\\"\"\n", cFullName, n); // Full name with no.  i.e. "High-Speed Digitaltest-Modul 3"
         }
         else
         {
            fprintf(pFile, "ArgVal = \"\\\"%s\\\"\"\n", cFullName); // Full name of the device without number
         }
         // alwaysOntop
         fprintf(pFile, "\n[SF.Seq[5].Main[%i].TS.SData.Call.Parms[3]]\n", iStepIndex);
         fprintf(pFile, "Name = \"alwaysOntop\"\n");
         fprintf(pFile, "ArgVal = \"True\"\n");
         // errorOccured
         fprintf(pFile, "\n[SF.Seq[5].Main[%i].TS.SData.Call.Parms[4]]\n", iStepIndex);
         fprintf(pFile, "Name = \"errorOccurred\"\n");
         fprintf(pFile, "NumType = 2\n");
         fprintf(pFile, "NumPass = 1\n");
         fprintf(pFile, "ArgVal = \"Step.Result.Error.Occurred\"\n");
         // errorCode
         fprintf(pFile, "\n[SF.Seq[5].Main[%i].TS.SData.Call.Parms[5]]\n", iStepIndex);
         fprintf(pFile, "Name = \"errorCode\"\n");
         fprintf(pFile, "NumPass = 1\n");
         fprintf(pFile, "ArgVal = \"Step.Result.Error.Code\"\n");
         // errorMessage
         fprintf(pFile, "\n[SF.Seq[5].Main[%i].TS.SData.Call.Parms[6]]\n", iStepIndex);
         fprintf(pFile, "Name = \"errorMessage\"\n");
         fprintf(pFile, "Type = 2\n");
         fprintf(pFile, "StrPass = 2\n");
         fprintf(pFile, "ArgVal = \"Step.Result.Error.Msg\"\n");
         // Step-Name
         fprintf(pFile, "\n[DEF, SF.Seq[5].Main[%i]]\n", iStepIndex);
         fprintf(pFile, "%%NAME = \"Text aktualisieren\"\n");
         // next step!
         iStepIndex++;

         // SEQ 5 == [-11-] == INITIALIZE DEVICES

         // Adapter 	
         fprintf(pFile, "\n[SF.Seq[5].Main[%i].TS]\n", iStepIndex);
         fprintf(pFile, "Adapter = \"Sequence Adapter\"\n");
         // SData
         fprintf(pFile, "\n[DEF, SF.Seq[5].Main[%i].TS]\n", iStepIndex);
         fprintf(pFile, "SData = \"TYPE, SeqCallStepAdditions\"\n");
         fprintf(pFile, "%%FLG: SData = 2097152\n");
         // SFPath & SeqName
         fprintf(pFile, "\n[SF.Seq[5].Main[%i].TS.SData]\n", iStepIndex);
         fprintf(pFile, "SFPath = \"TS_%s_Bibliothek.seq\"\n", cSetupName); // i.e.: "PHDT"
         fprintf(pFile, "SeqName = \"Setup\"\n");
         // Actual Arguments
         fprintf(pFile, "\n[DEF, SF.Seq[5].Main[%i].TS.SData]\n", iStepIndex);
         fprintf(pFile, "ActualArgs = Arguments\n");
         fprintf(pFile, "%%FLG: ActualArgs = 2097152\n");
         // Sequence Arguments
         fprintf(pFile, "\n[DEF, SF.Seq[5].Main[%i].TS.SData.ActualArgs]\n", iStepIndex);
         fprintf(pFile, "arg0 = \"TYPE, SequenceArgument\"\n");
         fprintf(pFile, "arg1 = \"TYPE, SequenceArgument\"\n");
         // Device
         fprintf(pFile, "\n[SF.Seq[5].Main[%i].TS.SData.ActualArgs.arg0]\n", iStepIndex);
         fprintf(pFile, "UseDef = False\n");
         fprintf(pFile, "Expr = \"\\\"device->%s\\\"\"\n", cAKA); // i.e.: "phdt"
         // resourceID
         fprintf(pFile, "\n[SF.Seq[5].Main[%i].TS.SData.ActualArgs.arg1]\n", iStepIndex);
         fprintf(pFile, "UseDef = False\n");
         fprintf(pFile, "Expr = \"StationGlobals.TSVP.rs%s_ID\"\n", cAKA); // i.e.: "phdt" 	
         // Step-Name
         fprintf(pFile, "\n[DEF, SF.Seq[5].Main[%i]]\n", iStepIndex);
         if (n > 0)
         {
            fprintf(pFile, "%%NAME = \"%s %i initialisieren\"\n", cSetupName, n); // Full name with no.  i.e. "High-Speed Digitaltest-Modul 3"
         }
         else
         {
            fprintf(pFile, "%%NAME = \"%s initialisieren\"\n", cSetupName); // Full name of the device without number
         }
         // next step!
         iStepIndex++;
      }

      // restore the original device quantity.
      iPHDTchecked = iDevCountBuffer[4];
      iPIO2checked = iDevCountBuffer[6];
   }


   // INITIALIZE USER INTERFACE

   // SEQ 5 == [-12-] == SET TEXT FOR INIT PANEL

   // Adapter
   fprintf(pFile, "\n[SF.Seq[5].Main[%i].TS]\n", iStepIndex);
   fprintf(pFile, "Adapter = \"DLL Flexible Prototype Adapter\"\n");
   // SData
   fprintf(pFile, "\n[DEF, SF.Seq[5].Main[%i].TS]\n", iStepIndex);
   fprintf(pFile, "SData = \"TYPE, FlexCStepAdditions\"\n");
   fprintf(pFile, "%%FLG: SData = 2097152\n");
   // LibPath & Params Def
   fprintf(pFile, "\n[SF.Seq[5].Main[%i].TS.SData.Call]\n", iStepIndex);
   fprintf(pFile, "LibPath = \"ts_support_32.dll\"\n");
   fprintf(pFile, "Func = \"tss_SetTextforInitPanel\"\n");
   fprintf(pFile, "%%LO: Parms = [0]\n");
   fprintf(pFile, "%%HI: Parms = [6]\n");
   // FCParameters
   fprintf(pFile, "\n[DEF, SF.Seq[5].Main[%i].TS.SData.Call.Parms]\n", iStepIndex);
   fprintf(pFile, "%%[0] = \"TYPE, FCParameter\"\n");
   fprintf(pFile, "%%[1] = \"TYPE, FCParameter\"\n");
   fprintf(pFile, "%%[2] = \"TYPE, FCParameter\"\n");
   fprintf(pFile, "%%[3] = \"TYPE, FCParameter\"\n");
   fprintf(pFile, "%%[4] = \"TYPE, FCParameter\"\n");
   fprintf(pFile, "%%[5] = \"TYPE, FCParameter\"\n");
   fprintf(pFile, "%%[6] = \"TYPE, FCParameter\"\n");
   //Return Value
   fprintf(pFile, "\n[SF.Seq[5].Main[%i].TS.SData.Call.Parms[0]]\n", iStepIndex);
   fprintf(pFile, "Name = \"Return Value\"\n");
   fprintf(pFile, "Type = 3\n");
   // sequenceContext
   fprintf(pFile, "\n[SF.Seq[5].Main[%i].TS.SData.Call.Parms[1]]\n", iStepIndex);
   fprintf(pFile, "Name = \"sequenceContext\"\n");
   fprintf(pFile, "Type = 4\n");
   fprintf(pFile, "ObjType = 1\n");
   fprintf(pFile, "ArgVal = \"ThisContext\"\n");
   // Text
   fprintf(pFile, "\n[SF.Seq[5].Main[%i].TS.SData.Call.Parms[2]]\n", iStepIndex);
   fprintf(pFile, "Name = \"text\"\n");
   fprintf(pFile, "Type = 2\n");
   fprintf(pFile, "StrPass = 2\n");
   fprintf(pFile, "ArgVal = \"\\\"Benutzeroberfläche\\\"\"\n"); // name to display: userinterface
   // alwaysOntop
   fprintf(pFile, "\n[SF.Seq[5].Main[%i].TS.SData.Call.Parms[3]]\n", iStepIndex);
   fprintf(pFile, "Name = \"alwaysOntop\"\n");
   fprintf(pFile, "ArgVal = \"True\"\n");
   // errorOccured
   fprintf(pFile, "\n[SF.Seq[5].Main[%i].TS.SData.Call.Parms[4]]\n", iStepIndex);
   fprintf(pFile, "Name = \"errorOccurred\"\n");
   fprintf(pFile, "NumType = 2\n");
   fprintf(pFile, "NumPass = 1\n");
   fprintf(pFile, "ArgVal = \"Step.Result.Error.Occurred\"\n");
   // errorCode
   fprintf(pFile, "\n[SF.Seq[5].Main[%i].TS.SData.Call.Parms[5]]\n", iStepIndex);
   fprintf(pFile, "Name = \"errorCode\"\n");
   fprintf(pFile, "NumPass = 1\n");
   fprintf(pFile, "ArgVal = \"Step.Result.Error.Code\"\n");
   // errorMessage
   fprintf(pFile, "\n[SF.Seq[5].Main[%i].TS.SData.Call.Parms[6]]\n", iStepIndex);
   fprintf(pFile, "Name = \"errorMessage\"\n");
   fprintf(pFile, "Type = 2\n");
   fprintf(pFile, "StrPass = 2\n");
   fprintf(pFile, "ArgVal = \"Step.Result.Error.Msg\"\n");
   // Step-Name
   fprintf(pFile, "\n[DEF, SF.Seq[5].Main[%i]]\n", iStepIndex);
   fprintf(pFile, "%%NAME = \"Text aktualisieren\"\n");
   // next step!
   iStepIndex++;

   // SEQ 5 == [-13-] == INITIALIZE INTERFACE

   // Adapter
   fprintf(pFile, "\n[SF.Seq[5].Main[%i].TS]\n", iStepIndex);
   fprintf(pFile, "Adapter = \"DLL Flexible Prototype Adapter\"\n");
   // SData 			
   fprintf(pFile, "\n[DEF, SF.Seq[5].Main[%i].TS]\n", iStepIndex);
   fprintf(pFile, "SData = \"TYPE, FlexCStepAdditions\"\n");
   fprintf(pFile, "%%FLG: SData = 2097152\n");
   // LibPath & Params Def
   fprintf(pFile, "\n[SF.Seq[5].Main[%i].TS.SData.Call]\n", iStepIndex);
   fprintf(pFile, "LibPath = \"tspan.dll\"\n"); // Dll name
   fprintf(pFile, "Func = \"tspan_Setup\"\n"); // Setup name
   fprintf(pFile, "%%LO: Parms = [0]\n");
   fprintf(pFile, "%%HI: Parms = [6]\n");
   // FCParameters			
   fprintf(pFile, "\n[DEF, SF.Seq[5].Main[%i].TS.SData.Call.Parms]\n", iStepIndex);
   fprintf(pFile, "%%[0] = \"TYPE, FCParameter\"\n");
   fprintf(pFile, "%%[1] = \"TYPE, FCParameter\"\n");
   fprintf(pFile, "%%[2] = \"TYPE, FCParameter\"\n");
   fprintf(pFile, "%%[3] = \"TYPE, FCParameter\"\n");
   fprintf(pFile, "%%[4] = \"TYPE, FCParameter\"\n");
   fprintf(pFile, "%%[5] = \"TYPE, FCParameter\"\n");
   fprintf(pFile, "%%[6] = \"TYPE, FCParameter\"\n");
   // Return Value
   fprintf(pFile, "\n[SF.Seq[5].Main[%i].TS.SData.Call.Parms[0]]\n", iStepIndex);
   fprintf(pFile, "Name = \"Return Value\"\n");
   fprintf(pFile, "Type = 3\n");
   // sequenceContext				
   fprintf(pFile, "\n[SF.Seq[5].Main[%i].TS.SData.Call.Parms[1]]\n", iStepIndex);
   fprintf(pFile, "Name = \"sequenceContext\"\n");
   fprintf(pFile, "Type = 4\n");
   fprintf(pFile, "ObjType = 1\n");
   fprintf(pFile, "ArgVal = \"ThisContext\"\n");
   // Bench Name
   fprintf(pFile, "\n[SF.Seq[5].Main[%i].TS.SData.Call.Parms[2]]\n", iStepIndex);
   fprintf(pFile, "Name = \"benchName\"\n");
   fprintf(pFile, "Type = 2\n");
   fprintf(pFile, "ArgVal = \"StationGlobals.TSVP.BenchName1\"\n"); // Bench No.		
   // resourceID
   fprintf(pFile, "\n[SF.Seq[5].Main[%i].TS.SData.Call.Parms[3]]\n", iStepIndex);
   fprintf(pFile, "Name = \"resourceID\"\n");
   fprintf(pFile, "NumPass = 1\n");
   fprintf(pFile, "ArgVal = \"StationGlobals.TSVP.Panel_ID\"\n");
   // errorOccurred
   fprintf(pFile, "\n[SF.Seq[5].Main[%i].TS.SData.Call.Parms[4]]\n", iStepIndex);
   fprintf(pFile, "Name = \"errorOccurred\"\n");
   fprintf(pFile, "NumType = 2\n");
   fprintf(pFile, "NumPass = 1\n");
   fprintf(pFile, "ArgVal = \"Step.Result.Error.Occurred\"\n");
   // errorCode
   fprintf(pFile, "\n[SF.Seq[5].Main[%i].TS.SData.Call.Parms[5]]\n", iStepIndex);
   fprintf(pFile, "Name = \"errorCode\"\n");
   fprintf(pFile, "NumPass = 1\n");
   fprintf(pFile, "ArgVal = \"Step.Result.Error.Code\"\n");
   // errorMessage
   fprintf(pFile, "\n[SF.Seq[5].Main[%i].TS.SData.Call.Parms[6]]\n", iStepIndex);
   fprintf(pFile, "Name = \"errorMessage\"\n");
   fprintf(pFile, "Type = 2\n");
   fprintf(pFile, "StrPass = 2\n");
   fprintf(pFile, "ArgVal = \"Step.Result.Error.Msg\"\n");
   // fprintf(pFile, "[SF.Seq[5].Main[0]] %%COMMENT = \"Here one could add a comment which would be displayed in teststand next to each step\"
   // Step-Name
   fprintf(pFile, "\n[DEF, SF.Seq[5].Main[%i]]\n", iStepIndex);
   fprintf(pFile, "%%NAME = \"Benutzeroberfläche initialisieren\"\n"); // Stepname
   // next step!
   iStepIndex++;


   // SEQ == [-14-] == SET SEQUENCEFILELOADCOMPLETE

   fprintf(pFile, "\n[SF.Seq[5].Main[%i].TS]\n", iStepIndex);
   fprintf(pFile, "Adapter = \"None Adapter\"\n");
   fprintf(pFile, "PostExpr = \"StationGlobals.TSVP.SequenceFileLoadComplete = True\"\n");

   fprintf(pFile, "\n[DEF, SF.Seq[5].Main[%i].TS]\n", iStepIndex);
   fprintf(pFile, "SData = \"TYPE, NoneStepAdditions\"\n");
   fprintf(pFile, "%%FLG: SData = 2097152\n");

   fprintf(pFile, "\n[DEF, SF.Seq[5].Main[%i]]\n", iStepIndex);
   fprintf(pFile, "%%NAME = \"StationGlobal setzen\"\n");


   // SEQ 5 == CLOSE PANELS

   // Def
   fprintf(pFile, "\n[DEF, SF.Seq[5].Cleanup]\n");
   fprintf(pFile, "%%[0] = FlexCStep\n");
   fprintf(pFile, "%%TYPE: %%[0] = \"Action\"\n");
   fprintf(pFile, "%%[1] = FlexCStep\n");
   fprintf(pFile, "%%TYPE: %%[1] = \"Action\"\n");


   // SEQ 5 == [-15-] == CLOSE INIT PANEL

   // Adapter
   fprintf(pFile, "\n[SF.Seq[5].Cleanup[0].TS]\n");
   fprintf(pFile, "Adapter = \"DLL Flexible Prototype Adapter\"\n");
   // SData
   fprintf(pFile, "\n[DEF, SF.Seq[5].Cleanup[0].TS]\n");
   fprintf(pFile, "SData = \"TYPE, FlexCStepAdditions\"\n");
   fprintf(pFile, "%%FLG: SData = 2097152\n");
   // LibPath & Param Def
   fprintf(pFile, "\n[SF.Seq[5].Cleanup[0].TS.SData.Call]\n");
   fprintf(pFile, "LibPath = \"ts_support_32.dll\"\n");
   fprintf(pFile, "Func = \"tss_HideInitPanel\"\n");
   fprintf(pFile, "%%LO: Parms = [0]\n");
   fprintf(pFile, "%%HI: Parms = [4]\n");
   // FCParameters
   fprintf(pFile, "\n[DEF, SF.Seq[5].Cleanup[0].TS.SData.Call.Parms]\n");
   fprintf(pFile, "%%[0] = \"TYPE, FCParameter\"\n");
   fprintf(pFile, "%%[1] = \"TYPE, FCParameter\"\n");
   fprintf(pFile, "%%[2] = \"TYPE, FCParameter\"\n");
   fprintf(pFile, "%%[3] = \"TYPE, FCParameter\"\n");
   fprintf(pFile, "%%[4] = \"TYPE, FCParameter\"\n");
   // Return Value
   fprintf(pFile, "\n[SF.Seq[5].Cleanup[0].TS.SData.Call.Parms[0]]\n");
   fprintf(pFile, "Name = \"Return Value\"\n");
   fprintf(pFile, "Type = 3\n");
   // sequenceContext
   fprintf(pFile, "\n[SF.Seq[5].Cleanup[0].TS.SData.Call.Parms[1]]\n");
   fprintf(pFile, "Name = \"sequenceContext\"\n");
   fprintf(pFile, "Type = 4\n");
   fprintf(pFile, "ObjType = 1\n");
   fprintf(pFile, "ArgVal = \"ThisContext\"\n");
   // errorOccurred
   fprintf(pFile, "\n[SF.Seq[5].Cleanup[0].TS.SData.Call.Parms[2]]\n");
   fprintf(pFile, "Name = \"errorOccurred\"\n");
   fprintf(pFile, "NumType = 2\n");
   fprintf(pFile, "NumPass = 1\n");
   fprintf(pFile, "ArgVal = \"Step.Result.Error.Occurred\"\n");
   // errorCode//
   fprintf(pFile, "\n[SF.Seq[5].Cleanup[0].TS.SData.Call.Parms[3]]\n");
   fprintf(pFile, "Name = \"errorCode\"\n");
   fprintf(pFile, "NumPass = 1\n");
   fprintf(pFile, "ArgVal = \"Step.Result.Error.Code\"\n");
   // errorMessage
   fprintf(pFile, "\n[SF.Seq[5].Cleanup[0].TS.SData.Call.Parms[4]]\n");
   fprintf(pFile, "Name = \"errorMessage\"\n");
   fprintf(pFile, "Type = 2\n");
   fprintf(pFile, "StrPass = 2\n");
   fprintf(pFile, "ArgVal = \"Step.Result.Error.Msg\"\n");
   // Step-Name
   fprintf(pFile, "\n[DEF, SF.Seq[5].Cleanup[0]]\n");
   fprintf(pFile, "%%NAME = \"Init Panel schließen\"\n");


   // SEQ 5 == [-16-] == CLOSE DEBUG PANEL

   // Adapter
   fprintf(pFile, "\n[SF.Seq[5].Cleanup[1].TS]\n");
   fprintf(pFile, "Adapter = \"DLL Flexible Prototype Adapter\"\n");
   // SData
   fprintf(pFile, "\n[DEF, SF.Seq[5].Cleanup[1].TS]\n");
   fprintf(pFile, "SData = \"TYPE, FlexCStepAdditions\"\n");
   fprintf(pFile, "%%FLG: SData = 2097152\n");
   // LibPath & Param Def
   fprintf(pFile, "\n[SF.Seq[5].Cleanup[1].TS.SData.Call]\n");
   fprintf(pFile, "LibPath = \"tspan.dll\"\n");
   fprintf(pFile, "Func = \"tspan_DisplayDebugPanel\"\n");
   fprintf(pFile, "%%LO: Parms = [0]\n");
   fprintf(pFile, "%%HI: Parms = [5]\n");
   // FCParameters
   fprintf(pFile, "\n[DEF, SF.Seq[5].Cleanup[1].TS.SData.Call.Parms]\n");
   fprintf(pFile, "%%[0] = \"TYPE, FCParameter\"\n");
   fprintf(pFile, "%%[1] = \"TYPE, FCParameter\"\n");
   fprintf(pFile, "%%[2] = \"TYPE, FCParameter\"\n");
   fprintf(pFile, "%%[3] = \"TYPE, FCParameter\"\n");
   fprintf(pFile, "%%[4] = \"TYPE, FCParameter\"\n");
   fprintf(pFile, "%%[5] = \"TYPE, FCParameter\"\n");
   // Return Value
   fprintf(pFile, "\n[SF.Seq[5].Cleanup[1].TS.SData.Call.Parms[0]]\n");
   fprintf(pFile, "Name = \"Return Value\"\n");
   fprintf(pFile, "Type = 3\n");
   // sequenceContext
   fprintf(pFile, "\n[SF.Seq[5].Cleanup[1].TS.SData.Call.Parms[1]]\n");
   fprintf(pFile, "Name = \"sequenceContext\"\n");
   fprintf(pFile, "Type = 4\n");
   fprintf(pFile, "ObjType = 1\n");
   fprintf(pFile, "ArgVal = \"ThisContext\"\n");
   // errorOccurred
   fprintf(pFile, "\n[SF.Seq[5].Cleanup[1].TS.SData.Call.Parms[2]]\n");
   fprintf(pFile, "Name = \"resourceID\"\n");
   fprintf(pFile, "ArgVal = \"StationGlobals.TSVP.Panel_ID\"\n");
   // errorOccurred
   fprintf(pFile, "\n[SF.Seq[5].Cleanup[1].TS.SData.Call.Parms[3]]\n");
   fprintf(pFile, "Name = \"errorOccurred\"\n");
   fprintf(pFile, "NumType = 2\n");
   fprintf(pFile, "NumPass = 1\n");
   fprintf(pFile, "ArgVal = \"Step.Result.Error.Occurred\"\n");
   // errorCode//
   fprintf(pFile, "\n[SF.Seq[5].Cleanup[1].TS.SData.Call.Parms[4]]\n");
   fprintf(pFile, "Name = \"errorCode\"\n");
   fprintf(pFile, "NumPass = 1\n");
   fprintf(pFile, "ArgVal = \"Step.Result.Error.Code\"\n");
   // errorMessage
   fprintf(pFile, "\n[SF.Seq[5].Cleanup[1].TS.SData.Call.Parms[5]]\n");
   fprintf(pFile, "Name = \"errorMessage\"\n");
   fprintf(pFile, "Type = 2\n");
   fprintf(pFile, "StrPass = 2\n");
   fprintf(pFile, "ArgVal = \"Step.Result.Error.Msg\"\n");
   // Step-Name
   fprintf(pFile, "\n[DEF, SF.Seq[5].Cleanup[1]]\n");
   fprintf(pFile, "%%NAME = \"Debug Panel anzeigen\"\n");


   // SEQ 5 == DEF, SF.Seq[5].RTS

   // Def
   fprintf(pFile, "\n[DEF, SF.Seq[5].RTS]\n");
   fprintf(pFile, "Type = Num\n");
   fprintf(pFile, "EPNameExpr = Str\n");
   fprintf(pFile, "EPEnabledExpr = Str\n");
   fprintf(pFile, "EPMenuHint = Str\n");
   fprintf(pFile, "EPIgnoreClient = Bool\n");
   fprintf(pFile, "EPInitiallyHidden = Bool\n");
   fprintf(pFile, "EPCheckToSaveTitledFile = Bool\n");
   fprintf(pFile, "ShowEPForFileWin = Bool\n");
   fprintf(pFile, "ShowEPForExeWin = Bool\n");
   fprintf(pFile, "CopyStepsOnOverriding = Bool\n");
   fprintf(pFile, "OptimizeNonReentrantCalls = Bool\n");
   fprintf(pFile, "Priority = Num\n");
   fprintf(pFile, "ShowEPAlways = Bool\n");
   fprintf(pFile, "ShowEPForEditorOnly = Bool\n");
   fprintf(pFile, "AllowIntExeOfEP = Bool\n");
   // RTS
   fprintf(pFile, "\n[SF.Seq[5].RTS]\n");
   fprintf(pFile, "EPEnabledExpr = \"True\"\n");
   fprintf(pFile, "EPCheckToSaveTitledFile = True\n");
   fprintf(pFile, "ShowEPForFileWin = True\n");
   fprintf(pFile, "CopyStepsOnOverriding = True\n");
   fprintf(pFile, "OptimizeNonReentrantCalls = True\n");
   fprintf(pFile, "Priority = 2953567917\n");


   // SEQ 6 ===== S E Q U E N C E F I L E U N L O A D

   iStepIndex = 0;
   k = iSpecDev + 4-1+1; // +4 because of swmgr & resmgr & two for extended UIR, -1 because zero-based, +1 to set SequenceFileLoad

   fprintf(pFile, "\n[DEF, SF.Seq[6]]\n");
   fprintf(pFile, "Parameters = Obj\n");
   fprintf(pFile, "Locals = Obj\n");
   fprintf(pFile, "Main = Objs\n");
   fprintf(pFile, "Setup = Objs\n");
   fprintf(pFile, "Cleanup = Objs\n");
   fprintf(pFile, "GotoCleanupOnFail = Bool\n");
   fprintf(pFile, "StoreResults = Bool\n");
   fprintf(pFile, "RecordResults = Bool\n");
   fprintf(pFile, "RTS = Obj\n");
   fprintf(pFile, "Requirements = Obj\n");
   fprintf(pFile, "%%NAME = \"SequenceFileUnload\"\n");

   fprintf(pFile, "\n[SF.Seq[6]]\n");
   fprintf(pFile, "%%FLG: Parameters = 262144\n");

   fprintf(pFile, "%%LO: Cleanup = [0]\n");
   fprintf(pFile, "%%HI: Cleanup = [%i]\n", k);
   // !!!
   fprintf(pFile, "%%FLG: GotoCleanupOnFail = 8\n");
   fprintf(pFile, "StoreResults = True\n");
   fprintf(pFile, "RecordResults = True\n");
   fprintf(pFile, "%%FLG: RecordResults = 8\n");
   fprintf(pFile, "%%FLG: RTS = 262152\n");
   fprintf(pFile, "%%FLG: Requirements = 4456456\n");

   fprintf(pFile, "\n[DEF, SF.Seq[6].Locals]\n");
   fprintf(pFile, "ResultList = Objs\n");

   fprintf(pFile, "\n[DEF, SF.Seq[6].Locals.ResultList]\n");
   fprintf(pFile, "%%EPTYPE = TEResult\n");

   n = k - (iPHDTchecked + iPIO2checked) + 1; // step-no. of first phdt or pio2 dev

   fprintf(pFile, "\n[DEF, SF.Seq[6].Cleanup]\n");
   for (i = 0; i <= k; i++)
   // how many dev to cleanup
   {
      if (i == n)
      // if 'step-no.' reached 'no. of first phdt or pio2' (if there are none of them i is never equal to k)
      {
         fprintf(pFile, "%%[%i] = SequenceCall\n", i);
         fprintf(pFile, "%%TYPE: %%[%i] = \"Action\"\n", i);
         n++;
      }
      else if (i == k)
      {
         fprintf(pFile, "%%[%i] = NoneStep\n", i);
         fprintf(pFile, "%%TYPE: %%[%i] = \"Statement\"\n", i);
      }
      else
      {
         fprintf(pFile, "%%[%i] = FlexCStep\n", i);
         fprintf(pFile, "%%TYPE: %%[%i] = \"Action\"\n", i);
      }
   }


   // C L O S E D E V I C E S

   for (i = 0; i <= (iSpecDev - iPHDTchecked - iPIO2checked); i++)
   // without phdt & pio2, because they need extra de-init.
   {
      // SELECT DEVICE
      if (iPSAMchecked > 0)
      {
         sprintf(cFullName, "Digitalmulitmeter");
         sprintf(cAKA, "dmm");
         sprintf(cSetupName, "DMM");
         // SELECT BENCH
         k = iDevCountBuffer[0] + 1-iPSAMchecked;
         /******************************************************/
         /*** iDevCountBuffer is no. of all dev of this type ***/
         /*** iXXXchecked is the no. of the current dev      ***/
         /*** k is the no. of the current bench			  ***/
         /*** i.e.: if iXXXchecked == 4 then k = 1			  ***/
         /***       if iXXXchecked == 3 then k = 2		      ***/
         /***       if iXXXchecked == 2 then k = 3			  ***/
         /***       if iXXXchecked == 1 then k = 4			  ***/
         /******************************************************/
         if (iDevCountBuffer[0] > 1)
         // only if there are more dev of same type
         {
            n = k; // no. of current dev for displayed text
         }
         else
         {
            n = 0;
         }
         iPSAMchecked--;
      }
      else if (iPAMchecked > 0)
      {
         sprintf(cFullName, "Signalanalysator");
         sprintf(cAKA, "siganl");
         sprintf(cSetupName, "SIGANL");
         // SELECT BENCH (explanation see above)
         k = iDevCountBuffer[1] + 1-iPAMchecked;
         if (iDevCountBuffer[1] > 1)
         // only if there are more dev of same type
         {
            n = k; // no. of current dev for displayed text
         }
         else
         {
            n = 0;
         }
         iPAMchecked--;
      }
      else if (iPFGchecked > 0)
      {
         sprintf(cFullName, "Funktionsgenerator");
         sprintf(cAKA, "funcgen");
         sprintf(cSetupName, "FUNCGEN");
         // SELECT BENCH (explanation see above)
         k = iDevCountBuffer[2] + 1-iPFGchecked;
         if (iDevCountBuffer[2] > 1)
         // only if there are more dev of same type
         {
            n = k; // no. of current dev for displayed text
         }
         else
         {
            n = 0;
         }
         iPFGchecked--;
      }
      else if (iPDFTchecked > 0)
      {
         sprintf(cFullName, "Digital-IO-Manager");
         sprintf(cAKA, "diomgr");
         sprintf(cSetupName, "DIOMGR");
         // SELECT BENCH
         k = 1; // every dev of this type in first bench
         n = 0; // initialize only one time, even for multiple dev
         iPDFTchecked = 0;
      }
      else if (iPICTchecked > 0)
      {
         sprintf(cFullName, "ICT Erweiterungsmodul");
         sprintf(cAKA, "ict");
         sprintf(cSetupName, "ICT");
         // SELECT BENCH
         k = 1; // multiple dev dont make sense
         n = 0; // initialize only one time
         iPICTchecked = 0;
      }
      else if (iPSUchecked > 0)
      {
         sprintf(cFullName, "DC-Stromversorgungs-Module");
         sprintf(cAKA, "dcpwr");
         sprintf(cSetupName, "DCPWR");
         // SELECT BENCH (explanation see above)
         k = 1; // every dev in first bench
         n = 0; // initialize only one time, even for multiple dev
         iPSUchecked = 0;
      }
      else
      {
         sprintf(cFullName, "Switch-Manager");
         sprintf(cAKA, "swmgr");
         sprintf(cSetupName, "SWMGR");
         // SELECT BENCH
         k = 1; // in first bench
         n = 0; // there is only one switch mgr
      }

      // SEQ 6 == [-0-] == CLOSE DEVICES

      // Adapter
      fprintf(pFile, "\n[SF.Seq[6].Cleanup[%i].TS]\n", iStepIndex);
      fprintf(pFile, "Adapter = \"DLL Flexible Prototype Adapter\"\n");
      // SData
      fprintf(pFile, "\n[DEF, SF.Seq[6].Cleanup[%i].TS]\n", iStepIndex);
      fprintf(pFile, "SData = \"TYPE, FlexCStepAdditions\"\n");
      fprintf(pFile, "%%FLG: SData = 2097152\n");
      // LibPath & Param Def
      fprintf(pFile, "\n[SF.Seq[6].Cleanup[%i].TS.SData.Call]\n", iStepIndex);
      fprintf(pFile, "LibPath = \"%s.dll\"\n", cAKA); // Dll name i.e. "dmm.dll"
      fprintf(pFile, "Func = \"%s_Cleanup\"\n", cSetupName); // Setup name i.e. "DMM_Setup"
      fprintf(pFile, "%%LO: Parms = [0]\n");
      fprintf(pFile, "%%HI: Parms = [5]\n");
      // FCParameters
      fprintf(pFile, "\n[DEF, SF.Seq[6].Cleanup[%i].TS.SData.Call.Parms]\n", iStepIndex);
      fprintf(pFile, "%%[0] = \"TYPE, FCParameter\"\n");
      fprintf(pFile, "%%[1] = \"TYPE, FCParameter\"\n");
      fprintf(pFile, "%%[2] = \"TYPE, FCParameter\"\n");
      fprintf(pFile, "%%[3] = \"TYPE, FCParameter\"\n");
      fprintf(pFile, "%%[4] = \"TYPE, FCParameter\"\n");
      fprintf(pFile, "%%[5] = \"TYPE, FCParameter\"\n");
      // Return Value
      fprintf(pFile, "\n[SF.Seq[6].Cleanup[%i].TS.SData.Call.Parms[0]]\n", iStepIndex);
      fprintf(pFile, "Name = \"Return Value\"\n");
      fprintf(pFile, "Type = 3\n");
      // sequenceContext
      fprintf(pFile, "\n[SF.Seq[6].Cleanup[%i].TS.SData.Call.Parms[1]]\n", iStepIndex);
      fprintf(pFile, "Name = \"sequenceContext\"\n");
      fprintf(pFile, "Type = 4\n");
      fprintf(pFile, "ObjType = 1\n");
      fprintf(pFile, "ArgVal = \"ThisContext\"\n");
      // resourceID
      fprintf(pFile, "\n[SF.Seq[6].Cleanup[%i].TS.SData.Call.Parms[2]]\n", iStepIndex);
      fprintf(pFile, "Name = \"resourceID\"\n");
      if (n > 0)
      // Device ID for Station Globals
      {
         fprintf(pFile, "ArgVal = \"StationGlobals.TSVP.%s_%i_ID\"\n", cAKA, n);
      }
      else
      {
         fprintf(pFile, "ArgVal = \"StationGlobals.TSVP.%s_ID\"\n", cAKA);
      }
      // errorOccurred
      fprintf(pFile, "\n[SF.Seq[6].Cleanup[%i].TS.SData.Call.Parms[3]]\n", iStepIndex);
      fprintf(pFile, "Name = \"errorOccurred\"\n");
      fprintf(pFile, "NumType = 2\n");
      fprintf(pFile, "NumPass = 1\n");
      fprintf(pFile, "ArgVal = \"Step.Result.Error.Occurred\"\n");
      // errorCode
      fprintf(pFile, "\n[SF.Seq[6].Cleanup[%i].TS.SData.Call.Parms[4]]\n", iStepIndex);
      fprintf(pFile, "Name = \"errorCode\"\n");
      fprintf(pFile, "NumPass = 1\n");
      fprintf(pFile, "ArgVal = \"Step.Result.Error.Code\"\n");
      fprintf(pFile, "ArgDisplayVal = \"Step.Result.Error.Code\"\n");
      // errorMessage
      fprintf(pFile, "\n[SF.Seq[6].Cleanup[%i].TS.SData.Call.Parms[5]]\n", iStepIndex);
      fprintf(pFile, "Name = \"errorMessage\"\n");
      fprintf(pFile, "Type = 2\n");
      fprintf(pFile, "StrPass = 2\n");
      fprintf(pFile, "ArgVal = \"Step.Result.Error.Msg\"\n");
      fprintf(pFile, "ArgDisplayVal = \"Step.Result.Error.Msg\"\n");
      // Step-Name
      fprintf(pFile, "\n[DEF, SF.Seq[6].Cleanup[%i]]\n", iStepIndex);
      if (n > 0)
      {
         fprintf(pFile, "%%NAME = \"%s %i beenden\"\n", cFullName, n); // Full name with no.  i.e. "Digitalmulitmeter 3"
      }
      else
      {
         fprintf(pFile, "%%NAME = \"%s beenden\"\n", cFullName); // Full name of the device without number
      }
      // next step!
      iStepIndex++;
   }

   // restore the original device quantity.
   iPSAMchecked = iDevCountBuffer[0];
   iPAMchecked = iDevCountBuffer[1];
   iPFGchecked = iDevCountBuffer[2];
   iPDFTchecked = iDevCountBuffer[3];
   iPICTchecked = iDevCountBuffer[5];
   iPSUchecked = iDevCountBuffer[7];


   // CLOSE PHDT & PIO2 DEVICES

   if (iPHDTchecked || iPIO2checked)
   {
      // SELECT DEVICE
      for (i = 0; i <= (iPHDTchecked + iPIO2checked); i++)
      {

         if (iPHDTchecked > 0)
         {
            sprintf(cFullName, "High-Speed Digitaltest-Modul");
            sprintf(cAKA, "phdt");
            sprintf(cSetupName, "PHDT");
            // SELECT BENCH (explanation see above)
            k = iDevCountBuffer[4] + 1-iPHDTchecked;
            if (iDevCountBuffer[4] > 1)
            // only if there are more dev of same type
            {
               n = k; // no. of current dev for displayed text
            }
            else
            {
               n = 0;
            }
            iPHDTchecked--;
         }
         else if (iPIO2checked > 0)
         {
            sprintf(cFullName, "Analog/Digital-IO-Modul");
            sprintf(cAKA, "pio2");
            sprintf(cSetupName, "PIO2");
            // SELECT BENCH (explanation see above)
            k = iDevCountBuffer[6] + 1-iPIO2checked;
            if (iDevCountBuffer[6] > 1)
            // only if there are more dev of same type
            {
               n = k; // no. of current dev for displayed text
            }
            else
            {
               n = 0;
            }
            iPIO2checked--;
         }

         // SEQ 6 == [-1-] == CLOSE DEVICES

         // Adapter
         fprintf(pFile, "\n[SF.Seq[6].Cleanup[%i].TS]\n", iStepIndex);
         fprintf(pFile, "Adapter = \"Sequence Adapter\"\n");
         // SData
         fprintf(pFile, "\n[DEF, SF.Seq[6].Cleanup[%i].TS]\n", iStepIndex);
         fprintf(pFile, "SData = \"TYPE, SeqCallStepAdditions\"\n");
         fprintf(pFile, "%%FLG: SData = 2097152\n");
         // SFPath & SeqName
         fprintf(pFile, "\n[SF.Seq[6].Cleanup[%i].TS.SData]\n", iStepIndex);
         fprintf(pFile, "SFPath = \"TS_%s_Bibliothek.seq\"\n", cSetupName);
         fprintf(pFile, "SeqName = \"Cleanup\"\n");
         // ActualArgs
         fprintf(pFile, "\n[DEF, SF.Seq[6].Cleanup[%i].TS.SData]\n", iStepIndex);
         fprintf(pFile, "ActualArgs = Arguments\n");
         fprintf(pFile, "%%FLG: ActualArgs = 2097152\n");
         // Type
         fprintf(pFile, "\n[DEF, SF.Seq[6].Cleanup[%i].TS.SData.ActualArgs]\n", iStepIndex);
         fprintf(pFile, "arg0 = \"TYPE, SequenceArgument\"\n");
         // Device
         fprintf(pFile, "\n[SF.Seq[6].Cleanup[%i].TS.SData.ActualArgs.arg0]\n", iStepIndex);
         fprintf(pFile, "UseDef = False\n");
         fprintf(pFile, "Expr = \"\\\"device->%s\\\"\"\n", cAKA);
         // Step-Name
         fprintf(pFile, "\n[DEF, SF.Seq[6].Cleanup[%i]]\n", iStepIndex);
         fprintf(pFile, "%%NAME = \"%s beenden\"\n", cSetupName);
         // next step!
         iStepIndex++;
      }

      // restore the original device quantity.
      iPHDTchecked = iDevCountBuffer[4];
      iPIO2checked = iDevCountBuffer[6];
   }


   // SEQ 6 == [-2-] == CLOSE INTERFACE

   for (i = 0; i < 2; i++)
   {
      // Adapter
      fprintf(pFile, "\n[SF.Seq[6].Cleanup[%i].TS]\n", iStepIndex);
      fprintf(pFile, "Adapter = \"DLL Flexible Prototype Adapter\"\n");
      // SData
      fprintf(pFile, "\n[DEF, SF.Seq[6].Cleanup[%i].TS]\n", iStepIndex);
      fprintf(pFile, "SData = \"TYPE, FlexCStepAdditions\"\n");
      fprintf(pFile, "%%FLG: SData = 2097152\n");
      // LibPath & Param Def
      fprintf(pFile, "\n[SF.Seq[6].Cleanup[%i].TS.SData.Call]\n", iStepIndex);
      fprintf(pFile, "LibPath = \"tspan.dll\"\n");
      if (i == 0)
      {
         fprintf(pFile, "Func = \"tspan_HideActualPanel\"\n");
      }
      else
      {
         fprintf(pFile, "Func = \"tspan_Cleanup\"\n");
      }
      fprintf(pFile, "%%LO: Parms = [0]\n");
      fprintf(pFile, "%%HI: Parms = [5]\n");
      // FCParameters
      fprintf(pFile, "\n[DEF, SF.Seq[6].Cleanup[%i].TS.SData.Call.Parms]\n", iStepIndex);
      fprintf(pFile, "%%[0] = \"TYPE, FCParameter\"\n");
      fprintf(pFile, "%%[1] = \"TYPE, FCParameter\"\n");
      fprintf(pFile, "%%[2] = \"TYPE, FCParameter\"\n");
      fprintf(pFile, "%%[3] = \"TYPE, FCParameter\"\n");
      fprintf(pFile, "%%[4] = \"TYPE, FCParameter\"\n");
      fprintf(pFile, "%%[5] = \"TYPE, FCParameter\"\n");
      // Return Value
      fprintf(pFile, "\n[SF.Seq[6].Cleanup[%i].TS.SData.Call.Parms[0]]\n", iStepIndex);
      fprintf(pFile, "Name = \"Return Value\"\n");
      fprintf(pFile, "Type = 3\n");
      // sequenceContext
      fprintf(pFile, "\n[SF.Seq[6].Cleanup[%i].TS.SData.Call.Parms[1]]\n", iStepIndex);
      fprintf(pFile, "Name = \"sequenceContext\"\n");
      fprintf(pFile, "Type = 4\n");
      fprintf(pFile, "ObjType = 1\n");
      fprintf(pFile, "ArgVal = \"ThisContext\"\n");
      // resourceID
      fprintf(pFile, "\n[SF.Seq[6].Cleanup[%i].TS.SData.Call.Parms[2]]\n", iStepIndex);
      fprintf(pFile, "Name = \"resourceID\"\n");
      fprintf(pFile, "ArgVal = \"StationGlobals.TSVP.Panel_ID\"\n");
      if (i == 0)
      {
         fprintf(pFile, "ArgDisplayVal = \"StationGlobals.TSVP.Panel_ID\"\n"); // this line is for "closing the UIR". No need for step "Cleanup"
      }
      // errorOccurred
      fprintf(pFile, "\n[SF.Seq[6].Cleanup[%i].TS.SData.Call.Parms[3]]\n", iStepIndex);
      fprintf(pFile, "Name = \"errorOccurred\"\n");
      fprintf(pFile, "NumType = 2\n");
      fprintf(pFile, "NumPass = 1\n");
      fprintf(pFile, "ArgVal = \"Step.Result.Error.Occurred\"\n");
      if (i == 0)
      {
         fprintf(pFile, "ArgDisplayVal = \"Step.Result.Error.Occurred\"\n"); // this line is for "closing the UIR". No need for step "Cleanup"
      }
      // errorCode
      fprintf(pFile, "\n[SF.Seq[6].Cleanup[%i].TS.SData.Call.Parms[4]]\n", iStepIndex);
      fprintf(pFile, "Name = \"errorCode\"\n");
      fprintf(pFile, "NumPass = 1\n");
      fprintf(pFile, "ArgVal = \"Step.Result.Error.Code\"\n");
      if (i == 0)
      {
         fprintf(pFile, "ArgDisplayVal = \"Step.Result.Error.Code\"\n");
      }
      // errorMessage
      fprintf(pFile, "\n[SF.Seq[6].Cleanup[%i].TS.SData.Call.Parms[5]]\n", iStepIndex);
      fprintf(pFile, "Name = \"errorMessage\"\n");
      fprintf(pFile, "Type = 2\n");
      fprintf(pFile, "StrPass = 2\n");
      fprintf(pFile, "ArgVal = \"Step.Result.Error.Msg\"\n");
      if (i == 0)
      {
         fprintf(pFile, "ArgDisplayVal = \"Step.Result.Error.Msg\"\n");
      }
      // Step-Name
      fprintf(pFile, "\n[DEF, SF.Seq[6].Cleanup[%i]]\n", iStepIndex);
      if (i == 0)
      {
         fprintf(pFile, "%%NAME = \"Aktuell angezeigte Benutzeroberfläche entfernen\"\n");
      }
      else
      {
         fprintf(pFile, "%%NAME = \"Cleanup\"\n");
      }
      // next step!
      iStepIndex++;
   }


   // SEQ 6 == [-3-] == CLOSE RESOURCE MANAGER

   // Adapter
   fprintf(pFile, "\n[SF.Seq[6].Cleanup[%i].TS]\n", iStepIndex);
   fprintf(pFile, "Adapter = \"DLL Flexible Prototype Adapter\"\n");
   // SData
   fprintf(pFile, "\n[DEF, SF.Seq[6].Cleanup[%i].TS]\n", iStepIndex);
   fprintf(pFile, "SData = \"TYPE, FlexCStepAdditions\"\n");
   fprintf(pFile, "%%FLG: SData = 2097152\n");
   // LibPath & Params Def
   fprintf(pFile, "\n[SF.Seq[6].Cleanup[%i].TS.SData.Call]\n", iStepIndex);
   fprintf(pFile, "LibPath = \"resmgr.dll\"\n");
   fprintf(pFile, "Func = \"RESMGR_Cleanup\"\n");
   fprintf(pFile, "%%LO: Parms = [0]\n");
   fprintf(pFile, "%%HI: Parms = [4]\n");
   // FCParameters
   fprintf(pFile, "\n[DEF, SF.Seq[6].Cleanup[%i].TS.SData.Call.Parms]\n", iStepIndex);
   fprintf(pFile, "%%[0] = \"TYPE, FCParameter\"\n");
   fprintf(pFile, "%%[1] = \"TYPE, FCParameter\"\n");
   fprintf(pFile, "%%[2] = \"TYPE, FCParameter\"\n");
   fprintf(pFile, "%%[3] = \"TYPE, FCParameter\"\n");
   fprintf(pFile, "%%[4] = \"TYPE, FCParameter\"\n");
   // Return Value
   fprintf(pFile, "\n[SF.Seq[6].Cleanup[%i].TS.SData.Call.Parms[0]]\n", iStepIndex);
   fprintf(pFile, "Name = \"Return Value\"\n");
   fprintf(pFile, "Type = 3\n");
   // sequenceContext
   fprintf(pFile, "\n[SF.Seq[6].Cleanup[%i].TS.SData.Call.Parms[1]]\n", iStepIndex);
   fprintf(pFile, "Name = \"sequenceContext\"\n");
   fprintf(pFile, "Type = 4\n");
   fprintf(pFile, "ObjType = 1\n");
   fprintf(pFile, "ArgVal = \"ThisContext\"\n");
   // errorOccurred
   fprintf(pFile, "\n[SF.Seq[6].Cleanup[%i].TS.SData.Call.Parms[2]]\n", iStepIndex);
   fprintf(pFile, "Name = \"errorOccurred\"\n");
   fprintf(pFile, "NumType = 2\n");
   fprintf(pFile, "NumPass = 1\n");
   fprintf(pFile, "ArgVal = \"Step.Result.Error.Occurred\"\n");
   // errorCode
   fprintf(pFile, "\n[SF.Seq[6].Cleanup[%i].TS.SData.Call.Parms[3]]\n", iStepIndex);
   fprintf(pFile, "Name = \"errorCode\"\n");
   fprintf(pFile, "NumPass = 1\n");
   fprintf(pFile, "ArgVal = \"Step.Result.Error.Code\"\n");
   // errorMessage
   fprintf(pFile, "\n[SF.Seq[6].Cleanup[%i].TS.SData.Call.Parms[4]]\n", iStepIndex);
   fprintf(pFile, "Name = \"errorMessage\"\n");
   fprintf(pFile, "Type = 2\n");
   fprintf(pFile, "StrPass = 2\n");
   fprintf(pFile, "ArgVal = \"Step.Result.Error.Msg\"\n");
   // Step-Name
   fprintf(pFile, "\n[DEF, SF.Seq[6].Cleanup[%i]]\n", iStepIndex);
   fprintf(pFile, "%%NAME = \"Resource-Manager entladen\"\n");
   // next step!
   iStepIndex++;



   // SEQ == [-4-] == SET SEQUENCEFILELOADCOMPLET

   fprintf(pFile, "\n[SF.Seq[6].Cleanup[%i].TS]\n", iStepIndex);
   fprintf(pFile, "Adapter = \"None Adapter\"\n");
   fprintf(pFile, "PostExpr = \"StationGlobals.TSVP.SequenceFileLoadComplete = False\"\n");

   fprintf(pFile, "\n[DEF, SF.Seq[6].Cleanup[%i].TS]\n", iStepIndex);
   fprintf(pFile, "SData = \"TYPE, NoneStepAdditions\"\n");
   fprintf(pFile, "%%FLG: SData = 2097152\n");

   fprintf(pFile, "\n[DEF, SF.Seq[6].Cleanup[%i]]\n", iStepIndex);
   fprintf(pFile, "%%NAME = \"StationGlobal setzen\"\n");





   // SEQ 6 == DEF, SF.Seq[6].RTS

   // Def
   fprintf(pFile, "\n[DEF, SF.Seq[6].RTS]\n");
   fprintf(pFile, "Type = Num\n");
   fprintf(pFile, "EPNameExpr = Str\n");
   fprintf(pFile, "EPEnabledExpr = Str\n");
   fprintf(pFile, "EPMenuHint = Str\n");
   fprintf(pFile, "EPIgnoreClient = Bool\n");
   fprintf(pFile, "EPInitiallyHidden = Bool\n");
   fprintf(pFile, "EPCheckToSaveTitledFile = Bool\n");
   fprintf(pFile, "ShowEPForFileWin = Bool\n");
   fprintf(pFile, "ShowEPForExeWin = Bool\n");
   fprintf(pFile, "CopyStepsOnOverriding = Bool\n");
   fprintf(pFile, "OptimizeNonReentrantCalls = Bool\n");
   fprintf(pFile, "Priority = Num\n");
   fprintf(pFile, "ShowEPAlways = Bool\n");
   fprintf(pFile, "ShowEPForEditorOnly = Bool\n");
   fprintf(pFile, "AllowIntExeOfEP = Bool\n");
   // RTS
   fprintf(pFile, "\n[SF.Seq[6].RTS]\n");
   fprintf(pFile, "EPEnabledExpr = \"True\"\n");
   fprintf(pFile, "EPCheckToSaveTitledFile = True\n");
   fprintf(pFile, "ShowEPForFileWin = True\n");
   fprintf(pFile, "CopyStepsOnOverriding = True\n");
   fprintf(pFile, "OptimizeNonReentrantCalls = True\n");
   fprintf(pFile, "Priority = 2953567917\n");

   // REST

   fprintf(pFile, "\n[%%TYPES]\n");
   fprintf(pFile, "Path = \"Path\"\n");
   fprintf(pFile, "Action = \"Action\"\n");
   fprintf(pFile, "StepTypeSubstepsArray = \"StepTypeSubstepsArray\"\n");
   fprintf(pFile, "StepTypeDescFmt = \"StepTypeDescFmt\"\n");
   fprintf(pFile, "StepTypeDefNameFmt = \"StepTypeDefNameFmt\"\n");
   fprintf(pFile, "StepTypeMenu = \"StepTypeMenu\"\n");
   fprintf(pFile, "TEInf = \"TEInf\"\n");
   fprintf(pFile, "Error = \"Error\"\n");
   fprintf(pFile, "CommonResults = \"CommonResults\"\n");
   fprintf(pFile, "FlexCStepAdditions = \"FlexCStepAdditions\"\n");
   fprintf(pFile, "FCParameter = \"FCParameter\"\n");
   fprintf(pFile, "UUT = \"UUT\"\n");
   fprintf(pFile, "NI_CriticalFailureStackEntry = \"NI_CriticalFailureStackEntry\"\n");
   fprintf(pFile, "EditSubstep = \"EditSubstep\"\n");
   fprintf(pFile, "NoneStepAdditions = \"NoneStepAdditions\"\n");
   fprintf(pFile, "Statement = \"Statement\"\n");
   fprintf(pFile, "Label = \"Label\"\n");
   fprintf(pFile, "Goto = \"Goto\"\n");
   fprintf(pFile, "NI_Wait = \"NI_Wait\"\n");
   fprintf(pFile, "PostSubstep = \"PostSubstep\"\n");
   fprintf(pFile, "StepTypeDescFmt = \"StepTypeDescFmt\"\n");
   fprintf(pFile, "StepTypeDefNameFmt = \"StepTypeDefNameFmt\"\n");
   fprintf(pFile, "UUT = \"UUT\"\n");
   fprintf(pFile, "NI_CriticalFailureStackEntry = \"NI_CriticalFailureStackEntry\"\n");

   if (iPHDTchecked || iPIO2checked)
   // if phdt or pio2 is available some lines have to be added
   {
      fprintf(pFile, "SeqCallStepAdditions = \"SeqCallStepAdditions\"\n");
      fprintf(pFile, "SequenceArgument = \"SequenceArgument\"\n");
   }
   // Rest
   fprintf(pFile, "\n");
   sprintf(cPathName, "%s\\resources\\template5.txt", cProjectDir); // Insert template with rest

   pFile = MergeEncodedTextFile(pFile, cPathName);
   if (pFile == 0)
   {
      MessagePopup("TG-ITS", "Could not open %s\nCheck resource folder!");
      return 0;
   }

   // MORE ADDITIONS IF PHDT OR PIO2 ARE AVAILABLE
   if (iPHDTchecked || iPIO2checked)
   {
      // DEF, SeqCallStepAdditions
      fprintf(pFile, "\n\n[DEF, SeqCallStepAdditions]\n");
      fprintf(pFile, "%%LOCATION = \"StdTypes\"\n");
      fprintf(pFile, "SFPath = \"TYPE, Path\"\n");
      fprintf(pFile, "SFPathExpr = Str\n");
      fprintf(pFile, "SeqName = Str\n");
      fprintf(pFile, "SeqNameExpr = Str\n");
      fprintf(pFile, "ActualArgs = Arguments\n");
      fprintf(pFile, "%%FLG: ActualArgs = 2097152\n");
      fprintf(pFile, "UseCurFile = Bool\n");
      fprintf(pFile, "SpecifyByExpr = Bool\n");
      fprintf(pFile, "Prototype = Obj\n");
      fprintf(pFile, "%%FLG: Prototype = 2097152\n");
      fprintf(pFile, "UsePrototype = Bool\n");
      fprintf(pFile, "SpecifyHostByExpr = Bool\n");
      fprintf(pFile, "RemoteExecution = Bool\n");
      fprintf(pFile, "RemoteHost = Str\n");
      fprintf(pFile, "RemoteHostExpr = Str\n");
      fprintf(pFile, "AutoWaitAsync = Bool\n");
      fprintf(pFile, "CreateThreadSuspended = Bool\n");
      fprintf(pFile, "AsyncThreadExpr = Str\n");
      fprintf(pFile, "ThreadOpt = Num\n");
      fprintf(pFile, "ExecModelOpt = Num\n");
      fprintf(pFile, "ExecTypeMask = Num\n");
      fprintf(pFile, "ExecTypeMaskExpr = Str\n");
      fprintf(pFile, "ExecBreakOnEntryExpr = Str\n");
      fprintf(pFile, "ExecModelPath = \"TYPE, Path\"\n");
      fprintf(pFile, "ExecModelPathExpr = Str\n");
      fprintf(pFile, "ExecSync = Bool\n");
      fprintf(pFile, "Trace = Str\n");
      fprintf(pFile, "IgnoreTerminate = Bool\n");
      fprintf(pFile, "%%ROOT_TYPE = True\n");
      // SeqCallStepAdditions
      fprintf(pFile, "\n[SeqCallStepAdditions]\n");
      fprintf(pFile, "AutoWaitAsync = True\n");
      fprintf(pFile, "ExecModelOpt = 1\n");
      fprintf(pFile, "ExecBreakOnEntryExpr = \"False\"\n");
      fprintf(pFile, "Trace = \"Don't Change\"\n");
      fprintf(pFile, "%%TIMESTAMP = 1008353140\n");
      fprintf(pFile, "%%VERSION = \"2.0.1.121\"\n");
      fprintf(pFile, "%%FLG = 33554456\n");
      // DEF, SequenceArgument
      fprintf(pFile, "\n[DEF, SequenceArgument]\n");
      fprintf(pFile, "%%LOCATION = \"StdTypes\"\n");
      fprintf(pFile, "UseDef = Bool\n");
      fprintf(pFile, "Expr = Str\n");
      fprintf(pFile, "%%ROOT_TYPE = True\n");
      // SequenceArgument
      fprintf(pFile, "\n[SequenceArgument]\n");
      fprintf(pFile, "UseDef = True\n");
      fprintf(pFile, "%%TIMESTAMP = 1018442948\n");
      fprintf(pFile, "%%VERSION = \"2.0.1.121\"\n");
      fprintf(pFile, "%%FLG = 33554456\n");
   }


   // E N D
   fclose(pFile);
   iWantTstSeq = 1; // for the export-completed-popup
   return 0;
}

/* FUNCTION *****************************************************************/
/**
DoubleBackslash
 *
@brief This function duplicates all backslashes of a character array (i.e paths)
\n[code by Albert Killer]
 *
@param cOldPath: input character array
@param cNewPath: output character array
 *
@return void
 *****************************************************************************/
void DoubleBackslash(char cOldPath[], char cNewPath[])
{
   int o, n;
   for (n = 0, o = 0; o < 300; o++, n++)
   {
      if (cOldPath[o] == '\\')
      {
         cNewPath[n] = '\\';
         n++;
         cNewPath[n] = '\\';
         n++;
         cNewPath[n] = '\\';
         n++;
         cNewPath[n] = '\\';
      }
      else
      {
         cNewPath[n] = cOldPath[o];
      }
   }
   return ;
}
