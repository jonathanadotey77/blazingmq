#ifndef INCLUDED_Z_BMQA_SESSION
#define INCLUDED_Z_BMQA_SESSION

#include <z_bmqt_sessionoptions.h>
#include <z_bmqa_messageeventbuilder.h>
#include <z_bmqa_confirmeventbuilder.h>
#include <z_bmqa_messageproperties.h>
#include <z_bmqa_event.h>
#include <z_bmqa_messageevent.h>
#include <z_bmqt_uri.h>
#include <z_bmqa_queueid.h>
#include <z_bmqa_message.h>
#include <stdint.h>

#if defined(__cplusplus)
extern "C" {
#endif

typedef struct z_bmqa_SessionEventHandler z_bmqa_SessionEventHandler;


typedef struct z_bmqa_Session z_bmqa_Session;

typedef struct z_bmqa_SessionEvent z_bmqa_SessionEvent;

typedef struct z_bmqa_OpenQueueStatus z_bmqa_OpenQueueStatus;

typedef void(*z_bmqa_SessionEventHandlerCb)(z_bmqa_SessionEvent* sessionEvent, void* data);

typedef struct EventHandlerData {
    z_bmqa_SessionEventHandlerCb callback;
    void* data;
} EventHandlerData;

// void z_bmqa_Session__setEventHandler(z_bmqa_Session* session_obj, EventHandlerData* data) {
//     if(data.callback != NULL) {
//         z_bmqa_SessionEvent* event = NULL;

//         data.callback(event, NULL);
//     }
// }

int z_bmqa_Session__create(z_bmqa_Session** session_obj, const z_bmqt_SessionOptions* options);

int z_bmqa_Session__createAsync(z_bmqa_Session** session_obj, z_bmqa_SessionEventHandler* eventHandler, const z_bmqt_SessionOptions* options);

int z_bmqa_Session__start(z_bmqa_Session* session_obj, int64_t milliseconds);

int z_bmqa_Session__startAsync();

int z_bmqa_Session__stop(z_bmqa_Session* session_obj);

int z_bmqa_Session__stopAsync(z_bmqa_Session* session_obj);

int z_bmqa_Session__finalizeStop(z_bmqa_Session* session_obj);

int z_bmqa_Session__loadMessageEventBuilder(z_bmqa_Session* session_obj, z_bmqa_MessageEventBuilder** builder);

int z_bmqa_Session__loadConfirmEventBuilder(z_bmqa_Session* session_obj, z_bmqa_ConfirmEventBuilder** builder);

int z_bmqa_Session__loadMessageProperties(z_bmqa_Session* session_obj, z_bmqa_MessageProperties** buffer);

int z_bmqa_Session__getQueueIdWithUri(z_bmqa_Session* session_obj, z_bmqa_QueueId** queueId, const z_bmqt_Uri* uri);

int z_bmqa_Session__getQueueIdWithCorrelationId(z_bmqa_Session* session_obj, z_bmqa_QueueId** queueId, const z_bmqt_CorrelationId* correlationId);

int z_bmqa_Session__openQueueSync(z_bmqa_Session* session_obj,z_bmqa_QueueId* queueId,const z_bmqt_Uri* uri,uint64_t flags /*,z_bmqa_OpenQueueStatus* out_obj*/);


// int z_bmqa_Session__openQueueAsync(z_bmqa_Session* session_obj,
//                                   z_bmqa_QueueId* queueId,
//                                   const z_bmqt_Uri* uri, uint64_t flags,
//                                   const z_bmqt_QueueOptions* options,
//                                   int64_t timeout);

int z_bmqa_Session__configureQueueSync(z_bmqa_Session* session_obj,
                                   z_bmqa_QueueId* queueId,
                                   const z_bmqt_QueueOptions* options,
                                   int64_t timeout);

// int z_bmqa_Session__configureQueueAsync(z_bmqa_Session* session_obj,
//                                    z_bmqa_QueueId* queueId,
//                                    const z_bmqt_QueueOptions* options,
//                                    int64_t timeout);

int z_bmqa_Session__closeQueueSync(z_bmqa_Session* session_obj, z_bmqa_QueueId* queueId, int64_t timeout /*,z_bmqa_CloseQueueStatus**/);

int z_bmqa_Session__closeQueueAsync(z_bmqa_Session* session_obj, z_bmqa_QueueId* queueId, int64_t timeout);

int z_bmqa_Session_nextEvent(z_bmqa_Session* session_obj, z_bmqa_Event** event_obj, int64_t timeout);

int z_bmqa_Session__post(z_bmqa_Session* session_obj, const z_bmqa_MessageEvent* event);

int z_bmqa_Session__confirmMessage(z_bmqa_Session* session_obj, const z_bmqa_Message* message);

int z_bmqa_Session__confirmMessageWithCookie(z_bmqa_Session* session_obj, const z_bmqa_MessageConfirmationCookie* cookie);

int z_bmqa_Session__confirmMessages(z_bmqa_Session* session_obj, z_bmqa_ConfirmEventBuilder* builder);

#if defined(__cplusplus)
}
#endif

#endif
