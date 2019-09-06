//========================================================================================
//  
//  $File: //depot/devtech/nevis/plugin/source/sdksamples/customactionfilter/CTMStartupShutDownResponder.cpp $
//  
//  Owner: Adobe Developer Technologies
//  
//  $Author: pmbuilder $
//  
//  $DateTime: 2017/09/11 07:38:03 $
//  
//  $Revision: #9 $
//  
//  $Change: 998069 $
//  
//  Copyright 1997-2010 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//========================================================================================

#include "VCPlugInHeaders.h"

// Interface includes:
#include "ISession.h"

// General includes:
#include "CPMUnknown.h"
#include "IApplication.h"
#include "IIntData.h"

// Project includes:
#include "BLID.h"
#include "IStartupShutdownService.h"

/** Implements IStartupShutdownService; purpose is to install the idle task.


@ingroup paneltreeview
*/
class CTMStartupShutDownResponder :
	public CPMUnknown<IStartupShutdownService>
{
public:
	/**	Constructor
	@param boss interface ptr from boss object on which this interface is aggregated.
	*/
	CTMStartupShutDownResponder(IPMUnknown* boss);

	/**	Destructor
	*/
	virtual ~CTMStartupShutDownResponder() {}

	/**	Called by the core when app is starting up
	*/
	virtual void Startup();

	/**	Called by the core when app is shutting down
	*/
	virtual void Shutdown();
};

/* CREATE_PMINTERFACE
Binds the C++ implementation class onto its ImplementationID
making the C++ code callable by the application.
*/
CREATE_PMINTERFACE(CTMStartupShutDownResponder, kTMStartupShutdownImpl)

/* Constructor
*/
CTMStartupShutDownResponder::CTMStartupShutDownResponder(IPMUnknown* boss) :
	CPMUnknown<IStartupShutdownService>(boss)
{
}


/* Startup
*/
void CTMStartupShutDownResponder::Startup()
{
	do
	{
		InterfacePtr<IApplication> iptrApplication(GetExecutionContextSession()->QueryApplication());
		if (iptrApplication == nil)
			break;
		InterfacePtr<IIntData>iptrScriptCount(iptrApplication, IID_ITMSCRIPTMANAGER);
		if(iptrScriptCount == nil)
			break;
		iptrScriptCount->Set(0);
	} while (kFalse);
}


/* Shutdown - clear the action map from memory
*/
void CTMStartupShutDownResponder::Shutdown()
{

}


