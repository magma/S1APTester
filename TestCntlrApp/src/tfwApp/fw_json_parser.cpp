/* header include files -- defines (.h) */
#include <json/json.h>
#include <string>
#include <unordered_map>
#include <forward_list>

#include "envopt.h"        /* environment options */
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */
#include "gen.h"           /* general */
#include "ssi.h"           /* system services */
#include "cm_hash.h"       /* common hashing */
#include "cm_llist.h"      /* common linked list */
#include "cm_mblk.h"       /* common  */
#include "cm5.h"           /* common timer */
#include "cm_tpt.h"        /* common transport defines */
#include "cm_inet.h"       /* common sockets */
#include "cm_dns.h"        /* common DNS Library */
#include "ss_queue.h"      /* queues */
#include "ss_task.h"       /* tasking */
#include "ss_msg.h"        /* messaging */
#include "ss_mem.h"        /* memory management interface */
#include "ss_gen.h"        /* general */
#include "rl_interface.h"
#include "rl_common.h"
#include "lfw.h"
#include "uet.h"
#include "nbu.h"
#include "fw.h"

#include "gen.x"           /* general */
#include "ssi.x"           /* system services */
#include "cm_hash.x"       /* common hashing */
#include "cm_llist.x"      /* common linked list */
#include "cm_lib.x"        /* common library */
#include "cm5.x"           /* common timer */
#include "cm_tpt.x"        /* common transport typedefs */
#include "cm_inet.x"       /* common sockets */
#include "cm_mblk.x"       /* common blk memory */
#include "cm_dns.x"        /* common DNS Library */
#include "ss_queue.x"      /* queues */
#include "ss_task.x"       /* tasking */
#include "ss_timer.x"      /* timers */
#include "ss_strm.x"       /* STREAMS */
#include "ss_msg.x"        /* messaging */
#include "ss_mem.x"        /* memory management interface */
#include "ss_drvr.x"       /* driver tasks */
#include "ss_gen.x"        /* general */
#include "uet.x"
#include "nbu.x"
#include "fw_read_dflcfg.h"
#include "fw.x"
#include "fw_log.h"

using namespace std;

EXTERN FwCb gfwCb;

#include "fw_json_parser.h"

/**< Function to un-bind Json Array type. */
PRIVATE BaseObj* unBindJsonArray(Json::Value);
/**< Function to unbind Json object type. */
PRIVATE BaseObj* unBindJsonObj(Json::Value);
PRIVATE Json::Value bindObjType(ObjectValue*);
PRIVATE Json::Value bindStringArrayType(ArrayValue *obj);

/**
 * @brief    Method to get json object type.
 *
 * @details This function returns the object type.
 *
 * @return  jsonObjType
 */
jsonObjType BaseObj :: getJsonObjType(void)
{
   return this->objType;
}

/**
 * @brief    Method to set json object type.
 *
 * @details This function used to set the object type.
 *
 * @param[in][in] type : jsonObjType.
 *
 * @return  VOID
 */
void  BaseObj :: setjsonObjType(jsonObjType type)
{
   this->objType = type;
}

/**
 * @brief   Constructor for ObjectValue
 *
 * @details This is constructor for ObjectValue
 *
 * @return  VOID
 */
ObjectValue :: ObjectValue()
{
   objName.clear();
   tagValueEntries.clear();
   setjsonObjType(JSON_SIMPLE_TYPE);
}

/**
 * @brief  Destructor for ObjectValue
 *
 * @details This function is used to free the memory allocated to its member 
 *          variables.
 *
 */
ObjectValue :: ~ObjectValue()
{
   objName.clear();
   tagValueEntries.clear();
   for(U16 cnt = 0; cnt < objList.size(); cnt++)
   {
      jsonObjType type = ((BaseObj *)objList[cnt])->getJsonObjType();
      if(type == JSON_OBJ_TYPE || type == JSON_SIMPLE_TYPE)
      {
         ObjectValue *obj = (ObjectValue *)objList[cnt];
         delete obj;
      }
      else if(type == JSON_ARRAY_TYPE)
      {
         ArrayValue *arrObj = (ArrayValue *)objList[cnt];
         delete arrObj;
      }
   }
}

