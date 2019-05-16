#ifndef GNUPLOT_H
#define GNUPLOT_H

#include <string>
#include <stdexcept>
#include <sstream>
#include <fstream>

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__TOS_WIN__)
//defined for 32 and 64-bit environments
 #include <io.h>                // for _access(), _mktemp()
#elif defined(unix) || defined(__unix) || defined(__unix__) || defined(__APPLE__)
//all UNIX-like OSs (Linux, *BSD, MacOSX, Solaris, ...)
 #include <unistd.h>            // for access(), mkstemp()
 #define GP_MAX_TMP_FILES  64
#else
 #error unsupported or unknown operating system
#endif

class GnuplotException : public std::runtime_error{
public:
    GnuplotException(const std::string &msg) : std::runtime_error(msg){}
};

class Gnuplot{
        FILE* pipe;
        std::string command;
        int fileIterator;

        //wspolrzedne do rysowania wykresu dwuwymiarowego
        int coord1;
        int coord2;
public:
    Gnuplot(const std::string& gnuplot_path = "gnuplot") : command(""), fileIterator(0), coord1(0), coord2(1){
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__TOS_WIN__)
        pipe = _popen(gnuplot_path.c_str(), "w");
#elif defined(unix) || defined(__unix) || defined(__unix__) || defined(__APPLE__)
        pipe = popen(gnuplot_path.c_str(), "w");
#endif
        if(pipe == nullptr){
            throw GnuplotException("Couldn't open connection to gnuplot");
        }
    }

    ~Gnuplot(){
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__TOS_WIN__)
        _pclose(pipe);
#elif defined(unix) || defined(__unix) || defined(__unix__) || defined(__APPLE__)
        pclose(pipe);
#endif
    }

    void setCoord(int coord1, int coord2){
        this->coord1 = coord1;
        this->coord2 = coord2;
    }

    void execute(){
        fputs((command + "\n").c_str(), pipe);
        fflush(pipe);
        command = "";
        fileIterator = 0;
    }

    void addElements(const double* const* begin, const double* const* end, const std::string& style = "with points", const std::string& fileid = ""){
        std::ostringstream filename;
        filename << "/tmp/gnuplot";
        if(fileid == "")
            filename << fileIterator++;
        else
            filename << fileid;
        std::ofstream os(filename.str());
        while(begin != end){
            os << (*begin)[coord1] << " " << (*begin)[coord2] << std::endl;
            begin++;
        }
        os.close();
        if(fileIterator > 1)
            command += ", ";
        else
            command += "plot ";
        command += "\"" + filename.str() + "\" ";
        command += "notitle ";
        command += style;
    }

    Gnuplot& operator<<(const std::string& cmd){
        command += cmd;
        return *this;
    }

    Gnuplot& operator<<(int value){
        command += std::to_string(value);
        return *this;
    }

    Gnuplot& operator<<(double value){
        command += std::to_string(value);
        return *this;
    }
};

#endif //GNUPLOT_H
