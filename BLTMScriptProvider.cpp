//========================================================================================
//  
//  $File: //depot/devtech/nevis/plugin/source/sdksamples/basicshape/BLScriptProvider.cpp $
//  
//  Owner: Adobe Developer Technologies
//  
//  $Author: pmbuilder $
//  
//  $DateTime: 2016/09/30 00:23:18 $
//  
//  $Revision: #7 $
//  
//  $Change: 964874 $
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
#include "IScript.h"
#include "IScriptRequestData.h"
#include "IScriptObjectParent.h"
#include "IPageItemScriptUtils.h"
#include "INewPageItemCmdData.h"
#include "IPathUtils.h"
#include "IPageItemTypeUtils.h"
#include "IMultiColumnTextFrame.h"
#include "ITextScriptUtils.h"
#include "TextScriptID.h"
#include "ITextModel.h"
#include "ICommand.h"
#include "ITextModel.h"
#include "ITextTarget.h"
#include "TextIterator.h"
#include "TextAttributeRunIterator.h"

// Implementation includes:
#include "CmdUtils.h"
#include "CAlert.h"
#include "CScriptProvider.h"
#include "IDOMElement.h"

// Project includes:
#include "BLID.h"
#include "ITextScriptUtils.h"
#include "ITextAttributeSuite.h"
#include "IApplication.h"
#include "IIntData.h"
#include "Logger.h"
#include "OwnedItemDataList.h"
#include "IItemStrand.h"
#include "PersistRealNumberData.h"
#include "ITextAttrInt32.h"

/** From SDK sample; shows how to implement a script provider for a custom page item,
kBscShpPageItemBoss.

See Scripting Resources defined in the plug-in's .fr file.

@see kBscShpPageItemBoss - the scriptable boss
@see kBasicShapeObjectScriptElement - the script object that exposes kBscShpPageItemBoss in the Scripting DOM
@see BscShp.fr
@see IPageItemScriptUtils
@ingroup basicshape
*/
class BLScriptProvider : public RepresentScriptProvider
{
public:
	/** Constructor
	@param boss the boss object this interface is aggregated onto
	*/
	BLScriptProvider(IPMUnknown *boss);

	/** Destructor.
	*/
	virtual ~BLScriptProvider();

	/** Called if a provider can handle a method/event.
	@param methodID identifies the ID of the method/event to handle.
	@param data identifies an interface pointer used to extract data.
	@param script identifies an interface pointer on the script object representing the parent of the application object.
	*/
	virtual ErrorCode	HandleMethod(ScriptID methodID, IScriptRequestData* data, IScript* script);

	/** Called if a provider can access a property.
	@param propID identifies the property ID.
	@param data identifies an interface pointer used to extract data.
	@param script identifies an interface pointer on the script object representing.
	*/
	virtual ErrorCode	AccessProperty(ScriptID propID, IScriptRequestData* data, IScript* script);

protected:
	/**	Get the number of child objects in a collection on the given parent.
	@param data IN identifies the type of child object.
	@param parent IN references the owner of the collection.
	@return the number of child objects.
	*/
	virtual int32		GetNumObjects(const IScriptRequestData* data, IScript* parent);

	/**	Append the nth child object from a collection on the given parent.
	@param data IN identifies the type of child object.
	@param parent IN references the owner of the collection.
	@param n IN the index (0-based) of the desired child object in the collection.
	@param objectList OUT the nth child gets added to this list
	@return kSuccess on success, other ErrorCode otherwise.
	*/
	virtual ErrorCode	AppendNthObject(const IScriptRequestData* data, IScript* parent, int32 n, ScriptList& objectList);

	/**	Append all child objects in a collection on the given parent.
	n is a 0-based index.
	@param data IN identifies the type of child object.
	@param parent IN references the owner of the collection.
	@param objectList OUT the objects in the collection.
	@return kSuccess on success, other ErrorCode otherwise.
	*/
	virtual ErrorCode	AppendAllObjects(const IScriptRequestData* data, IScript* parent, ScriptList& objectList);

private:
	ErrorCode AccessInsertion(IScriptRequestData*data, IScript*script);
	ErrorCode AccessDeletion(IScriptRequestData*poData, IScript* poScript);
	int32  GetCallCount();
	PMString GetText(IScript* poScript, RangeData oRangeData);
	void IterateInsertedText(IScript* poScript, RangeData oRangeData);
	bool16 IsDeletionAnchored(IScript* poScript, RangeData oRangeData);
	int32 GetRevisionNumber(InterfacePtr<ITextAttributeSuite>& iptrTextAttributeSuite, int32 nAttribCount, ClassID tClassID);
};

