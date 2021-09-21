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
@file util.c
 *
@brief Include all utility functions
 *
@version 1.0.0.1
 *
@author Robert Renner <A HREF="mailto:4r@sw-its.net">4r@sw-its.net</A>\n

Language: ANSI-C ISO/IEC9899:1990
 *
<b>History:</b>
- <b>02.12.04 R.Renner</b>
- Initial revision
- <b>05.11.08 R.Renner</b>
- Debugging of some functions

 ******************************************************************************
 *****************************************************************************/

/* INCLUDE FILES ************************************************************/
#include "main.h"


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
pAppendDevice
 *
@brief This function appends a new device to the general device list
 *
@param pFirst: First element of device list
@param iType: Type of device (GPIB, PXI ...)
@param cBenchName: Name of device
@param ResourceDescription: Resource descriptor of device
@param iID: ID of device (is used to identify device in UIR or menu bar)
 *
@return First element of device list
 *****************************************************************************/
ressource* pAppendDevice(ressource* pFirst, int iType, char* cBenchName, char* ResourceDescription, int iID, int iSlot, int iFrame)
{
   ressource* pTMP;
   ressource* pTMPnew;
   ressource* pTMPBuffer;

   if (pFirst == NULL)
   {
      pFirst = malloc(sizeof(*pFirst));
      if (pFirst != NULL)
      {
         pFirst->iInternalType = iType;
         pFirst->iID = iID;
         pFirst->iMarkedForExport = 0;
         sprintf(pFirst->cBenchName, cBenchName);
         sprintf(pFirst->cRessourceDesc, ResourceDescription);
         pFirst->iSlot = iSlot;
         pFirst->iFrame = iFrame;
         sprintf(pFirst->cDescription, "");
         sprintf(pFirst->cType, "");
         sprintf(pFirst->cDriverDLL, "");
         sprintf(pFirst->cDriverPrefix, "");
         sprintf(pFirst->cDriverOption, "");
         sprintf(pFirst->cSFTDll, "");
         sprintf(pFirst->cSFTPrefix, "");
         pFirst->iBaudrate = 0;
         sprintf(pFirst->cParity, "NONE");
         sprintf(pFirst->cHandshake, "NONE");
         pFirst->iDataBits = 0;
         pFirst->iStopBits = 0;
         pFirst->next = NULL;
      }
      else
      {
         MessagePopup("TG-ITS", "Not enough memory!");
         pFirst = NULL;
         return pFirst;
      }
   }
   else
   {
      pTMP = pFirst;

      pTMPnew = malloc(sizeof(*pTMP));

      if (pTMPnew != NULL)
      {
         pTMPnew->iInternalType = iType;
         pTMPnew->iID = iID;
         pTMPnew->iMarkedForExport = 0;
         sprintf(pTMPnew->cBenchName, cBenchName);
         sprintf(pTMPnew->cRessourceDesc, ResourceDescription);
         pTMPnew->iFrame = iFrame;
         pTMPnew->iSlot = iSlot;
         sprintf(pTMPnew->cDescription, "");
         sprintf(pTMPnew->cType, "");
         sprintf(pTMPnew->cDriverDLL, "");
         sprintf(pTMPnew->cDriverPrefix, "");
         sprintf(pTMPnew->cDriverOption, "");
         sprintf(pTMPnew->cSFTDll, "");
         sprintf(pTMPnew->cSFTPrefix, "");
         pTMPnew->iBaudrate = 0;
         sprintf(pTMPnew->cParity, "NONE");
         sprintf(pTMPnew->cHandshake, "NONE");
         pTMPnew->iDataBits = 0;
         pTMPnew->iStopBits = 0;
      }
      else
      {
         MessagePopup("TG-ITS", "Not enough memory!");
         pTMP = NULL;
         return pFirst;
      }

      if (iType == PXI)
      {
         // Case 1A: No PXI but other devices available
         if (pTMP->iInternalType != PXI)
         {
            pTMPnew->next = pTMP;
            pFirst = pTMPnew;
         }

         // Case 1B: PXI available
         else if (pTMP->iInternalType == PXI)
         {
            if (pTMP->next != NULL)
            {
               while ((pTMP->iInternalType == PXI) && (pTMP->next != NULL))
               {
                  if (pTMP->next->iInternalType == CAN)
                  {
                     break;
                  }
                  pTMP = pTMP->next;
               }
            }
            pTMPnew->next = pTMP->next;
            pTMP->next = pTMPnew;
         }
      }

      if (iType == CAN)
      {
         // Case 2A: No CAN and no PXI but other devices available
         if (pTMP->iInternalType != CAN && pTMP->iInternalType != PXI)
         {
            pTMPnew->next = pTMP;
            pFirst = pTMPnew;
         }
         // Case 2B: PXI and/or CAN available
         else if ((pTMP->iInternalType == CAN) || (pTMP->iInternalType == PXI))
         {
            while ((pTMP->iInternalType == PXI) && (pTMP->next != NULL))
            {
               pTMP = pTMP->next;
            }
            while ((pTMP->iInternalType == CAN) && (pTMP->next != NULL))
            {
               if (pTMP->next->iInternalType == ASRL)
               {
                  break;
               }
               pTMP = pTMP->next;
            }
            pTMPnew->next = pTMP->next;
            pTMP->next = pTMPnew;
         }
      }

      if (iType == ASRL)
      {
         // Case 3A: No ASRL, no CAN and no PXI but other devices available
         if ((pTMP->iInternalType != ASRL) && (pTMP->iInternalType != CAN) && (pTMP->iInternalType != PXI))
         {
            pTMPnew->next = pTMP;
            pFirst = pTMPnew;
         }
         // Case 3B: ASRL and/or PXI and/or CAN available
         else if ((pTMP->iInternalType == ASRL) || (pTMP->iInternalType == CAN) || (pTMP->iInternalType == PXI))
         {
            while ((pTMP->iInternalType == PXI) && (pTMP->next != NULL))
            {
               pTMP = pTMP->next;
            }
            while ((pTMP->iInternalType == CAN) && (pTMP->next != NULL))
            {
               pTMP = pTMP->next;
            }
            while ((pTMP->iInternalType == ASRL) && (pTMP->next != NULL))
            {
               if (pTMP->next->iInternalType == GPIB)
               {
                  break;
               }
               pTMP = pTMP->next;
            }
            pTMPnew->next = pTMP->next;
            pTMP->next = pTMPnew;
         }
      }

      if (iType == GPIB)
      {
         // Case 4A: No GPIB, no ASRL, no CAN and no PXI but other devices available
         if ((pTMP->iInternalType != GPIB) && (pTMP->iInternalType != ASRL) && (pTMP->iInternalType != CAN) && (pTMP->iInternalType != PXI))
         {
            pTMPnew->next = pTMP;
            pFirst = pTMPnew;
         }
         // Case 4B: GPIB and/or ASRL and/or PXI and/or CAN available
         else if ((pTMP->iInternalType == GPIB) || (pTMP->iInternalType == ASRL) || (pTMP->iInternalType == CAN) || (pTMP->iInternalType == PXI))
         {
            while ((pTMP->iInternalType == PXI) && (pTMP->next != NULL))
            {
               pTMP = pTMP->next;
            }
            while ((pTMP->iInternalType == CAN) && (pTMP->next != NULL))
            {
               pTMP = pTMP->next;
            }
            while ((pTMP->iInternalType == ASRL) && (pTMP->next != NULL))
            {
               pTMP = pTMP->next;
            }
            while ((pTMP->iInternalType == GPIB) && (pTMP->next != NULL))
            {
               if (pTMP->next->iInternalType == DAQ)
               {
                  break;
               }
               pTMP = pTMP->next;
            }
            pTMPnew->next = pTMP->next;
            pTMP->next = pTMPnew;
         }
      }

      if (iType == DAQ)
      {
         // Case 5A: No DAQ, no GPIB, no ASRL, no CAN and no PXI but other devices available
         if ((pTMP->iInternalType != DAQ) && (pTMP->iInternalType != GPIB) && (pTMP->iInternalType != ASRL) && (pTMP->iInternalType != CAN) && (pTMP->iInternalType != PXI))
         {
            pTMPnew->next = pTMP;
            pFirst = pTMPnew;
         }
         // Case 5B: DAQ and/or GPIB and/or ASRL and/or PXI and/or CAN available
         else if ((pTMP->iInternalType == DAQ) || (pTMP->iInternalType == GPIB) || (pTMP->iInternalType == ASRL) || (pTMP->iInternalType == CAN) || (pTMP->iInternalType == PXI))
         {
            while (pTMP->next != NULL)
            {
               pTMP = pTMP->next;
            }
            pTMPnew->next = pTMP->next;
            pTMP->next = pTMPnew;
         }
      }
   }
   return pFirst;
}

