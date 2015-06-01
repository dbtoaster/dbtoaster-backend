/*
 * iprogram.hpp
 *
 *  Created on: May 8, 2012
 *      Author: daniel
 */

#ifndef DBTOASTER_IPROGRAM_H
#define DBTOASTER_IPROGRAM_H

#include <thread>
#include <condition_variable>
#include <mutex>
#include <future>
#include <functional>
#include <cassert>
#include "serialization.hpp"

namespace dbtoaster {

struct event_t;
struct tlq_t;

/**
 * IProgram is the base class for executing sql programs. It provides
 * functionality for running the program in synchronous or asynchronous mode
 * and recording intermediate or final snapshots of the results.
 *
 * The 'TLQ_T' class parameter represents the data-structure used for 
 * storing the results of the program.
 */

class IProgram {
public:
    typedef std::shared_ptr<tlq_t> snapshot_t;

    IProgram() :
        running(false)
        , finished(false)
        , snapshot_ready(true)
        , snapshot_request(false)
    {}
    virtual ~IProgram() {
    }

    /**
     * This should get overridden by a function that does initialization work,
     * such as processing the static table tuples.
     */
    virtual void init() = 0;

    /**
     * Executes the program by launching the virtual method 'process_streams()'.
     * @param async If 'true' the execution is performed in a separate thread.
     */
    void run( bool async = false );

    /**
     * This function provides a way for testing whether the program has 
     * finished or not when run in asynchronous mode.
     * @return 'true' if the program has finished execution.
     */
    bool is_finished()
    {
        return finished;
    }

    /**
     * Obtains a snapshot of the results of the program. If the program is
     * currently running in asynchronous mode, it will make sure that the
     * snapshot is consistent.
     * @return A snapshot of the 'TLQ_T' data-structure representing 
     *         the results of the program.
     */
    snapshot_t get_snapshot();

protected:
    /**
     * This should get overridden by a function that reads stream events and
     * processes them by calling process_stream_event().
     */
    virtual void process_streams() = 0;

    /**
     * This should get overridden by a function that processes an event by
     * calling the appropriate trigger. This function can also be used for
     * performing additional tasks before or after processing an event, such
     * as handling requests for consistent snapshots of the results.
     * In order to preserve functionality, functions that override it should
     * call their base class variants.
     * @param ev The event being processed.
     */
    virtual void process_stream_event(const event_t& ev);

    /**
     * Virtual function that should implement the functionality of taking
     * snapshots of the results of the program.
     * @return The collected snapshot.
     */
    virtual snapshot_t take_snapshot() = 0;

    /**
     * Tests the running state of the program.
     * @return 'true' if the program is currently being executed.
     */
    bool is_running(){ return running; }

    /**
     * Signal the beginning of the execution of the program.
     */
    void start_running();
    /**
     * Signal the end of the execution of the program.
     */
    void stop_running();

    /**
     * Function for processing requests for program results snapshot.
     * Gets executed only between the processing of events and not during,
     * in order to get consistent results.
     */
    void process_snapshot();

    /*
     * Function for recording a request for a snapshot.
     */
    void request_snapshot();

    /**
     * Function for waiting for a previously recorded snapshot request to
     * complete.
     * @return The snapshot taken as a response of a previously recorded 
     *         request.
     */
    snapshot_t wait_for_snapshot();

private:
    bool running;
    bool finished;
    std::mutex running_mtx;

    std::condition_variable snapshot_ready_cond;
    std::mutex snapshot_ready_mtx;
    bool snapshot_ready;

    bool snapshot_request;
    snapshot_t snapshot;
};
}

#endif /* DBTOASTER_DBT_IPROGRAM_H */
