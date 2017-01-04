//
//  main.cpp
//  thread
//
//  Created by 冯文斌 on 16/12/7.
//  Copyright © 2016年 kelvin. All rights reserved.
//

#include <iostream>
#include <pthread.h>
#include <uv.h>
#include <string.h>
#include "db_client_manager.hpp"

using namespace std;

uint64_t repeat = 0;

static void OnUVTimer(uv_timer_t *handle) {
    g_pDBClientMgr->Activate();
}

int main(int argc, const char * argv[]) {
    
    g_pDBClientMgr = new KDBClientMgr;
    
    uv_loop_t *loop = uv_default_loop();
    uv_timer_t timer_req;
    uv_timer_init(loop, &timer_req);
    uv_timer_start(&timer_req, OnUVTimer, 0, 1000);
    
    string szTbName = "account";
    string szKey = "key";
    string szValue = "test2222";
    
    IKG_Buffer* pHsetBuffer = DB_CreateHsetBuffer(szTbName, szKey,szValue);
    g_pDBClientMgr->PushRedisRequest(1, pHsetBuffer);
    g_pDBClientMgr->PushMysqlRequest(1, pHsetBuffer);
    
    //IKG_Buffer* pSetBuffer = DB_CreateSetBuffer(szTbName, szKey,szValue);
    //g_pDBClientMgr->PushRedisRequest(1, pSetBuffer);
    //g_pDBClientMgr->PushMysqlRequest(1, pSetBuffer);
    
    //IKG_Buffer* pGetBuffer = DB_CreateGetBuffer(szTbName, szKey);
    //g_pDBClientMgr->PushRedisRequest(1, pGetBuffer);
    //g_pDBClientMgr->PushMysqlRequest(1, pGetBuffer);
    //g_pDBClientMgr->RequestMySQLQuery(1, pGetBuffer);
    
    //IKG_Buffer* pRedisSetBuffer = DB_CreateSetBuffer(tb, key,value);
    //g_pDBClientMgr->PushRedisRequest(1, pRedisSetBuffer);
    
    /*IKG_Buffer* pGetBuffer = DB_CreateRedisGetBuffer(key);
    g_pDBClientMgr->PushRedisRequest(1, pGetBuffer);
    
    IKG_Buffer* pExpireBuffer = DB_CreateRedisExpireBuffer(key, 5);
    g_pDBClientMgr->PushRedisRequest(1, pExpireBuffer);
    
    string szKey = "hkey";
    string szField = "hfiled";
    string szValue = "hvalue11";
    
    IKG_Buffer* pHsetBuffer = DB_CreateRedisHsetBuffer(szKey, szField, szValue);
    g_pDBClientMgr->PushRedisRequest(1, pHsetBuffer);
    
    IKG_Buffer* pHgetBuffer = DB_CreateRedisHgetBuffer(szKey, szField);
    g_pDBClientMgr->PushRedisRequest(1, pHgetBuffer);
    
    IKG_Buffer* pDelBuffer = DB_CreateRedisDelBuffer(key);
    g_pDBClientMgr->PushRedisRequest(1, pDelBuffer);
    
    IKG_Buffer* pHdelBuffer = DB_CreateRedisHdelBuffer(szKey, szField);
    g_pDBClientMgr->PushRedisRequest(1, pHdelBuffer);*/
    
    //IKG_Buffer* pHgetBuffer = DB_CreateHgetBuffer(szTbName, szKey);
    //g_pDBClientMgr->PushRedisRequest(1, pHsetBuffer);
    //g_pDBClientMgr->RequestMySQLQuery(1, pHgetBuffer);
    
    //IKG_Buffer* pHdelBuffer = DB_CreateDelBuffer(szTbName, szKey);
    //g_pDBClientMgr->PushRedisRequest(1, pHdelBuffer);
    //g_pDBClientMgr->PushMysqlRequest(1, pHdelBuffer);
    
    //IKG_Buffer* pHdelBuffer = DB_CreateHdelBuffer(szTbName, szKey);
    //g_pDBClientMgr->PushRedisRequest(1, pHdelBuffer);
    //g_pDBClientMgr->PushMysqlRequest(1, pHdelBuffer);
    
    return uv_run(loop, UV_RUN_DEFAULT);
}