/* FUNCTION *****************************************************************/
/**
CheckVendor
 *
@brief This function search in file /resources/vendor.txt for given vendor ID
and returns the company name
 *
@param vendorID: Value from config space of found devices
@param cVendor: Buffer which contain company name
 *
@return Error code
 *****************************************************************************/
int CheckVendor(int vendorID, char* cVendor)
{
   FILE* pVendorFile;
   char cPath[512];
   char cRead[512];
   char cFirstChar;
   int ID;
   int i;

   iError = 0;

   sprintf(cPath, "%s\\resources\\vendor.txt", cProjectDir);

   pVendorFile = fopen(cPath, "r");
   if (!pVendorFile)
   {
      MessagePopup("TG-ITS", "Konnte Vendor.txt nicht öffnen!");
      return  - 1;
   }

   while (!feof(pVendorFile))
   {
      fscanf(pVendorFile, "%x", &ID);
      cFirstChar = fgetc(pVendorFile);
      while (cFirstChar == ' ')
      {
         cFirstChar = fgetc(pVendorFile);
      }
      i = 0;
      while (cFirstChar != '\n')
      {
         cRead[i] = cFirstChar;
         cFirstChar = fgetc(pVendorFile);
         i++;
      }
      cRead[i] = '\0';
      if (ID == vendorID)
      {
         break;
      }
   }
   sprintf(cVendor, "%s", cRead);
   fclose(pVendorFile);
   return iError;
}