/**
 * @brief   Constructor for ArrayValue
 *
 * @details This is constructor for ArrayValue
 *
 * @return  VOID
 */
ArrayValue :: ArrayValue()
{
   arrName.clear();
   strList.clear();
   setjsonObjType(JSON_ARRAY_TYPE);
}

/**
 * @brief  Destructor for ArrayValue
 *
 * @details This function is used to free the memory allocated to its member 
 *          variables.
 *
 */
ArrayValue :: ~ArrayValue()
{
   arrName.clear();
   strList.clear();
   for(U16 cnt = 0; cnt < objList.size(); cnt++)
   {
      jsonObjType type = ((BaseObj *)objList[cnt])->getJsonObjType();
      if(type == JSON_OBJ_TYPE || type == JSON_SIMPLE_TYPE)
      {
         ObjectValue *obj = (ObjectValue *)objList[cnt];
         delete obj;
      }
      else if(type == JSON_ARRAY_TYPE)
      {
         ArrayValue *arrObj = (ArrayValue *)objList[cnt];
         delete arrObj;
      }
   }
}
/**
 * @brief    Method to set tagname and tagvalues.
 *
 * @details Method to set tagname and tagvalues of tagValuePair class members.
 *
 * @param[in][in] tagName  : string.
 * @param[in][in] tagValue : string.
 *
 * @return  VOID
 */
void tagValuePair :: setTagValues(const string tagName, const string tagValue)
{
   this->name = tagName;
   this->value = tagValue;
}

/**
 * @brief    Method to get tagname.
 *
 * @details Method to get tagname of tagValuePair object.
 *
 * @return  string - tagname.
 */
string tagValuePair :: getTagName(void)
{
   return this->name;
}

/**
 * @brief    Method to get tagvalue.
 *
 * @details Method to get tagvalue of tagValuePair object.
 *
 * @return  string - tagvalue.
 */
string tagValuePair :: getTagValue(void)
{
   return this->value;
}

/**
 * @brief    Method to set object name.
 *
 * @details Method to set object name of ObjectValue type object.
 *
 * @param[in][in] objname : string
 *
 * @return  VOID
 */
void ObjectValue :: setObjName(string objname)
{
   this->objName = objname;
}

/**
 * @brief    Method to insert tag-value-pair.
 *
 * @details Method to insert tagValuePair object into vector in ObjectValue.
 *
 * @param[in][in] tagVal : Reference to tagValuePair object.
 *
 * @return  VOID
 */
void ObjectValue :: pushTagValEntry(tagValuePair &tagVal)
{
   this->tagValueEntries.push_back(tagVal);
}

/**
 * @brief    Method to insert an object.
 *
 * @details Method to insert an object into vector in ObjectValue.
 *
 * @param[in][in] obj : Pointer to BaseObj type.
 *
 * @return  VOID
 */
void ObjectValue :: pushObject(BaseObj *obj)
{
   this->objList.push_back(obj);
}

/**
 * @brief    Method to get json object name.
 *
 * @details
 *
 * @return  string - json object name.
 */
string ObjectValue :: getObjName()
{
   return this->objName;
}

/**
 * @brief    Method to get number of entries in objList vector.
 *
 * @details
 *
 * @return  S16 - number of entries.
 */
U16 ObjectValue :: getNumOfEntriesInObjList(void)
{
   return this->objList.size();
}

/**
 * @brief    Method to get number of entries in tagValueEntries vector.
 *
 * @details
 *
 * @return  S16 - number of entries.
 */
U16 ObjectValue :: getNumOfEntriesInTagValList(void)
{
   return this->tagValueEntries.size();
}