/* Makes the implementation available to the application.
*/
CREATE_PMINTERFACE(BLScriptProvider, kBLScriptProviderImpl)

/*
*/
BLScriptProvider::BLScriptProvider(IPMUnknown *boss) :
	RepresentScriptProvider(boss)
{
}

/*
*/
BLScriptProvider::~BLScriptProvider()
{
}

/*
*/
int32 BLScriptProvider::GetNumObjects(const IScriptRequestData* data, IScript* parent)
{
	return Utils<IPageItemScriptUtils>()->CountPageItemChildren(parent, data);
}

/*
*/
ErrorCode BLScriptProvider::AppendNthObject(const IScriptRequestData* data, IScript* parent, int32 n, ScriptList& objectList)	//0-based index
{
	return Utils<IPageItemScriptUtils>()->GetNthPageItemChild(n, parent, data, objectList);
}

/*
*/
ErrorCode BLScriptProvider::AppendAllObjects(const IScriptRequestData* data, IScript* parent, ScriptList& objectList)
{
	return Utils<IPageItemScriptUtils>()->GetEveryPageItemChild(parent, data, objectList);
}

/*
*/
ErrorCode BLScriptProvider::HandleMethod(ScriptID methodID, IScriptRequestData* data, IScript* script)
{
	return RepresentScriptProvider::HandleMethod(methodID, data, script);
}

ErrorCode BLScriptProvider::AccessProperty(ScriptID propID, IScriptRequestData* data, IScript* script)
{
	switch (propID.Get())
	{
	case p_ContainsInsertion:
		return AccessInsertion(data, script);
	case p_ContainsDeletion:
		return AccessDeletion(data, script);
	default:
		return RepresentScriptProvider::AccessProperty(propID, data, script);
	}

}

ErrorCode BLScriptProvider::AccessInsertion(IScriptRequestData*poData, IScript* poScript)
{
	ErrorCode tResult = kFailure;
	bool16 bContainsInsertion = kFalse;
	do
	{
		if (poData->IsPropertyGet())
		{
			int32 nAttributeCount = 0;
			RangeData oRangeData = Utils<ITextScriptUtils>()->GetScriptTextRange(poScript);
			PMString strRange = "Start : ";
			strRange.AppendNumber(oRangeData.Start(nil));
			strRange.Append(" End :");
			strRange.AppendNumber(oRangeData.End());
			Logger::Info("BLScriptProvider", "AccessInsertion", "RangeData : " + strRange.GetPlatformString());
			PMString strText = GetText(poScript, oRangeData);
			Logger::Info("BLScriptProvider", "AccessInsertion", "Script TextContent : " + strText.GetPlatformString());
			InterfacePtr<ITextAttributeSuite> iptrTextAttributeSuite(poScript, UseDefaultIID());
			if (iptrTextAttributeSuite == nil)
				break;
			nAttributeCount = iptrTextAttributeSuite->CountAttributes(kBLTextAttrInsertedTextBoss);
			PMString strAttribCount = "";
			strAttribCount.AppendNumber(nAttributeCount);
			Logger::Info("BLScriptProvider", "AccessInsertion", "Insert Attribute Count : " + strAttribCount.GetPlatformString());
			if (iptrTextAttributeSuite->CountAttributes(kBLTextAttrInsertedTextBoss) <= 0)
				break;
			int32 nRevision = -1;
			nRevision = GetRevisionNumber(iptrTextAttributeSuite, iptrTextAttributeSuite->CountAttributes(kBLTextAttrInsertedTextBoss), kBLTextAttrInsertedTextBoss);

			PMString strRevisionNo = "";
			strRevisionNo.AppendNumber(nRevision);
			Logger::Info("BLScriptProvider", "AccessInsertion", "Insert revision number : " + strRevisionNo.GetPlatformString());
			bContainsInsertion = nRevision > 0;
		}
	} while (kFalse);
	ScriptData oReturnData;
	oReturnData.SetBoolean(bContainsInsertion);
	poData->AppendReturnData(poScript, p_ParentStory, oReturnData);
	PMString strResult = "false";
	if (bContainsInsertion)
		strResult = "true";
	Logger::Info("BLScriptProvider", "AccessInsertion", "Result : " + strResult.GetPlatformString());
	tResult = kSuccess;
	return tResult;
}