/* FUNCTION *****************************************************************/
/**
CheckNIBoards
 *
@brief This function search in file /resources/daqboards.txt for given board ID
and returns the product name
 *
@param GivenID: Value from config space of found devices
@param Type: Buffer which contain product name
 *
@return Error code
 *****************************************************************************/
int CheckNIBoards(int GivenID, char* Type)
{
   FILE* pBoardFile;
   char cPath[512];
   char cRead[512];
   char cFirstChar;
   int ID;
   int i;

   iError = 0;

   sprintf(cPath, "%s\\resources\\daqboards.txt", cProjectDir);

   pBoardFile = fopen(cPath, "r");
   if (!pBoardFile)
   {
      MessagePopup("TG-ITS", "Konnte daqboards.txt nicht öffnen!");
      return  - 1;
   }

   while (!feof(pBoardFile))
   {
      fscanf(pBoardFile, "%i", &ID);
      cFirstChar = fgetc(pBoardFile);
      while (cFirstChar == ' ')
      {
         cFirstChar = fgetc(pBoardFile);
      }
      i = 0;
      while ((cFirstChar != '\n') && (!feof(pBoardFile)))
      {
         cRead[i] = cFirstChar;
         cFirstChar = fgetc(pBoardFile);
         i++;
      }
      cRead[i] = '\0';
      if (ID == GivenID)
      {
         sprintf(Type, "%s", cRead);
         break;
      }
   }

   fclose(pBoardFile);
   return iError;
}

/* FUNCTION *****************************************************************/
/**
AppendSignsAndCR
 *
@brief This function append a string and a carriage return to another string
 *
@param Append: Destination buffer
@param ToAppend: Source buffer
 *
@return Destination buffer
 *****************************************************************************/
char* AppendSignsAndCR(char* Append, char* ToAppend)
{
   int i;
   int iLengthOld;
   int iLengthAppend;
   iLengthOld = strlen(Append);
   iLengthAppend = strlen(ToAppend);
   for (i = iLengthOld; i < (iLengthOld + iLengthAppend); i++)
   {
      Append[i] = ToAppend[i - iLengthOld];
   }
   Append[i] = '\0';
   iLengthOld = strlen(Append);
   Append[iLengthOld] = 13;
   Append[iLengthOld + 1] = '\0';
   return Append;
}

/* FUNCTION *****************************************************************/
/**
InsertMenuItems
 *
@brief This function insert all found devices into the menu bar
 *
@param void
 *
@return void
 *****************************************************************************/
void InsertMenuItems(void)
{
   int NewID;
   ressource* ptr;
   if (iDevicesFound)
   {
      if (iSub1ID)
      {
         DiscardMenu(iMenuHandle, iSub1ID);
      }
      iSub1ID = NewSubMenu(iMenuHandle, MENU_EDIT_EDIT);
      if (iSub1ID > 0)
      {
         ptr = pFirstRessource;
         if (ptr != NULL)
         {
            while (ptr)
            {
               sprintf(cMsgText, "%s - %s", ptr->cBenchName, ptr->cRessourceDesc);
               NewID = NewMenuItem(iMenuHandle, iSub1ID, cMsgText,  - 1, 0, EditRessource, 0);
               ptr->menuID = NewID;
               ptr = ptr->next;
            }
            SetMenuBarAttribute(iMenuHandle, MENU_EDIT_EDIT, ATTR_DIMMED, 0);
         }
         else
         {
            DiscardMenu(iMenuHandle, iSub1ID);
            iSub1ID = 0;
            SetMenuBarAttribute(iMenuHandle, MENU_EDIT_EDIT, ATTR_DIMMED, 1);
         }



      }
   }
}

/* FUNCTION *****************************************************************/
/**
HandleError
 *
@brief This function formats an error string and display a message popup
 *
@param pFuncName: Called function
@param iError: Error code
 *
@return void
 *****************************************************************************/
void HandleError(char* pFuncName, ViStatus iError)
{
   char ErrorString[128];

   Fmt(ErrorString, "%s< Function: %s, Errorcode: %d", pFuncName, iError);
   MessagePopup("TG-ITS", ErrorString);
}