/**
 * @brief    Method to get a tagValuePair entry in tagValuePair vector a at 
 *           index
 *
 * @details
 *
 * @param[in][in] indx : integer
 *
 * @return tagValuePair object.
 */
tagValuePair ObjectValue :: getTagValEntry(U16 indx)
{
   FwCb *fwCb = NULLP;
   FW_GET_CB(fwCb);
   FW_LOG_ENTERFN(fwCb);

   if(indx > tagValueEntries.size())
      FW_LOG_ERROR(fwCb, "Referring a bad Index");
   return this->tagValueEntries[indx];
}

/**
 * @brief    Method to get an entry in objList vector at a index
 *
 * @details
 *
 * @param[in][in] indx : integer
 *
 * @return BaseObj object pointer.
 */
BaseObj* ObjectValue :: getObj(U16 indx)
{
   return this->objList[indx];
}

/**
 * @brief    Method to create and insert a tagValuePair object into ObjectValue.
 *
 * @details
 *
 * @param[in][in] tagName : string.
 * @param[in][in] value   : string.
 *
 * @return VOID
 */
void ObjectValue :: pushTagValuePair(string attrName, string value)
{
   tagValuePair obj;
   obj.setTagValues(attrName, value);

   this->objType = JSON_OBJ_TYPE;
   this->tagValueEntries.push_back(obj);
}

/**
 * @brief    Method to set array name.
 *
 * @details Method to set json array name of ArrayValue type object.
 *
 * @param[in][in] name : string
 *
 * @return  VOID
 */
void ArrayValue :: setArrName(string &name)
{
   this->arrName = name;
}

/**
 * @brief    Method to insert a string into strList of ArrayValue object.
 *
 * @details
 *
 * @param[in][in] str : string.
 *
 * @return VOID
 */
void ArrayValue :: pushString(string str)
{
   this->strList.push_back(str);
}

/**
 * @brief    Method to insert an object.
 *
 * @details Method to insert an object into vector in ArrayValue.
 *
 * @param[in][in] obj : Pointer to BaseObj type.
 *
 * @return  VOID
 */
void ArrayValue :: pushObject(BaseObj *obj)
{
   this->objList.push_back(obj);
}

/**
 * @brief    Method to get array name ArrayValue type object.
 *
 * @details
 *
 * @return  string - json array name.
 */
string ArrayValue :: getArrName(void)
{
   return this->arrName;
}

/**
 * @brief    Method to get number of entries in strList list in ArrayValue 
 *           object.
 *
 * @details
 *
 * @return  S16 - number of entries.
 */
U16 ArrayValue :: getNumOfEntriesInStrList(void)
{
   return this->strList.size();
}

/**
 * @brief    Method to get number of entries in objList list.
 *
 * @details
 *
 * @return  S16 - number of entries.
 */
U16 ArrayValue :: getNumOfEntriesInObjList(void)
{
   return this->objList.size();
}

/**
 * @brief    Method to get string from list strList in ArrayValue type object 
 *           at input parameter index.
 *
 * @details
 *
 * @param[in][in] indx : Integer.
 *
 * @return  string - string from strList.
 */
string ArrayValue :: getString(U16 indx)
{
   return this->strList[indx];
}

/**
 * @brief    Method to get object from vector objList in ArrayValue object at a
 *           index.
 *
 * @details
 *
 * @param[in][in] BaseObj*  : Pointer to BaseObj.
 *
 * @return  string - string from strList.
 */
BaseObj* ArrayValue :: getObj(U16 indx)
{
   return this->objList[indx];
}

/**
 * @brief    constructor for CJsonParser class
 *
 */
CJsonParser :: CJsonParser(void)
{
}

/**
 * @brief    Distructor for CJsonParser class
 *
 */
CJsonParser::~CJsonParser(void)
{
}

