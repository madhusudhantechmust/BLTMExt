//========================================================================================
//  
//  $File: $
//  
//  Owner: TM
//  
//  $Author: $
//  
//  $DateTime: $
//  
//  $Revision: $
//  
//  $Change: $
//  
//  Copyright 1997-2012 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//========================================================================================


#ifndef __BLID_h__
#define __BLID_h__

#include "SDKDef.h"

// Company:
#define kBLCompanyKey	kSDKDefPlugInCompanyKey		// Company name used internally for menu paths and the like. Must be globally unique, only A-Z, 0-9, space and "_".
#define kBLCompanyValue	kSDKDefPlugInCompanyValue	// Company name displayed externally.

// Plug-in:
#define kBLPluginName	"BLTMExt"			// Name of this plug-in.
#define kBLPrefixNumber	0x167c00 		// Unique prefix number for this plug-in(*Must* be obtained from Adobe Developer Support).
#define kBLVersion		kSDKDefPluginVersionString						// Version of this plug-in (for the About Box).
#define kBLAuthor		"TM"					// Author of this plug-in (for the About Box).

// Plug-in Prefix: (please change kBLPrefixNumber above to modify the prefix.)
#define kBLPrefix		RezLong(kBLPrefixNumber)				// The unique numeric prefix for all object model IDs for this plug-in.
#define kBLStringPrefix	SDK_DEF_STRINGIZE(kBLPrefixNumber)	// The string equivalent of the unique prefix number for  this plug-in.

// Missing plug-in: (see ExtraPluginInfo resource)
#define kBLMissingPluginURLValue		kSDKDefPartnersStandardValue_enUS // URL displayed in Missing Plug-in dialog
#define kBLMissingPluginAlertValue	kSDKDefMissingPluginAlertValue // Message displayed in Missing Plug-in dialog - provide a string that instructs user how to solve their missing plug-in problem
#define kBlackLining_Prefix			RezLong(0xb5200) 
// PluginID:
DECLARE_PMID(kPlugInIDSpace, kBLPluginID, kBLPrefix + 0)

#define kBLTextAttrInsertedTextBoss kBlackLining_Prefix + 30
#define kBLTextAttrDeletedTextBoss kBlackLining_Prefix + 28
#define kHidTxtModelBoss kBlackLining_Prefix + 48

// ClassIDs:
DECLARE_PMID(kClassIDSpace, kBLScriptProviderBoss, kBLPrefix + 3)
//DECLARE_PMID(kClassIDSpace, kBLBoss, kBLPrefix + 4)
//DECLARE_PMID(kClassIDSpace, kBLBoss, kBLPrefix + 5)
//DECLARE_PMID(kClassIDSpace, kBLBoss, kBLPrefix + 6)
//DECLARE_PMID(kClassIDSpace, kBLBoss, kBLPrefix + 7)
//DECLARE_PMID(kClassIDSpace, kBLBoss, kBLPrefix + 8)
//DECLARE_PMID(kClassIDSpace, kBLBoss, kBLPrefix + 9)
//DECLARE_PMID(kClassIDSpace, kBLBoss, kBLPrefix + 10)
//DECLARE_PMID(kClassIDSpace, kBLBoss, kBLPrefix + 11)
//DECLARE_PMID(kClassIDSpace, kBLBoss, kBLPrefix + 12)
//DECLARE_PMID(kClassIDSpace, kBLBoss, kBLPrefix + 13)
//DECLARE_PMID(kClassIDSpace, kBLBoss, kBLPrefix + 14)
//DECLARE_PMID(kClassIDSpace, kBLBoss, kBLPrefix + 15)
//DECLARE_PMID(kClassIDSpace, kBLBoss, kBLPrefix + 16)
//DECLARE_PMID(kClassIDSpace, kBLBoss, kBLPrefix + 17)
//DECLARE_PMID(kClassIDSpace, kBLBoss, kBLPrefix + 18)
//DECLARE_PMID(kClassIDSpace, kBLBoss, kBLPrefix + 19)
//DECLARE_PMID(kClassIDSpace, kBLBoss, kBLPrefix + 20)
//DECLARE_PMID(kClassIDSpace, kBLBoss, kBLPrefix + 21)
//DECLARE_PMID(kClassIDSpace, kBLBoss, kBLPrefix + 22)
//DECLARE_PMID(kClassIDSpace, kBLBoss, kBLPrefix + 23)
//DECLARE_PMID(kClassIDSpace, kBLBoss, kBLPrefix + 24)
//DECLARE_PMID(kClassIDSpace, kBLBoss, kBLPrefix + 25)


