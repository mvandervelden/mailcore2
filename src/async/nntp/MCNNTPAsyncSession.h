#ifndef MAILCORE_MCNNTPASYNCSESSION_H

#define MAILCORE_MCNNTPASYNCSESSION_H

#include <MailCore/MCBaseTypes.h>

#ifdef __cplusplus

namespace mailcore {
    
    class NNTPOperation;
    class NNTPSession;
    class NNTPFetchHeaderOperation;
    class NNTPFetchArticleOperation;
    class MCNNTPFetchArticlesOperation;
    class NNTPListNewsgroupsOperation;
    class NNTPOperationQueueCallback;
    class NNTPConnectionLogger;
    
    class NNTPAsyncSession : public Object {
    public:
        NNTPAsyncSession();
        virtual ~NNTPAsyncSession();
        
        virtual void setHostname(String * hostname);
        virtual String * hostname();
        
        virtual void setPort(unsigned int port);
        virtual unsigned int port();
        
        virtual void setUsername(String * login);
        virtual String * username();
        
        virtual void setPassword(String * password);
        virtual String * password();
        
        virtual void setConnectionType(ConnectionType connectionType);
        virtual ConnectionType connectionType();
        
        virtual void setTimeout(time_t timeout);
        virtual time_t timeout();
        
        virtual void setCheckCertificateEnabled(bool enabled);
        virtual bool isCheckCertificateEnabled();
        
        virtual void setConnectionLogger(ConnectionLogger * logger);
        virtual ConnectionLogger * connectionLogger();
        
#ifdef __APPLE__
        virtual void setDispatchQueue(dispatch_queue_t dispatchQueue);
        virtual dispatch_queue_t dispatchQueue();
#endif
        
        virtual MCNNTPFetchArticlesOperation * fetchArticlesOperation(String * group);
        
        virtual NNTPFetchHeaderOperation * fetchHeaderOperation(String * groupName, unsigned int index);
        
        virtual NNTPFetchArticleOperation * fetchArticleOperation(String *groupName, unsigned int index);
        
        virtual NNTPListNewsgroupsOperation * listAllNewsgroupsOperation();
        virtual NNTPListNewsgroupsOperation * listSubscribedNewsgroupsOperation();
        
        virtual NNTPOperation * disconnectOperation();
        
        virtual NNTPOperation * checkAccountOperation();
        
    private:
        NNTPSession * mSession;
        OperationQueue * mQueue;
        NNTPOperationQueueCallback * mQueueCallback;
        ConnectionLogger * mConnectionLogger;
        pthread_mutex_t mConnectionLoggerLock;
        NNTPConnectionLogger * mInternalLogger;
        
    public: // private
        virtual void runOperation(NNTPOperation * operation);
        virtual NNTPSession * session();
        virtual void logConnection(ConnectionLogType logType, Data * buffer);
    };
    
}

#endif

#endif