/**
 * @brief   Encodes values in user defined structure to Json format.
 *
 * @details  This function encodes the information in user defined structure to 
 *           Json string format.
 *
 * @param[in][in]  obj     : Pointer to object of type ObjectValue.
 * @param[in][out] payload : reference to string(array of charecters).
 *
 * @return  ROK - If encoding is successful.
 *
 *          RFAILED - If it receives invalid object types.
 */
S16 CJsonParser :: bindPayload(ObjectValue *obj, string &payLoad)
{
   FwCb *fwCb = NULLP;

   FW_GET_CB(fwCb);

   Json::Value mainAttr; /* Json object */
   Json::FastWriter fastwriter; /* Json-style converter from Json string */
   Json::StyledWriter styled; /* Json-style writer */

   mainAttr = bindObjType(obj);

   FW_LOG_DEBUG(fwCb, (styled.write(mainAttr)).c_str());
   payLoad = fastwriter.write(mainAttr);

   return 0;
} /* End of bindPayload */

/**
 * @brief   Encodes values in an array of user defined structures to Json 
 *          Array format.
 *
 * @details  This function encodes the data in the form of array to 
 *           Json Array of objects. Also conciders objects with in array.
 *
 * @param[in][in] obj : Pointer to an object of type ArrayValue.
 *
 * @return  Json::Value object of type array.
 */
Json::Value bindObjArrayType(ArrayValue *obj)
{
   Json::Value item;
   Json::Value array;
   U16 cnt = 0;
   U16 numEntries = 0;

   FwCb *fwCb = NULLP;
   FW_GET_CB(fwCb);

   /**< Process all entries in this object, based on object type in each entry 
    * call object processing functions */
   numEntries = obj->getNumOfEntriesInObjList();
   for(cnt = 0; cnt < obj->getNumOfEntriesInObjList(); cnt++)
   {
      BaseObj *baseObj = obj->getObj(cnt);
      jsonObjType objType = baseObj->getJsonObjType();
      if(objType == JSON_OBJ_TYPE)
      {
         ObjectValue *itemObj = (ObjectValue *)baseObj;
         item[itemObj->getObjName()] = bindObjType(itemObj);
      }
      else if(objType == JSON_STRING_TYPE)
      {
         ArrayValue *itemArr = (ArrayValue *)baseObj;
         FW_LOG_DEBUG(fwCb, "Calling bindArrayType");
         item[itemArr->getArrName()] = bindStringArrayType(itemArr);
      }
      else if(objType == JSON_ARRAY_TYPE)
      {
         ArrayValue *itemArr = (ArrayValue *)baseObj;
         FW_LOG_DEBUG(fwCb, "Calling bindArrayType");
         item[itemArr->getArrName()] = bindObjArrayType(itemArr);
      }
      else if(objType == JSON_SIMPLE_TYPE)
      {
         ObjectValue *itemObj = (ObjectValue *)baseObj;
         string tagName = itemObj->getObjName();
         if(tagName.empty())
         {
            array.append(bindObjType(itemObj));
         }
         else
         {
            item = bindObjType(itemObj);
            array.append(item);
         }
      }
      array.append(item);
   }
   return array;
} /* End of bindObjArrayType */

/**
 * @brief   Encodes values in an object of user defined structures to Json 
 *          object format.
 *
 * @details  This function encodes the data in the form of object to 
 *           Json object of objects. It function also conciders the nested 
 *           objects and array within objects.
 *
 * @param[in][in] obj : Pointer to an object of type ObjectValue.
 *
 * @return  Json::Value object.
 */