// InterfaceIDs:
DECLARE_PMID(kInterfaceIDSpace, IID_ITMSCRIPTMANAGER, kBLPrefix + 0)
//DECLARE_PMID(kInterfaceIDSpace, IID_IBLINTERFACE, kBLPrefix + 1)
//DECLARE_PMID(kInterfaceIDSpace, IID_IBLINTERFACE, kBLPrefix + 2)
//DECLARE_PMID(kInterfaceIDSpace, IID_IBLINTERFACE, kBLPrefix + 3)
//DECLARE_PMID(kInterfaceIDSpace, IID_IBLINTERFACE, kBLPrefix + 4)
//DECLARE_PMID(kInterfaceIDSpace, IID_IBLINTERFACE, kBLPrefix + 5)
//DECLARE_PMID(kInterfaceIDSpace, IID_IBLINTERFACE, kBLPrefix + 6)
//DECLARE_PMID(kInterfaceIDSpace, IID_IBLINTERFACE, kBLPrefix + 7)
//DECLARE_PMID(kInterfaceIDSpace, IID_IBLINTERFACE, kBLPrefix + 8)
//DECLARE_PMID(kInterfaceIDSpace, IID_IBLINTERFACE, kBLPrefix + 9)
//DECLARE_PMID(kInterfaceIDSpace, IID_IBLINTERFACE, kBLPrefix + 10)
//DECLARE_PMID(kInterfaceIDSpace, IID_IBLINTERFACE, kBLPrefix + 11)
//DECLARE_PMID(kInterfaceIDSpace, IID_IBLINTERFACE, kBLPrefix + 12)
//DECLARE_PMID(kInterfaceIDSpace, IID_IBLINTERFACE, kBLPrefix + 13)
//DECLARE_PMID(kInterfaceIDSpace, IID_IBLINTERFACE, kBLPrefix + 14)
//DECLARE_PMID(kInterfaceIDSpace, IID_IBLINTERFACE, kBLPrefix + 15)
//DECLARE_PMID(kInterfaceIDSpace, IID_IBLINTERFACE, kBLPrefix + 16)
//DECLARE_PMID(kInterfaceIDSpace, IID_IBLINTERFACE, kBLPrefix + 17)
//DECLARE_PMID(kInterfaceIDSpace, IID_IBLINTERFACE, kBLPrefix + 18)
//DECLARE_PMID(kInterfaceIDSpace, IID_IBLINTERFACE, kBLPrefix + 19)
//DECLARE_PMID(kInterfaceIDSpace, IID_IBLINTERFACE, kBLPrefix + 20)
//DECLARE_PMID(kInterfaceIDSpace, IID_IBLINTERFACE, kBLPrefix + 21)
//DECLARE_PMID(kInterfaceIDSpace, IID_IBLINTERFACE, kBLPrefix + 22)
//DECLARE_PMID(kInterfaceIDSpace, IID_IBLINTERFACE, kBLPrefix + 23)
//DECLARE_PMID(kInterfaceIDSpace, IID_IBLINTERFACE, kBLPrefix + 24)
//DECLARE_PMID(kInterfaceIDSpace, IID_IBLINTERFACE, kBLPrefix + 25)


