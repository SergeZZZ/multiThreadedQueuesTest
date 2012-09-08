#ifndef CONSUMER_H
#define CONSUMER_H


#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <DataPacket.h>

using namespace boost::posix_time;

const int process_time = 5;

template<typename QueueType>
class Consumer
{
public:
    Consumer(QueueType &_queue, int _process_time,
                    int _workerNum, int _workerTotal, int _totalCycles):
                     queue_(_queue),
                    process_time_(_process_time),  //not used
                    thisWorkerNum_(_workerNum),
                    workerTotalNum_( _workerTotal ),
                    totalCycles_(_totalCycles)
    {
    }
    void StartWorker() {
       thread_ = boost::thread(boost::bind(&Consumer::worker, boost::ref(*this)));
    }
    void waitForForker() {
        thread_.join();
    }

private:

   void worker() {
       boost::posix_time::ptime sTime = microsec_clock::local_time();
       std::cout<<"Consumer: " << thisWorkerNum_<<" Start: "<< to_simple_string(sTime)<<std::endl;

       int cycle(0);
       while(cycle++ <  totalCycles_/workerTotalNum_) {
           consumeItem();
       }

       boost::posix_time::ptime eTime = microsec_clock::local_time();
       std::cout<<"Consumer: " << thisWorkerNum_<<" Elapsed: "<< time_duration (eTime -  sTime) <<std::endl;
   }

   void consumeItem() {
       //boost::posix_time::ptime sTime = microsec_clock::local_time();
       //std::cout<<"consumeItem: Start: "<< to_simple_string(sTime)<<std::endl;

       DataPacket * packet;
       queue_.wait_and_pop(packet);
       delete packet;
       volatile int workload (0);
       while(workload < process_time*1000 )
       {
           ++workload;
       }

       //boost::posix_time::ptime eTime = microsec_clock::local_time();
       //std::cout<<"consumeItem Elapsed: "<< time_duration (eTime -  sTime) <<std::endl;

   }

   QueueType &queue_;
   int process_time_;
   boost::thread thread_;
   int thisWorkerNum_;
   int workerTotalNum_;
   int totalCycles_;
};

#endif // CONSUMER_H