PRIVATE Json::Value bindObjType(ObjectValue *obj)
{
   Json::Value item;
   U16 cnt = 0;
   U16 numEntries;

   /**< Process all entries in tagValue List */
   numEntries = obj->getNumOfEntriesInTagValList();
   for(cnt = 0; cnt < numEntries; cnt++)
   {
      tagValuePair tagValEntry = obj->getTagValEntry(cnt);
      item[tagValEntry.getTagName()] = tagValEntry.getTagValue();
   }

   /**< Process all entries in object list, in object list each entry may be 
    * an object or array of objects or array of strings */
   numEntries = obj->getNumOfEntriesInObjList();
   for(cnt = 0; cnt < numEntries; cnt++)
   {
      BaseObj *baseObj = obj->getObj(cnt);
      jsonObjType objType = baseObj->getJsonObjType();
      if(objType == JSON_OBJ_TYPE)
      {
         ObjectValue *itemObj = (ObjectValue *)baseObj;
         item[itemObj->getObjName()] = bindObjType(itemObj);
      }
      else if(objType == JSON_STRING_TYPE)
      {
         ArrayValue *itemArr = (ArrayValue *)baseObj;
         item[itemArr->getArrName()] = bindStringArrayType(itemArr);
      }
      else if(objType == JSON_ARRAY_TYPE)
      {
         ArrayValue *itemArr = (ArrayValue *)baseObj;
         item[itemArr->getArrName()] = bindObjArrayType(itemArr);
      }
      else if(objType == JSON_SIMPLE_TYPE)
      {
         ObjectValue *itemObj = (ObjectValue *)baseObj;
         item.append(bindObjType(itemObj)); 
      }
   }
   return item;
} /* End of bindObjType */

/**
 * @brief   Encodes values of type array of string type to Json format.
 *
 * @details  This function encodes the data in the form of array of strings to 
 *           Json array of strings.
 *
 * @param[in][in] obj : Pointer to an object of type ArrayValue.
 *
 * @return  Json::Value object.
 */
PRIVATE Json::Value bindStringArrayType(ArrayValue *obj)
{
   U16 cnt = 0;
   U16 numEntries = 0;
   Json::Value item;
   /**< Get all strings in string list and put them into Json object */
   numEntries = obj->getNumOfEntriesInStrList();
   for(cnt = 0; cnt < numEntries; cnt++)
   {
      string str = obj->getString(cnt);
      item.append(str);
   }
   return item;
} /* End of bindStringArrayType */

/**
 * @brief    Function to convert Json formatted string to application 
 *           specific structures.
 *
 * @details  This function converts the Json string to Json Objects and then 
 *           maps the Json object values to application specific structures.
 *
 *           The decoding is performed based on Json object type.The object 
 *           may be of type Json array(If Json object starts with [ and ends 
 *           with ]) or Json object(If Json object starts with { and ends 
 *           with }).
 *
 * @param[in][in]   payload : string or array of charectors.
 * @param[in][out]  obj     : Double pointer of type ObjectValue.
 *
 * @return  ROK     - If decoding is successful
 *
 *          RFAILED - If it receives invalid/non-compatible values.
 */
S16 CJsonParser :: unBindPayload(string &payload, ObjectValue **obj)
{
   U16 retVal = ROK;
   Json::Value mainAttr;
   Json::Reader reader;
   Json::StyledWriter styled;
   FwCb * fwCb = NULLP;

   FW_GET_CB(fwCb);

   cmMemset((U8*)&mainAttr, 0, sizeof(Json::Value));
   bool result = reader.parse(payload, mainAttr);

   if(!result)
   {
      FW_LOG_ERROR(fwCb, "Recieved incorrect Json String!!");
      FW_LOG_EXITFN(fwCb, RFAILED);
   }
   FW_LOG_DEBUG(fwCb, (styled.write(mainAttr)).c_str());
   if(mainAttr.type() == Json::arrayValue)
   {
      *obj = (ObjectValue *)unBindJsonArray(mainAttr);
   }
   else
   {
      *obj = (ObjectValue *)unBindJsonObj(mainAttr);
   }
   return retVal;
} /* End of unBindPayload */

/**
 * @brief    Function to convert Json object type to application 
 *           specific structures.
 *
 * @details  This function converts the Json object types to application 
 *           specific structures. Also takes care about nested Json objects.
 *
 * @param[in][in] jsonObj : Json::Value object.
 *
 * @return BaseObj* - Pointer to BaseObj type object. 
 *
 */
