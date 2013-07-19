///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Headers //////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <QCoreApplication>
#include "QtCGI.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Main() ///////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * @paragraph This function executes the application
 * @brief main()
 * @param int intArguments
 * @param char* charArguments[]
 * @return int
 */
int main(int intArguments, char* charArguments[])
{
        // Initializet the application
        QCoreApplication qcaGeoData(intArguments, charArguments);
        // Instatiate the CGI mapper
        QtCGI::Instance(true);
        // Set the header type
        QtCGI::Instance()->SetContentType(QtCGI::ContentTypeHTML);
        // Create the response placeholder
        QString strResponse = "<html><head><title>QtCGI</title></head><body><h1>Hello World!</h1><hr>";
        // Check for POST data
        if (QtCGI::Instance()->GetParam("firstName").isEmpty()) {
                // Add the form
                strResponse.append("<form action=\"helloWorld.qgi\" method=\"post\"><input name=\"firstName\" placeholder=\"What is your name?\" type=\"text\"><input type=\"submit\" value=\"Go!\"></form>");
        } else {
                // Display the name
                strResponse.append(QString("Hello <strong>%1</strong>!").arg(QtCGI::Instance()->GetParam("firstName")));
        }
        // Set the content
        QtCGI::Instance()->SetContent(strResponse);
        // Write the content
        QtCGI::Instance()->WriteResponse();
        // Return the application execution
        qcaGeoData.exit();
}