void BLScriptProvider::IterateInsertedText(IScript* poScript, RangeData oRangeData)
{
	do
	{
		InterfacePtr<IScriptObjectParent>iptrScriptParent(poScript, UseDefaultIID());
		if (iptrScriptParent == nil)
			break;
		InterfacePtr<ITextModel>iptrTextModel((ITextModel*)iptrScriptParent->QueryParent(IID_ITEXTMODEL));
		if (iptrTextModel == nil)
			break;
		RangeData::Lean tLean = RangeData::kLeanForward;
		InDesign::TextRange tTextRange(iptrTextModel, oRangeData.Start(nil), oRangeData.Length(), tLean);
		K2Vector<InDesign::TextRange> arrTextRanges;
		arrTextRanges.push_back(tTextRange);
		K2Vector<ClassID> AttrClasses;
		AttrClasses.push_back(kBLTextAttrInsertedTextBoss);
		TextAttributeRunIterator runIterator(arrTextRanges.begin(), arrTextRanges.end(), AttrClasses.begin(), AttrClasses.end());
		while (runIterator)
		{
			RangeData oRunRangeData = runIterator.GetRunRange();
			PMString strText = GetText(poScript, oRunRangeData);
			Logger::Info("BLScriptProvider", "AccessInsertion", "Inserted Text Content : " + strText.GetPlatformString());
		}
	} while (kFalse);
}

int32  BLScriptProvider::GetCallCount()
{
	int32 nCount = 0;
	do
	{
		InterfacePtr<IApplication> iptrApplication(GetExecutionContextSession()->QueryApplication());
		if (iptrApplication == nil)
			break;
		InterfacePtr<IIntData>iptrScriptCount(iptrApplication, IID_ITMSCRIPTMANAGER);
		if (iptrScriptCount == nil)
			break;
		nCount = iptrScriptCount->Get();
		iptrScriptCount->Set(nCount + 1);
	} while (kFalse);
	return nCount;
}

PMString BLScriptProvider::GetText(IScript* poScript, RangeData oRangeData)
{
	PMString strText = "";
	do
	{
		InterfacePtr<ITextTarget>iptrTextTarget(poScript, UseDefaultIID());
		if (iptrTextTarget == nil)
			break;
		InterfacePtr<ITextModel>iptrTextModel((ITextModel*)iptrTextTarget->QueryTextModel());
		if (iptrTextModel == nil)
			break;
		WideString strContent("");
		TextIterator oTextIterator(iptrTextModel, oRangeData.Start(nil));
		int32 nLength = oRangeData.Length();
		oTextIterator.AppendToStringAndIncrement(&strContent, nLength);
		strContent.GetSystemString(&strText);
	} while (kFalse);
	return strText;
}