// ImplementationIDs:
DECLARE_PMID(kImplementationIDSpace, kBLScriptProviderImpl, kBLPrefix + 0)
DECLARE_PMID(kImplementationIDSpace, kTMStartupShutdownImpl, kBLPrefix + 1)
//DECLARE_PMID(kImplementationIDSpace, kBLImpl, kBLPrefix + 2)
//DECLARE_PMID(kImplementationIDSpace, kBLImpl, kBLPrefix + 3)
//DECLARE_PMID(kImplementationIDSpace, kBLImpl, kBLPrefix + 4)
//DECLARE_PMID(kImplementationIDSpace, kBLImpl, kBLPrefix + 5)
//DECLARE_PMID(kImplementationIDSpace, kBLImpl, kBLPrefix + 6)
//DECLARE_PMID(kImplementationIDSpace, kBLImpl, kBLPrefix + 7)
//DECLARE_PMID(kImplementationIDSpace, kBLImpl, kBLPrefix + 8)
//DECLARE_PMID(kImplementationIDSpace, kBLImpl, kBLPrefix + 9)
//DECLARE_PMID(kImplementationIDSpace, kBLImpl, kBLPrefix + 10)
//DECLARE_PMID(kImplementationIDSpace, kBLImpl, kBLPrefix + 11)
//DECLARE_PMID(kImplementationIDSpace, kBLImpl, kBLPrefix + 12)
//DECLARE_PMID(kImplementationIDSpace, kBLImpl, kBLPrefix + 13)
//DECLARE_PMID(kImplementationIDSpace, kBLImpl, kBLPrefix + 14)
//DECLARE_PMID(kImplementationIDSpace, kBLImpl, kBLPrefix + 15)
//DECLARE_PMID(kImplementationIDSpace, kBLImpl, kBLPrefix + 16)
//DECLARE_PMID(kImplementationIDSpace, kBLImpl, kBLPrefix + 17)
//DECLARE_PMID(kImplementationIDSpace, kBLImpl, kBLPrefix + 18)
//DECLARE_PMID(kImplementationIDSpace, kBLImpl, kBLPrefix + 19)
//DECLARE_PMID(kImplementationIDSpace, kBLImpl, kBLPrefix + 20)
//DECLARE_PMID(kImplementationIDSpace, kBLImpl, kBLPrefix + 21)
//DECLARE_PMID(kImplementationIDSpace, kBLImpl, kBLPrefix + 22)
//DECLARE_PMID(kImplementationIDSpace, kBLImpl, kBLPrefix + 23)
//DECLARE_PMID(kImplementationIDSpace, kBLImpl, kBLPrefix + 24)
//DECLARE_PMID(kImplementationIDSpace, kBLImpl, kBLPrefix + 25)


// ActionIDs:
DECLARE_PMID(kActionIDSpace, kBLAboutActionID, kBLPrefix + 0)
//DECLARE_PMID(kActionIDSpace, kBLActionID, kBLPrefix + 5)
//DECLARE_PMID(kActionIDSpace, kBLActionID, kBLPrefix + 6)
//DECLARE_PMID(kActionIDSpace, kBLActionID, kBLPrefix + 7)
//DECLARE_PMID(kActionIDSpace, kBLActionID, kBLPrefix + 8)
//DECLARE_PMID(kActionIDSpace, kBLActionID, kBLPrefix + 9)
//DECLARE_PMID(kActionIDSpace, kBLActionID, kBLPrefix + 10)
//DECLARE_PMID(kActionIDSpace, kBLActionID, kBLPrefix + 11)
//DECLARE_PMID(kActionIDSpace, kBLActionID, kBLPrefix + 12)
//DECLARE_PMID(kActionIDSpace, kBLActionID, kBLPrefix + 13)
//DECLARE_PMID(kActionIDSpace, kBLActionID, kBLPrefix + 14)
//DECLARE_PMID(kActionIDSpace, kBLActionID, kBLPrefix + 15)
//DECLARE_PMID(kActionIDSpace, kBLActionID, kBLPrefix + 16)
//DECLARE_PMID(kActionIDSpace, kBLActionID, kBLPrefix + 17)
//DECLARE_PMID(kActionIDSpace, kBLActionID, kBLPrefix + 18)
//DECLARE_PMID(kActionIDSpace, kBLActionID, kBLPrefix + 19)
//DECLARE_PMID(kActionIDSpace, kBLActionID, kBLPrefix + 20)
//DECLARE_PMID(kActionIDSpace, kBLActionID, kBLPrefix + 21)
//DECLARE_PMID(kActionIDSpace, kBLActionID, kBLPrefix + 22)
//DECLARE_PMID(kActionIDSpace, kBLActionID, kBLPrefix + 23)
//DECLARE_PMID(kActionIDSpace, kBLActionID, kBLPrefix + 24)
//DECLARE_PMID(kActionIDSpace, kBLActionID, kBLPrefix + 25)