BaseObj* unBindJsonObj(Json::Value jsonObj)
{
   U16 cnt;
   Json::Value::Members names;
   ObjectValue *appObj = NULLP;
   FwCb *fwCb = NULLP;

   FW_GET_CB(fwCb);

   /**< Get all tag-names from Json object */
   names = jsonObj.getMemberNames();

   /**< Visit each object using tag name, check its object type and call 
    * appropriate unbind functions */
   U16 numEntries = names.size();
   if(!numEntries)
   {
      FW_LOG_DEBUG(fwCb, "No elements in Object");
      //return NULLP;
   }

   appObj = new ObjectValue;
   for(cnt = 0; cnt < numEntries; cnt++)
   {
      if(jsonObj[names[cnt]].type() == Json::stringValue)
      {
         appObj->pushTagValuePair(names[cnt], jsonObj[names[cnt]].asString());
      }
      else if(jsonObj[names[cnt]].type() == Json::objectValue)
      {
         ObjectValue *obj = (ObjectValue *)unBindJsonObj(jsonObj[names[cnt]]);
         if(names[cnt].empty())
         {
            obj->setjsonObjType(JSON_SIMPLE_TYPE);
         }
         else
         {
            obj->setObjName(names[cnt]);
         }
         appObj->pushObject(obj);
      }
      else if(jsonObj[names[cnt]].type() == Json::arrayValue)
      {
         ArrayValue *obj = (ArrayValue *)unBindJsonArray(jsonObj[names[cnt]]);
         obj->setArrName(names[cnt]);
         appObj->pushObject(obj);
      }
      else
      {
         FW_LOG_ERROR(fwCb, "Un-supported Json type");
         //delete appObj;
         //appObj = NULLP;
         //break;
      }
   }
   return appObj;
} /* End of unBindJsonObj */

/**
 * @brief    Function to convert Json array type to application 
 *           specific structures.
 *
 * @details  This function converts the Json array types to application 
 *           specific structures. Also takes care about handling of nested 
 *           Json arrays, Json objects, Json array of strings.
 *
 * @param[in][in]  array   : Json::Value object.
 *
 * @return BaseObj* - Pointer to BaseObj type object. 
 *
 */
BaseObj* unBindJsonArray(Json::Value array)
{
   U16 cnt;
   Json::Value::Members names;
   ArrayValue *appObj = NULLP;
   FwCb *fwCb = NULLP;

   FW_GET_CB(fwCb);

   /**< Visit all entries in Json array, cehck its type and call appropriate 
    * unbind functions */
   U16 arrSize = array.size();
   if(!arrSize)
   {
      FW_LOG_ERROR(fwCb, "No elements in Array Object");
      //return NULLP;
   }

   appObj = new ArrayValue;
   for(cnt = 0; cnt < array.size(); cnt++)
   {
      if(array[cnt].type() == Json::stringValue)
      {
         appObj->pushString(array[cnt].asString());
         appObj->setjsonObjType(JSON_STRING_TYPE);
      }
      else if(array[cnt].type() == Json::objectValue)
      {
         ObjectValue *obj = (ObjectValue *)unBindJsonObj(array[cnt]);
         obj->setjsonObjType(JSON_SIMPLE_TYPE);
         appObj->setjsonObjType(JSON_ARRAY_TYPE);
         appObj->pushObject(obj);
      }
      else if(array[cnt].type() == Json::arrayValue)
      {
         ArrayValue *obj = (ArrayValue *)unBindJsonArray(array[cnt]);
         appObj->setjsonObjType(JSON_ARRAY_TYPE);
         appObj->pushObject(obj);
      }
      else
      {
         FW_LOG_ERROR(fwCb, "Un-supported Json type");
         //delete appObj;
         //appObj = NULLP;
         //break;
      }
   }
   return appObj;
} /* End of unBindJsonArray */
/** @} */ /*end of group*/