ErrorCode BLScriptProvider::AccessDeletion(IScriptRequestData*poData, IScript* poScript)
{
	ErrorCode tResult = kFailure;
	bool16 bContainsDeletion = kFalse;
	do
	{
		if (poData->IsPropertyGet())
		{
			int32 nAttributeCount = 0;
			RangeData oRangeData = Utils<ITextScriptUtils>()->GetScriptTextRange(poScript);
			PMString strRange = "Start : ";
			strRange.AppendNumber(oRangeData.Start(nil));
			strRange.Append(" End :");
			strRange.AppendNumber(oRangeData.End());
			Logger::Info("BLScriptProvider", "AccessDeletion", "RangeData : " + strRange.GetPlatformString());
			PMString strText = GetText(poScript, oRangeData);
			Logger::Info("BLScriptProvider", "AccessDeletion", "Script TextContent : " + strText.GetPlatformString());
			InterfacePtr<ITextAttributeSuite> iptrTextAttributeSuite(poScript, UseDefaultIID());
			if (iptrTextAttributeSuite == nil)
				break;
			nAttributeCount = iptrTextAttributeSuite->CountAttributes(kBLTextAttrDeletedTextBoss);
			PMString strAttribCount = "";
			strAttribCount.AppendNumber(nAttributeCount);
			Logger::Info("BLScriptProvider", "AccessDeletion", "Strike thru Attribute Count : " + strAttribCount.GetPlatformString());
			int32 nRevision = -1;
			if (iptrTextAttributeSuite->CountAttributes(kBLTextAttrDeletedTextBoss) > 0)
				nRevision = GetRevisionNumber(iptrTextAttributeSuite, iptrTextAttributeSuite->CountAttributes(kBLTextAttrDeletedTextBoss), kBLTextAttrDeletedTextBoss);
			PMString strRevisionNo = "";
			strRevisionNo.AppendNumber(nRevision);
			Logger::Info("BLScriptProvider", "AccessDeletion", "Strike thru revision number : " + strRevisionNo.GetPlatformString());
			bContainsDeletion = nRevision > 0;
			if (!bContainsDeletion)
				bContainsDeletion = IsDeletionAnchored(poScript, oRangeData);
		}
	} while (kFalse);
	ScriptData oReturnData;
	oReturnData.SetBoolean(bContainsDeletion);
	poData->AppendReturnData(poScript, p_ParentStory, oReturnData);
	PMString strResult = "false";
	if (bContainsDeletion)
		strResult = "true";
	Logger::Info("BLScriptProvider", "AccessDeletion", "Result : " + strResult.GetPlatformString());
	tResult = kSuccess;
	return tResult;
}

bool16 BLScriptProvider::IsDeletionAnchored(IScript* poScript, RangeData oRangeData)
{
	bool16 bContainsHiddenText = kFalse;
	do
	{
		InterfacePtr<ITextTarget>iptrTextTarget(poScript, UseDefaultIID());
		if (iptrTextTarget == nil)
			break;
		InterfacePtr<ITextModel>iptrTextModel((ITextModel*)iptrTextTarget->QueryTextModel());
		if (iptrTextModel == nil)
			break;
		InterfacePtr<IItemStrand> iptrItemStrand(static_cast<IItemStrand*>(iptrTextModel->QueryStrand(kOwnedItemStrandBoss, IItemStrand::kDefaultIID)));
		if (iptrItemStrand == nil)
			break;
		UIDRef tStrandUIDRef = ::GetUIDRef(iptrItemStrand);
		OwnedItemDataList tOwnedItemDataList;
		bool16 bShowText = kFalse;
		iptrItemStrand->CollectOwnedItems(oRangeData.Start(nil), oRangeData.Length(), &tOwnedItemDataList);
		if (tOwnedItemDataList.Length() <= 0)
			break;
		TextIndex tTextIndex;
		for (int32 nIndex = 0; !bContainsHiddenText && nIndex < tOwnedItemDataList.Length(); nIndex++)
		{
			OwnedItemData tOwnedItemData = tOwnedItemDataList[nIndex];
			UID tUID = tOwnedItemData.fUID;
			tTextIndex = tOwnedItemData.fAt;
			PMReal nDeletedRevisionNo = -1;
			UID tOwnedUid = iptrItemStrand->GetOwnedUID(tTextIndex, kHidTxtModelBoss);
			bContainsHiddenText = tOwnedUid != kInvalidUID;
		}
	} while (kFalse);
	PMString strResult = "false";
	if (bContainsHiddenText)
		strResult = "true";
	Logger::Info("BLScriptProvider", "IsDeletionAnchored", "Result : " + strResult.GetPlatformString());
	return bContainsHiddenText;
}

int32 BLScriptProvider::GetRevisionNumber(InterfacePtr<ITextAttributeSuite>& iptrTextAttributeSuite, int32 nAttribCount, ClassID tClassID)
{
	int32 nRevision = -1;
	Logger::Info("BLScriptProvider", "GetRevisionNumber", "");
	for (int32 nIndex = 0; nRevision <= 0 && nIndex < nAttribCount; nIndex++)
	{
		InterfacePtr<const ITextAttrInt32> iptrTextAttrInt32(static_cast<const ITextAttrInt32*>(iptrTextAttributeSuite->QueryAttributeN(nIndex, tClassID, ITextAttrInt32::kDefaultIID)));
		if (iptrTextAttrInt32)
			nRevision = iptrTextAttrInt32->GetInt32();
	}
	return nRevision;
}
// End, BLScriptProvider.cpp.
