
namespace dbtoaster{
    class CustomProgram_1 : public Program
    {
    public:
        void process_stream_event(const event_t& ev) {
            cout << "on_" << dbtoaster::event_name[ev.type] << "_";
            // cout << get_relation_name(ev.id) << "(" << ev.data << ")" << endl;

            Program::process_stream_event(ev);
        }
    };

    class CustomProgram_2 : public Program
    {
    public:
        void process_streams() {
            for( long i = 1; i <= 10; ++i ) {
                event_args_t ev_args;
                ev_args.push_back(std::shared_ptr<long>(new long(i)));
                ev_args.push_back(std::shared_ptr<long>(new long(i+10)));
                event_t ev( insert_tuple, get_relation_id("S"), 0, ev_args);

                process_stream_event(ev);
            }
        }
    };
}


/**
 * In order to compile this file one would have to include a header containing
 * the definition of "dbtoaster::Program" and "dbtoaster::Program::snapshot_t"
 * as generated by the dbtoaster C++ code generator. Using the "-c" dbtoaster
 * command line option the generated header file is automatically included and
 * compiled against this file.
 */

/**
 * Determines whether "--async" was specified as a command line argument.
 *
 * @param argc
 * @param argv
 * @return true if "--async" is one of the command line arguments
 */
bool async_mode(int argc, char* argv[])
{
    for(int i = 1; i < argc; ++i)
        if( !strcmp(argv[i],"--async") )
            return true;
    return false;
}

/**
 * Main function that executes the sql program corresponding to the header file
 * included. If "-async" is among the command line arguments then the execution
 * is performed asynchronous in a seperate thread, otherwise it is performed in
 * the same thread. If performed in a separate thread and while not finished it
 * continuously gets snapshots of the results and prints them in xml format. At
 * the end of the execution the final results are also printed.
 *
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, char* argv[]) {
    dbtoaster::Program p(argc,argv);
    bool async = p.is_async(); //async_mode(argc,argv);
    bool no_output = p.is_no_output();
    //dbtoaster::CustomProgram_1 p;
    //dbtoaster::CustomProgram_2 p;
    dbtoaster::Program::snapshot_t snap;

    // if(!no_output) cout << "Initializing program:" << endl;
    p.init();

    // if(!no_output) cout << "Running program:" << endl;
    p.run( async );
    while( !p.is_finished() )
    {
       snap = p.get_snapshot();
       DBT_SERIALIZATION_NVP_OF_PTR(cout, snap);
    }

    // if(!no_output) cout << "Printing final result:" << endl;
    if(!no_output) {
        snap = p.get_snapshot();
        DBT_SERIALIZATION_NVP_OF_PTR(cout, snap);
        cout << std::endl;
    }
    return 0;
}
