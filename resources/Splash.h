/**************************************************************************/
/* LabWindows/CVI User Interface Resource (UIR) Include File              */
/* Copyright (c) National Instruments 2011. All Rights Reserved.          */
/*                                                                        */
/* WARNING: Do not add to, delete from, or otherwise modify the contents  */
/*          of this include file.                                         */
/**************************************************************************/

#include <userint.h>

#ifdef __cplusplus
    extern "C" {
#endif

     /* Panels and Controls: */

#define  SPLASH                           1       /* callback function: SlpashCallBack */
#define  SPLASH_PICTURE                   2       /* callback function: PictureCallBack */
#define  SPLASH_SELECTEDSEQ               3       /* callback function: PictureCallBack */
#define  SPLASH_LABEL                     4       /* callback function: PictureCallBack */
#define  SPLASH_PRODUCT                   5       /* callback function: PictureCallBack */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */ 

int  CVICALLBACK PictureCallBack(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK SlpashCallBack(int panel, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
