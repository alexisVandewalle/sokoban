// AppException.h
#ifndef EXCEPTIONS_H // include guard
#define EXCEPTIONS_H

#include <stdexcept>

using namespace std;

namespace soko
{
    /**
     * base class for exception handling in sokoban App
     */
    class AppException : public exception
    {
        private:
        public:
    };

    class FileNotFoundException : public AppException
    {
        private:
            string filePath;
        public:
            FileNotFoundException(string filePathAttr) : filePath(filePathAttr){}
            string getFilePath(){ return filePath; }
    };


    class FileWriteException : public AppException
    {
        private:
            string filePath;
        public:
            FileWriteException(string filePathAttr) : filePath(filePathAttr){}
            string getFilePath(){ return filePath; }
    };
}

#endif /* EXCEPTIONS_H */
