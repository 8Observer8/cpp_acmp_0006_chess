#include <string>
#include <stdexcept>

//#define TESTING
#ifndef TESTING

#include <iostream>
#include <fstream>

class FileError : public std::runtime_error {
public:

    FileError( const std::string &fileNameIn ) :
        std::runtime_error( "" ),
        m_fileName( fileNameIn ) {
    }

    virtual const char *what( ) const throw () {
        return m_message.c_str( );
    }

    virtual ~FileError( ) throw () {
    }

protected:
    std::string m_fileName;
    std::string m_message;
};

class FileOpenError : public FileError {
public:

    FileOpenError( const std::string &fileName ) : FileError( fileName ) {
        m_message = "Unable to open file " + m_fileName;
    }
};

class FileReadError : public FileError {
public:

    FileReadError( const std::string &fileName ) : FileError( fileName ) {
        m_message = "Error reading " + m_fileName;
    }
};

class FileWriteError : public FileError {
public:

    FileWriteError( const std::string &fileName ) : FileError( fileName ) {
        m_message = "Error writing " + m_fileName;
    }
};
#endif

class LogicError : public std::logic_error {
public:

    LogicError( ) : std::logic_error( "" ) {

    }

    virtual const char *what( ) const throw () {
        return m_message.c_str( );
    }

    virtual ~LogicError( ) throw () {

    }

protected:
    std::string m_message;
};

class EmptyArgument : public LogicError {
public:

    EmptyArgument( ) {
        m_message = "Error: empty argument";
    }
};

class BadArgument : public LogicError {
public:

    BadArgument( const std::string &argument ) {
        m_message = "Bad argument: " + argument;
    }
};

#ifndef TESTING

void readData( const std::string &fileName, std::string &textOfMove)
throw( FileOpenError, FileReadError );

void writeResult( const std::string &fileName, const std::string &result )
throw( FileOpenError, FileWriteError );

bool isCorrectMove( const std::string &textOfMove )
throw( EmptyArgument, BadArgument );

int main( ) {

    std::string fileNameIn = "input.txt";
    std::string textOfMove;

    // Read the input data
    try {
        readData( fileNameIn, textOfMove );
    } catch( const FileError &e ) {
        std::cerr << e.what() << std::endl;
        return 1;
    } catch( ... ) {
        std::cerr << "Error: unknown exception" << std::cerr;
        return 1;
    }

    // Data processing
    std::string result;
    try {
        if ( isCorrectMove( textOfMove ) ) {
            result = "YES";
        } else {
            result = "NO";
        }
    } catch( const BadArgument &e ) {
        result = "ERROR";
    } catch( const LogicError &e ) {
        std::cerr << e.what( ) << std::endl;
        return 1;
    } catch( ... ) {
        std::cerr << "Error: unknown exception" << std::endl;
        return 1;
    }

    // Write the result to the output file
    std::string fileNameOut = "output.txt";
    try {
        writeResult( fileNameOut, result );
    } catch( const FileError &e ) {
        std::cerr << e.what( ) << std::endl;
        return 1;
    } catch ( ... ) {
        std::cerr << "Error: unknown exception" << std::endl;
        return 1;
    }

    return 0;
}

void readData( const std::string &fileName, std::string &textOfMove)
throw( FileOpenError, FileReadError ) {
    // Open the input file for reading
    std::ifstream file;
    file.open( fileName.c_str( ) );
    if ( file.fail( ) ) {
        throw FileOpenError( fileName );
    }

    // Read data from the input file
    if ( !( file >> textOfMove ) ) {
        throw FileReadError( fileName );
    }
}

void writeResult( const std::string &fileName, const std::string &result )
throw( FileOpenError, FileWriteError ) {
    // Open the output file for writing
    std::ofstream file;
    file.open( fileName.c_str( ) );
    if ( file.fail( ) ) {
        throw FileOpenError( fileName );
    }

    // Write data to the output file
    if ( !( file << result << std::endl ) ) {
        throw FileWriteError( fileName );
    }
}
#endif

bool isCorrectMove( const std::string &textOfMove )
throw( EmptyArgument, BadArgument ) {
    return true;
}
