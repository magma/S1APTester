#ifndef __TMR_H__
#define __TMR_H__

#ifdef __cplusplus
extern "C"
{
#endif

#define TMR_MAX_NUM_ENTITY       255
#define TMR_MAX_NUM_INST         8  

#define TMR_CREATE_REG_ID(_ne, _ni)    ((_ne) << 8 | (_ni))


#define TMR_GET_ENT_AND_INST(_regId, _entityIdx, _instIdx) \
{\
   _instIdx = (_regId) & 0xF;\
   _entityIdx = (_regId) >> 8;\
}

#define TMR_GET_ENTCB(_ent, _inst, _tmrEntCb) \
{\
   _tmrEntCb = tmrEntDb[_ent][_inst];\
}

#define TMR_CRAETE_TMR_ID(_tmrEntCb)   (++(_tmrEntCb)->lastTmrId)


#define TMR_DFLT_LOG_LVL


#define TMR_LOG_ENTERFN() \
{\
}

#define  TMR_LOG_EXITFN(_ret) \
{\
   return _ret;\
}

#define TMR_LOG_DEBUG(...) \
{\
}

#define TMR_LOG_ERROR(...) \
{\
}

#define TMR_LOG_EXITFNVOID()



#define TMR_BASE_ERR           0

#define TMR_ERR_TMR_DB_FULL    (TMR_BASE_ERR + 1)
#define TMR_ERR_DUP_REG        (TMR_BASE_ERR + 2)
#define TMR_ERR_MEM_ALLOC      (TMR_BASE_ERR + 3) 
#define TMR_ERR_INV_TMR_ID     (TMR_BASE_ERR + 4)
#define TMR_ERR_INV_REG_ID     (TMR_BASE_ERR + 5)
#define TMR_ERR_INVALID_PARAMS (TMR_BASE_ERR + 6)
#define TMR_ERR_INV_TMR_CFG    (TMR_BASE_ERR + 7)
#define TMR_ERR_INV_ENT        (TMR_BASE_ERR + 8)
#define TMR_ERR_INV_INST       (TMR_BASE_ERR + 9)

#ifdef __cplusplus
}
#endif
#endif