// WidgetIDs:
//DECLARE_PMID(kWidgetIDSpace, kBLWidgetID, kBLPrefix + 2)
//DECLARE_PMID(kWidgetIDSpace, kBLWidgetID, kBLPrefix + 3)
//DECLARE_PMID(kWidgetIDSpace, kBLWidgetID, kBLPrefix + 4)
//DECLARE_PMID(kWidgetIDSpace, kBLWidgetID, kBLPrefix + 5)
//DECLARE_PMID(kWidgetIDSpace, kBLWidgetID, kBLPrefix + 6)
//DECLARE_PMID(kWidgetIDSpace, kBLWidgetID, kBLPrefix + 7)
//DECLARE_PMID(kWidgetIDSpace, kBLWidgetID, kBLPrefix + 8)
//DECLARE_PMID(kWidgetIDSpace, kBLWidgetID, kBLPrefix + 9)
//DECLARE_PMID(kWidgetIDSpace, kBLWidgetID, kBLPrefix + 10)
//DECLARE_PMID(kWidgetIDSpace, kBLWidgetID, kBLPrefix + 11)
//DECLARE_PMID(kWidgetIDSpace, kBLWidgetID, kBLPrefix + 12)
//DECLARE_PMID(kWidgetIDSpace, kBLWidgetID, kBLPrefix + 13)
//DECLARE_PMID(kWidgetIDSpace, kBLWidgetID, kBLPrefix + 14)
//DECLARE_PMID(kWidgetIDSpace, kBLWidgetID, kBLPrefix + 15)
//DECLARE_PMID(kWidgetIDSpace, kBLWidgetID, kBLPrefix + 16)
//DECLARE_PMID(kWidgetIDSpace, kBLWidgetID, kBLPrefix + 17)
//DECLARE_PMID(kWidgetIDSpace, kBLWidgetID, kBLPrefix + 18)
//DECLARE_PMID(kWidgetIDSpace, kBLWidgetID, kBLPrefix + 19)
//DECLARE_PMID(kWidgetIDSpace, kBLWidgetID, kBLPrefix + 20)
//DECLARE_PMID(kWidgetIDSpace, kBLWidgetID, kBLPrefix + 21)
//DECLARE_PMID(kWidgetIDSpace, kBLWidgetID, kBLPrefix + 22)
//DECLARE_PMID(kWidgetIDSpace, kBLWidgetID, kBLPrefix + 23)
//DECLARE_PMID(kWidgetIDSpace, kBLWidgetID, kBLPrefix + 24)
//DECLARE_PMID(kWidgetIDSpace, kBLWidgetID, kBLPrefix + 25)

// ScriptElementIDs:
DECLARE_PMID(kScriptInfoIDSpace, kPropertyContainsInsertionScriptElement, kBLPrefix + 0)
DECLARE_PMID(kScriptInfoIDSpace, kPropertyContainsDeletionScriptElement, kBLPrefix + 1)

// "About Plug-ins" sub-menu:
#define kBLAboutMenuKey			kBLStringPrefix "kBLAboutMenuKey"
#define kBLAboutMenuPath		kSDKDefStandardAboutMenuPath kBLCompanyKey

// "Plug-ins" sub-menu:
#define kBLPluginsMenuKey 		kBLStringPrefix "kBLPluginsMenuKey"
#define kBLPluginsMenuPath		kSDKDefPlugInsStandardMenuPath kBLCompanyKey kSDKDefDelimitMenuPath kBLPluginsMenuKey

// Menu item keys:

// Other StringKeys:
#define kBLAboutBoxStringKey	kBLStringPrefix "kBLAboutBoxStringKey"
#define kBLTargetMenuPath kBLPluginsMenuPath

// Menu item positions:


// Initial data format version numbers
#define kBLFirstMajorFormatNumber  RezLong(1)
#define kBLFirstMinorFormatNumber  RezLong(0)

// Data format version numbers for the PluginVersion resource 
#define kBLCurrentMajorFormatNumber kBLFirstMajorFormatNumber
#define kBLCurrentMinorFormatNumber kBLFirstMinorFormatNumber

enum ScriptPropertyIDs
{
	// Text Variables
	p_ContainsInsertion = 'ADef',
	p_ContainsDeletion = 'ADeg',
};
#endif // __BLID_h__
