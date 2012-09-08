#include <boost/pool/pool.hpp>
#include <boost/pool/pool_alloc.hpp>
#include <boost/pool/object_pool.hpp>
#include <list>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/function.hpp>
#include <boost/signal.hpp>
#include <boost/bind.hpp>
#include <StandardQueue.h>
#include <boost/foreach.hpp>
#include "Consumer.h"


#define process_time 5

const int cycles = 500000;

const int workerNum = 2;

typedef StandardQueue < DataPacket* > StandardQueueType;

typedef boost::shared_ptr<Consumer<StandardQueueType> > ConsumerPtr;


int main(int argc, char *argv[])
{
    StandardQueueType queue;

    std::list <ConsumerPtr> workerPool;
    for (int i =0 ; i<workerNum ; ++i) {
        workerPool.push_back(ConsumerPtr(new Consumer <StandardQueueType >(queue, 0, i, workerNum, cycles)));
    }

    BOOST_FOREACH(ConsumerPtr consumer, workerPool)
    {
        consumer->StartWorker();
    }

    int cycle(0);
    while(cycle++ <  cycles) {
        DataPacket *packet = new DataPacket();
        queue.push(packet);
    }

    BOOST_FOREACH(ConsumerPtr consumer, workerPool)
    {
        consumer->waitForForker();
    }

}





