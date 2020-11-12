// The MIT License (MIT)

// Copyright (c) 2014 Mohammad Dashti
// (www.mdashti.com - mohammad.dashti [at] epfl [dot] ch - mdashti [at] gmail [dot] com)

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#ifdef _MSC_VER
#pragma warning(disable : 4786)  // identifier too long
#endif


#ifndef FILEPATH_HPP
#define FILEPATH_HPP


#include <string>
#include <sstream>
#include <list>
#include <locale>
#include <cstdlib>
#include <cstdio>

using namespace std;

namespace dbtoaster
{
    class path_delimiters
    {
    public:
        static bool is_path_delim(char c)      { return (c == '/') || (c == '\\'); }
        static bool is_drive_delim(char c)     { return (c == ':'); }
        static bool is_scheme_delim(char c)    { return (c == ':'); }
        static bool is_port_delim(char c)      { return (c == ':'); }
        static bool is_query_delim(char c)     { return (c == '?'); }
        static bool is_extension_delim(char c) { return (c == '.'); }

        static char path_delim()      { return '/'; }
        static char drive_delim()     { return ':'; }
        static char scheme_delim()    { return ':'; }
        static char port_delim()      { return ':'; }
        static char query_delim()     { return '?'; }
        static char extension_delim() { return '.'; }

        static const char* unknown_scheme() { return "unknown"; }
    };

    typedef std::list<std::string>::const_iterator list_itr;

    // basic_filepath<char, delimT>
    template<typename delimT = path_delimiters >
    class basic_filepath
    {
    public:
        // constructors

        basic_filepath() {
            // empty path
            parse(std::string().c_str());
        }


        basic_filepath(const char* path) {
            parse(path);
        }


        basic_filepath(const std::string& path) {
            parse(path.c_str());
        }

        // operator overloads
        basic_filepath<delimT>&
        operator=(const basic_filepath<delimT>& rhs) {
            if (this != &rhs) {
                parse(rhs.str().c_str());
            }
            return *this;
        }

        // operator overloads
        basic_filepath<delimT>&
        operator/=(const char* path) {
            string s(path);
            s = str()+delimT::path_delim()+s;
            parse(s.c_str());
            return *this;
        }

        // operator overloads
        basic_filepath<delimT>&
        operator/=(const string& path) {
            return operator/=(path.c_str());
        }


        // stringify
        std::string str() const {
            std::basic_ostringstream<char> s;
            
            // add URL elements
            if (is_url()) {
                s << m_scheme;
                s << delimT::scheme_delim();
                s << delimT::path_delim();
                s << delimT::path_delim();
                s << m_server;
                if (m_port != 0) {
                    s << delimT::port_delim();
                    s << m_port;
                }
            }

            // add Windows elements
            if (is_windows()) {
                s << m_drive;
                s << delimT::drive_delim();
            }

            // add leading path delimiter if absolute
            if (m_is_absolute) {
                s << delimT::path_delim();
            }

            // add directories
            for (list_itr i = m_path_segments.begin();
                 i != m_path_segments.end();
                 i++) {
                s << *i << delimT::path_delim();
            }

            // add file and extension
            if (m_file.length() > 0) {
                s << m_file;
                if (m_extension.length() > 0) {
                    s << delimT::extension_delim() << m_extension;
                }
            }

            // final URL elements
            if (is_url() && m_query.length() > 0) {
                s << delimT::query_delim() << m_query;
            }

            return s.str();
        }


        // Windows/DOS
        
        bool is_windows() const {
            return (m_drive != char());
        }


        void set_drive(char drive) const {
            m_drive = drive;
        }


        char get_drive() const {
            return m_drive;
        }


        // URL

        bool is_url() const {
            return (m_scheme.length() != 0);
        }


        void set_scheme(const std::string& scheme) {
            m_scheme = scheme;
        }


        std::string get_scheme() const {
            return m_scheme;
        }

        void set_server(const std::string& server) {
            if (is_url() == false) {
                m_scheme = delimT::unknown_scheme();
            }
            m_server = server;
        }

        std::string get_server() const {
            return m_server;
        }

        void set_port(int port) {
            if (is_url() == false) {
                m_scheme = delimT::unknown_scheme();
            }
            m_port = port;
        }

        int get_port() const {
            return m_port;
        }

        void set_query(const std::string& query) {
            if (is_url() == false) {
                m_scheme = delimT::unknown_scheme();
            }
            m_query = query;
        }

        std::string get_query() const {
            return m_query;
        }


        // general        

        bool is_absolute() const {
            return m_is_absolute;
        }


        std::string get_path() const {
            std::string r;
            if (m_is_absolute) {
                r = delimT::path_delim();
            }

            for (list_itr i = m_path_segments.begin();
                 i != m_path_segments.end();
                 i++) {
                r += *i;
                r += delimT::path_delim();
            }
            return r;
        }


