/*
 * @enum jsonObjType
 *
 * @brief  This enum defines different json object types.
 */
typedef enum
{
   JSON_SIMPLE_TYPE,
   JSON_STRING_TYPE,
   JSON_OBJ_TYPE,
   JSON_ARRAY_TYPE
}jsonObjType;

/*
 * @class BaseObj
 *
 * @brief  This class is used as base class for all Json classes.
 */
class BaseObj
{
   protected:
      jsonObjType objType; /**< To hold the object type */
   public:
      jsonObjType getJsonObjType(void); /**< Method to get json object type */
      void setjsonObjType(jsonObjType); /**< Method to set json object type */
};

/*
 * @class tagValuePair
 *
 * @brief  This class is used to store tag value pair in a json object.
 */
class tagValuePair
{
   private:
      string name; /**< To hold tag name */
      string value; /**< To hold tag value */

   public:
      void setTagValues(const string, const string); /**< Method to set tag 
                                                  and value to class members */
      string getTagName(void); /**< Method to get tag name from class member */
      string getTagValue(void); /**< Method to get tag val from class member */
};

/*
 * @class ArrayValue
 *
 * @brief  This class is used to store values from Json Array type objects.
 *         derived from the class BaseObj.
 *
 * @details This class holds follwing Json arry types.
 *          1) Array of objects
 *          Eg:
 *          [
 *             {
 *                enodebId:1234,
 *                enodebname:enb1
 *             }
 *             {
 *                enodebId:1235,
 *                enodebname:enb2
 *             }
 *          ]
 *          2) Array of strings
 *          Eg:
 *          enodebs:[enodeb1,enodeb2,enodeb3]
 *
 */
class ArrayValue : public BaseObj
{
   private:
      string arrName; /**< To store array name */
      vector<string> strList; /**< To store list of strings if array type 
                                is JSON_STRING_TYPE */
      vector<BaseObj *> objList; /**< To store list of object if array type is 
                                   JSON_ARRAY_TYPE */

   public:
      ArrayValue(void); /**< Constructor to the class */
      ~ArrayValue(void); /**< Destructor of the class */
      void setArrName(string &); /**< Method to store array name */
      void pushString(string); /**< Method to insert a string into string 
                                 list */
      void pushObject(BaseObj *); /**< Method to insert an object into object 
                                    list */
      string getArrName(void); /**< Method to get name of the array */
      U16 getNumOfEntriesInStrList(void); /**< Method to get number of 
                                               strings in string list */
      U16 getNumOfEntriesInObjList(void); /**< Method to get number of 
                                               objects in object list */
      string getString(U16); /**< Method to get a string entry from string 
                                  list using input parameter */
      BaseObj* getObj(U16); /**< Method to get an object from object list 
                                 using input parameter */
};

/*
 * @class ObjectValue
 *
 * @brief  This class is used to store values from Json object.
 *         derived from the class BaseObj.
 *
 * @details This class holds following object types.
 *         1) Json simple object
 *            Eg:
 *            {
 *               username:radisys,
 *               password:radisys
 *            }
 *         2) Json nested objects
 *            Eg:
 *             {
 *                ossname:OSS-RC_1,
 *                anrfunceutran:{
 *                   anrinterfreqstate:DEACTIVE|ACTIVE,
 *                   anrintrafreqstate:DEACTIVE|ACTIVE
 *                }
 *             }
 *         3) Json objects containing arrays
 *            Eg:
 *             {
 *                ossname:OSS-RC_1,
 *                enodebs:[
 *                   {
 *                      enodebId:1234,
 *                      enodebname:enb1
 *                   },
 *                   {
 *                      enodebId:1234,
 *                      enodebname:enb1
 *                   }
 *                ]
 *             }
 *
 */
class ObjectValue : public BaseObj
{
   private:
      string objName; /**< To store object name */
      vector<tagValuePair> tagValueEntries; /**< To store tag-value entry */
      vector<BaseObj *> objList; /**< To store objects */

   public:
      ObjectValue(); /**< Constructor of the class */
      ~ObjectValue(); /**< Destructor of the class */
      void setObjName(string); /**< Method to set object name */
      void pushTagValEntry(tagValuePair &); /**< Method to insert tagValuePair 
                                              object into tag-value list */
      void pushObject(BaseObj *); /**< Method to insert an object inot object 
                                    list */
      string getObjName(void); /**< Method to get object name */
      U16 getNumOfEntriesInTagValList(void); /**< Method to get number of 
                                                  entries in tag-value list */
      U16 getNumOfEntriesInObjList(void); /**< Method to get number of 
                                               entries in object list */
      tagValuePair getTagValEntry(U16); /**< Method to get tag-value entry 
                                             at input parameter index */
      BaseObj* getObj(U16); /**< Method to get an object entry at input 
                                 parameter index */
      void pushTagValuePair(string, string); /**< Method to insert a tag-value
                          entry using tag-name and tag-value as input string */
};

/*
 * @class CJsonParser
 *
 * @brief  This class contains metods to bind and unbinding of Json object.
 */
class CJsonParser
{
   public:
      CJsonParser();
      ~CJsonParser();

      S16 bindPayload(ObjectValue *, string &); /**< Method to create Json 
                                                    string. */
      S16 unBindPayload(string &, ObjectValue **); /**< Method to convert 
                                        Json string to Network tree element. */
   private:
};