/* FUNCTION *****************************************************************/
/**
MergeTextFile
 *
@brief This function merges all content of an text file into a given file
container
 *
@param fDestination: File pointer to desination file
@param cSourceFileName: File name of file that must be merged
 *
@return File pointer of given destination file
 *****************************************************************************/
FILE* MergeTextFile(FILE* fDestination, char* cSourceFileName)
{
   char cPath[MAX_PATHNAME_LEN];
   FILE* fSource;

   fSource = fopen(cSourceFileName, "rt");
   if (!fSource)
   {
      fclose(fDestination);
      iError = 1;
      return 0;
   }
   rewind(fSource);

   while (!feof(fSource))
   {
      fputc(fgetc(fSource), fDestination);
   }
   fclose(fSource);
   fseek(fDestination,  - 1L, SEEK_CUR);
   return fDestination;
}

/* FUNCTION *****************************************************************/
/**
MergeEncodedTextFile
 *
@brief This function decodes & merges all content of an encoded text file
into a given file container.
\n[code by Albert Killer]
 *
@param fDestination: File pointer to desination file
@param cSourceFileName: File name of file that must be merged
 *
@return File pointer of given destination file
 *****************************************************************************/
FILE* MergeEncodedTextFile(FILE* fDestination, char* cSourceFileName)
{
   char cPath[MAX_PATHNAME_LEN];
   char readChar, writeChar;
   char decodedChar = ' ';
   FILE* fSource;
   int i;

   char Bchstbn[55] =
   {
      'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '\n', ' ', '\0'
   };
   char Zeichen[55] =
   {
      'ü', 'ö', 'ä', 'Ü', 'Ö', 'Ä', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', 'ß', '!', '"', '§', '$', '%', '&', '/', '\\', '(', ')', '[', ']', '{', '}', '=', '?', '+', '*', '~', '#', '\'', ',', ';', '.', ':', '-', '_', '<', '>', '|', '^', '°', '²', '³', '@', '\t', ' ', '\0'
   };

   fSource = fopen(cSourceFileName, "rt");
   if (!fSource)
   {
      fclose(fDestination);
      iError = 1;
      return 0;
   }
   rewind(fSource);

   while (!feof(fSource))
   {
      readChar = fgetc(fSource);

      for (i = 0; i < 55; i++)
      {
         if (readChar == Bchstbn[i])
         {
            writeChar = Zeichen[i];
         }
         else if (readChar == Zeichen[i])
         {
            writeChar = Bchstbn[i];
         }
      }

      if (!feof(fSource))
      {
         fputc(writeChar, fDestination);
      }
   }
   fclose(fSource);
   fseek(fDestination,  - 1L, SEEK_CUR);
   return fDestination;
}

/* FUNCTION *****************************************************************/
/**
CheckBenchNames
 *
@brief This function checks all bench names
 *
@param void
 *
@return Error code
 *****************************************************************************/
int CheckBenchNames(void)
{
   ressource* pCompare;
   ressource* pActual;
   pActual = pFirstRessource;
   while (pActual)
   {
      pCompare = pActual->next;
      while (pCompare)
      {
         if (!strcmp(pCompare->cBenchName, pActual->cBenchName))
         {
            sprintf(cMsgText, "Cannot write physical layer.\n");
            strcat(cMsgText, "You cannot use the same bench name (");
            strcat(cMsgText, pCompare->cBenchName);
            strcat(cMsgText, ") for two devices!\n");
            strcat(cMsgText, pCompare->cRessourceDesc);
            strcat(cMsgText, " <-> ");
            strcat(cMsgText, pActual->cRessourceDesc);
            MessagePopup("TG-ITS", cMsgText);
            return  - 1;
         }
         pCompare = pCompare->next;
      }
      pActual = pActual->next;
   }
   return 0;
}

/* FUNCTION *****************************************************************/
/**
GetSlotNumber
 *
@brief This function checks all bench names
 *
@param cResourceDescriptor: CAN resource descriptor
 *
@return Slot number
 *****************************************************************************/
int GetSlotNumber(char* cResourceDescriptor)
{
   int idx;
   int idy;
   int iCount;
   int iLength;
   char cSlot[3];
   //Sample CAN0::0::1::12
   idx = 0;
   idy = 0;
   iCount = 0;
   iLength = strlen(cResourceDescriptor);
   while ((iCount != 6) && (idx < iLength))
   {
      if (cResourceDescriptor[idx] == ':')
      {
         iCount++;
      }
      idx++;
   }
   if ((iLength - idx) > 2)
   {
      return  - 1;
   }
   while (idx < iLength)
   {
      cSlot[idy] = cResourceDescriptor[idx];
      idx++;
      idy++;
   }
   cSlot[idy] = '\0';
   return atoi(cSlot);
}

/******************************************************************************/
// END OF FILE