        bool has_file() const {
            return (m_file.length() != 0);
        }


        void set_file(const std::string& file) {
            m_file = file;
        }


        std::string get_file() const {
            return m_file;
        }


        std::string filename() const {
            return m_file;
        }


        void set_extension(const std::string& extension) {
            m_extension = extension;
        }

        
        std::string get_extension() {
            return m_extension;
        }

        basic_filepath& make_preferred() {
            return *this;
        }


    private:
        void parse(const char* s) {
            // initialize
            m_is_absolute = false;
            m_drive = char();
            m_scheme = std::string();
            m_server = std::string();
            m_port = 0;
            m_query = std::string();
            m_path_segments.clear();
            m_file = std::string();
            m_extension = std::string();

            // check for Windows path first
            if (std::isalpha(s[0]) &&
                    delimT::is_drive_delim(s[1]) &&
                    delimT::is_path_delim(s[2])) {
                m_drive = s[0];
                m_is_absolute = true;
                s += 3;
            }

            const char* p = s;

            if (!is_windows()) {
                // check for URL
                while (*p) {
                    if (delimT::is_scheme_delim(*p)) {
                        m_scheme = std::string(s, p - s);
                        s = p + 1;

                        // possibly skip the next two path delimiters
                        if (delimT::is_path_delim(*s)) {
                            s++;
                        }
                        if (delimT::is_path_delim(*s)) {
                            s++;
                        }
                        break;
                    }
                    p++;
                }

                // if we found a URL, parse server/port
                if (m_scheme.length() > 0) {
                
                    // server
                    while (*s) {
                        if (delimT::is_port_delim(*s) ||
                            delimT::is_path_delim(*s)) {
                            break;
                        }
                        m_server += *s;
                        s++;
                    }

                    // port
                    if (delimT::is_port_delim(*s)) {
                        s++;
                        std::string port;
                        while (*s && !delimT::is_path_delim(*s)) {
                            port += *s;
                            s++;
                        }

                        std::basic_istringstream<char> is(port);
                        is >> m_port;
                    }
                }
            }

            // parse path list
            std::string c;
            while (*s) {
                // if it's a path delimiter, add it to the path list
                if (delimT::is_path_delim(*s)) {
                    if (c.length() > 0) {
                        m_path_segments.push_back(c);
                    } else {
                        // if first segment is empty
                        // (first path character is /),
                        // path is absolute
                        if (m_path_segments.size() == 0) {
                            m_is_absolute = true;
                        }
                    }
                    c = std::string();
                    s++;
                    continue;
                }

                c += *s;
                s++;
            }

            // parse filename in c
            const char* q = c.c_str();
            p = q;
            while (*p) {
                if (delimT::is_query_delim(*p)) {
                    // grab the query string
                    m_query = p + 1;
                    break;
                }
                p++;
            }

            // get a file+extension string
            std::string file(q, p - q);
            int pos = -1;
            for (int i = file.length() - 1; i >= 0; i--) {
                if (delimT::is_extension_delim(file[i])) {
                    pos = i;
                    break;
                }
            }

            if (pos == -1) {
                m_file = file;
            } else {
                m_file = file.substr(0, pos);
                m_extension = file.substr(pos + 1, file.length() - pos - 1);
            }
        }


    private:
        bool m_is_absolute;

        // windows
        char m_drive;

        // URL
        std::string m_scheme;
        std::string m_server;
        int    m_port;
        std::string m_query;

        // general
        std::list<std::string> m_path_segments;
        std::string m_file;
        std::string m_extension;        
    };


    typedef basic_filepath<>    path;

    inline bool file_exists (const std::string& name) {
        path p(name.c_str());
        if (FILE *file = fopen(p.str().c_str(), "r")) {
            fclose(file);
            return true;
        } else {
            return false;
        }   
    }

#include <stdio.h>  /* defines FILENAME_MAX */
#ifdef WINDOWS
    #include <direct.h>
    #define GetCurrentDir _getcwd
#else
    #include <unistd.h>
    #define GetCurrentDir getcwd
#endif

#define ERR_CURRENT_DIR_NOT_ACCESSIBLE 22

    inline path current_path() {
        char cCurrentPath[FILENAME_MAX];
        if (!GetCurrentDir(cCurrentPath, sizeof(cCurrentPath)))
        {
            throw ERR_CURRENT_DIR_NOT_ACCESSIBLE;
        }
        cCurrentPath[sizeof(cCurrentPath) - 1] = '\0'; /* not really required */
        return path(cCurrentPath);
    }

    inline std::ostream& operator<< (std::ostream& o, path const& p)
    {
      return o << p.str();
    }
} // end namespace

#endif // FILEPATH_HPP
